#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "headers.h"
using namespace std;

/*
При написании имен переменных, функций и других элементов программы на языке C
 допускается использование только латинских букв (прописных и строчных), цифр и символа нижнего подчеркивания.
Имя должно начинаться с буквы или символа нижнего подчеркивания и может содержать любую комбинацию латинских букв,
 цифр и символа нижнего подчеркивания. Однако, имена не могут начинаться с цифр.
Структура описания структуры:
struct name {
    type attr1;
    type attr2;
    type attr3;
} ;
имена аттрибутов не могут повторяться, но могут совпадать с именем структуры.

*/


int begin(){

    string file_name;
    ifstream file;
    cout << "Данная программа проверяет содержимое файла на правильность описания структурного типа в языке С" << endl;
    do {
        cout << "Введите имя файла:" << endl;
        cin >> file_name;
        file.open(file_name);
    } while(!file.is_open());
    cout << "Файл найден" << endl;

    return 0;
}

int find_struct(ifstream file){
    string word;
    int flag = 0;
    for (file >> word; !file.eof(); file >> word){
        if (word == "struct"){
            flag = 1;
            is_initialization(file);
        }
    }
    if (!flag){
        cout << "Ни одной структуры не найдено" << endl;
        return -1;
    }
    return 0;
}

int is_initialization(ifstream& file){
    string struct_name;
    file >> struct_name;
    if (struct_name == "{" || struct_name == "}"){
        ;
    }

    return 0;
}


//it works
int is_good_name(string name){
    vector<string> forbidden = {"auto","break","case","char","const","continue","default","do","double","else","enum",
    "extern","float","for","goto","if","inline","int","long","register","restrict","return",
    "short","signed","sizeof","static","struct","switch","typedef","union","unsigned","void",
    "volatile","while",};
    int output_code = 0;
    for (int i = 0; i< forbidden.size();i++){
        if (name == forbidden[i]){
            cout << "Имя " << name << " является зарезервированным и не может быть использовано" << endl;
            output_code = -1;
        }
    }
    if (!output_code && isdigit(name[0])){
        cout << "Имя " << name << " начинается с цифры и не может быть использовано" << endl;
        output_code = -2;
    }
    for (int i = 0; !output_code && i < name.size();i++){
        if ( !( isalnum(name[i]) || (name[i] =='_') ||
              (i == 0 && (name[i] == '*' || name[i] == '}' || name[i] == '{')) || 
              (i == name.size()-1 && (name[i] == ';' || name[i] == '{' || name[i] == '}'))) ){
            cout << "Имя " << name << " содержит недопустимые символы и не может быть использовано" << endl;
            output_code = -3;
        }
    }
    if (output_code == 0){
        if (name[name.size()-1] == ';')  output_code = 1;
        if (name[name.size()-1] == '{')  output_code = 2;
        if (name[name.size()-1] == '}')  output_code = 3;
        if (name[0] == '*') output_code += 10;
        if (name[0] == '{') output_code += 20;
        if (name[0] == '}') output_code += 30;
    }

    return output_code;
}

/*
-1 -- output
0-3 -- modifier
4-7 -- type
*/
//
int is_good_type(string name){
    int rez = 0;
    vector<string> types = {"char","int","float","double"};
    if (name[0] == '{'){
        rez = 10;
        name.erase(0,1);
    } else if (name[0] == ';'){
        rez = 20;
        name.erase(0,1);
    }

    for (int i = 0; i < types.size(); i++){
        if (name == types[i])   rez+=i+1;
    }

    if ( rez % 10 == 0)  rez = -1;

    return rez;
}

int is_good_attr(ifstream& file){
    return 0;
}



int main(){
    int tmp_rez;
    vector<string> names = {"boba","1boba","ne_boba","boba1","b_1_o_2_0",
    "_boba","123","цапля","!boba","b,oba","boba.","{boba","boba{", "boba{}", "boba;",
    ";boba", "*boba"};
    for (int i = 0; i< names.size();i++){
        tmp_rez = is_good_name(names[i]);
        if (tmp_rez >= 0){
            cout << "Имя " << names[i] << " правильное, код: " << tmp_rez << endl;
        } else {
            cout << "Имя " << names[i] << " неправильное, код: " << tmp_rez << endl;
        }
    }
}
