#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "checkers.hpp"
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


int checkers::begin(){

    string file_name;
    cout << "Данная программа проверяет содержимое файла на правильность описания структурного типа в языке С" << endl;
    cout << "Введите имя файла:" << endl;
    cin >> file_name;
    file.open(file_name);
    if (!file.is_open()){
        cerr << "Файл не найден" << endl;
        return -1;
    }
    cout << "Файл найден" << endl;
    find_line();
    return 0;
}
//zer gut
int checkers::find_line(){
    string word;
    char last = ' ';
    int flag = 0, index;
    do{
        getline(file,line);
        line_ind++;
        if (line.length()>2){
        last = line[line.length()-2];
        }
        if (line.find("struct") != string::npos){
            //cout << "is good" << endl;
            index = find_struct(last);
            if (index >= 0){
                flag = 1;
                cout << "В строке " << line_ind << " найдена структура с началом имени в " << index << endl;
                //is_initialization(index);
            } else {
                cout <<"В строке " << line_ind << " структура не подходит, код ошибки " << index << endl;
            }
            cout << line << endl;
        }

    } while (!file.eof());
    if (!flag){
        cout << "Ни одной структуры не найдено" << endl;
        return 0;
    }
    return flag;
}
//zer gut
int checkers::find_struct(char last){
    string correct_last = "; {}\t";
    //cout << "is good" << endl;
    unsigned int index = line.find("struct");
    //cout << "is good" << endl;
    if (index == 0 && correct_last.find(last) == string::npos){
        return -1;
    } else if (index != 0 && correct_last.find(line[index-1]) == string::npos){
        return -2;
    }
    //cout << "is good" << endl;
    if (line.length() >= index+8){
        index += 6;
        int dop_flag = 0;
        while (line[index] == ' '){
            index++;
            dop_flag = 1;
        }
        if (dop_flag && line[index] != '\n'){
            return index;
        } else {
            return -3;
        }
    }
    return -4;
}

int checkers::is_initialization(int beginning){
    char c;
    int index = beginning;
    int countr = 0;
    do{                 //пропускаем пробелы
        file >> c;
        index++;
    } while(c == ' ');
    while (c != EOF && (isalnum(c) || c == '_') && countr < 255){
        word.push_back(c);
        file >> c;
        countr++;
    }
    while (c == ' ' || c == '\n'){
        if (c == '\n')  line_ind++;
        file >> c;
    }
    if (countr == 0){
        cerr << "ОШИБКА: Имя структуры не указано" << endl;
    }else if(countr >= 255){
        cerr << "ОШИБКА: Имя структуры слишком большое" << endl;
    } else if (is_good_name() < 0){
        ;//ошибка уже будет выведена
    } else if (c == ';'){
        cout << "struct " << word << ";" << "не является обьявлением структуры" << endl;
    } else if (c != '{'){
        cerr << "ОШИБКА: Ожидалось \"{\", но после имени идёт " << c << endl;
    } else {
        //имя нормальное, после него есть {
        //while (is_good_attr());
        cout << "Ура, пока всё хорошо" << endl;
    }
    return 0;
}


//it works
int checkers::is_good_name(){
    vector<string> forbidden = {"auto","break","case","char","const","continue","default","do","double","else","enum",
    "extern","float","for","goto","if","inline","int","long","register","restrict","return",
    "short","signed","sizeof","static","struct","switch","typedef","union","unsigned","void",
    "volatile","while",};
    int output_code = 0;
    for (unsigned int i = 0; i< forbidden.size();i++){
        if (word == forbidden[i]){
            cerr << "ОШИБКА: Имя " << word << " является зарезервированным и не может быть использовано" << endl;
            output_code = -1;
        }
    }
    if (!output_code && isdigit(word[0])){
        cerr << "ОШИБКА: Имя " << word << " начинается с цифры и не может быть использовано" << endl;
        output_code = -2;
    }
    for (unsigned int i = 0; !output_code && i < word.size();i++){
        if (!( isalnum(word[i]) || word[i] == '_')){
            cerr << "ОШИБКА: Имя " << word << " содержит недопустимые символы и не может быть использовано" << endl;
            output_code = -3;
        }
    }

    return output_code;
}

/*иди нафиг
-1 -- output
0-3 -- modifier
4-7 -- type
*/
//
int checkers::is_good_type(){
    int rez = 0;
    vector<string> types = {"char","int","float","double"};
    if (word[0] == '{'){
        rez = 10;
        word.erase(0,1);
    } else if (word[0] == ';'){
        rez = 20;
        word.erase(0,1);
    }

    for (unsigned int i = 0; i < types.size(); i++){
        if (word == types[i])   rez+=i+1;
    }

    if ( rez % 10 == 0)  rez = -1;

    return rez;
}

// int checkers::is_good_attr(){
//     char letter;
//     int rez = 0;
//     file >> letter;
//     while (letter )
//     return 0;
// }



// int main(){
//     checkers checker;
//     checker.begin();
//     return 0;
// }
