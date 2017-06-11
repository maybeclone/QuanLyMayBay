#include "Utility.h"


void ShowCur(bool CursorVisibility){
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor = {1, CursorVisibility};
    SetConsoleCursorInfo(handle, &cursor);
}
/*
	ma : chuoi
	size: size max
	n : size hien tai
	c : ki tu muon them
*/

int them(char* ma, int size, int &n, char c){
	if(n == size-1)
		return 0;
	ma[n] = c;
	n++;
	return 1;
}

int xoa(char* ma, int &n){
	if(n==0){
		return 0;
	}
	n--;
	return 1;
}

int checkMa(char* ma, int size, int &n, char& c){
	if(c<0){
		c= getch();
		return 0;
	} else if((c>='A' && c<='Z') || (c>='0' && c<='9')){
		return them(ma, size, n, c);
	} else if(c>='a' && c<='z'){
		c = c - 32;
		return them(ma, size, n, c);
	} else if(c==BACKSPACE){
		return xoa(ma, n) ? 3 : 0;
	} else
		return 0;
}

int checkMa_DEMO(char* ma, int size, int &n, char& c){
	if(c<0){
		c= getch();
		if(c==PAGE_DOWN)
			return PAGE_DOWN;
		else if(c==PAGE_UP)
			return PAGE_UP;
	}
	if((c>='A' && c<='Z') || (c>='0' && c<='9')){
		return them(ma, size, n, c);
	} else if(c>='a' && c<='z'){
		c = c - 32;
		return them(ma, size, n, c);
	} else if(c==BACKSPACE){
		return xoa(ma, n) ? 3 : 0;
	} else
		return 0;
}

/*
	1 : them dc, in ki tu ra
	0 : khong them dc
	3 : xoa, in ki tu ' '
*/

int nhapMa(char* ma, int size){
	int n=0;
	short x = wherex();
	short y = wherey();
	
	char c;
	while(c!=ENTER){
		c=getch();
		int check = checkMa(ma, size, n, c);
		if(check==3){
			x--;
			gotoxy(x, y);
			wcout<<" ";
			gotoxy(x, y);	
		}else if(check==1){
			wcout<<c;
			x++;	
		} else if(c==ESC){
			return ESC;
		}
		if(c==ENTER && n==0)
			c=0;
	}
	ma[n] = '\0';
}

int checkSo(char* ma, int size, int &n, char& c){
	if(c<0){
		c= getch();
		return 0;
	} else if(c>='0' && c<='9'){
		return them(ma, size, n, c);
	} else if(c==BACKSPACE){
		return xoa(ma, n) ? 3 : 0;
	} else
		return 0;
}

int nhapSo(char* ma, int size){
	int n=0;
	short x = wherex();
	short y = wherey();
	
	char c;
	while(c!=ENTER){
		c=getch();
		int check = checkSo(ma, size, n, c);
		if(check==3){
			x--;
			gotoxy(x, y);
			wcout<<" ";
			gotoxy(x, y);	
		}else if(check==1){
			wcout<<c;
			x++;	
		} else if(c==ESC){
			return ESC;
		}
		if(c==ENTER && n==0)
			c=0;
	}
	ma[n] = '\0';
}

int checkTen(char* ma, int size, int &n, char& c){
	if(c<0){
		c= getch();
		return 0;
	} else if(c>='A' && c<='Z'){
		return them(ma, size, n, c);
	} else if(c>='a' && c<='z'){
		c = c - 32;
		return them(ma, size, n, c);
	} else if(c==SPACE && ma[n-1]!=' '){
		return them(ma, size, n, c);
	} else if(c==BACKSPACE){
		return xoa(ma, n) ? 3 : 0;
	} else
		return 0;
}

int nhapTen(char* ma, int size){
	int n=0;
	short x = wherex();
	short y = wherey();
	
	char c;
	while(c!=ENTER){
		c=getch();
		int check = checkTen(ma, size, n, c);
		if(check==3){
			x--;
			gotoxy(x, y);
			wcout<<" ";
			gotoxy(x, y);	
		}else if(check==1){
			wcout<<c;
			x++;	
		} else if(c==ESC){
			return ESC;
		}
		if(c==ENTER && n==0)
			c=0;
	}
	ma[n] = '\0';
}

/*
	ma : chuoi muon sua
	size: size max cua chuoi
	_n: size hien gio
*/

