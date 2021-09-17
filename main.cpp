
#include <iostream>
#include "libcurl.hpp"
#include "Stock.hpp"
#include "Readdata.hpp"
#include <stdio.h>
#include <map>
#include "Calculate.hpp"
#include "gnuplotnew.h"
#include "operatorOverloading.hpp"
#include "Menu.hpp"
#include <algorithm>
using namespace std;

int main()
{
    int selection;
    vector<vector<double>> Matrix(3);
    
    ReadCSV(SymbolList,ReportList,SurpriseList,Group,DateVec);
    
    
    auto it=Beat_Map.begin();

    vector<TradingData> SPY_Hist_Price;//calculate return of SPY
    SPY_Hist_Price=libcurl("SPY", DateVec[0], DateVec[DateVec.size()-1]); //extract the data of SPY

    for(vector<TradingData>::iterator itr=SPY_Hist_Price.begin();itr!=SPY_Hist_Price.end();++itr)
    {
        RSPY.push_back(((itr+1)->price-itr->price)/itr->price);
    }

    CAAR Beat(Beat_Map,RSPY);
    CAAR Meet(Meet_Map,RSPY);
    CAAR Miss(Miss_Map,RSPY);


    string GroupName;
    string Indicator;

    int retrieved = 0;

    while(true)
        {
            cout << "  Project Menu"<<endl;
            cout << "  *********************************************************"<<endl;
            cout << "  1.  Retrieve Historical Price Data for all stocks"<<endl;
            cout << "  2.  Get information for one stock"<<endl;
            cout << "  3.  Show AAR, AAR-SD, CAAR and CAAR-SD for each group"<<endl;
            cout << "  4.  Show the gnuplot graph with CAAR for all 3 groups"<<endl;
            cout << "  5.  Exit"<<endl;;
            cout << "  *********************************************************"<<endl;
            cout << "  Enter your selection: ";
            cin >> selection;
            cout << endl;
            
            if(selection == 1){
                retrieved = 1;
                cout << "Retrieve Data"<<endl;
                cout << "\n";
                Hist_Price_Collection=libcurl(SymbolList, ReportList, DateVec);
                for(int i=0;i<SymbolList.size();i++) //import data of the stocks
                {
                    Stock stk(SymbolList[i],ReportList[i],SurpriseList[i],Group[i]);
                    stk.Hist_Price=Hist_Price_Collection[i];

                    for(vector<TradingData>::iterator itr=stk.Hist_Price.begin();itr!=stk.Hist_Price.end();itr++)
                    {
                        stk.r.push_back(((itr+1)->price-itr->price)/itr->price);
                    }
                        
        
                    if(stk.type=="Beat")
                        Beat_Map[stk.symbol]=stk;
                    else if(stk.type=="Meet")
                        Meet_Map[stk.symbol]=stk;
                    else if(stk.type=="Miss")
                        Miss_Map[stk.symbol]=stk;


                }
                Beat.map=Beat_Map;
                Meet.map=Meet_Map;
                Miss.map=Miss_Map;
        
                CAARMat[0]=Beat.CalculateCAAR();
                CAARMat[1]=Meet.CalculateCAAR();
                CAARMat[2]=Miss.CalculateCAAR();
                
                AARMat[0]=Beat.Calculate_AAR();
                AARMat[1]=Meet.Calculate_AAR();
                AARMat[2]=Miss.Calculate_AAR();
                
                BeatMat[0] =Beat.Calculate_AAR_Mean();
                BeatMat[1] = Beat.Calculate_AAR_SD();
                BeatMat[2] = Beat.Calculate_CAAR_Mean();
                BeatMat[3] = Beat.Calculate_CAAR_SD();
                
                MeetMat[0] = Meet.Calculate_AAR_Mean();
                MeetMat[1] = Meet.Calculate_AAR_SD();
                MeetMat[2] = Meet.Calculate_CAAR_Mean();
                MeetMat[3] = Meet.Calculate_CAAR_SD();
                
                MissMat[0] = Miss.Calculate_AAR_Mean();
                MissMat[1] = Miss.Calculate_AAR_SD();
                MissMat[2] = Miss.Calculate_CAAR_Mean();
                MissMat[3] = Miss.Calculate_CAAR_SD();
                
                Matrix[0]=BeatMat;
                Matrix[1]=MeetMat;
                Matrix[2] = MissMat;

                cout << "Well Done" <<endl;
                cout << "Finished Retrieveing Price Data"<<endl;
            }

            if(selection == 2){
                if (retrieved == 0){
                    retrieved = 1;
                    cout << "We need to retrieve data first" << endl;
                    cout << "Retrieve Data"<<endl;
                    cout << "\n";
                    Hist_Price_Collection=libcurl(SymbolList, ReportList, DateVec);
                    for(int i=0;i<SymbolList.size();i++) //import data of the stocks
                    {
                        Stock stk(SymbolList[i],ReportList[i],SurpriseList[i],Group[i]);
                        stk.Hist_Price=Hist_Price_Collection[i];
                        
                        for(vector<TradingData>::iterator itr=stk.Hist_Price.begin();itr!=stk.Hist_Price.end();itr++)
                        {
                            stk.r.push_back(((itr+1)->price-itr->price)/itr->price);
                        }
                        
                        
                        if(stk.type=="Beat")
                            Beat_Map[stk.symbol]=stk;
                        else if(stk.type=="Meet")
                            Meet_Map[stk.symbol]=stk;
                        else if(stk.type=="Miss")
                            Miss_Map[stk.symbol]=stk;
                        
                        
                    }
                    Beat.map=Beat_Map;
                    Meet.map=Meet_Map;
                    Miss.map=Miss_Map;
                    
                    CAARMat[0]=Beat.CalculateCAAR();
                    CAARMat[1]=Meet.CalculateCAAR();
                    CAARMat[2]=Miss.CalculateCAAR();
                    
                    AARMat[0]=Beat.Calculate_AAR();
                    AARMat[1]=Meet.Calculate_AAR();
                    AARMat[2]=Miss.Calculate_AAR();
                    
                    BeatMat[0] =Beat.Calculate_AAR_Mean();
                    BeatMat[1] = Beat.Calculate_AAR_SD();
                    BeatMat[2] = Beat.Calculate_CAAR_Mean();
                    BeatMat[3] = Beat.Calculate_CAAR_SD();
                    
                    MeetMat[0] = Meet.Calculate_AAR_Mean();
                    MeetMat[1] = Meet.Calculate_AAR_SD();
                    MeetMat[2] = Meet.Calculate_CAAR_Mean();
                    MeetMat[3] = Meet.Calculate_CAAR_SD();
                    
                    MissMat[0] = Miss.Calculate_AAR_Mean();
                    MissMat[1] = Miss.Calculate_AAR_SD();
                    MissMat[2] = Miss.Calculate_CAAR_Mean();
                    MissMat[3] = Miss.Calculate_CAAR_SD();
                    
                    Matrix[0]=BeatMat;
                    Matrix[1]=MeetMat;
                    Matrix[2] = MissMat;
                    
                    cout << "Well Done" <<endl;
                    cout << "Finished Retrieveing Price Data"<<endl;
                }
                    
                cout << "Getting Historical information"<<endl;
                cout << "Enter the Stock name: ";
                cin  >> stockSymbol;
                
                transform(stockSymbol.begin(),stockSymbol.end(),stockSymbol.begin(),::toupper);

                it=Beat_Map.find(stockSymbol);
                if(it!=Beat_Map.end())
                {
                    cout<<"The Historical Data of "<<stockSymbol<<" is : "<<endl;
                    cout<<it->second.Hist_Price;
                    cout<<endl;
                    cout<<"The Report Date of "<<stockSymbol<<" is : "<<it->second.report_date<<endl;
                    cout<<"The Surprise percentage of "<<stockSymbol<<" is : "<<it->second.surprise<<endl;
                    cout<<"The Group of "<<stockSymbol<<" is : "<<it->second.type<<endl;
                }
                else
                {
                    it=Meet_Map.find(stockSymbol);
                    if(it!=Meet_Map.end())
                    {
                        cout<<"The Historical Data of "<<stockSymbol<<" is : "<<endl;
                        cout<<it->second.Hist_Price;
                        cout<<endl;
                        cout<<"The Report Date of "<<stockSymbol<<" is : "<<it->second.report_date<<endl;
                        cout<<"The Surprise percentage of "<<stockSymbol<<" is : "<<it->second.surprise<<endl;
                        cout<<"The Group of "<<stockSymbol<<" is : "<<it->second.type<<endl;

                    }
                    else
                    {
                        it=Miss_Map.find(stockSymbol);
                        if(it!=Miss_Map.end())
                        {
                            cout<<"The Historical Data of "<<stockSymbol<<" is : "<<endl;
                            cout<<it->second.Hist_Price;
                            cout<<endl;
                            cout<<"The Report Date of "<<stockSymbol<<" is : "<<it->second.report_date<<endl;
                            cout<<"The Surprise percentage of "<<stockSymbol<<" is : "<<it->second.surprise<<endl;
                            cout<<"The Group of "<<stockSymbol<<" is : "<<it->second.type<<endl;

                        }
                        else
                        {
                            cout<<"The Stock is not in the list"<<endl;
                        }
                    }
                }
            }
            if(selection == 3){
                if (retrieved == 0){
                    retrieved = 1;
                    cout << "We need to retrieve data first" << endl;
                    cout << "Retrieve Data"<<endl;
                    cout << "\n";
                    Hist_Price_Collection=libcurl(SymbolList, ReportList, DateVec);
                    for(int i=0;i<SymbolList.size();i++) //import data of the stocks
                    {
                        Stock stk(SymbolList[i],ReportList[i],SurpriseList[i],Group[i]);
                        stk.Hist_Price=Hist_Price_Collection[i];
                        
                        for(vector<TradingData>::iterator itr=stk.Hist_Price.begin();itr!=stk.Hist_Price.end();itr++)
                        {
                            stk.r.push_back(((itr+1)->price-itr->price)/itr->price);
                        }
                        
                        
                        if(stk.type=="Beat")
                            Beat_Map[stk.symbol]=stk;
                        else if(stk.type=="Meet")
                            Meet_Map[stk.symbol]=stk;
                        else if(stk.type=="Miss")
                            Miss_Map[stk.symbol]=stk;
                        
                        
                    }
                    Beat.map=Beat_Map;
                    Meet.map=Meet_Map;
                    Miss.map=Miss_Map;
                    
                    CAARMat[0]=Beat.CalculateCAAR();
                    CAARMat[1]=Meet.CalculateCAAR();
                    CAARMat[2]=Miss.CalculateCAAR();
                    
                    AARMat[0]=Beat.Calculate_AAR();
                    AARMat[1]=Meet.Calculate_AAR();
                    AARMat[2]=Miss.Calculate_AAR();
                    
                    BeatMat[0] =Beat.Calculate_AAR_Mean();
                    BeatMat[1] = Beat.Calculate_AAR_SD();
                    BeatMat[2] = Beat.Calculate_CAAR_Mean();
                    BeatMat[3] = Beat.Calculate_CAAR_SD();
                    
                    MeetMat[0] = Meet.Calculate_AAR_Mean();
                    MeetMat[1] = Meet.Calculate_AAR_SD();
                    MeetMat[2] = Meet.Calculate_CAAR_Mean();
                    MeetMat[3] = Meet.Calculate_CAAR_SD();
                    
                    MissMat[0] = Miss.Calculate_AAR_Mean();
                    MissMat[1] = Miss.Calculate_AAR_SD();
                    MissMat[2] = Miss.Calculate_CAAR_Mean();
                    MissMat[3] = Miss.Calculate_CAAR_SD();
                    
                    Matrix[0]=BeatMat;
                    Matrix[1]=MeetMat;
                    Matrix[2] = MissMat;
                    
                    cout << "Well Done" <<endl;
                    cout << "Finished Retrieveing Price Data"<<endl;
                }

                cout<<"Which group do you want to show? "<<endl;
                cout<<"Group One: Beat"<<endl;
                cout<<"Gouup Two: Meet"<<endl;
                cout<<"Group Three: Miss"<<endl;
                cin>>GroupName;
                transform(GroupName.begin(),GroupName.end(),GroupName.begin(),::toupper);
                cout<<"Which Indicator do you want to show? "<<endl;
                cout<<"Indicator One: AAR"<<endl;
                cout<<"Indicator Two: CAAR"<<endl;
                cin>>Indicator;
                transform(Indicator.begin(),Indicator.end(),Indicator.begin(),::toupper);
                if(GroupName == "BEAT")
                {
                    if(Indicator == "CAAR")
                    {
                        cout<<CAARMat[0]<<endl;
                        cout << "Beat CAAR Mean is " << Matrix[0][2] << endl;
                        cout << "Beat CAAR Std is " << Matrix[0][3] <<endl;
                        cout << endl;
                        
                    }
                    else
                    {
                        cout<<AARMat[0]<<endl;
                        cout << "Beat AAR Mean is " << Matrix[0][0] << endl;
                        cout << "Beat AAR Std is " << Matrix[0][1] <<endl;
                        cout<<endl;
                    }
                }
                else if(GroupName == "MEET")
                {
                    if(Indicator == "CAAR")
                    {
                        cout<<CAARMat[1]<<endl;
                        cout << "Meet CAAR Mean is " << Matrix[1][2] << endl;
                        cout << "Meet CAAR Std is " << Matrix[1][3] <<endl;
                        cout<<endl;
                    }
                    else
                    {
                        cout<<AARMat[1]<<endl;
                        cout << "Meet AAR Mean is " << Matrix[1][0] << endl;
                        cout << "Meet AAR Std is " << Matrix[1][1] <<endl;
                        cout<<endl;
                    }
                }
                else if(GroupName == "MISS")
                {
                    if(Indicator == "CAAR")
                    {
                        cout<<CAARMat[2]<<endl;
                        cout << "Miss CAAR Mean is " << Matrix[2][2] << endl;
                        cout << "Miss CAAR Std is " << Matrix[2][3] <<endl;

                        cout<<endl;
                    }
                    else
                    {
                        cout<<AARMat[2]<<endl;
                        cout << "Miss AAR Mean is " << Matrix[2][0] << endl;
                        cout << "Miss AAR Std is " << Matrix[2][1] <<endl;

                        cout<<endl;
                    }
                }
            }
            if(selection == 4){
                if (retrieved == 0){
                    retrieved = 1;
                    cout << "We need to retrieve data first" << endl;
                    cout << "Retrieve Data"<<endl;
                    cout << "\n";
                    Hist_Price_Collection=libcurl(SymbolList, ReportList, DateVec);
                    for(int i=0;i<SymbolList.size();i++) //import data of the stocks
                    {
                        Stock stk(SymbolList[i],ReportList[i],SurpriseList[i],Group[i]);
                        stk.Hist_Price=Hist_Price_Collection[i];
                        
                        for(vector<TradingData>::iterator itr=stk.Hist_Price.begin();itr!=stk.Hist_Price.end();itr++)
                        {
                            stk.r.push_back(((itr+1)->price-itr->price)/itr->price);
                        }
                        
                        
                        if(stk.type=="Beat")
                            Beat_Map[stk.symbol]=stk;
                        else if(stk.type=="Meet")
                            Meet_Map[stk.symbol]=stk;
                        else if(stk.type=="Miss")
                            Miss_Map[stk.symbol]=stk;
                        
                        
                    }
                    Beat.map=Beat_Map;
                    Meet.map=Meet_Map;
                    Miss.map=Miss_Map;
                    
                    CAARMat[0]=Beat.CalculateCAAR();
                    CAARMat[1]=Meet.CalculateCAAR();
                    CAARMat[2]=Miss.CalculateCAAR();
                    
                    AARMat[0]=Beat.Calculate_AAR();
                    AARMat[1]=Meet.Calculate_AAR();
                    AARMat[2]=Miss.Calculate_AAR();
                    
                    BeatMat[0] =Beat.Calculate_AAR_Mean();
                    BeatMat[1] = Beat.Calculate_AAR_SD();
                    BeatMat[2] = Beat.Calculate_CAAR_Mean();
                    BeatMat[3] = Beat.Calculate_CAAR_SD();
                    
                    MeetMat[0] = Meet.Calculate_AAR_Mean();
                    MeetMat[1] = Meet.Calculate_AAR_SD();
                    MeetMat[2] = Meet.Calculate_CAAR_Mean();
                    MeetMat[3] = Meet.Calculate_CAAR_SD();
                    
                    MissMat[0] = Miss.Calculate_AAR_Mean();
                    MissMat[1] = Miss.Calculate_AAR_SD();
                    MissMat[2] = Miss.Calculate_CAAR_Mean();
                    MissMat[3] = Miss.Calculate_CAAR_SD();
                    
                    Matrix[0]=BeatMat;
                    Matrix[1]=MeetMat;
                    Matrix[2] = MissMat;
                    
                    cout << "Well Done" <<endl;
                    cout << "Finished Retrieveing Price Data"<<endl;
                }

                cout<<"This is the Graph of CAAR for all 3 groups "<<endl;
                plotresults(CAARMat, 61);

            }
            if(selection == 5){
                cout << "Exit the Program" ;
                cout << "\n";
                break;
            }

        }

        return 0;
    }




