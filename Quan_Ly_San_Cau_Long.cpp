#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <limits>
#include <iomanip>
#include<fstream>
#include<sstream>
using namespace std;

class KhachHang {
private:
    int maKh;
    string ten;
    string soDienThoai;
    string diaChi;
friend class Tinhnang;
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
        if (thang == 4 || thang == 6 || thang == 9 || thang == 11) maxN = 30;
        else if (thang == 2) {
            bool nhuan = (nam % 4 == 0 && (nam % 100 != 0 || nam % 400 == 0));
            maxN = nhuan ? 29 : 28;
        }
        return ngay <= maxN;
    }
    bool operator<(const Ngay& n) const {
        if (nam != n.nam) return nam < n.nam;
        if (thang != n.thang) return thang < n.thang;
        return ngay < n.ngay;
    }
    bool operator==(const Ngay& n) const {
        return (ngay == n.ngay && thang == n.thang && nam == n.nam);
    }
};

class DatSan {
private:
    int maDat;
    int maKh;
    int maSan;
    Ngay ngay;
    Gio bd, kt;
    friend class Tinhnang;
};

class ThanhToan {
private:
    int maTT;
    int maDat;
    double soTien;
    bool daThanh;
    friend class Tinhnang;
};

class San {
private:
    int maSan;
    string loai;
    string beMat;
    int giaCao, giaThuong;
public:
    San(int m, const string& l, const string& b) :maSan(m), loai(l), beMat(b) {
    }
    San(){
        giaCao=120;
        giaThuong=80;
    }
    int layMaSan() const { return maSan; }
    string layLoai() const { return loai; }
    string layBeMat() const { return beMat; }
    friend class Tinhnang;
};

class Tinhnang {
public:
    string to_string(const int &x);
    int nhapSo(const string& s);
    void nhapChuoi(const string& s, string& out);
    void nhapNgay(Ngay& n);
    bool hopLeGio(const Gio& g);
    double tinhTien(const Gio& bd, const Gio& kt, const &giaCao, const &giaThuong);
    bool trungGio(const Gio& t, const Gio& bd, const Gio& kt);
    void Thuc_hien(vector<San>& dsSan, vector<KhachHang>& dsKh, vector<DatSan>& dsDat,
         vector<ThanhToan>& dsTT, int &nextKh, int &nextDat, int &nextTT, San &s) {
        while (true) {
            cout << "\n===== MENU =====" << endl;
            cout << "1. Quan ly san" << endl;
            cout << "2. Dat san/Huy san" << endl;
            cout << "3. Quan ly khach hang" << endl;
            cout << "4. Thanh toan" << endl;
            cout << "5. Bao cao thong ke" << endl;
            cout << "6. Tim kiem khach hang" << endl;
            cout << "7. Xuat toan bo danh sach khach hang" << endl;
            cout << "8. Xuat hoa don khach hang" << endl;
            cout << "9. Thoat" << endl;
            cout << "=================" << endl;
            int c = nhapSo("Lua chon: ");
            switch (c) {
            case 1: {
                quan_ly_san(dsSan);
                break;
            }
            case 2: {
                Dat_Huy(dsSan, dsKh, dsDat, dsTT, nextKh, nextDat, nextTT,s);
                break;
            }
            case 3: {
                Quan_ly_Kh(dsSan, dsKh, dsDat, nextKh);
                break;
            }

            case 4: {
                Thanh_toan(dsTT);
                break;
            }
            case 5: {
                Doanh_thu(dsTT);
                break;
            }
            case 6: {
                Tim_kiem(dsKh);
                break;
            }
            case 7: {
                Xuat_ds(dsKh);
                break;
            }
            case 8: {
                Xuat_hoa_don(dsKh, dsDat, dsTT);
                break;
            }
            case 9:
                cout << "Thoat chuong trinh!";
                return;
            default: {
                cout << "Lua chon khong hop le. Vui long nhap lai." << endl;
                break;
            }
            }
        }
    }
private:
    void quan_ly_san(vector<San>& dsSan) {
        cout << "Danh sach san:" << endl;
        for (size_t i = 0;i < dsSan.size();i++) {
            cout << "San " << dsSan[i].layMaSan()
                << " (" << dsSan[i].layLoai()
                << ", " << dsSan[i].layBeMat() << ")" << endl;
        }
    }

