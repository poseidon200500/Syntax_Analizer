#ifndef HEADERS_H
#define HEADERS_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class checkers {
  ifstream file;
  string word = "";
  string line = "";
  int index = 0;
  int line_ind = 0;
  int attr_cout = 0;
  int struct_result = 0;

 public:
  int begin();
  int find_struct(char last);
  int find_line();
  int is_good_name();
  void check_name();
  int is_good_type();
  int is_good_attr();
  int is_next_end();
  int is_initialization();

  void pass_tab();
  void big_pass_tab();
  void get_word();

  void clear_attrs();
};

#endif