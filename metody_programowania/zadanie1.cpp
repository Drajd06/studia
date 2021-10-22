#include <iostream>
#include <cmath>

using namespace std;

class punkt {
    double _x, _y, _z;

    public:
        punkt(): _x(0), _y(0), _z(0) {}
        punkt(const double &a1, const double &a2, const double &a3) : _x(a1), _y(a2), _z(a3) {}

        const double& x() const { return _x; }
        const double& y() const { return _y; }
        const double& z() const { return _z; }

        double& x() {return _x;}
        double& y() {return _y;}
        double& z() {return _z;}
};

class prostokat : public punkt {
    double _a, _b;

    public:
        prostokat(): punkt(0, 0, 0), _a(0), _b(0){}
        prostokat(const double &a1, const double &a2, const double &a3, const double &a4, const double &a5): punkt(a1, a2, a3), _a(a4), _b(a5){}
        prostokat(const punkt &a1, const double &a2, const double &a3): punkt(a1), _a(a2), _b(a3){}

        const double& a() const {return _a;}
        const double& b() const {return _b;}

        double& a() {return _a;}
        double& b() {return _b;}

        double pole() const{return _a*_b;}
};

class graniastoslup : public prostokat {
    double _h;

    public:
        graniastoslup(): prostokat(punkt(0, 0, 0), 0, 0), _h(0){}
        graniastoslup(const double &a1, const double &a2, const double &a3, const double &a4, const double &a5, const double &a6): prostokat(punkt(a1, a2, a3), a4, a5), _h(a6){}
        graniastoslup(const punkt &a1, const double &a4, const double &a5, const double &a6): prostokat(a1, a4, a5), _h(a6){}
        graniastoslup(const prostokat &a1, const double &a6): prostokat(a1), _h(a6){}

        const double& h() const {return _h;}

        double& h() {return _h;}

        double objetosc() const {return pole() * h();}
};



int main() {
    punkt p1, p2(1, 2, 3);
    const punkt p3(1.1, 2.2, 3.3);

    cout << p1.x() << endl;
    cout << p2.x() << endl;


    cout << p3.x() << endl;

    cout << p3.x() << '\t' << p3.y() << '\t' << p3.z() << endl;

    //zwraca referencje, a potem zmienia jej zawartosc
    p1.x() = 1;
    p1.y() = 10;
    p1.z() = 100;

    cout << p1.x() << '\t' << p1.y() << '\t' << p1.z() << endl;

    prostokat pr1, pr2(1, 2, 3, 10.5, 20.5);

    const prostokat pr3(p2, 5, 5);

    pr1.x() = 2;
    pr1.y() = 20;
    pr1.x() = 200;
    pr1.a() = 10;
    pr1.b() = 10;
    cout << pr1.x() << '\t' << pr1.y() << '\t' << pr1.z() << '\t'
         << pr1.a() << '\t' << pr1.b() << '\t' << endl;
    cout << pr1.pole() << endl;

    cout << pr3.x() << '\t' << pr3.y() << '\t' << pr3.z() << '\t'
         << pr3.a() << '\t' << pr3.b() << '\t' << endl;

    cout << pr3.pole() << endl;

    graniastoslup g1, g2(1, 2, 3, 10.5, 20.5, 30.5), g3(p2, 100, 200, 300);
    const graniastoslup g4(pr3, 5);

    cout << g4.x() << '\t' << g4.y() << '\t' << g4.z() << '\n'
         << g4.a() << '\t' << g4.b() << '\t' << g4.h() << '\n'
         << g4.objetosc() << endl;

    g1.a() = 10;
    g1.b() = 10;
    g1.h() = 10;

    cout << g1.x() << '\t' << g1.y() << '\t' << g1.z() << '\n'
         << g1.a() << '\t' << g1.b() << '\t' << g1.h() << '\n'
         << g1.objetosc() << endl;
}
