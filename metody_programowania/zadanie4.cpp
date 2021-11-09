#include <cmath>
#include <iostream>

using namespace std;

class point {
    double tab[3];

   public:
    point() : tab{0, 0, 0} {}
    point(const double (&t)[3]) : tab{t[0], t[1], t[2]} {}
    point(const double& a1, const double& a2, const double& a3)
        : tab{a1, a2, a3} {}

    friend ostream& operator<<(ostream& out, const point& p);

    const double& operator[](const int i) const { return tab[i]; };

    const double distance(const point& p) const {
        return sqrt((p.tab[0] - tab[0]) * (p.tab[0] - tab[0]) +
                    (p.tab[1] - tab[1]) * (p.tab[1] - tab[1]) +
                    (p.tab[2] - tab[2]) * (p.tab[2] - tab[2]));
    }

    const point operator+(const point& p) {
        return point(tab[0] + p.tab[0], tab[1] + p.tab[1], tab[2] + p.tab[2]);
    };

    const point operator-(const point& p) {
        return point(tab[0] - p.tab[0], tab[1] - p.tab[1], tab[2] - p.tab[2]);
    };

    friend const point operator*(const double a, const point& p);
    friend const point operator*(const point& p, const double a);

    bool operator<(const point& p) const{
      return distance(point()) < p.distance(point());
    };

    bool operator==(const point& p) const{
        return fabs(distance(point()) - p.distance(point())) < 1e-10;
    };

    friend istream& operator>>(istream& cin, point& p);
};

ostream& operator<<(ostream& out, const point& p) {
    return out << p.tab[0] << ' ' << p.tab[1] << ' ' << p.tab[2];
}
<
const point operator*(const double a, const point& p) {
    return point(a * p.tab[0], a * p.tab[1], a * p.tab[2]);
};

const point operator*(const point& p, const double a) {
    return point(a * p.tab[0], a * p.tab[1], a * p.tab[2]);
};

istream& operator>>(istream& in, point& p) {
    cout << "Podaj x\n";
    in >> p.tab[0];

    cout << "Podaj y\n";
    in >> p.tab[1];

    cout << "Podaj z\n";
    in >> p.tab[2];
    return in;
}

int main() {
    double x[2][3] = {{1.0, 1.0, 1.0}, {1.0, 2.0, 3.0}};

    point p1(x[0]), p2(x[1]);

    const point p3(0.4, 0.2, 0.1);

    cout << p1 << ", " << p2 << '\n';

    cout << p3[0] << ' ' << p3[1] << ' ' << p3[2] << '\n';

    cout << p1.distance(point()) << endl;
    cout << p3.distance(p1) << endl;

    cout << p1 + p2 << endl;
    cout << p1 - p3 << endl;

    cout << 3.14 * p2 << endl;
    cout << p2 * 3.14 << endl;

    cout << (p1 < p3) << endl;
    cout << (p1 == point(1.0, 1.0, 1.0)) << endl;

    cin >> p1;
    cout << p1 << '\n';
    return 0;
}
