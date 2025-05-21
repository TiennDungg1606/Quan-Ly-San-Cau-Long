//khai báo các thư viện cần thiết
#include<iostream>
#include<string>
#include<vector>
#include<limits>
#include<iomanip>
#include<fstream>
#include<sstream>

using namespace std;

//định nghĩa lớp Khách hàng
class KhachHang {
private:
    int maKh;
    string ten;
    string soDienThoai;
    string diaChi;
    //friend để lớp tính năng truy cập được private
    friend class Tinhnang;
};

//định nghĩa lớp giờ
class Gio {
public:
    int gio;
    int phut;
    //Quá tải toán tử so sánh giờ
    bool operator<=(const Gio& g) const {
        return (gio < g.gio) || (gio == g.gio && phut <= g.phut);
    }
    bool operator>=(const Gio& g) const {
        return (gio > g.gio) || (gio == g.gio && phut >= g.phut);
    }
};

//định nghĩa lớp ngày
class Ngay {
public:
    int ngay;
    int thang;
    int nam;
    //Kiểm tra tính hợp lệ của ngày tháng năm
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
    //Quá tải toán tử so sánh ngày tháng năm
    bool operator==(const Ngay& n) const {
        return (ngay == n.ngay && thang == n.thang && nam == n.nam);
    }
};

//định nghĩa lớp quản lí đặt sân
class DatSan {
private:
    int maDat;
    int maSan;
    KhachHang kh;
    Ngay ngay;
    Gio bd, kt;
    //friend để lớp tính năng truy cập được private
    friend class Tinhnang;
};

// định nghĩa lớp thanh toán
class ThanhToan : private DatSan {
private:
    double soTien;
    double no;
    bool daThanh;
    //friend để lớp tính năng truy cập được private
    friend class Tinhnang;
};

//định nghĩa lớp quản lí sân
class San {
private:
    int maSan;
    string loai;
    string beMat;
    bool trangThai;
    int giaCao, giaThuong;
public:
    San(int m, const string& l, const string& b, const bool& t) :maSan(m), loai(l), beMat(b), trangThai(t) {}
    San() {
        giaCao = 120;
        giaThuong = 80;
    }
    //setter
    void taoMaSan(int m) { maSan = m; }
    void taoLoai(const string& l) { loai = l; }
    void taoBeMat(const string& b) { beMat = b; }
    void taoTrangThai(bool t) { trangThai = t; }
    void taoGiaCao(int g) { giaCao = g; }
    void taoGiaThuong(int g) { giaThuong = g; }
    //getter
    int layMaSan() const { return maSan; }
    string layLoai() const { return loai; }
    string layBeMat() const { return beMat; }
    bool layTrangThai() const { return trangThai; }
    int layGiaCao() const { return giaCao; }
    int layGiaThuong() const { return giaThuong; }
};

