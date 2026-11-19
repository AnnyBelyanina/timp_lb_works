#include <UnitTest++/UnitTest++.h>
#include "transpositionCipher.h"
#include <string>
#include <clocale> 

SUITE(TranspositionKeyTest){
    TEST(ValidKey){
        TranspositionCipher cp(3);
        CHECK(true);
    }
    TEST(ZeroKey){
        CHECK_THROW(TranspositionCipher cp(0),cipher_error);
    }
    
    TEST(NegativeKey){
        CHECK_THROW(TranspositionCipher cp(-5),cipher_error);
    }
    TEST(TrivialKey){
        CHECK_THROW(TranspositionCipher cp(1),cipher_error);
    }
}

struct TranspFixture {
    TranspositionCipher* p;
    TranspFixture() {
        p = new TranspositionCipher(3);
    }
    ~TranspFixture() {
        delete p;
    }
};

SUITE(TranspositionEncryptTest) {
    TEST_FIXTURE(TranspFixture, ValidText) {
        CHECK(p->encrypt(L"ПРИВЕТМИР") == std::wstring(L"ИТРРЕИПВМ"));
    }
    TEST_FIXTURE(TranspFixture, TextWithSymbols) {
        CHECK(p->encrypt(L"А Б В Г Д") == std::wstring(L"Б Д В А Г"));
    }
    TEST_FIXTURE(TranspFixture, EmptyText){
        CHECK_THROW(p->encrypt(L""), cipher_error);
    }
    TEST_FIXTURE(TranspFixture, NonPrintableText){
        CHECK_THROW(p->encrypt(L"ПРИВЕТ\nМИР"), cipher_error);
    }
    TEST_FIXTURE(TranspFixture, KeyGreaterThanLength){
        TranspositionCipher cp(10);
        CHECK_THROW(cp.encrypt(L"ПРИВЕТ"), cipher_error);
    }
}

SUITE(TranspositionDecryptTest) {
    TEST_FIXTURE(TranspFixture, ValidText) {
        CHECK(p->decrypt(L"ИТРРЕИПВМ") == std::wstring(L"ПРИВЕТМИР"));
    }
    TEST_FIXTURE(TranspFixture, TextWithSpaces) {
        CHECK(p->decrypt(L"Б Д В А Г") == std::wstring(L"А Б В Г Д"));
    }
    TEST_FIXTURE(TranspFixture, EmptyText) {
        CHECK_THROW(p->decrypt(L""), cipher_error);
    }
    TEST_FIXTURE(TranspFixture, NonPrintableText) {
        CHECK_THROW(p->decrypt(L"ИТР\nРЕИ"), cipher_error);
    }
    TEST_FIXTURE(TranspFixture, KeyGreaterThanLength) {
        TranspositionCipher cp(10);
        CHECK_THROW(cp.decrypt(L"ПРИВЕТМИР"), cipher_error);
    }
}

int main(int argc, char** argv) {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    return UnitTest::RunAllTests();
}