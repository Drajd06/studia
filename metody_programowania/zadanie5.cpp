#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

class Uint {
    unsigned v;

   public:
    Uint() : v(0) {}
    Uint(const unsigned& a) : v(a) {}
    operator unsigned() const { return v; }
    friend ostream& operator<<(ostream& out, const Uint& r) {
        return out << r.v;
    }
    friend istream& operator>>(istream& in, Uint& r) { return in >> r.v; }
};

struct blad {
    string txt;
    unsigned lp;
    blad() : lp(0) {}
    blad(const string& a, unsigned b) : txt(a), lp(b) {}
};
ostream& operator<<(ostream& out, const blad& p) {
    return out << p.txt << ' ' << p.lp << endl;
}

using naturalne = Uint;

class polygon;

class point {
    double x, y;

   public:
    point() : x(0), y(0) {}

    double distance(const point&) const;

    friend class polygon;
    friend ostream& operator<<(ostream&, const point&);
};
ostream& operator<<(ostream& out, const point& p) {
    return out << p.x << " " << p.y << endl;
};

double point::distance(const point& a) const {
    return sqrt((a.x - x) * (a.x - x) + (a.y - y) * (a.y - y));
}

class polygon {
    unsigned n;
    point* points;
    naturalne* order;

   public:
    polygon() : n(0), points(nullptr), order(nullptr) {}
    ~polygon() {
        delete[] points;
        delete[] order;
        cout << "\n\n!!!~polygon()!!!\n\n";
    }

    void read(ifstream&);
    double obwod() const;
    double pole() const;
};

double polygon::obwod() const {
    double obw = 0;
    if (!order) throw string("Brak tablicy order.");
    if (!points) throw string("Brak tablicy points.");

    for (int i = 0, j = 0; (unsigned)i < n; i++) {
        j = order[i] - 1;
        if (j < 0)
            throw string("Niedozwolona wartość 0 w tablicy order.");
        else if (j > n)
            throw string("Wartosc wieksza od " + n +
                         string(" w tablicy order."));
        obw += points[j].distance(points[order[(i + 1) % n] - 1]);
        //0+1%4-1 = 1
        //          2
        //          3
        //          0
    }
    return obw;
}

double polygon::pole() const {
    double pol = 0;
    for (int i = 0, j = 0; (unsigned)i < n; i++) {
        j = order[i] - 1;
        if (j < 0)
            throw string("Niedozwolona wartość 0 w tablicy order.");
        else if (j > n)
            throw string("Wartosc wieksza od " + n +
                         string(" w tablicy order."));

        pol += points[j].x * points[order[(i + 1) % n] - 1].y -
               points[order[(i + 1) % n] - 1].x * points[j].y;
    }
    return pol / 2;
}

void polygon::read(ifstream& file) {
    string tmp;

    getline(file, tmp);
    if (tmp != "[POLYGON]") throw string("Brak nagłówka \"[POLYGON]\"");

    getline(file, tmp);
    if (tmp != "[NUMBER OF NODES]")
        throw string("Brak nagłówka \"[NUMBER OF NODES]\"");

    file >> n;
    getline(file, tmp);
    if (!file || tmp[0] != '\0')
        throw string("Nieprawidłowy format parmetru \"n\"");
    if (n < 3) throw string("Liczba punktów mniejsza od 3");

    getline(file, tmp);
    if (tmp != "[NODES]") throw string("Brak nagłówka \"[NODES]\"");

    points = new point[n];
    for (size_t i = 0; i < n; i++) {
        double* tmpValues = new double[3];
        for (size_t j = 0; j < 3; j++) {
            file >> tmpValues[j];
        }

        getline(file, tmp);
        if (!file || tmp[0] != '\0') {
            // blad b("Nieprawidlowa ilosc znakow tablicy [NODES] w linii: ", i + 1);
            // cout << b;
            // throw;
            throw string("Nieprawidlowa ilosc znakow tablicy [NODES] w linii: " + to_string(i+1) + "\n");
        }
        points[(int)tmpValues[0] - 1].x = tmpValues[1];
        points[(int)tmpValues[0] - 1].y = tmpValues[2];
    }

    getline(file, tmp);
    if (tmp != "[POLYGON]") throw string("Brak nagłówka \"[POLYGON]\"");

    order = new naturalne[n];
    for (size_t i = 0; i < n; i++) {
        file >> order[i];
    }
};

int main(int argc, char** argv) try {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    if (argc != 2) throw 0;
    if (strlen(argv[1]) < 5) throw 1;  // a.txt

    // if (string(argv[1]).substr(strlen(argv[1]) - 4, strlen(argv[1])) !=
    // ".txt") throw 2;
    if (string(argv[1] + strlen(argv[1]) - 4) != ".txt") throw 2;

    ifstream file(argv[1]);
    if (!file) throw 3;
    {
        try {
            polygon poly;
            poly.read(file);
            cout << "obwod: " << poly.obwod() << endl;
            cout << "pole  : " << poly.pole() << endl;

        } catch (const string& e) {
            cout << e << endl;
        } catch (const blad& e) {
            cout << e;
        }

        file.close();
    };

#ifdef _WIN32
    system("PAUSE");
#endif
    return 0;
}

catch (int err) {
    switch (err) {
        case 0:
            cout << err << ": Zła liczba parametrów programu.\n";
            break;
        case 1:
            cout << err << ": Zła nazwa pliku z danymi.\n";
            break;
        case 2:
            cout << err
                 << ": Złe rozszerzenie pliku z danymi - musi być *.txt .\n";
            break;
        case 3:
            cout << err << ": Brak pliku o nazwie " << argv[1] << " .\n";
    }
} catch (...) {
    cout << "Nieznana sytuacja wyjątkowa.\n";
}
