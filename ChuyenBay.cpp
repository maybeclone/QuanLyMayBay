#include "ChuyenBay.h"

ChuyenBay::ChuyenBay(){
	trangThai = HET_VE;
	dsVe = NULL; 
	soVe=0;
}

ChuyenBay::ChuyenBay(int soCho, char* sanBayDen, Date ngKhoiHanh){
	soVe = soCho;
	dsVe = new char*[soVe];
	for(int i=0; i<soVe; i++){
		dsVe[i] = new char[MAX_CMND];
		strcpy(dsVe[i], "");
	}
	trangThai = CON_VE; // ve con
	strcpy(this->sanBayDen, sanBayDen);
	this->ngKhoiHanh = ngKhoiHanh;
}

ChuyenBay::ChuyenBay(char* maCB, char* sanBayDen, int soVe, Date ngKhoiHanh){
	this->soVe = soVe;
	strcpy(this->maCB, maCB);
	strcpy(this->sanBayDen, sanBayDen);
	this->ngKhoiHanh = ngKhoiHanh;	
	dsVe = new char*[soVe];
	for(int i=0; i<soVe; i++){
		dsVe[i] = new char[MAX_CMND];
		strcpy(dsVe[i], "");
	}
	trangThai = CON_VE;
}

ChuyenBay::ChuyenBay(char* maCB, char* sanBayDen, Date ngKhoiHanh, int trangThai){
	strcpy(this->maCB, maCB);
	strcpy(this->sanBayDen, sanBayDen);
	this->ngKhoiHanh = ngKhoiHanh;
	this->trangThai = trangThai;
	this->soVe = 0;
}

ChuyenBay::ChuyenBay(const ChuyenBay& cb){
	strcpy(maCB, cb.maCB);
	strcpy(sanBayDen, cb.sanBayDen);
	trangThai = cb.trangThai;
	ngKhoiHanh = cb.ngKhoiHanh;
	soVe = cb.soVe;
	dsVe = new char*[soVe];
	for(int i=0; i<soVe; i++){
		dsVe[i] = new char[MAX_CMND];
		strcpy(dsVe[i], cb.dsVe[i]);
	}
}

ChuyenBay ChuyenBay::operator=(const ChuyenBay& cb){
	strcpy(maCB, cb.maCB);
	strcpy(sanBayDen, cb.sanBayDen);
	trangThai = cb.trangThai;
	ngKhoiHanh = cb.ngKhoiHanh;
	soVe = cb.soVe;
	dsVe = new char*[soVe];
	for(int i=0; i<soVe; i++){
		dsVe[i] = new char[MAX_CMND];
		strcpy(dsVe[i], cb.dsVe[i]);
	}
	return *this;
}

ChuyenBay::~ChuyenBay(){
	if(soVe>0 && dsVe !=NULL){
		for(int i=0; i<soVe; i++){
			delete[] dsVe[i];
		}
		delete[] dsVe;	
	}
}

int ChuyenBay::getTrangThai(){
	return trangThai;
}

void ChuyenBay::xuat(){
	wcout<<setw(MAX_MA_CB)<<left<<maCB<<"\t"<<setw(MAX_SAN_BAY)<<left<<sanBayDen<<"\t";
	wcout<<setw(2)<<left<<trangThai<<"\t"<<"\t"<<soVe<<"\t";
	ngKhoiHanh.xuat();
	wcout<<endl;
}

int ChuyenBay::getSoVe(){
	return soVe;
}

char* ChuyenBay::getMaCB(){
	return maCB;
}

int ChuyenBay::huyChuyen(){
	if(trangThai==HUY || trangThai==HOAN_TAT){
		return 0;
	}
	trangThai = HUY;
	return 1;
}

int ChuyenBay::update(){
	if(trangThai==HUY || trangThai==HOAN_TAT){
		return 0;
	}
	ngKhoiHanh.nhap();
	return 1;
}

