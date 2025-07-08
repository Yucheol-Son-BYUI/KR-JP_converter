#include "pch.h"
#include "hangul2kana.h"
#include <cstdlib>   // malloc/free
#include <wchar.h>    // wcslen, wcscpy


CORE_API KanaTable g_hiraganaTable;
CORE_API KanaTable g_katakanaTable;

static const wchar_t INITIAL[19] = {
    L'ㄱ',L'ㄲ',L'ㄴ',L'ㄷ',L'ㄸ',
    L'ㄹ',L'ㅁ',L'ㅂ',L'ㅃ',L'ㅅ',
    L'ㅆ',L'ㅇ',L'ㅈ',L'ㅉ',L'ㅊ',
    L'ㅋ',L'ㅌ',L'ㅍ',L'ㅎ'
};
static const wchar_t MEDIAL[21] = {
    L'ㅏ',L'ㅐ',L'ㅑ',L'ㅒ',L'ㅓ',
    L'ㅔ',L'ㅕ',L'ㅖ',L'ㅗ',L'ㅘ',
    L'ㅙ',L'ㅚ',L'ㅛ',L'ㅜ',L'ㅝ',
    L'ㅞ',L'ㅟ',L'ㅠ',L'ㅡ',L'ㅢ',
    L'ㅣ'
};
static const wchar_t FINAL[28] = {
    L'\0',L'ㄱ',L'ㄲ',L'ㄳ',L'ㄴ',
    L'ㄵ',L'ㄶ',L'ㄷ',L'ㄹ',L'ㄺ',
    L'ㄻ',L'ㄼ',L'ㄽ',L'ㄾ',L'ㄿ',
    L'ㅀ',L'ㅁ',L'ㅂ',L'ㅄ',L'ㅅ',
    L'ㅆ',L'ㅇ',L'ㅈ',L'ㅊ',L'ㅋ',
    L'ㅌ',L'ㅍ',L'ㅎ'
};

bool initialize() {
    g_hiraganaTable.clear();
    g_katakanaTable.clear();
    g_hiraganaTable.resize(KANA_ROW_COUNT);
    g_katakanaTable.resize(KANA_ROW_COUNT);

    // basic character
    g_hiraganaTable[AA] = { L"あ",L"い",L"う",L"え",L"お" };
    g_hiraganaTable[KA] = { L"か",L"き",L"く",L"け",L"こ" };
    g_hiraganaTable[SA] = { L"さ",L"し",L"す",L"せ",L"そ" };
    g_hiraganaTable[TA] = { L"た",L"ち",L"つ",L"て",L"と" };
    g_hiraganaTable[NA] = { L"な",L"に",L"ぬ",L"ね",L"の" };
    g_hiraganaTable[HA] = { L"は",L"ひ",L"ふ",L"へ",L"ほ" };
    g_hiraganaTable[MA] = { L"ま",L"み",L"む",L"め",L"も" };
    g_hiraganaTable[YA] = { L"や",L"",  L"ゆ",L"",  L"よ" };
    g_hiraganaTable[RA] = { L"ら",L"り",L"る",L"れ",L"ろ" };
    g_hiraganaTable[WA] = { L"わ",L"",  L"",  L"",  L"を" };
    g_hiraganaTable[N] = { L"ん" };

    // 탁음 & 반탁음
    g_hiraganaTable[GA] = { L"が",L"ぎ",L"ぐ",L"げ",L"ご" };
    g_hiraganaTable[JA] = { L"ざ",L"じ",L"ず",L"ぜ",L"ぞ" };
    g_hiraganaTable[DA] = { L"だ",L"ぢ",L"づ",L"で",L"ど" };
    g_hiraganaTable[BA] = { L"ば",L"び",L"ぶ",L"べ",L"ぼ" };
    g_hiraganaTable[PA] = { L"ぱ",L"ぴ",L"ぷ",L"ぺ",L"ぽ" };

    // 요음
    g_hiraganaTable[YO] = { L"ゃ",L"",L"ゅ",L"",L"ょ"};
    //g_hiraganaTable[KYA] = { L"きゃ",L"きゅ",L"きょ" };
    //g_hiraganaTable[GYA] = { L"ぎゃ",L"ぎゅ",L"ぎょ" };
    //g_hiraganaTable[SYA] = { L"しゃ",L"しゅ",L"しょ" };
    //g_hiraganaTable[JA] = { L"じゃ",L"じゅ",L"じょ" };
    //g_hiraganaTable[CHYA] = { L"ちゃ",L"ちゅ",L"ちょ" };
    //g_hiraganaTable[NYA] = { L"にゃ",L"にゅ",L"にょ" };
    //g_hiraganaTable[HYA] = { L"ひゃ",L"ひゅ",L"ひょ" };
    //g_hiraganaTable[BYA] = { L"びゃ",L"びゅ",L"びょ" };
    //g_hiraganaTable[PYA] = { L"ぴゃ",L"ぴゅ",L"ぴょ" };

    // 촉음
    g_hiraganaTable[CHOT] = { L"っ" };
    // *KATAKANA*
    // basic 50 character
    g_katakanaTable[AA] = { L"ア",L"イ",L"ウ",L"エ",L"オ" };
    g_katakanaTable[KA] = { L"カ",L"キ",L"ク",L"ケ",L"コ" };
    g_katakanaTable[SA] = { L"サ",L"シ",L"ス",L"セ",L"ソ" };
    g_katakanaTable[TA] = { L"タ",L"チ",L"ツ",L"テ",L"ト" };
    g_katakanaTable[NA] = { L"ナ",L"ニ",L"ヌ",L"ネ",L"ノ" };
    g_katakanaTable[HA] = { L"ハ",L"ヒ",L"フ",L"ヘ",L"ホ" };
    g_katakanaTable[MA] = { L"マ",L"ミ",L"ム",L"メ",L"モ" };
    g_katakanaTable[YA] = { L"ヤ",L"",  L"ユ",L"",  L"ヨ" };
    g_katakanaTable[RA] = { L"ラ",L"リ",L"ル",L"レ",L"ロ" };
    g_katakanaTable[WA] = { L"ワ",L"",  L"",  L"",  L"ヲ" };
    g_katakanaTable[N] = { L"ン" };

    // 탁음, 반탁음
    g_katakanaTable[GA] = { L"ガ",L"ギ",L"グ",L"ゲ",L"ゴ" };
    g_katakanaTable[JA] = { L"ザ",L"ジ",L"ズ",L"ゼ",L"ゾ" };
    g_katakanaTable[DA] = { L"ダ",L"ヂ",L"ヅ",L"デ",L"ド" };
    g_katakanaTable[BA] = { L"バ",L"ビ",L"ブ",L"ベ",L"ボ" };
    g_katakanaTable[PA] = { L"パ",L"ピ",L"プ",L"ペ",L"ポ" };

    // 요음
    g_katakanaTable[YO] = { L"ャ",L"", L"ュ",L"", L"ョ" };
    //g_katakanaTable[KYA] = { L"キャ",L"キュ",L"キョ" };
    //g_katakanaTable[GYA] = { L"ギャ",L"ギュ",L"ギョ" };
    //g_katakanaTable[SYA] = { L"シャ",L"シュ",L"ショ" };
    //g_katakanaTable[JA] = { L"ジャ",L"ジュ",L"ジョ" };
    //g_katakanaTable[CHYA] = { L"チャ",L"チュ",L"チョ" };
    //g_katakanaTable[NYA] = { L"ニャ",L"ニュ",L"ニョ" };
    //g_katakanaTable[HYA] = { L"ヒャ",L"ヒュ",L"ヒョ" };
    //g_katakanaTable[BYA] = { L"ビャ",L"ビュ",L"ビョ" };
    //g_katakanaTable[PYA] = { L"ピャ",L"ピュ",L"ピョ" };

    // 촉음
    g_katakanaTable[CHOT] = { L"ッ" };

    return true;
}

