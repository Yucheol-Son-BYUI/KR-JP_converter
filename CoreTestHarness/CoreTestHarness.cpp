#include <iostream>
#include "hangul2kana.h"
#include <io.h>     // _setmode, _fileno
#include <fcntl.h>  // _O_U16TEXT
#include <string>
#include <windows.h>


int wmain() {
    //_setmode(_fileno(stdout), _O_U16TEXT);
    SetConsoleOutputCP(949);
    SetConsoleCP(949);
    std::wcin.imbue(std::locale("kor"));  // 또는 "Korean"
    std::wcout.imbue(std::locale("kor"));

    if (!initialize()) {
        std::wcerr << L"initialize() 실패\n";
        return -1;
    }

    std::wcout << "************ Initialization Complete! ************" << "\n";

    //// TEST: initialize
    //// 히라가나 테이블
    //std::wcout << L"=== Hiragana Table ===\n";
    //std::wcout << "KANA_ROW_COUNT: " << KANA_ROW_COUNT << "\n";
    //for (int row = 0; row < KANA_ROW_COUNT; ++row) {
    //    std::wcout << L"Row " << row << L": ";
    //    for (const auto& entry : g_hiraganaTable[row]) {
    //        if (entry.empty()) std::wcout << L"- ";
    //        else std::wcout << entry << L" ";
    //    }
    //    std::wcout << L"\n";
    //}

    //// TEST: initialize
    //// 가타카나 테이블
    //std::wcout << L"=== Katakana Table ===\n";
    //for (int row = 0; row < KANA_ROW_COUNT; ++row) {
    //    std::wcout << L"Row " << row << L": ";
    //    for (const auto& entry : g_katakanaTable[row]) {
    //        if (entry.empty())
    //            std::wcout << L"- ";
    //        else 
    //            std::wcout << entry << L" ";
    //    }
    //    std::wcout << L"\n";
    //}

    // 완성형 한글 분해 테스트
    std::wstring sample = L"강감찬";
    std::wcout << L"DecomposeString: ";
    auto jamos = decomposeString(sample);
    for (wchar_t j : jamos) {
        std::wcout << j << L' ';
    }
    std::wcout << L"\n";

    // 간단 변환 테스트
    const wchar_t* in = L"곤니치와";
    wchar_t* out = convertString(in, false);
    std::wcout << L"convertString(\"" << in << L"\"): " << out << L"\n";
    freeResult(out);


    bool exit = false;
    std::wstring str;
    do {
        std::wcout << L"일본어 독음을 입력하세요.\n";
        std::getline(std::wcin, str);

        std::wcout << convertString(str.c_str(), false) << "\n";
    } while (!exit);

    return 0;
}
