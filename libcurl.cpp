
#include "libcurl.hpp"
#include "Stock.hpp"
using namespace std;
#include <string>
#include <fstream>
#include <sstream>

size_t write_data(void *ptr, int size, int nmemb, FILE *stream)
{
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;
}


void *myrealloc(void *ptr, size_t size)
{
    /* There might be a realloc() out there that doesn't like reallocing
     NULL pointers, so we take care of it here */
    if (ptr)
        return realloc(ptr, size);
    else
        return malloc(size);
}


size_t write_data2(void *ptr, size_t size, size_t nmemb, void *data)
{
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)data;
    
    mem->memory = (char *)myrealloc(mem->memory, mem->size + realsize + 1);
    if (mem->memory) {
        memcpy(&(mem->memory[mem->size]), ptr, realsize);
        mem->size += realsize;
        mem->memory[mem->size] = 0;
    }
    return realsize;
}

string getTimeinSeconds(string Time)
{
    std::tm t = {0}; //Time structure
    std::istringstream ssTime(Time);
    char time[100];
    memset(time, 0, 100);
    if (ssTime >> std::get_time(&t, "%Y-%m-%dT%H:%M:%S"))
    {
        sprintf (time, "%ld", mktime(&t));
        return string(time);
    }
    else
    {
        cout << "Parse failed\n";
        return "";
    }
}


vector<vector<TradingData>> libcurl(vector<string> SymbolList,vector<string> ReportdateList,vector<string> DateVec)
{
    vector<vector<TradingData>> Hist_Price_Collection;
    Hist_Price_Collection.resize(SymbolList.size());
    
    struct MemoryStruct data; //save the data in memory.
    data.memory = NULL;
    data.size = 0;
 
    //file pointer to create file that store the data
    FILE *fp;
    
    //name of files
    const char outfilename[FILENAME_MAX] = "Output.txt";

    
    /* declaration of an object CURL */
    CURL *handle;
    
    /* result of the whole process */
    CURLcode result;
    
    /* the first functions */
    /* set up the program environment that libcurl needs */
    curl_global_init(CURL_GLOBAL_ALL);
    
    /* curl_easy_init() returns a CURL easy handle that you're gonna reuse in other easy functions*/
    handle = curl_easy_init();
    
    /* if everything's all right with the easy handle... */
    
  if (handle)
    {
    string sCookies, sCrumb;
     for(int i=0;i<SymbolList.size();i++)
        {
    if (sCookies.length() == 0 || sCrumb.length() == 0)
    {
        fp = fopen(outfilename, "w");
        //give handle the URL
       curl_easy_setopt(handle, CURLOPT_URL, "https://finance.yahoo.com/quote/AMZN/history");
        curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0);
        curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0);
        curl_easy_setopt(handle, CURLOPT_COOKIEJAR, "cookies.txt");
        curl_easy_setopt(handle, CURLOPT_COOKIEFILE, "cookies.txt");
        
        curl_easy_setopt(handle, CURLOPT_ENCODING, "");
        curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data);
        //I/O buffer
        //write_data is a function, processing data and save that in file output.txt
        curl_easy_setopt(handle, CURLOPT_WRITEDATA, fp);//fp is the file that we want to write in
        result = curl_easy_perform(handle);
        fclose(fp);
        
        curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data2);
        curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void *)&data);
         // we first write data in memory in a MemoryStruct data;
    
        // perform, then store the expected code in 'result'
        result = curl_easy_perform(handle);
        
        //Get Crumb
        char cKey[] = "CrumbStore\":{\"crumb\":\"";
        char *ptr1 = strstr(data.memory, cKey);//Returns a pointer to the first occurrence of str2 in str1, or a null pointer if str2 is not part of str1.
        char *ptr2 = ptr1 + strlen(cKey);
        char *ptr3 = strstr(ptr2, "\"}");
        
        if ( ptr3 != NULL )
            *ptr3 = NULL;  //cut the URL to only extract crumb!
        
        sCrumb = ptr2; //key
        fp = fopen("cookies.txt", "r");
        char cCookies[100];
        if (fp)
            {
                while (fscanf(fp, "%s", cCookies) != EOF);
                fclose(fp);
            }
        else
            cerr << "cookies.txt does not exists" << endl;
        
        sCookies = cCookies;

        free(data.memory);
        data.memory = NULL;
        data.size= 0;
    }
        free(data.memory);
        data.memory = NULL;
        data.size= 0;
    
    
    string urlA = "https://query1.finance.yahoo.com/v7/finance/download/";
    string urlB = "?period1=";
    string urlC = "&period2=";
    string urlD = "&interval=1d&events=history&crumb=";
    vector<string>::iterator it=find(DateVec.begin(),DateVec.end(),ReportdateList[i]);
            string start_time=*(it-31)+"T16:00:00";
            string end_time=*(it+30)+"T16:00:00";
            string startTime = getTimeinSeconds(start_time);
            string endTime = getTimeinSeconds(end_time);
    string url = urlA + SymbolList[i] + urlB + startTime + urlC + endTime + urlD + sCrumb;//make the download URL in the program.
    const char * cURL = url.c_str();
    const char * cookies = sCookies.c_str();//change to C.
        curl_easy_setopt(handle, CURLOPT_COOKIE, cookies);   // Only needed for 1st stock
        curl_easy_setopt(handle, CURLOPT_URL, cURL);
        curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data2);
        curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void *)&data);
      result = curl_easy_perform(handle);
        

    stringstream sData(data.memory);
    string line,sValue,sDate;
    getline(sData, line);
   
    double dValue=0.0;
    for (; getline(sData, line); )
        {
            
            sDate=line.substr(0,line.find_first_of(','));
            line.erase(line.find_last_of(','));
            sValue=line.substr(line.find_last_of(',')+1);
            dValue=strtod(sValue.c_str(),NULL);
            if (dValue>10000)
                {
                    cout<< dValue;
                    dValue = 0 ;
                }
            TradingData data_(sDate,dValue);
            Hist_Price_Collection[i].push_back(data_);

        }
            cout<<"Stock "<<i+1<<" is retrieved"<<endl;
    }
    free(data.memory);
    data.size= 0;
    }
  else
  {
      fprintf(stderr, "Curl init failed!\n");
  }
    
    /* cleanup since you've used curl_easy_init */
    curl_easy_cleanup(handle);
    
    /* this function releases resources acquired by curl_global_init() */
    curl_global_cleanup();
    return Hist_Price_Collection;
}



