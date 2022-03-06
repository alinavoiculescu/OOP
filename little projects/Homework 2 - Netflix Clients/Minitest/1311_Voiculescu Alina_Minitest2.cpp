#include <iostream>
#include <cstring>

using namespace std;

class Ingredient
{
    char denumire[100];
    double pretUnitar;
    int cantitate;

public:
    Ingredient();
    Ingredient(char[100], double, int);
    Ingredient(const Ingredient&);
    Ingredient& operator=(Ingredient&);
    ~Ingredient() {}
    operator char*() {return denumire;}
    int get_pret(){return pretUnitar;}
    friend istream& operator>>(istream&, Ingredient&);
    friend ostream& operator<<(ostream&, Ingredient&);
};


class Tort
{
    char* denumire;
    Ingredient lista_de_ingrediente[100];
    int nrIngrediente;
    static double Suma;

public:
    Tort();
    Tort(char*, int, Ingredient[100]);
    Tort(Tort&);
    Tort& operator=(Tort&);
    ~Tort() {delete denumire;}
    int get_suma(){return Suma;}
    friend istream& operator>>(istream&, Tort&);
    friend ostream& operator<<(ostream&, Tort&);

};

double Tort::Suma = 0;

class Comanda
{
protected:
    static int nr_comanda;
    int nrt;
    Tort t[100];

public:
    Comanda();
    Comanda(int, Tort[100]);
    Comanda(Comanda&);
    Comanda& operator=(Comanda&);
    virtual ~Comanda() {}
    virtual void Afisare();
    virtual double Total();
    friend istream& operator>>(istream&, Comanda&);
    friend ostream& operator<<(ostream&, Comanda&);
};

int Comanda::nr_comanda = 0;

class Comanda_Online: public Comanda
{
    char nume_client[100];
    char adresa[100];

public:
    Comanda_Online();
    Comanda_Online(int, Tort[100], char[100], char[100]);
    Comanda_Online(Comanda_Online&);
    Comanda_Online& operator=(Comanda_Online&);
    ~Comanda_Online() {}
    void Afisare();
    double Total();
    friend istream& operator>>(istream&, Comanda_Online&);
    friend ostream& operator<<(ostream&, Comanda_Online&);
};

int main()
{
//    Ingredient A;
//    cout<<A<<endl;
//
//    Ingredient B("Ingr1", 2.3, 3);
//    cout<<B<<endl;
//
//    Ingredient C;
//    C=B;
//    cout<<C<<endl;
//
//    Tort D;
//    cout<<D<<endl;
//
//    Tort E;
//    cin>>E;
//    cout<<E<<endl;

//    Comanda F;
//    cout<<F<<endl;

//    Comanda G;
//    cin>>G;
//    cout<<G<<endl;

//    Comanda_Online H;
//    cout<<H;

//    Comanda_Online I;
//    cin>>I;
//    cout<<I;

/////UPCASTING
//    Comanda *Com;
//    Comanda_Online *ComOn;
//    cin>>ComOn;
//    cout<<endl<<endl<<"Comanda online este: "<<endl<<ComOn;
//
//    Com = &ComOn;
//    cout<<endl<<endl<<"Comanda, dupa upcasting, este: "<<endl<<*Com;


/////DOWNCASTING&VECTOR
//    Comanda **c;
//    int n, optiune;
//    try
//    {
//        cout<<"Introduceti numarul de comenzi: ";
//        cin>>n;
//        if(n<=0)
//            throw 13;
//    }
//    catch(int x)
//    {
//        cout<<"Dimensiunea vectorului nu poate fi nula sau negativa!";
//    }
//    c = new Comanda* [n];
//
//    for(int i = 0; i < n; i++)
//    {
//        cout<<"Dati optiunea dorita: "<<endl;
//        cout<<"1. Comanda; 2. Comanda Online"<<endl;
//        cin>>optiune;
//        if(optiune == 1)
//        {
//            c[i] = new Comanda();
//            cin>>*c[i];
//        }
//        else
//        {
//            c[i] = new Comanda_Online();
//            cin>>*dynamic_cast<Comanda_Online*>(c[i]);
//        }
//    }
//
//    for (int i = 0; i <n; i++)
//        c[i]->Afisare();

    return 0;
}

