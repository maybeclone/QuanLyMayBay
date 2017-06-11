
#ifndef DSMB_H
#define DSMB_H
#include "MayBay.h"

#define MAX_MB 100

class DSMB
{
	private:
		int size;
		MayBay ds[MAX_MB];

	protected:
		void delAtPosition(int);
		int isDuplicate(char*);
		void DHxuatMB(short x, short y, int selection);
		void DH_MBthemCB(MayBay*, short, short, short, short);
		int isDuplicateCB_All(char*);

	public:
		DSMB(int size=0);
		
		int insert(MayBay);
		int del(char*); // check status cua chuyen->chi xoa khi all hoan tat
		int update(char*);
		
		int getSize();
		MayBay* getMayBay(char*);
		MayBay* getMayBay(int);

		void xuat();
		void DHnhapMB(short, short, short, short);
		void DHgetMB(short, short, short, short);
		void DHsuaMB(short, short, short, short);
		void DHsuaTT_MB(short, short, short, short, MayBay*);
		void DHxoaMB(short, short, short, short);
		void DHxoaTT_MB(short, short, short, short, MayBay*);
		
		void write(ofstream&);
		void read(ifstream&);
		
		int timkiemMBcoSB(char*);
		
		ChuyenBay* getCBcuaMB(char*, char*);
		
		void xemMB_ALL(short, short, short, short);
		
		int timCBdeSua_ALL(char*, ChuyenBay* &);
		int xoaCB_ALL(char*);
		int huyCB_ALL(char*, ChuyenBay*&);
		
		void capNhatSTT_ALL(Date&);
		
		int coHanhKhach_ALL(char*);
		
		ChuyenBay* getCBinDSHK_ALL(char*);
		
		ChuyenBay* getCBtheoMaCB(char*);
		
};
#endif
