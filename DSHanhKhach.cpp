#include "DSHanhKhach.h"

DSHanhKhach::DSHanhKhach(){
	root = NULL;
}

DSHanhKhach::~DSHanhKhach(){
	del(root);
}

void DSHanhKhach::del(NodeHK* node){
	if(node!=NULL){
		del(node->left);
		del(node->right);
		delete node;
	}
}

int DSHanhKhach::themHK(HanhKhach& newHK){
	return themHK_DQ(root, newHK);
}

int DSHanhKhach::themHK_DQ(NodeHK*& node, HanhKhach& newHK){
	if(node == NULL) { // nut p la nut la
		node = new NodeHK(newHK);
		return 1;
	} 
	if(strcmpi(node->hk.getCMND(), newHK.getCMND())>0)
		return themHK_DQ(node->left, newHK);	
	else if( strcmpi(node->hk.getCMND(), newHK.getCMND())<0)
		return themHK_DQ(node->right, newHK);
	else // bang nhau
		return 0;
}

int DSHanhKhach::getSize(){
	int dem = 0;
	demSize_DQ(root, dem);
	return dem;
}

void DSHanhKhach::demSize_DQ(NodeHK* node, int& dem){
	if(node!=NULL){
		dem++;
		demSize_DQ(node->left, dem);
		demSize_DQ(node->right, dem);
	}
}

void DSHanhKhach::xuat(){
	xuat_DQ(root);
}

void DSHanhKhach::xuat_DQ(NodeHK* node){
	if(node!=NULL){
		node->hk.xuat();
		xuat_DQ(node->left);
		xuat_DQ(node->right);
	}
}

HanhKhach* DSHanhKhach::getHK(char* CMND){
	NodeHK* p = root;
	while(p!=NULL){
		if(strcmpi(p->hk.getCMND(), CMND)>0){
			p=p->left;
		} else if(strcmpi(p->hk.getCMND(), CMND)<0){
			p=p->right;
		} else{
			return &(p->hk);
		}
	}
}

int DSHanhKhach::isDuplicate(char* CMND){
	NodeHK* p = root;
	while(p!=NULL){
		if(strcmpi(p->hk.getCMND(), CMND)>0)
			p = p->left;
		else if (strcmpi(p->hk.getCMND(), CMND)<0)
			p = p->right;
		else
			return 1;
	}
	return 0;
}

void DSHanhKhach::nhapHK(){
	char CMND[MAX_CMND];
	char ho[MAX_HO_HK];
	char ten[MAX_TEN_HK];
	char phai_C;
	bool phai;
	int check;
	do{
		cout<<"Nhap CMND: ";
		cin.getline(CMND, MAX_CMND);	
		check = isDuplicate(CMND);
		if(check)
			cout<<"Nguoi dung ton tai";
	} while(check);
	cout<<"Nhap Ho: ";
	cin.getline(ho, MAX_HO_HK);
	cout<<"Nhap Ten: ";
	cin.getline(ten, MAX_TEN_HK);
	// 'n' or 'y'
	cout<<"Nhap Phai: ";
	cin>>phai_C;
	phai_C == 'n' ? phai = true : phai = false;
	HanhKhach newHK(CMND, ho, ten, phai);
	themHK(newHK);
}

void DSHanhKhach::write(ofstream& fout){
	stack<NodeHK*> Stack;
	NodeHK* p = root;
	int size = getSize();
	fout.write((char*) &size, sizeof(int));
	while(p!=NULL){
		
		fout.write((char*) &(p->hk), sizeof(HanhKhach));
		
		if(p->right!=NULL)
			Stack.push(p->right);
		if(p->left!=NULL)
			p=p->left;
		else if(Stack.empty())
			break;
		else{
			p = Stack.top();
			Stack.pop();
		}		
	}
}

