/*************************************************************************
    > File Name: Express.cpp
    > Author: Herixth
    > Mail: herixth@gmail.com 
    > Created Time: 2018年11月15日 17:06:04
 ************************************************************************/

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
using namespace std;


int main() {
    
    string input = "";
    getline(cin, input);
    fstream oup("tmp.py", ios::out);
    oup << "try:\n"; 
    oup << "    print ("  << input << ")\n";
    oup << "except Exception, e:\n";
    oup << "    print ('error')\n";
    oup.close();
    
    system("python tmp.py");
    system("del tmp.py");
    
    return 0;
}
