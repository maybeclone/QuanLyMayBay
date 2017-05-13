#include "DSMB.h"

DSMB::DSMB(int msCB){
	this->size = size;
}

int DSMB::isDuplicate(char* soHieu){
	for(int i=0; i<size; i++){
		if(strcmpi(ds[i].getSoHieu(), soHieu)==0)
			return 1;
	}
	return 0;
}

int DSMB::insert(MayBay newMB){
	if(size==MAX_MB || isDuplicate(newMB.getSoHieu())) return 0;
	ds[size] = newMB;
	return size++;
}

void DSMB::xuat(){
	if(size==0){
		cout<<"Danh Sach rong"<<endl;
		return;
	}
		
	for(int i=0; i<size; i++){
		ds[i].xuat();
	}	
}

int DSMB::getSize(){
	return size;
}

MayBay* DSMB::getMayBay(int position){
	if(position<0 || position>=size)
		return NULL;
	return &ds[position];
}

MayBay* DSMB::getMayBay(char* soHieu){
	for(int i=0; i<size; i++){
		if(strcmp(ds[i].getSoHieu(), soHieu)==0){
			return &ds[i];
		}
	}
	return NULL;
}

void DSMB::delAtPosition(int position){
	for(int i=position; i<size; i++){
		ds[i] = ds[i+1];
	}
	size--;
}

int DSMB::del(char* soHieu){
	for(int i=0; i<size; i++){
		if((strcmp(ds[i].getSoHieu(), soHieu)==0)){
			delAtPosition(i);
			return 1;
		}
	}
	return 0;
}

int DSMB::update(char* soHieu){
	for(int i=0; i<size; i++){
		if(strcmp(ds[i].getSoHieu(), soHieu)==0 && ds[i].checkTrangThai()){
			char soHieu[MAX_SOHIEU_MB];
			int soCho;
			cout<<"So Hieu: ";
			cin.getline(soHieu, MAX_SOHIEU_MB);
			cout<<"So Cho: ";
			cin>>soCho;
			ds[i].setSoCho(soCho);
			ds[i].setSoHieu(soHieu);
			return 1;
		}
	}
	return 0;
}

void DSMB::DHnhapMB(short x1, short y1, short x2, short y2){

	char soHieu[MAX_SOHIEU_MB];
	char soCho[4];
	int check;
	
	SetBGColor(COLOR_BG_DEFAULT);
	SetColor(COLOR_TEXT_DEFAULT);
	
	veKhung(x1, y1, x2, y2);
	
	SetColor(COLOR_HIGHLIGHT_TEXT);
	gotoxy(x1+8, y1+4);
	wcout<<"So Hieu: ";
	gotoxy(x1+8, y1+8);
	wcout<<"So Cho: ";

	short x[2] = {x1+7, x1+26};
	short y[2] = {y1+12, y1+12};
	short CD = 15;
	short CR = 3;
	
	char menu[2][15] = {"Xoa Het",
						"Them MB"}; 
	
	while(true){
		ShowCur(true);
		SetBGColor(COLOR_BG_ITEM);
		SetColor(COLOR_TEXT_ITEM);
		veKhungItem(x[0], y[0], x[0]+CD, y[0]+CR);
		gotoxy(x[0]+(CD/3), y[0]+1); wcout<<menu[0];
		veKhungItem(x[1], y[1], x[1]+CD, y[1]+CR);
		gotoxy(x[1]+(CD/3), y[1]+1); wcout<<menu[1];
		SetBGColor(COLOR_BG_DEFAULT);
		do{
			SetColor(COLOR_TEXT_DEFAULT);
			gotoxy(x1+17, y1+4);
			fflush(stdin);
			if(nhapMa(soHieu, MAX_SOHIEU_MB)==ESC)
				return;
			check = isDuplicate(soHieu);
			if(check){
				gotoxy(x1+14, y1+6);
				SetColor(COLOR_WARRING);
				wcout<<"MAY BAY DA TON TAI!";
				gotoxy(x1+17, y1+4);
				SetColor(COLOR_BG_DEFAULT);
				wcout<<soHieu;
			}
		} while(check);
		
		gotoxy(x1+14, y1+6);
		SetColor(COLOR_BG_DEFAULT);
		wcout<<"MAY BAY DA TON TAI!";	
		SetColor(COLOR_TEXT_DEFAULT);
		do{
			gotoxy(x1+17, y1+8);
			fflush(stdin);
			SetColor(COLOR_TEXT_DEFAULT);
			if(nhapSo(soCho, 4)==ESC){
				return;
			}
			if(atoi(soCho)>MAX_SOCHO){
				gotoxy(x1+14, y1+9);
				SetColor(COLOR_WARRING);
				wcout<<"SO CHO PHAI <= "<<MAX_SOCHO;
				gotoxy(x1+17, y1+8);
				SetColor(COLOR_BG_DEFAULT);
				wcout<<soCho;
					
			}
		} while(atoi(soCho)>MAX_SOCHO);
		gotoxy(x1+14, y1+9);
		SetColor(COLOR_BG_DEFAULT);
		wcout<<"SO CHO PHAI <= "<<MAX_SOCHO;
	
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
				MayBay mb(soHieu, atoi(soCho));
				insert(mb);
				gotoxy(x1+8, y1+10);
				SetColor(COLOR_SUCCESS);
				SetBGColor(COLOR_BG_DEFAULT);
				wcout<<"THEM THANH CONG! NHAN PHIM BAT KI";
				getch();
				gotoxy(x1+8, y1+10);
				SetColor(COLOR_BG_DEFAULT);
				SetBGColor(COLOR_BG_DEFAULT);
				wcout<<"THEM THANH CONG! NHAN PHIM BAT KI";
				break;
		}
		SetColor(COLOR_BG_DEFAULT);
		SetBGColor(COLOR_BG_DEFAULT);
		gotoxy(x1+17, y1+4);
		wcout<<soHieu;
		gotoxy(x1+17, y1+8);
		wcout<<soCho;
	}
}

