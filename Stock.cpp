

#include "Stock.hpp"
#include "libcurl.hpp"
#include "Readdata.hpp"
#include <iostream>
#include <algorithm>

using namespace std;


Stock::Stock(string symbol_,string report_date_,double surprise_,int group_)
{
    symbol=symbol_;
    report_date=report_date_;
    surprise=surprise_;
    group=group_;
    
    if(group_ == 1)
    {
        type="Beat";
    }
    else if(group_ == 2)
    {
        type="Meet";
    }
    else
    {
        type="Miss";
    }
    vector<string> SymbolList1;
    vector<string> ReportdateList1;
    vector<double> SurpriseList1;
    vector<int> Group1;
    vector<string> DateVec1;
    
    ReadCSV(SymbolList1,ReportdateList1,SurpriseList1,Group1,DateVec1);
    
    
    //find the address of report_date in the vector
    
    for(int i=0;i<DateVec1.size();i++)
    {
        if(DateVec1[i] == report_date)
        {
            DateLoc=i;
        }
    }
     
}
