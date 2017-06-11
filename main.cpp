#include <iostream>
#include "DSMB.h"
#include "DSHanhKhach.h"

#define X1 3
#define Y1 1
#define X2 116
#define Y2 28

using namespace std;

DSMB dsmb;
DSHanhKhach dsHanhKhach;

char menuChinh[6][MAX_TEXT_MENU] = {"1. Dat Ve",
						 			"2. QLCB",
						 			"3. QLMB",
						 			"4. DSHK",
						 			"5. Xuat File",
						 			"6. Thoat"	};

char menuPhu_DatVe[2][MAX_TEXT_MENU] = {"Mua Ve",
										"Ve Trong"};

char menuPhu_QLMB[5][MAX_TEXT_MENU]	= {"Xem MB",
									   "Them MB",
									   "Sua MB",
									   "Xoa MB",
									   "Thong Ke"};
									   
char menuPhu_QLCB[6][MAX_TEXT_MENU]	= {"Xem CB",
									   "Them CB",
									   "Sua CB",
									   "Xoa CB",
									   "Huy CB",
									   "In (ngay)"};
				  
char menuPhu_HK[5][MAX_TEXT_MENU] = {"Xem HK",
									 "Them HK",
									 "Sua HK",
									 "Xoa HK",
									 "In (maCB)"};

void QLMB_ThongKe(short x1, short y1, short x2, short y2){
	/*
		Tong so cac ChuyenBay bao gom ca ChuyenBay HUY.
	*/
	
	float sale[5] = {0.1, 0.4, 0.25,};
	SetBGColor(COLOR_BG_DEFAULT);
	SetColor(COLOR_TEXT_DEFAULT);
	veLable(sale, 5, X1+8, Y1+1, 70);
	gotoxy(X1+11, Y1+2);
	wcout<<"STT";
	gotoxy(X1+22, Y1+2);
	wcout<<"SO HIEU MAY BAY";
	gotoxy(X1+49, Y1+2);
	wcout<<"SO CHO";
	gotoxy(X1+63, Y1+2);
	wcout<<"SO CHUYEN BAY";
	
	MayBay* mb;
	int soLuong_CB_max;
	int vitri_max;
	short x_bang = X1+8;
	short y_bang = Y1+4;
	int stt = 1;
	int flag[dsmb.getSize()] = {0};
	int dem = 0;
	while(dem<dsmb.getSize()){
		for(int i=0; i<dsmb.getSize(); i++){
			if(flag[i]==0){
				soLuong_CB_max = dsmb.getMayBay(i)->getSLCB();
				vitri_max = i; 	
				break;
			}
		}
		for(int i=0; i<dsmb.getSize(); i++){
			if(dsmb.getMayBay(i)->getSLCB() > soLuong_CB_max && flag[i]==0){
				vitri_max = i;
				soLuong_CB_max = dsmb.getMayBay(i)->getSLCB();
			}
		}
		flag[vitri_max] = 1;
		dsmb.getMayBay(vitri_max)->xuatThongKe(x_bang, y_bang, stt);
		dem++;
	}
		for(int i=x_bang+1; i<x_bang+70; i++){
		gotoxy(i, y_bang-1);
		wcout<<TB_LINE;
	}
	gotoxy(x_bang, y_bang-1);
	wcout<<BL_LINE;
	gotoxy(x_bang+70, y_bang-1);
	wcout<<BR_LINE;
	gotoxy(x_bang+7, y_bang-1);
	wcout<<BWB_LINE;
	gotoxy(x_bang+35, y_bang-1);
	wcout<<BWB_LINE;
	gotoxy(x_bang+52, y_bang-1);
	wcout<<BWB_LINE;

	while(true){
		if(getch()==ESC){
			return;
		}
	}
}

void case_QLMB(short x1, short y1, short x2, short y2){
	int s = 1;
	while(true){
		inLable(X1+48, Y1+1);
		s = veMenu(menuPhu_QLMB, 5, x1-10, y1, x2, y2, MARGIN_X+CD_ITEM+2, MARGIN_Y, CD_ITEM/2+1, CR_ITEM, s);
		switch(s){
			case 1:
				xoaKhung(X1+48, Y1+1, X2-2, Y2-2);
				dsmb.xemMB_ALL(x2+8, y1+3 , X2-8, Y2-2);
				break;
			case 2:
				xoaKhung(X1+48, Y1+1, X2-2, Y2-2);
				dsmb.DHnhapMB(x2+10, y1+5 , X2-10, Y2-5);
				ShowCur(false);	
				xoaKhung(x2+10, y1+5 , X2-10, Y2-5);
				break;
			case 3:
				xoaKhung(X1+48, Y1+1, X2-2, Y2-2);
				/*
					MayBay co ChuyenBay CON_VE hoac HET_VE
					thi khong the sua.
					
					MayBay co ChuyenBay da PUBLIC thi
					khong the sua. 
				*/
				dsmb.DHsuaMB(x2+8, y1+3 , X2-8, Y2-2);
				break;
			case 4:
				xoaKhung(X1+48, Y1+1, X2-2, Y2-2);
				/*
					MayBay co ChuyenBay CON_VE hoac HET_VE
					thi khong the xoa.
					
					MayBay co ChuyenBay da PUBLIC thi
					khong the xoa. 
				*/
				dsmb.DHxoaMB(x2+8, y1+3 , X2-8, Y2-2);
				break;
			case 5:
				SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_TEXT_DEFAULT);
				system("cls");
				QLMB_ThongKe(X1+10, Y1-8 , X1+100, Y1+19);
				SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_TEXT_DEFAULT);
				system("cls");
				return;
			case 0:
				xoaMenuItem(menuPhu_QLMB, 5, x1, y1, x2, y2, MARGIN_X+CD_ITEM+2, MARGIN_Y, CD_ITEM/2+1, CR_ITEM);
				return;
		}
	}
}

void QLCB_suaCB(short x1, short y1, short x2, short y2){
	/*
		Khong the sua CB da HOAN_TAT hoac
		da bi HUY.
		Chi Hieu Chinh duoc Ngay/Gio khoi hanh
	*/
	
	SetBGColor(COLOR_BG_DEFAULT);
	SetColor(COLOR_TEXT_DEFAULT);
	veKhung(x1, y1, x2, y2);
	gotoxy(x1+8, y1+2);
	SetColor(COLOR_HIGHLIGHT_TEXT);
	wcout<<"Ma CB:";
	
	char maCB[MAX_MA_CB];
	ChuyenBay* cb;
	short x[2] = {x1+4, x1+23};
	short y[2] = {y1+7, y1+7};
	short CD = 15;
	short CR = 3;
	
	char menu[2][15] = {"Xoa Het",
						"Xem MB"};
		
	while(true){
		SetBGColor(COLOR_BG_ITEM);
		SetColor(COLOR_TEXT_ITEM);
		veKhungItem(x[0], y[0], x[0]+CD, y[0]+CR);
		gotoxy(x[0]+(CD/3), y[0]+1); wcout<<menu[0];
		veKhungItem(x[1], y[1], x[1]+CD, y[1]+CR);
		gotoxy(x[1]+(CD/3), y[1]+1); wcout<<menu[1];
		ShowCur(true);
		int check;
		do{
			gotoxy(x1+15, y1+2);
			SetBGColor(COLOR_BG_DEFAULT);
			SetColor(COLOR_TEXT_DEFAULT);
			if(nhapMa(maCB, MAX_MA_CB)==ESC){
				return;
			}
			check = dsmb.timCBdeSua_ALL(maCB, cb);
			if(check!=10){
				gotoxy(x1+10, y1+4);
				SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_WARRING);
			}
			if(check==HOAN_TAT){
				wcout<<"CHUYEN BAY DA HOAN TAT!   ";
			} else if(check==HUY){
				wcout<<"CHUYEN BAY DA BI HUY!     ";
			} else if(check==-1){
				wcout<<"KHONG TIM THAY CHUYEN BAY!";
			}
			if(check!=10){
				gotoxy(x1+15, y1+2);
				SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_BG_DEFAULT);
				wcout<<maCB;
			}		
		} while(check!=10);
		gotoxy(x1+10, y1+4);
		SetBGColor(COLOR_BG_DEFAULT);
		SetColor(COLOR_BG_DEFAULT);
		wcout<<"                           ";
		ShowCur(false);
		int selection = 2;
		SetBGColor(COLOR_BG_ITEM_SELECTED);
		SetColor(COLOR_TEXT_ITEM_SELECTED);
		veKhungItem(x[selection-1], y[selection-1], x[selection-1]+CD, y[selection-1]+CR);
		gotoxy(x[selection-1]+(CD/3), y[selection-1]+1); wcout<<menu[selection-1];
	
		char c=0;
		while(c!=ESC && c!=ENTER){
			c = getch();
			if(c<0)
				c = getch();
			if(c==RIGHT || c==LEFT){
				SetBGColor(COLOR_BG_ITEM);
				SetColor(COLOR_TEXT_ITEM);
				veKhungItem(x[selection-1], y[selection-1], x[selection-1]+CD, y[selection-1]+CR);
				gotoxy(x[selection-1]+(CD/3), y[selection-1]+1); wcout<<menu[selection-1];
			}
			switch(c){
				case RIGHT:
					selection--;
					if(selection == 0)
						selection = 2;
					SetBGColor(COLOR_BG_ITEM_SELECTED);
					SetColor(COLOR_TEXT_ITEM_SELECTED);
					veKhungItem(x[selection-1], y[selection-1], x[selection-1]+CD, y[selection-1]+CR);
					gotoxy(x[selection-1]+(CD/3), y[selection-1]+1); wcout<<menu[selection-1];
					break;
				case LEFT:
					selection++;
					if(selection == 3)
						selection = 1;
					SetBGColor(COLOR_BG_ITEM_SELECTED);
					SetColor(COLOR_TEXT_ITEM_SELECTED);
					veKhungItem(x[selection-1], y[selection-1], x[selection-1]+CD, y[selection-1]+CR);
					gotoxy(x[selection-1]+(CD/3), y[selection-1]+1); wcout<<menu[selection-1];
					break;
				case ESC:
					return;
				case ENTER:
					break;
				}
			}
		switch(selection){
			case 1:
				break;
			case 2:
				xoaKhung(x1, y1, x2, y2);
				cb->DHhieuchinhNgKhoiHanh(x1, y1-3, x2, y2+3);
				ShowCur(false);
				xoaKhung(x1, y1-3, x2, y2+3);
				return;
		}
		gotoxy(x1+15, y1+2);
		SetBGColor(COLOR_BG_DEFAULT);
		SetColor(COLOR_BG_DEFAULT);
		wcout<<maCB;
	}
}