void DSMB::write(ofstream& fout){
	fout.write((char*) &size, sizeof(int));
	NodeCB* temp;
	for(int i=0; i<size; i++){
		temp = ds[i].getFirst();
		
		/* Khu con tro first. Trc khi luu FILE.
		Luu xong dlieu MayBay tra con tro ve de luu CB.*/
		ds[i].setFirst(NULL);
		fout.write((char*) &ds[i], sizeof(MayBay));
		ds[i].setFirst(temp);
	
		ds[i].writeCB(fout);
	}
}

void DSMB::read(ifstream& fin){
	int dem = 0;
	fin.read((char*) &dem, sizeof(int));
	MayBay newMB;
	while(dem>0){
		fin.read((char*) &newMB, sizeof(MayBay));
		newMB.readCB(fin);
		insert(newMB);
		dem--;
	}
}

void DSMB::DHxuatMB(short x, short y, int selection){
	int start = (selection-1)*10;
	int end = (selection*10<=size) ? selection*10 : size;
	
	//xoa
	ShowCur(false);
	SetBGColor(COLOR_BG_DEFAULT);
	SetColor(COLOR_BG_DEFAULT);
	short temp = y;
	for(int i=0; i<10; i++){
		gotoxy(x+4, temp);
		wcout<<"       ";
		gotoxy(x+20, temp);
		wcout<<"          ";
		gotoxy(x+40, temp);
		wcout<<"         ";
		temp = temp+2;
	}

	SetColor(COLOR_TEXT_DEFAULT);
	for(int i=start; i<end; i++){
		gotoxy(x+6, y);
		wcout<<i+1;
		gotoxy(x+22, y);
		wcout<<ds[i].getSoHieu();
		gotoxy(x+42, y);
		wcout<<ds[i].getSoCho();
		y = y+2;
	}
	ShowCur(true);
}

void DSMB::DHgetMB(short x1, short y1, short x2, short y2){

	float sale[2] = {0.25, 0.5};
	//col-1
	veTable(2, sale, x1, y1, x2, y2);

	gotoxy(x1+10, y1-2);
	SetBGColor(COLOR_BG_DEFAULT);
	SetColor(COLOR_HIGHLIGHT_TEXT);
	wcout<<"So Hieu:";
	
	SetColor(COLOR_TEXT_DEFAULT);
	// Tieu de
	gotoxy(x1+5, y1+1);
	wcout<<"STT";
	gotoxy(x1+20, y1+1);
	wcout<<"So Hieu MB";
	gotoxy(x1+42, y1+1);
	wcout<<"So Cho";
	
	// tinh vs in so trang
	int soTrang = tinhSoTrang(size);
	
	int x_td = (x1+x2)/2;
	for(int i=1; i<=soTrang; i++){
		gotoxy(x_td-soTrang+3*i-2, y2+1);
		wcout<<i;
	}
	if(soTrang>0){
		SetBGColor(COLOR_BG_ITEM_SELECTED);
		SetColor(COLOR_TEXT_ITEM_SELECTED);
		gotoxy(x_td-soTrang+1, y2+1);   wcout<<1;	
	}
	int selection=1;
	while(true){
		int n=0;
		char soHieu[MAX_SOHIEU_MB];
		DHxuatMB(x1, y1+3, selection);
		short x = x1+20;
		short y = y1-2;
		char c;
		ShowCur(true);
		while(true){
			SetBGColor(COLOR_BG_DEFAULT);
			SetColor(COLOR_TEXT_DEFAULT);
			gotoxy(x, y);
			c=getch();
			int check = checkMa_DEMO(soHieu, MAX_SOHIEU_MB, n, c);
			if(check==3){
				x--;
				gotoxy(x, y);
				wcout<<" ";
				gotoxy(x, y);	
			}else if(check==1){
				wcout<<c;
				x++;	
			} else if(c==ESC){
				xoaKhung(x1, y1-2, x2, y2+1);
				ShowCur(false);
				return;
			} else if(check==PAGE_UP && soTrang>1){
				SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_TEXT_DEFAULT);
				gotoxy(x_td-soTrang+3*selection-2, y2+1);   wcout<<selection;
				selection++;
				if(selection>soTrang)
					selection = 1;
				DHxuatMB(x1, y1+3, selection);
				SetBGColor(COLOR_BG_ITEM_SELECTED);
				SetColor(COLOR_TEXT_ITEM_SELECTED);
				gotoxy(x_td-soTrang+3*selection-2, y2+1);   wcout<<selection;
			} else if(check==PAGE_DOWN && soTrang>1){
				SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_TEXT_DEFAULT);
				gotoxy(x_td-soTrang+3*selection-2, y2+1);   wcout<<selection;
				selection--;
				if(selection==0)
					selection = soTrang;
				DHxuatMB(x1, y1+3, selection);
				SetBGColor(COLOR_BG_ITEM_SELECTED);
				SetColor(COLOR_TEXT_ITEM_SELECTED);
				gotoxy(x_td-soTrang+3*selection-2, y2+1);   wcout<<selection;
			}
			if(c==ENTER && n!=0)
				break;
		}
		soHieu[n] = '\0';
		MayBay* mb = getMayBay(soHieu);
		if(mb == NULL){
			gotoxy(x1+15, y1-1);
			SetBGColor(COLOR_BG_DEFAULT);
			SetColor(COLOR_WARRING);
			wcout<<"KHONG TIM THAY MAY BAY";
			gotoxy(x1+20, y1-2);
			SetBGColor(COLOR_BG_DEFAULT);
			SetColor(COLOR_BG_DEFAULT);
			wcout<<soHieu;
		} else {
			xoaKhung(x1, y1-2, x2, y2+1);
			ShowCur(false);
			DH_MBthemCB(mb, x1+2, y1, x2-2, y2-1);
			ShowCur(false);
			xoaKhung(x1+2, y1, x2-2, y2-1);
			return;
		}
	}
}