vector<TradingData> libcurl(string Symbol,string start_time,string end_time)
{
    vector<TradingData> Hist_Price;
    
    struct MemoryStruct data; //save the data in memory.
    data.memory = NULL;
    data.size = 0;
    
    //file pointer to create file that store the data
    FILE *fp;
    
    //name of files
    const char outfilename[FILENAME_MAX] = "Output.txt";
    
    
    /* declaration of an object CURL */
    CURL *handle;
    
    /* result of the whole process */
    CURLcode result;
    
    /* the first functions */
    /* set up the program environment that libcurl needs */
    curl_global_init(CURL_GLOBAL_ALL);
    
    /* curl_easy_init() returns a CURL easy handle that you're gonna reuse in other easy functions*/
    handle = curl_easy_init();
    
    /* if everything's all right with the easy handle... */
    
    if (handle)
    {
        string sCookies, sCrumb;
        
            if (sCookies.length() == 0 || sCrumb.length() == 0)
            {
                fp = fopen(outfilename, "w");
                //give handle the URL
                curl_easy_setopt(handle, CURLOPT_URL, "https://finance.yahoo.com/quote/AMZN/history");
                curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0);
                curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0);
                curl_easy_setopt(handle, CURLOPT_COOKIEJAR, "cookies.txt");
                curl_easy_setopt(handle, CURLOPT_COOKIEFILE, "cookies.txt");
                
                curl_easy_setopt(handle, CURLOPT_ENCODING, "");
                curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data);
                //I/O buffer
                //write_data is a function, processing data and save that in file output.txt
                curl_easy_setopt(handle, CURLOPT_WRITEDATA, fp);//fp is the file that we want to write in
                result = curl_easy_perform(handle);
                fclose(fp);
                
                curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data2);
                curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void *)&data);
                // we first write data in memory in a MemoryStruct data;
                
                // perform, then store the expected code in 'result'
                result = curl_easy_perform(handle);
                
                //Get Crumb
                char cKey[] = "CrumbStore\":{\"crumb\":\"";
                char *ptr1 = strstr(data.memory, cKey);//Returns a pointer to the first occurrence of str2 in str1, or a null pointer if str2 is not part of str1.
                char *ptr2 = ptr1 + strlen(cKey);
                char *ptr3 = strstr(ptr2, "\"}");
                
                if ( ptr3 != NULL )
                    *ptr3 = NULL;  //cut the URL to only extract crumb!
                
                sCrumb = ptr2; //key
                fp = fopen("cookies.txt", "r");
                char cCookies[100];
                if (fp) {
                    while (fscanf(fp, "%s", cCookies) != EOF);
                    fclose(fp);
                }
                else
                    cerr << "cookies.txt does not exists" << endl;
                
                sCookies = cCookies;
                
                free(data.memory);
                data.memory = NULL;
                data.size= 0;
            }
            free(data.memory);
            data.memory = NULL;
            data.size= 0;
            
            
            string urlA = "https://query1.finance.yahoo.com/v7/finance/download/";
            string urlB = "?period1=";
            string urlC = "&period2=";
            string urlD = "&interval=1d&events=history&crumb=";
            string startTime = getTimeinSeconds(start_time+"T16:00:00");
            string endTime = getTimeinSeconds(end_time+"T16:00:00");
            string url = urlA + Symbol + urlB + startTime + urlC + endTime + urlD + sCrumb;//make the download URL in the program.
            const char * cURL = url.c_str();
            const char * cookies = sCookies.c_str();//change to C.
            curl_easy_setopt(handle, CURLOPT_COOKIE, cookies);   // Only needed for 1st stock
            curl_easy_setopt(handle, CURLOPT_URL, cURL);
            curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data);
            curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data2);
            curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void *)&data);
            result = curl_easy_perform(handle);
            
            
            stringstream sData(data.memory);
            string line,sValue,sDate;
            getline(sData, line);
            
            double dValue=0.0;
            for (; getline(sData, line); )
            {
                
                sDate=line.substr(0,line.find_first_of(','));
                line.erase(line.find_last_of(','));
                sValue=line.substr(line.find_last_of(',')+1);
                dValue=strtod(sValue.c_str(),NULL);
                if (dValue>10000)
                {
                    cout<< dValue;
                    dValue = 0 ;
                }
                

                TradingData data_(sDate,dValue);
                Hist_Price.push_back(data_);
                
            }
        
        free(data.memory);
        data.size= 0;
    }
    else
    {
        fprintf(stderr, "Curl init failed!\n");
    }
    
    /* cleanup since you've used curl_easy_init */
    curl_easy_cleanup(handle);
    
    /* this function releases resources acquired by curl_global_init() */
    curl_global_cleanup();
    return Hist_Price;
}

