#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

int main(){
    vector <ifstream> structs;
    ifstream file;
    string line;
    file.open("test.c");
    getline(file,line);
    printf("%c %c %c\n",line[line.length() - 3],line[line.length() - 2],line[line.length() - 1]);
    cout << line.length();
    file.close();
    return 0;
}