void ChuyenBay::write(ofstream& fout){

	fout.write((char*) &maCB, sizeof(char)*MAX_MA_CB);
	fout.write((char*) &sanBayDen, sizeof(char)*MAX_SAN_BAY);
	fout.write((char*) &soVe, sizeof(int));	

	fout.write((char*) &trangThai, sizeof(trangThai));
	fout.write((char*) &ngKhoiHanh, sizeof(Date));
	
	for(int i=0; i<soVe; i++){
		fout.write(dsVe[i], sizeof(char)*MAX_CMND);
	}
}

void ChuyenBay::read(ifstream& fin){
	
	fin.read((char*) &maCB, sizeof(char)*MAX_MA_CB);
	fin.read((char*) &sanBayDen, sizeof(char)*MAX_SAN_BAY);
	fin.read((char*) &soVe, sizeof(int));
	
	fin.read((char*) &trangThai, sizeof(trangThai));
	fin.read((char*) &ngKhoiHanh, sizeof(Date));

	dsVe = new char*[soVe];
	for(int i=0; i<soVe; i++){
		dsVe[i] = new char[MAX_CMND];
		fin.read(dsVe[i], sizeof(char)*MAX_CMND);
	}
}

char* ChuyenBay::getSanBayDen(){
	return sanBayDen;
}

Date* ChuyenBay::getNgKhoiHanh(){
	return &ngKhoiHanh;
}
int ChuyenBay::soVeConTrong(){
	int dem=0;
	for(int i=0; i<soVe; i++){
		if(strcmpi(dsVe[i], "")==0){
			dem++;
		}
	}
	return dem;
}

void ChuyenBay::datVe(int* dsVeMua, int soVeMua, char* CMND){
	for(int i=0; i<soVeMua; i++){
		strcpy(dsVe[dsVeMua[i]], CMND);
	}
	// cap nhat trang thai
	if(soVeConTrong()==0){
		trangThai=HET_VE;
	}
}

char** ChuyenBay::getDSVe(){
	return dsVe;
}

