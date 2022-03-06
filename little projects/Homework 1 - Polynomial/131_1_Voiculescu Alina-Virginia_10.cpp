#include <iostream>

using namespace std;

class Polinom           ///clasa
{
    double Coef[100];   /*private*/
    int NrElemente;

public:                 /*public*/
    Polinom();
    Polinom(const Polinom&);
    friend istream& operator>>(istream&, Polinom&);
    friend ostream& operator<<(ostream&, const Polinom&);
    Polinom& operator=(Polinom&);
    friend Polinom& operator+(Polinom&, Polinom&);
    friend Polinom& operator-(Polinom&, Polinom&);
    friend Polinom& operator*(Polinom&, Polinom&);
    ~Polinom();
    void set_Polinom(double, int);  /*set*/
    int NrElem();
    int get_Grad();
    void get_Polinom();
    void ValPunct(double);
    /************************/
    void citire();
};

void mesaj_scris()
{
    cout<<endl;
    cout<<"Alegeti numarul corespunzator comenzii dorite:"<<endl;
    cout<<"     1. Citirea polinomului de baza."<<endl;
    cout<<"     2. Afisarea polinomului de baza."<<endl;
    cout<<"     3. Aflarea valorii intr-un punct."<<endl;
    cout<<"     4. Adunarea a doua polinoame."<<endl;
    cout<<"     5. Scaderea a doua polinoame."<<endl;
    cout<<"     6. Inmultirea a doua polinoame."<<endl;
    cout<<"     0. Iesire."<<endl;
}

int meniu()
{
    Polinom A;  /// polinomul de baza

    cout<<"Pentru a putea rula programul, este nevoie de minim un polinom; il vom denumi <de baza>"<<endl;

    mesaj_scris();

    int optiune;
    cin>>optiune;
    while(optiune)
    {
        switch(optiune)
        {
        case 1:  /// citirea polinomului de baza
        {
            A.citire();
            break;
            break;
        }
        case 2:  /// afisarea polinomului de baza
        {
            cout<<endl<<"Polinomul dumneavoastra este: "<<A<<endl;
            break;
        }
        case 3:   /// valoarea intr-un punct
        {
            cout<<endl<<"Introduceti valoarea: ";
            int e;
            cin>>e;
            A.ValPunct(e);
            break;
        }
        case 4:
        {
            /// adunarea a 2 polinoame
            Polinom A1;
            A1.citire();
            cout<<endl<<"Polinomul dumneavoastra este: "<<A1<<endl;

            cout<<"Adunarea polinomului ";
            cout<<A;
            cout<<endl<<"cu cea a polinomului ";
            cout<<A1;
            cout<<endl<<"este egala cu polinomul: ";
            Polinom B;
            B=A+A1;
            cout<<B;
            break;
        }
        case 5:
        {
            /// scaderea a 2 polinoame
            Polinom A1;
            A1.citire();
            cout<<endl<<"Polinomul dumneavoastra este: "<<A1<<endl;

            cout<<"Scaderea polinomului ";
            cout<<A;
            cout<<endl<<"cu cea a polinomului ";
            cout<<A1;
            cout<<endl<<"este egala cu polinomul: ";
            Polinom B;
            B=A-A1;
            cout<<B;
            break;
        }
        case 6:
        {
            /// inmultirea a 2 polinoame
            Polinom A1;
            A1.citire();
            cout<<endl<<"Polinomul dumneavoastra este: "<<A1<<endl;

            cout<<"Inmultirea polinomului ";
            cout<<A;
            cout<<endl<<"cu cea a polinomului ";
            cout<<A1;
            cout<<endl<<"este egala cu polinomul: ";
            Polinom B;
            B=A*A1;
            cout<<B;
            break;
        }
        }
        cout<<"Doriti o alta optiune?"<<endl;
        mesaj_scris();
        cin>>optiune;
    }

}

int main()
{
    meniu();
    return 0;
}

/*************************************/
void Polinom::citire()
{
    int nr_elem,a,b,c;
    cout<<endl<<"Introduceti numarul de elemente: ";
    cin>>nr_elem;

    cout<<endl<<"Introduceti elementele(tip: 1 2, 1 = coeficient, 2 = grad): ";
    for (int i = 0; i < nr_elem; i++)
    {
        cin>>a>>b;
        set_Polinom(a,b);
    }
}
/*************************************/
Polinom::Polinom()      ///constructor de initializare
{
    for (int i = 0; i < 100; i++)
        Coef[i] = 0;
}

Polinom::Polinom(const Polinom& A) ///constructor de copiere
{
    NrElemente = A.NrElemente;
    for (int i = 0; i < 100; i++)
        this->Coef[i] = A.Coef[i];
}

Polinom& Polinom::operator=(Polinom& A)
{
    if (this != &A)
    {
        NrElemente = A.NrElemente;
        for (int i = 0; i < NrElemente; i++)
            this->Coef[i] = A.Coef[i];
    }
    return *this;

}

istream& operator>>(istream& in, Polinom& A)
{
    in>>A.NrElemente;
    for (int i = 0; i < A.NrElemente; i++)
        in>>A.Coef[i];
    return in;
}

