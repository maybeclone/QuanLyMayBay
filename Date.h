#include <iostream>
#include <iomanip>
using namespace std;

class Date
{
	private:
		int ngay;
		int thang;
		int nam;
		int gio;
		int phut;
	public:
		Date(int gio=0, int phut=0, int ngay=0, int thang=0, int nam=0){
			this->ngay = ngay;
			this->thang = thang;
			this->nam = nam;
			this->gio = gio;
			this->phut = phut;
		}
		
		void setGio(int gio){
			this->gio = gio;
		}
		void setPhut(int phut){
			this->phut = phut;
		}
		void setNgay(int ngay){
			this->ngay = ngay;
		}
		void setThang(int thang){
			this->thang = thang;
		}
		void setNam(int nam){
			this->nam = nam;
		}
		void nhap(){
			cout<<"Nhap gio: ";
			cin>>gio;
			cout<<"Nhap phut: ";
			cin>>phut;
			cout<<"Nhap ngay: ";
			cin>>ngay;
			cout<<"Nhap thang: ";
			cin>>thang;
			cout<<"Nhap nam: ";
			cin>>nam;	
		}
		int getNam(){
			return nam;
		}
		int getNgay(){
			return ngay;
		}
		int getThang(){
			return thang;
		}
		int getGio(){
			return gio;
		}
		int getPhut(){
			return phut;
		}
		void xuat(){
			wcout<<setw(2)<<setfill((wchar_t)'0')<<right<<gio<<":"<<setw(2)<<right<<phut<<" ";
			wcout<<setw(2)<<right<<ngay<<"/"<<setw(2)<<right<<thang<<"/"<<setw(4)<<setfill((wchar_t)'0')<<nam;
			wcout<<setfill((wchar_t)' ');
		}
			
		void xuatNgay(){
			wcout<<setw(2)<<setfill((wchar_t) '0')<<right<<ngay<<"/";
			wcout<<setw(2)<<setfill((wchar_t) '0')<<right<<thang<<"/";
			wcout<<setw(4)<<right<<nam;
		}
		
		void xuatNgSua(){
			wcout<<setw(4)<<right<<nam<<"/";
			wcout<<setw(2)<<setfill((wchar_t) '0')<<right<<thang<<"/";
			wcout<<setw(2)<<setfill((wchar_t) '0')<<right<<ngay;
		}
		
		void xuatGio(){
			wcout<<setw(2)<<setfill((wchar_t) '0')<<right<<gio<<":";
			wcout<<setw(2)<<setfill((wchar_t) '0')<<right<<phut;
		}
		
		int nhoHonBang(Date &now){
			if(this->nam > now.nam){
				return 0;
			} else if(this->nam < now.nam)
				return 1;
			if(this->thang > now.thang)
				return 0;
			else if(this->thang < now.thang)
				return 1;
			if(this->ngay > now.ngay)
				return 0;
			else if(this->ngay < now.ngay)
				return 1;
			return 1;
		}
		
		int bang(const Date &date){
			if(nam==date.nam && thang==date.thang && ngay==date.ngay){
				return 1;
			}
			return 0;
		}
		
};

