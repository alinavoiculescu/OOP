#include <iostream>
#include <typeinfo>
#include <windows.h>
#include <vector>
#include <map>

using namespace std;

template <class T>
class Abonament
{
protected:
    T nume_abonament;
    float pret;
    int perioada;

public:
    Abonament();
    Abonament(T, float, int);
    Abonament(const Abonament<T>&);
    virtual ~Abonament() {}
    Abonament& operator=(Abonament<T>&);
    virtual void afis();
    virtual float incasare() {return pret * perioada;}
    template <class T1>
    friend istream& operator>>(istream&, Abonament<T1>&);
    template <class T1>
    friend ostream& operator<<(ostream&, Abonament<T1>&);
    virtual void set_reducere(int r) { }
    virtual int get_reducere() const {return 0;}
    template <class T2, class U2>
    friend class Abonat;
};

template <class T>
class Abonament_Premium: public Abonament<T>
{
    int reducere;
    static int nrAbonamente_Premium;

public:
    Abonament_Premium();
    Abonament_Premium(T, float, int, int);
    Abonament_Premium(const Abonament_Premium<T>&);
    ~Abonament_Premium() { /*nrAbonamente_Premium--;*/ };
    Abonament_Premium& operator=(Abonament_Premium<T>&);
    void afis();
    float incasare(){return Abonament<T>::pret * ((100-(float)reducere)/100) * Abonament<T>::perioada;}
    template <class T1>
    friend istream& operator>>(istream&, Abonament_Premium<T1>&);
    template <class T1>
    friend ostream& operator<<(ostream&, Abonament_Premium<T1>&);
    //static int get_nrAbonamente(){return nrAbonamente_Premium;};
    //static void set_nrAbonamente(int nrAb){nrAbonamente_Premium = nrAb;}
    void set_reducere(int r) {reducere = r;}
    int get_reducere() const {return reducere;}
    static void afis_nrAbonamente_Premium()
    {
        if (nrAbonamente_Premium)
            cout<<endl<<"Numarul de clienti cu abonament premium este: "<<nrAbonamente_Premium<<"."<<endl;
        else
            cout<<endl<<"Nu exista clienti cu abonament premium. :( ";
    }
};

template <class T>
int Abonament_Premium<T>::nrAbonamente_Premium = 0;

template <class U>
class Persoana
{
protected:
    U id;
    string nume;
    string cnp;

public:
    Persoana();
    Persoana(U, string);
    Persoana(U, string, string);
    Persoana(const Persoana<U>&);
    virtual ~Persoana() {};
    Persoana& operator=(const Persoana<U>&);
    void afis() {cout<<id<<" "<<nume<<" "<<cnp<<endl;}
    template <class U1>
    friend istream& operator>>(istream&, Persoana<U1>&);
    template <class U1>
    friend ostream& operator<<(ostream&, Persoana<U1>&);
};

template <class T, class U>
class Abonat: public Persoana<U>
{
protected:
    string nr_telefon;
    Abonament<T> *x;

public:
    Abonat();
    Abonat(U, string, string);
    Abonat(U, string, string, string);
    Abonat(const Abonat<T, U>&);
    ~Abonat() {};
    Abonat& operator=(const Abonat<T, U>&);
    template <class T2, class U2>
    friend istream& operator>>(istream&, Abonat<T2, U2>&);
    template <class T2, class U2>
    friend ostream& operator<<(ostream&, Abonat<T2, U2>&);

    template <class T3, class U3>
    friend class Clienti;
};

