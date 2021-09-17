

#ifndef Stock_hpp
#define Stock_hpp
#include <vector>
#include <string>
#include <stdio.h>
#include <ctime>
#include <iostream>
#include <map>
using namespace std;



class TradingData
{
public:
    double price;
    string sDate;
    TradingData() : sDate(""), price(0.0) {}
    TradingData(string sDate_, double price_) : sDate(sDate_),price(price_){}
    
    double getClose()
    {
        return price;
    }
    
    TradingData operator&= (const TradingData & Data_)
    {
        price = Data_.price;
        sDate = Data_.sDate;
        return *this;
    }
    
    friend ostream & operator << (ostream & out,  TradingData  Data)
    {
        out<<Data.sDate<<" "<<Data.price<<endl;
        return out;
    }
 
};

class Stock
{
public:
    string symbol;
    vector<TradingData> Hist_Price;
    string report_date;
    string type;
    double surprise;
    int group;
    int DateLoc;
    vector<double> r; //return
    
    Stock(): symbol(""), report_date(""), group(0), type(""), surprise(0),Hist_Price(){}
    Stock(string symbol_,string report_date_,double surprise_,int group_);
};
    

#endif /* Stock_hpp */
