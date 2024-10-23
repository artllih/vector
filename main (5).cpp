#include <iostream>
#include <vector>
#include <string>
#include <exception>
using namespace std;


class zly_argument : public exception {
    string tekst;
public:
    zly_argument(const string& msg) : tekst(msg) {}
    string what() {
        return tekst;
    }
};

class log_error : public exception {
    string tekst;
public:
    log_error(const string& msg) : tekst(msg) {}
    string what() {
        return tekst;
    }
};

class malo_przedm : public exception {
    string tekst;
public:
    malo_przedm(const string& msg) : tekst(msg) {}
    string what() {
        return tekst;
    }
};

class item_error : public exception {
    string tekst;
public:
    item_error(const string& msg) : tekst(msg) {}
    string what() {
        return tekst;
    }
};


class Przedmiot {
public:
    string nazwa;
    int ilosc;
};

class Plecak {
private:
    vector<Przedmiot> przedmioty;
    vector<string> zakazane = {"papierosy", "nóż"};

public:
    void wsadz(string co, int ile) {
        if (ile < 0) {
            throw zly_argument("Czlowieku, ale ze ty minus chcesz dodac?");
        }
        for (string zakazany : zakazane) {
            if (co == zakazany) {
                throw log_error("Zakazany przedmiot: " + co);
            }
        }
        przedmioty.push_back({co, ile});
    }

    void wyciagnij(string co, int ile) {
        for (auto &Przedmiot : przedmioty) {
            if (Przedmiot.nazwa == co) {
                if (Przedmiot.ilosc >= ile) {
                    Przedmiot.ilosc -= ile;
                } else {
                    throw malo_przedm("Za malo przedmiotow");
                }
                return;
            }
        }
        throw item_error("Przedmiot nie znaleziony");
    }

    void wypisz() {
        cout << "Zawartosc plecaka:" << endl;
        for (Przedmiot p : przedmioty) {
            cout << p.nazwa << " - " << p.ilosc << endl;
        }
    }

    void schowaj(string co, int ile) {
        if (ile < 0) {
            throw zly_argument("No znowu minus dodajesz?");
        }
        przedmioty.push_back({co, ile});
    }

    void przeszukaj() {
        for (auto it = przedmioty.begin(); it != przedmioty.end();) {
            if (it->nazwa == "papierosy" || it->nazwa == "nóż") {
                cout << "Na kuchni czeka rozmowa... " << it->nazwa << endl;
                it = przedmioty.erase(it);
            } else {
                ++it;
            }
        }
    }
};

int main() {
    Plecak plecak;

    try {
        plecak.wsadz("jabłko", -2);
        plecak.wsadz("nóż", 1);  
        plecak.wsadz("woda", 1);
        plecak.wypisz();

        plecak.schowaj("papierosy", 2);  
        plecak.przeszukaj();
        plecak.wypisz();

        plecak.wyciagnij("jabłko", 1);
        plecak.wypisz();
    }
    catch (zly_argument& e) {
        cout << "Blad: " << e.what() << endl;
    }
    catch (log_error& e) {
        cout << "Blad logiczny: " << e.what() << endl;
    }
    catch (malo_przedm& e) {
        cout << "Blad zakresu: " << e.what() << endl;
    }
    catch (item_error& e) {
        cout << "Blad wykonania: " << e.what() << endl;
    }
    catch (exception& e) {
        cout << "Nieznany blad: " << e.what() << endl;
    }

    return 0;
}