template <class T, class U>
class Clienti
{
    int nrClienti;
    vector<Abonat<T, U>> listaClienti;

public:
    Clienti();
    Clienti(int);
    Clienti(const Clienti&);
    ~Clienti() { }
    Clienti& operator=(Clienti&);
    template <class T1, class U1>
    friend istream& operator>>(istream&, Clienti<T1, U1>&);
    template <class T1, class U1>
    friend ostream& operator<<(ostream&, Clienti<T1, U1>&);
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

template <class T>
Abonament<T>::Abonament()
{

    //nume_abonament = "Nume abonament necunoscut";
    pret = 0;
    perioada = 0;
}

template <class T>
Abonament<T>::Abonament(T s, float f, int i)
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

template <class T>
Abonament_Premium<T>::Abonament_Premium(): Abonament<T>()
{
    reducere = 0;
    nrAbonamente_Premium++;
}

//Pseudoconstructor pentru tip de baza
template <class T>
Abonament_Premium<T>::Abonament_Premium(T s, float f, int i1, int i2): Abonament<T>(s, f, i1), reducere(i2)
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

template <class U>
Persoana<U>::Persoana()
{
    nume = "Nume persoana necunoscut";
    cnp = "Cod Numeric Personal necunoscut";
}

template <class U>
Persoana<U>::Persoana(U i, string s)
{
    id = i;
    nume = s;
    cnp = "Cod Numeric Personal necunoscut";
}

template <class U>
Persoana<U>::Persoana(U i, string s1, string s2)
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

template <class T, class U>
Abonat<T, U>::Abonat(): Persoana<U>()
{
    nr_telefon = "Numar de telefon necunoscut";
    x = new Abonament<T>(); /// by default consider un abonament standard
}

template <class T, class U>
Abonat<T, U>::Abonat(U i, string s1, string s2): Persoana<U>(i, s1)
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
        x = new Abonament<T>();
    else
        x = new Abonament_Premium<T>();
}

template <class T, class U>
Abonat<T, U>::Abonat(U i, string s1, string s2, string s3): Persoana<U>(i, s1, s2)
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
        x = new Abonament<T>();
    else
        x = new Abonament_Premium<T>();
}

template <class T, class U>
Clienti<T, U>::Clienti()
{
    nrClienti = 0;
}

template <class T, class U>
Clienti<T, U>::Clienti(int nr)
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
        Abonat<T, U> UNKNOWN;
        listaClienti[i] = UNKNOWN;
    }
}

template <class T>
Abonament<T>::Abonament(const Abonament<T>& A)
{
    nume_abonament = A.nume_abonament;
    pret = A.pret;
    perioada = A.perioada;
}

template <class T>
Abonament_Premium<T>::Abonament_Premium(const Abonament_Premium<T>& A): Abonament<T>(A)
{
    reducere = A.reducere;
    nrAbonamente_Premium++;
}

template <class U>
Persoana<U>::Persoana(const Persoana<U>& P)
{
    id = P.id;
    nume = P.nume;
    cnp = P.cnp;
}

template <class T, class U>
Abonat<T, U>::Abonat(const Abonat<T, U>& A): Persoana<U>(A)
{
    nr_telefon = A.nr_telefon;
    if (typeid(*(A.x)) == typeid(Abonament<T>))
    {
        x = new Abonament<T>();
        x->nume_abonament = (A.x)->nume_abonament;
        x->pret = (A.x)->pret;
        x->perioada = (A.x)->perioada;
    }
    else
    {
        x = new Abonament_Premium<T>();
        x->nume_abonament = (A.x)->nume_abonament;
        x->pret = (A.x)->pret;
        x->perioada = (A.x)->perioada;
        x->set_reducere( (A.x)->get_reducere() );
    }
}

template <class T, class U>
Clienti<T, U>::Clienti(const Clienti& C)
{
    nrClienti = C.nrClienti;
    for (int i = 0; i < nrClienti; i++)
    {
        listaClienti[i] = C.listaClienti[i];
    }
}

template <class T>
Abonament<T>& Abonament<T>::operator=(Abonament<T>& A)
{
    if(this != &A)
    {
        nume_abonament = A.nume_abonament;
        pret = A.pret;
        perioada = A.perioada;
    }

    return *this;
}

template <class T>
Abonament_Premium<T>& Abonament_Premium<T>::operator=(Abonament_Premium<T>& A)
{
    if(this != &A)
    {
        Abonament<T>::operator=(A);
        reducere = A.reducere;
    }

    return *this;
}

template <class U>
Persoana<U>& Persoana<U>::operator=(const Persoana<U>& P)
{
    if (this != &P)
    {
        id = P.id;
        nume = P.nume;
        cnp = P.cnp;
    }

    return *this;
}