Ingredient::Ingredient()
{
    strcpy(denumire, "Necunoscuta");
    pretUnitar = 0;
    cantitate = 0;
}

Ingredient::Ingredient(char a[100], double b, int c)
{
    strcpy(denumire, a);
    pretUnitar = b;
    cantitate = c;
}

Ingredient::Ingredient(const Ingredient& I)
{
    strcpy(denumire, I.denumire);
    pretUnitar = I.pretUnitar;
    cantitate = I.cantitate;
}

Ingredient& Ingredient::operator=(Ingredient& I)
{
    if (this != &I)
    {
        strcpy(denumire, I.denumire);
        pretUnitar = I.pretUnitar;
        cantitate = I.cantitate;
    }

    return *this;
}

istream& operator>>(istream& in, Ingredient& I)
{
    cout<<"Denumire: ";
    in.get();
    in.getline(I.denumire, 100);
    cout<<endl;
    cout<<"Pret unitar: ";
    in>>I.pretUnitar;
    cout<<endl;
    cout<<"Cantitate: ";
    in>>I.cantitate;
    cout<<endl;

    return in;
}

ostream& operator<<(ostream& out, Ingredient& I)
{
    out<<"Denumire: "<<I.denumire<<endl;
    out<<"Pret unitar: "<<I.pretUnitar<<endl;
    out<<"Cantitate: "<<I.cantitate<<endl;

    return out;
}

Tort::Tort()
{
    denumire = "Necunoscuta";
    nrIngrediente = 0;
}

Tort::Tort(char* a, int c, Ingredient b[100])
{
    denumire = a;
    nrIngrediente = c;
    for(int i = 0; i < nrIngrediente; i++)
    {
        lista_de_ingrediente[i] = b[i];
        double pret = (lista_de_ingrediente[i]).get_pret();
        Suma += pret;
    }

}

Tort::Tort(Tort& T)
{
    denumire = T.denumire;
    nrIngrediente = T.nrIngrediente;
    for (int i = 0; i < nrIngrediente; i++)
    {
        lista_de_ingrediente[i] = T.lista_de_ingrediente[i];
        double pret = (lista_de_ingrediente[i]).get_pret();
        Suma += pret;
    }
}

Tort& Tort::operator=(Tort& T)
{
    if (this != &T)
    {
        denumire = T.denumire;
        nrIngrediente = T.nrIngrediente;
        for (int i = 0; i < nrIngrediente; i++)
            lista_de_ingrediente[i] = T.lista_de_ingrediente[i];
    }

    return *this;
}

istream& operator>>(istream& in, Tort& T)
{
    cout<<"Denumire: ";
    T.denumire = new char[100];
    in>>T.denumire;
    cout<<endl;
    cout<<"Nr. Ingrediente: ";
    in>>T.nrIngrediente;
    cout<<endl;
    cout<<"Ingrediente: "<<endl;
    for (int i = 0; i < T.nrIngrediente; i++)
    {
        cout<<"Ingredientul "<<i+1<<": ";
        in>>T.lista_de_ingrediente[i];
        cout<<endl;
    }
    cout<<endl;

    return in;
}

ostream& operator<<(ostream& out, Tort& T)
{
    out<<"Denumire: "<<T.denumire<<endl;
    out<<"Nr. ingrediente: "<<T.nrIngrediente<<endl;
    for (int i = 0; i < T.nrIngrediente; i++)
    {
        out<<"Ingredientul "<<i+1<<": "<<T.lista_de_ingrediente[i]<<endl;
    }
    out<<endl;

    return out;
}

