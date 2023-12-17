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
bool is_good_name(string name){
    vector<string> forbidden = {"auto","break","case","char","const","continue","default","do","double","else","enum",
    "extern","float","for","goto","if","inline","int","long","register","restrict","return",
    "short","signed","sizeof","static","struct","switch","typedef","union","unsigned","void",
    "volatile","while",};
    int error_code = 0;
    for (int i = 0; i< forbidden.size();i++){
        if (name == forbidden[i]){
            cout << "Имя " << name << " является зарезервированным и не может быть использовано" << endl;
            error_code = -1;
        }
    }
    if (!error_code && isdigit(name[0])){
        cout << "Имя " << name << " начинается с цифры и не может быть использовано" << endl;
        error_code = -2;
    }
    for (int i = 0; !error_code && i < name.size();i++){
        if ( !( isalnum(name[i]) || (name[i] =='_') ) ){
            cout << "Имя " << name << " содержит недопустимые символы и не может быть использовано" << endl;
            error_code = -3;
        }
    }
    return error_code;
}


int main(){
    vector<string> names = {"boba","1boba","ne_boba","boba1","b_1_o_2_0","_boba","123","цапля","!boba","b,oba","boba."};
    for (int i = 0; i< names.size();i++){
        if (is_good_name(names[i]) == 0){
            cout << "Имя " << names[i] << " правильное" << endl;
        } else {
            cout << "Имя " << names[i] << " неправильное" << endl;
        }
    }
}
