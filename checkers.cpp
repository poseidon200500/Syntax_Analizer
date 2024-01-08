#define _CRT_SECURE_NO_WARNINGS

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

cout << "Строка " << line_ind << ": " << endl;
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
    cout << "Файл найден\n" << endl;
    find_line();
    return 0;
}
//zer gut
int checkers::find_line(){
    string word;
    char last = ' ';
    int flag = 0;
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
                cout << "Строка " << line_ind << ": найдена структура с началом имени в " << index << endl;
                
                is_initialization();
                //is_initialization(index);
            } else {
                cout << "Строка " << line_ind << ": структура не подходит, код ошибки " << index << endl;
            }
            //cout << line << endl;
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

int checkers::is_initialization(){
    int len = line.length();
    //printf("%c %d\n",line[beginning],line[beginning]);
    int countr = 0;
    word = "";
    while (index < len && (isalnum(line[index]) || line[index] == '_') && countr < 255){
        word.push_back(line[index]);
        index++;
        countr++;
    }
    
    while (index < len && (line[index] == ' ' || line[index] == '\n' || line[index] == '\t')){
        if (line[index] == '\n')  line_ind++;
        index++;
    }
    cout << "Имя = " << word << endl;
    if (countr == 0){
        cerr << "Строка " << line_ind << ": ОШИБКА: Имя структуры не указано" << endl;
    }else if(countr >= 255){
        cerr << "Строка " << line_ind << ": ОШИБКА: Имя структуры слишком большое" << endl;
    } else if (is_good_name() < 0){
        ;//ошибка уже будет выведена
    } else if (line[index] == ';'){
        cout << "Строка " << line_ind << ": struct " << word << ";" << " не является обьявлением структуры" << endl;
    } else if (line[index] != '{'){
        cerr << "Строка " << line_ind << ": ОШИБКА: Ожидалось \"{\", но после имени идёт " << line[index] << endl;
    } else {
        //имя нормальное, после него есть {
        cout << "Ура, пока всё хорошо" << endl;
        cout << "now char = \'" << line[index] << "\'" << endl;
    
        is_good_attr();
        cout << endl;
    }

    return 0;
}



int checkers::is_good_name(){
    vector<string> forbidden = {"auto","break","case","char","const","continue","default","do","double","else","enum",
    "extern","float","for","goto","if","inline","int","long","register","restrict","return",
    "short","signed","sizeof","static","struct","switch","typedef","union","unsigned","void",
    "volatile","while",};
    int output_code = 0;
    for (unsigned int i = 0; i< forbidden.size();i++){
        if (word == forbidden[i]){
            cerr << "Строка " << line_ind << ": ОШИБКА: Имя " << word << " является зарезервированным и не может быть использовано" << endl;
            output_code = -1;
        }
    }
    if (!output_code && isdigit(word[0])){
        cerr << "Строка " << line_ind << ": ОШИБКА: Имя " << word << " начинается с цифры и не может быть использовано" << endl;
        output_code = -2;
    }
    for (unsigned int i = 0; !output_code && i < word.size();i++){
        if (!( isalnum(word[i]) || word[i] == '_')){
            cerr << "Строка " << line_ind << ": ОШИБКА: Имя " << word << " содержит недопустимые символы и не может быть использовано" << endl;
            output_code = -3;
        }
    }
    if (output_code != 0){
        struct_result = -1;
    }
    return output_code;
}

int checkers::is_good_type(){
    int res = 0;
    vector<string> types = {"char","int","float","double","char*","int*","float*","double*"};
    for (unsigned int i = 0; i < types.size(); i++){
        if (word == types[i])   res+=i+1;
    }

    cout << " Полученный тип это " << word << endl; 
    if (line[index] != ' '){
        cout << "Строка " << line_ind << ": ОШИБКА: Недопустимый символ при определении типа " << line[index] << endl;
        res = -1;
    } else if (word.length() >= 7 || res == 0){
        cout << " Строка " << line_ind << ": ОШИБКА: Неправильное название базового типа " << word << endl;
        res = -1;
    }
    return res;
}

int checkers::is_next_end(){
    big_pass_tab();
    if (line[index] == '}'){
        cout << "Я нашёл скобку!!!!!" << endl;
        if (attr_cout == 0){
            cout << "Строка " << line_ind << ": ОШИБКА: в структуре отсутствуют атрибуты" << endl;
        } else if (struct_result != 0) {
            cout << "Обьявление структуры содержит ошибки" << endl;
        } else {
            cout << "Обьявление структуры правильное" << endl;
        }
    }
}

int checkers::is_good_attr(){
    cout << endl;
    index++; // ?
    is_next_end();
    //получение типа
    get_word();
    // а теперь проверяем имя типа
    is_good_type();
    pass_tab();
    //получение и проверка имени атрибута
    get_word();
    pass_tab();
    check_name();
    big_pass_tab();
    if (line[index] == '}' || res != 0){
        //cout << "Я нашёл скобку!!!!!" << endl;
        return res;
    } else {
        attr_cout++;
        is_good_attr();
    }

    return res;
}

void checkers::pass_tab(){
    while (line[index] == ' ' || line[index] == '\t'){
        index++;
    }
}

void checkers::big_pass_tab(){
    while (line[index] == ' ' || line[index] == '\t' || line[index] == '\n' || index == (int)line.length()-1){
        if (line[index] == '\n' || index == (int)line.length()-1){
            getline(file,line);
            index = 0;
            line_ind++;
        } else {
            index++;
        }
    }
}


void checkers::get_word(){
    word = "";
    int countr = 0;
    while (line[index] != ' ' && line[index] != ';' && line[index] != '}' && line[index] != '\n' && countr < 256){
        word.push_back(line[index]);
        index++;
        countr++;
    }
}

void checkers::check_name(){
    if (line[index] != ';'){
        cout << "Строка " << line_ind << ": ОШИБКА: Отсутствует ; при определении поля структуры " << line[index] << endl;
        struct_result = -1;
    } else if (word.length() >= 256 || is_good_name()){
        cout << "Строка " << line_ind << ": ОШИБКА: Неправильное имя базового типа " << word << endl;
        struct_result = -1;
    }
    if (struct_result == 0){
        cout << "Строка " << line_ind << ": имя " << word << " правильное" << endl;
        //cout << "Строка " << line_ind << ": содержит правильное определение поля структуры" << endl;
        pass_tab();
    }
}


// int main(){
//     checkers checker;
//     checker.begin();
//     return 0;
// }
