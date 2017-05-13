#include "HanhKhach.h"

HanhKhach::HanhKhach(){
	
}

HanhKhach::HanhKhach(char* CMND, char* ho, char* ten, bool phai){
	strcpy(this->CMND, CMND);
	strcpy(this->ho, ho);
	strcpy(this->ten, ten);
	this->phai = phai;
}

void HanhKhach::xuat(){
	wcout<<setw(MAX_CMND)<<left<<CMND<<"\t";
	wcout<<setw(40)<<left<<ho<<" "<<ten<<"\t";
	phai ? wcout<<"Nam" : wcout<<"Nu";
	wcout<<endl;
}

char* HanhKhach::getCMND(){
	return CMND;
}

char* HanhKhach::getTen(){
	return ten;
}

char* HanhKhach::getHo(){
	return ho;
}

bool HanhKhach::getPhai(){
	return phai;
}

void HanhKhach::setCMND(char* CMND){
	strcpy(this->CMND, CMND);
}

void HanhKhach::setTen(char* ten){
	strcpy(this->ten, ten);
}

void HanhKhach::setHo(char* ho){
	strcpy(this->ho, ho);
}

void HanhKhach::setPhai(bool phai){
	this->phai = phai;
}

void HanhKhach::DHinHKtheoMaCB(short &x, short &y, int &stt, int soVe){

	gotoxy(x+3, y);
	wcout<<stt;
	gotoxy(x+9, y);
	wcout<<"["<<soVe<<"]";
	gotoxy(x+21, y);
	wcout<<CMND;
	gotoxy(x+42, y);
	wcout<<ho<<" "<<ten;
	gotoxy(x+66, y);
	phai ? wcout<<"Nam" : wcout<<"Nu";
	
	gotoxy(x, y);
	wcout<<LR_LINE;
	gotoxy(x+70, y);
	wcout<<LR_LINE;
	gotoxy(x+7, y);
	wcout<<LR_LINE;
	gotoxy(x+14, y);
	wcout<<LR_LINE;
	gotoxy(x+35, y);
	wcout<<LR_LINE;
	gotoxy(x+63, y);
	wcout<<LR_LINE;
	
	gotoxy(x, y+1);
	wcout<<LR_LINE;
	gotoxy(x+70, y+1);
	wcout<<LR_LINE;
	gotoxy(x+7, y+1);
	wcout<<LR_LINE;
	gotoxy(x+14, y+1);
	wcout<<LR_LINE;
	gotoxy(x+35, y+1);
	wcout<<LR_LINE;
	gotoxy(x+63, y+1);
	wcout<<LR_LINE;
	
	y=y+2;
	stt++;
}


