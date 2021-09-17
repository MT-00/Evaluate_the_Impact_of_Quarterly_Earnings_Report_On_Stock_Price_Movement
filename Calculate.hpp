#pragma once
#include "Stock.hpp"
#include <vector>
#include <map>
#include <iostream>
#include "Readdata.hpp"
#include "libcurl.hpp"
using namespace std;
class CAAR
{
public:
    //constructor with parameter
    CAAR(map<string,Stock> map_,vector<double> RSPY_)
    {
        map=map_;
        RSPY=RSPY_;
    }
    
    vector<vector<vector<double>>> Rit;
    vector<vector<int>> Findloc;
    vector<double> RSPY;
    vector<vector<double>> CAARMatrix;
    vector<vector<double>> AAR;
    map<string,Stock> map;
    vector<vector <string>> random_;
    vector<string> symbol;
    vector<double> CAAR_ave;
    vector<double> AAR_avg;
    vector<double> CalculateCAAR();
    vector<double> Calculate_AAR();
    double Calculate_CAAR_SD();
    double Calculate_AAR_SD();
    double Calculate_CAAR_Mean();
    double Calculate_AAR_Mean();
};
vector<string> random_select(vector<string> symbol);//random select function