void DSHanhKhach::read(ifstream& fin){
	HanhKhach newHK;
	int dem=0;
	fin.read((char*) &dem, sizeof(int));
	while(dem>0){
		fin.read((char*) &newHK, sizeof(HanhKhach));
		themHK(newHK);
		dem--;
	}
}

void DSHanhKhach::DHthemHK(short x1, short y1, short x2, short y2){
	SetBGColor(COLOR_BG_DEFAULT);
	SetColor(COLOR_TEXT_DEFAULT);
	veKhung(x1, y1, x2, y2);
	
	SetColor(COLOR_HIGHLIGHT_TEXT);
	gotoxy(x1+6, y1+2);
	wcout<<"CMND     :";
	gotoxy(x1+6, y1+5);
	wcout<<"Ho HK    :";
	gotoxy(x1+6, y1+8);
	wcout<<"Ten HK   :";
	gotoxy(x1+6, y1+11);
	wcout<<"Gioi Tinh:";
	
	short x[2] = {x1+7, x1+26};
	short y[2] = {y1+14, y1+14};
	short CD = 15;
	short CR = 3;
	
	char menu[2][15] = {"Xoa Het",
						"Them HK"}; 
	
	// input
	char CMND[MAX_CMND];
	bool phai;
	char ten[MAX_TEN_HK];
	char ho[MAX_HO_HK];
	int check;
	
	while(true){
		gotoxy(x1+20, y1+11);
		SetBGColor(COLOR_BG_ITEM);
		SetColor(COLOR_TEXT_ITEM);
		wcout<<" Nam ";
		gotoxy(x1+31, y1+11);
		wcout<<" Nu ";

		ShowCur(true);
		SetBGColor(COLOR_BG_ITEM);
		SetColor(COLOR_TEXT_ITEM);
		veKhungItem(x[0], y[0], x[0]+CD, y[0]+CR);
		gotoxy(x[0]+(CD/3), y[0]+1); wcout<<menu[0];
		veKhungItem(x[1], y[1], x[1]+CD, y[1]+CR);
		gotoxy(x[1]+(CD/3), y[1]+1); wcout<<menu[1];
	
		do{
			SetBGColor(COLOR_BG_DEFAULT);
			SetColor(COLOR_TEXT_DEFAULT);
			gotoxy(x1+18, y1+2);
			fflush(stdin);
			if(nhapSo(CMND, MAX_CMND)==ESC){
				return;
			}
			check = isDuplicate(CMND);
			if(check){
				gotoxy(x1+18, y1+3);
				SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_WARRING);
				wcout<<"HANH KHACH DA TON TAI!";
				gotoxy(x1+18, y1+2);
				SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_BG_DEFAULT);
				wcout<<CMND;
			}
			if(strlen(CMND)<9){
				gotoxy(x1+18, y1+3);
				SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_WARRING);
				wcout<<"CMND BAO GOM 9 SO";
				gotoxy(x1+18, y1+2);
				SetBGColor(COLOR_BG_DEFAULT);
				SetColor(COLOR_BG_DEFAULT);
				wcout<<CMND;
			}
		} while(check || strlen(CMND)<9);
		gotoxy(x1+18, y1+3);
		SetBGColor(COLOR_BG_DEFAULT);
		SetColor(COLOR_BG_DEFAULT);
		wcout<<"                       ";
	
		gotoxy(x1+18, y1+5);
		SetBGColor(COLOR_BG_DEFAULT);
		SetColor(COLOR_TEXT_DEFAULT);
		fflush(stdin);
		if(nhapTen(ho, MAX_HO_HK)==ESC)
			return;
	
		gotoxy(x1+18, y1+8);
		fflush(stdin);
		if(nhapTen(ten, MAX_TEN_HK)==ESC)
			return;
		
		int gioiTinh = 1;
		gotoxy(x1+20, y1+11);
		SetBGColor(COLOR_BG_ITEM_SELECTED);
		SetColor(COLOR_TEXT_ITEM_SELECTED);
		wcout<<" Nam ";
	
		ShowCur(false);
		char c=0;
		while(c!=ENTER){
			c = getch();
			if(c<0)
				c = getch();
			if(c==RIGHT || c==LEFT){
				if(gioiTinh == 1){
					gotoxy(x1+20, y1+11);
					SetBGColor(COLOR_BG_ITEM);
					SetColor(COLOR_TEXT_ITEM);
					wcout<<" Nam ";
				} else if(gioiTinh == 2){
					gotoxy(x1+20, y1+11);
					SetBGColor(COLOR_BG_ITEM);
					SetColor(COLOR_TEXT_ITEM);
					gotoxy(x1+31, y1+11);
					wcout<<" Nu ";
				}
			}
		switch(c){
			case LEFT:
				gioiTinh--;
				if(gioiTinh == 0)
					gioiTinh = 2;
				if(gioiTinh == 1){
					gotoxy(x1+20, y1+11);
					SetBGColor(COLOR_BG_ITEM_SELECTED);
					SetColor(COLOR_TEXT_ITEM_SELECTED);
					wcout<<" Nam ";
				} else if(gioiTinh == 2){
					gotoxy(x1+20, y1+11);
					SetBGColor(COLOR_BG_ITEM_SELECTED);
					SetColor(COLOR_TEXT_ITEM_SELECTED);
					gotoxy(x1+31, y1+11);
					wcout<<" Nu ";
				}
				break;
			case RIGHT:
				gioiTinh++;
				if(gioiTinh == 3)
					gioiTinh = 1;
				if(gioiTinh == 1){
					gotoxy(x1+20, y1+11);
					SetBGColor(COLOR_BG_ITEM_SELECTED);
					SetColor(COLOR_TEXT_ITEM_SELECTED);
					wcout<<" Nam ";
				} else if(gioiTinh == 2){
					gotoxy(x1+20, y1+11);
					SetBGColor(COLOR_BG_ITEM_SELECTED);
					SetColor(COLOR_TEXT_ITEM_SELECTED);
					gotoxy(x1+31, y1+11);
					wcout<<" Nu ";
				}
				break;
			case ENTER:
				break;
			case ESC:
				return;
		}
	}
		(gioiTinh==1) ? phai = true : phai = false;
		
		ShowCur(false);
		int selection = 2;
		SetBGColor(COLOR_BG_ITEM_SELECTED);
		SetColor(COLOR_TEXT_ITEM_SELECTED);
		veKhungItem(x[selection-1], y[selection-1], x[selection-1]+CD, y[selection-1]+CR);
		gotoxy(x[selection-1]+(CD/3), y[selection-1]+1); wcout<<menu[selection-1];
		
		c=0;
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
				// tao hanh khach vs insert
				HanhKhach hk(CMND, ho, ten, phai);
				themHK(hk);
				gotoxy(x1+8, y1+13);
				SetColor(COLOR_SUCCESS);
				SetBGColor(COLOR_BG_DEFAULT);
				wcout<<"THEM THANH CONG! NHAN PHIM BAT KI";
				getch();
				gotoxy(x1+8, y1+13);
				SetColor(COLOR_BG_DEFAULT);
				SetBGColor(COLOR_BG_DEFAULT);
				wcout<<"THEM THANH CONG! NHAN PHIM BAT KI";
				break;
		}
		SetBGColor(COLOR_BG_DEFAULT);
		SetColor(COLOR_BG_DEFAULT);
		gotoxy(x1+18, y1+2);
		wcout<<CMND;
		gotoxy(x1+18, y1+5);
		wcout<<ho;
		gotoxy(x1+18, y1+8);
		wcout<<ten;
	}
}