void ChuyenBay::DHhieuchinhNgKhoiHanh(short x1, short y1, short x2, short y2){
	SetBGColor(COLOR_BG_DEFAULT);
	SetColor(COLOR_TEXT_DEFAULT);
	veKhung(x1, y1, x2, y2);
	
	SetBGColor(COLOR_BG_DEFAULT);
	SetColor(COLOR_HIGHLIGHT_TEXT);
	gotoxy(x1+6, y1+2);
	wcout<<"Ma CB    :";
	gotoxy(x1+6, y1+4);
	wcout<<"So Cho   :";
	gotoxy(x1+6, y1+6);
	wcout<<"Tr Thai  :";
	gotoxy(x1+6, y1+8);
	wcout<<"Ng K.Hanh:";
	gotoxy(x1+6, y1+10);
	wcout<<"Gio BD   :";
	
	SetBGColor(COLOR_BG_DEFAULT);
	SetColor(COLOR_TEXT_DEFAULT);
	gotoxy(x1+18, y1+2);
	wcout<<maCB;
	gotoxy(x1+18, y1+4);
	wcout<<soVe;
	gotoxy(x1+18, y1+6);
	trangThai == CON_VE ? wcout<<"CON VE" : wcout<<"HET VE";
	gotoxy(x1+30, y1+8);
	wcout<<"YYYY/MM/DD";
	gotoxy(x1+30, y1+10);
	wcout<<"HH:mm";
	
	short x[2] = {x1+4, x1+23};
	short y[2] = {y1+13, y1+13};
	short CD = 15;
	short CR = 3;
	
	char menu[2][15] = {"Xoa Het",
						"Sua CB"};
	
	char ngay[3];
	char thang[3];
	char nam[5];
	char gio[3];
	char phut[3];
	int check;
	
	time_t  theTime = time(NULL);
	struct tm *aTime = localtime(&theTime);
	int cur_nam = aTime->tm_year+1900;
	int cur_thang = aTime->tm_mon+1;
	int cur_ngay = aTime->tm_mday;
	
	while(true){
		SetBGColor(COLOR_BG_DEFAULT);
		SetColor(COLOR_TEXT_DEFAULT);
		
		gotoxy(x1+18, y1+8);
		ngKhoiHanh.xuatNgSua();
		gotoxy(x1+18, y1+10);
		ngKhoiHanh.xuatGio();
		
		itoa(ngKhoiHanh.getNam(), nam, 10);
		itoa(ngKhoiHanh.getThang(), thang, 10);
		itoa(ngKhoiHanh.getNgay(), ngay, 10);
		itoa(ngKhoiHanh.getGio(), gio, 10);
		itoa(ngKhoiHanh.getPhut(), phut, 10);
		
		if(strlen(ngay)==1){
			ngay[0] = (wchar_t) '0';
			ngay[1] = (wchar_t) ngKhoiHanh.getNgay()+48;
			ngay[2] ='\0';
		}
		if(strlen(thang)==1){
			thang[0] = (wchar_t) '0';
			thang[1] = (wchar_t) ngKhoiHanh.getThang()+48;
			thang[2] = '\0';
		}
		if(strlen(gio)==1){
			gio[0] = (wchar_t) '0';
			gio[1] = (wchar_t) ngKhoiHanh.getGio()+48;
			gio[2] = '\0';
		}
		if(strlen(phut)==1){
			phut[0] = (wchar_t) '0';
			phut[1] = (wchar_t) ngKhoiHanh.getPhut()+48;
			gio[2] = '\0';
		}
		
		ShowCur(true);
		SetBGColor(COLOR_BG_ITEM);
		SetColor(COLOR_TEXT_ITEM);
		veKhungItem(x[0], y[0], x[0]+CD, y[0]+CR);
		gotoxy(x[0]+(CD/3), y[0]+1); wcout<<menu[0];
		veKhungItem(x[1], y[1], x[1]+CD, y[1]+CR);
		gotoxy(x[1]+(CD/3), y[1]+1); wcout<<menu[1];
	
		// get cur time vs date
		check = 1;
		do{
			if(!check){
				strcpy(nam,"");
			}
			SetColor(COLOR_TEXT_DEFAULT);
			SetBGColor(COLOR_BG_DEFAULT);
			gotoxy(x1+18+strlen(nam), y1+8);
			fflush(stdin);
			if(nhapSo_EDIT(nam, 5, strlen(nam))==ESC)
				return;
			check = checkNam(atoi(nam), cur_nam);
			if(!check){
				gotoxy(x1+10, y1+9);
				SetColor(COLOR_WARRING);
				wcout<<"NAM PHAI >= "<<cur_nam<<" VA <= "<<MAX_NAM;
				gotoxy(x1+18, y1+8);
				SetColor(COLOR_BG_DEFAULT);
				wcout<<nam;
			}
		} while(!check);
		gotoxy(x1+10, y1+9);
		SetColor(COLOR_BG_DEFAULT);
		wcout<<"NAM PHAI >= "<<cur_nam<<" VA <= "<<MAX_NAM;
		check=1;
		do{	
			if(check==-1 || check ==0){
				strcpy(thang,"");
			}
			SetBGColor(COLOR_BG_DEFAULT);
			SetColor(COLOR_TEXT_DEFAULT);
			gotoxy(x1+23+strlen(thang), y1+8);
			fflush(stdin);
			if(nhapSo_EDIT(thang, 3, strlen(thang))==ESC)
				return;
			check = checkThang(atoi(nam), atoi(thang), cur_nam, cur_thang);
			if(check == -1){
				gotoxy(x1+10, y1+9);
				SetColor(COLOR_BG_DEFAULT);
				wcout<<"                              ";
				gotoxy(x1+10, y1+9);
				SetColor(COLOR_WARRING);
				wcout<<"THANG PHAI >= THANG "<<cur_thang<<" NAM "<<cur_nam;
				gotoxy(x1+23, y1+8);
				SetColor(COLOR_BG_DEFAULT);
				wcout<<thang;
			} else if(check == 0){
				gotoxy(x1+10, y1+9);
				SetColor(COLOR_BG_DEFAULT);
				wcout<<"                              ";
				gotoxy(x1+15, y1+9);
				SetColor(COLOR_WARRING);
				wcout<<"NAM CO 12 THANG";
				gotoxy(x1+23, y1+8);
				SetColor(COLOR_BG_DEFAULT);
				wcout<<thang;
			}
		} while(check!=1);
	
		gotoxy(x1+23, y1+8);
		SetColor(COLOR_TEXT_DEFAULT);
		wcout<<setw(2)<<setfill((wchar_t)'0')<<right<<thang; 
		
		gotoxy(x1+10, y1+9);
		SetColor(COLOR_BG_DEFAULT);
		wcout<<"                              ";
		check=1;	
		do{
			if(check>=28 || check==0){
				strcpy(ngay,"");
			}
			SetBGColor(COLOR_BG_DEFAULT);
			SetColor(COLOR_TEXT_DEFAULT);
			gotoxy(x1+26+strlen(ngay), y1+8);
			fflush(stdin);
			if(nhapSo_EDIT(ngay, 3, strlen(ngay))==ESC)
				return;
			check = checkNgay(atoi(nam), atoi(thang), atoi(ngay), cur_nam, cur_thang, cur_ngay);
			if(check==0){
				gotoxy(x1+10, y1+9);
				SetColor(COLOR_BG_DEFAULT);
				wcout<<"                           ";
				gotoxy(x1+10, y1+9);
				SetColor(COLOR_WARRING);
				wcout<<"NGAY PHAI > NGAY "<<cur_ngay<<" THANG "<<cur_thang;
				gotoxy(x1+26, y1+8);
				SetColor(COLOR_BG_DEFAULT);
				wcout<<ngay;
			} else if(check>=28){
				gotoxy(x1+10, y1+9);
				SetColor(COLOR_BG_DEFAULT);
				wcout<<"                           ";
				gotoxy(x1+15, y1+9);
				SetColor(COLOR_WARRING);
				wcout<<"THANG "<<thang<<" CO "<<check<<" NGAY ";
				gotoxy(x1+26, y1+8);
				SetColor(COLOR_BG_DEFAULT);
				wcout<<ngay;
			}
		} while(check!=1);
		
		gotoxy(x1+26, y1+8);
		SetColor(COLOR_TEXT_DEFAULT);
		wcout<<setw(2)<<setfill((wchar_t)'0')<<right<<ngay; 
		
		gotoxy(x1+10, y1+9);
		SetColor(COLOR_BG_DEFAULT);
		wcout<<"                           ";
		
		check=1;
		do{
			if(!check)
				strcpy(gio,"");
			SetColor(COLOR_TEXT_DEFAULT);
			gotoxy(x1+18+strlen(gio), y1+10);
			fflush(stdin);
			if(nhapSo_EDIT(gio, 3, strlen(gio))==ESC)
				return;
			check = checkGio(atoi(gio));
			if(!check){
				gotoxy(x1+15, y1+11);
				SetColor(COLOR_WARRING);
				wcout<<"NGAY CO 24 GIO";
				gotoxy(x1+18, y1+10);
				SetColor(COLOR_BG_DEFAULT);
				wcout<<gio;
			}
		} while(!check);
		
		gotoxy(x1+18, y1+10);
		SetColor(COLOR_TEXT_DEFAULT);
		wcout<<setw(2)<<setfill((wchar_t)'0')<<right<<gio; 
		gotoxy(x1+15, y1+11);
		SetColor(COLOR_BG_DEFAULT);
		wcout<<"NGAY CO 24 GIO";
		check=1;
		do{	
			if(!check)
				strcpy(phut,"");
			SetColor(COLOR_TEXT_DEFAULT);
			gotoxy(x1+21+strlen(phut), y1+10);
			fflush(stdin);
			if(nhapSo_EDIT(phut, 3, strlen(phut))==ESC)
				return;
			check = checkPhut(atoi(phut));
			if(!check){
				gotoxy(x1+15, y1+11);
				SetColor(COLOR_WARRING);
				wcout<<"GIO CO 60 PHUT";
				gotoxy(x1+21, y1+10);
				SetColor(COLOR_BG_DEFAULT);
				wcout<<phut;
			}
		} while(!check);
		
		gotoxy(x1+15, y1+11);
		SetColor(COLOR_BG_DEFAULT);
		wcout<<"GIO CO 60 PHUT";
		gotoxy(x1+21, y1+10);
		SetColor(COLOR_TEXT_DEFAULT);
		wcout<<setw(2)<<setfill((wchar_t)'0')<<right<<phut;
		
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
				// hieu chinh ng khoi hanh
				ngKhoiHanh.setGio(atoi(gio));
				ngKhoiHanh.setNgay(atoi(ngay));
				ngKhoiHanh.setPhut(atoi(phut));
				ngKhoiHanh.setNam(atoi(nam));
				ngKhoiHanh.setThang(atoi(thang));
				gotoxy(x1+6, y1+12);
				SetColor(COLOR_SUCCESS);
				SetBGColor(COLOR_BG_DEFAULT);
				wcout<<"SUA THANH CONG! NHAN PHIM BAT KI";
				getch();
				gotoxy(x1+6, y1+12);
				SetColor(COLOR_BG_DEFAULT);
				SetBGColor(COLOR_BG_DEFAULT);
				wcout<<"SUA THANH CONG! NHAN PHIM BAT KI";
				return;
		}
	}	
}

