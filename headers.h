#ifndef HEADERS_H
#define HEADERS_H

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int begin();
int find_struct(ifstream file);

int is_initialization(ifstream& file);
#endif