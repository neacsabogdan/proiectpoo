#pragma once
#include <iostream>
#include <string>
using namespace std;

class coloana
{
private:
	char* numecol;
	string tipcol;
	int dim;
	string val_implicita;
public:
	coloana() 
	{
		numecol = nullptr;
		tipcol = "";
		dim = 0;
		val_implicita = "";
	}
	coloana(char* numecol) :coloana() 
	{
		this->numecol = numecol;
	}
	coloana(char* numecol, string tipcol) :coloana() 
	{
		this->numecol = numecol;
		this->tipcol = tipcol;
	}
	coloana(const coloana& c)
	{
		if (c.numecol != nullptr && strlen(c.numecol) > 0) 
		{
			numecol = new char[strlen(c.numecol)+1];
			strcpy_s(numecol, strlen(c.numecol) + 1, c.numecol);
		}
		else 
		{
			numecol = nullptr;
		}
		tipcol = c.tipcol;
		dim = c.dim;
		val_implicita = c.val_implicita;
	}

	coloana& operator=(const coloana& c)
	{
		if (numecol != nullptr) 
		{
			delete[] numecol;
		}
		if (c.numecol != nullptr && strlen(c.numecol) > 0) 
		{
			numecol = new char[strlen(c.numecol) + 1];
			strcpy_s(numecol, strlen(c.numecol) + 1, c.numecol);
		}
		tipcol = c.tipcol;
		dim = c.dim;
		val_implicita = c.val_implicita;
		return *this;
	}

	~coloana()
	{
		if (numecol != nullptr) 
		{
			delete[] numecol;
		}
	}

	coloana operator+(int val)
	{
		if (val > 0)
		{
			coloana copy = *this;
			copy.dim += val;
			return copy;
		}
		else
		{
			throw 22;
		}
	}

	coloana operator++()
	{
		dim++;
		return *this;
	}

	coloana operator++(int i)
	{
		coloana copy = *this;
		dim++;
		return copy;
	}

	char& operator[](int index)
	{
		if (index >= 0 && index < strlen(numecol))
		{
			return numecol[index];
		}
		else
		{
			throw exception("Index invalid");
		}
	}
	explicit operator int()
	{
		return dim;
	}

	bool operator!()
	{
		return dim > 0;
	}

	bool operator<(coloana c)
	{
		return this->dim < c.dim;
	}

	bool operator==(coloana c)
	{
		if (this->numecol == c.numecol && this->tipcol == c.tipcol && 
			this->dim == c.dim && this->val_implicita == c.val_implicita)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	char* getnumecol()
	{
		if (numecol != nullptr) 
		{
			char* copie = new char[strlen(numecol)+1];
			strcpy_s(copie, strlen(numecol) + 1, numecol);
			return copie;
		}
		else 
		{
			return nullptr;
		}
	}
	void setnumecol(char* numecol)
	{
		if (numecol != nullptr) 
		{
			if (this->numecol != nullptr) 
			{
				delete[] this->numecol;
			}
			this->numecol = new char[strlen(numecol) + 1];
			strcpy_s(this->numecol, strlen(numecol) + 1, numecol);
		}
	}
	string gettipcol()
	{
		return tipcol;
	}
	void settipcol(string tipcol)
	{
		this->tipcol = tipcol;
	}
	int getdim()
	{
		return dim;
	}
	void setdim(int dim)
	{
		this->dim = dim;
	}
	string getvalimplicita()
	{
		return val_implicita;
	}
	void setvalimplicita(string val_implicita)
	{
		this->val_implicita = val_implicita;
	}

	friend ostream& operator<<(ostream&, coloana);
	friend istream& operator>>(istream&, coloana&);
};

ostream& operator<<(ostream& out, coloana c)
{
	out << "Nume coloana: ";
	if (c.numecol != nullptr) 
	{
		out << c.numecol;
	}
	out << endl;
	out << "Tip coloana: " << c.tipcol << endl;
	out << "Dimensiune coloana: " << c.dim << endl;
	out << "Valoare implicita: " << c.val_implicita;
	return out;
}

istream& operator>>(istream& in, coloana& c)
{
	char buffer[100];
	cout << "Nume coloana: ";
	in >> ws;
	in.getline(buffer, 99);
	if (c.numecol != nullptr) 
	{
		delete[] c.numecol;
	}
	c.numecol = new char[strlen(buffer) + 1];
	strcpy_s(c.numecol, strlen(buffer) + 1, buffer);
	cout << "Tip coloana: ";
	in >> c.tipcol;
	cout << "Dimensiune coloana = ";
	in >> c.dim;
	cout << "Valoare implicita = ";
	in >> c.val_implicita;
	return in;
}

coloana operator+(int val, coloana c)
{
	int z = c.getdim();
	z += val;
	c.setdim(z);
	return c;
}
class tabela
{
private:
	string numetab;
	int nrcol;
	coloana* col;
	static string bazadeprov;
public:
	tabela()
	{
		numetab = "";
		nrcol = 0;
		col = nullptr;
	}