    void Dat_Huy(vector<San>& dsSan, vector<KhachHang>& dsKh, vector<DatSan>& dsDat, 
        vector<ThanhToan>& dsTT, int &nextKh, int &nextDat, int &nextTT, San &s) {
        cout << "1. Dat san" << "\n";
        cout << "2. Huy san" << "\n";
        int m = nhapSo("Lua chon: ");
        if (m == 1) {
            int isMember = nhapSo("La thanh vien? (1-Co,0-Khach vang lai): ");
            int maKh;
            if (isMember == 1) {
                maKh = nhapSo("Ma khach hang: ");
                bool ok = false;
                for (size_t i = 0;i < dsKh.size();i++) if (dsKh[i].maKh == maKh) ok = true;
                if (!ok) { cout << "Khach hang khong hop le." << endl; }
            }
            else {
                maKh = 0;
            }
            DatSan d;
            d.maDat = nextDat++;
            d.maKh = maKh;
            nhapNgay(d.ngay);
            d.maSan = nhapSo("Ma san (1-12): ");
            while (d.maSan < 1 || d.maSan>12) {
                cout << "Ma san khong hop le. Vui long nhap lai." << endl;
                d.maSan = nhapSo("Ma san (1-12): ");
            }
            cout << "Nhap gio bat dau (g p): "; cin >> d.bd.gio >> d.bd.phut;
            while (!hopLeGio(d.bd)) {
                cout << "Gio khong hop le. Vui long nhap lai: "; cin >> d.bd.gio >> d.bd.phut;
            }
            cout << "Nhap gio ket thuc (g p): "; cin >> d.kt.gio >> d.kt.phut;
            while (!hopLeGio(d.kt)) {
                cout << "Gio khong hop le. Vui long nhap lai: "; cin >> d.kt.gio >> d.kt.phut;
            }
            bool trung = false;
            for (size_t i = 0;i < dsDat.size();i++) {
                if (dsDat[i].maSan == d.maSan && dsDat[i].ngay == d.ngay) {
                    if (trungGio(d.bd, dsDat[i].bd, dsDat[i].kt) ||
                        trungGio(d.kt, dsDat[i].bd, dsDat[i].kt)) {
                        trung = true; break;
                    }
                }
            }
            if (trung) { cout << "Khung gio da duoc dat. Quay lai menu." << endl; }
            dsDat.push_back(d);
            double tien = tinhTien(d.bd, d.kt,s.giaCao,s.giaThuong);
            ThanhToan tt;
            tt.maTT = nextTT++;
            tt.maDat = d.maDat;
            tt.soTien = tien;
            tt.daThanh = false;
            cout << "So tien can thanh toan: " << tien << " nghin" << endl;
            int daTT = nhapSo("Da thanh toan (1-Roi,0-Chua): ");
            tt.daThanh = (daTT == 1);
            dsTT.push_back(tt);
            cout << "Dat san thanh cong." << endl;
            cout << "Ma dat san: " << setw(4) << setfill('0') << d.maDat << setfill(' ') << '.' << endl;
        }
        else if (m == 2) {
            int maDat = nhapSo("Ma dat san: ");
            bool co = false;
            for (size_t i = 0;i < dsDat.size();i++) {
                if (dsDat[i].maDat == maDat) {
                    co = true;
                    dsDat.erase(dsDat.begin() + i);
                    break;
                }
            }
            if (!co) cout << "Ma dat khong hop le." << endl;
            else cout << "Huy dat san thanh cong." << endl;
        }
    }
    void Quan_ly_Kh(vector<San>& dsSan, vector<KhachHang>& dsKh, vector<DatSan>& dsDat, int &nextKh) {
        cout << "1. Them khach hang" << endl;
        cout << "2. Xem lich su dat san cua khach" << endl;
        int m = nhapSo("Lua chon: ");
        if (m == 1) {
            KhachHang kh;
            nhapChuoi("Ten: ", kh.ten);
            cout << "SDT: ";getline(cin >> ws, kh.soDienThoai);
            nhapChuoi("Dia chi: ", kh.diaChi);

            bool soTrung = false;
            for (size_t i = 0; i < dsKh.size(); i++) {
                if (dsKh[i].soDienThoai == kh.soDienThoai) {
                    soTrung = true;
                    break;
                }
            }

            if (soTrung) {
                cout << "So dien thoai da ton tai. Khong them khach hang." << endl;
            }
            else {
                kh.maKh = nextKh++;
                dsKh.push_back(kh);
                cout << "Them khach hang thanh cong. Ma khach hang: "
                    << setw(4) << setfill('0') << kh.maKh << setfill(' ') << endl;
            }
        }
        else if (m == 2) {
            int ma = nhapSo("Ma KH: ");
            bool co = false;
            for (size_t i = 0; i < dsKh.size(); i++) {
                if (dsKh[i].maKh == ma) {
                    co = true;
                    break;
                }
            }
            if (!co) {
                cout << "Ma khach hang khong hop le." << endl;

            }
            cout << "Lich su dat san:" << endl;
            for (size_t i = 0; i < dsDat.size(); i++) {
                if (dsDat[i].maKh == ma) {
                    cout << "Dat " << dsDat[i].maDat << ": San " << dsDat[i].maSan
                        << " " << dsDat[i].ngay.ngay << "/" << dsDat[i].ngay.thang
                        << "/" << dsDat[i].ngay.nam << " "
                        << dsDat[i].bd.gio << ":" << setw(2) << setfill('0') << dsDat[i].bd.phut
                        << "-" << dsDat[i].kt.gio << ":" << setw(2) << setfill('0') << dsDat[i].kt.phut
                        << setfill(' ') << endl;
                }
            }
        }

    }
    void Thanh_toan(vector<ThanhToan>& dsTT) {
        cout << "Lich thanh toan:" << endl;
        for (size_t i = 0;i < dsTT.size();i++) {
            cout << "Ma thanh toan: " << setw(4) << setfill('0') << dsTT[i].maTT << setfill(' ') << ", "
                << " Ma dat: " << setw(4) << setfill('0') << dsTT[i].maDat << setfill(' ') << ", "
                << " So tien: " << dsTT[i].soTien << ", "
                << " Da Thanh Toan: " << (dsTT[i].daThanh ? "Roi" : "Chua") << endl;
        }
    }
    void Doanh_thu(vector<ThanhToan>& dsTT) {
        double sum = 0; int count = 0;
        for (size_t i = 0;i < dsTT.size();i++) {
            sum += dsTT[i].soTien;
            count++;
        }
        cout << "Doanh thu: " << sum << " nghin" << endl;
        cout << "So luot dat san: " << count << endl;
    }
    void Tim_kiem(vector<KhachHang>& dsKh) {
        string key;
        cout << "Nhap tu khoa (maKH, ten, SDT, dia chi): ";
        cin.ignore(); getline(cin, key);
        cout << "Ket qua tim kiem:" << endl;

        for (size_t i = 0; i < dsKh.size(); i++) {
            string maKhStr = to_string(dsKh[i].maKh);
            while (maKhStr.length() < 4) maKhStr = "0" + maKhStr;

            if (maKhStr.find(key) != string::npos || dsKh[i].soDienThoai.find(key) != string::npos) {
                cout << "MaKH:" << setw(4) << setfill('0') << dsKh[i].maKh << setfill(' ') << ", "
                    << " Ten:" << dsKh[i].ten << ", "
                    << " SDT:" << dsKh[i].soDienThoai << ", "
                    << " Dia chi:" << dsKh[i].diaChi << endl;
                break;
            }
            else if
                (dsKh[i].ten.find(key) != string::npos ||
                    dsKh[i].diaChi.find(key) != string::npos) {

                cout << "MaKH: " << setw(4) << setfill('0') << dsKh[i].maKh << setfill(' ') << ", "
                    << " Ten: " << dsKh[i].ten << ", "
                    << " SDT: " << dsKh[i].soDienThoai << ", "
                    << " Dia chi: " << dsKh[i].diaChi << endl;
            }
        }
    }
    void Xuat_ds(vector<KhachHang>& dsKh) {
        if (dsKh.empty()) {
            cout << "Khong co khach hang nao." << endl;
        }
        else {
            cout << "===========Danh sach khach hang==========" << "\n";
            for (size_t i = 0; i < dsKh.size(); i++) {
                cout << "Ma Khach hang: " << setw(4) << setfill('0') << dsKh[i].maKh << setfill(' ') << "\n";
                cout << "Ten: " << dsKh[i].ten << "\n";
                cout << "So dien thoai: " << dsKh[i].soDienThoai << "\n";
                cout << "Dia chi: " << dsKh[i].diaChi << "\n";
                cout << "===================================" << "\n";
            }
        }
    }
    void Xuat_hoa_don(vector<KhachHang>& dsKh, vector<DatSan> &dsDat, vector<ThanhToan>& dsTT) {
        ofstream fs("Hoa_don.txt");
        cout << "Nhap ma khach hang can xuat hoa don: ";
        int maKh;
        cin >> maKh;
        bool ktra = false;
        for (size_t i = 0; i < dsKh.size(); i++) {
            if (dsKh[i].maKh == maKh) {
                ktra = true;
                break;
            }
        }
        if (ktra) {
            fs << "===============Hoa don khach hang================" << "\n";
            fs << "ten khach hang: " << dsKh[maKh - 1].ten << "\n";
            fs << "so dien thoai: " << dsKh[maKh - 1].soDienThoai << "\n";
            fs << "dia chi: " << dsKh[maKh - 1].diaChi << "\n";
            fs << "==================================================" << "\n";
            fs << "San da dat: " << "\n";
            for (size_t i = 0; i < dsDat.size(); i++) {
                if (dsDat[i].maKh == maKh) {
                    fs << "Ma dat: " << setw(4) << setfill('0') << dsDat[i].maDat << setfill(' ') << "\n";
                    fs << "Ma san: " << dsDat[i].maSan << "\n";
                    fs << "Ngay dat: " << dsDat[i].ngay.ngay << "/" << dsDat[i].ngay.thang
                        << "/" << dsDat[i].ngay.nam << "\n";
                    fs << "Gio bat dau: " << dsDat[i].bd.gio << ":" << setw(2) << setfill('0') << dsDat[i].bd.phut
                        << "\n";
                    fs << "Gio ket thuc: " << dsDat[i].kt.gio << ":" << setw(2) << setfill('0') << dsDat[i].kt.phut
                        << "\n";
                    fs << "So tien: " << dsTT[i].soTien << "\n";
                    fs << "Cam on quy khach da su dung dich vu!" << "\n";
                }
            }
            fs.close();
            system("start Hoa_don.txt");
        }
        else cout << "Khong tim thay ma khach hang";
    }
};
int Tinhnang::nhapSo(const string& s) {
    int x;
    while (true) {
        cout << s;
        if (cin >> x) break;
        cout << "Du lieu khong hop le. Vui long nhap lai." << endl;
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return x;

}

void Tinhnang::nhapChuoi(const string& s, string& out) {
    cout << s;
    cin.ignore(); getline(cin, out);
}

void Tinhnang::nhapNgay(Ngay& n) {
    do {
        cout << "Nhap ngay (dd mm yyyy): "; cin >> n.ngay >> n.thang >> n.nam;
        if (!n.hopLe()) cout << "Ngay khong hop le. Vui long nhap lai." << endl;
    } while (!n.hopLe());
}

bool Tinhnang::hopLeGio(const Gio& g) {
    return g.gio >= 0 && g.gio < 24 && g.phut >= 0 && g.phut < 60;
}

double Tinhnang::tinhTien(const Gio& bd, const Gio& kt, const &giaCao, const &giaThuong) {
    int phut = (kt.gio * 60 + kt.phut) - (bd.gio * 60 + bd.phut);
    double gio = phut / 60.0;
    if (bd.gio >= 18 && bd.gio < 22) return gio * giaCao;
    return gio * giaThuong;
}

bool Tinhnang::trungGio(const Gio& t, const Gio& bd, const Gio& kt) {
    return !(t < bd) && (t < kt);
}

string Tinhnang::to_string(const int &x) {
   stringstream ss;
   ss << x;
   return ss.str();
}

int main() {
    vector<San> dsSan;
    for (int i = 1;i <= 6;i++) dsSan.push_back(San(i, "Trong nha", "Tham"));
    for (int i = 7;i <= 12;i++) dsSan.push_back(San(i, "Ngoai troi", "Nhua"));
    vector<KhachHang> dsKh;
    vector<DatSan> dsDat;
    vector<ThanhToan> dsTT;
    int nextKh = 1, nextDat = 1, nextTT = 1;
    Tinhnang a;
    San s;
    a.Thuc_hien(dsSan,dsKh,dsDat,dsTT,nextKh,nextDat,nextTT,s);
    return 0;
}