ostream& operator<<(ostream& out, const Polinom& A)
{
    int afis = 0, nr = 0;
    for (int i=99; i>=0; i--)
    {
        if (A.Coef[i] == 1)
        {
            if (afis != 0 && i != 0)
                if (i == 1)
                    out<<"+ X ";
                else
                    out<<"+ X^"<<i<<" ";
            else if (i != 0)
                if (i == 1)
                    out<<"X ";
                else
                    out<<"X^"<<i<<" ";
            if (afis != 0 && i == 0)
                out<<"+ "<<1<<" ";
            else if (i == 0)
                out<<1<<" ";

            afis = 1;
            nr += 1;
        }
        else if (A.Coef[i] == -1)
        {
            if (afis != 0 && i != 0)
                if (i == 1)
                    out<<"- X ";
                else
                    out<<"- X^"<<i<<" ";
            else if (i != 0)
                if (i == 1)
                    out<<"- X ";
                else
                    out<<"- X^"<<i<<" ";
            if (afis != 0 && i == 0)
                out<<"- "<<1<<" ";
            else if (i == 0)
                out<<-1<<" ";

            afis = 1;
            nr += 1;
        }
        else if (A.Coef[i] != 0)
        {
            if (i == 0)
            {
                if (afis != 0)
                    out<<"+ "<<A.Coef[i]<<" ";
                else
                    out<<A.Coef[i]<<" ";
                afis = 1;
                nr += 1;
            }
            else if (i == 1)
            {
                if (afis != 0)
                    out<<"+ "<<A.Coef[i]<<"X"<<" ";
                else
                    out<<A.Coef[i]<<"X"<<" ";
                afis = 1;
                nr += 1;
            }
            else if (A.Coef[i] < 0)
            {
                out<<A.Coef[i]<<"X^"<<i<<" ";
                afis = 1;
                nr += 1;
            }
            else
            {
                if (afis != 0)
                    out<<"+ "<<A.Coef[i]<<"X^"<<i<<" ";
                else
                    out<<A.Coef[i]<<"X^"<<i<<" ";
                afis = 1;
                nr += 1;
            }
        }
    }
    if (afis != 0)
        out<<"= 0"<<endl;
    else
        out<<"0 = 0"<<endl;
    out<<endl;
    return out;
}

Polinom& operator+(Polinom& A, Polinom& B)
{
    Polinom C;
    C.NrElemente = max(A.NrElemente, B.NrElemente);
    for (int i = 0; i < max(A.NrElemente, B.NrElemente); i++)
        C.Coef[i] = A.Coef[i] + B.Coef[i];
    return C;

}
Polinom& operator-(Polinom& A, Polinom& B)
{
    Polinom C;
    C.NrElemente = max(A.NrElemente, B.NrElemente);
    for (int i = 0; i < max(A.NrElemente, B.NrElemente); i++)
        C.Coef[i] = A.Coef[i] - B.Coef[i];
    return C;
}

Polinom& operator*(Polinom& A, Polinom& B)
{
    Polinom C;
    C.NrElemente = A.NrElemente + B.NrElemente;
    for (int i = 0; i<A.NrElemente; i++)
    {
        for (int j = 0; j < B.NrElemente; j++)
            C.Coef[i+j] += A.Coef[i]*B.Coef[j];
    }
    return C;
}

Polinom::~Polinom()
{
    ///cout<<endl<<"Polinomul dumneavoastra a fost distrus."<<endl;
}

void Polinom::set_Polinom(double x, int y)  /*set*/
{
    Coef[y] = x;
    NrElemente = NrElem();
}

int Polinom::NrElem()
{
    int n=0;
    for (int i=0; i<100; i++)
        if (Coef[i]!=0)
            n=i+1;
    return n;
}

int Polinom::get_Grad()
{
    int Grad = NrElemente - 1;
    return Grad;
}

void Polinom::get_Polinom()
{
    int afis = 0, nr = 0;
    for (int i=99; i>=0; i--)
    {
        if (Coef[i] == 1)
        {
            if (afis != 0 && i != 0)
                if (i == 1)
                    cout<<"+ X ";
                else
                    cout<<"+ X^"<<i<<" ";
            else if (i != 0)
                if (i == 1)
                    cout<<"X ";
                else
                    cout<<"X^"<<i<<" ";
            if (afis != 0 && i == 0)
                cout<<"+ "<<1<<" ";
            else if (i == 0)
                cout<<1<<" ";
            afis = 1;
            nr += 1;
        }
        else if (Coef[i] == -1)
        {
            if (afis != 0 && i != 0)
                if (i == 1)
                    cout<<"- X ";
                else
                    cout<<"- X^"<<i<<" ";
            else if (i != 0)
                if (i == 1)
                    cout<<"- X ";
                else
                    cout<<"- X^"<<i<<" ";
            if (afis != 0 && i == 0)
                cout<<"- "<<1<<" ";
            else if (i == 0)
                cout<<-1<<" ";
            afis = 1;
            nr += 1;
        }
        else if (Coef[i] != 0)
        {
            if (i == 0)
            {
                if (afis != 0)
                    cout<<"+ "<<Coef[i]<<" ";
                else
                    cout<<Coef[i]<<" ";
                afis = 1;
                nr += 1;
            }
            else if (i == 1)
            {
                if (afis != 0)
                    cout<<"+ "<<Coef[i]<<"X"<<" ";
                else
                    cout<<Coef[i]<<"X"<<" ";
                afis = 1;
                nr += 1;
            }
            else if (Coef[i] < 0)
            {
                cout<<Coef[i]<<"X^"<<i<<" ";
                afis = 1;
                nr += 1;
            }
            else
            {
                if (afis != 0)
                    cout<<"+ "<<Coef[i]<<"X^"<<i<<" ";
                else
                    cout<<Coef[i]<<"X^"<<i<<" ";
                afis = 1;
                nr += 1;
            }
        }
    }
    if (afis != 0)
        cout<<"= 0"<<endl;
    else
        cout<<"0 = 0"<<endl;


}

void Polinom::ValPunct(double a)
{
    int val=0, p=1;
    for (int i=0; i<NrElemente; i++)
    {
        val = val + Coef[i]*p;
        p = p*a;
    }
    cout<<"Valoarea polinomului in punctul "<<a<<" este "<<val<<"."<<endl;
}
