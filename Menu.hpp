
#ifndef Menu_h
#define Menu_h
#include <vector>
#include <map>

#include<iostream>

map<string,Stock> Beat_Map;
map<string,Stock> Meet_Map;
map<string,Stock> Miss_Map;


vector<string> SymbolList;
vector<string> ReportList;
vector<double> SurpriseList;
vector<int> Group;
vector<string> DateVec;

string stockSymbol;

vector<double> RSPY;
vector<vector<double>> AARMat(3);
vector<vector<double>> CAARMat(3);
vector<vector<TradingData>> Hist_Price_Collection;



vector<double> BeatMat(4);
vector<double> MeetMat(4);
vector<double> MissMat(4);

#endif /* Menu_h */
