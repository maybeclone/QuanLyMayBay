#ifndef DSHANHKHACH_H
#define DSHANHKHACH_H

#include <fstream>
#include <stack>
#include "NodeHK.h"
#include "Utility.h"

class DSHanhKhach
{
	private:
		NodeHK* root;
		void del(NodeHK*);
	protected:
		int themHK_DQ(NodeHK*&, HanhKhach&);
		void demSize_DQ(NodeHK*, int&);
		void xuat_DQ(NodeHK*);
	public:
		DSHanhKhach();
		~DSHanhKhach();
		
		int themHK(HanhKhach&);
		int getSize();
		
		int isDuplicate(char*);
		void xuat();
		
		void nhapHK();
		
		// doc & ghi FILE
		void write(ofstream&);
		void read(ifstream&);
		
		void DHthemHK(short, short, short, short);
		int DHthemHKtheoCMND(short, short, short, short, char*);
		int DHsuaHK(short, short, short, short, char*);
		
		HanhKhach* getHK(char*);
		
		void xoaHK(char*);
		void xoaHK_DQ(char*, NodeHK*&);
		void timNhoNhat(NodeHK*&, NodeHK*&);
		
		void DHxuatHK_ALL(short&, short&, int&);
		void DHxuatHK_ALL_DQ(NodeHK*, short&, short&, int&);
	
};

#endif