void QLCB_xoaCB(short x1, short y1, short x2, short y2){
	
	/*
		co the xoa CB: 
			1. Da HOAN_TAT
			2. Da HUY
			3. Da PUBLIC nhung chua ban dc ve nao.
	*/
	
	SetBGColor(COLOR_BG_DEFAULT);
	SetColor(COLOR_TEXT_DEFAULT);
	veKhung(x1, y1, x2, y2);
	gotoxy(x1+8, y1+2);
	SetColor(COLOR_HIGHLIGHT_TEXT);
	wcout<<"Ma CB:";
	
	char maCB[MAX_MA_CB];
	short x[2] = {x1+4, x1+23};
	short y[2] = {y1+7, y1+7};
	short CD = 15;
	short CR = 3;
	char menu[2][15] = {"Xoa het",
						"Xoa CB"}; 
	
	while(true){
		SetBGColor(COLOR_BG_ITEM);
		SetColor(COLOR_TEXT_ITEM);
		veKhungItem(x[0], y[0], x[0]+CD, y[0]+CR);
		gotoxy(x[0]+(CD/3), y[0]+1); wcout<<menu[0];
		veKhungItem(x[1], y[1], x[1]+CD, y[1]+CR);
		gotoxy(x[1]+(CD/3), y[1]+1); wcout<<menu[1];
		ShowCur(true);
		int check;
		do{
			gotoxy(x1+15, y1+2);
			SetBGColor(COLOR_BG_DEFAULT);
			SetColor(COLOR_TEXT_DEFAULT);
			if(nhapMa(maCB, MAX_MA_CB)==ESC){
				return;
			}
			check = dsmb.xoaCB_ALL(maCB);
			if(check==-1){
				gotoxy(x1+5, y1+4);
				SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_WARRING);
				wcout<<"CB KHONG TON TAI HOAC KHONG THE XOA";
				gotoxy(x1+15, y1+2);
				SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_BG_DEFAULT);
				wcout<<maCB;
			}
		} while(check==-1);
		gotoxy(x1+5, y1+4);
		SetBGColor(COLOR_BG_DEFAULT);
		SetColor(COLOR_WARRING);
		wcout<<"TIM THAY CB! XOA VINH VIEN CB!      ";
		ShowCur(false);
		int selection = 2;
		SetBGColor(COLOR_BG_ITEM_SELECTED);
		SetColor(COLOR_TEXT_ITEM_SELECTED);
		veKhungItem(x[selection-1], y[selection-1], x[selection-1]+CD, y[selection-1]+CR);
		gotoxy(x[selection-1]+(CD/3), y[selection-1]+1); wcout<<menu[selection-1];
	
		char c=0;
		while(c!=ESC && c!=ENTER){
		c = getch();
		if(c<0)
			c = getch();
		if(c==RIGHT || c==LEFT){
			SetBGColor(COLOR_BG_ITEM);
			SetColor(COLOR_TEXT_ITEM);
			veKhungItem(x[selection-1], y[selection-1], x[selection-1]+CD, y[selection-1]+CR);
			gotoxy(x[selection-1]+(CD/3), y[selection-1]+1); wcout<<menu[selection-1];
		}
		switch(c){
			case RIGHT:
				selection--;
				if(selection == 0)
					selection = 2;
				SetBGColor(COLOR_BG_ITEM_SELECTED);
				SetColor(COLOR_TEXT_ITEM_SELECTED);
				veKhungItem(x[selection-1], y[selection-1], x[selection-1]+CD, y[selection-1]+CR);
				gotoxy(x[selection-1]+(CD/3), y[selection-1]+1); wcout<<menu[selection-1];
				break;
			case LEFT:
				selection++;
				if(selection == 3)
					selection = 1;
				SetBGColor(COLOR_BG_ITEM_SELECTED);
				SetColor(COLOR_TEXT_ITEM_SELECTED);
				veKhungItem(x[selection-1], y[selection-1], x[selection-1]+CD, y[selection-1]+CR);
				gotoxy(x[selection-1]+(CD/3), y[selection-1]+1); wcout<<menu[selection-1];
				break;
			case ESC:
				return;
			case ENTER:
				break;
			}
		}
		switch(selection){
			case 1:
				break;
			case 2:
				xoaKhung(x1, y1, x2, y2);
				dsmb.getMayBay(check)->deleteTheoMaCB(maCB); 
				ShowCur(false);
				xoaKhung(x1, y1-3, x2, y2+3);
				return;
		}
		gotoxy(x1+15, y1+2);
		SetBGColor(COLOR_BG_DEFAULT);
		SetColor(COLOR_BG_DEFAULT);
		wcout<<maCB;
		gotoxy(x1+5, y1+4);
		SetBGColor(COLOR_BG_DEFAULT);
		SetColor(COLOR_BG_DEFAULT);
		wcout<<"CB KHONG TON TAI HOAC KHONG THE XOA";
	}
}

void QLCB_huyCB(short x1, short y1, short x2, short y2){
/*
	HUY ChuyenBay CON_VE va HET_VE
*/

	SetBGColor(COLOR_BG_DEFAULT);
	SetColor(COLOR_TEXT_DEFAULT);
	veKhung(x1, y1, x2, y2);
	gotoxy(x1+8, y1+2);
	SetColor(COLOR_HIGHLIGHT_TEXT);
	wcout<<"Ma CB:";
	
	char maCB[MAX_MA_CB];
	short x[2] = {x1+4, x1+23};
	short y[2] = {y1+7, y1+7};
	short CD = 15;
	short CR = 3;
	char menu[2][15] = {"Xoa het",
						"Huy CB"}; 
	
	while(true){
		SetBGColor(COLOR_BG_ITEM);
		SetColor(COLOR_TEXT_ITEM);
		veKhungItem(x[0], y[0], x[0]+CD, y[0]+CR);
		gotoxy(x[0]+(CD/3), y[0]+1); wcout<<menu[0];
		veKhungItem(x[1], y[1], x[1]+CD, y[1]+CR);
		gotoxy(x[1]+(CD/3), y[1]+1); wcout<<menu[1];
		ShowCur(true);
		int check;
		ChuyenBay* cb = NULL;
		do{
			gotoxy(x1+15, y1+2);
			SetBGColor(COLOR_BG_DEFAULT);
			SetColor(COLOR_TEXT_DEFAULT);
			if(nhapMa(maCB, MAX_MA_CB)==ESC){
				return;
			}
			check = dsmb.huyCB_ALL(maCB, cb);
			if(!check){
				gotoxy(x1+5, y1+4);
				SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_WARRING);
				wcout<<"CB KHONG TON TAI HOAC KHONG THE HUY";
				gotoxy(x1+15, y1+2);
				SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_BG_DEFAULT);
				wcout<<maCB;
			}
		} while(!check);
		gotoxy(x1+5, y1+4);
		SetBGColor(COLOR_BG_DEFAULT);
		SetColor(COLOR_WARRING);
		wcout<<"HUY CB SE ANH HUONG TOI H.KHACH     ";
		ShowCur(false);
		int selection = 2;
		SetBGColor(COLOR_BG_ITEM_SELECTED);
		SetColor(COLOR_TEXT_ITEM_SELECTED);
		veKhungItem(x[selection-1], y[selection-1], x[selection-1]+CD, y[selection-1]+CR);
		gotoxy(x[selection-1]+(CD/3), y[selection-1]+1); wcout<<menu[selection-1];
	
		char c=0;
		while(c!=ESC && c!=ENTER){
		c = getch();
		if(c<0)
			c = getch();
		if(c==RIGHT || c==LEFT){
			SetBGColor(COLOR_BG_ITEM);
			SetColor(COLOR_TEXT_ITEM);
			veKhungItem(x[selection-1], y[selection-1], x[selection-1]+CD, y[selection-1]+CR);
			gotoxy(x[selection-1]+(CD/3), y[selection-1]+1); wcout<<menu[selection-1];
		}
		switch(c){
			case RIGHT:
				selection--;
				if(selection == 0)
					selection = 2;
				SetBGColor(COLOR_BG_ITEM_SELECTED);
				SetColor(COLOR_TEXT_ITEM_SELECTED);
				veKhungItem(x[selection-1], y[selection-1], x[selection-1]+CD, y[selection-1]+CR);
				gotoxy(x[selection-1]+(CD/3), y[selection-1]+1); wcout<<menu[selection-1];
				break;
			case LEFT:
				selection++;
				if(selection == 3)
					selection = 1;
				SetBGColor(COLOR_BG_ITEM_SELECTED);
				SetColor(COLOR_TEXT_ITEM_SELECTED);
				veKhungItem(x[selection-1], y[selection-1], x[selection-1]+CD, y[selection-1]+CR);
				gotoxy(x[selection-1]+(CD/3), y[selection-1]+1); wcout<<menu[selection-1];
				break;
			case ESC:
				return;
			case ENTER:
				break;
			}
		}
		switch(selection){
			case 1:
				break;
			case 2:
				xoaKhung(x1, y1, x2, y2);
				if(cb!=NULL)
					cb->huyChuyen();
				ShowCur(false);
				xoaKhung(x1, y1-3, x2, y2+3);
				return;
		}
		gotoxy(x1+15, y1+2);
		SetBGColor(COLOR_BG_DEFAULT);
		SetColor(COLOR_BG_DEFAULT);
		wcout<<maCB;
		gotoxy(x1+5, y1+4);
		SetBGColor(COLOR_BG_DEFAULT);
		SetColor(COLOR_BG_DEFAULT);
		wcout<<"HUY CB SE ANH HUONG TOI H.KHACH     ";
	}
}

