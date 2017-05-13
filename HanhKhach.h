#ifndef HANHKHACH_H
#define HANHKHACH_H

#include <iomanip>
#include <string.h>
#include <iostream>
#include "mylib.h"
#include "dohoa.h"

using namespace std;

#define MAX_TEN_HK 16
#define MAX_HO_HK 30
#define MAX_CMND 10

class HanhKhach
{
	private:
		char CMND[MAX_CMND]; // 9 so
		char ten[MAX_TEN_HK];
		char ho[MAX_HO_HK];
		bool phai; // false nu true nam
	public:
		HanhKhach();
		HanhKhach(char*, char*, char*, bool);
		
		void xuat();
		
		// getter
		char* getCMND();
		char* getTen();
		char* getHo();
		bool getPhai();
		
		// setter
		void setCMND(char*);
		void setTen(char*);
		void setHo(char*);
		void setPhai(bool);
		
		void DHinHKtheoMaCB(short&, short&, int&, int);
};

#endif