int DSHanhKhach::DHsuaHK(short x1, short y1, short x2, short y2, char* _CMND){
	SetBGColor(COLOR_BG_DEFAULT);
	SetColor(COLOR_TEXT_DEFAULT);
	veKhung(x1, y1, x2, y2);
	
	HanhKhach* hk = getHK(_CMND);
	bool phai;
	char ten[MAX_TEN_HK];
	char ho[MAX_HO_HK];
	int gioiTinh;
	
	short x[2] = {x1+7, x1+26};
	short y[2] = {y1+14, y1+14};
	short CD = 15;
	short CR = 3;
	
	char menu[2][15] = {"Xoa Het",
						"Cap nhat"}; 
	
	SetColor(COLOR_HIGHLIGHT_TEXT);
	gotoxy(x1+6, y1+2);
	wcout<<"CMND     :";
	gotoxy(x1+6, y1+5);
	wcout<<"Ho HK    :";
	gotoxy(x1+6, y1+8);
	wcout<<"Ten HK   :";
	gotoxy(x1+6, y1+11);
	wcout<<"Gioi Tinh:";
	
	SetColor(COLOR_TEXT_DEFAULT);
	gotoxy(x1+18, y1+2);
	wcout<<hk->getCMND();
	
	while(true){
		SetBGColor(COLOR_BG_DEFAULT);
		SetColor(COLOR_TEXT_DEFAULT);
		strcpy(ho, hk->getHo());
		strcpy(ten, hk->getTen());
		phai = hk->getPhai();
		gotoxy(x1+18, y1+5);
		wcout<<ho;
		gotoxy(x1+18, y1+8);
		wcout<<ten;
		
		gotoxy(x1+20, y1+11);
		SetBGColor(COLOR_BG_ITEM);
		SetColor(COLOR_TEXT_ITEM);
		wcout<<" Nam ";
		gotoxy(x1+31, y1+11);
		wcout<<" Nu ";
		
		gioiTinh = phai ? 1 : 2;
		SetBGColor(COLOR_BG_ITEM_SELECTED);
		SetColor(COLOR_TEXT_ITEM_SELECTED);
		if(gioiTinh==1){
			gotoxy(x1+20, y1+11);
			wcout<<" Nam ";	
		} else if(gioiTinh==2){
			gotoxy(x1+31, y1+11);
			wcout<<" Nu ";
		}
	
		SetBGColor(COLOR_BG_ITEM);
		SetColor(COLOR_TEXT_ITEM);
		veKhungItem(x[0], y[0], x[0]+CD, y[0]+CR);
		gotoxy(x[0]+(CD/3), y[0]+1); wcout<<menu[0];
		veKhungItem(x[1], y[1], x[1]+CD, y[1]+CR);
		gotoxy(x[1]+(CD/3), y[1]+1); wcout<<menu[1];
		
		ShowCur(true);
		gotoxy(x1+18+strlen(ho), y1+5);
		SetBGColor(COLOR_BG_DEFAULT);
		SetColor(COLOR_TEXT_DEFAULT);
		fflush(stdin);
		if(nhapTen_EDIT(ho, MAX_HO_HK, strlen(ho))==ESC)
			return ESC;
		gotoxy(x1+18+strlen(ten), y1+8);
		fflush(stdin);
		if(nhapTen_EDIT(ten, MAX_HO_HK, strlen(ten))==ESC)
			return ESC;
	
		ShowCur(false);
		char c=0;
		while(c!=ENTER){
			c = getch();
			if(c<0)
				c = getch();
			if(c==RIGHT || c==LEFT){
				if(gioiTinh == 1){
					gotoxy(x1+20, y1+11);
					SetBGColor(COLOR_BG_ITEM);
					SetColor(COLOR_TEXT_ITEM);
					wcout<<" Nam ";
				} else if(gioiTinh == 2){
					gotoxy(x1+20, y1+11);
					SetBGColor(COLOR_BG_ITEM);
					SetColor(COLOR_TEXT_ITEM);
					gotoxy(x1+31, y1+11);
					wcout<<" Nu ";
				}
			}
			switch(c){
				case LEFT:
					gioiTinh--;
					if(gioiTinh == 0)
						gioiTinh = 2;
					if(gioiTinh == 1){
						gotoxy(x1+20, y1+11);
						SetBGColor(COLOR_BG_ITEM_SELECTED);
						SetColor(COLOR_TEXT_ITEM_SELECTED);
						wcout<<" Nam ";
					} else if(gioiTinh == 2){
						gotoxy(x1+20, y1+11);
						SetBGColor(COLOR_BG_ITEM_SELECTED);
						SetColor(COLOR_TEXT_ITEM_SELECTED);
						gotoxy(x1+31, y1+11);
						wcout<<" Nu ";
					}
					break;
				case RIGHT:
					gioiTinh++;
					if(gioiTinh == 3)
						gioiTinh = 1;
					if(gioiTinh == 1){
						gotoxy(x1+20, y1+11);
						SetBGColor(COLOR_BG_ITEM_SELECTED);
						SetColor(COLOR_TEXT_ITEM_SELECTED);
						wcout<<" Nam ";
					} else if(gioiTinh == 2){
						gotoxy(x1+20, y1+11);
						SetBGColor(COLOR_BG_ITEM_SELECTED);
						SetColor(COLOR_TEXT_ITEM_SELECTED);
						gotoxy(x1+31, y1+11);
						wcout<<" Nu ";
					}
					break;
				case ENTER:
					break;
				case ESC:
					return ESC;
			}
		}
		(gioiTinh==1) ? phai = true : phai = false;
		
		ShowCur(false);
		int selection = 2;
		SetBGColor(COLOR_BG_ITEM_SELECTED);
		SetColor(COLOR_TEXT_ITEM_SELECTED);
		veKhungItem(x[selection-1], y[selection-1], x[selection-1]+CD, y[selection-1]+CR);
		gotoxy(x[selection-1]+(CD/3), y[selection-1]+1); wcout<<menu[selection-1];
		
		c=0;
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
				// tao hanh khach vs insert
				hk->setHo(ho); hk->setTen(ten); hk->setPhai(phai);
				gotoxy(x1+8, y1+13);
				SetColor(COLOR_SUCCESS);
				SetBGColor(COLOR_BG_DEFAULT);
				wcout<<"CAP NHAT THANH CONG! NHAN PHIM BAT KI";
				getch();
				gotoxy(x1+8, y1+13);
				SetColor(COLOR_BG_DEFAULT);
				SetBGColor(COLOR_BG_DEFAULT);
				wcout<<"CAP NHAT THANH CONG! NHAN PHIM BAT KI";
				return 1;
		}
		SetBGColor(COLOR_BG_DEFAULT);
		SetColor(COLOR_BG_DEFAULT);
		gotoxy(x1+18, y1+5);
		wcout<<ho;
		gotoxy(x1+18, y1+8);
		wcout<<ten;
	}
}