int nhapTen_EDIT(char* ma, int size, int _n){
	int n=_n;
	short x = wherex();
	short y = wherey();
	
	char c;
	while(c!=ENTER){
		c=getch();
		int check = checkTen(ma, size, n, c);
		if(check==3){
			x--;
			gotoxy(x, y);
			wcout<<" ";
			gotoxy(x, y);	
		}else if(check==1){
			wcout<<c;
			x++;	
		} else if(c==ESC){
			return ESC;
		}
		if(c==ENTER && n==0)
			c=0;
	}
	ma[n] = '\0';
}

int nhapSo_EDIT(char* ma, int size, int _n){
	int n=_n;
	short x = wherex();
	short y = wherey();
	
	char c;
	while(c!=ENTER){
		c=getch();
		int check = checkSo(ma, size, n, c);
		if(check==3){
			x--;
			gotoxy(x, y);
			wcout<<" ";
			gotoxy(x, y);	
		}else if(check==1){
			wcout<<c;
			x++;	
		} else if(c==ESC){
			return ESC;
		}
		if(c==ENTER && n==0)
			c=0;
	}
	ma[n] = '\0';
}

int nhapMa_EDIT(char* ma, int size, int _n){
	int n=_n;
	short x = wherex();
	short y = wherey();
	
	char c;
	while(c!=ENTER){
		c=getch();
		int check = checkMa(ma, size, n, c);
		if(check==3){
			x--;
			gotoxy(x, y);
			wcout<<" ";
			gotoxy(x, y);	
		}else if(check==1){
			wcout<<c;
			x++;	
		} else if(c==ESC){
			return ESC;
		}
		if(c==ENTER && n==0)
			c=0;
	}
	ma[n] = '\0';
}

int tinhSoTrang(int size){
	return (size%10!=0) ? size/10+1 : size/10;
}

bool checkNMNhuan(int yyyy){
	if(yyyy%4==0 && yyyy%100 !=0){
		return true;
	} else if(yyyy%100==0){
		return true;
	}
	return false;
}

int checkNam(int nam, int cur_nam){
	if(nam>=cur_nam && nam<=MAX_NAM)
		return 1;
	return 0;
}

int checkThang(int nam, int thang, int cur_nam, int cur_thang){
	if(thang<=0 || thang>12){
		return 0;
	}
	if(nam == cur_nam && thang<cur_thang)
		return -1;
	return 1;
}


int checkNgay(int nam, int thang, int ngay, int cur_nam, int cur_thang, int cur_ngay){
	int months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if(checkNMNhuan(nam))
		months[1] = 29;
	else
		months[1] = 28;
	if(ngay<=0 || ngay>months[thang-1])
		return months[thang-1];
	if(thang == cur_thang && ngay <= cur_ngay && nam == cur_nam)
		return 0;
	return 1;
}

int checkGio(int gio){
	if(gio>=0 && gio<24)
		return 1;
	return 0;
}

int checkPhut(int phut){
	if(phut>=0 && phut <=59)
		return 1;
	return 0;
}

void ve1Ve(int soVe, short x, short y){
	gotoxy(x, y);
	if(soVe>99){
		wcout<<" "<<soVe;
	} else{
		wcout<<" "<<soVe<<" "; 	
	}
}

/*
	Xoa ve trong Dsach ve mua
*/
void deleteViTri(int* soVe, int& size, int position){
	for(int i=position; i<size-1; i++){
		soVe[i] = soVe[i+1];
	}
	size--;
}

int isDuplicate(int* soVe, int size, int x){
	for(int i=0; i<size; i++){
		if(soVe[i]==x)
			return 1;
	}
	return 0;
}

int soVeCon(char** ve, int size){
	int dem=0;
	for(int i=0; i<size; i++){
		if(strcmpi(ve[i], "")==0){
			dem++;
		}
	}
	return dem;
}