template <class T, class U>
Abonat<T, U>& Abonat<T, U>::operator=(const Abonat<T, U>& A)
{
    if (this != &A)
    {
        Persoana<U>::operator=(A);
        nr_telefon = A.nr_telefon;
        if (typeid(*(A.x)) == typeid(Abonament<T>))
        {
            x = new Abonament<T>();
            x->nume_abonament = (A.x)->nume_abonament;
            x->pret = (A.x)->pret;
            x->perioada = (A.x)->perioada;
        }
        else
        {
            x = new Abonament_Premium<T>();
            x->nume_abonament = (A.x)->nume_abonament;
            x->pret = (A.x)->pret;
            x->perioada = (A.x)->perioada;
            x->set_reducere( (A.x)->get_reducere() );
        }
    }
}

template <class T, class U>
Clienti<T, U>& Clienti<T, U>::operator=(Clienti<T, U>& C)
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

template <class T1>
istream& operator>>(istream& in, Abonament<T1>& A)
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

template <class T1>
istream& operator>>(istream& in, Abonament_Premium<T1>& A)
{
    in>>(Abonament<T1>&) A;
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

template <class U1>
istream& operator>>(istream& in, Persoana<U1>& P)
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

template <class T2, class U2>
istream& operator>>(istream& in, Abonat<T2, U2>& A)
{
    in>>(Persoana<U2>&) A;
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
         A.x = new Abonament<T2>();
         in>>(Abonament<T2>&) (*A.x);
    }
    else
    {
        A.x = new Abonament_Premium<T2>();
        in>>(Abonament_Premium<T2>&) (*A.x);
    }

    return in;
}

template <class T, class U>
istream& operator>>(istream& in, Clienti<T, U>& C)
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
        Abonat<T, U> Ab;
        in>>Ab;
        C.listaClienti.push_back(Ab);
        //int nrAb;
        //nrAb = Abonament_Premium<T>::get_nrAbonamente();
        //nrAb--;
        //Abonament_Premium<T>::set_nrAbonamente(nrAb);
    }

    return in;
}

template <class T1>
ostream& operator<<(ostream& out, Abonament<T1>& A)
{
    out<<endl;
    out<<"Nume abonament: "<<A.nume_abonament<<endl;
    out<<"Pret: "<<A.pret<<(char)(238)<<endl;
    out<<"Perioada: "<<A.perioada;

    if (A.perioada == 1)
        out<<" luna"<<endl;
    else
        out<<" luni"<<endl;

    return out;
}

template <class T1>
ostream& operator<<(ostream& out, Abonament_Premium<T1>& A)
{
    out<<(Abonament<T1>&) A;
    out<<"Reducere: "<<A.reducere<<"%"<<endl;

    return out;
}

template <class U1>
ostream& operator<<(ostream& out, Persoana<U1>& P)
{
    out<<endl;
    out<<"ID: "<<P.id<<endl;
    out<<"Nume: "<<P.nume<<endl;
    out<<"CNP: "<<P.cnp<<endl;

    return out;
}

template <class T2, class U2>
ostream& operator<<(ostream& out, Abonat<T2, U2>& A)
{
    out<<(Persoana<U2>&) A;
    out<<"Numar de telefon: "<<A.nr_telefon;
    if (typeid(*(A.x)) == typeid(Abonament<T2>))
        out<<(Abonament<T2>&) (*(A.x));
    else
        out<<(Abonament_Premium<T2>&)(*(A.x));

    return out;
}

template <class T, class U>
ostream& operator<<(ostream& out, Clienti<T, U>& C)
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

template <class T, class U>
void Clienti<T, U>::SumaIncasata()
{
    float Suma = 0;
    for(int i = 0; i < nrClienti ;i++)
    {
        float incasare = (listaClienti[i].x)->incasare();
        Suma += incasare;
    }

    cout<<endl<<"Suma incasata de la toti abonatii Netflix este: "<<Suma<<".";
}