int DSHanhKhach::DHthemHKtheoCMND(short x1, short y1, short x2, short y2, char* CMND){
	SetBGColor(COLOR_BG_DEFAULT);
	SetColor(COLOR_TEXT_DEFAULT);
	veKhung(x1, y1, x2, y2);
	
	SetColor(COLOR_HIGHLIGHT_TEXT);
	gotoxy(x1+6, y1+2);
	wcout<<"CMND     :";
	gotoxy(x1+6, y1+5);
	wcout<<"Ho HK    :";
	gotoxy(x1+6, y1+8);
	wcout<<"Ten HK   :";
	gotoxy(x1+6, y1+11);
	wcout<<"Gioi Tinh:";
	
	gotoxy(x1+18, y1+2);
	SetBGColor(COLOR_BG_DEFAULT);
	SetColor(COLOR_TEXT_DEFAULT);
	wcout<<CMND;
	
	short x[2] = {x1+7, x1+26};
	short y[2] = {y1+14, y1+14};
	short CD = 15;
	short CR = 3;
	
	char menu[2][15] = {"Xoa Het",
						"Them HK"}; 
	
	// input
	bool phai;
	char ten[MAX_TEN_HK];
	char ho[MAX_HO_HK];
	int check;
	
	while(true){
		gotoxy(x1+20, y1+11);
		SetBGColor(COLOR_BG_ITEM);
		SetColor(COLOR_TEXT_ITEM);
		wcout<<" Nam ";
		gotoxy(x1+31, y1+11);
		wcout<<" Nu ";

		ShowCur(true);
		SetBGColor(COLOR_BG_ITEM);
		SetColor(COLOR_TEXT_ITEM);
		veKhungItem(x[0], y[0], x[0]+CD, y[0]+CR);
		gotoxy(x[0]+(CD/3), y[0]+1); wcout<<menu[0];
		veKhungItem(x[1], y[1], x[1]+CD, y[1]+CR);
		gotoxy(x[1]+(CD/3), y[1]+1); wcout<<menu[1];
	
		gotoxy(x1+18, y1+5);
		SetBGColor(COLOR_BG_DEFAULT);
		SetColor(COLOR_TEXT_DEFAULT);
		fflush(stdin);
		if(nhapTen(ho, MAX_HO_HK)==ESC)
			return ESC;
	
		gotoxy(x1+18, y1+8);
		fflush(stdin);
		if(nhapTen(ten, MAX_TEN_HK)==ESC)
			return ESC;
		
		int gioiTinh = 1;
		gotoxy(x1+20, y1+11);
		SetBGColor(COLOR_BG_ITEM_SELECTED);
		SetColor(COLOR_TEXT_ITEM_SELECTED);
		wcout<<" Nam ";
	
		ShowCur(false);
		char c=0;
		while(c!=ENTER){
			c = getch();
			if(c<0)
				c = getch();
			if(c==RIGHT || c==LEFT){
				if(gioiTinh == 1){
					gotoxy(x1+20, y1+11);
					SetBGColor(COLOR_BG_ITEM);
					SetColor(COLOR_TEXT_ITEM);
					wcout<<" Nam ";
				} else if(gioiTinh == 2){
					gotoxy(x1+20, y1+11);
					SetBGColor(COLOR_BG_ITEM);
					SetColor(COLOR_TEXT_ITEM);
					gotoxy(x1+31, y1+11);
					wcout<<" Nu ";
				}
			}
		switch(c){
			case LEFT:
				gioiTinh--;
				if(gioiTinh == 0)
					gioiTinh = 2;
				if(gioiTinh == 1){
					gotoxy(x1+20, y1+11);
					SetBGColor(COLOR_BG_ITEM_SELECTED);
					SetColor(COLOR_TEXT_ITEM_SELECTED);
					wcout<<" Nam ";
				} else if(gioiTinh == 2){
					gotoxy(x1+20, y1+11);
					SetBGColor(COLOR_BG_ITEM_SELECTED);
					SetColor(COLOR_TEXT_ITEM_SELECTED);
					gotoxy(x1+31, y1+11);
					wcout<<" Nu ";
				}
				break;
			case RIGHT:
				gioiTinh++;
				if(gioiTinh == 3)
					gioiTinh = 1;
				if(gioiTinh == 1){
					gotoxy(x1+20, y1+11);
					SetBGColor(COLOR_BG_ITEM_SELECTED);
					SetColor(COLOR_TEXT_ITEM_SELECTED);
					wcout<<" Nam ";
				} else if(gioiTinh == 2){
					gotoxy(x1+20, y1+11);
					SetBGColor(COLOR_BG_ITEM_SELECTED);
					SetColor(COLOR_TEXT_ITEM_SELECTED);
					gotoxy(x1+31, y1+11);
					wcout<<" Nu ";
				}
				break;
			case ENTER:
				break;
			case ESC:
				return ESC;
		}
	}
		(gioiTinh==1) ? phai = true : phai = false;
		
		ShowCur(false);
		int selection = 2;
		SetBGColor(COLOR_BG_ITEM_SELECTED);
		SetColor(COLOR_TEXT_ITEM_SELECTED);
		veKhungItem(x[selection-1], y[selection-1], x[selection-1]+CD, y[selection-1]+CR);
		gotoxy(x[selection-1]+(CD/3), y[selection-1]+1); wcout<<menu[selection-1];
		
		c=0;
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
				// tao hanh khach vs insert
				HanhKhach hk(CMND, ho, ten, phai);
				themHK(hk);
				gotoxy(x1+8, y1+13);
				SetColor(COLOR_SUCCESS);
				SetBGColor(COLOR_BG_DEFAULT);
				wcout<<"THEM THANH CONG! NHAN PHIM BAT KI";
				getch();
				gotoxy(x1+8, y1+13);
				SetColor(COLOR_BG_DEFAULT);
				SetBGColor(COLOR_BG_DEFAULT);
				wcout<<"THEM THANH CONG! NHAN PHIM BAT KI";
				return 1;
		}
		SetBGColor(COLOR_BG_DEFAULT);
		SetColor(COLOR_BG_DEFAULT);
		gotoxy(x1+18, y1+5);
		wcout<<ho;
		gotoxy(x1+18, y1+8);
		wcout<<ten;
	}		
}

