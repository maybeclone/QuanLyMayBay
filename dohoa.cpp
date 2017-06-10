#include "dohoa.h"


void xoaMenuItem(char dsMenu[][MAX_TEXT_MENU], int size, short x1, short y1, short x2, short y2,
					const short MAR_X, const short MAR_Y, const short CD, const short CR){
	short y = y1+MAR_Y;
	short x = MAR_X;
	SetBGColor(COLOR_BG_DEFAULT);
	SetColor(COLOR_BG_DEFAULT);
	for(int i=0; i<size; i++){
		gotoxy(x, y);
		veKhungItem(x, y, x+CD, y+CR);
		gotoxy(x+(CD/3), y+1);
		wcout<<dsMenu[i];
		y = y+CR+1;
	}
}

int veMenu(char dsMenu[][MAX_TEXT_MENU], int size, short x1, short y1, short x2, short y2, 
				const short MAR_X, const short MAR_Y, const short CD, const short CR, int sel){
	short y = y1+MAR_Y;
	short x = MAR_X ;
	
	SetBGColor(COLOR_BG_ITEM);
	SetColor(COLOR_TEXT_ITEM);
	for(int i=0; i<size; i++){
		gotoxy(x, y);
		veKhungItem(x, y, x+CD, y+CR);
		gotoxy(x+(CD/3), y+1);
		wcout<<dsMenu[i];
		y = y+CR+1; // 1 - K/C o giua item btn
	}
	SetColor(COLOR_TEXT_DEFAULT);
	SetBGColor(COLOR_BG_DEFAULT);
	
	
	int selection = sel;
	y = selection*4-1;
	gotoxy(x, y);
	
	SetColor(COLOR_TEXT_ITEM_SELECTED);
	SetBGColor(COLOR_BG_ITEM_SELECTED);
	
	veKhungItem(x, y, x+CD, y+CR);
	gotoxy(x+(CD/3), y+1);
	wcout<<dsMenu[selection-1];
	
	char c = 0;
	while(true){
		c = getch();
		if(c<0){
			c = getch();
		}
		
		if(c==UP || c==DOWN){			
			SetColor(COLOR_TEXT_ITEM);
			SetBGColor(COLOR_BG_ITEM);
			
			veKhungItem(x, y, x+CD, y+CR);
			gotoxy(x+(CD/3), y+1);
			wcout<<dsMenu[selection-1];
		}
		switch (c){
			case UP:
				selection--;
				if(selection<1)
					selection = size;
				y = selection*4-1;
				gotoxy(x, y);
				SetColor(COLOR_TEXT_ITEM_SELECTED);
				SetBGColor(COLOR_BG_ITEM_SELECTED);
			
				veKhungItem(x, y, x+CD, y+CR);
				gotoxy(x+(CD/3), y+1);
				wcout<<dsMenu[selection-1];
			
				SetColor(COLOR_TEXT_DEFAULT);	
				SetBGColor(COLOR_BG_DEFAULT);
				break;
			case DOWN:
				selection++;
				if(selection>size)
					selection = 1;
				y = selection*4-1;
				gotoxy(x, y);
				SetColor(COLOR_TEXT_ITEM_SELECTED);
				SetBGColor(COLOR_BG_ITEM_SELECTED);
			
				veKhungItem(x, y, x+CD, y+CR);
				gotoxy(x+(CD/3), y+1);
				wcout<<dsMenu[selection-1];
			
				SetColor(COLOR_TEXT_DEFAULT);	
				SetBGColor(COLOR_BG_DEFAULT);
				break;
			case RIGHT:
			case ENTER:
				return selection;
			case LEFT:
			case ESC:
				return 0;
			}
	}
}

void veKhungMenu(short x1, short y1, short x2, short y2){
	ve4Goc(x1, y1, x2, y2);
	veCanhTB(x1, y1, x2, y2);
	veCanhTB(x1, y2, x2, y1);
	veCanhLR(x1, y1, x2, y2);
	veCanhLR(x2, y1, x1, y2);
	veCanhBETWEEN((x2+x1)/2-10, y1, (x2+x1)/2-10, y2);
}

void veKhungItem(short x1, short y1, short x2, short y2){	
	for(int j=y1; j<y2; j++){
		for(int i=x1; i<=x2; i++){
			gotoxy(i, j);
			wcout<<" ";
		}
	}

}

