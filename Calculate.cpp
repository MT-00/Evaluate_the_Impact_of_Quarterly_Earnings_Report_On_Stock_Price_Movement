#include "Calculate.hpp"
#include <iostream>
#include <vector>
#include <ctime>
#include <map>
#include<iostream>
#include<vector>
#include <stdlib.h> /* srand, rand */
#include <time.h> /* time */
#include <numeric>
#include<string>
#include<algorithm>
#include<list>
#include<set>
#include <math.h>

using namespace std;
typedef vector<double> Vector;


// to do bootstrap
vector<string> random_select(vector<string> symbol)
{
    
   
    do{
       // srand( (unsigned int) time(NULL) );
        symbol.erase(symbol.begin()+rand()%symbol.size());
    }
    while(symbol.size()>30);
    return symbol;
}

vector<double> CAAR::CalculateCAAR()
{
    // Extract the symbol in the map to the vector symbol
    for(std::map<string,Stock>::iterator it = map.begin(); it != map.end(); ++it)
    {
        symbol.push_back(it->first);
        
    }
    random_.resize(30);
    for (int i=0;i<30;i++)
    {
        random_[i]=random_select(symbol);
    }
    //Put all stock return vectors in the rit vector;Put DateLoc in findloc vector.
    Rit.resize(30);
    Findloc.resize(30);
    for (int i=0;i<30;i++)
    {
        random_[i].resize(30);
        for (int j=0;j<30;j++)
        {
            std::map<string,Stock>::iterator itr= map.find(random_[i][j]);
            if(itr!=map.end())
            {
                Rit[i].push_back(itr->second.r);
                
                Findloc[i].push_back(itr->second.DateLoc);
            }
        }
    }
    //Calculate ARIT
    for (int i=0;i<30;i++)
    {
        Rit[i].resize(30);
        Findloc[i].resize(30);
        for (int j=0;j<30;j++)
        {
            Rit[i][j].resize(61);
            for (int m=0;m<61;m++)
            {
                Rit[i][j][m]=Rit[i][j][m]-(RSPY[Findloc[i][j]+m-30]);
            }
        }
    }
    //Calculate AAR
    AAR.resize(30);
    for (int i=0;i<30;i++)
    {
        AAR[i].resize(61);
        for(int m=0;m<61;m++)
        {
            for (int j=0;j<30;j++)
            {
                AAR[i][m]+=Rit[i][j][m];
            }
            AAR[i][m]=AAR[i][m]/30;
        };
    };
    
    //Calculate CAAR
    CAARMatrix.resize(30);
    for (int i=0;i<30;i++)
    {
        CAARMatrix[i].resize(61);
        for (int m = 0; m < 61; m++)
        {
            if (m == 0)
            {
                CAARMatrix[i][m] = AAR[i][m];
            }
            else {
                CAARMatrix[i][m] = CAARMatrix[i][m-1] + AAR[i][m];
            }
        }
    }
    // take the average of CAAR
    CAAR_ave.resize(61);
    for(int m = 0; m < 61; m++)
    {
        for (int i=0;i<30;i++)
        {
            CAAR_ave[m]+=CAARMatrix[i][m];
        }
        CAAR_ave[m]=CAAR_ave[m]/30;
    }
    return CAAR_ave;
}
// Calculate AAR
vector<double> CAAR::Calculate_AAR()
{
    AAR_avg.resize(61);
    for(int m = 0; m < 61; m++)
    {
        for (int i=0;i<30;i++)
        {
            AAR_avg[m]+=AAR[i][m];
        }
        AAR_avg[m]=AAR_avg[m]/30;
    }
    return AAR_avg;
}

double CAAR::Calculate_CAAR_SD() {
    double sum = std::accumulate(CAAR_ave.begin(), CAAR_ave.end(), 0.0);
    double mean = sum / CAAR_ave.size();
    
    std::vector<double> diff(CAAR_ave.size());
    std::transform(CAAR_ave.begin(), CAAR_ave.end(), diff.begin(), [mean](double x) { return x - mean; });
    double sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
    double stdev = sqrt(sq_sum / CAAR_ave.size());
    return stdev;
}
double CAAR::Calculate_CAAR_Mean() {
    double sum = std::accumulate(CAAR_ave.begin(), CAAR_ave.end(), 0.0);
    double mean = sum / CAAR_ave.size();
    
    std::vector<double> diff(CAAR_ave.size());
    std::transform(CAAR_ave.begin(), CAAR_ave.end(), diff.begin(), [mean](double x) { return x - mean; });
   // double sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
   // double stdev = sqrt(sq_sum / CAAR_ave.size());
    return mean;
}
double CAAR::Calculate_AAR_SD() {
    double sum = std::accumulate(AAR_avg.begin(), AAR_avg.end(), 0.0);
    double mean = sum / AAR_avg.size();
    
    std::vector<double> diff(AAR_avg.size());
    std::transform(AAR_avg.begin(), AAR_avg.end(), diff.begin(), [mean](double x) { return x - mean; });
    double sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
    double stdev = sqrt(sq_sum / AAR_avg.size());
    return stdev;
}
double CAAR::Calculate_AAR_Mean() {
    double sum = std::accumulate(AAR_avg.begin(), AAR_avg.end(), 0.0);
    double mean = sum / AAR_avg.size();
    
    std::vector<double> diff(AAR_avg.size());
    std::transform(AAR_avg.begin(), AAR_avg.end(), diff.begin(), [mean](double x) { return x - mean; });
   // double sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
   // double stdev = sqrt(sq_sum / AAR_Avg.size());
    return mean;
}

