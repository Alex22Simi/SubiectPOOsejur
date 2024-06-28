#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Sejur
{
	const int idSejur;
	string destinatie;//operator de indexare ->mai usor de aplicat pe atribute
	//diferite de char*
	int nrNopti;
	int nrPersoane;
	int* varstaPersoane;
	float pret;
public:
	Sejur():idSejur(1)
	{
		this->destinatie = "X";
		this->nrNopti = 0;
		this->nrPersoane = 0;
		this->varstaPersoane = NULL;
		this->pret = 0;
	}
	Sejur(int idSejur,string destinatie, int nrNopti,int nrPersoane, int* varstaPersoane, float pret):idSejur(idSejur)
	{
		this->destinatie = destinatie;
		this->nrNopti = nrNopti;
		this->nrPersoane = nrPersoane;
		this->varstaPersoane = new int[this->nrPersoane];
		for (int i = 0; i < this->nrPersoane; i++)
		{
			this->varstaPersoane[i] = varstaPersoane[i];
		}
		this->pret = pret;
	}
	int getNrNopti()
	{
		return this->nrNopti;
	}
	void setNrNopti(int nrNopti)
	{
		this->nrNopti = nrNopti;
	}
	float getPret()
	{
		return this->pret;
	}
	void setPret(float pret)
	{
		if (pret >= 100)
		{
			this->pret = pret;
		}
	}
	int getNrPersoane()
	{
		return this->nrPersoane;
	}
	int* getVarstaPersoane()
	{
		return this->varstaPersoane;
	}

	void setVarstaPersoane(int nrPersoane, int* varstaPersoane)
	{
		if (nrPersoane > 0 && varstaPersoane != NULL)
		{
			if (this->varstaPersoane != NULL)
			{
				delete[] this->varstaPersoane;
			}
			this->nrPersoane = nrPersoane;
			this->varstaPersoane = new int[this->nrPersoane];

			for (int i = 0; i < this->nrPersoane; i++)
			{
				this->varstaPersoane[i] = varstaPersoane[i];
			}
		}
	}

	~Sejur()
	{
		if (this->varstaPersoane != NULL)
		{
			delete[] this->varstaPersoane;
		}
	}
	//constr de copiere 
	Sejur(const Sejur& s):idSejur(s.idSejur)
	{
		this->destinatie = s.destinatie;
		this->nrNopti = s.nrNopti;
		this->nrPersoane = s.nrPersoane;
		this->varstaPersoane = new int[this->nrPersoane];
		for (int i = 0; i < this->nrPersoane; i++)
		{
			this->varstaPersoane[i] = s.varstaPersoane[i];
		}
		this->pret = s.pret;
	}
	//operator =
	Sejur& operator=(const Sejur& s)
	{
		if (this != &s)
		{
			if (this->varstaPersoane != NULL)
			{
				delete[] this->varstaPersoane;
			}
			this->destinatie = s.destinatie;
			this->nrNopti = s.nrNopti;
			this->nrPersoane = s.nrPersoane;
			this->varstaPersoane = new int[this->nrPersoane];
			for (int i = 0; i < this->nrPersoane; i++)
			{
				this->varstaPersoane[i] = s.varstaPersoane[i];
			}
			this->pret = s.pret;
		}
		return *this;
	}
	//obiect+ valoare
	//obiect+ obiect
	//valoare+ obiect
	friend Sejur operator+(float valoare, Sejur s)
	{
		//in functiile friend si static nu folosim this!!!!!
		Sejur copie = s;
		copie.pret += valoare;
		return copie;
	}
	//operator indexare
	int& operator[](int poz)
	{
		if (poz >= 0 && poz < this->nrPersoane)
		{
			return this->varstaPersoane[poz];
		}
		else
		{
			int err = -1;
			return err;
		}
	}
	//scriere in fisier -> nu citim artibute const sau statice
	//serializare -> transformarea unui obiect intr-o secv de biti
	void serializare(string numeFisier)
	{
		ofstream f(numeFisier, ios::out | ios::binary);
		//cum scriem string in binar
		int lungDestinatie = this->destinatie.size();
		f.write((char*)&lungDestinatie, sizeof(lungDestinatie));
		f.write(this->destinatie.c_str(), lungDestinatie + 1);
		//c_str() -> transforma un string intr-un const char*

		//cum scriem la char* in binar
		//int lungDestinatie = strlen(this->destinatie);
		//f.write((char*)&lungDestinatie, sizeof(lungDestinatie));
		//f.write(this->destinatie, lungDestinatie + 1);


		//asa scriem un numar -> 24==> '2' '4'
		f.write((char*)&this->nrNopti, sizeof(this->nrNopti));
		f.write((char*)&this->nrPersoane, sizeof(this->nrPersoane));
		for (int i = 0; i < this->nrPersoane; i++)
		{
			f.write((char*)&this->varstaPersoane[i], sizeof(this->varstaPersoane[i]));
		}
		f.write((char*)&this->pret, sizeof(this->pret));
		f.close();
	}
	//deserializare -> transfomarea dintr=o secv de biti intr-un obiect
	void deserializare(string numeFisier)
	{
		ifstream f(numeFisier, ios::in | ios::binary);
		if (f.is_open())
		{
			//cum citim un string
			int lungDestinatie = 0;
			f.read((char*)&lungDestinatie, sizeof(lungDestinatie));
			char* aux = new char[lungDestinatie + 1];
			f.read(aux, lungDestinatie + 1);
			this->destinatie = aux;
			delete[] aux;

			//cum citim un char*
			/*if (this->destinatie != NULL)
			{
				delete[] this->destinatie;
			}
			int lungDestinatie = 0;
			f.read((char*)&lungDestinatie, sizeof(lungDestinatie));
			this->destinatie = new char[lungDestinatie + 1];
			f.read(this->destinatie, lungDestinatie + 1);*/
			

			//nr intregi etc
			f.read((char*)&this->nrNopti, sizeof(this->nrNopti));
			f.read((char*)&this->nrPersoane, sizeof(this->nrPersoane));
			if (this->varstaPersoane != NULL)
			{
				delete[] this->varstaPersoane;
			}
			this->varstaPersoane = new int[this->nrPersoane];
			for (int i = 0; i < this->nrPersoane; i++)
			{
				f.read((char*)&this->varstaPersoane[i], sizeof(this->varstaPersoane[i]));
			}
			f.read((char*)&this->pret, sizeof(this->pret));
			f.close();

		}
		else
		{
			cout << "Nu exista fisierul cautat!" << endl;
		}
	}

	friend ostream& operator<<(ostream &out, const Sejur& s )
	{
		out << s.idSejur << endl;
		out << s.destinatie << endl;
		out << s.nrNopti << endl;
		out << s.nrPersoane << endl;
		for (int i = 0; i < s.nrPersoane; i++)
		{
			out << s.varstaPersoane[i] << ", ";
		}
		out << endl;
		out << s.pret << endl;
		return out;
	}
};
class AgentieTurism
{
	string nume;
	int nrSejururi;
	Sejur* sejururi;
public:
	AgentieTurism()
	{
		this->nume = "?";
		this->nrSejururi = 0;
		this->sejururi = NULL;

	}
	AgentieTurism(string nume, int nrSejururi, Sejur* sejururi)
	{
		this->nume = nume;
		this->nrSejururi = nrSejururi;
		this->sejururi = new Sejur[this->nrSejururi];
		for (int i = 0; i < nrSejururi; i++)
		{
			this->sejururi[i] = sejururi[i];
		}
	}
	AgentieTurism(const AgentieTurism& a)
	{
		this->nume = a.nume;
		this->nrSejururi = a.nrSejururi;
		this->sejururi = new Sejur[this->nrSejururi];
		for (int i = 0; i < a.nrSejururi; i++)
		{
			this->sejururi[i] = a.sejururi[i];
		}
	}
	~AgentieTurism()
	{
		if (this->sejururi != NULL)
		{
			delete[] this->sejururi;
		}
	}
	AgentieTurism& operator=(const AgentieTurism& a)
	{
		if (this != &a)
		{
			if (this->sejururi != NULL)
			{
				delete[] this->sejururi;
			}
			this->nume = a.nume;
			this->nrSejururi = a.nrSejururi;
			this->sejururi = new Sejur[this->nrSejururi];
			for (int i = 0; i < a.nrSejururi; i++)
			{
				this->sejururi[i] = a.sejururi[i];
			}
		}
		return *this;
	}
	friend ostream& operator <<(ostream& out, const AgentieTurism& a)
	{
		out << a.nume << endl;
		out << a.nrSejururi << endl;
		out << "--------------------" << endl;
		for (int i = 0; i < a.nrSejururi; i++)
		{
			out << a.sejururi[i] << endl;
		}
		out << "--------------------" << endl;
		return out;
	}
	void adaugaSejur(Sejur s)
	{
		AgentieTurism copie = *this;
		if (this->sejururi != NULL)
		{
			delete[] this->sejururi;
		}
		this->nrSejururi++;
		this->sejururi = new Sejur[this->nrSejururi];
		for (int i = 0; i < copie.nrSejururi; i++)
		{
			this->sejururi[i] = copie.sejururi[i];
		}
		this->sejururi[this->nrSejururi - 1] = s;
	}
};
template<typename T>
void afisare(T obj)
{
	cout << obj << endl;
}

