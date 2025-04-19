#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <algorithm>
#include <sstream>

using namespace std;

enum CourtStatus { AVAILABLE, RESERVED, IN_USE };

struct Date {
    int day, month, year;
    bool operator<(const Date& o) const {
        if (year != o.year) return year < o.year;
        if (month != o.month) return month < o.month;
        return day < o.day;
    }
    bool operator==(const Date& o) const {
        return day == o.day && month == o.month && year == o.year;
    }
};

struct Time {
    int hour, minute;
    bool operator<(const Time& o) const {
        if (hour != o.hour) return hour < o.hour;
        return minute < o.minute;
    }
    bool operator==(const Time& o) const {
        return hour == o.hour && minute == o.minute;
    }
    bool operator<=(const Time& o) const { return (*this < o) || (*this == o); }
    bool operator>=(const Time& o) const { return !(*this < o); }
};

bool validDate(int d, int m, int y) {
    if (y < 1900 || m < 1 || m > 12 || d < 1) return false;
    int mdays[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    bool leap = (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
    if (leap) mdays[2] = 29;
    return d <= mdays[m];
}

bool validTime(int h, int mi) {
    return h >= 0 && h < 24 && mi >= 0 && mi < 60;
}

class Customer {
    int id;
    string name, phone, address;
public:
    Customer(): id(0) {}
    Customer(int _id, const string& n, const string& p, const string& a)
        : id(_id), name(n), phone(p), address(a) {}
    int getID() const { return id; }
    string getName() const { return name; }
    string getPhone() const { return phone; }
    string getAddress() const { return address; }
};

class Court {
    int id;
    string type;
    double peakRate, offRate;
    map< Date, map< Time, CourtStatus > > schedule;
public:
    Court(): id(0), peakRate(0), offRate(0) {}
    Court(int _id, const string& t, double pr, double ofr)
        : id(_id), type(t), peakRate(pr), offRate(ofr) {}
    int getID() const { return id; }
    string getType() const { return type; }
    double getPeakRate() const { return peakRate; }
    double getOffRate() const { return offRate; }
    void setStatus(const Date& d, const Time& t, CourtStatus s) {
        schedule[d][t] = s;
    }
    map< Time, CourtStatus >& getDaySchedule(const Date& d) {
        return schedule[d];
    }
    vector< pair< Time, Time > > getReserved(const Date& d) const {
        vector< pair< Time, Time > > v;
        map< Date, map< Time, CourtStatus > >::const_iterator it = schedule.find(d);
        if (it == schedule.end()) return v;
        const map< Time, CourtStatus >& daySched = it->second;
        vector< Time > times;
        for (map< Time, CourtStatus >::const_iterator jt = daySched.begin(); jt != daySched.end(); ++jt) {
            if (jt->second == RESERVED) times.push_back(jt->first);
        }
        if (times.empty()) return v;
        Time start = times[0], prev = times[0];
        for (size_t i = 1; i < times.size(); ++i) {
            int prevMin = prev.hour * 60 + prev.minute;
            int curMin = times[i].hour * 60 + times[i].minute;
            if (curMin == prevMin + 30) {
                prev = times[i];
            } else {
                Time end = prev;
                end.minute += 30;
                if (end.minute >= 60) { end.minute -= 60; end.hour++; }
                v.push_back(make_pair(start, end));
                start = times[i];
                prev = times[i];
            }
        }
        Time end = prev;
        end.minute += 30;
        if (end.minute >= 60) { end.minute -= 60; end.hour++; }
        v.push_back(make_pair(start, end));
        return v;
    }
};

struct Reservation { int rid, cid, courtId; Date date; Time start, end; };
struct Payment { int pid, rid; double amt; string method, detail; Date date; };

int calcDuration(const Time& s, const Time& e) {
    return (e.hour - s.hour) * 60 + (e.minute - s.minute);
}

int main() {
    vector< Customer > customers;
    vector< Court > courts;
    vector< Reservation > reservations;
    vector< Payment > payments;
    int nextCust = 1001, nextRes = 1, nextPay = 1;
    for (int i = 1; i <= 6; ++i) courts.push_back(Court(i, "Trong nha", 100, 50));
    for (int i = 7; i <= 12; ++i) courts.push_back(Court(i, "Ngoai troi", 80, 40));

    int choice;
    do {
        cout << "\n=== Quan Ly San Cau Long ===\n";
        cout << "1. Xem danh sach san\n";
        cout << "2. Dang ky khach hang\n";
        cout << "3. Xem danh sach khach hang\n";
        cout << "4. Dat san\n";
        cout << "5. Xem lich dat san\n";
        cout << "0. Thoat\n";
        cout << "Lua chon: "; cin >> choice; cin.ignore();
        switch (choice) {
            case 1: {
                for (size_t i = 0; i < courts.size(); ++i) {
                    cout << "ID=" << courts[i].getID()
                         << " |" << courts[i].getType()
                         << " |Peak=" << courts[i].getPeakRate()
                         << " |Off=" << courts[i].getOffRate() << "k\n";
                }
                break;
            }
            case 2: {
                string n, p, a;
                cout << "Nhap ten: "; getline(cin, n);
                cout << "Phone: "; getline(cin, p);
                cout << "Dia chi: "; getline(cin, a);
                bool dup = false;
                for (size_t i = 0; i < customers.size(); ++i) {
                    if (customers[i].getPhone() == p) { dup = true; break; }
                }
                if (dup) cout << "Phone da ton tai!\n";
                else {
                    customers.push_back(Customer(nextCust, n, p, a));
                    cout << "Dang ky thanh cong, ID=" << nextCust << "\n";
                    nextCust++;
                }
                break;
            }
            case 3: {
                if (customers.empty()) cout << "Danh sach khach hang trong!\n";
                else {
                    for (size_t i = 0; i < customers.size(); ++i) {
                        cout << customers[i].getID()
                             << " |" << customers[i].getName()
                             << " |" << customers[i].getPhone()
                             << " |" << customers[i].getAddress() << "\n";
                    }
                }
                break;
            }
            case 4: {
                Date d;
                while (true) {
                    int day, mon, yr;
                    cout << "Nhap ngay (dd mm yyyy): "; cin >> day >> mon >> yr;
                    if (validDate(day, mon, yr)) { d.day = day; d.month = mon; d.year = yr; break; }
                    cout << "Ngay khong hop le.\n";
                }
                for (size_t i = 0; i < courts.size(); ++i) {
                    vector< pair< Time, Time > > res = courts[i].getReserved(d);
                    cout << "Court " << courts[i].getID() << ": ";
                    if (res.empty()) cout << "Trong\n";
                    else {
                        for (size_t j = 0; j < res.size(); ++j) {
                            cout << res[j].first.hour << ":" << res[j].first.minute
                                 << "-" << res[j].second.hour << ":" << res[j].second.minute;
                            if (j + 1 < res.size()) cout << ", ";
                        }
                        cout << "\n";
                    }
                }
                cout << "Ban la thanh vien? (1=Yes,0=No): "; int isMem; cin >> isMem;
                int cid = 0;
                if (isMem == 1) {
                    cout << "Nhap Customer ID: "; cin >> cid;
                    bool found = false;
                    for (size_t k = 0; k < customers.size(); ++k) {
                        if (customers[k].getID() == cid) { found = true; break; }
                    }
                    if (!found) break;
                }
                int sid;
                while (true) {
                    cout << "Nhap Court ID de dat: "; cin >> sid;
                    bool valid = false;
                    for (size_t k = 0; k < courts.size(); ++k) {
                        if (courts[k].getID() == sid) { valid = true; break; }
                    }
                    if (valid) break;
                }
                Time ts, te;
                do { cout << "Nhap gio bat dau (h m): "; cin >> ts.hour >> ts.minute; } while (!validTime(ts.hour, ts.minute));
                do { cout << "Nhap gio ket thuc (h m): "; cin >> te.hour >> te.minute; } while (!validTime(te.hour, te.minute) || !(ts < te));
                bool conflict = false;
                for (size_t i = 0; i < courts.size(); ++i) {
                    if (courts[i].getID() == sid) {
                        map< Time, CourtStatus >& sched = courts[i].getDaySchedule(d);
                        Time slot = ts;
                        while (slot < te) {
                            if (sched[slot] == RESERVED) { conflict = true; break; }
                            slot.minute += 30;
                            if (slot.minute >= 60) { slot.minute -= 60; slot.hour++; }
                        }
                        if (!conflict) {
                            slot = ts;
                            while (slot < te) {
                                courts[i].setStatus(d, slot, RESERVED);
                                slot.minute += 30;
                                if (slot.minute >= 60) { slot.minute -= 60; slot.hour++; }
                            }
                        }
                        break;
                    }
                }
                if (conflict) break;
                Reservation r;
                r.rid = nextRes;
                r.cid = cid;
                r.courtId = sid;
                r.date = d;
                r.start = ts;
                r.end = te;
                reservations.push_back(r);
                nextRes++;
                double rate = 0;
                for (size_t i = 0; i < courts.size(); ++i) 
                    if (courts[i].getID() == sid) {
                        rate = (ts.hour >= 18 && ts.hour < 22) ? courts[i].getPeakRate() : courts[i].getOffRate();
                        break;
                    }
                int mins = calcDuration(ts, te);
                double total = rate * (mins / 60.0);
                cout << "Phai tra: " << total << "k\n";
                cout << "Hinh thuc (1=Cash,2=Transfer): "; int pmth; cin >> pmth;
                string method, detail;
                if (pmth == 1) method = "Cash";
                else { method = "Transfer"; detail = "TK MB 0366152973"; }
                Payment pay;
                pay.pid = nextPay;
                pay.rid = r.rid;
                pay.amt = total;
                pay.method = method;
                pay.detail = detail;
                pay.date = d;
                payments.push_back(pay);
                nextPay++;
                break;
            }
            case 5: {
                int day, mon, yr;
                cout << "Nhap ngay (dd mm yyyy): "; cin >> day >> mon >> yr;
                if (!validDate(day, mon, yr)) break;
                Date d = { day, mon, yr };
                for (size_t i = 0; i < reservations.size(); ++i) {
                    Reservation& rr = reservations[i];
                    if (rr.date == d) {
                        cout << rr.rid << " | " << rr.courtId << " | "
                             << rr.start.hour << ":" << rr.start.minute
                             << "-" << rr.end.hour << ":" << rr.end.minute;
                        if (rr.cid == 0) cout << " | Khach vang lai\n";
                        else cout << " | Cust=" << rr.cid << "\n";
                    }
                }
                break;
            }
            case 0:
                break;
            default:
                break;
        }
    } while (choice != 0);
    return 0;
}
