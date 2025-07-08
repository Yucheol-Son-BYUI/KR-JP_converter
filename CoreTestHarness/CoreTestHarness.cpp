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
    std::wcin.imbue(std::locale("kor"));  // �Ǵ� "Korean"
    std::wcout.imbue(std::locale("kor"));

    if (!initialize()) {
        std::wcerr << L"initialize() ����\n";
        return -1;
    }

    std::wcout << "************ Initialization Complete! ************" << "\n";

    //// TEST: initialize
    //// ���󰡳� ���̺�
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
    //// ��Ÿī�� ���̺�
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

    // �ϼ��� �ѱ� ���� �׽�Ʈ
    std::wstring sample = L"������";
    std::wcout << L"DecomposeString: ";
    auto jamos = decomposeString(sample);
    for (wchar_t j : jamos) {
        std::wcout << j << L' ';
    }
    std::wcout << L"\n";

    // ���� ��ȯ �׽�Ʈ
    const wchar_t* in = L"���ġ��";
    wchar_t* out = convertString(in, false);
    std::wcout << L"convertString(\"" << in << L"\"): " << out << L"\n";
    freeResult(out);


    bool exit = false;
    std::wstring str;
    do {
        std::wcout << L"�Ϻ��� ������ �Է��ϼ���.\n";
        std::getline(std::wcin, str);

        std::wcout << convertString(str.c_str(), false) << "\n";
    } while (!exit);

    return 0;
}
