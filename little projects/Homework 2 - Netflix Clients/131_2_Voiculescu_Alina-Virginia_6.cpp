#include <iostream>
#include <typeinfo>
#include <windows.h>

using namespace std;

class Abonament
{
protected:
    string nume_abonament;
    float pret;
    int perioada;

public:
    Abonament();
    Abonament(string, float, int);
    Abonament(const Abonament&);
    virtual ~Abonament() {}
    Abonament& operator=(Abonament&);
    virtual void afis();
    virtual float incasare() {return pret * perioada;}
    friend istream& operator>>(istream&, Abonament&);
    friend ostream& operator<<(ostream&, Abonament&);

    virtual void set_reducere(int r) { }
    virtual int get_reducere(){return 0;}

    friend class Abonat;
};

class Abonament_Premium: public Abonament
{
    int reducere;
    static int nrAbonamente_Premium;

public:
    Abonament_Premium();
    Abonament_Premium(string, float, int, int);
    Abonament_Premium(const Abonament_Premium&);
    ~Abonament_Premium() {};
    Abonament_Premium& operator=(Abonament_Premium&);
    void afis();
    float incasare(){return pret * ((100-(float)reducere)/100) * perioada;}
    friend istream& operator>>(istream&, Abonament_Premium&);
    friend ostream& operator<<(ostream&, Abonament_Premium&);


    void set_reducere(int r) {reducere = r;}
    int get_reducere() {return reducere;}
    static void afis_nrAbonamente_Premium()
    {
        if (nrAbonamente_Premium)
            cout<<endl<<"Numarul de clienti cu abonament premium este: "<<nrAbonamente_Premium<<"."<<endl;
        else
            cout<<endl<<"Nu exista clienti cu abonament premium. :( ";
    }
};

int Abonament_Premium::nrAbonamente_Premium = 0;

class Persoana
{
protected:
    int id;
    string nume;
    string cnp;

public:
    Persoana();
    Persoana(int, string);
    Persoana(int, string, string);
    Persoana(const Persoana&);
    virtual ~Persoana() {};
    Persoana& operator=(const Persoana&);
    void afis() {cout<<id<<" "<<nume<<" "<<cnp<<endl;}
    friend istream& operator>>(istream&, Persoana&);
    friend ostream& operator<<(ostream&, Persoana&);
};

class Abonat: public Persoana
{
protected:
    string nr_telefon;
    Abonament *x;

public:
    Abonat();
    Abonat(int, string, string);
    Abonat(int, string, string, string);
    Abonat(const Abonat&);
    ~Abonat() {};
    Abonat& operator=(const Abonat&);
    friend istream& operator>>(istream&, Abonat&);
    friend ostream& operator<<(ostream&, Abonat&);
    friend class Clienti;
};


class Clienti
{
    int nrClienti;
    Abonat listaClienti[100];

public:
    Clienti();
    Clienti(int);
    Clienti(const Clienti&);
    ~Clienti() { }
    Clienti& operator=(Clienti&);
    friend istream& operator>>(istream&, Clienti&);
    friend ostream& operator<<(ostream&, Clienti&);
    void SumaIncasata();
};

void mesaj_scris();

void mesaj_scris1();

void mesaj_scris2();

void meniu();

void meniu1();

void meniu2();

int main()
{
    cout<<"-----------BINE ATI VENIT LA NETFLIX!-----------"<<endl<<endl<<endl;

    meniu();

    return 0;
}

//Constructori de initializare + parametrizati

Abonament::Abonament()
{
    nume_abonament = "Nume abonament necunoscut";
    pret = 0;
    perioada = 0;
}

Abonament::Abonament(string s, float f, int i)
{
    nume_abonament = s;
    pret = f;
    perioada = i;
    try
    {
        if (pret < 0 || perioada < 0)
            throw 2;
    }
    catch(int)
    {
        cout<<endl<<"->!!! Pretul sau perioada nu pot fi negative! !!!<-"<<endl<<endl;
    }
}

Abonament_Premium::Abonament_Premium(): Abonament()
{
    reducere = 0;
    nrAbonamente_Premium++;
}

//Pseudoconstructor pentru tip de baza

Abonament_Premium::Abonament_Premium(string s, float f, int i1, int i2): Abonament(s, f, i1), reducere(i2)
{
    try
    {
        if (reducere < 0)
            throw 3;
    }
    catch(int)
    {
        cout<<endl<<"->!!! Reducerea nu poate fi negativa! !!!<-"<<endl<<endl;
    }
    nrAbonamente_Premium++;
}

Persoana::Persoana()
{
    id = -1;
    nume = "Nume persoana necunoscut";
    cnp = "Cod Numeric Personal necunoscut";
}