int DSMB::isDuplicateCB_All(char* maCB){
	for(int i=0; i<getSize(); i++){
		if(getMayBay(i)->isDuplicateCB(maCB))
			return 1;
	}
	return 0;
}

void DSMB::DH_MBthemCB(MayBay* mb, short x1, short y1, short x2, short y2){
	SetColor(COLOR_TEXT_DEFAULT);
	SetBGColor(COLOR_BG_DEFAULT);
	veKhung(x1, y1, x2, y2);
	
	SetColor(COLOR_HIGHLIGHT_TEXT);
	gotoxy(x1+4, y1+3);
	wcout<<"Ma Chuyen Bay:";
	gotoxy(x1+4, y1+6);
	wcout<<"San Bay Den:";
	gotoxy(x1+4, y1+9);
	wcout<<"Ngay Khoi Hanh:";
	gotoxy(x1+4, y1+12);
	wcout<<"Gio Khoi Hanh:";
	
	SetColor(COLOR_TEXT_DEFAULT);
	gotoxy(x1+35, y1+9);
	wcout<<"YYYY/MM/DD";
	gotoxy(x1+35, y1+12);
	wcout<<"HH:mm";
	
	short x[2] = {x1+7, x1+25};
	short y[2] = {y1+16, y1+16};
	short CD = 15;
	short CR = 3;
	char menu[2][10] = {"Xoa Het",
						"Them CB"};
	int check;
	
	char maCB[MAX_MA_CB];
	char sanBayDen[MAX_SAN_BAY];
	char nam[5], thang[3], ngay[3], gio[3], phut[3];
	
	while(true){
		SetBGColor(COLOR_BG_ITEM);
		SetColor(COLOR_TEXT_ITEM);
		veKhungItem(x[0], y[0], x[0]+CD, y[0]+CR);
		gotoxy(x[0]+(CD/3), y[0]+1); wcout<<menu[0];
		veKhungItem(x[1], y[1], x[1]+CD, y[1]+CR);
		gotoxy(x[1]+(CD/3), y[1]+1); wcout<<menu[1];
		
		SetBGColor(COLOR_BG_DEFAULT);
		ShowCur(true);
		do{
			SetColor(COLOR_TEXT_DEFAULT);
			gotoxy(x1+20, y1+3);
			fflush(stdin);
			if(nhapMa(maCB, MAX_MA_CB)==ESC)
				return;
			check = isDuplicateCB_All(maCB);
			if(check){
				SetColor(COLOR_WARRING);
				gotoxy(x1+10, y1+4);
				wcout<<"MA CHUYEN BAY DA TON TAI!";
				gotoxy(x1+20, y1+3);
				SetColor(COLOR_BG_DEFAULT);
				wcout<<maCB;
			}	
		} while(check);
		SetColor(COLOR_BG_DEFAULT);
		gotoxy(x1+10, y1+4);
		wcout<<"MA CHUYEN BAY DA TON TAI!";

		SetColor(COLOR_TEXT_DEFAULT);
		gotoxy(x1+20, y1+6);
		fflush(stdin);
		if(nhapTen(sanBayDen, MAX_SAN_BAY)==ESC)
			return;
		gotoxy(x1+20, y1+9);
		wcout<<"    /  / ";
		// get cur time vs date
		time_t  theTime = time(NULL);
		struct tm *aTime = localtime(&theTime);
		int cur_nam = aTime->tm_year+1900;
		int cur_thang = aTime->tm_mon+1;
		int cur_ngay = aTime->tm_mday;
		do{
			SetColor(COLOR_TEXT_DEFAULT);
			gotoxy(x1+20, y1+9);
			fflush(stdin);
			if(nhapSo(nam, 5)==ESC)
				return;
			check = checkNam(atoi(nam), cur_nam);
			if(!check){
				gotoxy(x1+10, y1+10);
				SetColor(COLOR_WARRING);
				wcout<<"NAM PHAI >= "<<cur_nam<<" VA <= "<<MAX_NAM;
				gotoxy(x1+20, y1+9);
				SetColor(COLOR_BG_DEFAULT);
				wcout<<nam;
			}
		} while(!check);
		gotoxy(x1+10, y1+10);
		SetColor(COLOR_BG_DEFAULT);
		wcout<<"NAM PHAI >= "<<cur_nam<<" VA <= "<<MAX_NAM;

		do{	
			SetColor(COLOR_TEXT_DEFAULT);
			gotoxy(x1+25, y1+9);
			fflush(stdin);
			if(nhapSo(thang, 3)==ESC)
				return;
			check = checkThang(atoi(nam), atoi(thang), cur_nam, cur_thang);
			if(check == -1){
				gotoxy(x1+10, y1+10);
				SetColor(COLOR_BG_DEFAULT);
				wcout<<"                                     ";
				gotoxy(x1+10, y1+10);
				SetColor(COLOR_WARRING);
				wcout<<"THANG PHAI >= THANG "<<cur_thang<<" NAM "<<cur_nam;
				gotoxy(x1+25, y1+9);
				SetColor(COLOR_BG_DEFAULT);
				wcout<<thang;
			} else if(check == 0){
				gotoxy(x1+10, y1+10);
				SetColor(COLOR_BG_DEFAULT);
				wcout<<"                                     ";
				gotoxy(x1+15, y1+10);
				SetColor(COLOR_WARRING);
				wcout<<"NAM CO 12 THANG";
				gotoxy(x1+25, y1+9);
				SetColor(COLOR_BG_DEFAULT);
				wcout<<thang;
			}
		} while(check!=1);
	
		gotoxy(x1+25, y1+9);
		SetColor(COLOR_TEXT_DEFAULT);
		wcout<<setw(2)<<setfill((wchar_t)'0')<<right<<thang; 
		
		gotoxy(x1+10, y1+10);
		SetColor(COLOR_BG_DEFAULT);
		wcout<<"                                     ";
		
		do{
			SetColor(COLOR_TEXT_DEFAULT);
			gotoxy(x1+28, y1+9);
			fflush(stdin);
			if(nhapSo(ngay, 3)==ESC)
				return;
			check = checkNgay(atoi(nam), atoi(thang), atoi(ngay), cur_nam, cur_thang, cur_ngay);
			if(check==0){
				gotoxy(x1+10, y1+10);
				SetColor(COLOR_BG_DEFAULT);
				wcout<<"                                    ";
				gotoxy(x1+10, y1+10);
				SetColor(COLOR_WARRING);
				wcout<<"NGAY PHAI > NGAY "<<cur_ngay<<" THANG "<<cur_thang;
				gotoxy(x1+28, y1+9);
				SetColor(COLOR_BG_DEFAULT);
				wcout<<ngay;
			} else if(check>=28){
				gotoxy(x1+10, y1+10);
				SetColor(COLOR_BG_DEFAULT);
				wcout<<"                                    ";
				gotoxy(x1+15, y1+10);
				SetColor(COLOR_WARRING);
				wcout<<"THANG "<<thang<<" CO "<<check<<" NGAY ";
				gotoxy(x1+28, y1+9);
				SetColor(COLOR_BG_DEFAULT);
				wcout<<ngay;
			}
		} while(check!=1);
		
		gotoxy(x1+28, y1+9);
		SetColor(COLOR_TEXT_DEFAULT);
		wcout<<setw(2)<<setfill((wchar_t)'0')<<right<<ngay; 
		
		gotoxy(x1+10, y1+10);
		SetColor(COLOR_BG_DEFAULT);
		wcout<<"                                    ";
	
		SetColor(COLOR_TEXT_DEFAULT);
		gotoxy(x1+22, y1+12);
		wcout<<":";
		
		do{
			SetColor(COLOR_TEXT_DEFAULT);
			gotoxy(x1+20, y1+12);
			fflush(stdin);
			if(nhapSo(gio, 3)==ESC)
				return;
			check = checkGio(atoi(gio));
			if(!check){
				gotoxy(x1+15, y1+13);
				SetColor(COLOR_WARRING);
				wcout<<"NGAY CO 24 GIO";
				gotoxy(x1+20, y1+12);
				SetColor(COLOR_BG_DEFAULT);
				wcout<<gio;
			}
		} while(!check);
		
		gotoxy(x1+20, y1+12);
		SetColor(COLOR_TEXT_DEFAULT);
		wcout<<setw(2)<<setfill((wchar_t)'0')<<right<<gio; 
		gotoxy(x1+15, y1+13);
		SetColor(COLOR_BG_DEFAULT);
		wcout<<"NGAY CO 24 GIO";
		
		do{
			SetColor(COLOR_TEXT_DEFAULT);
			gotoxy(x1+23, y1+12);
			fflush(stdin);
			if(nhapSo(phut, 3)==ESC)
				return;
			check = checkPhut(atoi(phut));
			if(!check){
				gotoxy(x1+15, y1+13);
				SetColor(COLOR_WARRING);
				wcout<<"GIO CO 60 PHUT";
				gotoxy(x1+23, y1+12);
				SetColor(COLOR_BG_DEFAULT);
				wcout<<phut;
			}
		} while(!check);
		
		gotoxy(x1+15, y1+13);
		SetColor(COLOR_BG_DEFAULT);
		wcout<<"GIO CO 60 PHUT";
		gotoxy(x1+23, y1+12);
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
				// tao chuyen bay vs insert
				Date date(atoi(gio), atoi(phut), atoi(ngay), atoi(thang), atoi(nam));
				ChuyenBay cb(maCB, sanBayDen, mb->getSoCho(), date);
				mb->insert(cb);
				gotoxy(x1+8, y1+14);
				SetColor(COLOR_SUCCESS);
				SetBGColor(COLOR_BG_DEFAULT);
				wcout<<"THEM THANH CONG! NHAN PHIM BAT KI";
				getch();
				gotoxy(x1+8, y1+14);
				SetColor(COLOR_BG_DEFAULT);
				SetBGColor(COLOR_BG_DEFAULT);
				wcout<<"THEM THANH CONG! NHAN PHIM BAT KI";
				break;
		}
		SetColor(COLOR_BG_DEFAULT);
		SetBGColor(COLOR_BG_DEFAULT);
		gotoxy(x1+20, y1+3);
		wcout<<maCB;
		gotoxy(x1+20, y1+6);
		wcout<<sanBayDen;
		gotoxy(x1+20, y1+9);
		wcout<<"    /  /  ";
		gotoxy(x1+20, y1+12);
		wcout<<"  :  ";
	}	
}