void QLCB_xemCB(short x1, short y1, short x2, short y2){

	// ve bang
	float sale[5] = {0.1, 0.2, 0.25, 0.25, 0.1};
	SetBGColor(COLOR_BG_DEFAULT);
	SetColor(COLOR_TEXT_DEFAULT);
	veLable(sale, 5, X1+8, Y1+1, 70);
	gotoxy(X1+10, Y1+2);
	wcout<<"STT";
	gotoxy(X1+16, Y1+2);
	wcout<<"MA CHUYEN BAY";
	gotoxy(X1+33, Y1+2);
	wcout<<"SAN BAY DEN";
	gotoxy(X1+49, Y1+2);
	wcout<<"NG KHOI HANH";
	gotoxy(X1+64, Y1+2);
	wcout<<"T.THAI";
	gotoxy(X1+71, Y1+2);
	wcout<<"S.HIEU";

	SetBGColor(COLOR_BG_ITEM_SELECTED);
	gotoxy(X1+88, Y1+6);
	wcout<<"  ";
	SetBGColor(COLOR_BG_ITEM);
	gotoxy(X1+88, Y1+8);
	wcout<<"  ";
	SetBGColor(COLOR_WARRING);
	gotoxy(X1+88, Y1+10);
	wcout<<"  ";
	
	SetBGColor(COLOR_BG_DEFAULT);
	gotoxy(X1+94, Y1+6);
	wcout<<"HET VE";
	gotoxy(X1+94, Y1+8);
	wcout<<"HOAN TAT";
	gotoxy(X1+94, Y1+10);
	wcout<<"HUY";
	SetColor(COLOR_HIGHLIGHT_TEXT);
	gotoxy(X1+88, Y1+12);
	wcout<<"X ";
	SetColor(COLOR_TEXT_DEFAULT);
	gotoxy(X1+94, Y1+12);
	wcout<<"VE DA BAN";
	SetBGColor(COLOR_BG_DEFAULT);
	
	short x_bang = X1+8;
	short y_bang = Y1+4;
	int stt = 1;
	for(int i=0; i<dsmb.getSize(); i++){
		dsmb.getMayBay(i)->DHshowCB_ALL(x_bang, y_bang, stt);
	}
	for(int i=x_bang+1; i<x_bang+70; i++){
		gotoxy(i, y_bang-1);
		wcout<<TB_LINE;
	}
	gotoxy(x_bang, y_bang-1);
	wcout<<BL_LINE;
	gotoxy(x_bang+70, y_bang-1);
	wcout<<BR_LINE;

	gotoxy(x_bang+7, y_bang-1);
	wcout<<BWB_LINE;
	gotoxy(x_bang+21, y_bang-1);
	wcout<<BWB_LINE;
	gotoxy(x_bang+38, y_bang-1);
	wcout<<BWB_LINE;
	gotoxy(x_bang+38, y_bang-1);
	wcout<<BWB_LINE;
	gotoxy(x_bang+55, y_bang-1);
	wcout<<BWB_LINE;
	gotoxy(x_bang+62, y_bang-1);
	wcout<<BWB_LINE;
	char c;
	while(c!=ESC){
		c = getch();
	}
}

void QLCB_IntheoNgay_InCB(Date &date){
	
	float sale[4] = {0.1, 0.3, 0.3, 0.18};
	SetBGColor(COLOR_BG_DEFAULT);
	SetColor(COLOR_TEXT_DEFAULT);
	veLable(sale, 4, X1+8, Y1, 70);
	gotoxy(X1+11, Y1+1);
	wcout<<"STT";
	gotoxy(X1+20, Y1+1);
	wcout<<"MA CHUYEN BAY";
	gotoxy(X1+42, Y1+1);
	wcout<<"SAN BAY DEN";
	gotoxy(X1+59, Y1+1);
	wcout<<"GIO K.HANH";
	gotoxy(X1+71, Y1+1);
	wcout<<"V.TRONG";
	
	short x_bang = X1+8;
	short y_bang = Y1+3;
	int stt = 1;
	
	SetBGColor(COLOR_BG_DEFAULT);
	SetColor(COLOR_TEXT_DEFAULT);
	for(int i=0; i<dsmb.getSize(); i++){
		dsmb.getMayBay(i)->inCBtheoDatevsConVe(date, x_bang, y_bang, stt);
	}
	
	for(int i=x_bang+1; i<x_bang+70; i++){
		gotoxy(i, y_bang-1);
		wcout<<TB_LINE;
	}
	
	gotoxy(x_bang, y_bang-1);
	wcout<<BL_LINE;
	gotoxy(x_bang+70, y_bang-1);
	wcout<<BR_LINE;

	gotoxy(x_bang+7, y_bang-1);
	wcout<<BWB_LINE;
	gotoxy(x_bang+28, y_bang-1);
	wcout<<BWB_LINE;
	gotoxy(x_bang+49, y_bang-1);
	wcout<<BWB_LINE;
	gotoxy(x_bang+61, y_bang-1);
	wcout<<BWB_LINE;
	char c;
	while(c!=ESC){
		c = getch();
	}
}

void QLCB_IntheoNgay(short x1, short y1, short x2, short y2){
	
	char ngay[3], thang[3], nam[5];
	short x[2] = {X1+26, X1+45};
	short y[2] = {Y1+5, Y1+5};
	short CD = 15;
	short CR = 3;
	char menu[2][15] = {"Xoa het",
						"Xem CB"};
	int check;
						
	while(true){
		SetBGColor(COLOR_BG_DEFAULT);
		SetColor(COLOR_TEXT_DEFAULT);
		veKhung(X1+23, Y1, X1+63, Y1+9);
		gotoxy(X1+25, Y1+2);
		SetColor(COLOR_HIGHLIGHT_TEXT);
		wcout<<"Ng Khoi Hanh: ";
		SetBGColor(COLOR_BG_ITEM);
		SetColor(COLOR_TEXT_ITEM);
		veKhungItem(x[0], y[0], x[0]+CD, y[0]+CR);
		gotoxy(x[0]+(CD/3), y[0]+1); wcout<<menu[0];
		veKhungItem(x[1], y[1], x[1]+CD, y[1]+CR);
		gotoxy(x[1]+(CD/3), y[1]+1); wcout<<menu[1];
		
		time_t  theTime = time(NULL);
		struct tm *aTime = localtime(&theTime);
		int cur_nam = aTime->tm_year+1900;
		int cur_thang = aTime->tm_mon+1;
		int cur_ngay = aTime->tm_mday;
		ShowCur(true);
				
		SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_TEXT_DEFAULT);
				gotoxy(X1+43, Y1+2);
				wcout<<"/";
				gotoxy(X1+46, Y1+2);
				wcout<<"/";
				gotoxy(X1+50, Y1+2);
				wcout<<"(YYYY/MM/DD)";

			do{
				
				gotoxy(X1+39, Y1+2);
				fflush(stdin);
				if(nhapSo(nam, 5)==ESC)
					return;
				check = checkNam(atoi(nam), cur_nam);
				if(!check){
					gotoxy(X1+30, Y1+3);
					SetColor(COLOR_WARRING);
					wcout<<"NAM PHAI >= "<<cur_nam<<" VA <= "<<MAX_NAM;
					gotoxy(X1+39, Y1+2);
					SetColor(COLOR_BG_DEFAULT);
					wcout<<nam;
				}
			} while(!check);
			gotoxy(X1+30, Y1+3);
			SetColor(COLOR_BG_DEFAULT);
			wcout<<"NAM PHAI >= "<<cur_nam<<" VA <= "<<MAX_NAM;

			do{	
				SetColor(COLOR_TEXT_DEFAULT);
				gotoxy(X1+44, Y1+2);
				fflush(stdin);
				if(nhapSo(thang, 3)==ESC)
					return;
				check = checkThang(atoi(nam), atoi(thang), cur_nam, cur_thang);
				if(check == -1){
					gotoxy(X1+30, Y1+3);
					SetColor(COLOR_BG_DEFAULT);
					wcout<<"                                ";
					gotoxy(X1+30, Y1+3);
					SetColor(COLOR_WARRING);
					wcout<<"THANG PHAI >= THANG "<<cur_thang<<" NAM "<<cur_nam;
					gotoxy(X1+44, Y1+2);
					SetColor(COLOR_BG_DEFAULT);
					wcout<<thang;
				} else if(check == 0){
					gotoxy(X1+30, Y1+3);
					SetColor(COLOR_BG_DEFAULT);
					wcout<<"                                ";
					gotoxy(X1+35, Y1+3);
					SetColor(COLOR_WARRING);
					wcout<<"NAM CO 12 THANG";
					gotoxy(X1+44, Y1+2);
					SetColor(COLOR_BG_DEFAULT);
					wcout<<thang;
				}
			} while(check!=1);
	
			gotoxy(X1+44, Y1+2);
			SetColor(COLOR_TEXT_DEFAULT);
			wcout<<setw(2)<<setfill((wchar_t)'0')<<right<<thang; 
			
			gotoxy(X1+30, Y1+3);
			SetColor(COLOR_BG_DEFAULT);
			wcout<<"                                ";
		
			do{
				SetColor(COLOR_TEXT_DEFAULT);
				gotoxy(X1+47, Y1+2);
				fflush(stdin);
				if(nhapSo(ngay, 3)==ESC)
					return;
				check = checkNgay(atoi(nam), atoi(thang), atoi(ngay), cur_nam, cur_thang, cur_ngay);
				if(check==0){
					gotoxy(X1+30, Y1+3);
					SetColor(COLOR_BG_DEFAULT);
					wcout<<"                               ";
					gotoxy(X1+30, Y1+3);
					SetColor(COLOR_WARRING);
					wcout<<"NGAY PHAI > NGAY "<<cur_ngay<<" THANG "<<cur_thang;
					gotoxy(X1+47, Y1+2);
					SetColor(COLOR_BG_DEFAULT);
					wcout<<ngay;
				} else if(check>=28){
					gotoxy(X1+30, Y1+3);
					SetColor(COLOR_BG_DEFAULT);
					wcout<<"                               ";
					gotoxy(X1+35, Y1+3);
					SetColor(COLOR_WARRING);
					wcout<<"THANG "<<thang<<" CO "<<check<<" NGAY ";
					gotoxy(X1+47, Y1+2);
					SetColor(COLOR_BG_DEFAULT);
					wcout<<ngay;
				}
			} while(check!=1);
		
			gotoxy(X1+47, Y1+2);
			SetColor(COLOR_TEXT_DEFAULT);
			wcout<<setw(2)<<setfill((wchar_t)'0')<<right<<ngay; 
			
			gotoxy(X1+30, Y1+3);
			SetColor(COLOR_BG_DEFAULT);
			wcout<<"                               ";
		
		ShowCur(false);
		int selection = 2;
		SetBGColor(COLOR_BG_ITEM_SELECTED);
		SetColor(COLOR_TEXT_ITEM_SELECTED);
		veKhungItem(x[selection-1], y[selection-1], x[selection-1]+CD, y[selection-1]+CR);
		gotoxy(x[selection-1]+(CD/3), y[selection-1]+1); wcout<<menu[selection-1];
			char c=0;
		while(c!=ESC && c!=ENTER){
			c = getch();
			if(c<0)
				c = getch();
			if(c==RIGHT || c==LEFT){
				SetBGColor(COLOR_BG_ITEM);
				SetColor(COLOR_TEXT_ITEM);
				veKhungItem(x[selection-1], y[selection-1], x[selection-1]+CD, y[selection-1]+CR);
				gotoxy(x[selection-1]+(CD/3), y[selection-1]+1); wcout<<menu[selection-1];
			}
			switch(c){
				case RIGHT:
					selection--;
					if(selection == 0)
						selection = 2;
					SetBGColor(COLOR_BG_ITEM_SELECTED);
					SetColor(COLOR_TEXT_ITEM_SELECTED);
					veKhungItem(x[selection-1], y[selection-1], x[selection-1]+CD, y[selection-1]+CR);
					gotoxy(x[selection-1]+(CD/3), y[selection-1]+1); wcout<<menu[selection-1];
					break;
				case LEFT:
					selection++;
					if(selection == 3)
						selection = 1;
					SetBGColor(COLOR_BG_ITEM_SELECTED);
					SetColor(COLOR_TEXT_ITEM_SELECTED);
					veKhungItem(x[selection-1], y[selection-1], x[selection-1]+CD, y[selection-1]+CR);
					gotoxy(x[selection-1]+(CD/3), y[selection-1]+1); wcout<<menu[selection-1];
					break;
				case ESC:
					return;
				case ENTER:
					break;
			}
		}
		switch(selection){
			case 1:
				break;
			case 2:
				SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_TEXT_DEFAULT);
				system("cls");
				Date date(0, 0, atoi(ngay), atoi(thang), atoi(nam));
				QLCB_IntheoNgay_InCB(date);
				SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_TEXT_DEFAULT);
				system("cls");
				break;
		}
		SetBGColor(COLOR_BG_DEFAULT);
		SetColor(COLOR_BG_DEFAULT);
		gotoxy(X1+39, Y1+2);
		wcout<<"    /  /  ";
	}
}

