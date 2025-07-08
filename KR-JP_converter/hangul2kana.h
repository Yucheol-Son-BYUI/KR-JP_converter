#pragma once

#ifdef CORE_EXPORTS
#define CORE_API __declspec(dllexport)
#else
#define CORE_API __declspec(dllimport)
#endif
#include <vector>
#include <string>
enum KanaRow {
	AA, KA, SA, TA, NA,
	HA, MA, YA, RA, WA, N,
	GA, JA, DA, BA, PA,
	//KYA, GYA, SYA, JA, CHYA, NYA, HYA, BYA, PYA,
	YO,
	CHOT,
	KANA_ROW_COUNT
};

// 전역 매핑 테이블 타입 정의 및 extern 선언
typedef std::vector<std::vector<std::wstring>> KanaTable;
extern CORE_API KanaTable g_hiraganaTable;
extern CORE_API KanaTable g_katakanaTable;
extern "C" {
	// 전처리, 매핑 테이블 로드 등
	CORE_API bool initialize();

	// 완성된 한글 문장 일괄 변환
	CORE_API wchar_t* convertString(const wchar_t* hangul, bool toKatakana);

	// 자모 단위 상태 초기화
	CORE_API void resetState();

	// 자모 하나를 넘겨받아 누적 변환
	CORE_API wchar_t* processJamo(wchar_t jamo, bool toKatakana);

	// 버퍼에 남은 최종 변환 문자열 얻기
	CORE_API wchar_t* finalizeBuffer(bool toKatakana);

	// 호출자가 받은 wchar_t* 결과 해제
	CORE_API void freeResult(wchar_t* ptr);
}

// 한글 분해 API
// U+AC00~U+D7A3 완성형 한글을 초성/중성/종성으로 분해
CORE_API bool decomposeHangul(
	wchar_t syllable,
	wchar_t& cho,
	wchar_t& jung,
	wchar_t& jong
);

// 문자열 전체 분해
CORE_API std::vector<wchar_t> decomposeString(const std::wstring& s);