void veKhung(short x1, short y1, short x2, short y2){
	ve4Goc(x1, y1, x2, y2);
	veCanhTB(x1, y1, x2, y2);
	veCanhTB(x1, y2, x2, y2);
	veCanhLR(x1, y1, x2, y2);
	veCanhLR(x2, y1, x1, y2 );
}

void veCanhLR(short x1, short y1, short x2, short y2){
	for(int i=y1+1; i<y2; i++){
		gotoxy(x1, i);
		wcout<<LR;
	}
}

void veCanhBETWEEN(short x1, short y1, short x2, short y2){
	gotoxy(x1, y1);
	wcout<<BWT;
	gotoxy(x2, y2);
	wcout<<BWB;
	for(int i=y1+1; i<y2; i++){
		gotoxy(x1, i);
		wcout<<LR;
	}
}

void veCanhTB(short x1, short y1, short x2, short y2){
	gotoxy(x1+1, y1);
	for(int i=x1; i<x2-1; i++){
		wcout<<TB;
	}
}

void ve4Goc(short x1, short y1, short x2, short y2){
	gotoxy(x1, y1);
	wcout<<TL;
	gotoxy(x2, y2);
	wcout<<BR;
	gotoxy(x2, y1);
	wcout<<TR;
	gotoxy(x1, y2);
	wcout<<BL;
}

void xoaKhung(short x1, short y1, short x2, short y2){
	SetBGColor(COLOR_BG_DEFAULT);
	SetColor(COLOR_BG_DEFAULT);
	for(int i=y1; i<=y2; i++){
		for(int j=x1; j<=x2; j++){
			gotoxy(j, i);
			wcout<<" ";
		}
	}
}

void veTable(int col, float *sale, short x1, short y1, short x2, short y2){
	/*	
		col : so cot
		sale : ti le giua cac cot
		x1, y1: top left
		x2, y2: right bottom
	*/
	
	// vi tri mang sale
	int dem=0;
	// vi tri ve cot
	int temp=x1+(x2-x1)*sale[0];
	
	SetBGColor(COLOR_BG_DEFAULT);
	SetColor(COLOR_TEXT_DEFAULT);
	gotoxy(x1, y1);
	wcout<<TL_LINE;
	gotoxy(x2, y1);
	wcout<<TR_LINE;
	
	// VE PHAN TREN
	for(int i=x1+1; i<x2;i++){
		gotoxy(i, y1);
		
		// i = vi tri ve cot
		if(i == temp && dem<col){
			dem++;
			temp=temp+sale[dem]*(x2-x1);
			wcout<<BWT_LINE;
		} else
			wcout<<TB_LINE;
	}
	
	// VE PHAN DUOI
	dem=0;
	temp=x1+(x2-x1)*sale[0];
	
	gotoxy(x1, y2);
	wcout<<BL_LINE;
	gotoxy(x2, y2);
	wcout<<BR_LINE;
	for(int i=x1+1; i<x2;i++){
		gotoxy(i, y2);
		if(i == temp && dem<col){
			dem++;
			temp=temp+sale[dem]*(x2-x1);
			wcout<<BWB_LINE;
		} else
			wcout<<TB_LINE;
	}
	
	// VE PHAN GIUA CAC COT
	for(int i=y1+2; i<y2; i=i+2){
		dem=0;
		temp=x1+(x2-x1)*sale[0];
		
		for(int j=x1; j<=x2;j++){
			gotoxy(j, i-1);
			if(j == temp && dem<col){
				dem++;
				temp=temp+sale[dem]*(x2-x1);
				wcout<<LR_LINE;
			} 
			if(j==x1 || j==x2)
				wcout<<LR_LINE;
		}	
		dem=0;
		temp=x1+(x2-x1)*sale[0];
		
		for(int j=x1; j<=x2; j++){
			gotoxy(j, i);
			if(j == temp && dem<col){
				dem++;
				temp=temp+sale[dem]*(x2-x1);
				wcout<<PLUS_LINE;
			} else if(j==x1)
				wcout<<BWL_LINE;
			else if(j==x2)
				wcout<<BWR_LINE;
			else
				wcout<<TB_LINE;	
		}
	}
	dem=0;
	temp=x1+(x2-x1)*sale[0];
	
	// VE PHAN GIUA CAC HANG
	for(int j=x1; j<=x2;j++){
		gotoxy(j, y2-1);
		if(j == temp && dem<col){
			dem++;
			temp=temp+sale[dem]*(x2-x1);
			wcout<<LR_LINE;
		} 
		if(j==x1 || j==x2)
			wcout<<LR_LINE;
	}	
}

