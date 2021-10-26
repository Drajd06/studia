#include <cmath>
#include <iostream>

using namespace std;

class punkt {
    double _x, _y;

   public:
    punkt() : _x(0), _y(0) {}
    punkt(const double& x, const double& y) : _x(x), _y(y) {}

    const double& x() const { return _x; }
    const double& y() const { return _y; }

    double& x() { return _x; }
    double& y() { return _y; }

    const double odleglosc(const punkt& p) {
        return sqrt((p._x - _x) * (p._x - _x) + (p._y - _y) * (p._y - _y));
    }

    friend ostream& operator<<(ostream& out, const punkt& r);
};

ostream& operator<<(ostream& out, const punkt& r) {
    return out << r._x << ' ' << r._y << '\n';
}

class wielobok {
    size_t roz;
    punkt* wsk;

   public:
    wielobok() : roz(0), wsk(0) {}

    wielobok(const punkt* b, const punkt* e)
        : roz(e - b > 0 ? e - b : 0), wsk(roz ? new punkt[roz] : 0) {
        wsk = new punkt[roz];
        for (size_t i = 0; i < roz; i++) {
            wsk[i].x() = b[i].x();
            wsk[i].y() = b[i].y();
        }
    }

    const double obwod() {
        double ob = 0;
        for (size_t i = 0; i < roz; i++) ob += wsk[i].odleglosc(wsk[i + 1]);
        return ob;
    }

    wielobok(const wielobok& r) : roz(r.roz) {
        wsk = new punkt[roz];
        for (size_t i = 0; i < roz; i++) {
            wsk[i].x() = r.wsk[i].x();
            wsk[i].y() = r.wsk[i].y();
        }
    }
    wielobok& operator=(const wielobok& r) {
        if (this != &r) {
            roz = r.roz;
            wsk = new punkt[roz];
            for (size_t i = 0; i < roz; i++) wsk[i] = r.wsk[i];
        }
        return *this;
    }

    punkt& operator[](const size_t i) { return wsk[i]; }

    ~wielobok() {delete[] wsk;}

    const size_t& ilosc() const { return roz; }

    friend ostream& operator<<(ostream& out, const wielobok& r);
};

ostream& operator<<(ostream& out, const wielobok& r) {
    for (size_t i = 0; i < r.roz; i++) {
        out<<r.wsk[i];
    }
    return out;
}

int main() {
    punkt p(2, 3);
    cout << p.x() << ' ' << p.y() << '\n';
    p.x() = 1;
    p.y() = 1;
    cout << p.x() << ' ' << p.y() << '\n';
    cout << p.odleglosc(punkt()) << "\n\n";

    const punkt t[] = {punkt(0, 0), punkt(0, 1), punkt(1, 1), punkt(1, 0)};

    for (size_t i = 0; i < sizeof(t) / sizeof(punkt); ++i)
        cout << i + 1 << ")  " << t[i] << endl;

    cout << "\n*****\n";
    wielobok w1(t, t + 4);
    cout << w1.obwod() << '\n';

    cout << w1[1];
    w1[1] = punkt(0.5, 0.5);
    cout << w1.obwod() << '\n';
    cout << "***\n\n";

    wielobok w2;
    w2 = wielobok(t, t + 3);
    cout << w2.obwod() << '\n';

    for (size_t i = 0; i < w2.ilosc(); ++i)
        cout << w2[i].x() << ' ' << w2[i].y() << '\n';

    cout << "\n*****\n";
    wielobok w3(w2);
    w3[1] = punkt(0, -1);
    w3[2] = punkt(-1, -1);
    for (size_t i = 0; i < w3.ilosc(); ++i) {
        cout << w3[i] << endl;
    }
    cout << "***\n\n";

    cout << "\n*****\n";
    cout << w2 << "***\n" << w3;
    cout << "*****\n\n";

    cout << w2.obwod() - w3.obwod() << "\n\n";

    return 0;
}
