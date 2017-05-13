#ifndef MAYBAY_H
#define MAYBAY_H


#include <iomanip>
#include <string.h>
#include <iostream>
#include <conio.h>
#include <fstream>
#include <time.h>
#include "ChuyenBay.h"

#include "NodeCB.h"

#include "dohoa.h"
#include "Utility.h"


using namespace std;

#define MAX_SOHIEU_MB 6
#define MAX_SOCHO 450

class MayBay
{
	private:
		char soHieu[MAX_SOHIEU_MB];
		int soCho;
		NodeCB* first;
		
	protected:
		void deleteFirst();
		void deleteAfter(NodeCB*);
	public:
		
		void insert(ChuyenBay&);
		int deleteTheoMaCB(char*);
		
		MayBay();
		MayBay(char*, int);
		MayBay(char*,int, NodeCB*);
		~MayBay();
		
		MayBay( MayBay&);
		MayBay operator=(MayBay&);
	
		// getter vs setter
		NodeCB* getFirst();
		void setFirst(NodeCB*);
		char* getSoHieu();
		int getSoCho();
		int getSizeCB();
		void setSoHieu(char*);
		void setSoCho(int);
		
		// kiem tra SUA duoc hay khong
		int checkTrangThai();
	
		int updateCB(char*);
		
		ChuyenBay* getCB(char*);
		
		void themCB();
		void xuatCB();
		
		void xuat();
		void nhap();
		
		void writeCB(ofstream&);
		void readCB(ifstream&);
		
		int isDuplicateCB(char*);
		
		int timKiemSanBayDen(char*);
		
		void DHinCBtheoSanBay(char*, short &x, short &y, int&);
		
		ChuyenBay* getCBtheoSanBay(char*, char*);
		
		int coTheXoa(NodeCB*&);
		int coTheHuy(NodeCB*&);
		int suaCB(char*, ChuyenBay*&);
		int xoaCB(char*);
		int huyCB(char*, ChuyenBay*&);
		
		void DHshowCB_ALL(short&, short&, int &);
		
		void capNhatSTT(Date&);
		
		int coHanhKhach(char*);
		
		ChuyenBay* getCBinDSHK(char*);
		
		void inCBtheoDatevsConVe(const Date&, short&, short&, int&);
		
		int getSLCB();
		void xuatThongKe(short &, short &, int &);
};

#endif