//định nghĩa lớp tính năng
class Tinhnang {
public:
    //khai báo các hàm thành viên
    int nhapSo(const string& s);
    void nhapChuoi(const string& s, string& out);
    void nhapNgay(Ngay& n);
    bool hopLeGio(const Gio& g);
    double tinhTien(const Gio& bd, const Gio& kt, const San& s);
    bool trungGio(const Gio& bd1, const Gio& kt1, const Gio& bd2, const Gio& kt2);
    string to_string(int x);
    // Hàm dừng và xóa màn hình sau mỗi chức năng
    void pauseAndClear() {
        cout << "\nNhan phim enter de tro lai menu...";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Xóa sạch bộ đệm
        cin.get();
        system("cls");
    }
    void Thuc_hien(vector<San>& dsSan, vector<KhachHang>& dsKh, vector<DatSan>& dsDat, vector<ThanhToan>& dsTT, int& nextKh, int& nextDat, int& nextTT, San& s) {
        while (true) {
            cout << "\n===================== MENU ======================" << endl;
            cout << "|" << "1. Quan ly san" << "                                 |" << endl; //xem danh sách sân/cập mặt nhật sân/cập nhật trạng thái sân
            cout << "|" << "2. Dat san/Huy san" << "                             |" << endl;
            cout << "|" << "3. Quan ly khach hang" << "                          |" << endl;
            cout << "|" << "4. Thanh toan" << "                                  |" << endl;
            cout << "|" << "5. Bao cao thong ke" << "                            |" << endl; //MENU làm việc của dự án
            cout << "|" << "6. Tra cuu" << "                                     |" << endl;
            cout << "|" << "7. Xuat danh sach thong tin khach hang" << "         |" << endl;
            cout << "|" << "8. Xuat hoa don khach hang" << "                     |" << endl;
            cout << "|" << "0. Thoat" << "                                       |" << endl;
            cout << "=================================================" << endl;
            int c = nhapSo("Lua chon: ");
            switch (c) {
            case 1: {
                quan_ly_san(dsSan, s);
                pauseAndClear();
                break;
            }
            case 2: {
                Dat_Huy(dsSan, dsKh, dsDat, dsTT, nextKh, nextDat, nextTT, s);
                pauseAndClear();
                break;
            }
            case 3: {
                Quan_ly_Kh(dsSan, dsKh, dsDat, nextKh);
                pauseAndClear();
                break;
            }
            case 4: {
                Thanh_toan(dsTT);
                pauseAndClear();
                break;
            }
            case 5: {
                Doanh_thu(dsTT, dsKh, dsDat);
                pauseAndClear();
                break;
            }
            case 6: {
                Tim_kiem(dsKh, dsDat);
                pauseAndClear();
                break;
            }
            case 7: {
                Xuat_ds(dsKh);
                pauseAndClear();
                break;
            }
            case 8: {
                Xuat_hoa_don(dsKh, dsDat, dsTT);
                pauseAndClear();
                break;
            }
            case 0:
                cout << "Thoat chuong trinh!";
                return;
            default: {
                cout << "Lua chon khong hop le. Vui long nhap lai." << endl;
                pauseAndClear();
                break;
            }
            }
        }
    }
private:
    void quan_ly_san(vector<San>& dsSan, San& s) {
        cout << "1.Xem trang thai san\n";
        cout << "2.Cap nhat mat san\n";
        cout << "3.Cap nhat trang thai san\n";
        cout << "4.Cap nhat gia san\n";
        int m = nhapSo("Lua chon: ");
        if (m == 1) {
            cout << "Gia san hien tai: " << endl;
            cout << "Gia cao: " << s.layGiaCao() << " nghin" << endl;
            cout << "Gia thuong: " << s.layGiaThuong() << " nghin" << endl;
            cout << "-*-*-*-*-*-*-* Danh sach san *-*-*-*-*-*-*-*-*-*" << endl;
            // In bảng danh sách sân với khung chữ nhật đẹp
            int width1 = 8, width2 = 15, width3 = 15, width4 = 15;
            cout << "+" << string(width1, '-') << "+" << string(width2, '-') << "+" << string(width3, '-') << "+" << string(width4, '-') << "+" << endl;
            // In tiêu đề
            cout << "|" << left << setw(width1) << "Ma San"
                << "|" << left << setw(width2) << "Loai"
                << "|" << left << setw(width3) << "Be Mat"
                << "|" << left << setw(width4) << "Trang Thai" << "|" << endl;
            // In dòng phân cách tiêu đề
            cout << "+" << string(width1, '-') << "+" << string(width2, '-') << "+" << string(width3, '-') << "+" << string(width4, '-') << "+" << endl;
            // In từng dòng dữ liệu
            for (size_t i = 0; i < dsSan.size(); i++) {
                cout << "|" << left << setw(width1) << dsSan[i].layMaSan()
                    << "|" << left << setw(width2) << dsSan[i].layLoai()
                    << "|" << left << setw(width3) << dsSan[i].layBeMat()
                    << "|" << left << setw(width4) << (dsSan[i].layTrangThai() ? "Tot" : "Bao tri") << "|" << endl;
                // Nếu muốn kẻ bên trong từng dòng:
                cout << "+" << string(width1, '-') << "+" << string(width2, '-') << "+" << string(width3, '-') << "+" << string(width4, '-') << "+" << endl;
            }
        }
        if (m == 2) {
            while (true) {
                int ma = nhapSo("Ma san: ");
                bool ktra = false;
                for (size_t i = 0; i < dsSan.size(); i++) {
                    if (dsSan[i].layMaSan() == ma) {
                        cout << "Nhap loai san ban muon cap nhat: ";
                        string bemat;
                        getline(cin >> ws, bemat);
                        dsSan[i].taoBeMat(bemat);
                        ktra = true;
                        cout << "*-*-*-*Cap nhat thanh cong*-*-*-*\n";
                        break;
                    }
                }
                if (!ktra) { cout << "Ma san khong hop le!"; }
                cout << "Ban co muon tiep tuc cap nhat?(0-co,1-khong)\n";
                int so = nhapSo("Lua chon: ");
                if (so == 1) break;
            }
        }
        if (m == 3) {
            while (true) {
                int ma = nhapSo("Ma san muon thay doi trang thai: ");
                bool ktra = false;
                for (size_t i = 0; i < dsSan.size(); i++) {
                    if (dsSan[i].layMaSan() == ma) {
                        int n = nhapSo("Ban muon thay doi?(0-Bao tri,1-Trang thai tot): ");
                        if (n == 0) { dsSan[i].taoTrangThai(false); }
                        if (n == 1) { dsSan[i].taoTrangThai(true); }
                        cout << "*-*-*-*Cap nhat thanh cong*-*-*-*\n";
                        ktra = true;
                        break;
                    }
                }
                if (!ktra) { cout << "*-*-*-*Ma khong hop le!*-*-*-*\n"; }
                cout << "Ban co muon tiep tuc cap nhat?(0-co,1-khong)\n";
                int so = nhapSo("Lua chon: ");
                if (so == 1) break;
            }
        }
        else if (m == 4) {
            cout << "Bạn muốn cập nhật giá nào? (1-Gia cao, 2-Gia thuong): \n";
            int n = nhapSo("Lua chon: ");
            if (n == 1) {
                int g = nhapSo("Nhap gia cao: ");
                s.taoGiaCao(g);
                cout << "*-*-*-*Cap nhat thanh cong*-*-*-*\n";
            }
            else if (n == 2) {
                int g = nhapSo("Nhap gia thuong: ");
                s.taoGiaThuong(g);
                cout << "*-*-*-*Cap nhat thanh cong*-*-*-*\n";
            }
            else {
                cout << "Lua chon khong hop le." << endl;
            }
        }
    }

