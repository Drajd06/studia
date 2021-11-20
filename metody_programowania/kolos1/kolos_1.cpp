#include <fstream>
#include <iostream>

using namespace std;

class K1 {
    string *p1;

   public:
    K1() : p1(new string("No nic no")) {}
    K1(const string &s) : p1(new string(s)) {}
    K1(const K1 &k1) : p1(new string(*k1.p1)) {}

    string &_p1() { return *p1; }
    string &_p1() const { return *p1; }

    ~K1() {
        delete p1;
        // cout << "\n\n!!!~K1()!!!\n\n";
    }

    K1 &operator=(const K1 &r) {
        if (this != &r) *p1 = *r.p1;
        return *this;
    }
};

class K2 {
    K1 txt[2];
    int w1;

   public:
    K2() : txt(), w1(0) {}
    K2(const string &s1, const string &s2, const int &_w1) : txt{}, w1(_w1) {
        txt[0]._p1() = s1;
        txt[1]._p1() = s2;
    }

    friend ostream &operator<<(ostream &out, const K2 &k);

    const K2 operator+(const int &num) {
        return K2(txt[0]._p1(), txt[1]._p1(), w1 + num);
    }

    K2 operator+=(const int &num) {
        this->w1 += num;
        return *this;
    }

    K1 *getTxt() { return txt; }
    int &getW1() { return w1; }

    friend const K2 operator+(const K2 &k, const string &str);
    friend const K2 operator+(const string &str, const K2 &k);
};

ostream &operator<<(ostream &out, const K2 &k) {
    return out << k.txt[0]._p1() << ", " << k.txt[1]._p1() << ", " << k.w1
               << endl;
}

const K2 operator+(const K2 &k, const string &str) {
    return K2(k.txt[0]._p1(), k.txt[1]._p1() + str, k.w1);
}
const K2 operator+(const string &str, const K2 &k) {
    return K2(k.txt[0]._p1(), str + k.txt[1]._p1(), k.w1);
}

int main(int argc, char **argv) {
    K2 ob1, ob2;

    const K2 *wsk1 = new K2("Ala", "Koala", 15);
    const K2 ob3(*wsk1);
    delete wsk1;
    wsk1 = 0;

    const K2 *wsk2 = new K2(ob3);
    ob2 = *wsk2;
    cout << ob1 << *wsk2;
    delete wsk2;
    wsk2 = 0;

    cout << ob2;
    cout << ob2 + 10;

    cout << "*****    3   *****\n\n";

    K2 tab[4];

    if (argc != 2) throw string("Brak parametru");

    ifstream file(argv[1]);
    if (!file) throw string("Blad otwarcia pliku");
    {
        try {
            for (size_t i = 0; i < 4; i++) {
                string tmp;
                file >> tab[i].getTxt()[0]._p1();
                file >> tab[i].getTxt()[1]._p1();
                file >> tab[i].getW1();
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

    tab[1] = tab[1] + " Kowalska";
    tab[3] = "Bocian " + tab[3];

    for (size_t i = 0; i < 4; i++) cout << tab[i];

    cout << "*****    5   *****\n\n";
    return 0;
}
