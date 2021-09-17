
#ifndef libcurl_hpp
#define libcurl_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <locale>
#include <iomanip>
#include "curl/curl.h"
#include "Stock.hpp"
using namespace std;
typedef vector<double> Vector;

struct MemoryStruct {
    char *memory;
    size_t size;
};
size_t write_data(void *ptr, int size, int nmemb, FILE *stream);//
void *myrealloc(void *ptr, size_t size);
size_t write_data2(void *ptr, size_t size, size_t nmemb, void *data);
vector<vector<TradingData>> libcurl(vector<string> SymbolList,vector<string> ReportdateList,vector<string> DateVec); //get price of each stock
string getTimeinSeconds(string Time);
vector<TradingData> libcurl(string Symbol,string start_time,string end_time); //get price of SPY


#endif /* libcurl_hpp */
