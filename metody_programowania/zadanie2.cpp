#include <iostream>
#ifdef _WIN32
#include <windows.h>
#endif

#include <typeinfo>

using namespace std;

class adres {
    string miasto, ulica;
    int nr;

   public:
    adres() : miasto("brak"), ulica("brak"), nr(0) {}

    adres(const string& a1, const string& a2, int a3)
        : miasto(a1), ulica(a2), nr(a3) {}

    string& getMiasto() { return miasto; }

    ostream& view(ostream& out) const {
        return out << miasto << ", " << ulica << ", " << nr << '\n';
    }

    friend ostream& operator<<(ostream& out, const adres& r);
};

ostream& operator<<(ostream& out, const adres& r) { return r.view(out); }

class osoba {
    string imie;
    int wiek;
    adres* adr;

   public:
    osoba() : imie("brak"), wiek(0), adr(new adres()) {}
    osoba(const string& a1, const int& a2, const adres& a3)
        : imie(a1), wiek(a2), adr(new adres(a3)) {}

    osoba(const osoba& a1)
        : imie(a1.imie), wiek(a1.wiek), adr(new adres(*a1.adr)) {}

    osoba& operator=(const osoba& a1) {
        imie = a1.imie;
        wiek = a1.wiek;
        *adr = *a1.adr;
        return *this;
    }

    ostream& view(ostream& out) const {
        return out << imie << ", " << wiek << ", " << *adr << '\n';
    }

    ~osoba() { delete adr; }

    friend ostream& operator<<(ostream& out, const osoba& r);

    string& miasto() { return adr->getMiasto(); }
};

ostream& operator<<(ostream& out, const osoba& r) { return r.view(out); }

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    adres* wsk = new adres("Czestochowa", "Dabrowskiego", 73);

    cout << "wsk: " << wsk << '\n';
    cout << "*wsk: " << *wsk << '\n';

    adres a1(*wsk);
    delete wsk;
    wsk = nullptr;

    const adres* wsk1 = new adres("Lodz", "Piotrkowska", 33);

    cout << "a1: " << a1 << '\n';
    cout << "*wsk1: " << *wsk1 << '\n';

    adres a2;
    cout << "a2: " << a2 << '\n';
    a2 = a1;
    cout << "a2: " << a2 << '\n';

    osoba os1("Ala", 25, *wsk1);
    delete wsk1;

    cout << "os1: " << os1 << '\n';

    osoba os2(os1);

    os1.miasto() = "Zmieniono miasto osoby 1.";

    cout << "os2: " << os2 << '\n';

    osoba os3;
    cout << "os3: " << os3 << '\n';
    os3 = os2;

    os1.miasto() = "Drugi raz zmieniono miasto osoby 1.";

    cout << "os3: " << os3 << '\n';

    cout << "os1: " << os1;
    return 0;
}
