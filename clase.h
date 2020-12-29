#pragma once
#include <iostream>
#include <string>
using namespace std;

class coloana
{
private:
	string numecol;
	string tipcol;
	string dim;
	string val_implicita;
};

class tabela 
{
private:
	string numetab;
	int nrcol;
	coloana* col;
};

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
};
