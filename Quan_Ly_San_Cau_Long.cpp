#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <limits>

using namespace std;

class KhachHang {
public:
    int maKh;
    string ten;
    string soDienThoai;
    string diaChi;
};

class Gio {
public:
    int gio;
    int phut;
    bool operator<(const Gio& g) const {
        return (gio < g.gio) || (gio == g.gio && phut < g.phut);
    }
};

class Ngay {
public:
    int ngay;
    int thang;
    int nam;
    bool hopLe() const {
        if (thang < 1 || thang > 12) return false;
        if (ngay < 1) return false;
        int maxN = 31;
        if (thang==4||thang==6||thang==9||thang==11) maxN=30;
        else if (thang==2) {
            bool nhuan=(nam%4==0 && (nam%100!=0||nam%400==0));
            maxN=nhuan?29:28;
        }
        return ngay<=maxN;
    }
    bool operator<(const Ngay& n) const {
        if (nam!=n.nam) return nam<n.nam;
        if (thang!=n.thang) return thang<n.thang;
        return ngay<n.ngay;
    }
};

class DatSan {
public:
    int maDat;
    int maKh;
    int maSan;
    Ngay ngay;
    Gio bd, kt;
};

class ThanhToan {
public:
    int maTT;
    int maDat;
    double soTien;
    bool daThanh;
};

class San {
private:
    int maSan;
    string loai;
    string beMat;
public:
    San(int m, const string& l, const string& b):maSan(m),loai(l),beMat(b){}
    int layMaSan() const { return maSan; }
    string layLoai() const { return loai; }
    string layBeMat() const { return beMat; }
};

int nhapSo(const string& s) {
    int x;
    while (true) {
        cout<<s;
        if (cin>>x) break;
        cout<<"Du lieu khong hop le. Vui long nhap lai."<<endl;
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }
    return x;
}

void nhapChuoi(const string& s, string& out) {
    cout<<s;
    cin.ignore(); getline(cin, out);
}

void nhapNgay(Ngay& n) {
    do{
        cout<<"Nhap ngay (dd mm yyyy): "; cin>>n.ngay>>n.thang>>n.nam;
        if (!n.hopLe()) cout<<"Ngay khong hop le. Vui long nhap lai."<<endl;
    } while(!n.hopLe());
}

bool hopLeGio(const Gio& g) {
    return g.gio>=0 && g.gio<24 && g.phut>=0 && g.phut<60;
}

double tinhTien(const Gio& bd, const Gio& kt, double giaCao, double giaThuong) {
    int phut = (kt.gio*60+kt.phut) - (bd.gio*60+bd.phut);
    double gio = phut/60.0;
    if (bd.gio>=18 && bd.gio<22) return gio*giaCao;
    return gio*giaThuong;
}

int main(){
    vector<San> dsSan;
    for(int i=1;i<=6;i++) dsSan.push_back(San(i,"Trong nha","Tham"));
    for(int i=7;i<=12;i++) dsSan.push_back(San(i,"Ngoai troi","Nhua"));
    vector<KhachHang> dsKh;
    vector<DatSan> dsDat;
    vector<ThanhToan> dsTT;
    int nextKh=1, nextDat=1, nextTT=1;
    while(true){
        cout<<"\n===== MENU ====="<<endl;
        cout<<"1. Quan ly san"<<endl;
        cout<<"2. Dat san"<<endl;
        cout<<"3. Quan ly khach hang"<<endl;
        cout<<"4. Thanh toan"<<endl;
        cout<<"5. Bao cao thong ke"<<endl;
        cout<<"6. Tim kiem loc"<<endl;
        cout<<"7. Thoat"<<endl;
        int c=nhapSo("Lua chon: ");
        switch(c){
            case 1:{
                cout<<"Danh sach san:"<<endl;
                for(size_t i=0;i<dsSan.size();i++){
                    cout<<"San "<<dsSan[i].layMaSan()
                        <<" ("<<dsSan[i].layLoai()
                        <<", "<<dsSan[i].layBeMat()<<")"<<endl;
                }
                break;
            }
            case 2:{
                int maKh=nhapSo("Ma khach hang: ");
                bool ok=false;
                for(size_t i=0;i<dsKh.size();i++) if(dsKh[i].maKh==maKh) ok=true;
                if(!ok){cout<<"Khach hang khong hop le."<<endl;break;}
                DatSan d;
                d.maDat=nextDat++;
                d.maKh=maKh;
                nhapNgay(d.ngay);
                int ms;
                do{ms=nhapSo("Ma san (1-12): ");}
                while(ms<1||ms>12);
                d.maSan=ms;
                do{cout<<"Gio BD (g p): ";cin>>d.bd.gio>>d.bd.phut;}while(!hopLeGio(d.bd));
                do{cout<<"Gio KT (g p): ";cin>>d.kt.gio>>d.kt.phut;}while(!hopLeGio(d.kt));
                dsDat.push_back(d);
                double tien = tinhTien(d.bd,d.kt,120,80);
                ThanhToan tt;
                tt.maTT=nextTT++;
                tt.maDat=d.maDat;
                tt.soTien=tien;
                tt.daThanh=false;
                dsTT.push_back(tt);
                cout<<"Dat san thanh cong. Tien: "<<tien<<" nghin"<<endl;
                break;
            }
            case 3:{
                cout<<"1. Them khach hang"<<endl;
                cout<<"2. Xem lich su dat san cua khach"<<endl;
                int m=nhapSo("Lua chon: ");
                if(m==1){
                    KhachHang kh;
                    kh.maKh=nextKh++;
                    nhapChuoi("Ten: ",kh.ten);
                    nhapChuoi("SDT: ",kh.soDienThoai);
                    nhapChuoi("Dia chi: ",kh.diaChi);
                    dsKh.push_back(kh);
                    cout<<"Them thanh cong. Ma KH: "<<kh.maKh<<endl;
                } else if(m==2){
                    int ma=nhapSo("Ma KH: ");
                    cout<<"Lich su dat san:"<<endl;
                    for(size_t i=0;i<dsDat.size();i++){
                        if(dsDat[i].maKh==ma){
                            cout<<"Dat "<<dsDat[i].maDat<<": San "<<dsDat[i].maSan
                                <<" ngay "<<dsDat[i].ngay.ngay<<"/"<<dsDat[i].ngay.thang
                                <<"/"<<dsDat[i].ngay.nam
                                <<" "<<dsDat[i].bd.gio<<":"<<dsDat[i].bd.phut
                                <<"-"<<dsDat[i].kt.gio<<":"<<dsDat[i].kt.phut<<endl;
                        }
                    }
                }
                break;
            }
            case 4:{
                cout<<"Lich thanh toan:"<<endl;
                for(size_t i=0;i<dsTT.size();i++){
                    cout<<"TT "<<dsTT[i].maTT
                        <<" Dat"<<dsTT[i].maDat
                        <<" Tien:"<<dsTT[i].soTien
                        <<" DaTT:"<<(dsTT[i].daThanh?"Yes":"No")<<endl;
                }
                break;
            }
            case 5:{
                cout<<"Doanh thu: ";
                double sum=0;
                for(size_t i=0;i<dsTT.size();i++) sum+=dsTT[i].soTien;
                cout<<sum<<" nghin"<<endl;
                break;
            }
            case 6:{
                cout<<"Chua ho tro."<<endl;
                break;
            }
            case 7: return 0;
        }
    }
    return 0;
}