int DSMB::timkiemMBcoSB(char* sanBay){
	for(int i=0; i<size; i++){
		if(ds[i].timKiemSanBayDen(sanBay)){
			return 1;
		}
	}
	return 0;
}

ChuyenBay* DSMB::getCBcuaMB(char* maCB, char* sanBay){
	ChuyenBay* cb;
	for(int i=0 ; i<size; i++){
		cb = ds[i].getCBtheoSanBay(maCB, sanBay);
		if(cb!=NULL){
			return cb;
		}
	}
	return NULL;
}

void DSMB::DHsuaMB(short x1, short y1, short x2, short y2){
	float sale[2] = {0.25, 0.5};
	//col-1
	veTable(2, sale, x1, y1, x2, y2);

	gotoxy(x1+10, y1-2);
	SetBGColor(COLOR_BG_DEFAULT);
	SetColor(COLOR_HIGHLIGHT_TEXT);
	wcout<<"So Hieu:";
	
	SetColor(COLOR_TEXT_DEFAULT);
	// Tieu de
	gotoxy(x1+5, y1+1);
	wcout<<"STT";
	gotoxy(x1+20, y1+1);
	wcout<<"So Hieu MB";
	gotoxy(x1+42, y1+1);
	wcout<<"So Cho";
	
	// tinh vs in so trang
	int soTrang = tinhSoTrang(size);
	
	int x_td = (x1+x2)/2;
	for(int i=1; i<=soTrang; i++){
		gotoxy(x_td-soTrang+3*i-2, y2+1);
		wcout<<i;
	}
	if(soTrang>0){
		SetBGColor(COLOR_BG_ITEM_SELECTED);
		SetColor(COLOR_TEXT_ITEM_SELECTED);
		gotoxy(x_td-soTrang+1, y2+1);   wcout<<1;	
	}
	int selection=1;
	while(true){
		int n=0;
		char soHieu[MAX_SOHIEU_MB];
		DHxuatMB(x1, y1+3, selection);
		short x = x1+20;
		short y = y1-2;
		char c;
		ShowCur(true);
		while(true){
			SetBGColor(COLOR_BG_DEFAULT);
			SetColor(COLOR_TEXT_DEFAULT);
			gotoxy(x, y);
			c=getch();
			int check = checkMa_DEMO(soHieu, MAX_SOHIEU_MB, n, c);
			if(check==3){
				x--;
				gotoxy(x, y);
				wcout<<" ";
				gotoxy(x, y);	
			}else if(check==1){
				wcout<<c;
				x++;	
			} else if(c==ESC){
				xoaKhung(x1, y1-2, x2, y2+1);
				ShowCur(false);
				return;
			} else if(check==PAGE_UP && soTrang>1){
				SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_TEXT_DEFAULT);
				gotoxy(x_td-soTrang+3*selection-2, y2+1);   wcout<<selection;
				selection++;
				if(selection>soTrang)
					selection = 1;
				DHxuatMB(x1, y1+3, selection);
				SetBGColor(COLOR_BG_ITEM_SELECTED);
				SetColor(COLOR_TEXT_ITEM_SELECTED);
				gotoxy(x_td-soTrang+3*selection-2, y2+1);   wcout<<selection;
			} else if(check==PAGE_DOWN && soTrang>1){
				SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_TEXT_DEFAULT);
				gotoxy(x_td-soTrang+3*selection-2, y2+1);   wcout<<selection;
				selection--;
				if(selection==0)
					selection = soTrang;
				DHxuatMB(x1, y1+3, selection);
				SetBGColor(COLOR_BG_ITEM_SELECTED);
				SetColor(COLOR_TEXT_ITEM_SELECTED);
				gotoxy(x_td-soTrang+3*selection-2, y2+1);   wcout<<selection;
			}
			if(c==ENTER && n!=0)
				break;
		}
		soHieu[n] = '\0';
		MayBay* mb = getMayBay(soHieu);
		if(mb == NULL){
			gotoxy(x1+15, y1-1);
			SetBGColor(COLOR_BG_DEFAULT);
			SetColor(COLOR_WARRING);
			wcout<<"KHONG TIM THAY MAY BAY ";
			gotoxy(x1+20, y1-2);
			SetBGColor(COLOR_BG_DEFAULT);
			SetColor(COLOR_BG_DEFAULT);
			wcout<<soHieu;
		} else {
			if(!mb->checkTrangThai()){
				gotoxy(x1+15, y1-1);
				SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_WARRING);
				wcout<<"MAY BAY KHONG THE SUA ";
				gotoxy(x1+20, y1-2);
				SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_BG_DEFAULT);
				wcout<<soHieu;
			} else{
				xoaKhung(x1, y1-2, x2, y2+1);
				ShowCur(false);
				DHsuaTT_MB(x1, y1+2, x2, y2-4, mb);
				xoaKhung(x1, y1+2, x2, y2-4);
				return;			
			}
		}
	}		
}