int main()
{
	Sejur s;
	cout << s.getPret() << endl;
	s.setPret(500);
	s.setPret(55);
	cout << s.getPret() << endl;

	cout << endl << endl << endl;
	int varsta[] = { 44, 11,22, 18, 16, 43, 21 };
	Sejur s1(21, "Poiana Brasov", 4, 3, varsta, 700);
	cout << s1.getPret() << endl;
	cout << s1.getNrPersoane() << endl;
	for (int i = 0; i < s1.getNrPersoane(); i++)
	{
		cout << s1.getVarstaPersoane()[i] << " ani, ";
	}
	cout << endl;
	s1.setPret(800);
	s1.setVarstaPersoane(5, varsta);
	cout << s1.getNrPersoane() << endl;
	for (int i = 0; i < s1.getNrPersoane(); i++)
	{
		cout << s1.getVarstaPersoane()[i] << " ani, ";
	}
	cout << endl;
	Sejur s2 = 1000 + s1;
	cout << s2.getPret() << endl;
	cout << endl << endl;
	cout << s1[1] << endl;
	s1[1] = 66;
	cout << s1.getNrPersoane() << endl;
	for (int i = 0; i < s1.getNrPersoane(); i++)
	{
		cout << s1.getVarstaPersoane()[i] << " ani, ";
	}

	//testare citire//scriere fisiere

	cout << endl << endl;
	s1.serializare("ex.bin");
	Sejur s3;
	cout << s3 << endl;
	s3.deserializare("ex.bin");
	cout << s3 << endl;
	cout << endl << endl << endl;

	Sejur s4(121, "Valencia", 6, 2, varsta, 3700);
	AgentieTurism a;
	cout << a << endl;

	Sejur vectSejur[] = { s, s1, s2, s3 };
	AgentieTurism a1("ExPoo Travel", 3, vectSejur);
	cout << a1 << endl;

	AgentieTurism a2(a);
	cout << a2 << endl;

	a2 = a1;
	cout << a2 << endl;

	cout << endl << endl << endl << endl;
	a2.adaugaSejur(s4);
	cout << a2 << endl;

	cout << endl << endl;
	afisare(44);
	afisare("Materie");
	cout << endl << endl;
	afisare(s4);
	cout << endl << endl;
	afisare(a2);
}