void case_QLCB(short x1, short y1, short x2, short y2){
	int s = 1;
	MayBay* mb = NULL;
	while(true){
		inLable(X1+48, Y1+1);
		s = veMenu(menuPhu_QLCB, 6, x1-10, y1, x2, y2, MARGIN_X+CD_ITEM+2, MARGIN_Y, CD_ITEM/2+1, CR_ITEM, s);
		switch(s){
			case 1:
				SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_TEXT_DEFAULT);
				system("cls");
				QLCB_xemCB(X1+10, Y1-8 , X1+100, Y1+19);
				SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_TEXT_DEFAULT);
				system("cls");
				return;
			case 2:
				xoaKhung(X1+48, Y1+1, X2-2, Y2-2);
				dsmb.DHgetMB(x2+8, y1+3 , X2-8, Y2-2);
				break;
			case 3:
				xoaKhung(X1+48, Y1+1, X2-2, Y2-2);
				QLCB_suaCB(x2+12, y1+8 , X2-14, Y2-8);
				ShowCur(false);
				xoaKhung(x2+12, y1+8 , X2-14, Y2-8);
				break;
			case 4:
				xoaKhung(X1+48, Y1+1, X2-2, Y2-2);
				QLCB_xoaCB(x2+12, y1+8 , X2-14, Y2-8);
				ShowCur(false);
				xoaKhung(x2+12, y1+8 , X2-14, Y2-8);
				break;
			case 5:
				xoaKhung(X1+48, Y1+1, X2-2, Y2-2);
				QLCB_huyCB(x2+12, y1+8 , X2-14, Y2-8);
				ShowCur(false);
				xoaKhung(x2+12, y1+8 , X2-14, Y2-8);
				break;
			case 6:
				SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_TEXT_DEFAULT);
				system("cls");
				QLCB_IntheoNgay(x1, y1, x2, y1);
				ShowCur(false);
				SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_TEXT_DEFAULT);
				system("cls");
				return;
			case 0:
				xoaMenuItem(menuPhu_QLMB, 6, x1, y1, x2, y2, MARGIN_X+CD_ITEM+2, MARGIN_Y, CD_ITEM/2+1, CR_ITEM);
				return;
		}
	}
}

int HK_NhapCMND(short x1, short y1, short x2, short y2, char* CMND){
	SetBGColor(COLOR_BG_DEFAULT);
	SetColor(COLOR_TEXT_DEFAULT);
	veKhung(x1, y1, x2, y2);
	
	SetColor(COLOR_HIGHLIGHT_TEXT);
	gotoxy(x1+6, y1+2);
	wcout<<"CMND: ";
	
	short x[2] = {x1+7, x1+26};
	short y[2] = {y1+5, y1+5};
	short CD = 15;
	short CR = 3;
	
	char menu[2][15] = {"Xoa Het",
						"Sua TT"};
	
	
	int check;
	while(true){
		SetBGColor(COLOR_BG_ITEM);
		SetColor(COLOR_TEXT_ITEM);
		veKhungItem(x[0], y[0], x[0]+CD, y[0]+CR);
		gotoxy(x[0]+(CD/3), y[0]+1); wcout<<menu[0];
		veKhungItem(x[1], y[1], x[1]+CD, y[1]+CR);
		gotoxy(x[1]+(CD/3), y[1]+1); wcout<<menu[1];
		do{
			ShowCur(true);
			gotoxy(x1+12, y1+2);
			SetBGColor(COLOR_BG_DEFAULT);
			SetColor(COLOR_TEXT_DEFAULT);
			fflush(stdin);
			if(nhapSo(CMND, MAX_CMND)==ESC){
				return ESC;
			}
			check = dsHanhKhach.isDuplicate(CMND);
			if(!check){
				gotoxy(x1+12, y1+3);
				SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_WARRING);
				wcout<<"HANH KHACH CHUA TON TAI!";
				gotoxy(x1+12, y1+2);
				SetColor(COLOR_BG_DEFAULT);
				wcout<<CMND;	
			}
		} while(!check);
		gotoxy(x1+12, y1+3);
		SetBGColor(COLOR_BG_DEFAULT);
		SetColor(COLOR_BG_DEFAULT);
		wcout<<"HANH KHACH CHUA TON TAI!";
	
		ShowCur(false);
		int selection = 2;
		SetBGColor(COLOR_BG_ITEM_SELECTED);
		SetColor(COLOR_TEXT_ITEM_SELECTED);
		veKhungItem(x[selection-1], y[selection-1], x[selection-1]+CD, y[selection-1]+CR);
		gotoxy(x[selection-1]+(CD/3), y[selection-1]+1); wcout<<menu[selection-1];
		
		char c;
		while(c!=ESC && c!=ENTER){
			c = getch();
			if(c<0)
				c = getch();
			if(c==RIGHT || c==LEFT){
				SetBGColor(COLOR_BG_ITEM);
				SetColor(COLOR_TEXT_ITEM);
				veKhungItem(x[selection-1], y[selection-1], x[selection-1]+CD, y[selection-1]+CR);
				gotoxy(x[selection-1]+(CD/3), y[selection-1]+1); wcout<<menu[selection-1];
			}
			switch(c){
				case RIGHT:
					selection--;
					if(selection == 0)
						selection = 2;
					SetBGColor(COLOR_BG_ITEM_SELECTED);
					SetColor(COLOR_TEXT_ITEM_SELECTED);
					veKhungItem(x[selection-1], y[selection-1], x[selection-1]+CD, y[selection-1]+CR);
					gotoxy(x[selection-1]+(CD/3), y[selection-1]+1); wcout<<menu[selection-1];
					break;
				case LEFT:
					selection++;
					if(selection == 3)
						selection = 1;
					SetBGColor(COLOR_BG_ITEM_SELECTED);
					SetColor(COLOR_TEXT_ITEM_SELECTED);
					veKhungItem(x[selection-1], y[selection-1], x[selection-1]+CD, y[selection-1]+CR);
					gotoxy(x[selection-1]+(CD/3), y[selection-1]+1); wcout<<menu[selection-1];
					break;
				case ESC:
					return ESC;
				case ENTER:
					break;
			}
		}
		switch(selection){
			case 1:
				break;
			case 2:
				return 1;
		}
		gotoxy(x1+12, y1+2);
		SetBGColor(COLOR_BG_DEFAULT);
		SetColor(COLOR_BG_DEFAULT);
		wcout<<CMND;
	}
			
}

void QLHK_xemHK(short x1, short y1, short x2, short y2){
	// ve bang
	float sale[3] = {0.1, 0.3, 0.4};
	SetBGColor(COLOR_BG_DEFAULT);
	SetColor(COLOR_TEXT_DEFAULT);
	veLable(sale, 3, X1+8, Y1+1, 70);
	gotoxy(X1+10, Y1+2);
	wcout<<"STT";
	gotoxy(X1+24, Y1+2);
	wcout<<"CMND";
	gotoxy(X1+46, Y1+2);
	wcout<<"HO VA TEN";
	gotoxy(X1+67, Y1+2);
	wcout<<"GIOI TINH";


	
	short x_bang = X1+8;
	short y_bang = Y1+4;
	int stt = 1;
	dsHanhKhach.DHxuatHK_ALL(x_bang, y_bang, stt);
	for(int i=x_bang+1; i<x_bang+70; i++){
		gotoxy(i, y_bang-1);
		wcout<<TB_LINE;
	}
	gotoxy(x_bang, y_bang-1);
	wcout<<BL_LINE;
	gotoxy(x_bang+70, y_bang-1);
	wcout<<BR_LINE;
	
	gotoxy(x_bang+7, y_bang-1);
	wcout<<BWB_LINE;
	gotoxy(x_bang+28, y_bang-1);
	wcout<<BWB_LINE;
	gotoxy(x_bang+56, y_bang-1);
	wcout<<BWB_LINE;

	char c;
	while(c!=ESC){
		c = getch();
	}
}

