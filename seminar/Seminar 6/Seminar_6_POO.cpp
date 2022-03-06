#include <iostream>
#include <vector>
using namespace std;


class Bilet {
    protected:
        string statie_plecare;
        string statie_sosire;
        string data_plecare;
        int durata;
        int distanta;
        string id_bilet;
        string id_tren;
        static int nr_ord;

        virtual void read(istream&);
        virtual void write(ostream&) const;
    
    public:
        Bilet () = default;
        Bilet (string, string, string, int, int, string, string = "RII");
        virtual double price() = 0;
        virtual ~Bilet() {}

        string getIdTren ();

        bool operator >= (int);
        bool operator == (string);

        friend istream& operator>> (istream&, Bilet&);
        friend ostream& operator<< (ostream&, const Bilet&);
};

Bilet:: Bilet (string plecare, string sosire, string data, int durat, int dist, string tren, string tip) :
    statie_plecare(plecare), statie_sosire(sosire), data_plecare(data), durata(durat), distanta(dist), id_tren(tren)
{
    nr_ord++;
    this->id_bilet = tip + to_string(nr_ord);
}

istream& operator>> (istream& in, Bilet& b) {
    b.read(in);
    return in;
}

ostream& operator<< (ostream& out, const Bilet& b) {
    b.write(out);
    return out;
}

double Bilet::price() {
    return 0.39 * this->distanta;
}

void Bilet::read(istream& in) {
    in >> this->statie_plecare;
    in >> this->statie_sosire;
    in >> this->data_plecare;
    in >> this->distanta;
    in >> this->durata;
    in >> this->id_tren;
}


void Bilet::write (ostream& out) const {
    out << "-----------------------------" << endl;
    out << "Statie plecare" << this->statie_plecare << endl;
    out << "Statie sosire" << this->statie_sosire << endl;
    out << "Data plecare" << this->data_plecare << endl;
    out << "Distanta" << this->distanta << endl;
    out << "Durata" << this->durata << endl;
    out << "ID Tren" << this->id_tren << endl;
    out << "ID Bilet" << this->id_bilet << endl; 
}

string Bilet::getIdTren () {
    return this->id_tren;
}

bool Bilet::operator>= (int d) {
    return this->distanta >= d;
}

bool Bilet::operator== (string id) {
    return this->id_bilet == id;
}

class BiletRegioClasaII : public Bilet {
    public:
        BiletRegioClasaII() = default;
        BiletRegioClasaII (string, string, string, int, int, string);
        double price () {
            return Bilet::price();
        }
};

BiletRegioClasaII::BiletRegioClasaII (string plecare, string sosire, string data, int durat, int dist, string tren) : 
    Bilet(plecare, sosire, data, durat, dist, tren) 
{
    
}

class BiletRegioClasaI : virtual public Bilet {
    protected:
        string meniu;
    public:
        BiletRegioClasaI() = default;
        BiletRegioClasaI (string, string, string, int, int, string, string);

        void read(istream& in)  {
            Bilet::read(in);
            in >> this->meniu;
        }
        void write(ostream& out) const {
            Bilet::write(out);
            out << "Meniu inclus:" << this->meniu << endl;
        }
        
        double price() {
            double value = Bilet::price();
            return value + value * 0.2;
        }
};

BiletRegioClasaI::BiletRegioClasaI (string plecare, string sosire, string data, int durat, int dist, string tren, string menu) : 
    Bilet(plecare, sosire, data, durat, dist, tren, "RI"), meniu(menu)
{
    
}

int Bilet::nr_ord = 0;


class BiletInterRegioClasaII : virtual public Bilet {
    protected:
        int loc_rezervat;
    public:
        BiletInterRegioClasaII() = default;
        BiletInterRegioClasaII (string, string, string, int, int, string, int);

        void read(istream& in)  {
            Bilet::read(in);
            in >> this->loc_rezervat;
        }
        void write(ostream& out) const {
            Bilet::write(out);
            out << "Loc rezervat:" << this->loc_rezervat << endl;
        }
        
        double price() {
            return 0.7 * this->distanta;
        }
};

BiletInterRegioClasaII::BiletInterRegioClasaII (string plecare, string sosire, string data, int durat, int dist, string tren, int loc) : 
    Bilet(plecare, sosire, data, durat, dist, tren, "IRII"), loc_rezervat(loc)
{
    
}

class BiletInterRegioClasaI : public BiletRegioClasaI, public BiletInterRegioClasaII {

    public:
        void read(istream& in)  {
            BiletInterRegioClasaII::read(in);
            in >> this->meniu;
        }

        void write(ostream& out) const {
            BiletInterRegioClasaII:write(out);
            out << "Meniu inclus:" << this->meniu << endl;
        }
        
        double price() {
            double value = Bilet::price();
            return value + value * 0.2;
        }
};

class Meniu {
    public:

    static void run () {
        vector<Bilet*> bilete;

        auto result = find(bilete.begin(), bilete.end(), "id_citit de la tastatura");

        if (result != bilete.end()) {
            bilete.erase(result);
        }
    }
};

int main() {

};