void veLable(float* sale, int col, short x1, short y1, int CD){
	short x = x1;
	int dem=0;
	int temp = x1+CD*sale[0];
	
	gotoxy(x1, y1);
	wcout<<TL_LINE;
	gotoxy(x1, y1+1);
	wcout<<LR_LINE;
	gotoxy(x1, y1+2);
	wcout<<BWL_LINE;
	gotoxy(x1+CD, y1+2);
	wcout<<BWR_LINE;
	gotoxy(x1+CD, y1+1);
	wcout<<LR_LINE;
	gotoxy(x1+CD, y1);
	wcout<<TR_LINE;
	
	for(int i=x1+1; i<CD+x1; i++){
		gotoxy(i, y1);
		if(i==temp && dem<col){
			dem++;
			temp=temp+sale[dem]*CD;
			wcout<<BWT_LINE;
			gotoxy(i, y1+1);
			wcout<<LR_LINE;
			gotoxy(i, y1+2);
			wcout<<PLUS_LINE;
		} else{
			wcout<<TB_LINE;
			gotoxy(i, y1+2);
			wcout<<TB_LINE;
		}
	}
}

void inLable(short x, short y){
	SetBGColor(COLOR_BG_DEFAULT);
	SetColor(14);
	gotoxy(x+12, y);
	wcout<<"_______ _____  _________ _____   __   ______ __  __";
	gotoxy(x+12, y+1);
	wcout<<"__  __ \\__  / / /___    |___  | / /   ___  / _ \\/ /";
	gotoxy(x+12, y+2);
	wcout<<"_  / / /_  / / / __  /| |__   |/ /    __  /  __  / ";
	gotoxy(x+12, y+3);
	wcout<<"/ /_/ / / /_/ /  _  ___ |_  /|  /     _  /____  /  ";
	gotoxy(x+12, y+4);
	wcout<<"\\___\\_\\ \\____/   /_/  |_|/_/ |_/      /_____//_/   ";

	gotoxy(x+6, y+7);
	wcout<<"_______________  _______  ____  _________________   __";
	gotoxy(x+6, y+8);
	wcout<<"__  ____/___  / / /__  / / /_ \\/ /___  ____/___  | / /";
	gotoxy(x+6, y+9);
	wcout<<"_  /     __  /_/ / _  / / / __  / __  __/   __   |/ / ";
	gotoxy(x+6, y+10);
	wcout<<"/ /___   _  __  /  / /_/ /  _  /  _  /___   _  /|  /  ";
	gotoxy(x+6, y+11);
	wcout<<"\\____/   /_/ /_/   \\____/   /_/   /_____/   /_/ |_/  ";
	
	gotoxy(x+2,y+14);
	wcout<<"________ _______ __  __";
	gotoxy(x+2,y+15);
	wcout<<"___  __ )___    |_ \\/ /";
	gotoxy(x+2,y+16);
	wcout<<"__  __  |__  /| |__  / ";
	gotoxy(x+2,y+17);
	wcout<<"_  /_/ / _  ___ |_  /  ";
	gotoxy(x+2,y+18);
	wcout<<"/_____/  /_/  |_|/_/  ";
	
	SetColor(13);
	gotoxy(x+32, y+16);
	wcout<<"CAU TRUC DU LIEU VA GIAI THUAT";
	gotoxy(x+38, y+18);
	wcout<<"De Tai Ket Thuc Mon";
	
	SetColor(10); 
	gotoxy(x+34, y+20);
	wcout<<"HO TEN: ";
	gotoxy(x+34, y+22);
	wcout<<"MA SV : ";
	gotoxy(x+34, y+24);
	wcout<<"LOP   : ";
	
	SetColor(11);
	gotoxy(x+42, y+20);
	wcout<<"Le Thanh Trung";
	gotoxy(x+42, y+22);
	wcout<<"N14DCPT048";
	gotoxy(x+42, y+24);
	wcout<<"D14CQPU01-N";
	
}
          