void QLHK_xoaHK(short x1, short y1, short x2, short y2){
	SetBGColor(COLOR_BG_DEFAULT);
	SetColor(COLOR_TEXT_DEFAULT);
	veKhung(x1, y1, x2, y2);
	gotoxy(x1+8, y1+2);
	SetColor(COLOR_HIGHLIGHT_TEXT);
	wcout<<"CMND:";
	
	char CMND[MAX_CMND];
	short x[2] = {x1+4, x1+23};
	short y[2] = {y1+7, y1+7};
	short CD = 15;
	short CR = 3;
	char menu[2][15] = {"Xoa het",
						"Xoa HK"}; 
	
	while(true){
		SetBGColor(COLOR_BG_ITEM);
		SetColor(COLOR_TEXT_ITEM);
		veKhungItem(x[0], y[0], x[0]+CD, y[0]+CR);
		gotoxy(x[0]+(CD/3), y[0]+1); wcout<<menu[0];
		veKhungItem(x[1], y[1], x[1]+CD, y[1]+CR);
		gotoxy(x[1]+(CD/3), y[1]+1); wcout<<menu[1];
		ShowCur(true);
		int check;
		do{
			gotoxy(x1+15, y1+2);
			SetBGColor(COLOR_BG_DEFAULT);
			SetColor(COLOR_TEXT_DEFAULT);
			if(nhapSo(CMND, MAX_CMND)==ESC){
				return;
			}
			check = dsHanhKhach.isDuplicate(CMND);
			if(!check){
				gotoxy(x1+5, y1+4);
				SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_WARRING);
				wcout<<"     HANH KHACH KHONG TON TAI!   ";
				gotoxy(x1+15, y1+2);
				SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_BG_DEFAULT);
				wcout<<CMND;
			} else{
				check = dsmb.coHanhKhach_ALL(CMND);
				if(check){
					gotoxy(x1+5, y1+4);
					SetBGColor(COLOR_BG_DEFAULT);
					SetColor(COLOR_WARRING);
					wcout<<"   HANH KHACH SAP CO CHUYEN BAY!";
					gotoxy(x1+15, y1+2);
					SetBGColor(COLOR_BG_DEFAULT);
					SetColor(COLOR_BG_DEFAULT);
					wcout<<CMND;
					check = false;
				} else{
					check = true;
				}
			}
		} while(!check);
		gotoxy(x1+5, y1+4);
		SetBGColor(COLOR_BG_DEFAULT);
		SetColor(COLOR_WARRING);
		wcout<<"XOA HANH KHACH SE MAT HET DU LIEU";
		ShowCur(false);
		int selection = 2;
		SetBGColor(COLOR_BG_ITEM_SELECTED);
		SetColor(COLOR_TEXT_ITEM_SELECTED);
		veKhungItem(x[selection-1], y[selection-1], x[selection-1]+CD, y[selection-1]+CR);
		gotoxy(x[selection-1]+(CD/3), y[selection-1]+1); wcout<<menu[selection-1];
	
		char c=0;
		while(c!=ESC && c!=ENTER){
		c = getch();
		if(c<0)
			c = getch();
		if(c==RIGHT || c==LEFT){
			SetBGColor(COLOR_BG_ITEM);
			SetColor(COLOR_TEXT_ITEM);
			veKhungItem(x[selection-1], y[selection-1], x[selection-1]+CD, y[selection-1]+CR);
			gotoxy(x[selection-1]+(CD/3), y[selection-1]+1); wcout<<menu[selection-1];
		}
		switch(c){
			case RIGHT:
				selection--;
				if(selection == 0)
					selection = 2;
				SetBGColor(COLOR_BG_ITEM_SELECTED);
				SetColor(COLOR_TEXT_ITEM_SELECTED);
				veKhungItem(x[selection-1], y[selection-1], x[selection-1]+CD, y[selection-1]+CR);
				gotoxy(x[selection-1]+(CD/3), y[selection-1]+1); wcout<<menu[selection-1];
				break;
			case LEFT:
				selection++;
				if(selection == 3)
					selection = 1;
				SetBGColor(COLOR_BG_ITEM_SELECTED);
				SetColor(COLOR_TEXT_ITEM_SELECTED);
				veKhungItem(x[selection-1], y[selection-1], x[selection-1]+CD, y[selection-1]+CR);
				gotoxy(x[selection-1]+(CD/3), y[selection-1]+1); wcout<<menu[selection-1];
				break;
			case ESC:
				return;
			case ENTER:
				break;
			}
		}	
		switch(selection){
			case 1:
				break;
			case 2:
				dsHanhKhach.xoaHK(CMND);
				break;
		}
		gotoxy(x1+15, y1+2);
		SetBGColor(COLOR_BG_DEFAULT);
		SetColor(COLOR_BG_DEFAULT);
		wcout<<CMND;
		gotoxy(x1+5, y1+4);
		wcout<<"XOA HANH KHACH SE MAT HET DU LIEU";
	}	
}

void QLHK_IntheoMaCB_InHK(ChuyenBay* cb){
	char** dsVe = cb->getDSVe();
	
	SetBGColor(COLOR_BG_DEFAULT);
	SetColor(COLOR_HIGHLIGHT_TEXT);
	gotoxy(X1+20, Y1+1);
	wcout<<"DANH SACH HANH KHACH THUOC CHUYEN BAY ";
	gotoxy(X1+17, Y1+3);
	wcout<<"Ngay Khoi Hanh: ";
	gotoxy(X1+47, Y1+3);
	wcout<<"Noi den: ";
	SetColor(COLOR_TEXT_DEFAULT);
	gotoxy(X1+58, Y1+1);
	wcout<<cb->getMaCB();
	gotoxy(X1+33, Y1+3);
	cb->getNgKhoiHanh()->xuatNgay();
	gotoxy(X1+56, Y1+3);
	wcout<<cb->getSanBayDen();
	
	float sale[4] = {0.1, 0.1, 0.3, 0.4};
	SetBGColor(COLOR_BG_DEFAULT);
	SetColor(COLOR_TEXT_DEFAULT);
	veLable(sale, 4, X1+8, Y1+5, 70);
	gotoxy(X1+11, Y1+6);
	wcout<<"STT";
	gotoxy(X1+17, Y1+6);
	wcout<<"SO VE";
	gotoxy(X1+30, Y1+6);
	wcout<<"SO CMND";
	gotoxy(X1+53, Y1+6);
	wcout<<"HO VA TEN";
	gotoxy(X1+73, Y1+6);
	wcout<<"PHAI";
	
	short x_bang = X1+8;
	short y_bang = Y1+8;
	int stt = 1;
	
	SetBGColor(COLOR_BG_DEFAULT);
	SetColor(COLOR_TEXT_DEFAULT);
	for(int i=0; i<cb->getSoVe(); i++){
		if(strcmpi(dsVe[i], "")!=0){
			HanhKhach* hk = dsHanhKhach.getHK(dsVe[i]);
			hk->DHinHKtheoMaCB(x_bang, y_bang, stt, i);
		}
	}
	
	for(int i=x_bang+1; i<x_bang+70; i++){
		gotoxy(i, y_bang-1);
		wcout<<TB_LINE;
	}
	
	gotoxy(x_bang, y_bang-1);
	wcout<<BL_LINE;
	gotoxy(x_bang+70, y_bang-1);
	wcout<<BR_LINE;

	gotoxy(x_bang+7, y_bang-1);
	wcout<<BWB_LINE;
	gotoxy(x_bang+14, y_bang-1);
	wcout<<BWB_LINE;
	gotoxy(x_bang+35, y_bang-1);
	wcout<<BWB_LINE;
	gotoxy(x_bang+63, y_bang-1);
	wcout<<BWB_LINE;
	char c;
	while(c!=ESC){
		c = getch();
	}
}

void QLHK_IntheoMaCB(short x1, short y1, short x2, short y2){
	SetBGColor(COLOR_BG_DEFAULT);
	SetColor(COLOR_TEXT_DEFAULT);
	veKhung(X1+23, Y1, X1+63, Y1+9);
	gotoxy(X1+28, Y1+2);
	SetColor(COLOR_HIGHLIGHT_TEXT);
	wcout<<"Ma CB: ";
	
	char maCB[MAX_MA_CB];
	short x[2] = {X1+26, X1+45};
	short y[2] = {Y1+5, Y1+5};
	short CD = 15;
	short CR = 3;
	char menu[2][15] = {"Xoa het",
						"Xem HK"}; 
						
	while(true){
		SetBGColor(COLOR_BG_ITEM);
		SetColor(COLOR_TEXT_ITEM);
		veKhungItem(x[0], y[0], x[0]+CD, y[0]+CR);
		gotoxy(x[0]+(CD/3), y[0]+1); wcout<<menu[0];
		veKhungItem(x[1], y[1], x[1]+CD, y[1]+CR);
		gotoxy(x[1]+(CD/3), y[1]+1); wcout<<menu[1];
		ChuyenBay* cb = NULL;
		do{
			ShowCur(true);
			SetBGColor(COLOR_BG_DEFAULT);
			SetColor(COLOR_TEXT_DEFAULT);
			gotoxy(X1+36, Y1+2);
			if(nhapMa(maCB, MAX_MA_CB)==ESC){
				return;
			}
			cb = dsmb.getCBinDSHK_ALL(maCB);
			if(cb==NULL){
				gotoxy(X1+28, Y1+3);
				SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_WARRING);
				wcout<<"CB KHONG TON TAI HOAC DA HUY";
				SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_BG_DEFAULT);
				gotoxy(X1+36, Y1+2);
				wcout<<maCB;
			}
		} while(!cb);
		
		gotoxy(X1+28, Y1+3);
		SetBGColor(COLOR_BG_DEFAULT);
		SetColor(COLOR_BG_DEFAULT);
		wcout<<"CB KHONG TON TAI HOAC DA HUY";
		
		ShowCur(false);
		int selection = 2;
		SetBGColor(COLOR_BG_ITEM_SELECTED);
		SetColor(COLOR_TEXT_ITEM_SELECTED);
		veKhungItem(x[selection-1], y[selection-1], x[selection-1]+CD, y[selection-1]+CR);
		gotoxy(x[selection-1]+(CD/3), y[selection-1]+1); wcout<<menu[selection-1];
		char c=0;
		while(c!=ESC && c!=ENTER){
			c = getch();
			if(c<0)
				c = getch();
			if(c==RIGHT || c==LEFT){
				SetBGColor(COLOR_BG_ITEM);
				SetColor(COLOR_TEXT_ITEM);
				veKhungItem(x[selection-1], y[selection-1], x[selection-1]+CD, y[selection-1]+CR);
				gotoxy(x[selection-1]+(CD/3), y[selection-1]+1); wcout<<menu[selection-1];
			}
			switch(c){
				case RIGHT:
					selection--;
					if(selection == 0)
						selection = 2;
					SetBGColor(COLOR_BG_ITEM_SELECTED);
					SetColor(COLOR_TEXT_ITEM_SELECTED);
					veKhungItem(x[selection-1], y[selection-1], x[selection-1]+CD, y[selection-1]+CR);
					gotoxy(x[selection-1]+(CD/3), y[selection-1]+1); wcout<<menu[selection-1];
					break;
				case LEFT:
					selection++;
					if(selection == 3)
						selection = 1;
					SetBGColor(COLOR_BG_ITEM_SELECTED);
					SetColor(COLOR_TEXT_ITEM_SELECTED);
					veKhungItem(x[selection-1], y[selection-1], x[selection-1]+CD, y[selection-1]+CR);
					gotoxy(x[selection-1]+(CD/3), y[selection-1]+1); wcout<<menu[selection-1];
					break;
				case ESC:
					return;
				case ENTER:
					break;
			}
		}
		switch(selection){
			case 1:
				break;
			case 2:
				SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_TEXT_DEFAULT);
				system("cls");
				QLHK_IntheoMaCB_InHK(cb);
				return;
		}
		SetBGColor(COLOR_BG_DEFAULT);
		SetColor(COLOR_BG_DEFAULT);
		gotoxy(X1+36, Y1+2);
		wcout<<maCB;
	}
}