void DSHanhKhach::xoaHK(char* CMND){
	xoaHK_DQ(CMND, root);
}

void DSHanhKhach::timNhoNhat(NodeHK* &p, NodeHK* &q){
	if(q->left!=NULL){
		timNhoNhat(p, q->left);
	} else{
		p->hk =  q->hk;
		p = q;
		q = q->right;
	}
}

void DSHanhKhach::xoaHK_DQ(char* CMND, NodeHK* &p){
	if(p==NULL){
		return;
	}
	if(strcmpi(p->hk.getCMND(), CMND)>0){
		xoaHK_DQ(CMND, p->left);
	} else if(strcmpi(p->hk.getCMND(), CMND)<0){
		xoaHK_DQ(CMND, p->right);
	} else { // bang nhau
		NodeHK* q = p;
		if(p->left==NULL){
			p = p->right;
		} else if(p->right==NULL){
			p = p->left;
		} else { // co 2 con
			timNhoNhat(q, q->right);
		}
		delete q;
	}
}

void DSHanhKhach::DHxuatHK_ALL(short &x, short &y, int &stt){
	DHxuatHK_ALL_DQ(root, x, y, stt);
}

void DSHanhKhach::DHxuatHK_ALL_DQ(NodeHK* p, short &x, short &y, int &stt){
	if(p==NULL)
		return;
	
		SetBGColor(COLOR_BG_DEFAULT);
		SetColor(COLOR_TEXT_DEFAULT);
		gotoxy(x+3, y);
		wcout<<stt;
	
		gotoxy(x+13, y);
		wcout<<p->hk.getCMND();
	
		gotoxy(x+32, y);
		wcout<<p->hk.getHo()<<" "<<p->hk.getTen();
	
		gotoxy(x+62, y);
		p->hk.getPhai() ? wcout<<"Nam" : wcout<<"Nu";

		gotoxy(x, y);
		wcout<<LR_LINE;
		gotoxy(x+7, y);
		wcout<<LR_LINE;
		gotoxy(x+28, y);
		wcout<<LR_LINE;
		gotoxy(x+56, y);
		wcout<<LR_LINE;
		gotoxy(x+70, y);
		wcout<<LR_LINE;
			
		gotoxy(x, y+1);
		wcout<<LR_LINE;
		gotoxy(x+7, y+1);
		wcout<<LR_LINE;
		gotoxy(x+28, y+1);
		wcout<<LR_LINE;
		gotoxy(x+56, y+1);
		wcout<<LR_LINE;
		gotoxy(x+70, y+1);
		wcout<<LR_LINE;
			
		y=y+2;
		stt++;
		DHxuatHK_ALL_DQ(p->left, x, y, stt);
		DHxuatHK_ALL_DQ(p->right, x, y, stt); 
}

