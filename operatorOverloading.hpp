
#ifndef Header_h
#define Header_h

#include<vector>
#include<iostream>
#include <stdio.h>
#include"Stock.hpp"
ostream & operator << (ostream & out, vector<double> r);

ostream & operator << (ostream & out, vector<int> r);

ostream & operator << (ostream & out, vector<string> r);

ostream & operator << (ostream & out, vector<TradingData> r);

vector<double> operator*(const vector<double>& v, double c);

vector<double> operator+(const vector<double>& v1, const vector<double>& v2);



#endif /* Header_h */