Persoana::Persoana(int i, string s)
{
    id = i;
    nume = s;
    cnp = "Cod Numeric Personal necunoscut";
}

Persoana::Persoana(int i, string s1, string s2)
{
    id = i;
    nume = s1;
    cnp = s2;

    try
    {
        if ((cnp).size() != 13)
            throw 13;
    }
    catch(int x)
    {
        cout<<endl<<endl<<"ERROR "<<x;
        cout<<endl<<"->!!! CNP-ul trebuie sa aiba 13 cifre! !!!<-"<<endl<<endl;
    }
}

Abonat::Abonat(): Persoana()
{
    nr_telefon = "Numar de telefon necunoscut";
    x = new Abonament(); /// by default consider un abonament standard
}

Abonat::Abonat(int i, string s1, string s2): Persoana(i, s1)
{
    nr_telefon = s2;

    int tip;
    cout<<"Ce tip de abonament? \n --> 1 - Standard \n --> 2 - Premium"<<endl;
    cout<<"Introduceti tipul de abonament dorit: "<<endl;
    try
    {
        if (!(cin>>tip))
            throw 201;
    }
    catch(int x)
    {
        cout<<endl<<endl<<"ERROR "<<x;
        cout<<endl<<"->!!! Tipul abonamentului nu poate fi format din litere! !!!<-"<<endl;
    }
    if (tip == 1)
        x = new Abonament();
    else
        x = new Abonament_Premium();
}

Abonat::Abonat(int i, string s1, string s2, string s3): Persoana(i, s1, s2)
{
    nr_telefon = s3;

    int tip;
    cout<<"Ce tip de abonament? \n --> 1 - Standard \n --> 2 - Premium"<<endl;
    cout<<"Introduceti tipul de abonament dorit: "<<endl;
    try
    {
        if (!(cin>>tip))
            throw 201;
    }
    catch(int x)
    {
        cout<<endl<<endl<<"ERROR "<<x;
        cout<<endl<<"->!!! Tipul abonamentului nu poate fi format din litere! !!!<-"<<endl;
    }
    if (tip == 1)
        x = new Abonament();
    else
        x = new Abonament_Premium();
}

Clienti::Clienti()
{
    nrClienti = 0;
}

Clienti::Clienti(int nr)
{
    nrClienti = nr;
    try
    {
        if (nr < 0)
            throw 432;
    }
    catch(int x)
    {
        cout<<endl<<endl<<"ERROR "<<x;
        cout<<endl<<"->!!! Numarul de clienti nu poate fi negativ! !!!<-"<<endl<<endl;
    }
    for (int i = 0; i < nrClienti; i++)
    {
        Abonat UNKNOWN;
        listaClienti[i] = UNKNOWN;
    }
}

Abonament::Abonament(const Abonament& A)
{
    nume_abonament = A.nume_abonament;
    pret = A.pret;
    perioada = A.perioada;
}

Abonament_Premium::Abonament_Premium(const Abonament_Premium& A): Abonament(A)
{
    reducere = A.reducere;
    nrAbonamente_Premium++;
}

Persoana::Persoana(const Persoana& P)
{
    id = P.id;
    nume = P.nume;
    cnp = P.cnp;
}

Abonat::Abonat(const Abonat& A): Persoana(A)
{
    nr_telefon = A.nr_telefon;
    if (typeid(*(A.x)) == typeid(Abonament))
    {
        x = new Abonament();
        x->nume_abonament = (A.x)->nume_abonament;
        x->pret = (A.x)->pret;
        x->perioada = (A.x)->perioada;
    }
    else
    {
        x = new Abonament_Premium();
        x->nume_abonament = (A.x)->nume_abonament;
        x->pret = (A.x)->pret;
        x->perioada = (A.x)->perioada;
        x->set_reducere( (A.x)->get_reducere() );
    }
}

Clienti::Clienti(const Clienti& C)
{
    nrClienti = C.nrClienti;
    for (int i = 0; i < nrClienti; i++)
    {
        listaClienti[i] = C.listaClienti[i];
    }
}

Abonament& Abonament::operator=(Abonament& A)
{
    if(this != &A)
    {
        nume_abonament = A.nume_abonament;
        pret = A.pret;
        perioada = A.perioada;
    }

    return *this;
}

Abonament_Premium& Abonament_Premium::operator=(Abonament_Premium& A)
{
    if(this != &A)
    {
        Abonament::operator=(A);
        reducere = A.reducere;
    }

    return *this;
}