    void Dat_Huy(vector<San>& dsSan, vector<KhachHang>& dsKh, vector<DatSan>& dsDat, vector<ThanhToan>& dsTT, int& nextKh, int& nextDat, int& nextTT, San& s) {
        cout << "1. Dat san" << "\n";
        cout << "2. Huy san" << "\n";
        int m = nhapSo("Lua chon: ");
        if (m == 1) {
            DatSan d;
            int isMember = nhapSo("La thanh vien? (1-Co,0-Khach vang lai): ");
            int maKh;
            if (isMember == 1) {
                maKh = nhapSo("Ma khach hang: ");
                bool ok = false;
                int j;
                for (size_t i = 0;i < dsKh.size();i++) {
                    if (dsKh[i].maKh == maKh) {
                        ok = true;
                        j = i;
                        break;
                    }
                }
                if (!ok) {
                    cout << "Khach hang khong hop le." << endl;
                    return;
                }
                else {
                    d.kh = dsKh[j];
                }
            }
            else if (isMember == 0) {
                maKh = 0;
                KhachHang vangLai;
                vangLai.maKh = 0;
                vangLai.ten = "Khach vang lai";
                vangLai.soDienThoai = "";
                vangLai.diaChi = "";
                d.kh = vangLai;
            }
            else {
                cout << "Lua chon khong hop le." << endl;
                return;
            }
            d.maDat = nextDat++;
            nhapNgay(d.ngay);
            cout << "*-*-*-*-*-* Danh sach san *-*-*-*-*-*" << endl;
            // Table for Danh sach san
            int width1 = 8, width2 = 12, width3 = 40;
            cout << string(width1, '-') << "+" << string(width2, '-') << "+" << string(width3, '-') << endl;
            cout << setw(width1) << left << "Ma san" << "|"
                 << setw(width2) << left << "Trang thai" << "|"
                 << setw(width3) << left << "Khung gio" << endl;
            cout << string(width1, '-') << "+" << string(width2, '-') << "+" << string(width3, '-') << endl;
            for (size_t i = 0; i < dsSan.size(); i++) {
                string khungGio = "";
                for (size_t j = 0; j < dsDat.size(); j++) {
                    if (dsDat[j].ngay == d.ngay && dsDat[j].maSan == dsSan[i].layMaSan()) {
                        if (!khungGio.empty()) khungGio += ", ";
                        khungGio += to_string(dsDat[j].bd.gio) + ":" + (dsDat[j].bd.phut < 10 ? "0" : "") + to_string(dsDat[j].bd.phut)
                            + "-" + to_string(dsDat[j].kt.gio) + ":" + (dsDat[j].kt.phut < 10 ? "0" : "") + to_string(dsDat[j].kt.phut);
                    }
                }
                if (khungGio.empty()) khungGio = "Trong";
                string trangThai = dsSan[i].layTrangThai() ? "Tot" : "Bao tri";
                cout << setw(width1) << left << dsSan[i].layMaSan() << "|"
                     << setw(width2) << left << trangThai << "|"
                     << setw(width3) << left << khungGio << endl;
                cout << string(width1, '-') << "+" << string(width2, '-') << "+" << string(width3, '-') << endl;
            }
            cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << endl;
            cout << "Khung gio mo cua tu 5:00 - 22:00." << endl;
            d.maSan = nhapSo("*Ma san (1-12): ");
            while (d.maSan < 1 || d.maSan>12 || dsSan[d.maSan - 1].layTrangThai() == false) {
                cout << "Ma san khong hop le hoac san dang duoc bao tri. Vui long nhap lai." << endl;
                d.maSan = nhapSo("*Ma san (1-12): ");
            }
            cout << "*Nhap gio, phut bat dau (g p): "; cin >> d.bd.gio >> d.bd.phut;
            while (!hopLeGio(d.bd)) {
                cout << "Gio khong hop le. Vui long nhap lai: "; cin >> d.bd.gio >> d.bd.phut;
            }
            cout << "*Nhap gio, phut ket thuc (g p): "; cin >> d.kt.gio >> d.kt.phut;
            while (!hopLeGio(d.kt)) {
                cout << "Gio khong hop le. Vui long nhap lai: "; cin >> d.kt.gio >> d.kt.phut;
            }
            if (d.kt <= d.bd) {
                cout << "Gio ket thuc phai lon hon gio bat dau." << endl;
                return;
            }
            bool trung = false;
            for (size_t i = 0;i < dsDat.size();i++) {
                if (dsDat[i].maSan == d.maSan && dsDat[i].ngay == d.ngay) {
                    if (trungGio(d.bd, d.kt, dsDat[i].bd, dsDat[i].kt)) {
                        trung = true; break;
                    }
                }
            }
            if (trung) {
                cout << "Khung gio da duoc dat. Quay lai menu." << endl;
                nextDat--;
            }
            else {
                dsDat.push_back(d);
                double tien = tinhTien(d.bd, d.kt, s);
                ThanhToan tt;
                tt.daThanh = false;
                cout << "*So tien can thanh toan: " << tien << " nghin" << endl;
                if (isMember == 0) {
                    cout << "Khach vang lai phai thanh toan tien!" << endl;
                    tt.maDat = d.maDat;
                    tt.kh = d.kh;
                    tt.soTien = tien;
                    tt.daThanh = true;
                    dsTT.push_back(tt);
                    cout << "*-*-*-* Dat San Thanh Cong! *-*-*-*\n";
                    cout << "         Ma dat san: " << right << setw(4) << setfill('0') << d.maDat << '.' << endl;
                }
                else {
                    int daTT = nhapSo("Ban muon (1-Thanh toan, 0-Tra sau)?: ");
                    if (daTT == 1) {
                        tt.maDat = d.maDat;
                        tt.kh = d.kh;
                        tt.soTien = tien;
                        tt.no = 0.0;
                        tt.daThanh = true;
                        dsTT.push_back(tt);
                        cout << "*-*-*-*-*-*-*-* Dat san thanh cong *-*-*-*-*-*-*-*" << endl;
                        cout << "                 Ma dat san: "<< right << setw(4) << setfill('0') << d.maDat << '.' << endl;
                    }
                    else {
                        tt.maDat = d.maDat;
                        tt.kh = d.kh;
                        tt.no = tien;
                        tt.soTien = 0.0;
                        tt.daThanh = false;
                        dsTT.push_back(tt);
                        cout << "*-*-*-*-*-*-*-* Dat san thanh cong *-*-*-*-*-*-*-*" << endl;
                        cout << "                 Ma dat san: " << right << setw(4) << setfill('0') << d.maDat << '.' << endl;
                    }
                }
                cout << setfill(' ');
            }
        }
        else if (m == 2) {
            int maDat = nhapSo("Ma dat san: ");
            bool co = false;
            for (size_t i = 0;i < dsDat.size();i++) {
                if (dsDat[i].maDat == maDat) {
                    co = true;
                    dsDat.erase(dsDat.begin() + i);
                    dsTT.erase(dsTT.begin() + i);
                    break;
                }
            }
            if (co == false) cout << "*-*-*-*-*-*-* Ma dat khong hop le *-*-*-*-*-*-*" << endl;
            else cout << "*-*-*-*-*-*-* Huy dat san thanh cong *-*-*-*-*-*-*" << endl;
        }
    }
    void Quan_ly_Kh(vector<San>& dsSan, vector<KhachHang>& dsKh, vector<DatSan>& dsDat, int& nextKh) {
        cout << "1. Dang ki khach hang" << endl;
        cout << "2. Cap nhat thong tin khach hang" << endl;
        cout << "3. Xem lich su dat san cua khach" << endl;
        int m = nhapSo("Lua chon: ");
        if (m == 1) {
            cout << "*************************************************\n";
            KhachHang kh;
            nhapChuoi("Ten: ", kh.ten);
            nhapChuoi("SDT: ", kh.soDienThoai);
            nhapChuoi("Dia chi: ", kh.diaChi);

            bool soTrung = false;
            for (size_t i = 0; i < dsKh.size(); i++) {
                if (dsKh[i].soDienThoai == kh.soDienThoai) {
                    soTrung = true;
                    break;
                }
            }

            if (soTrung) {
                cout << "So dien thoai da ton tai. Khong the them khach hang." << endl;
                return;
            }
            else {
                kh.maKh = nextKh++;
                dsKh.push_back(kh);
                cout << "**** Them khach hang thanh cong. Ma KH: "
                   << right << setw(4) << setfill('0') << kh.maKh << setfill(' ')<< " ****" << endl;
            }
        }
        else if (m == 2) {
            int makh = nhapSo("Nhap ma khach hang: ");
            bool ktra = false;
            int j;
            for (size_t i = 0; i < dsKh.size(); i++) {
                if (dsKh[i].maKh == makh) {
                    j = i;
                    ktra = true;
                    break;
                }
            }
            if (!ktra) {
                cout << "Ma khach hang khong ton tai." << endl;
                return;
            }
            else {
                cout << "Can cap nhat thong tin gi? (1-Ten, 2-SDT, 3-Dia chi): ";
                KhachHang kh1;
                int n = nhapSo("Lua chon: ");
                if (n == 1) {
                    nhapChuoi("Ten: ", kh1.ten);
                    dsKh[j].ten = kh1.ten;
                    cout << "Cap nhat thanh cong!" << endl;
                }
                else if (n == 2) {
                    nhapChuoi("SDT: ", kh1.soDienThoai);
                    bool soTrung = false;
                    for (size_t i = 0; i < dsKh.size(); i++) {
                        if (dsKh[i].soDienThoai == kh1.soDienThoai && dsKh[i].maKh != makh) {
                            soTrung = true;
                            break;
                        }
                    }
                    if (soTrung) {
                        cout << "So dien thoai da ton tai. Khong the cap nhat." << endl;
                        return;
                    }
                    else {
                        dsKh[j].soDienThoai = kh1.soDienThoai;
                        cout << "Cap nhat thanh cong!" << endl;
                    }
                }
                else if (n == 3) {
                    nhapChuoi("Dia chi: ", kh1.diaChi);
                    dsKh[j].diaChi = kh1.diaChi;
                    cout << "Cap nhat thanh cong!" << endl;
                }
            }
        }
        else if (m == 3) {
            int ma = nhapSo("Ma KH: ");
            bool co = false;
            for (size_t i = 0; i < dsKh.size(); i++) {
                if (dsKh[i].maKh == ma) {
                    co = true;
                    break;
                }
            }
            if (co == false) {
                cout << "*-*-*-*Ma khach hang khong hop le! *-*-*-*" << endl;
            }
            else {
                cout << "*-*-*-*-*-*-* Lich su dat san *-*-*-*-*-*-*" << endl;
                int dem = 0;
                for (size_t i = 0; i < dsDat.size(); i++) {
                    if (dsDat[i].kh.maKh == ma) {
                        dem++;
                    }
                }
                if (dem == 0) { cout << "      Khach hang chua thuc hien dat san!"; }
                else {
                    for (size_t i = 0; i < dsDat.size(); i++) {
                        if (dsDat[i].kh.maKh == ma) {
                            cout << "Ma dat: " << right <<setw(4) << setfill('0') << dsDat[i].maDat << ", San " << dsDat[i].maSan
                                << ", " << dsDat[i].ngay.ngay << "/" << dsDat[i].ngay.thang
                                << "/" << dsDat[i].ngay.nam << ", "
                                << dsDat[i].bd.gio << ":" <<right << setw(2) << setfill('0') << dsDat[i].bd.phut
                                << "-" << dsDat[i].kt.gio << ":" << right << setw(2) << setfill('0') << dsDat[i].kt.phut
                                << setfill(' ') << endl;
                        }
                    }
                }
            }
        }
    }