	tabela(string numetab) :tabela()
	{
		this->numetab = numetab;
	}

	tabela(string numetab, int nrcol) :tabela()
	{
		this->numetab = numetab;
		this->nrcol = nrcol;
	}

	tabela(tabela& t)
	{
		numetab = t.numetab;
		if (t.nrcol > 0 && t.col != nullptr)
		{
			nrcol = t.nrcol;
			col = new coloana[t.nrcol];
			for (int i = 0; i < t.nrcol; i++)
			{
				col[i] = t.col[i];
			}
		}
		else
		{
			nrcol = 0;
			col = nullptr;
		}
	}

	tabela& operator=(const tabela& t)
	{
		if (col != nullptr)
		{
			delete[] col;
		}
		numetab = t.numetab;
		if (t.nrcol > 0 && t.col != nullptr)
		{
			nrcol = t.nrcol;
			col = new coloana[t.nrcol];
			for (int i = 0; i < t.nrcol; i++)
			{
				col[i] = t.col[i];
			}
		}
		else
		{
			nrcol = 0;
			col = nullptr;
		}
		return *this;
	}

	~tabela()
	{
		if (col != nullptr)
		{
			delete[] col;
		}
	}

	tabela operator+(int val)
	{
		if (val > 0)
		{
			tabela copy = *this;
			copy.nrcol += val;
			return copy;
		}
		else
		{
			throw 22;
		}
	}

	tabela operator++()
	{
		nrcol++;
		return *this;
	}

	tabela operator++(int i)
	{
		tabela copy = *this;
		nrcol++;
		return copy;
	}

	coloana& operator[](int index)
	{
		if (index >= 0 && index < nrcol)
		{
			return col[index];
		}
		else
		{
			throw exception("Index invalid");
		}
	}
	explicit operator int()
	{
		return nrcol;
	}

	bool operator!()
	{
		return nrcol > 0;
	}

	bool operator<(tabela t)
	{
		return this->nrcol < t.nrcol;
	}

