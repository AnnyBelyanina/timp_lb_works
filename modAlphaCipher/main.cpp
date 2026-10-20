#include <iostream>
#include <locale>
#include "modAlphaCipher.h"

using namespace std;
void check(const wstring& Text, const wstring& key, const bool destructCipherText = false){
    try {
        wstring cipherText;
        wstring decryptedText;
        modAlphaCipher cipher(key);
        cipherText = cipher.encrypt(Text);
        if (destructCipherText)
            cipherText.front() = towlower(cipherText.front());
        decryptedText = cipher.decrypt(cipherText);
        wcout<<"key="<<key<<endl;
        wcout<<Text<<endl;
        wcout<<cipherText<<endl;
        wcout<<decryptedText<<endl;
        if (Text == decryptedText)
            wcout<<"Ok\n";
        else
            wcout<<"Err\n";
    }
    catch(const cipher_error& e){
        wcerr << L"Error: " << e.what() << endl;
    }
}

int main(int argc, char **argv)
{
	setlocale(LC_ALL,"ru_RU.UTF-8");
	check(L"ЛОВКАЯКОРИЧНЕВАЯЛИСАПЕРЕПРЫГНУЛАЛЕНИВУЮСОБАКУ",L"ПРОСТОЙ");
	check(L"ЛОВКАЯКОРИЧНЕВАЯЛИСАПЕРЕПРЫГНУЛАЛЕНИВУЮСОБАКУ",L"ПРИМЕР");
	check(L"ЛОВКАЯКОРИЧНЕВАЯЛИСАПЕРЕПРЫГНУЛАЛЕНИВУЮСОБАКУ",L"АБВГ");
	
    check(L"ЛОВКАЯКОРИЧНЕВАЯЛИСАПЕРЕПРЫГНУЛАЛЕНИВУЮСОБАКУ", L"");
    check(L"ЛОВКАЯКОРИЧНЕВАЯЛИСАПЕРЕПРЫГНУЛАЛЕНИВУЮСОБАКУ", L"АБВГ123");
    check(L"123456", L"АБВГ");
    check(L"ЛОВКАЯКОРИЧНЕВАЯЛИСА", L"ПРОСТОЙ", true);
    
    return 0;
}