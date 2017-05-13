#include "MayBay.h"

MayBay::MayBay(){
	first = NULL;
}

MayBay::MayBay(char* soHieu, int soCho){
	strcpy(this->soHieu, soHieu);
	this->soCho = soCho;
	first = NULL;
}

MayBay::MayBay(char* soHieu, int soCho, NodeCB* first){
	strcpy(this->soHieu, soHieu);
	this->soCho = soCho;
	this->first = first;
}

MayBay::MayBay(MayBay& mb){
	strcpy(this->soHieu, mb.soHieu);
	soCho = mb.soCho;
	// kiem tra mb.first neu la NULL thi first = NULL khong thi sao chep dlieu
	if(mb.first==NULL){
		first = NULL;
	}
	// sao chep dlieu tu mb
	NodeCB* p = mb.first;
	first = NULL;
	while(p!=NULL){
		insert(p->cb);
		p = p->next;
	}
}

MayBay MayBay::operator=(MayBay& mb){
	strcpy(this->soHieu, mb.soHieu);
	soCho = mb.soCho;
	// kiem tra mb.first neu la NULL thi first = NULL khong thi sao chep dlieu
	if(mb.first==NULL){
		first = NULL;
	}
	first = NULL;
	// sao chep dlieu tu mb
	NodeCB* p = mb.first;
	while(p!=NULL){
		insert(p->cb);
		p = p->next;
	}
	return *this;
}

MayBay::~MayBay(){
	NodeCB* temp = NULL;
	while(first!=NULL){
		temp = first;
		first = first->next;
		delete temp;
	}
}

void MayBay::xuat(){
	wcout<<setw(MAX_SOHIEU_MB)<<left<<soHieu<<"\t"<<setw(3)<<left<<soCho<<endl;
	if(first!=NULL)
		xuatCB();
}

void MayBay::nhap(){
	fflush(stdin);
	cout<<"So Hieu: ";
	cin.getline(soHieu, MAX_SOHIEU_MB);
	cout<<"So Cho: ";
	cin>>soCho;
}

int MayBay::getSoCho(){
	return soCho;
}

char* MayBay::getSoHieu(){
	return soHieu;
}

void MayBay::setSoHieu(char* soHieu){
	strcpy(this->soHieu, soHieu);
}

void MayBay::setSoCho(int soCho){
	this->soCho = soCho;
}

int MayBay::checkTrangThai(){
	NodeCB* p = first;
	while(p!=NULL){
		int status = p->cb.getTrangThai();
		if(status!=HOAN_TAT && status !=HUY)
			return 0;
		p = p->next;
	}
	return 1;
}

void MayBay::insert(ChuyenBay& newCB){
	if(first==NULL){
		NodeCB* newNode = new NodeCB(newCB, first);
		first = newNode;
	}
	else{
		NodeCB*p=first;
		for(; p->next!=NULL; p=p->next);
		NodeCB* newNode = new NodeCB(newCB, p->next);
		p->next = newNode;
	}
}

void MayBay::themCB(){
//	char maCB[MAX_MA_CB];
//	char sanBayDen[MAX_SAN_BAY];
//	Date date;
//	int check;
//	do{
//		fflush(stdin);
//		wcout<<"Nhap Ma CB: ";
//		cin.getline(maCB, MAX_MA_CB);
//		check = isDuplicateCB_All(dsmb);
//	} while(check)
//	fflush(stdin);
//	wcout<<"Nhap Noi Den: ";
//	cin.getline(sanBayDen, MAX_SAN_BAY);
//	date.nhap();
//	ChuyenBay cb(maCB, sanBayDen, soCho, date);
//	insert(cb);
}

int MayBay::isDuplicateCB(char* maCB){
	NodeCB* p = first;
	while(p!=NULL){
		if(strcmpi(p->cb.getMaCB(), maCB) == 0)
			return 1;
		p=p->next;
	}
	return 0;
}


void MayBay::xuatCB(){
	if(first==NULL){
		wcout<<"Khong co chuyen bay"<<endl;
		return;
	}	
	NodeCB* p = first;
	while(p!=NULL){
		p->cb.xuat();
		p = p->next;
	}
}

ChuyenBay* MayBay::getCB(char* maCB){
	NodeCB* p = first;
	while(p!=NULL){
		if(strcmpi(p->cb.getMaCB(), maCB) == 0){
			return &(p->cb);
		}
		p = p->next;
	}
	return NULL;
}

int MayBay::updateCB(char* maCB){
	ChuyenBay* cb = getCB(maCB);
	if(cb==NULL){
		return 0;
	}
	return cb->update();
}

int MayBay::getSizeCB(){
	if(first == NULL)
		return 0;
	int dem = 0;
	NodeCB* p = first;
	while(p!=NULL){
		dem++;
		p=p->next;
	}
	return dem;
}

void MayBay::writeCB(ofstream& fout){
	int size = getSizeCB();
	fout.write((char*) &size, sizeof(int));
	NodeCB* p = first;
	while(p!=NULL){
		p->cb.write(fout);
		p = p->next;
	}
}

