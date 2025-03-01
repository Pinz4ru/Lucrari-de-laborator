#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

class Rezervare {
protected:
    string numeClient, prenumeCLient, data, ora;
    int nrPersoane;
public:
    Rezervare(string nume, string prenume, string d, string o, int persoane) : numeClient(nume),prenumeCLient(prenume), data(d), ora(o), nrPersoane(persoane) {}
    virtual ~Rezervare() {}
    virtual float calculeazaPret() const = 0;
    virtual int calculeazaDurata() const { return 2; } 
    virtual void afiseaza() const {
        cout << "Client: " << numeClient << ", Data: " << data << " Ora: " << ora << ", Nr. persoane: " << nrPersoane<<" Pretul rezervarii: "<<calculeazaPret()<<endl;
        cout<<"----------------------------------------------------------------------------------------------------------------"<<endl;
    }
};

class RezervareZilnica : public Rezervare {
public:
    RezervareZilnica(string nume, string prenume, string d, string o, int persoane) : Rezervare(nume,prenume, d, o, persoane) {}
    float calculeazaPret() const override {
        float pret = 50;
        if (nrPersoane > 2) {
            pret += (nrPersoane - 2) * 20;
        }
        return pret;
    }
    void afiseaza() const override {
        cout << "[Zilnic] "; 
        Rezervare::afiseaza();
    }
};

class RezervareEvenimentSpecial : public Rezervare {
public:
    RezervareEvenimentSpecial(string nume, string prenume, string d, string o, int persoane) : Rezervare(nume,prenume, d, o, persoane) {}
    float calculeazaPret() const override {
        float pret = 200;
        if (nrPersoane > 10) {
            pret += (nrPersoane - 10) * 10;
        }
        return pret;
    }
    int calculeazaDurata() const override { return 6; }
    void afiseaza() const override {
        cout << "[Eveniment Special] ";  
        Rezervare::afiseaza();
    }
};

class RezervareGrupMare : public Rezervare {
public:
    RezervareGrupMare(string nume, string prenume, string d, string o, int persoane) : Rezervare(nume,prenume, d, o, persoane) {}
    float calculeazaPret() const override {
        float pret = 500;
        if (nrPersoane > 20) {
            pret += (nrPersoane - 20) * 10;
        }
        return pret;
    }
    int calculeazaDurata() const override { return 3; }
    void afiseaza() const override{
        cout << "[Grup Mare] "; 
        Rezervare::afiseaza();
    }
};

int main() {
    ifstream fin("rezervari.in");
    if (!fin) {
        cerr << "Eroare la deschiderea fisierului!";
        return 1;
    }
    
    vector<Rezervare*> rezervari;
    string linie, tip, nume,prenume, data, ora;
    int persoane;
    
    while (getline(fin, linie)) {
        stringstream ss(linie);
        ss >> tip >> nume >>prenume>> data >> ora >> persoane;
        
        if (tip == "RezervareZilnica") rezervari.push_back(new RezervareZilnica(nume, prenume, data, ora, persoane));
        else if (tip == "RezervareEvenimentSpecial") rezervari.push_back(new RezervareEvenimentSpecial(nume,prenume, data, ora, persoane));
        else if (tip == "RezervareGrupMare") rezervari.push_back(new RezervareGrupMare(nume,prenume, data, ora, persoane));
    }
    fin.close();
    
    cout << "Rezervari citite:\n";
    for (auto r : rezervari) {
        r->afiseaza();
    }
    
    for (auto r : rezervari) delete r;
    return 0;
}

