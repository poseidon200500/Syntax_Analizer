#ifndef HEADERS_H
#define HEADERS_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

class checkers{
    ifstream file;
    string word = "";
    string line = "";
    int line_ind = 0;
public:
    int begin();
    int find_struct(char last);
    int find_line();
    int is_good_name();
    int is_good_type();
    int is_good_attr();
    int is_initialization(int beginning);
};


#endif