static KanaRow mapInitialRow(wchar_t cho) {
    switch (cho) {
    case L'ㄱ':              return GA;
    case L'ㅋ': case L'ㄲ':   return KA;
    case L'ㄴ':              return NA;
    case L'ㄷ':              return DA;
    case L'ㅌ': case L'ㄸ':   return TA;
    case L'ㅂ':              return BA;
    case L'ㅍ': case L'ㅃ':  return PA;
    case L'ㅅ':              return SA;
    case L'ㅈ':              return JA;
    // case L'ㅊ':            // ㅊ은 따로 처리
    case L'ㅎ':              return HA;
    case L'ㅁ':              return MA;
    case L'ㄹ':              return RA;
    case L'ㅇ':              return AA; 
    }
}

static bool mapBasicVowel(wchar_t jung, int& col) {
    switch (jung) {
    case L'ㅏ': col = 0; return true;
    case L'ㅣ': col = 1; return true;
    case L'ㅜ': case L'ㅡ': col = 2; return true;
    case L'ㅔ': case L'ㅐ': col = 3; return true;
    case L'ㅗ': col = 4; return true;
    default:     return false;
    }
}

static bool mapYoVowel(wchar_t jung, int& col) {
    switch (jung) {
    case L'ㅑ': col = 0; return true;
    case L'ㅠ': col = 2; return true;
    case L'ㅛ': col = 4; return true;
    default:     return false;
    }
}

