#include <fstream>
#include <iostream>

using namespace std;

class K1 {
    string* p1;

   public:
    K1() : p1(new string[2]) {
        p1[0] = "No nie ma";
        p1[1] = "No nie ma";
    }
    K1(const string& str1, const string& str2) : p1(new string[2]) {
        p1[0] = str1;
        p1[1] = str2;
    }
    K1(const K1& k) : p1(new string[2]) {
        p1[0] = k.p1[0];
        p1[1] = k.p1[1];
    }

    ~K1() { delete[] p1; }

    K1& operator=(const K1& r) {
        if (this != &r) {
            p1[0] = r.p1[0];
            p1[1] = r.p1[1];
        }
        return *this;
    }

    string& operator[](const size_t& i) const { return p1[i]; }
};

class K2 {
    K1 w1;
    double w2;

   public:
    K2() : w1(), w2(0) {}
    K2(const string& str1, const string& str2, const double& w)
        : w1(str1, str2), w2(w) {}
    K2(const K2& k) : w1(k.w1[0], k.w1[1]), w2(k.w2) {}

    K2(const K1& k, const double& w) : w1(k), w2(w) {}

    friend ostream& operator<<(ostream& out, const K2& k);
    const K2 operator-(const double& num) const { return K2(w1, w2 - num); }
    K2 operator+=(const double& num) {
        this->w2 += num;
        return *this;
    }

    friend const K2 operator+(const K2& k);

    const K1& getW1() const { return w1; }
    double& getW2() { return w2; }
    const double& getW2() const { return w2; }
};

ostream& operator<<(ostream& out, const K2& k) {
    return out << k.w1[0] << " " << k.w1[1] << " " << k.w2 << endl;
}

const K2 operator+(const K2& k, const string& str) {
    return K2(k.getW1()[0], k.getW1()[1] + str, k.getW2());
}

const K2 operator+(const string& str, const K2& k) {
    return K2(str + k.getW1()[0], k.getW1()[1], k.getW2());
}

int main(int argc, char** argv) {
    K2 ob1, ob2;
    const K2* wsk1 = new K2("kawa", "z mlekiem", 4.50);
    const K2 ob3(*wsk1);
    delete wsk1;
    wsk1 = 0;

    const K2* wsk2 = new K2(ob3);
    ob2 = *wsk2;
    cout << ob1 << *wsk2;
    delete wsk2;
    wsk2 = 0;

    cout << ob2;
    cout << ob2 - 1.25;

    cout << "*****    3   *****\n\n";

    K2 tab[4];

    if (argc != 2) throw string("Brak parametru");

    ifstream file(argv[1]);
    if (!file) throw string("Blad otwarcia pliku");
    {
        try {
            for (size_t i = 0; i < 4; i++) {
                string tmp;

                file >> tab[i].getW1()[0];
                file >> tab[i].getW1()[1];
                file >> tab[i].getW2();

                getline(file, tmp);
            }
        } catch (...) {
            cout << "Error";
        }
        file.close();
    }

    for (size_t i = 0; i < 4; i++) {
        tab[i] += 1;
        cout << tab[i];
    }
    cout << "*****    4   *****\n\n";

    tab[1] = tab[1] + " with sugar";
    tab[3] = "hot " + tab[3];

    for (size_t i = 0; i < 4; i++) cout << tab[i];

    cout << "*****    5   *****\n\n";
    return 0;
}
