// Finn Nguyen
// CPSC 301-01 
// Tues-Thurs: 10-12:50pm 

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;

struct PERSON
{
	char Name[20];
	float Balance;
};

void Display(const PERSON *a, int N);
int FindRichest(const PERSON *a, int N);
void Deposit(const char CustName[], PERSON *a, int N);
void NewCopy(const char filename[], const PERSON *a, int N);


int main()
{
	
	ifstream fin;
	
	PERSON *a;
	
	int N;
	
	char first[20];
	
	char last[20];
	
	char CustName[20];
	
	float balance;
	
	int i;

	
	fin.open("data.txt");

	
	if (!fin)
	{
		
		cout << "Error: could not open file 'data.txt'" << endl;
		
		return 1;
	}

	
	N = 0;
	while (fin >> first >> last >> balance)
		N++;

	
	fin.close();
	fin.clear();

	
	fin.open("data.txt");

	
	if (!fin)
	{
		
		cout << "Error: could not open file 'data.txt'" << endl;
		
		return 1;
	}

	
	a = new PERSON[N];

	for (i = 0; i < N; i++)
	{
		fin >> first >> last >> a[i].Balance;

		strcpy(a[i].Name, first);
		strcat(a[i].Name, " ");
		strcat(a[i].Name, last);
	}

		fin.close();

	Display(a, N);

	i = FindRichest(a, N);
	cout << endl;
	cout << "The customer with maximum balance is " << a[i].Name << endl;

	cout << endl;
	cout << "Enter your full name to deposit money: ";
	cin >> first >> last;
	
	strcpy(CustName, first);
	strcat(CustName, " ");
	strcat(CustName, last);
	
	Deposit(CustName, a, N);

	NewCopy("data.txt", a, N);

	delete[] a;

	return 0;
}

void Display(const PERSON *a, int N)
{
	cout << left << setw(20) << "Name" << right << setw(10) << "Balance" << endl;
	cout << "-----------------------------------------------" << endl;

	cout << fixed << showpoint << setprecision(2);

	for (int i = 0; i < N; i++)
	{
		cout << left << setw(20) << a[i].Name << right << setw(10) << a[i].Balance << endl;
	}
}

int FindRichest(const PERSON *a, int N)
{
	int maximum = 0;

	for (int i = 1; i < N; i++)
		if (a[i].Balance > a[maximum].Balance)
			maximum = i;

	return maximum;
}

void Deposit(const char CustName[], PERSON *a, int N)
{
	for (int i = 0; i < N; i++)
	{
		if (strcmp(a[i].Name, CustName) == 0)
		{
			float amount;

			cout << CustName << ", how much would you like to deposit? ";
			cin >> amount;

			if (amount > 0)
			{
				a[i].Balance += amount;

				cout << "Now your new balance is " << a[i].Balance << endl;
			}
			else
			{
				cout << "Error: amount must be positive" << endl;
			}

			return;
		}
	}

	cout << "Error: no such customer" << endl;
}

void NewCopy(const char filename[], const PERSON *a, int N)
{
	ofstream fout;

	fout.open(filename);

	if (!fout)
	{
		cout << "Error: could not open file '" << filename << "'" << endl;
		return;
	}

	fout << fixed << showpoint << setprecision(2);

	for (int i = 0; i < N; i++)
		fout << a[i].Name << " " << a[i].Balance << endl;

	fout.close();
}