void DSMB::DHsuaTT_MB(short x1, short y1, short x2, short y2, MayBay* mb){
	char soHieu[MAX_SOHIEU_MB];
	char soCho[4];
	
	SetBGColor(COLOR_BG_DEFAULT);
	SetColor(COLOR_TEXT_DEFAULT);
	
	veKhung(x1, y1, x2, y2);
	
	SetColor(COLOR_HIGHLIGHT_TEXT);
	gotoxy(x1+8, y1+4);
	wcout<<"So Hieu: ";
	gotoxy(x1+8, y1+8);
	wcout<<"So Cho: ";
	

	short x[2] = {x1+7, x1+26};
	short y[2] = {y1+12, y1+12};
	short CD = 15;
	short CR = 3;
	
	char menu[2][15] = {"Xoa Het",
						"Sua MB"}; 
	
	while(true){
		int check=0;
		SetColor(COLOR_TEXT_DEFAULT);
		strcpy(soHieu, mb->getSoHieu());
		itoa(mb->getSoCho(), soCho, 10);
		gotoxy(x1+17, y1+4);
		wcout<<soHieu;
		gotoxy(x1+17, y1+8);
		wcout<<soCho;
		ShowCur(true);
		SetBGColor(COLOR_BG_ITEM);
		SetColor(COLOR_TEXT_ITEM);
		veKhungItem(x[0], y[0], x[0]+CD, y[0]+CR);
		gotoxy(x[0]+(CD/3), y[0]+1); wcout<<menu[0];
		veKhungItem(x[1], y[1], x[1]+CD, y[1]+CR);
		gotoxy(x[1]+(CD/3), y[1]+1); wcout<<menu[1];
		SetBGColor(COLOR_BG_DEFAULT);
		do{
			if(check){
				strcpy(soHieu,"");
			}
			SetColor(COLOR_TEXT_DEFAULT);
			gotoxy(x1+17+strlen(soHieu), y1+4);
			fflush(stdin);
			if(nhapMa_EDIT(soHieu, MAX_SOHIEU_MB, strlen(soHieu))==ESC)
				return;
			check = isDuplicate(soHieu);
			if(check && strcmpi(soHieu, mb->getSoHieu())!=0){
				gotoxy(x1+14, y1+6);
				SetColor(COLOR_WARRING);
				wcout<<"MAY BAY DA TON TAI!";
				gotoxy(x1+17, y1+4);
				SetColor(COLOR_BG_DEFAULT);
				wcout<<soHieu;
			}
		} while(check && strcmpi(soHieu, mb->getSoHieu())!=0);
		
		gotoxy(x1+14, y1+6);
		SetColor(COLOR_BG_DEFAULT);
		wcout<<"MAY BAY DA TON TAI!";	
		SetColor(COLOR_TEXT_DEFAULT);
		do{
			if(atoi(soCho)>MAX_SOCHO){
				strcpy(soCho, "");
			}
			gotoxy(x1+17+strlen(soCho), y1+8);
			fflush(stdin);
			SetColor(COLOR_TEXT_DEFAULT);
			if(nhapSo_EDIT(soCho, 4, strlen(soCho))==ESC){
				return;
			}
			if(atoi(soCho)>MAX_SOCHO){
				gotoxy(x1+14, y1+9);
				SetColor(COLOR_WARRING);
				wcout<<"SO CHO PHAI <= "<<MAX_SOCHO;
				gotoxy(x1+17, y1+8);
				SetColor(COLOR_BG_DEFAULT);
				wcout<<soCho;
			}
		} while(atoi(soCho)>MAX_SOCHO);
		gotoxy(x1+14, y1+9);
		SetColor(COLOR_BG_DEFAULT);
		wcout<<"SO CHO PHAI <= "<<MAX_SOCHO;
	
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
				mb->setSoCho(atoi(soCho));
				mb->setSoHieu(soHieu);
				gotoxy(x1+8, y1+10);
				SetColor(COLOR_SUCCESS);
				SetBGColor(COLOR_BG_DEFAULT);
				wcout<<"SUA THANH CONG! NHAN PHIM BAT KI";
				getch();
				gotoxy(x1+8, y1+10);
				SetColor(COLOR_BG_DEFAULT);
				SetBGColor(COLOR_BG_DEFAULT);
				wcout<<"SUA THANH CONG! NHAN PHIM BAT KI";
				return;
		}
		SetColor(COLOR_BG_DEFAULT);
		SetBGColor(COLOR_BG_DEFAULT);
		gotoxy(x1+17, y1+4);
		wcout<<soHieu;
		gotoxy(x1+17, y1+8);
		wcout<<soCho;
	}	
}

