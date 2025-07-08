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

// ���� ���� ���̺� Ÿ�� ���� �� extern ����
typedef std::vector<std::vector<std::wstring>> KanaTable;
extern CORE_API KanaTable g_hiraganaTable;
extern CORE_API KanaTable g_katakanaTable;
extern "C" {
	// ��ó��, ���� ���̺� �ε� ��
	CORE_API bool initialize();

	// �ϼ��� �ѱ� ���� �ϰ� ��ȯ
	CORE_API wchar_t* convertString(const wchar_t* hangul, bool toKatakana);

	// �ڸ� ���� ���� �ʱ�ȭ
	CORE_API void resetState();

	// �ڸ� �ϳ��� �Ѱܹ޾� ���� ��ȯ
	CORE_API wchar_t* processJamo(wchar_t jamo, bool toKatakana);

	// ���ۿ� ���� ���� ��ȯ ���ڿ� ���
	CORE_API wchar_t* finalizeBuffer(bool toKatakana);

	// ȣ���ڰ� ���� wchar_t* ��� ����
	CORE_API void freeResult(wchar_t* ptr);
}

// �ѱ� ���� API
// U+AC00~U+D7A3 �ϼ��� �ѱ��� �ʼ�/�߼�/�������� ����
CORE_API bool decomposeHangul(
	wchar_t syllable,
	wchar_t& cho,
	wchar_t& jung,
	wchar_t& jong
);

// ���ڿ� ��ü ����
CORE_API std::vector<wchar_t> decomposeString(const std::wstring& s);