void case_HK(short x1, short y1, short x2, short y2){
	int s =1;
	char CMND[MAX_CMND];
	int temp;
	while(true){
		inLable(X1+48, Y1+1);
		s = veMenu(menuPhu_HK, 5, x1, y1, x2, y2, MARGIN_X+CD_ITEM+2, MARGIN_Y, CD_ITEM/2+1, CR_ITEM, s);
		switch(s){
			case 1:
				SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_TEXT_DEFAULT);
				system("cls");
				QLHK_xemHK(X1+10, Y1-8 , X1+100, Y1+19);
				SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_TEXT_DEFAULT);
				system("cls");
				return;
			case 2:
				xoaKhung(X1+48, Y1+1, X2-2, Y2-2);
				dsHanhKhach.DHthemHK(x2+10, y1+5 , X2-10, Y2-4);
				xoaKhung(x2+10, y1+5 , X2-10, Y2-4);
				break;
			case 3:
				xoaKhung(X1+48, Y1+1, X2-2, Y2-2);
				temp = HK_NhapCMND(x2+10, y1+9 , X2-10, Y2-9, CMND);
				xoaKhung(x2+10, y1+9 , X2-10, Y2-9);
				if(temp==ESC)
					break;
				dsHanhKhach.DHsuaHK(x2+10, y1+5 , X2-10, Y2-4, CMND);
				xoaKhung(x2+10, y1+5 , X2-10, Y2-4);
				break;
			case 4:
				xoaKhung(X1+48, Y1+1, X2-2, Y2-2);
				QLHK_xoaHK(x2+12, y1+8 , X2-14, Y2-8);
				ShowCur(false);
				xoaKhung(x2+12, y1+8 , X2-14, Y2-8);
				break;
			case 5:
				SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_TEXT_DEFAULT);
				system("cls");
				QLHK_IntheoMaCB(x1, y1, x2, y1);
				ShowCur(false);
				SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_TEXT_DEFAULT);
				system("cls");
				return;
			case 0:
				xoaMenuItem(menuPhu_HK, 5, x1, y1, x2, y2, MARGIN_X+CD_ITEM+2, MARGIN_Y, CD_ITEM/2+1, CR_ITEM);
				return;
		}
		ShowCur(false);
	}
}

void docDlieuFile(){
	ifstream fin_dsmb("dsmb.dat", ios::binary);
	dsmb.read(fin_dsmb);
	fin_dsmb.close();
	ifstream fin_dshk("dshk.dat", ios::binary);
	dsHanhKhach.read(fin_dshk);
	fin_dshk.close();	
}

void ghiDlieuFile(short x1, short y1, short x2, short y2){
	SetColor(COLOR_TEXT_DEFAULT);
	SetBGColor(COLOR_BG_DEFAULT);
	veKhung(x1, y1, x2, y2);
	gotoxy(x1+4, y1+2);
	SetColor(COLOR_WARRING);
	SetBGColor(COLOR_BG_DEFAULT);
	wcout<<"CHU Y: ";
	gotoxy(x1+6, y1+4);
	SetColor(COLOR_TEXT_DEFAULT);
	wcout<<"Ban co muon ghi de du lieu len File ?";
	
	short x[2] = {x1+7, x1+26};
	short y[2] = {y1+7, y1+7};
	short CD = 15;
	short CR = 3;
	char menu[2][15] = {"Khong",
						"Dong y"}; 
	
	SetBGColor(COLOR_BG_ITEM);
	SetColor(COLOR_TEXT_ITEM);
	veKhungItem(x[0], y[0], x[0]+CD, y[0]+CR);
	gotoxy(x[0]+(CD/3), y[0]+1); wcout<<menu[0];
	
	
	ShowCur(false);
	int selection = 2;
	SetBGColor(COLOR_BG_ITEM_SELECTED);
	SetColor(COLOR_TEXT_ITEM_SELECTED);
	veKhungItem(x[selection-1], y[selection-1], x[selection-1]+CD, y[selection-1]+CR);
	gotoxy(x[selection-1]+(CD/3), y[selection-1]+1); wcout<<menu[selection-1];
	
	char c=0;
	while(c!=ESC && c!=ENTER){
		c = getch();
		if(c<0)
			c = getch();
		if(c==RIGHT || c==LEFT){
			SetBGColor(COLOR_BG_ITEM);
			SetColor(COLOR_TEXT_ITEM);
			veKhungItem(x[selection-1], y[selection-1], x[selection-1]+CD, y[selection-1]+CR);
			gotoxy(x[selection-1]+(CD/3), y[selection-1]+1); wcout<<menu[selection-1];
		}
		switch(c){
			case RIGHT:
				selection--;
				if(selection == 0)
					selection = 2;
				SetBGColor(COLOR_BG_ITEM_SELECTED);
				SetColor(COLOR_TEXT_ITEM_SELECTED);
				veKhungItem(x[selection-1], y[selection-1], x[selection-1]+CD, y[selection-1]+CR);
				gotoxy(x[selection-1]+(CD/3), y[selection-1]+1); wcout<<menu[selection-1];
				break;
			case LEFT:
				selection++;
				if(selection == 3)
					selection = 1;
				SetBGColor(COLOR_BG_ITEM_SELECTED);
				SetColor(COLOR_TEXT_ITEM_SELECTED);
				veKhungItem(x[selection-1], y[selection-1], x[selection-1]+CD, y[selection-1]+CR);
				gotoxy(x[selection-1]+(CD/3), y[selection-1]+1); wcout<<menu[selection-1];
				break;
			case ESC:
				return;
			case ENTER:
				break;
		}	
	}
	switch(selection){
		case 1:
			break;
		case 2:
			ofstream fout_dsmb("dsmb.dat", ios::binary);
			dsmb.write(fout_dsmb);
			fout_dsmb.close();
			ofstream fout_dshk("dshk.dat", ios::binary);
			dsHanhKhach.write(fout_dshk);
			fout_dshk.close();
			SetBGColor(COLOR_BG_DEFAULT);
			SetColor(COLOR_SUCCESS);
			gotoxy(x1+13, y1+5);
			wcout<<"XUAT FILE THANG CONG!";
			char c;
			while(c!=ESC){
				c = getch();
			}
			return;	
	}
		
}

char* DatVe_timSanBay(short x1, short y1, short x2, short y2){
	SetBGColor(COLOR_BG_DEFAULT);
	SetColor(COLOR_TEXT_DEFAULT);
	veKhung(x1+10, y1+8, x2-10, y2-8);
	gotoxy(x1+15, y1+11);
	SetColor(COLOR_HIGHLIGHT_TEXT);
	wcout<<"San Bay Den: ";
	
	
	char* sanBay = new char[MAX_SAN_BAY];
	short x[2] = {x1+17, x1+36};
	short y[2] = {y1+15, y1+15};
	short CD = 15;
	short CR = 3;
	char menu[2][15] = {"Xoa het",
						"Xem CB"}; 
	
	while(true){
		SetBGColor(COLOR_BG_ITEM);
		SetColor(COLOR_TEXT_ITEM);
		veKhungItem(x[0], y[0], x[0]+CD, y[0]+CR);
		gotoxy(x[0]+(CD/3), y[0]+1); wcout<<menu[0];
		veKhungItem(x[1], y[1], x[1]+CD, y[1]+CR);
		gotoxy(x[1]+(CD/3), y[1]+1); wcout<<menu[1];
		
		ShowCur(true);
		
		int check;
		do{
			SetBGColor(COLOR_BG_DEFAULT);
			SetColor(COLOR_TEXT_DEFAULT);
			gotoxy(x1+28, y1+11);
			fflush(stdin);
			if(nhapTen(sanBay, MAX_SAN_BAY)==ESC){
				return NULL;
			}
			check = dsmb.timkiemMBcoSB(sanBay);
			if(!check){
				gotoxy(x1+21, y1+13);
				SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_WARRING);
				wcout<<"KHONG TIM THAY CB THICH HOP!";
				gotoxy(x1+28, y1+11);
				SetColor(COLOR_BG_DEFAULT);
				wcout<<sanBay;
			}
		} while(!check);
		gotoxy(x1+21, y1+13);
		SetBGColor(COLOR_BG_DEFAULT);
		SetColor(COLOR_BG_DEFAULT);
		wcout<<"KHONG TIM THAY CB THICH HOP!";
		
		ShowCur(false);
		int selection = 2;
		SetBGColor(COLOR_BG_ITEM_SELECTED);
		SetColor(COLOR_TEXT_ITEM_SELECTED);
		veKhungItem(x[selection-1], y[selection-1], x[selection-1]+CD, y[selection-1]+CR);
		gotoxy(x[selection-1]+(CD/3), y[selection-1]+1); wcout<<menu[selection-1];
		char c=0;
		while(c!=ESC && c!=ENTER){
			c = getch();
			if(c<0)
				c = getch();
			if(c==RIGHT || c==LEFT){
				SetBGColor(COLOR_BG_ITEM);
				SetColor(COLOR_TEXT_ITEM);
				veKhungItem(x[selection-1], y[selection-1], x[selection-1]+CD, y[selection-1]+CR);
				gotoxy(x[selection-1]+(CD/3), y[selection-1]+1); wcout<<menu[selection-1];
			}
			switch(c){
				case RIGHT:
					selection--;
					if(selection == 0)
						selection = 2;
					SetBGColor(COLOR_BG_ITEM_SELECTED);
					SetColor(COLOR_TEXT_ITEM_SELECTED);
					veKhungItem(x[selection-1], y[selection-1], x[selection-1]+CD, y[selection-1]+CR);
					gotoxy(x[selection-1]+(CD/3), y[selection-1]+1); wcout<<menu[selection-1];
					break;
				case LEFT:
					selection++;
					if(selection == 3)
						selection = 1;
					SetBGColor(COLOR_BG_ITEM_SELECTED);
					SetColor(COLOR_TEXT_ITEM_SELECTED);
					veKhungItem(x[selection-1], y[selection-1], x[selection-1]+CD, y[selection-1]+CR);
					gotoxy(x[selection-1]+(CD/3), y[selection-1]+1); wcout<<menu[selection-1];
					break;
				case ESC:
					return NULL;
				case ENTER:
					break;
			}
		}
		switch(selection){
				case 1:
					break;
				case 2:
					return sanBay;	
				
		}
		gotoxy(x1+28, y1+11);
		SetBGColor(COLOR_BG_DEFAULT);
		SetColor(COLOR_BG_DEFAULT);
		wcout<<sanBay;	
	}
}