void DSMB::DHxoaMB(short x1, short y1, short x2, short y2){
	float sale[2] = {0.25, 0.5};
	//col-1
	veTable(2, sale, x1, y1, x2, y2);

	gotoxy(x1+10, y1-2);
	SetBGColor(COLOR_BG_DEFAULT);
	SetColor(COLOR_HIGHLIGHT_TEXT);
	wcout<<"So Hieu:";
	
	SetColor(COLOR_TEXT_DEFAULT);
	// Tieu de
	gotoxy(x1+5, y1+1);
	wcout<<"STT";
	gotoxy(x1+20, y1+1);
	wcout<<"So Hieu MB";
	gotoxy(x1+42, y1+1);
	wcout<<"So Cho";
	
	// tinh vs in so trang
	int soTrang = tinhSoTrang(size);
	
	int x_td = (x1+x2)/2;
	for(int i=1; i<=soTrang; i++){
		gotoxy(x_td-soTrang+3*i-2, y2+1);
		wcout<<i;
	}
	if(soTrang>0){
		SetBGColor(COLOR_BG_ITEM_SELECTED);
		SetColor(COLOR_TEXT_ITEM_SELECTED);
		gotoxy(x_td-soTrang+1, y2+1);   wcout<<1;	
	}
	int selection=1;
	while(true){
		int n=0;
		char soHieu[MAX_SOHIEU_MB];
		DHxuatMB(x1, y1+3, selection);
		short x = x1+20;
		short y = y1-2;
		char c;
		ShowCur(true);
		while(true){
			SetBGColor(COLOR_BG_DEFAULT);
			SetColor(COLOR_TEXT_DEFAULT);
			gotoxy(x, y);
			c=getch();
			int check = checkMa_DEMO(soHieu, MAX_SOHIEU_MB, n, c);
			if(check==3){
				x--;
				gotoxy(x, y);
				wcout<<" ";
				gotoxy(x, y);	
			}else if(check==1){
				wcout<<c;
				x++;	
			} else if(c==ESC){
				xoaKhung(x1, y1-2, x2, y2+1);
				ShowCur(false);
				return;
			} else if(check==PAGE_UP && soTrang>1){
				SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_TEXT_DEFAULT);
				gotoxy(x_td-soTrang+3*selection-2, y2+1);   wcout<<selection;
				selection++;
				if(selection>soTrang)
					selection = 1;
				DHxuatMB(x1, y1+3, selection);
				SetBGColor(COLOR_BG_ITEM_SELECTED);
				SetColor(COLOR_TEXT_ITEM_SELECTED);
				gotoxy(x_td-soTrang+3*selection-2, y2+1);   wcout<<selection;
			} else if(check==PAGE_DOWN && soTrang>1){
				SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_TEXT_DEFAULT);
				gotoxy(x_td-soTrang+3*selection-2, y2+1);   wcout<<selection;
				selection--;
				if(selection==0)
					selection = soTrang;
				DHxuatMB(x1, y1+3, selection);
				SetBGColor(COLOR_BG_ITEM_SELECTED);
				SetColor(COLOR_TEXT_ITEM_SELECTED);
				gotoxy(x_td-soTrang+3*selection-2, y2+1);   wcout<<selection;
			}
			if(c==ENTER && n!=0)
				break;
		}
		soHieu[n] = '\0';
		MayBay* mb = getMayBay(soHieu);
		if(mb == NULL){
			gotoxy(x1+15, y1-1);
			SetBGColor(COLOR_BG_DEFAULT);
			SetColor(COLOR_WARRING);
			wcout<<"KHONG TIM THAY MAY BAY ";
			gotoxy(x1+20, y1-2);
			SetBGColor(COLOR_BG_DEFAULT);
			SetColor(COLOR_BG_DEFAULT);
			wcout<<soHieu;
		} else {
			if(!mb->checkTrangThai()){
				gotoxy(x1+15, y1-1);
				SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_WARRING);
				wcout<<"MAY BAY KHONG THE XOA ";
				gotoxy(x1+20, y1-2);
				SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_BG_DEFAULT);
				wcout<<soHieu;
			} else{
				xoaKhung(x1, y1-2, x2, y2+1);
				ShowCur(false);
				DHxoaTT_MB(x1, y1+4, x2, y2-6, mb);
				xoaKhung(x1, y1+4, x2, y2-6);
				return;			
			}
		}
	}
}