void MayBay::readCB(ifstream& fin){
	int dem = 0;
	fin.read((char*) &dem, sizeof(int));
	ChuyenBay newCB;
	while(dem>0){
		newCB.read(fin);
		insert(newCB);
		dem--;
	}
}

void MayBay::setFirst(NodeCB* first){
	this->first = first;
}

NodeCB* MayBay::getFirst(){
	return first;
}

int MayBay::timKiemSanBayDen(char* sanBayDen){
	NodeCB* p = first;
	while(p!=NULL){
		if(strcmpi(p->cb.getSanBayDen(), sanBayDen)==0 && p->cb.getTrangThai()==CON_VE){
			return 1;		
		}
		p = p->next;
	}
	return 0;
}

void MayBay::DHinCBtheoSanBay(char* sanBay, short &x, short &y, int &stt){
	NodeCB* p = first;
	while(p!=NULL){
		if(p->cb.getTrangThai()==CON_VE 
				&& strcmpi(p->cb.getSanBayDen(), sanBay)==0){
			gotoxy(x+3, y);
			wcout<<stt;
			gotoxy(x+12, y);
			wcout<<p->cb.getMaCB();
			gotoxy(x+33, y);
			p->cb.getNgKhoiHanh()->xuatNgay();
			gotoxy(x+56, y);
			wcout<<soHieu;
			
			gotoxy(x, y);
			wcout<<LR_LINE;
			gotoxy(x+7, y);
			wcout<<LR_LINE;
			gotoxy(x+28, y);
			wcout<<LR_LINE;
			gotoxy(x+49, y);
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
			gotoxy(x+70, y+1);
			wcout<<LR_LINE;
			
			y=y+2;
			stt++;
		}
		
		p = p->next;
	}
}

ChuyenBay* MayBay::getCBtheoSanBay(char* maCB, char* sanBay){
	NodeCB* p = first;
	while(p!=NULL){
		if(strcmpi(p->cb.getMaCB(), maCB)==0
				&& strcmpi(p->cb.getSanBayDen(), sanBay)==0
						&& p->cb.getTrangThai()==CON_VE){
			return &(p->cb);			
		}
		p = p->next;
	}
	return NULL;
}

/*
    ----- SUA -----
	return HUY     : khi CB bi HUY
	return HOAN_TAT: khi CB da hoan tat
	return -1      : khong tim maCB
	return 10      : CB co stt la CON_VE or HET_VE
*/

int MayBay::suaCB(char* maCB, ChuyenBay* &cb){
	NodeCB* p = first;
	while(p!=NULL){
		if(strcmpi(p->cb.getMaCB(), maCB)==0){
			if(p->cb.getTrangThai()==HOAN_TAT){
				cb = NULL;
				return HOAN_TAT;	
			}
			else if(p->cb.getTrangThai()==HUY){
				cb = NULL;
				return HUY;	
			}
			else{
				cb = &(p->cb);
				return 10;
			}
		}
		
		p = p->next;
	}
	return -1;
}

void MayBay::deleteFirst(){
	NodeCB* p = first;
	first = first->next;
	delete p;
}

void MayBay::deleteAfter(NodeCB* p){
	NodeCB* q;
	q = p->next;
	p->next = q->next;
	delete q;
}

int MayBay::deleteTheoMaCB(char* maCB){
	if(first==NULL){
		return 0;
	}
	if(strcmpi(first->cb.getMaCB(), maCB)==0){
		deleteFirst();
		return 1;
	} else{
		NodeCB* p = first->next;
		NodeCB* q = first;
		while(p!=NULL){
			if(strcmpi(p->cb.getMaCB(), maCB)==0){
				deleteAfter(q);
				return 1;
			}
			q = p;
			p = p->next;
		}
	}
	return 0;
}

/*
   ---- XOA ----
   TH1: CB da HOAN TAT
   TH2: CB bi HUY
   TH3: CB CON VE = MAX
*/


int MayBay::coTheXoa(NodeCB*& p){
	if(p->cb.getTrangThai() == HOAN_TAT || p->cb.getTrangThai() == HUY || p->cb.soVeConTrong()==soCho){
		return 1;
	}
	return 0;
}

int MayBay::xoaCB(char* maCB){
	NodeCB* p = first;
	while(p!=NULL){
		if(strcmpi(p->cb.getMaCB(), maCB)==0 && coTheXoa(p)){
			return 1;
		}
		p = p->next;
	}
	return 0;
	
}

/*
   	-----HUY-----
	CB CON VE HOAC HET VE
*/

int MayBay::coTheHuy(NodeCB* &p){
	if(p->cb.getTrangThai()==CON_VE || p->cb.getTrangThai()==HET_VE){
		return 1;
	}
	return 0;
}

int MayBay::huyCB(char* maCB, ChuyenBay*& cb){
	NodeCB* p = first;
	cb = NULL;
	while(p!=NULL){
		if(strcmpi(p->cb.getMaCB(), maCB)==0 && coTheHuy(p)){
			cb = &(p->cb);
			return 1;
		}
		p = p->next;
	}
	return 0;
}

