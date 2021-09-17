#include"operatorOverloading.hpp"
#include<iostream>
#include<vector>
#include"Stock.hpp"
#include <stdio.h>
using namespace std;

ostream & operator << (ostream & out, vector<double> r)
{
    for(vector<double>::iterator itr=r.begin();itr!=r.end();++itr)
        out<<*itr<<endl;
    return out;
}
ostream & operator << (ostream & out, vector<int> r)
{
    for(vector<int>::iterator itr=r.begin();itr!=r.end();++itr)
        out<<*itr<<endl;
    return out;
}
ostream & operator << (ostream & out, vector<string> r)
{
    for(vector<string>::iterator itr=r.begin();itr!=r.end();++itr)
        out<<*itr<<endl;
    return out;
}


ostream & operator << (ostream & out, vector<TradingData> r)
{
    for(vector<TradingData>::iterator itr=r.begin();itr!=r.end();++itr)
        out<<*itr<<endl;
    return out;
}

vector<double> operator*(const vector<double>& v, double c) {
    
    vector<double> temp(v.size());
    for (unsigned int j = 0; j < v.size(); j++) temp[j] = v[j] * c;
    
    return temp;
}

vector<double> operator+(const vector<double>& v1, const vector<double>& v2) {
    vector<double> temp(v1.size());
    for (unsigned int j = 0; j < v1.size(); j++) temp[j] = v1[j] + v2[j];
    
    return temp;
}