ChuyenBay* DatVe_nhapMaCB(char* sanBayDen){
	SetBGColor(COLOR_BG_DEFAULT);
	SetColor(COLOR_TEXT_DEFAULT);
	veKhung(X1+23, Y1, X1+63, Y1+9);
	gotoxy(X1+28, Y1+2);
	SetColor(COLOR_HIGHLIGHT_TEXT);
	wcout<<"Ma CB: ";
	
	char maCB[MAX_MA_CB];
	short x[2] = {X1+26, X1+45};
	short y[2] = {Y1+5, Y1+5};
	short CD = 15;
	short CR = 3;
	char menu[2][15] = {"Xoa het",
						"Mua ve"}; 
	
	// ve bang
	float sale[3] = {0.1, 0.3, 0.3};
	SetBGColor(COLOR_BG_DEFAULT);
	SetColor(COLOR_TEXT_DEFAULT);
	veLable(sale, 3, X1+8, Y1+11, 70);
	gotoxy(X1+11, Y1+12);
	wcout<<"STT";
	gotoxy(X1+20, Y1+12);
	wcout<<"MA CHUYEN BAY";
	gotoxy(X1+41, Y1+12);
	wcout<<"NG KHOI HANH";
	gotoxy(X1+63, Y1+12);
	wcout<<"SO HIEU MB";
	
	short x_bang = X1+8;
	short y_bang = Y1+14;
	int stt = 1;
	for(int i=0; i<dsmb.getSize(); i++){
		dsmb.getMayBay(i)->DHinCBtheoSanBay(sanBayDen, x_bang, y_bang, stt);
	}
	for(int i=x_bang+1; i<x_bang+70; i++){
		gotoxy(i, y_bang-1);
		wcout<<TB_LINE;
	}
	gotoxy(x_bang, y_bang-1);
	wcout<<BL_LINE;
	gotoxy(x_bang+70, y_bang-1);
	wcout<<BR_LINE;

	gotoxy(x_bang+7, y_bang-1);
	wcout<<BWB_LINE;
	gotoxy(x_bang+28, y_bang-1);
	wcout<<BWB_LINE;
	gotoxy(x_bang+49, y_bang-1);
	wcout<<BWB_LINE;
	
	ChuyenBay* cb=NULL;
	
	while(true){
		SetBGColor(COLOR_BG_ITEM);
		SetColor(COLOR_TEXT_ITEM);
		veKhungItem(x[0], y[0], x[0]+CD, y[0]+CR);
		gotoxy(x[0]+(CD/3), y[0]+1); wcout<<menu[0];
		veKhungItem(x[1], y[1], x[1]+CD, y[1]+CR);
		gotoxy(x[1]+(CD/3), y[1]+1); wcout<<menu[1];
		ShowCur(true);
		do{
			SetBGColor(COLOR_BG_DEFAULT);
			SetColor(COLOR_TEXT_DEFAULT);
			gotoxy(X1+35, Y1+2);
			fflush(stdin);
			if(nhapMa(maCB, MAX_MA_CB)==ESC)
				return NULL;
			cb = dsmb.getCBcuaMB(maCB, sanBayDen);
			if(cb==NULL){
				gotoxy(X1+33, Y1+3);
				SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_WARRING);
				wcout<<"KHONG TIM THAY MA CB!";
				gotoxy(X1+35, Y1+2);
				SetColor(COLOR_BG_DEFAULT);
				wcout<<maCB;	
			}
		} while(cb==NULL);
	
		gotoxy(X1+33, Y1+3);
		SetBGColor(COLOR_BG_DEFAULT);
		SetColor(COLOR_BG_DEFAULT);
		wcout<<"KHONG TIM THAY MA CB!";

		ShowCur(false);
		int selection = 2;
		SetBGColor(COLOR_BG_ITEM_SELECTED);
		SetColor(COLOR_TEXT_ITEM_SELECTED);
		veKhungItem(x[selection-1], y[selection-1], x[selection-1]+CD, y[selection-1]+CR);
		gotoxy(x[selection-1]+(CD/3), y[selection-1]+1); wcout<<menu[selection-1];
		char c=0;
		while(c!=ESC && c!=ENTER){
			c = getch();
			if(c<0)
				c = getch();
			if(c==RIGHT || c==LEFT){
				SetBGColor(COLOR_BG_ITEM);
				SetColor(COLOR_TEXT_ITEM);
				veKhungItem(x[selection-1], y[selection-1], x[selection-1]+CD, y[selection-1]+CR);
				gotoxy(x[selection-1]+(CD/3), y[selection-1]+1); wcout<<menu[selection-1];
			}
			switch(c){
				case RIGHT:
					selection--;
					if(selection == 0)
						selection = 2;
					SetBGColor(COLOR_BG_ITEM_SELECTED);
					SetColor(COLOR_TEXT_ITEM_SELECTED);
					veKhungItem(x[selection-1], y[selection-1], x[selection-1]+CD, y[selection-1]+CR);
					gotoxy(x[selection-1]+(CD/3), y[selection-1]+1); wcout<<menu[selection-1];
					break;
				case LEFT:
					selection++;
					if(selection == 3)
						selection = 1;
					SetBGColor(COLOR_BG_ITEM_SELECTED);
					SetColor(COLOR_TEXT_ITEM_SELECTED);
					veKhungItem(x[selection-1], y[selection-1], x[selection-1]+CD, y[selection-1]+CR);
					gotoxy(x[selection-1]+(CD/3), y[selection-1]+1); wcout<<menu[selection-1];
					break;
				case ESC:
					return NULL;
				case ENTER:
					break;
			}	
		}
		switch(selection){
			case 1:
				break;
			case 2:
				return cb;		
		}
		SetBGColor(COLOR_BG_DEFAULT);
		SetColor(COLOR_BG_DEFAULT);
		gotoxy(X1+35, Y1+2);
		wcout<<maCB;
	}
}

void DatVe_ChonVe(ChuyenBay* &cb){
	char** dsVe = cb->getDSVe(); 
	int soVeDaMua=0;
	int* dsVeMua = veSoVe(dsVe, cb->getSoVe(), X1+7, Y1-2, X2, Y2, soVeDaMua);
	if(dsVeMua==NULL){
		return;
	}
	SetBGColor(COLOR_BG_DEFAULT);
	SetColor(COLOR_TEXT_DEFAULT);
	system("cls");
	SetBGColor(COLOR_BG_DEFAULT);
	SetColor(COLOR_TEXT_DEFAULT);
	veKhung(X1+23, Y1, X1+63, Y1+9);
	
	SetColor(COLOR_HIGHLIGHT_TEXT);
	gotoxy(X1+28, Y1+2);
	wcout<<"CMND: ";
	
	char CMND[MAX_CMND];
	short x[2] = {X1+26, X1+45};
	short y[2] = {Y1+5, Y1+5};
	short CD = 15;
	short CR = 3;
	
	char menu[2][15] = {"Xoa Het",
						"Them HK"};
	
	
	int check=-1;
	while(true){
		SetBGColor(COLOR_BG_ITEM);
		SetColor(COLOR_TEXT_ITEM);
		veKhungItem(x[0], y[0], x[0]+CD, y[0]+CR);
		gotoxy(x[0]+(CD/3), y[0]+1); wcout<<menu[0];
		veKhungItem(x[1], y[1], x[1]+CD, y[1]+CR);
		gotoxy(x[1]+(CD/3), y[1]+1); wcout<<menu[1];
		int len;
		do{
			ShowCur(true);
			gotoxy(X1+35, Y1+2);
			SetBGColor(COLOR_BG_DEFAULT);
			SetColor(COLOR_TEXT_DEFAULT);
			fflush(stdin);
			if(nhapSo(CMND, MAX_CMND)==ESC){
				return;
			}
			check = dsHanhKhach.isDuplicate(CMND);
			len = strlen(CMND);
			if(check && len==9){
				gotoxy(X1+33, Y1+3);
				SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_SUCCESS);
				wcout<<"HANH KHACH DA TON TAI!";
				gotoxy(X1+35, Y1+2);
				SetBGColor(COLOR_BG_ITEM_SELECTED);
				SetColor(COLOR_BG_ITEM_SELECTED);
				strcpy(menu[1], "Sua TT");
				gotoxy(x[1]+(CD/3), y[1]+1); wcout<<menu[1];
					
			} else if(!check && len==9){
				gotoxy(X1+33, Y1+3);
				SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_SUCCESS);
				wcout<<"HANH KHACH CHUA TON TAI!";
			}
			if(len<9){
				gotoxy(X1+38, Y1+3);
				SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_WARRING);
				wcout<<"CMND CO 9 SO";
				gotoxy(X1+35, Y1+2);
				SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_BG_DEFAULT);
				wcout<<CMND;
			}
		} while(len<9);
		
		ShowCur(false);
		int selection = 2;
		SetBGColor(COLOR_BG_ITEM_SELECTED);
		SetColor(COLOR_TEXT_ITEM_SELECTED);
		veKhungItem(x[selection-1], y[selection-1], x[selection-1]+CD, y[selection-1]+CR);
		gotoxy(x[selection-1]+(CD/3), y[selection-1]+1); wcout<<menu[selection-1];
		
		char c;
		while(c!=ESC && c!=ENTER){
			c = getch();
			if(c<0)
				c = getch();
			if(c==RIGHT || c==LEFT){
				SetBGColor(COLOR_BG_ITEM);
				SetColor(COLOR_TEXT_ITEM);
				veKhungItem(x[selection-1], y[selection-1], x[selection-1]+CD, y[selection-1]+CR);
				gotoxy(x[selection-1]+(CD/3), y[selection-1]+1); wcout<<menu[selection-1];
			}
			switch(c){
				case RIGHT:
					selection--;
					if(selection == 0)
						selection = 2;
					SetBGColor(COLOR_BG_ITEM_SELECTED);
					SetColor(COLOR_TEXT_ITEM_SELECTED);
					veKhungItem(x[selection-1], y[selection-1], x[selection-1]+CD, y[selection-1]+CR);
					gotoxy(x[selection-1]+(CD/3), y[selection-1]+1); wcout<<menu[selection-1];
					break;
				case LEFT:
					selection++;
					if(selection == 3)
						selection = 1;
					SetBGColor(COLOR_BG_ITEM_SELECTED);
					SetColor(COLOR_TEXT_ITEM_SELECTED);
					veKhungItem(x[selection-1], y[selection-1], x[selection-1]+CD, y[selection-1]+CR);
					gotoxy(x[selection-1]+(CD/3), y[selection-1]+1); wcout<<menu[selection-1];
					break;
				case ESC:
					return;
				case ENTER:
					break;
			}
		}
		SetBGColor(COLOR_BG_DEFAULT);
		SetColor(COLOR_TEXT_DEFAULT);
		system("cls");
		switch(selection){
			case 1:
				break;
			case 2:
				if(check){
					if(dsHanhKhach.DHsuaHK(X1+10, Y1 , X1+60, Y1+18, CMND)==ESC)
						return;		
				} else if(!check){
					if(dsHanhKhach.DHthemHKtheoCMND(X1+10, Y1 , X1+60, Y1+18, CMND)==ESC)
						return;
				}
				if(soVeDaMua!=0){
					// mua ve
					cb->datVe(dsVeMua, soVeDaMua, CMND);
					
					SetBGColor(COLOR_BG_DEFAULT);
					SetColor(COLOR_TEXT_DEFAULT);
					system("cls");
					veKhung(X1+10, Y1 , X1+60, Y1+8);
					gotoxy(X1+16, Y1+2);
					SetColor(COLOR_HIGHLIGHT_TEXT);
					wcout<<"So Ve:";
					gotoxy(X1+24, Y1+2);
					SetColor(COLOR_TEXT_DEFAULT);
					for(int i=0; i<soVeDaMua; i++){
						wcout<<dsVeMua[i]+1<<" ";
						if((i+1)%12==0){
							gotoxy(X1+20, Y1+3);
						}
					}
					gotoxy(X1+16, Y1+6);
					SetColor(COLOR_SUCCESS);
					wcout<<"DA DUOC MUA THANH CONG! NHAN PHIM BAT KY";
					getch();
				}
				if(dsVeMua!=NULL)
					delete[] dsVeMua;		
				// xoa mang Ve
				return;
		}
		gotoxy(X1+35, Y1+2);
		SetBGColor(COLOR_BG_DEFAULT);
		SetColor(COLOR_BG_DEFAULT);
		wcout<<CMND;
		gotoxy(X1+33, Y1+3);
		SetBGColor(COLOR_BG_DEFAULT);
		SetColor(COLOR_BG_DEFAULT);
		wcout<<"                         ";
	}	
}

