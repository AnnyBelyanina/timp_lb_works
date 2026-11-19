#include <UnitTest++/UnitTest++.h>
#include "modAlphaCipher.h"
#include <string>
#include <clocale>

SUITE(KeyTest) {
    TEST(ValidKey) {
        CHECK(modAlphaCipher(L"БВГ").encrypt(L"ААААА") == std::wstring(L"БВГБВ"));
    }
    TEST(LongKey) {
        CHECK(modAlphaCipher(L"БВГДЕЁЖЗИЙКЛ").encrypt(L"АААААААААА") == std::wstring(L"БВГДЕЁЖЗИЙ"));
    }
    TEST(LowCaseKey) {
        CHECK(modAlphaCipher(L"бвг").encrypt(L"ААААА") == std::wstring(L"БВГБВ"));
    }
    TEST(DigitsInKey) {
        CHECK_THROW(modAlphaCipher cp(L"Б1"), cipher_error);
    }
    TEST(PunctuationInKey) {
        CHECK_THROW(modAlphaCipher cp(L"Б,В"), cipher_error);
    }
    TEST(WhitespaceInKey) {
        CHECK_THROW(modAlphaCipher cp(L"Б В"), cipher_error);
    }
    TEST(EmptyKey) {
        CHECK_THROW(modAlphaCipher cp(L""), cipher_error);
    }
    TEST(WeakKey) {
        CHECK_THROW(modAlphaCipher cp(L"ААА"), cipher_error);
    }
}

struct KeyB_fixture {
    modAlphaCipher* p;
    KeyB_fixture() {
        p = new modAlphaCipher(L"Б");
    }
    ~KeyB_fixture() {
        delete p;
    }
};

SUITE(EncryptTest) {
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK(p->encrypt(L"СЪЕШЬЕЩЁМЯГКИХРУССКИХБУЛОК") == std::wstring(L"ТЫЁЩЭЁЪЖНАДЛЙЦСФТТЛЙЦВФМПЛ"));
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK(p->encrypt(L"съешьещёмягкихрусскихбулок") == std::wstring(L"ТЫЁЩЭЁЪЖНАДЛЙЦСФТТЛЙЦВФМПЛ"));
    }
    TEST_FIXTURE(KeyB_fixture, StringWithWhitespaceAndPunct) {
        CHECK(p->encrypt(L"Съешь ещё! Мягких русских булок?") == std::wstring(L"ТЫЁЩЭЁЪЖНАДЛЙЦСФТТЛЙЦВФМПЛ"));
    }
    TEST_FIXTURE(KeyB_fixture, StringWithNumbers) {
        CHECK(p->encrypt(L"Привет 2026 года") == std::wstring(L"РСЙГЁУДПЕБ"));
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->encrypt(L""), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, NoAlphaString) {
        CHECK_THROW(p->encrypt(L"1234+8765=9999"), cipher_error);
    }
    TEST(MaxShiftKey) {
        CHECK(modAlphaCipher(L"Я").encrypt(L"АБВГ") == std::wstring(L"ЯАБВ"));
    }
}

SUITE(DecryptTest) {
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK(p->decrypt(L"ТЫЁЩЭЁЪЖНАДЛЙЦСФТТЛЙЦВФМПЛ") == std::wstring(L"СЪЕШЬЕЩЁМЯГКИХРУССКИХБУЛОК"));
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_THROW(p->decrypt(L"тЪФЕШЬЕЁНБЛКЙУСЛТЛЙУСЙВЦМБП"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, WhitespaceString) {
        CHECK_THROW(p->decrypt(L"ТЪФЕ ШЬЕЁ НБЛК ЙУСЛ ТЛЙУ СЙВЦ МБП"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, DigitsString) {
        CHECK_THROW(p->decrypt(L"ТЪФЕШЬЕЁ2026НБЛКЙУСЛ"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, PunctString) {
        CHECK_THROW(p->decrypt(L"ТЪФЕШЬЕЁ,НБЛК"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->decrypt(L""), cipher_error);
    }
    TEST(MaxShiftKey) {
        CHECK(modAlphaCipher(L"Я").decrypt(L"ЯАБВ") == std::wstring(L"АБВГ"));
    }
}

int main(int argc, char** argv) {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    return UnitTest::RunAllTests();
}