    void Thanh_toan(vector<ThanhToan>& dsTT) {
        cout << "1. Lich su thanh toan\n";
        cout << "2. Tra no\n";
        int m = nhapSo("Lua chon: ");
        if (m == 1) {
            cout << "Lich su thanh toan:" << endl;
            int width1 = 12, width2 = 16, width3 = 24, width4 = 14, width5 = 16;
            cout << "+" << string(width1, '-') << "+" << string(width2, '-') << "+" << string(width3, '-') << "+" << string(width4, '-') << "+" << string(width5, '-') << "+" << endl;
            cout << "|" << left << setw(width1) << "Ma dat san"
                 << "|" << left << setw(width2) << "Ma khach hang"
                 << "|" << left << setw(width3) << "Ten khach hang"
                 << "|" << left << setw(width4) << "So tien"
                 << "|" << left << setw(width5) << "Trang thai" << "|" << endl;
            cout << "+" << string(width1, '-') << "+" << string(width2, '-') << "+" << string(width3, '-') << "+" << string(width4, '-') << "+" << string(width5, '-') << "+" << endl;
            for (size_t i = 0; i < dsTT.size(); i++) {
                string tien = to_string(dsTT[i].daThanh ? dsTT[i].soTien : dsTT[i].no) + " nghin";
                string trangthai = dsTT[i].daThanh ? "Da thanh toan" : "Chua thanh toan";
                cout << "|" << right << setw(4) << setfill('0') << dsTT[i].maDat << setw(9) << setfill(' ')
                     << "|" << right << setw(4) << setfill('0') << dsTT[i].kh.maKh << setw(13) << setfill(' ')
                     << "|" << left << setw(width3) << setfill(' ') << dsTT[i].kh.ten
                     << "|" << left << setw(width4) << setfill(' ') << tien
                     << "|" << left << setw(width5) << setfill(' ') << trangthai << "|" << endl;
                cout << "+" << string(width1, '-') << "+" << string(width2, '-') << "+" << string(width3, '-') << "+" << string(width4, '-') << "+" << string(width5, '-') << "+" << endl;
            }
        }
        if (m == 2) {
            cout << "Nhap ma dat san: ";
            int madat, j;
            cin >> madat;
            bool ktra = false;
            for (size_t i = 0; i < dsTT.size();i++) {
                if (dsTT[i].maDat == madat) {
                    ktra = true;
                    j = i;
                    break;
                }
            }
            if (!ktra) { cout << "Khong ton tai ma dat!"; return; }
            else {
                {
                    if (dsTT[j].daThanh == false && dsTT[j].maDat == madat) {
                        dsTT[j].soTien = dsTT[j].no;
                        dsTT[j].no = 0.0;
                        dsTT[j].daThanh = true;
                    }
                }
                cout << "*-*-*-* Tra no thanh cong *-*-*-*\n";
            }
        }
    }
    void Doanh_thu(vector<ThanhToan>& dsTT, vector<KhachHang>& dsKh, vector<DatSan>& dsDat) {
        cout << "1. Xem doanh thu\n";
        cout << "2. Danh sach khach hang con no\n";
        int n = nhapSo("Lua chon : ");
        int count = 0;
        if (n == 1) {
            double sum = 0.0;
            for (size_t i = 0;i < dsTT.size();i++) {
                sum += dsTT[i].soTien;
                count++;
            }
            cout << "Doanh thu: " << sum << " nghin" << endl;
            cout << "So luot dat san: " << count << endl;
        }
        if (n == 2) {
            cout << "================Danh sach khach hang con no=============" << endl;
            int width1 = 12, width2 = 18, width3 = 24, width4 = 18;
            cout << "+" << string(width1, '-') << "+" << string(width2, '-') << "+" << string(width3, '-') << "+" << string(width4, '-') << "+" << endl;
            cout << "|" << left << setw(width1) << "Ma dat san"
                << "|" << left << setw(width2) << "Ma khach hang"
                << "|" << left << setw(width3) << "Ten khach hang"
                << "|" << left << setw(width4) << "So tien" << "|" << endl;
            cout << "+" << string(width1, '-') << "+" << string(width2, '-') << "+" << string(width3, '-') << "+" << string(width4, '-') << "+" << endl;
            for (size_t i = 0;i < dsTT.size();i++) {
                if (dsTT[i].daThanh == false) {
                    string tienno = to_string(dsTT[i].no) + " nghin";
                    cout << "|"<< right << setw(4) << setfill('0') << dsTT[i].maDat << setw(9) << setfill(' ')
                        << "|" << right << setw(4) << setfill('0') << dsTT[i].kh.maKh << setw(15) << setfill(' ')
                        << "|" << left << setw(width3) << setfill(' ') << dsTT[i].kh.ten
                        << "|" << left << setw(width4) << setfill(' ') << tienno << "|" << endl;
                    cout << "+" << string(width1, '-') << "+" << string(width2, '-') << "+" << string(width3, '-') << "+" << string(width4, '-') << "+" << endl;
                }
            }
        }
    }
    void Tim_kiem(vector<KhachHang>& dsKh, vector<DatSan>& dsDat) {
        cout << "1. Tra cuu thong tin khach hang" << endl;
        cout << "2. Tra cuu thong tin dat san " << endl;
        int m = nhapSo("Lua chon: ");
        if (m == 1) {
            string key;
            cout << "Nhap tu khoa (maKH, ten, SDT, dia chi): ";
            getline(cin >> ws, key);
            cout << "Ket qua tim kiem:" << endl;

            for (size_t i = 0; i < dsKh.size(); i++) {
                string maKhStr = to_string(dsKh[i].maKh);
                while (maKhStr.length() < 4) maKhStr = "0" + maKhStr;

                if (maKhStr == key || dsKh[i].soDienThoai == key) {
                    cout << "MaKH:" <<right << setw(4) << setfill('0') << dsKh[i].maKh << setfill(' ') << ", "
                        << " Ten:" << dsKh[i].ten << ", "
                        << " SDT:" << dsKh[i].soDienThoai << ", "
                        << " Dia chi:" << dsKh[i].diaChi << endl;
                    break;
                }
                else if
                    (dsKh[i].ten.find(key) != string::npos ||
                        dsKh[i].diaChi.find(key) != string::npos) {

                    cout << "MaKH:" <<right<< setw(4) << setfill('0') << dsKh[i].maKh << setfill(' ') << ", "
                        << " Ten:" << dsKh[i].ten << ", "
                        << " SDT:" << dsKh[i].soDienThoai << ", "
                        << " Dia chi:" << dsKh[i].diaChi << endl;
                }
            }
        }
        else if (m == 2) {
            int maDat = nhapSo("Nhap ma dat san: ");
            cout << "Ket qua tim kiem:" << endl;
            for (size_t i = 0; i < dsDat.size(); i++) {
                if (dsDat[i].maDat == maDat) {
                    cout << "MaKH:" << right<< setw(4) << setfill('0') << dsDat[i].kh.maKh << setfill(' ') << ", "
                        << " Ten:" << dsDat[i].kh.ten << ", "
                        << " Ma san:" <<right<< setw(4) << setfill('0') << dsDat[i].maSan << ", "
                        << " Ngay dat:" << dsDat[i].ngay.ngay << "/" << dsDat[i].ngay.thang
                        << "/" << dsDat[i].ngay.nam << ", "
                        << " Thoi gian:" << dsDat[i].bd.gio << ":" << right<<setw(2) << setfill('0') << dsDat[i].bd.phut
                        << "-" << dsDat[i].kt.gio << ":" <<right<< setw(2) << setfill('0') << dsDat[i].kt.phut
                        << ". " << endl;
                    break;
                }
            }
        }
    }
    void Xuat_ds(vector<KhachHang>& dsKh) {
        if (dsKh.empty()) {
            cout << "Khong co khach hang nao." << endl;
        }
        else {
            cout << "===========Danh sach khach hang==========" << "\n";
            int width1 = 15, width2 = 24, width3 = 18, width4 = 18;
            cout << "+" << string(width1, '-') << "+" << string(width2, '-') << "+" << string(width3, '-') << "+" << string(width4, '-') << "+" << endl;
            cout << "|" << left << setw(width1) << "Ma khach hang"
                << "|" << left << setw(width2) << "Ten"
                << "|" << left << setw(width3) << "So dien thoai"
                << "|" << left << setw(width4) << "Dia chi" << "|" << endl;
            cout << "+" << string(width1, '-') << "+" << string(width2, '-') << "+" << string(width3, '-') << "+" << string(width4, '-') << "+" << endl;
            for (size_t i = 0; i < dsKh.size(); i++) {
                cout << "|" << right << setw(4) << setfill('0') << dsKh[i].maKh << setw(12) << setfill(' ');
                cout << "|" << left << setw(width2) << setfill(' ') << dsKh[i].ten;
                cout << "|" << left << setw(width3) << setfill(' ') << dsKh[i].soDienThoai;
                cout << "|" << left << setw(width4) << setfill(' ') << dsKh[i].diaChi << "|" << endl;
                cout << "+" << string(width1, '-') << "+" << string(width2, '-') << "+" << string(width3, '-') << "+" << string(width4, '-') << "+" << endl;
            }
        }
    }
    void Xuat_hoa_don(vector<KhachHang>& dsKh, vector<DatSan> dsDat, vector<ThanhToan>& dsTT) {
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
                if (dsDat[i].kh.maKh == maKh) {
                    fs << "Ma dat: " <<right<< setw(4) << setfill('0') << dsDat[i].maDat << setfill(' ') << "\n";
                    fs << "Ma san: " << dsDat[i].maSan << "\n";
                    fs << "Ngay dat: " << dsDat[i].ngay.ngay << "/" << dsDat[i].ngay.thang
                        << "/" << dsDat[i].ngay.nam << "\n";
                    fs << "Gio bat dau: " << dsDat[i].bd.gio << ":" <<right<< setw(2) << setfill('0') << dsDat[i].bd.phut
                        << "\n";
                    fs << "Gio ket thuc: " << dsDat[i].kt.gio << ":" <<right<< setw(2) << setfill('0') << dsDat[i].kt.phut
                        << "\n";
                    fs << "So tien: " << (dsTT[i].daThanh ? dsTT[i].soTien : dsTT[i].no) << "nghin.\n";

                    if (dsTT[i].daThanh == true)
                        fs << "*-*-*-*-*-* Khach hang da thanh toan *-*-*-*-*-*\n";

                    else fs << "*-*-*-*-* Khach hang chua thanh toan. Vui long thanh toan! *-*-*-*-*\n";
                    fs << "==================================================" << "\n";
                }
            }
            fs << "Cam on quy khach da su dung dich vu!" << "\n";
        }
        else cout << "Khong tim thay ma khach hang";
        fs.close();
        system("start Hoa_don.txt");
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
    getline(cin >> ws, out); // dùng ws để loại bỏ khoảng trắng đầu, không làm mất số 0
}

