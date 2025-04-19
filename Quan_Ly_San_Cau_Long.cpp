#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <limits>

using namespace std;

class TrangThaiSan {
public:
    static const int TRONG = 0;
    static const int DA_DAT = 1;
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
    bool operator<(const Ngay& n) const {
        if (nam != n.nam) return nam < n.nam;
        if (thang != n.thang) return thang < n.thang;
        return ngay < n.ngay;
    }
};

class ThoiGianDat {
public:
    Gio batDau;
    Gio ketThuc;
    int maKhachHang;
};

class San {
private:
    int maSo;
    map<Ngay, vector<ThoiGianDat> > lich;
public:
    San(int ma) : maSo(ma) {}
    int layMaSo() const { return maSo; }
    void datSan(const Ngay& ngay,
                const Gio& bd,
                const Gio& kt,
                int maKhachHang) {
        ThoiGianDat tg;
        tg.batDau = bd;
        tg.ketThuc = kt;
        tg.maKhachHang = maKhachHang;
        lich[ngay].push_back(tg);
    }
    vector< pair<Gio, Gio> > layKhungGioDaDat(const Ngay& ngayHienTai) const {
        vector< pair<Gio, Gio> > ketQua;
        map<Ngay, vector<ThoiGianDat> >::const_iterator it
            = lich.find(ngayHienTai);
        if (it == lich.end()) return ketQua;
        const vector<ThoiGianDat>& ds = it->second;
        for (size_t i = 0; i < ds.size(); ++i) {
            ketQua.push_back(
                pair<Gio, Gio>(ds[i].batDau, ds[i].ketThuc)
            );
        }
        return ketQua;
    }
    int trangThaiTrongNgay(const Ngay& ngay) const {
        map<Ngay, vector<ThoiGianDat> >::const_iterator it
            = lich.find(ngay);
        if (it == lich.end() || it->second.empty())
            return TrangThaiSan::TRONG;
        return TrangThaiSan::DA_DAT;
    }
};

class KhachHang {
public:
    int maSo;
    string ten;
    string soDienThoai;
    string diaChi;
};

