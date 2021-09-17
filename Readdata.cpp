

#include "Readdata.hpp"
int ReadCSV(vector<string> &SymbolList,vector<string> &ReportList,vector<double> &SurpriseList,vector<int> &Group, vector<string> &DateList)
{
    ifstream ifs("epsdata2.csv");
   
    if (!ifs.is_open()) {
        cerr << "Open epsdata.csv Failed" << endl;
        system("pause");
        return 1;
    }
    string line;
    getline(ifs, line); //ignore first line
    while (getline(ifs, line))
    {
        istringstream ss_line(line);
        string item = "";
        
        getline(ss_line, item, ',');
        string symbol = item;
        SymbolList.push_back(symbol);
        
        getline(ss_line, item, ',');
        string report_date = item;
        ReportList.push_back(report_date);
        
        getline(ss_line, item, ',');
        string date = item;
        DateList.push_back(date);

        getline(ss_line, item, ',');
        double surp = stod(item);
        SurpriseList.push_back(surp);
        
        getline(ss_line, item, ',');
        int group = stoi(item);
        Group.push_back(group);
        
    }
    return 0;
    
    
}

