#include "transpositionCipher.h"
#include <vector>
#include <cwctype>
using namespace std;

TranspositionCipher :: TranspositionCipher(int key){
    
    if (key <= 0){
        throw cipher_error("Key must be positive");
    }
    if (key == 1){
        throw cipher_error("Trivial transposition");
    }
    if (key > 10000){
        throw cipher_error("Key is too large");
    }
    
    cols = key;

}


inline wstring TranspositionCipher::getValidText(const wstring& text){
    if (text.empty()){
        throw cipher_error("Empty text");
    }
    wstring tmp;
    for (auto c : text){
        if (!iswprint(c)){
            throw cipher_error("Non-printable character in text");
        }
        tmp.push_back(c);
    }
    if (tmp.empty()){
        throw cipher_error("Empty text");
    }
    
    return tmp;
}


wstring TranspositionCipher:: encrypt(const wstring& text){
    wstring validText = getValidText(text);
    int s = validText.size();
    if (cols  > s) {
       throw cipher_error("Key is greater than lenght");
    }
        
    int rows = (s + cols - 1) / cols;
    vector<vector<wchar_t>> table (rows, vector<wchar_t>(cols, L' '));
    
    // Записываем текст в таблицу по строкам (слева направо, сверху вниз)
    for (int i = 0; i < s; i++){
        table[i / cols][i % cols] = validText[i];
    }
    // Считываем таблицу по столбцам справа налево , сверху вниз
    wstring result;
    for (int j = cols - 1; j >= 0; j--){        // столбцы справа налево
        for ( int i = 0; i < rows; i++){        // строки сверху вниз    
            if (i * cols +j < s){               // если клетка в пределах текста
                result += table[i][j];
            }
        }
    } 
    return result;
}   
wstring TranspositionCipher:: decrypt(const wstring& text){
    wstring validText = getValidText(text);
    int s = validText.size();
    if (cols  > s) {
       throw cipher_error("Key is greater than lenght");
    }
         
    
    int rows = (s + cols - 1) / cols;
    int full_rows = s / cols;             // сколько полных строк
    int rem = s % cols;                 // сколько столбцов имеют +1 символ
    vector<vector<wchar_t>> table (rows, vector<wchar_t>(cols, L' '));
    
    
    // Считаем высоту каждого столбца:
    // первые rem столбцов имеют full_rows+1 элементов, остальные — full_rows
    // индексация идёт справа налево, как при шифровании
    vector<int> height(cols);
    for (int j = 0; j < cols; j++){
        height[j] = full_rows + (j < rem ? 1 : 0);
    }
    
    // справа налево по столбцам, сверху вниз внутри столбца
    int idx = 0;
    for (int j = cols - 1; j >= 0; j--){
        for (int i = 0; i < height[j]; i++){
            table[i][j] = validText[idx++];
        }
    }
    
    // Читаем таблицу по строкам  получаем исходный текст
    wstring result;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (i * cols + j < s){
                result += table[i][j];
            }
        }
    }
    return result;
}