int nhapSo(const string& thongBao) {
    int x;
    while (true) {
        cout << thongBao;
        if (cin >> x) break;
        cout << "Du lieu khong hop le. Vui long nhap lai." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return x;
}

bool hopLeGio(int gio, int phut) {
    return (gio >= 0 && gio < 24 && phut >= 0 && phut < 60);
}

int main() {
    vector<San> danhSachSan;
    for (int i = 1; i <= 12; ++i) {
        San s(i);
        danhSachSan.push_back(s);
    }

    vector<KhachHang> danhSachKhachHang;

    while (true) {
        cout << endl;
        cout << "===== CHUONG TRINH QUAN LY SAN CAU LONG =====" << endl;
        cout << "1. Them khach hang" << endl;
        cout << "2. Dat san" << endl;
        cout << "3. Xem danh sach khach hang" << endl;
        cout << "4. Xem lich dat san trong ngay" << endl;
        cout << "5. Xem trang thai cac san" << endl;
        cout << "6. Thoat" << endl;

        int luaChon = nhapSo("Lua chon cua ban: ");

        switch (luaChon) {
            case 1: {
                KhachHang kh;
                kh.maSo = danhSachKhachHang.size() + 1;
                cout << "Nhap ten khach hang: ";
                cin.ignore();
                getline(cin, kh.ten);
                cout << "Nhap so dien thoai: ";
                getline(cin, kh.soDienThoai);
                cout << "Nhap dia chi: ";
                getline(cin, kh.diaChi);

                bool tonTai = false;
                for (size_t i = 0; i < danhSachKhachHang.size(); ++i) {
                    if (danhSachKhachHang[i].soDienThoai == kh.soDienThoai) {
                        tonTai = true;
                        break;
                    }
                }
                if (tonTai) {
                    cout << "So dien thoai da ton tai. Vui long kiem tra lai." << endl;
                } else {
                    danhSachKhachHang.push_back(kh);
                    cout << "Da them khach hang thanh cong." << endl;
                }
                break;
            }
            case 2: {
                int maKh = nhapSo("Nhap ma so khach hang: ");
                bool hopLeKH = false;
                for (size_t i = 0; i < danhSachKhachHang.size(); ++i) {
                    if (danhSachKhachHang[i].maSo == maKh) {
                        hopLeKH = true;
                        break;
                    }
                }
                if (!hopLeKH) {
                    cout << "Khong tim thay ma khach hang. Quay lai menu chinh." << endl;
                    break;
                }
                Ngay ngay;
                cout << "Nhap ngay dat (dd mm yyyy): ";
                cin >> ngay.ngay >> ngay.thang >> ngay.nam;

                int maSan;
                do {
                    maSan = nhapSo("Nhap ma san (1-12): ");
                    if (maSan < 1 || maSan > 12) {
                        cout << "Ma san khong hop le. Vui long nhap lai." << endl;
                    }
                } while (maSan < 1 || maSan > 12);

                Gio bd, kt;
                do {
                    cout << "Nhap gio bat dau (gio phut): ";
                    cin >> bd.gio >> bd.phut;
                    cout << "Nhap gio ket thuc (gio phut): ";
                    cin >> kt.gio >> kt.phut;
                    if (!hopLeGio(bd.gio, bd.phut) || !hopLeGio(kt.gio, kt.phut)) {
                        cout << "Gio nhap khong hop le. Vui long nhap lai." << endl;
                    }
                } while (!hopLeGio(bd.gio, bd.phut) || !hopLeGio(kt.gio, kt.phut));

                danhSachSan[maSan - 1].datSan(ngay, bd, kt, maKh);
                cout << "Da dat san thanh cong." << endl;
                break;
            }
            case 3: {
                cout << endl << "Danh sach khach hang:" << endl;
                for (size_t i = 0; i < danhSachKhachHang.size(); ++i) {
                    cout << "Ma khach hang: " << danhSachKhachHang[i].maSo
                         << ", Ten: " << danhSachKhachHang[i].ten
                         << ", SDT: " << danhSachKhachHang[i].soDienThoai
                         << ", Dia chi: " << danhSachKhachHang[i].diaChi
                         << endl;
                }
                break;
            }
            case 4: {
                Ngay ngay;
                cout << "Nhap ngay can xem lich (dd mm yyyy): ";
                cin >> ngay.ngay >> ngay.thang >> ngay.nam;
                for (size_t i = 0; i < danhSachSan.size(); ++i) {
                    vector< pair<Gio, Gio> > lich
                        = danhSachSan[i].layKhungGioDaDat(ngay);
                    cout << "San " << danhSachSan[i].layMaSo() << ": ";
                    if (lich.empty()) {
                        cout << "Trong" << endl;
                    } else {
                        for (size_t j = 0; j < lich.size(); ++j) {
                            cout << lich[j].first.gio << ":" << lich[j].first.phut
                                 << "-" << lich[j].second.gio << ":" << lich[j].second.phut;
                            if (j < lich.size() - 1) cout << ", ";
                        }
                        cout << endl;
                    }
                }
                break;
            }
            case 5: {
                Ngay ngay;
                cout << "Nhap ngay muon kiem tra trang thai san (dd mm yyyy): ";
                cin >> ngay.ngay >> ngay.thang >> ngay.nam;
                for (size_t i = 0; i < danhSachSan.size(); ++i) {
                    int tt = danhSachSan[i].trangThaiTrongNgay(ngay);
                    cout << "San " << danhSachSan[i].layMaSo() << ": "
                         << (tt == TrangThaiSan::TRONG ? "Trong" : "Da dat")
                         << endl;
                }
                break;
            }
            case 6:
                cout << "Cam on da su dung chuong trinh!" << endl;
                return 0;
            default:
                cout << "Lua chon khong hop le. Vui long chon lai." << endl;
        }
    }
    return 0;
}
