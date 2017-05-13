#pragma once
#include <windows.h>
#include "dohoa.h"

#define MAX_NAM 2200



// an hien con tro nhap nháy trong cua so Console
void ShowCur(bool CursorVisibility);

// input
int them(char* ma, int size, int &n, char c);
int xoa(char* ma, int &n);
int checkMa(char* ma, int size, int &n, char& c);
int nhapMa(char* ma, int size);
int nhapMa_EDIT(char* ma, int size, int _n);
int checkSo(char* ma, int size, int &n, char& c);
int nhapSo(char* ma, int size);
int nhapSo_EDIT(char* ma, int size, int _n);
int checkTen(char* ma, int size, int &n, char& c);
int nhapTen(char* ma, int size);
int nhapTen_EDIT(char* ma, int size, int _n);
int tinhSoTrang(int);
int checkMa_DEMO(char* ma, int size, int &n, char& c);

// check input Date

int checkNam(int nam, int cur_nam);
bool checkNMNhuan(int yyyy);
int checkThang(int nam, int thang, int cur_nam, int cur_thang);
int checkNgay(int nam, int thang, int ngay, int cur_nam, int cur_thang, int cur_ngay);
int checkGio(int gio);
int checkPhut(int phut);

// ve~ ve
void ve1Ve(int soVe, short x, short y);
void deleteViTri(int* soVe, int& size, int position);
int isDuplicate(int* soVe, int size, int x);
int soVeCon(char** ve, int size);
int* veSoVe(char** ve, int size, short x1, short y1, short x2, short y2, int& soVeMua);

void veVeTrong(char** ve, int size, short x1, short y1, short x2, short y2);

