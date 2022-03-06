#include <iostream>

using namespace std;

/// POO - constructori si destructor

class Masina
{
    int *v;
    string marca;
    int viteza;
public:
    string get_marca(){return marca;}
    int get_viteza() { return viteza;}
    void set_marca(string);

///    Masina(); /// constructor de initializare fara parametri
///    Masina(string); /// constr parametrizat cu 1 parametru
///    Masina(string, int);  /// constr parametrizat cu 2 parametri

    Masina(string s = "Dacia", int n = 200)  /// constr parametrizat cu 2 parametri si cu valori implicite
    {
     marca = s;
    viteza = n;
    v = new int [100];
    }

    Masina(int, string);
    ~Masina() { cout<<"Destructor  "<<marca<<endl;  delete[ ] v;}
};

/*
Masina::Masina()
{
    marca = "Dacia";
    viteza = 200;
}

Masina::Masina(string s)
{
    marca = s;
    viteza = 1200;
}

Masina::Masina(string s, int n)
{
    marca = s;
    viteza = n;
}*/

Masina::Masina(int n, string s)
{
    marca = s;
    viteza = n;
}

void Masina::set_marca(string s)
{
    marca = s;
}

int main()
{
        Masina A;
        cout<<A.get_marca()<<"  "<<A.get_viteza()<<endl;
        Masina B("Audi");
        cout<<B.get_marca()<<"  "<<B.get_viteza()<<endl;
        Masina C("BMW",300);
        cout<<C.get_marca()<<"  "<<C.get_viteza()<<endl;
        Masina D(400,"Tico");
        cout<<D.get_marca()<<"  "<<D.get_viteza()<<endl;
}

/// POO - operator de rezolutie de scop
/*class Masina
{
    string marca;
    int viteza;
public:
    void citire();
    void afisare();
    string get_marca();
    void set_marca(string);
};

class Punct
{
    int x;
    public:
    void citire();
};

void Punct::citire()
{
    cin>>x;
}

    void Masina::citire()
    {
        cin>>marca>>viteza;
    }
    void Masina::afisare()
    {
        cout<<marca<<"  "<<viteza<<endl;
    }

    string Masina::get_marca()
    {
        return marca;
    }
    void Masina::set_marca(string x)
    {
        marca = x;
    }

int main()
{
    Masina A;
///    cout<<A.marca; - inaccesibil pt ca private
    A.set_marca("Audi");
    cout<<A.get_marca();
    A.citire();
    A.afisare();
}
*/

/// POO - set si get
/*class Masina
{
    string marca;
    int viteza;
public:
    void citire()
    {
        cin>>marca>>viteza;
    }
    void afisare()
    {
        cout<<marca<<"  "<<viteza<<endl;
    }

    string get_marca()
    {
        return marca;
    }
    void set_marca(string x)
    {
        marca = x;
    }
};

int main()
{
    Masina A;
///    cout<<A.marca; - inaccesibil pt ca private
    A.set_marca("Audi");
    cout<<A.get_marca();
    A.citire();
    A.afisare();
}
*/

/// C / C++ -  clase
/*class Masina
{
    string marca;
    int viteza;
    public:
void citire() { cin>>marca>>viteza;}
void afisare() { cout<<marca<<"  "<<viteza<<endl;}
};

int main()
{
    Masina A;
///    cout<<A.marca; - inaccesibil pt ca private
    A.citire();
    A.afisare();
}*/

/// C / C++ -  structuri - includerea functiilor in structuri
/*struct Masina
{
    string marca;
    int viteza;
void citire() { cin>>marca>>viteza;}
void afisare() { cout<<marca<<"  "<<viteza<<endl;}
};

int main()
{
    Masina A;
    A.citire();
    A.afisare();
}
*/

/// C / C++ -  structuri
/*struct Masina
{
    string marca;
    int viteza;
};

void citire(Masina & m) { cin>>m.marca>>m.viteza;}

void afisare(Masina m) { cout<<m.marca<<"  "<<m.viteza<<endl;}

int main()
{
    Masina A;
    citire(A);
    afisare(A);
}
*/