int* veSoVe(char** ve, int size, short x1, short y1, short x2, short y2, int& soVeMua){
	short x = x1;
	short y = y1;
	int count=0;
	while(count<size){
		if(count%20 == 0){
			y=y+2;
			x=x1;
		}
		SetColor(COLOR_TEXT_DEFAULT);
		if(strcmp(ve[count],"")!=0){
			SetBGColor(COLOR_BG_ITEM);
		} else{
			SetBGColor(COLOR_BG_DEFAULT);
		}
		ve1Ve(count+1, x, y);
		x+=5;
		count++;
	}
	
	y=y1+2;
	x=x1;
	
	int selection; //[0, size-1]
	for(int i=0; i<size; i++){
		if(strcasecmp(ve[i], "")==0){
			SetBGColor(COLOR_BG_ITEM_SELECTED);
			SetColor(COLOR_TEXT_ITEM_SELECTED);
			selection = i;
			ve1Ve(i+1, x+5*i%10, y+(y/20)*2);
			break;
		}
	}
	
	// ve chu thich	
	gotoxy(x1, size/20*2+5);
	SetBGColor(COLOR_BG_ITEM);
	SetColor(COLOR_TEXT_ITEM);
	wcout<<" x ";
	SetBGColor(COLOR_BG_DEFAULT);
	SetColor(COLOR_TEXT_DEFAULT);
	wcout<<" CO NGUOI";
	
	gotoxy(x1+16, size/20*2+5);
	SetBGColor(COLOR_HIGHLIGHT_TEXT);
	SetColor(COLOR_TEXT_ITEM_SELECTED);
	wcout<<" x ";
	SetBGColor(COLOR_BG_DEFAULT);
	SetColor(COLOR_TEXT_DEFAULT);
	wcout<<" VE DA CHON";
	
	gotoxy(x1+36, size/20*2+5);
	SetBGColor(COLOR_BG_ITEM_SELECTED);
	SetColor(COLOR_TEXT_ITEM_SELECTED);
	wcout<<" x ";
	SetBGColor(COLOR_BG_DEFAULT);
	SetColor(COLOR_TEXT_DEFAULT);
	wcout<<" VE DANG CHON";
	
	gotoxy(x1+56, size/20*2+5);
	SetBGColor(COLOR_BG_DEFAULT);
	SetColor(COLOR_HIGHLIGHT_TEXT);
	wcout<<"[INSERT]: ";
	SetColor(COLOR_TEXT_DEFAULT);
	wcout<<"THEM VE VAO GIO";
	
	gotoxy(x1+85, size/20*2+5);
	SetBGColor(COLOR_BG_DEFAULT);
	SetColor(COLOR_HIGHLIGHT_TEXT);
	wcout<<"[ENTER]: ";
	SetColor(COLOR_TEXT_DEFAULT);
	wcout<<"MUA VE";
	
	soVeMua = 0;
	int veCon = soVeCon(ve, size);
	int* veMua = new int[veCon];
	bool chon = false;
	char c=0;
	while(true){
		c = getch();
			if(c<0){
				c=getch();
			}
			switch(c){
				case UP:
					if(!isDuplicate(veMua, soVeMua, selection)){
						SetBGColor(COLOR_BG_DEFAULT);
						SetColor(COLOR_TEXT_DEFAULT);						
						ve1Ve(selection+1, x+5*(selection%20), y+(selection/20)*2);
					} else{
						SetBGColor(COLOR_HIGHLIGHT_TEXT);
						SetColor(COLOR_TEXT_ITEM_SELECTED);
						ve1Ve(selection+1, x+5*(selection%20), y+(selection/20)*2);
					}
					selection-=20;	
					do{
						if(selection>=0){
							if(strcmpi(ve[selection],"")!=0){
								selection-=20;
							}	
						}
						if(selection<0){
							selection=selection+size/20*20;
							if(selection+20<size)
								selection+=20;
						}
					} while(strcmpi(ve[selection],"")!=0 || selection<0);
					SetBGColor(COLOR_BG_ITEM_SELECTED);
					SetColor(COLOR_TEXT_ITEM_SELECTED);
					ve1Ve(selection+1, x+5*(selection%20), y+(selection/20)*2);	
					
					chon = false;
					break;
				case DOWN:
					if(!isDuplicate(veMua, soVeMua, selection)){
						SetBGColor(COLOR_BG_DEFAULT);
						SetColor(COLOR_TEXT_DEFAULT);
						ve1Ve(selection+1, x+5*(selection%20), y+(selection/20)*2);			
					} else{
						SetBGColor(COLOR_HIGHLIGHT_TEXT);
						SetColor(COLOR_BG_DEFAULT);
						ve1Ve(selection+1, x+5*(selection%20), y+(selection/20)*2);
					}
					selection+=20;
					do{
						if(selection<size){
							if(strcmpi(ve[selection], "")!=0){
								selection+=20;
							}
						}
						if(selection>size-1){
							selection=selection-size/20*20;
							if(selection/20!=0)
								selection-=20;
						}
					} while(strcmpi(ve[selection], "")!=0 || selection>=size);	
					
					SetBGColor(COLOR_BG_ITEM_SELECTED);
					SetColor(COLOR_TEXT_ITEM_SELECTED);
					ve1Ve(selection+1, x+5*(selection%20), y+(selection/20)*2);	
					
					chon = false;
					break;
				case LEFT:
					if(!isDuplicate(veMua, soVeMua, selection)){
						SetBGColor(COLOR_BG_DEFAULT);
						SetColor(COLOR_TEXT_DEFAULT);
						ve1Ve(selection+1, x+5*(selection%20), y+(selection/20)*2);
					} else{
						SetBGColor(COLOR_HIGHLIGHT_TEXT);
						SetColor(COLOR_TEXT_ITEM_SELECTED);
						ve1Ve(selection+1, x+5*(selection%20), y+(selection/20)*2);
					}
					selection--;
					if(selection==-1){
						selection=size-1;
					}
					while(strcmpi(ve[selection],"")!=0){
						selection--;
						if(selection==-1){
							selection=size-1;
						}
					}
					SetBGColor(COLOR_BG_ITEM_SELECTED);
					SetColor(COLOR_TEXT_ITEM_SELECTED);
					ve1Ve(selection+1, x+5*(selection%20), y+(selection/20)*2);
					
					chon = false;
					break;
				case RIGHT:
					if(!isDuplicate(veMua, soVeMua, selection)){
						SetBGColor(COLOR_BG_DEFAULT);
						SetColor(COLOR_TEXT_DEFAULT);
						ve1Ve(selection+1, x+5*(selection%20), y+(selection/20)*2);
					} else{
						SetBGColor(COLOR_HIGHLIGHT_TEXT);
						SetColor(COLOR_TEXT_ITEM_SELECTED);
						ve1Ve(selection+1, x+5*(selection%20), y+(selection/20)*2);
					}
					selection++;
					if(selection>size-1){
						selection=0;
					}
					while(strcmpi(ve[selection],"")!=0){
						selection++;
						if(selection>size-1){
							selection=0;
						}
					}
					SetBGColor(COLOR_BG_ITEM_SELECTED);
					SetColor(COLOR_TEXT_ITEM_SELECTED);
					ve1Ve(selection+1, x+5*(selection%20), y+(selection/20)*2);
					
					chon = false;
					break;
				case INSERT:
					if(!isDuplicate(veMua, soVeMua, selection)){
						chon = true;
						veMua[soVeMua] = selection;
						soVeMua++;
						SetBGColor(COLOR_HIGHLIGHT_TEXT);
						SetColor(COLOR_TEXT_ITEM_SELECTED);
						ve1Ve(selection+1, x+5*(selection%20), y+(selection/20)*2);
					} else{
						chon = false;
						SetBGColor(COLOR_BG_ITEM_SELECTED);
						SetColor(COLOR_TEXT_ITEM_SELECTED);
						ve1Ve(selection+1, x+5*(selection%20), y+(selection/20)*2);
						for(int i=0; i<soVeMua; i++){
							if(veMua[i]==selection){
								deleteViTri(veMua, soVeMua, i);
								break;
							}
						}
					} 
					break;
				case ENTER:
					if(soVeMua>0)
						return veMua;
					break;
				case ESC:
					delete[] veMua;
					return NULL;
				}
		}

}

void veVeTrong(char** ve, int size, short x1, short y1, short x2, short y2){
	short x = x1;
	short y = y1;
	int count=0;
	while(count<size){
		if(count%20 == 0){
			y=y+2;
			x=x1;
		}
		SetColor(COLOR_TEXT_DEFAULT);
		if(strcmp(ve[count],"")!=0){
			SetBGColor(COLOR_BG_ITEM);
		} else{
			SetBGColor(COLOR_BG_DEFAULT);
		}
		ve1Ve(count+1, x, y);
		x+=5;
		count++;
	}
	gotoxy(x1, size/20*2+5);
	SetBGColor(COLOR_BG_ITEM);
	SetColor(COLOR_TEXT_ITEM);
	wcout<<" x ";
	SetBGColor(COLOR_BG_DEFAULT);
	SetColor(COLOR_TEXT_DEFAULT);
	wcout<<" CO NGUOI";
	
	gotoxy(x1+16, size/20*2+5);
	SetBGColor(COLOR_BG_DEFAULT);
	SetColor(COLOR_TEXT_DEFAULT);
	wcout<<" x ";
	SetBGColor(COLOR_BG_DEFAULT);
	SetColor(COLOR_TEXT_DEFAULT);
	wcout<<" VE TRONG";
}