void ChuyenBay::capNhatSTT(Date &now){
	if(ngKhoiHanh.nhoHonBang(now)){
		trangThai = HOAN_TAT;
	}
}

int ChuyenBay::coHanhKhach(char* CMND){
	for(int i=0; i<soVe; i++){
		if(strcmpi(dsVe[i], CMND)==0)
			return 1;
	}
	return 0;
}

void ChuyenBay::inCBtheoNgay(short& x, short &y, int &stt){
	SetBGColor(COLOR_BG_DEFAULT);
	SetColor(COLOR_TEXT_DEFAULT);
	gotoxy(x+3, y);
	wcout<<stt;
	
	gotoxy(x+14, y);
	wcout<<maCB;
	
	gotoxy(x+33, y);
	wcout<<sanBayDen;
	
	gotoxy(x+53, y);
	ngKhoiHanh.xuatGio();
		
	gotoxy(x+65, y);
	wcout<<soVeConTrong();
		
	gotoxy(x, y);
	wcout<<LR_LINE;
	gotoxy(x+7, y);
	wcout<<LR_LINE;
	gotoxy(x+28, y);
	wcout<<LR_LINE;
	gotoxy(x+49, y);
	wcout<<LR_LINE;
	gotoxy(x+61, y);
	wcout<<LR_LINE;
	gotoxy(x+70, y);
	wcout<<LR_LINE;

		
	gotoxy(x, y+1);
	wcout<<LR_LINE;
	gotoxy(x+7, y+1);
	wcout<<LR_LINE;
	gotoxy(x+28, y+1);
	wcout<<LR_LINE;
	gotoxy(x+49, y+1);
	wcout<<LR_LINE;
	gotoxy(x+61, y+1);
	wcout<<LR_LINE;
	gotoxy(x+70, y+1);
	wcout<<LR_LINE;
		
	y=y+2;
	stt++;
}