Persoana& Persoana::operator=(const Persoana& P)
{
    if (this != &P)
    {
        id = P.id;
        nume = P.nume;
        cnp = P.cnp;
    }

    return *this;
}

Abonat& Abonat::operator=(const Abonat& A)
{
    if (this != &A)
    {
        Persoana::operator=(A);
        nr_telefon = A.nr_telefon;
        if (typeid(*(A.x)) == typeid(Abonament))
        {
            x = new Abonament();
            x->nume_abonament = (A.x)->nume_abonament;
            x->pret = (A.x)->pret;
            x->perioada = (A.x)->perioada;
        }
        else
        {
            x = new Abonament_Premium();
            x->nume_abonament = (A.x)->nume_abonament;
            x->pret = (A.x)->pret;
            x->perioada = (A.x)->perioada;
            x->set_reducere( (A.x)->get_reducere() );
        }
    }
}

Clienti& Clienti::operator=(Clienti& C)
{
    if (this != &C)
    {
        nrClienti = C.nrClienti;
        for (int i = 0; i < nrClienti; i++)
        {
            listaClienti[i] = C.listaClienti[i];
        }
    }

    return *this;
}

istream& operator>>(istream& in, Abonament& A)
{
    cout<<"Nume abonament: ";
    in>>A.nume_abonament;
    cout<<"Pret lunar: ";

    try
    {
        if (!(in>>A.pret))
            throw 575;

        cout<<"Perioada (numarul de luni): ";

        if (!(in>>A.perioada))
            throw 576;
    }
    catch(int x)
    {
        cout<<endl<<endl<<"ERROR "<<x;
        if (x == 575)
            cout<<endl<<"->!!! Pretul nu poate fi format din litere! !!!<-"<<endl;
        else
            cout<<endl<<"->!!! Perioada nu poate fi formata din litere! !!!<-"<<endl;
    }

    return in;
}

istream& operator>>(istream& in, Abonament_Premium& A)
{
    in>>(Abonament&) A;
    cout<<"Reducere(%): ";

    try
    {
        if (!(in>>A.reducere))
            throw 578;
    }
    catch(int x)
    {
        cout<<endl<<endl<<"ERROR "<<x;
        cout<<endl<<"->!!! Reducerea nu poate fi formata din litere! !!!<-"<<endl;
    }

    return in;
}

istream& operator>>(istream& in, Persoana& P)
{
    cout<<"ID: ";

    try
    {
        if (!(in>>P.id))
            throw 572;
        cout<<"Nume: ";
        in>>P.nume;
        cout<<"CNP: ";
        in>>P.cnp;
        if ((P.cnp).size() != 13)
            throw 13;
    }
    catch(int x)
    {
        cout<<endl<<endl<<"ERROR "<<x;
        if (x == 572)
            cout<<endl<<"->!!! ID-ul nu poate fi format din litere! !!!<-"<<endl;
        else
            cout<<endl<<"->!!! CNP-ul trebuie sa aiba 13 cifre! !!!<-"<<endl<<endl;
    }

    return in;
}

istream& operator>>(istream& in, Abonat& A)
{
    in>>(Persoana&) A;
    cout<<"Numar de telefon: ";
    in>>A.nr_telefon;

    int tip;
    cout<<"Ce tip de abonament? \n --> 1 - Standard \n --> 2 - Premium"<<endl;
    cout<<"Introduceti tipul de abonament dorit: "<<endl;

    try
    {
        if (!(cin>>tip))
            throw 201;
    }
    catch(int x)
    {
        cout<<endl<<endl<<"ERROR "<<x;
        cout<<endl<<"->!!! Tipul abonamentului nu poate fi format din litere! !!!<-"<<endl;
    }

    if (tip == 1)
    {
         A.x = new Abonament();
         in>>(Abonament&) (*A.x);
    }
    else
    {
        A.x = new Abonament_Premium();
        in>>(Abonament_Premium&) (*A.x);
    }

    return in;
}

istream& operator>>(istream& in, Clienti& C)
{
    int tip_abonat;

    cout<<"Numar de clienti: ";
    try
    {
        if (!(in>>C.nrClienti) || C.nrClienti < 0)
            throw 212;
    }
    catch(int x)
    {
        cout<<endl<<endl<<"ERROR "<<x;
        cout<<endl<<"->!!! Numarul de clienti nu poate fi negativ si nu poate fi format din litere! !!!<-"<<endl<<endl;
    }
    for(int i = 0; i < C.nrClienti; i++)
    {
        cout<<endl<<endl<<endl<<"---CLIENT "<<i+1<<":"<<endl;
        in>>C.listaClienti[i];
    }

    return in;
}