	bool operator==(tabela t)
	{
		if (this->nrcol == t.nrcol && this->numetab == t.numetab && this->col == t.col)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	string getnumetab()
	{
		return numetab;
	}
	void setnumetab(string numetab)
	{
		this->numetab = numetab;
	}
	int getnrcol()
	{
		return nrcol;
	}
	void setnrcol(int nrcol)
	{
		this->nrcol = nrcol;
	}
	static string getbazadeprov()
	{
		return bazadeprov;
	}
	static void setbazadeprov(string bazadeprov)
	{
		tabela::bazadeprov = bazadeprov;
	}
	void setcol(char* numecol, string tipcol, int dim, string val_implicita) 
	{
		col->setnumecol(numecol);
		col->settipcol(tipcol);
		col->setdim(dim);
		col->setvalimplicita(val_implicita);
	}
	friend coloana;
	friend ostream& operator<<(ostream&, tabela);
	friend istream& operator>>(istream&, tabela&);
};

string tabela::bazadeprov = "Baza de date";

ostream& operator<<(ostream& out, tabela t)
{
	out << "Nume tabela: " << t.numetab << endl;
	out << "Nr coloane: " << t.nrcol << endl;
	out << "Coloane: ";
	if (t.col != nullptr)
	{
		out << t.col;
	}
	return out;
}

istream& operator>>(istream& in, tabela& t)
{
	cout << "Nume tabela = ";
	in >> ws;
	getline(in, t.numetab);
	cout << "Nr coloane = ";
	in >> t.nrcol;
	if (t.col != nullptr)
	{
		delete[] t.col;
	}
	if (t.nrcol > 0)
	{
		t.col = new coloana[t.nrcol];
		for (int i = 0; i < t.nrcol; i++)
		{
			cout << "Coloana[" << i << "] = ";
			in >> t.col[i];
		}
	}
	else
	{
		t.nrcol = 0;
		t.col = nullptr;
	}
	return in;
}

tabela operator+(int val, tabela t)
{
	int z = t.getnrcol();
	z += val;
	t.setnrcol(z);
	return t;
}

class bazadedate 
{
private:
	tabela* tabele;
	int nrtab;
	const char* numebaz;
public:

	bazadedate():numebaz("Baza de date")
	{
		nrtab = 0;
		tabele = nullptr;
	}
	bazadedate(int nrtab):numebaz("Baza de date")
	{
		this->nrtab = nrtab;
		tabele = nullptr;
	}
	bazadedate(int nrtab, tabela* tabele,char* numebaz):numebaz(numebaz)
	{
		this->nrtab = nrtab;
		if (nrtab > 0) 
		{
			this->tabele = new tabela[nrtab];
			for (int i = 0; i < nrtab; i++) 
			{
				this->tabele[i] = tabele[i];
			}
		}
		else 
		{
			this->tabele = nullptr;
		}
	}
	bazadedate(bazadedate& b):numebaz(b.numebaz)
	{
		nrtab = b.nrtab;
		if (b.nrtab > 0 && b.tabele != nullptr) 
		{
			tabele = new tabela[b.nrtab];
			for (int i = 0; i < b.nrtab; i++)
			{
				tabele[i] = b.tabele[i];
			}
		}
		else 
		{
			tabele = nullptr;
		}
	}
	bazadedate& operator=(const bazadedate& b) 
	{
		if (tabele != nullptr) 
		{
			delete[] tabele;
		}
		nrtab = b.nrtab;
		if (b.nrtab > 0 && b.tabele != nullptr)
		{
			tabele = new tabela[b.nrtab];
			for (int i = 0; i < b.nrtab; i++)
			{
				tabele[i] = b.tabele[i];
			}
		}
		else
		{
			tabele = nullptr;
		}
		return *this;
	}
	~bazadedate()
	{
		if (tabele != nullptr) 
		{
			delete[] tabele;
		}
	}
	bazadedate operator+(int val) 
	{
		if (val > 0) 
		{
			bazadedate copy = *this;
			copy.nrtab += val;
			return copy;
		}
		else 
		{
			throw 22;
		}
	}

	bazadedate operator++() 
	{
		nrtab++;
		return *this;
	}

	bazadedate operator++(int i) 
	{
		bazadedate copy = *this;
		nrtab++;
		return copy;
	}
	
	tabela& operator[](int index) 
	{
		if (index >= 0 && index < nrtab) 
		{
			return tabele[index];
		}
		else 
		{
			throw exception("Index invalid");
		}
	}
	explicit operator int() 
	{
		return nrtab;
	}

	bool operator!()
	{
		return nrtab > 0;
	}

	bool operator>(bazadedate b) 
	{
		return this->nrtab > b.nrtab;
	}
	
	bool operator==(bazadedate b) 
	{
		if (this->nrtab == b.nrtab && this->tabele == b.tabele && this->numebaz == b.numebaz) 
		{
			return true;
		}
		else 
		{
			return false;
		}
	}
	int getnrtab() 
	{
		return nrtab;
	}
	void setnrtab(int nrtab) 
	{
		if (nrtab > 0) 
		{
			nrtab = nrtab;
		}
	}
	string getnumebaz() 
	{
		return string(numebaz);
	}