void MayBay::DHshowCB_ALL(short &x, short &y, int& stt){
	NodeCB* p = first;
	while(p!=NULL){
		SetBGColor(COLOR_BG_DEFAULT);
		SetColor(COLOR_TEXT_DEFAULT);
		gotoxy(x+3, y);
		wcout<<stt;
	
		gotoxy(x+10, y);
		wcout<<p->cb.getMaCB();
	
		gotoxy(x+24, y);
		wcout<<p->cb.getSanBayDen();
	
		gotoxy(x+39, y);
		p->cb.getNgKhoiHanh()->xuat();
		
		gotoxy(x+58, y);
		if(p->cb.getTrangThai() == CON_VE){
			wcout<<p->cb.getSoVe() - p->cb.soVeConTrong();
		} else if(p->cb.getTrangThai()==HET_VE){
			SetBGColor(COLOR_BG_ITEM_SELECTED);
			wcout<<"  ";
		} else if(p->cb.getTrangThai()==HOAN_TAT){
			SetBGColor(COLOR_BG_ITEM);
			wcout<<"  ";
		} else if(p->cb.getTrangThai()==HUY){
			SetBGColor(COLOR_WARRING);
			wcout<<"  ";
		}
		
		SetBGColor(COLOR_BG_DEFAULT);
		gotoxy(x+64, y);
		wcout<<soHieu;
		
		gotoxy(x, y);
		wcout<<LR_LINE;
		gotoxy(x+7, y);
		wcout<<LR_LINE;
		gotoxy(x+21, y);
		wcout<<LR_LINE;
		gotoxy(x+38, y);
		wcout<<LR_LINE;
		gotoxy(x+55, y);
		wcout<<LR_LINE;
		gotoxy(x+62, y);
		wcout<<LR_LINE;
		gotoxy(x+70, y);
		wcout<<LR_LINE;
			
		gotoxy(x, y+1);
		wcout<<LR_LINE;
		gotoxy(x+7, y+1);
		wcout<<LR_LINE;
		gotoxy(x+21, y+1);
		wcout<<LR_LINE;
		gotoxy(x+38, y+1);
		wcout<<LR_LINE;
		gotoxy(x+55, y+1);
		wcout<<LR_LINE;
		gotoxy(x+62, y+1);
		wcout<<LR_LINE;
		gotoxy(x+70, y+1);
		wcout<<LR_LINE;
			
		y=y+2;
		stt++;
		p = p->next;
	}
}

void MayBay::capNhatSTT(Date& now){
	NodeCB* p = first;
	while(p!=NULL){
		if(p->cb.getTrangThai()==CON_VE || p->cb.getTrangThai()==HET_VE){
			p->cb.capNhatSTT(now);
		}
		p = p->next;
	}
}

/*
	-------CO HANH KHACH--------
	CB LA CON_VE HOAC HET_VE
	CB CO DSVE TON TAI CMND CUA HK
*/

int MayBay::coHanhKhach(char* CMND){
	NodeCB* p = first;
	while(p!=NULL){
		if(p->cb.getTrangThai()==CON_VE || p->cb.getTrangThai()==HET_VE){
			if(p->cb.coHanhKhach(CMND)==1)
				return 1;
		}
		p = p->next;	
	}
	return 0;
}

ChuyenBay* MayBay::getCBinDSHK(char* maCB){
	NodeCB* p = first;
	while(p!=NULL){
		if(strcmpi(p->cb.getMaCB(), maCB)==0){
			if(p->cb.getTrangThai()==HUY)
				return NULL;
			return &(p->cb);
		}
		p = p->next;
	}
	return NULL;
}

void MayBay::inCBtheoDatevsConVe(const Date &date, short &x, short &y, int &stt){
	NodeCB* p = first;
	while(p!=NULL){
		if(p->cb.getTrangThai()==CON_VE && p->cb.getNgKhoiHanh()->bang(date)==1){
			p->cb.inCBtheoNgay(x, y, stt);
		}
		p = p->next;
	}
}

int MayBay::getSLCB(){
	NodeCB* p = first;
	int dem=0;
	while(p!=NULL){
		dem++;
		p=p->next;
	}
	return dem;
}

void MayBay::xuatThongKe(short &x, short &y, int &stt){
		gotoxy(x+3, y);
		wcout<<stt;
		gotoxy(x+18, y);
		wcout<<soHieu;
		gotoxy(x+41, y);
		wcout<<soCho;
		gotoxy(x+61, y);
		wcout<<getSLCB();
			
		gotoxy(x, y);
		wcout<<LR_LINE;
		gotoxy(x+7, y);
		wcout<<LR_LINE;
		gotoxy(x+35, y);
		wcout<<LR_LINE;
		gotoxy(x+52, y);
		wcout<<LR_LINE;
		gotoxy(x+70, y);
		wcout<<LR_LINE;
		
		gotoxy(x, y+1);
		wcout<<LR_LINE;
		gotoxy(x+7, y+1);
		wcout<<LR_LINE;
		gotoxy(x+35, y+1);
		wcout<<LR_LINE;
		gotoxy(x+52, y+1);
		wcout<<LR_LINE;
		gotoxy(x+70, y+1);
		wcout<<LR_LINE;
		
		y=y+2;
		stt++;
}