template <class T>
void Abonament<T>::afis()
{
    cout<<endl;
    cout<<"Nume abonament: "<<nume_abonament<<endl;
    SetConsoleOutputCP(1252);
    cout<<"Pret: "<<pret<<(char)(238)<<endl;
    cout<<"Perioada: "<<perioada;

    if (perioada == 1)
        cout<<" luna"<<endl;
    else
        cout<<" luni"<<endl;
}

template <class T>
void Abonament_Premium<T>::afis()
{
    Abonament<T>::afis();
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
    cout<<"     3. Citirea a N abonamente de tip Standard sau Premium. ( **vector )"<<endl;
    cout<<"     4. Citirea a N abonamente de tip Standard sau Premium. ( map )"<<endl;
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

    Clienti<string, string> C;

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
                Abonament_Premium<string>::afis_nrAbonamente_Premium();
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
                Abonament<string> *Ab;
                Abonament_Premium<string> AbPrem;
                cin>>AbPrem;
                cout<<endl<<endl<<"-->Abonamentul este: "<<endl<<AbPrem;

                _AbPrem = typeid(AbPrem).name();
                _AbType = typeid(Abonament<string>).name();

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
                Abonat<string, string> A;
                cin>>A;
                cout<<endl<<endl<<"-->Datele abonatului sunt: "<<endl<<A;

                _Abonat = typeid(A).name();
                _PersType = typeid(Persoana<string>).name();

                if (_Abonat.substr(2) == _PersType.substr(1))
                    cout<<endl<<"In acest moment, aceasta este o simpla persoana."<<endl;
                else
                    cout<<endl<<"In acest moment, acesta este un abonat Netflix."<<endl;

                cout<<endl<<endl<<endl<<"...Facem conversia..."<<endl<<endl<<endl;
                Sleep(4000);

                Persoana<string> *P;
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
                Abonament<string> **a;
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

                a = new Abonament<string>* [n];

                for (int i = 0; i < n; i++)
                {
                    cout<<endl<<endl<<"Alegeti numarul corespunzator variantei dorite:"<<endl;
                    cout<<"     1. Abonament. "<<endl;
                    cout<<"     2. Abonament Premium."<<endl<<endl;

                    cin>>optiune1;
                    if (optiune1 == 1)
                    {
                        a[i] = new Abonament<string>();
                        cin>>*a[i];
                    }
                    else
                    {
                        a[i] = new Abonament_Premium<string>(); //upcasting
                        cin>>*dynamic_cast<Abonament_Premium<string>*>(a[i]);
                    }
                }

                cout<<endl<<endl<<endl<<"Abonamentele sunt:"<<endl<<endl;

                for (int i = 0; i < n; i++)
                    a[i] -> afis();

                break;
            }
            case 4:
            {
                map<int, Abonament<string>> Ab;
                map<int, Abonament_Premium<string>> AbP;

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

                int nr = 0;

                for (int i = 0; i < n; i++)
                {
                    cout<<endl<<endl<<"Alegeti numarul corespunzator variantei dorite:"<<endl;
                    cout<<"     1. Abonament. "<<endl;
                    cout<<"     2. Abonament Premium."<<endl<<endl;

                    cin>>optiune1;
                    if (optiune1 == 1)
                    {
                        nr++;
                        Abonament<string> _Ab;
                        cin>>_Ab;
                        Ab.insert(pair<int, Abonament<string>>(nr, _Ab));
                    }
                    else
                    {
                        nr++;
                        Abonament_Premium<string> _AbP;
                        cin>>_AbP;
                        AbP.insert(pair<int, Abonament_Premium<string>>(nr, _AbP));
                    }
                }

                cout<<endl<<endl<<endl<<"Abonamentele sunt:"<<endl<<endl;

                for (int i = 1; i <= n; i++)
                {
                    for (auto it1 : Ab)
                        if (it1.first == i)
                            (it1.second).afis();
                    for (auto it2 : AbP)
                        if (it2.first == i)
                            (it2.second).afis();
                }

                break;
            }
        }

        cout<<endl<<endl<<endl<<"Doriti o alta optiune?"<<endl<<endl<<endl;
        mesaj_scris2();
        cin>>opti;
    }
}