CORE_API wchar_t* convertString(const wchar_t* hangul, bool toKatakana) {
    std::wstring out;


    for (size_t i = 0; hangul[i]; ++i) {

        // Special case
        if (!toKatakana) {
            if (hangul[i] == L'은' || hangul[i] == L'는') {
                out += g_hiraganaTable[WA][0];
                continue;
            }
            else if (hangul[i] == L'을' || hangul[i] == L'를') {
                out += g_hiraganaTable[WA][4];
                continue;
            }
            else if (hangul[i] == L'야') {
                out += g_hiraganaTable[YA][0];
                continue;
            }
            else if (hangul[i] == L'유') {
                out += g_hiraganaTable[YA][2];
                continue;
            }
            else if (hangul[i] == L'요') {
                out += g_hiraganaTable[YA][4];
                continue;
            }
            else if (hangul[i] == L'치') {
                out += g_hiraganaTable[TA][1];
                continue;
            }
            else if (hangul[i] == L'차' || hangul[i] == L'챠') {
                out += g_hiraganaTable[TA][1];
                out += g_hiraganaTable[YO][0];
                continue;
            }
            else if (hangul[i] == L'츄') {
                out += g_hiraganaTable[TA][1];
                out += g_hiraganaTable[YO][2];
                continue;
            }
            else if (hangul[i] == L'초' || hangul[i] == L'쵸') {
                out += g_hiraganaTable[TA][1];
                out += g_hiraganaTable[YO][4];
                continue;
            }
            else if (hangul[i] == L'츠' || hangul[i] == L'추') {
                out += g_hiraganaTable[CHOT][0];
                continue;
            }
            else if (hangul[i] == L'와')
            {
                out += g_hiraganaTable[WA][0];
                continue;
            }
            else if (hangul[i] == L' ')
            {
                out += L' ';
                continue;
            }
            else if (hangul[i] == L',')
            {
                out += L'、';
                continue;
            }
            else if (hangul[i] == L'.')
            {
                out += L'。';
                continue;
            }
            else if (hangul[i] == L'.')
            {
                out += L'。';
                continue;
            }
            else if (hangul[i] == L'-')
            {
                out += L'ー';
                continue;
            }

        }
        wchar_t cho, jung, jong;
        if (!decomposeHangul(hangul[i], cho, jung, jong)) {
            out += hangul[i];
            continue;
        }

        // if cho is ㅊ, use special converting logic

        // 1) 초성+중성 → 카나 변환
        KanaRow row = mapInitialRow(cho);
        int col;
        if (mapBasicVowel(jung, col)) {
            // 기본 모음(あ い う え お)
            out += (toKatakana
                ? g_katakanaTable[row][col]
                : g_hiraganaTable[row][col]);
        }
        else if (mapYoVowel(jung, col)) {
            // 요음(ゃ ゅ ょ) 처리
            // TODO: 초성이 ㅇ인 경우는 요음 처리하지 말고 큰 문자 그대로
            // 1. 초성에 대응하는 I열(い) 문자
            const int I_COL = 1;
            out += (toKatakana
                ? g_katakanaTable[row][I_COL]
                : g_hiraganaTable[row][I_COL]);
            // 2. 요음 small 문자
            out += (toKatakana
                ? g_katakanaTable[YO][col]
                : g_hiraganaTable[YO][col]);
        }
        

        // 2) 종성 처리
        if (jong) {
            if (jong == L'ㄴ' || jong == L'ㅇ') {
                out += (toKatakana
                    ? g_katakanaTable[N][0]
                    : g_hiraganaTable[N][0]);
            }
            else if (jong == L'ㄱ' || jong == L'ㄷ' ||
                jong == L'ㅂ' || jong == L'ㅅ') {
                out += (toKatakana
                    ? g_katakanaTable[CHOT][0]
                    : g_hiraganaTable[CHOT][0]);
            }
        }
    }

    size_t count = out.size() + 1;
    wchar_t* result = static_cast<wchar_t*>(std::malloc(count * sizeof(wchar_t)));
    wcscpy_s(result, count, out.c_str());
    return result;
}


void resetState() {
    // TODO: 상태 초기화
}

wchar_t* processJamo(wchar_t jamo, bool toKatakana) {
    // TODO: 자모 누적 및 즉시 변환
    wchar_t* out = (wchar_t*)std::malloc(2 * sizeof(wchar_t));
    out[0] = jamo;
    out[1] = L'\0';
    return out;
}

wchar_t* finalizeBuffer(bool toKatakana) {
    // TODO: 남은 버퍼 변환
    wchar_t* out = (wchar_t*)std::malloc(sizeof(wchar_t));
    out[0] = L'\0';
    return out;
}

void freeResult(wchar_t* ptr) {
    std::free(ptr);
}

bool decomposeHangul(wchar_t syllable,
    wchar_t& cho,
    wchar_t& jung,
    wchar_t& jong)
{
    const int SBase = 0xAC00;
    const int LCount = 19, VCount = 21, TCount = 28;
    int SIndex = syllable - SBase;
    if (SIndex < 0 || SIndex >= LCount * VCount * TCount)
        return false;

    int LIndex = SIndex / (VCount * TCount);
    int VIndex = (SIndex % (VCount * TCount)) / TCount;
    int TIndex = SIndex % TCount;

    cho = INITIAL[LIndex];
    jung = MEDIAL[VIndex];
    jong = FINAL[TIndex];
    return true;
}


std::vector<wchar_t> decomposeString(const std::wstring& s) {
    std::vector<wchar_t> result;
    for (wchar_t wc : s) {
        wchar_t c1, c2, c3;
        if (decomposeHangul(wc, c1, c2, c3)) {
            result.push_back(c1);
            result.push_back(c2);
            if (c3) result.push_back(c3);
        }
        else {
            result.push_back(wc);
        }
    }
    return result;
}