ostream& operator<<(ostream& out, Abonament& A)
{
    out<<endl;
    out<<"Nume abonament: "<<A.nume_abonament<<endl;
    out<<"Pret: "<<A.pret<<endl;
    out<<"Perioada: "<<A.perioada;

    if (A.perioada == 1)
        out<<" luna"<<endl;
    else
        out<<" luni"<<endl;

    return out;
}

ostream& operator<<(ostream& out, Abonament_Premium& A)
{
    out<<(Abonament&) A;
    out<<"Reducere: "<<A.reducere<<"%"<<endl;

    return out;
}

ostream& operator<<(ostream& out, Persoana& P)
{
    out<<endl;
    out<<"ID: "<<P.id<<endl;
    out<<"Nume: "<<P.nume<<endl;
    out<<"CNP: "<<P.cnp<<endl;

    return out;
}

ostream& operator<<(ostream& out, Abonat& A)
{
    out<<(Persoana&) A;
    out<<"Numar de telefon: "<<A.nr_telefon;
    if (typeid(*(A.x)) == typeid(Abonament))
        out<<(Abonament&) (*(A.x));
    else
        out<<(Abonament_Premium&)(*(A.x));

    return out;
}

ostream& operator<<(ostream& out, Clienti& C)
{

    out<<"Numar de clienti: "<<C.nrClienti<<endl<<endl;
    if (C.nrClienti)
    {
        out<<"Clientii sunt:"<<endl<<endl;
        for(int i = 0; i < C.nrClienti; i++)
        {
            out<<"---CLIENT "<< i + 1 <<":";
            out<<C.listaClienti[i]<<endl<<endl;
        }

    }
    else
        out<<"Nu sunt clienti de afisat."<<endl<<endl;

    return out;
}

void Clienti::SumaIncasata()
{
    float Suma = 0;
    for(int i = 0; i < nrClienti ;i++)
    {
        float incasare = (listaClienti[i].x)->incasare();
        Suma += incasare;
    }

    cout<<endl<<"Suma incasata de la toti abonatii Netflix este: "<<Suma<<".";
}

void Abonament::afis()
{
    cout<<endl;
    cout<<"Nume abonament: "<<nume_abonament<<endl;
    cout<<"Pret: "<<pret<<endl;
    cout<<"Perioada: "<<perioada;

    if (perioada == 1)
        cout<<" luna"<<endl;
    else
        cout<<" luni"<<endl;
}

void Abonament_Premium::afis()
{
    Abonament::afis();
    cout<<"Reducere: "<<reducere<<"%"<<endl;
}

void mesaj_scris()
{
    cout<<"Alegeti numarul corespunzator variantei dorite:"<<endl;
    cout<<"     1. Meniu - Clienti Netflix."<<endl;
    cout<<"     2. Meniu - A little game. (upcasting, downcasting)"<<endl;
    cout<<"     0. Iesire."<<endl<<endl;
}

void mesaj_scris1()
{
    cout<<"Alegeti numarul corespunzator variantei dorite:"<<endl;
    cout<<"     1. Crearea unei noi liste de clienti Netflix."<<endl;
    cout<<"     2. Afisarea clientilor Netflix."<<endl;
    cout<<"     3. Afisarea numarului de clienti cu abonament premium Netflix."<<endl;
    cout<<"     4. Afisarea sumei incasate de la toti abonatii Netflix."<<endl;
    cout<<"     0. Iesire."<<endl<<endl;
}

void mesaj_scris2()
{
    cout<<"Alegeti numarul corespunzator variantei dorite:"<<endl;
    cout<<endl<<"                    ---------------UPCASTING---------------"<<endl<<endl;
    cout<<"     1. Conversia unui Abonament Premium intr-un Abonament Standard."<<endl;
    cout<<"     2. Conversia unui abonat Netflix intr-o simpla persoana."<<endl;
    cout<<"        (care nu are abonament Netflix :( )"<<endl;
    cout<<endl<<"                    ---------------DOWNCASTING---------------"<<endl;
    cout<<endl<<"                                        +"<<endl;
    cout<<endl<<"                    -----CITIREA SI AFISAREA A N OBIECTE-----"<<endl<<endl;
    cout<<"     3. Citirea a N abonamente de tip Standard sau Premium."<<endl;
    cout<<"     0. Iesire."<<endl<<endl;
}

void meniu()
{
    mesaj_scris();
    int opt;
    cin>>opt;

    while (opt)
    {
        if (opt == 1)
            meniu1();
        else
            meniu2();

        cout<<endl<<endl<<endl<<"Doriti o alta optiune?"<<endl<<endl<<endl;
        mesaj_scris();
        cin>>opt;
    }
}

