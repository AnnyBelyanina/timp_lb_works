#include <iostream>
#include <locale>
#include <limits>
#include "transpositionCipher.h"
using namespace std;

int main (int argc, char** argv){
    setlocale(LC_ALL, "ru_RU.UTF-8");
    
    int key;
    wstring text;
    unsigned op;
    try{
        wcout << L"Введите ключ (число столбцов): ";
        wcin >> key;
        wcin.ignore(numeric_limits<streamsize>::max(), L'\n');
        
        TranspositionCipher cipher(key);           // Создаём шифратор
        wcout << L"Ключ загружен\n";
    
        do {
            wcout << L"Выберите операцию (0-выход, 1-зашифровать, 2-расшифровать): ";
            wcin >> op;
            wcin.ignore(numeric_limits<streamsize>::max(), L'\n');
        
            if (op > 2) {
                wcout << L"Неправильная операция\n";
                continue;   // возвращаемся к началу цикла
            }

            if (op == 0) break; 
        
            wcout << L"Введите любой текст: ";
            getline(wcin,text);

            if (op == 1) {
                wcout << L"Зашифрованный текст: " << cipher.encrypt(text) << endl;
            }
            else {
                wcout << L"Расшифрованный текст: " << cipher.decrypt(text) << endl;
            }

        } while (op != 0);
    }
    catch (const cipher_error& e){
        wcerr << L"Ошибка:" << e.what() << endl;
        return 1;
    }
    return 0;
    
}