void DSMB::DHxoaTT_MB(short x1, short y1, short x2, short y2, MayBay* mb){
	SetBGColor(COLOR_BG_DEFAULT);
	SetColor(COLOR_TEXT_DEFAULT);
	
	veKhung(x1, y1, x2, y2);

	gotoxy(x1+8, y1+2);
	SetColor(COLOR_WARRING);
	wcout<<"CHU Y:";
	gotoxy(x1+10, y1+4);
	SetColor(COLOR_TEXT_DEFAULT);
	wcout<<"Ban co chac muon xoa May Bay "<<mb->getSoHieu();
	
	short x[2] = {x1+7, x1+26};
	short y[2] = {y1+8, y1+8};
	short CD = 15;
	short CR = 3;
	
	char menu[2][15] = {"Khong",
						"Dong y"}; 
						
	SetBGColor(COLOR_BG_ITEM);
	SetColor(COLOR_TEXT_ITEM);
	veKhungItem(x[0], y[0], x[0]+CD, y[0]+CR);
	gotoxy(x[0]+(CD/3), y[0]+1); wcout<<menu[0];
	SetBGColor(COLOR_BG_DEFAULT);
	
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
			return;
		case 2:
			del(mb->getSoHieu());
			gotoxy(x1+10, y1+6);
			SetColor(COLOR_SUCCESS);
			SetBGColor(COLOR_BG_DEFAULT);
			wcout<<"XOA THANH CONG! NHAN PHIM BAT KI";
			getch();
			gotoxy(x1+10, y1+6);
			SetColor(COLOR_BG_DEFAULT);
			SetBGColor(COLOR_BG_DEFAULT);
			wcout<<"XOA THANH CONG! NHAN PHIM BAT KI";
			return;
	}
	
}