Comanda::Comanda()
{
    nr_comanda++;
    nrt = 0;
}

Comanda::Comanda(int a, Tort b[100])
{
    nr_comanda++;
    nrt = a;
    for (int i = 0; i < nrt; i++)
        t[i] = b[i];
}

Comanda::Comanda(Comanda& C)
{
    nr_comanda++;
    nrt = C.nrt;
    for (int i = 0; i < nrt; i++)
    {
        t[i] = C.t[i];
    }
}

Comanda& Comanda::operator=(Comanda& C)
{
    if (this != &C)
    {
        nrt = C.nrt;
        for (int i = 0; i < nrt; i++)
        {
            t[i] = C.t[i];
        }
    }

    return *this;
}

istream& operator>>(istream& in, Comanda& C)
{
    cout<<"Nr. torturi: ";
    in>>C.nrt;
    cout<<"Torturile sunt: "<<endl;
    for (int i = 0; i < C.nrt; i++)
    {
        cout<<"Tortul "<<i+1<<": ";
        in>>C.t[i];
        cout<<endl;
    }
    cout<<endl;

    return in;
}


ostream& operator<<(ostream& out, Comanda& C)
{
    out<<"Nr. comanda:"<<C.nr_comanda<<endl;
    out<<"Nr. torturi: "<<C.nrt<<endl;
    for (int i = 0; i < C.nrt; i++)
    {
        out<<"Tortul "<<i+1<<": "<<C.t[i];
        out<<endl;
    }
    out<<endl;

    return out;
}

void Comanda::Afisare()
{
    cout<<"Nr. comanda:"<<nr_comanda<<endl;
    cout<<"Nr. torturi: "<<nrt<<endl;
    for (int i = 0; i < nrt; i++)
    {
        cout<<"Tortul "<<i+1<<": "<<t[i];
        cout<<endl;
    }
    cout<<endl;
}

Comanda_Online::Comanda_Online(): Comanda()
{
    strcpy(nume_client, "Necunoscut");
    strcpy(adresa, "Necunoscuta");
}

//Comanda_Online::Comanda_Online(int a, Tort b[100], char c[100], char d[100]): Comanda(a, b[100], c[100])
//{
//    strcpy(nume_client, d);
//    strcpy(adresa, e);
//}

Comanda_Online::Comanda_Online(Comanda_Online& C): Comanda(C)
{
    strcpy(nume_client, C.nume_client);
    strcpy(adresa, C.adresa);
}

Comanda_Online& Comanda_Online::operator=(Comanda_Online& C)
{
    if (this != &C)
    {
        Comanda::operator=(C);
        strcpy(nume_client, C.nume_client);
        strcpy(adresa, C.adresa);
    }

    return *this;
}

istream& operator>>(istream& in, Comanda_Online& C)
{
    in>>(Comanda&) C;
    cout<<"Nume client: ";
    in.get();
    in.getline(C.nume_client, 100);
    cout<<endl;
    cout<<"Adresa: ";
    in.get();
    in.getline(C.adresa, 100);
    cout<<endl;

    return in;
}

ostream& operator<<(ostream& out, Comanda_Online& C)
{
    out<<(Comanda&) C;
    out<<"Nume client: "<<C.nume_client<<endl;
    out<<"Adresa: "<<C.adresa<<endl;

    return out;
}

void Comanda_Online::Afisare()
{
    Comanda::Afisare();
    cout<<"Nume client: "<<nume_client<<endl;
    cout<<"Adresa: "<<adresa<<endl;
}

double Comanda::Total()
{
    double total = 0;
    for (int i = 0; i < nrt; i++)
    {
        total += t[i].get_suma();
    }

    return total;
}

double Comanda_Online::Total()
{
    double total = 0;
    for (int i = 0; i < nrt; i++)
    {
        total += t[i].get_suma();
    }

    return total * 110/100;
}
