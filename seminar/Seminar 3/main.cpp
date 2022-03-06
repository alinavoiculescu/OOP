#include <iostream>
#include <vector>

using namespace std;

class Candidat {
    string nume, prenume, frecventa, specializare, id;
    float medie_bac;
    static unsigned nr_ord;

    public:

        Candidat (string n = "", string p = "", float m = 0.0, string f = "ZI", string spec = "informatica");
        friend ostream& operator << (ostream&, const Candidat&);
        friend istream& operator >> (istream&, Candidat&);

        bool operator == (const string&) const;
        bool operator >= (const float&) const;

        string getSpecializare () const;
        string getId () const;
}; 
unsigned Candidat::nr_ord = 0;

Candidat::Candidat(string n, string p , float m, string f, string spec) : nume(n), prenume(p), frecventa(f), specializare(spec), medie_bac(m)
{
    string base = "FMI2021-";
    nr_ord++;
    this->id = base + to_string(nr_ord);
}

ostream& operator<<(ostream& out, const Candidat& c) {
    out << "Nume: " << c.nume << endl;
    out << "Prenume: " << c.prenume << endl;
    out << "Medie: " << c.medie_bac << endl;
    out << "Specializare: " << c.specializare << endl;
    out << "Frecventa: " << c.frecventa << endl;
    out << "ID: " << c.id << endl;

    return out;
}

istream& operator>> (istream& in, Candidat& c) {
    cout << "Introduceti un nou candidat" << endl;
    cout << "(nume, prenume, medie BAC, specializare, frecventa)";

    in >> c.nume >> c.prenume >> c.medie_bac >> c.specializare >> c.frecventa;

    return in;
}


bool Candidat::operator== (const string& f) const {
    if (this->frecventa == f) {
        return true;
    }
    return false;
    // return this->frecventa == f;
}

bool Candidat::operator>= (const float& f) const {
    return this->medie_bac >= f;
}

string Candidat::getSpecializare () const {
    return this->specializare;
}

string Candidat::getId () const {
    return this->id;
}

int main () {
    vector<Candidat> candidati;
    int run = 1;
    
    while (run == 1) {
        int option;

        cout << "Dati optiunea: ";
        cin >> option;

        switch (option)
        {
            case 1: {
                Candidat c;
                cin >> c;
                candidati.push_back(c);
                break;
            }

            case 2: {
                for (int i = 0; i < candidati.size(); i++) {
                    if (candidati[i] == "ZI") {
                        cout << candidati[i] << endl << "--------------" << endl;
                    }
                }
                break;
            }

            case 3: {
                for (int i = 0; i < candidati.size(); i++) {
                    if (candidati[i] >= 9) {
                        cout << candidati[i] << endl << "--------------" << endl;
                    }
                }
                break;
            }

            case 4: {
                unsigned info = 0, mate = 0;
                for (int i = 0; i < candidati.size(); i++) {
                    if (candidati[i].getSpecializare() == "informatica") {
                        info++;
                    } else {
                        mate++;
                    }
                }
                cout << "Studenti inscrisi informatica: " << info << endl;
                cout << "Studenti inscrisi matematica: " << mate << endl;
            }
            case 5: {
                string id_to_remove;
                bool ok = false;

                cout << "Dati id-ul studentului care trebuie eliminat";
                cin >> id_to_remove;

                for (auto it = candidati.begin(); it != candidati.end(); it++){
                    if ((*it).getId() == id_to_remove) {
                        candidati.erase(it);
                        ok = true;
                        break;
                    }
                }

                if (!ok) {
                    cout << "Studentul nu exista" << endl;
                }

                break;
            }
        }
        
        cout << "Continua? 1/0";
        cin >> run;
        cout << "===========" << endl;
    }

    return 0;
}