//#define MAIN

#ifdef  MAIN


#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <json/json.h>

using namespace std;

int main()
{
    cout << "test 1: " << endl;
    {
        string replyStr;
        ifstream initFile("C:\\Users\\zmm\\Documents\\Visual Studio 2015\\Projects\\xTestCpp11\\ISecExamPaperAddIn\\initTree.json", std::ios::in);
        char buf[1024];
        while (initFile.getline(buf, 1024))
            replyStr += buf;

        cout << replyStr << endl;
        
        Json::Reader reader;
        Json::Value replyVal;
        bool ok = reader.parse(replyStr, replyVal);
        if (!ok)
            cerr << "parse failed" << endl;

    }
    cout << endl;

    cout << "test 2: " << endl;
    {
       
    }
    cout << endl;
    


}
#endif //  MAIN