void meniu1()
{
    mesaj_scris1();
    int optiune;
    cin>>optiune;

    Clienti C;

    while (optiune)
    {
        switch(optiune)
        {
            case 1:
            {
                cin>>C;
                break;
            }
            case 2:
            {
                cout<<C;
                break;
            }
            case 3:
            {
                Abonament_Premium::afis_nrAbonamente_Premium();
                break;
            }
            case 4:
            {
                C.SumaIncasata();
                break;
            }
        }

        cout<<endl<<endl<<endl<<endl<<"Doriti o alta optiune?"<<endl<<endl<<endl;
        mesaj_scris1();
        cin>>optiune;
    }
}

void meniu2()
{
    mesaj_scris2();
    int opti;
    cin>>opti;

    while(opti)
    {
        switch(opti)
        {
            case 1:
            {
                string _Ab, _AbPrem, _AbType;
                Abonament *Ab;
                Abonament_Premium AbPrem;
                cin>>AbPrem;
                cout<<endl<<endl<<"-->Abonamentul este: "<<endl<<AbPrem;

                _AbPrem = typeid(AbPrem).name();
                _AbType = typeid(Abonament).name();

                if (_AbPrem.substr(2) == _AbType.substr(1))
                    cout<<endl<<"In acest moment, tipul abonamentului este STANDARD."<<endl;
                else
                    cout<<endl<<"In acest moment, tipul abonamentului este PREMIUM."<<endl;

                cout<<endl<<endl<<endl<<"...Facem conversia..."<<endl<<endl<<endl;
                Sleep(4000);

                Ab = &AbPrem;
                cout<<endl<<endl<<"-->Abonamentul este: "<<endl<<*Ab;

                _Ab = typeid(Ab).name();

                if (_Ab.substr(2) == _AbType.substr(1))
                    cout<<endl<<"In acest moment, tipul abonamentului este STANDARD."<<endl;
                else
                    cout<<endl<<"In acest moment, tipul abonamentului este PREMIUM."<<endl;

                break;
            }

            case 2:
            {
                string _Pers, _Abonat, _PersType;
                Persoana *P;
                Abonat A;
                cin>>A;
                cout<<endl<<endl<<"-->Datele abonatului sunt: "<<endl<<A;

                _Abonat = typeid(A).name();
                _PersType = typeid(Persoana).name();

                if (_Abonat.substr(2) == _PersType.substr(1))
                    cout<<endl<<"In acest moment, aceasta este o simpla persoana."<<endl;
                else
                    cout<<endl<<"In acest moment, acesta este un abonat Netflix."<<endl;

                cout<<endl<<endl<<endl<<"...Facem conversia..."<<endl<<endl<<endl;
                Sleep(4000);

                P = &A;
                cout<<endl<<endl<<"-->Datele persoanei (fostului abonat) sunt: "<<endl<<*P;

                _Abonat = typeid(P).name();

                if (_Abonat.substr(2) == _PersType.substr(1))
                    cout<<endl<<"In acest moment, aceasta este o simpla persoana."<<endl;
                else
                    cout<<endl<<"In acest moment, acesta este un abonat Netflix."<<endl;

                break;
            }

            case 3:
            {
                Abonament **a;
                int n, optiune1;

                try
                {
                    cout<<"Introduceti numarul de abonamente pe care doriti sa il introduceti: ";
                    cin>>n;
                    if (n <= 0)
                    throw 324;
                }
                catch(int x)
                {
                    cout<<endl<<endl<<"ERROR "<<x;
                    cout<<endl<<"->!!! Dimensiunea vectorului nu poate fi nula sau negativa! !!!<-"<<endl;
                }

                a = new Abonament* [n];

                for (int i = 0; i < n; i++)
                {
                    cout<<endl<<endl<<"Alegeti numarul corespunzator variantei dorite:"<<endl;
                    cout<<"     1. Abonament. "<<endl;
                    cout<<"     2. Abonament Premium."<<endl<<endl;

                    cin>>optiune1;
                    if (optiune1 == 1)
                    {
                        a[i] = new Abonament();
                        cin>>*a[i];
                    }
                    else
                    {
                        a[i] = new Abonament_Premium(); //upcasting
                        cin>>*dynamic_cast<Abonament_Premium*>(a[i]);
                    }
                }

                cout<<endl<<endl<<endl<<"Abonamentele sunt:"<<endl<<endl;

                for (int i = 0; i < n; i++)
                    a[i] -> afis();

                break;
            }
        }

        cout<<endl<<endl<<endl<<"Doriti o alta optiune?"<<endl<<endl<<endl;
        mesaj_scris2();
        cin>>opti;
    }
}
