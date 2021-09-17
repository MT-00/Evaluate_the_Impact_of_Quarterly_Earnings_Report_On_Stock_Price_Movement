
#ifndef gnuplotnew_h
#define gnuplotnew_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <vector>
using namespace std;


typedef vector<vector<double>> Matrix;
void plotresults(Matrix C,int size_)
{
    ofstream fout;
    fout.open("CAAR.txt");
    for (int i = 0; i < size_; i++)
    {
        fout << i - 30 << " " << C[0][i] << " " << C[1][i] << " " << C[2][i] << endl;
    }
    fout.close();
    
    fout.open("Plot.txt");
    fout << "set title \"CAAR\"" << endl;
    fout << "set yrange [-0.06:0.06]" << endl;
    fout << "plot 'CAAR.txt' using 1:3 title 'Meet' with lines lw 4, 'CAAR.txt' using 1:2 title 'Beat' with lines lw 4, 'CAAR.txt' using 1:4 title 'Miss' with lines lw 4" << endl;
    fout << "pause -1" << endl;
    fout.close();
    system("/opt/local/bin/gnuplot Plot.txt");
}




#endif /* gnuplotnew_h */