int DSMB::timCBdeSua_ALL(char* maCB, ChuyenBay* &cb){
	int check;
	for(int i=0; i<size; i++){
		check = ds[i].suaCB(maCB, cb);
		if(check == HUY){
			return HUY;
		} else if(check == HOAN_TAT){
			return HOAN_TAT;
		} else if(check == 10){
			return 10;
		}
	}
	return -1;
}

int DSMB::xoaCB_ALL(char* maCB){
	for(int i=0; i<size; i++){
		if(ds[i].xoaCB(maCB)){
			return i;
		}
	}
	return -1;
}

int DSMB::huyCB_ALL(char* maCB, ChuyenBay* &cb){
	for(int i=0; i<size; i++){
		if(ds[i].huyCB(maCB, cb)){
			return 1;
		}
	}
	return 0;
}

void DSMB::xemMB_ALL(short x1, short y1, short x2, short y2){
	float sale[2] = {0.25, 0.5};
	//col-1
	veTable(2, sale, x1, y1, x2, y2);
	
	SetColor(COLOR_TEXT_DEFAULT);
	// Tieu de
	gotoxy(x1+5, y1+1);
	wcout<<"STT";
	gotoxy(x1+20, y1+1);
	wcout<<"So Hieu MB";
	gotoxy(x1+42, y1+1);
	wcout<<"So Cho";
	
	// tinh vs in so trang
	int soTrang = tinhSoTrang(size);
	
	int x_td = (x1+x2)/2;
	for(int i=1; i<=soTrang; i++){
		gotoxy(x_td-soTrang+3*i-2, y2+1);
		wcout<<i;
	}
	if(soTrang>0){
		SetBGColor(COLOR_BG_ITEM_SELECTED);
		SetColor(COLOR_TEXT_ITEM_SELECTED);
		gotoxy(x_td-soTrang+1, y2+1);   wcout<<1;	
	}
	int selection=1;
	while(true){
		int n=0;
		char soHieu[MAX_SOHIEU_MB];
		DHxuatMB(x1, y1+3, selection);
		short x = x1+20;
		short y = y1-2;
		char c;
		while(true){
			ShowCur(false);
			SetBGColor(COLOR_BG_DEFAULT);
			SetColor(COLOR_TEXT_DEFAULT);
			c=getch();
			if(c==ESC){
				xoaKhung(x1, y1-2, x2, y2+1);
				ShowCur(false);
				return;
			} else if(c==PAGE_UP && soTrang>1){
				SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_TEXT_DEFAULT);
				gotoxy(x_td-soTrang+3*selection-2, y2+1);   wcout<<selection;
				selection++;
				if(selection>soTrang)
					selection = 1;
				DHxuatMB(x1, y1+3, selection);
				SetBGColor(COLOR_BG_ITEM_SELECTED);
				SetColor(COLOR_TEXT_ITEM_SELECTED);
				gotoxy(x_td-soTrang+3*selection-2, y2+1);   wcout<<selection;
			} else if(c==PAGE_DOWN && soTrang>1){
				SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_TEXT_DEFAULT);
				gotoxy(x_td-soTrang+3*selection-2, y2+1);   wcout<<selection;
				selection--;
				if(selection==0)
					selection = soTrang;
				DHxuatMB(x1, y1+3, selection);
				SetBGColor(COLOR_BG_ITEM_SELECTED);
				SetColor(COLOR_TEXT_ITEM_SELECTED);
				gotoxy(x_td-soTrang+3*selection-2, y2+1);   wcout<<selection;
			}
			if(c==ENTER && n!=0)
				break;
		}	
	}	
}

void DSMB::capNhatSTT_ALL(Date& now){
	for(int i=0; i<size; i++){
		ds[i].capNhatSTT(now);
	}
}

int DSMB::coHanhKhach_ALL(char* CMND){
	for(int i=0; i<size; i++){
		if(ds[i].coHanhKhach(CMND)==1){
			return 1;
		}
	}
	return 0;
}

ChuyenBay* DSMB::getCBinDSHK_ALL(char* maCB){
	ChuyenBay* cb;
	for(int i=0; i<size; i++){
		cb = ds[i].getCBinDSHK(maCB);
		if(cb!=NULL)
			return cb;
	}
	return NULL;
}

ChuyenBay* DSMB::getCBtheoMaCB(char* maCB){
	ChuyenBay* cb = NULL;
	for(int i=0; i<size; i++){
		cb = ds[i].getCB(maCB);
		if(cb!=NULL){
			return cb;
		}
	}
	return NULL;
}
