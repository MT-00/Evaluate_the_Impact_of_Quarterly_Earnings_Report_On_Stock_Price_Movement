
#ifndef Readdata_hpp
#define Readdata_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

int ReadCSV(vector<string> &SymbolList,vector<string> &ReportdateList,vector<double> &SurpriseList,vector<int> &Group,vector<string> &DateList);

#endif 
