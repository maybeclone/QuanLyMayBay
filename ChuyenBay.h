#ifndef CHUYENBAY_H
#define CHUYENBAY_H
#include "Date.h"
#include "HanhKhach.h"
#include <string.h>
#include <fstream>
#include <time.h>
#include "Utility.h"

#define HUY 0
#define CON_VE 1
#define HET_VE 2
#define HOAN_TAT 3
#define MAX_SAN_BAY 20
#define MAX_MA_CB 6

class ChuyenBay
{
	private:
		char maCB[MAX_MA_CB]; // duy I tren san bay;
		char sanBayDen[MAX_SAN_BAY];
		int trangThai; // 0: HUY	1: CON VE	2: HET VE	3: HOAN TAT
		Date ngKhoiHanh;
		char** dsVe = NULL; // MAX = so cho ngoi
		
		int soVe;
		
	public:
		
		ChuyenBay(const ChuyenBay&);
		ChuyenBay operator=(const ChuyenBay&);
		
		ChuyenBay();
		ChuyenBay(int, char*, Date); // constructor BO
		ChuyenBay(char*, char*, int, Date);
		ChuyenBay(char*, char*, Date, int);
		~ChuyenBay();
		
		int getTrangThai();
		int getSoVe();
		char* getMaCB();
		char* getSanBayDen();
		Date* getNgKhoiHanh();
		char** getDSVe();
		
		void xuat();
		
		int update(); //khong the update neu stt la HUY, HOAN_TAT
		int huyChuyen(); // khong the huy neu stt la HUY, HOAN_TAT

		void write(ofstream&);
		void read(ifstream&);
		
		int soVeConTrong();
		void datVe(int*, int, char*);
		
		void DHhieuchinhNgKhoiHanh(short, short, short, short);
		
		void capNhatSTT(Date&);
		
		int coHanhKhach(char*);
		
		void inCBtheoNgay(short&, short&y, int&);
};

#endif
