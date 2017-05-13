#pragma once
#include "mylib.h"
#include <iostream>
#include <windows.h>
#include <string.h>
#include <fstream>
#include <math.h>

#define CR_ITEM 3
#define CD_ITEM 25
#define MARGIN_X 7
#define MARGIN_Y 2
#define MAX_TEXT_MENU 15

#define ENTER 13
#define BACKSPACE 8
#define ESC 27
#define SPACE 32
#define PAGE_UP 73
#define PAGE_DOWN 81
#define RIGHT 77
#define LEFT 75
#define UP 72
#define DOWN 80
#define INSERT 82

#define COLOR_BG_DEFAULT 0
#define COLOR_BG_ITEM 3
#define COLOR_BG_ITEM_SELECTED 11
#define COLOR_TEXT_ITEM 15
#define COLOR_TEXT_ITEM_SELECTED 0
#define COLOR_TEXT_DEFAULT 15
#define COLOR_HIGHLIGHT_TEXT 14
#define COLOR_WARRING 12
#define COLOR_SUCCESS 9

using namespace std;

#include <io.h>
#include <fcntl.h>

const wchar_t TB = L'\x2550';
const wchar_t LR = L'\x2551';
const wchar_t TL = L'\x2554';
const wchar_t TR = L'\x2557';
const wchar_t BL = L'\x255A';
const wchar_t BR = L'\x255D';
const wchar_t BWT = L'\x2566';
const wchar_t BWB = L'\x2569';
const wchar_t BWL = L'\x2560';
const wchar_t BWR = L'\x2563';
const wchar_t PLUS = L'\x256C';

const wchar_t TB_LINE = L'\x2500';
const wchar_t LR_LINE = L'\x2502';
const wchar_t TL_LINE = L'\x250C';
const wchar_t TR_LINE = L'\x2510';
const wchar_t BL_LINE = L'\x2514';
const wchar_t BR_LINE = L'\x2518';
const wchar_t BWT_LINE = L'\x252C';
const wchar_t BWB_LINE = L'\x2534';
const wchar_t BWL_LINE = L'\x251C';
const wchar_t BWR_LINE = L'\x2524';
const wchar_t PLUS_LINE = L'\x253C';


	

void ve4Goc(short x1, short y1, short x2, short y2);
void veCanhTB(short x1, short y1, short x2, short y2);
void veCanhLR(short x1, short y1, short x2, short y2);
void veCanhBETWEEN(short x1, short y1, short x2, short y2);
void veKhungItem(short x1, short y1, short x2, short y2);

void xoaMenuItem(char dsMenu[][MAX_TEXT_MENU], int size, short x1, short y1, short x2, short y2,
					const short MAR_X, const short MAR_Y, const short CD, const short CR);

int veMenu(char dsMenu[][MAX_TEXT_MENU], int size, short x1, short y1, short x2, short y2, 
				const short MAR_X, const short MAR_Y, const short CD, const short CR, int sel);

void veKhungMenu(short x1, short y1, short x2, short y2);
void veKhungItem(short x1, short y1, short x2, short y2);
void veKhung(short x1, short y1, short x2, short y2);

void veCanhLR(short x1, short y1, short x2, short y2);

void veCanhBETWEEN(short x1, short y1, short x2, short y2);

void veCanhTB(short x1, short y1, short x2, short y2);

void ve4Goc(short x1, short y1, short x2, short y2);

void xoaKhung(short x1, short y1, short x2, short y2);

// col-1
void veTable(int col, float* sale, short x1, short y1, short x2, short y2);

void veLable(float* sale, int col, short x1, short y1, int CD);

void inLable(short x, short y);