void DatVe_MuaVe(short x1, short y1, short x2, short y2){
	
	int s=0;
	char* sanBayDen=NULL;
	ChuyenBay* cb;
	while(true){
		SetBGColor(COLOR_BG_DEFAULT);
		SetColor(COLOR_TEXT_DEFAULT);
		system("cls");
		sanBayDen = DatVe_timSanBay(x1, y1, x2, y2);
		xoaKhung(x1+10, y1+8, x2-10, y2-8);
		if(sanBayDen==NULL){
			ShowCur(false);
			return;
		} else{
			SetBGColor(COLOR_BG_DEFAULT);
			SetColor(COLOR_TEXT_DEFAULT);
			system("cls");
			cb=DatVe_nhapMaCB(sanBayDen);
			if(cb==NULL){
				continue;
			} else{
				SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_TEXT_DEFAULT);
				system("cls");
				DatVe_ChonVe(cb);
				SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_TEXT_DEFAULT);
				system("cls");
			}
		}
		delete sanBayDen;
	}
}

void DatVe_VeTrong(short x1, short y1, short x2, short y2){
	
	SetBGColor(COLOR_BG_DEFAULT);
	SetColor(COLOR_TEXT_DEFAULT);
	system("cls");

	char maCB[MAX_MA_CB];
	short x[2] = {x1+17, x1+36};
	short y[2] = {y1+15, y1+15};
	short CD = 15;
	short CR = 3;
	char menu[2][15] = {"Xoa het",
						"Xem CB"}; 
						
	while(true){
		SetBGColor(COLOR_BG_DEFAULT);
		SetColor(COLOR_TEXT_DEFAULT);
		veKhung(x1+10, y1+8, x2-10, y2-8);
		gotoxy(x1+15, y1+11);
		SetColor(COLOR_HIGHLIGHT_TEXT);
		wcout<<"Ma CB: ";
	
		SetBGColor(COLOR_BG_ITEM);
		SetColor(COLOR_TEXT_ITEM);
		veKhungItem(x[0], y[0], x[0]+CD, y[0]+CR);
		gotoxy(x[0]+(CD/3), y[0]+1); wcout<<menu[0];
		veKhungItem(x[1], y[1], x[1]+CD, y[1]+CR);
		gotoxy(x[1]+(CD/3), y[1]+1); wcout<<menu[1];
		
		ShowCur(true);
		ChuyenBay* cb=NULL;
		do{	
			SetBGColor(COLOR_BG_DEFAULT);
			SetColor(COLOR_TEXT_DEFAULT);
			gotoxy(x1+23, y1+11);
			if(nhapMa(maCB, MAX_MA_CB)==ESC)
				return;
			cb = dsmb.getCBtheoMaCB(maCB);
			if(cb==NULL){
				gotoxy(x1+22, y1+13);
				SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_WARRING);
				wcout<<"KHONG TIM THAY CHUYEN BAY!";
				SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_BG_DEFAULT);
				gotoxy(x1+23, y1+11);
				wcout<<maCB;
			}
		} while(cb==NULL);
			gotoxy(x1+22, y1+13);
			SetBGColor(COLOR_BG_DEFAULT);
			SetColor(COLOR_BG_DEFAULT);
			wcout<<"KHONG TIM THAY CHUYEN BAY!";
			ShowCur(false);
		
		int selection = 2;
		SetBGColor(COLOR_BG_ITEM_SELECTED);
		SetColor(COLOR_TEXT_ITEM_SELECTED);
		veKhungItem(x[selection-1], y[selection-1], x[selection-1]+CD, y[selection-1]+CR);
		gotoxy(x[selection-1]+(CD/3), y[selection-1]+1); wcout<<menu[selection-1];
		char c=0;
		while(c!=ESC && c!=ENTER){
			c = getch();
			if(c<0)
				c = getch();
			if(c==RIGHT || c==LEFT){
				SetBGColor(COLOR_BG_ITEM);
				SetColor(COLOR_TEXT_ITEM);
				veKhungItem(x[selection-1], y[selection-1], x[selection-1]+CD, y[selection-1]+CR);
				gotoxy(x[selection-1]+(CD/3), y[selection-1]+1); wcout<<menu[selection-1];
			}
			switch(c){
				case RIGHT:
					selection--;
					if(selection == 0)
						selection = 2;
					SetBGColor(COLOR_BG_ITEM_SELECTED);
					SetColor(COLOR_TEXT_ITEM_SELECTED);
					veKhungItem(x[selection-1], y[selection-1], x[selection-1]+CD, y[selection-1]+CR);
					gotoxy(x[selection-1]+(CD/3), y[selection-1]+1); wcout<<menu[selection-1];
					break;
				case LEFT:
					selection++;
					if(selection == 3)
						selection = 1;
					SetBGColor(COLOR_BG_ITEM_SELECTED);
					SetColor(COLOR_TEXT_ITEM_SELECTED);
					veKhungItem(x[selection-1], y[selection-1], x[selection-1]+CD, y[selection-1]+CR);
					gotoxy(x[selection-1]+(CD/3), y[selection-1]+1); wcout<<menu[selection-1];
					break;
				case ESC:
					return;
				case ENTER:
					break;
			}
		}
		switch(selection){
			case 1:
				break;
			case 2:
				SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_BG_DEFAULT);
				system("cls");
				veVeTrong(cb->getDSVe(), cb->getSoVe(), X1+7, Y1-2, X2, Y2);	
				while(true){
					if(getch()==ESC)
						break;
				}
				SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_BG_DEFAULT);
				system("cls");
				break;	
		}
		SetBGColor(COLOR_BG_DEFAULT);
		SetColor(COLOR_BG_DEFAULT);
		gotoxy(x1+23, y1+11);
		wcout<<maCB;
	}
		
}

void case_DatVe(short x1, short y1, short x2, short y2){
	int s =1;
	char CMND[MAX_CMND];
	int temp;
	while(true){
		s = veMenu(menuPhu_DatVe, 2, x1, y1, x2, y2, MARGIN_X+CD_ITEM+2, MARGIN_Y, CD_ITEM/2+1, CR_ITEM, s);
		switch(s){
			case 1:
				DatVe_MuaVe(X1+15, Y1-8 , X1+80, Y1+19);
				return;
			case 2:
				DatVe_VeTrong(X1+15, Y1-8 , X1+80, Y1+19);
				SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_BG_DEFAULT);
				system("cls");
				return;
			case 0:
				xoaMenuItem(menuPhu_HK, 5, x1, y1, x2, y2, MARGIN_X+CD_ITEM+2, MARGIN_Y, CD_ITEM/2+1, CR_ITEM);
				return;
		}
		ShowCur(false);		
	}
}

								   
int main(){
	_setmode(_fileno(stdout), _O_U16TEXT);
	int selection = 1;

	
	// doc dlieu tu file
	docDlieuFile();	
	
	time_t  theTime = time(NULL);
	struct tm *aTime = localtime(&theTime);
	int cur_nam = aTime->tm_year+1900;
	int cur_thang = aTime->tm_mon+1;
	int cur_ngay = aTime->tm_mday;
	Date now(0, 0,cur_ngay, cur_thang, cur_nam);
	dsmb.capNhatSTT_ALL(now);
		
	while(true){
		ShowCur(false);
		if(!selection)
			selection = 1;
		inLable(X1+48, Y1+1);
		SetBGColor(COLOR_BG_DEFAULT);
		SetColor(COLOR_TEXT_DEFAULT);
		veKhungMenu(X1, Y1, X2, Y2);
		selection = veMenu(menuChinh, 6, X1, Y1, (X1+X2)/2-10, Y2, MARGIN_X, MARGIN_Y, CD_ITEM, CR_ITEM, selection);
		switch(selection){
			case 1:
				case_DatVe(X1, Y1, (X1+X2)/2-10, Y2);
					
				break;
			case 2:
				case_QLCB(X1, Y1, (X1+X2)/2-10, Y2);
				
				break;
			case 3:
				case_QLMB(X1, Y1, (X1+X2)/2-10, Y2);
				
				break;
			case 4:
				case_HK(X1, Y1, (X1+X2)/2-10, Y2);
				
				break;
			case 5:
				xoaKhung(X1+48, Y1+1, X2-2, Y2-2);
				ghiDlieuFile((X1+X2)/2, Y1+8, X2-10, Y2-8);
				xoaKhung((X1+X2)/2, Y1+8, X2-10, Y2-8);
				break;
			case 0:
				break;
			case 6:
				SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_TEXT_DEFAULT);
				system("cls");
				return 0;
		}
	}	
}

	