void Tinhnang::nhapNgay(Ngay& n) {
    do {
        cout << "Nhap ngay (dd mm yyyy): "; cin >> n.ngay >> n.thang >> n.nam;
        if (!n.hopLe()) cout << "Ngay khong hop le. Vui long nhap lai." << endl;
    } while (!n.hopLe());
}

bool Tinhnang::hopLeGio(const Gio& g) {
    return g.gio >= 5 && g.gio < 22 && g.phut >= 0 && g.phut < 60;
}

double Tinhnang::tinhTien(const Gio& bd, const Gio& kt, const San& s) {
    int phut = (kt.gio * 60 + kt.phut) - (bd.gio * 60 + bd.phut);
    double gio = phut / 60.0;
    if (bd.gio >= 18 && bd.gio < 22) return gio * s.layGiaCao();
    return gio * s.layGiaThuong();
}

bool Tinhnang::trungGio(const Gio& bd1, const Gio& kt1, const Gio& bd2, const Gio& kt2) {
    // Trả về true nếu hai khoảng [bd1, kt1] và [bd2, kt2] giao nhau
    return !(kt1 <= bd2 || kt2 <= bd1);
}

string Tinhnang::to_string(int x) {
    stringstream ss;
    ss << x;
    return ss.str();
}
int main() {
    vector<San> dsSan;
    for (int i = 1;i <= 6;i++) dsSan.push_back(San(i, "Trong nha", "Tham", true));
    for (int i = 7;i <= 12;i++) dsSan.push_back(San(i, "Ngoai troi", "Nhua", true));
    vector<KhachHang> dsKh;
    vector<DatSan> dsDat;
    vector<ThanhToan> dsTT;
    San s;
    int nextKh = 1, nextDat = 1, nextTT = 1;
    Tinhnang a;
    a.Thuc_hien(dsSan, dsKh, dsDat, dsTT, nextKh, nextDat, nextTT, s);
    return 0;
}