	void create(char* numetab, int nrcol,coloana* c)
	{
		if (tabele != nullptr)
		{
			tabela* aux = new tabela[nrtab];
			for (int i = 0; i < nrtab - 1; i++)
			{
				aux[i] = tabele[i];
			}
			delete[] tabele;
			nrtab += 1;
			tabele = new tabela[nrtab];
			for (int i = 0; i < nrtab - 1; i++)
			{
				tabele[i] = aux[i];
			}
			tabele[nrtab].setnumetab(numetab);
			tabele[nrtab].setnrcol(nrcol);
			for (int i = 0; i < nrcol; i++)
			{
				tabele[nrtab].setcol(c[i].getnumecol(), c[i].gettipcol(), c[i].getdim(), c[i].getvalimplicita());
			}
			delete[] aux;
		}
		else
		{
			tabele = new tabela[nrtab];
			tabele[nrtab].setnumetab(numetab);
			tabele[nrtab].setnrcol(nrcol);
			for (int i = 0; i < nrcol; i++)
			{
				tabele[nrtab].setcol(c[i].getnumecol(), c[i].gettipcol(), c[i].getdim(), c[i].getvalimplicita());
			}
		}
	}

	void drop(string nume) 
	{
	int k = 0;
		for (int i = 0; i < this->nrtab; i++)
			{
			if (tabele[i].getnumetab() == nume) 
			{
				k = 1;
			}
			}
		if (k = 1)
		{
			if (nrtab == 1)
			{
				delete[] tabele;
			}
			else
			{
				tabela* aux = new tabela[nrtab - 1];
				for (int i = 0; i < nrtab - 1; i++)
				{
					if (tabele[i].getnumetab() != nume)
					{
						for (int j = 0; j < nrtab - 1; j++) 
						{
							aux[j] = tabele[i];
						}
					}
				}
			delete[] tabele;
			nrtab -= 1;
			tabele = new tabela[nrtab];
			for (int i = 0; i < nrtab; i++)
			{
				tabele[i] = aux[i];
			}
			delete[] aux;
			}
			cout << endl << "Tabela " << nume << " a fost stearsa";
		}
		else
		{
			cout << "Tabela cu numele " << nume << " nu exista";
		}
	}

	void display(string nume)
	{
		int k = 0;
		for (int i = 0; i < this->nrtab; i++)
		{
			if (tabele[i].getnumetab() == nume) 
			{
				k = 1;
			}
		}
		if (k = 1)
		{
			for (int i = 0; i < this->nrtab; i++)
			{
				if (tabele[i].getnumetab() == nume)
				{
					cout << tabele[i];
				}
			}
		}
		else cout << "Tabela cu numele " << nume << " nu exista";
	}
	friend class coloana;
	friend ostream& operator<<(ostream&, bazadedate);
	friend istream& operator>>(istream&, bazadedate&);
};


ostream& operator<<(ostream& out, bazadedate b) 
{
	out << "Numar tabele: " << b.nrtab << endl;
	out << "Tabele: ";
	if (b.tabele != nullptr) 
	{
		out << b.tabele;
	}
	out << endl;
	out << "Nume baza de date: " << b.numebaz;
	return out;
}

istream& operator>>(istream& in, bazadedate& b) 
{
	cout << "Numar tabele = ";
	in >> b.nrtab;
	cout << "Tabele:";
	if (b.tabele != nullptr) 
	{
		delete[] b.tabele;
	}
	if (b.nrtab > 0) 
	{
		b.tabele = new tabela[b.nrtab];
		for (int i = 0; i < b.nrtab; i++) 
		{
			cout << "Tabela[" << i << "] = ";
			in >> b.tabele[i];
		}
	}
	else 
	{
		b.nrtab = 0;
		b.tabele = nullptr;
	}
	return in;
}

bazadedate operator+(int val, bazadedate b) 
{
	int z = b.getnrtab();
	z += val;
	b.setnrtab(z);
	return b;
}
