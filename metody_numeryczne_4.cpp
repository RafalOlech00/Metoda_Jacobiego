#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;


void ShowTab(float** Tab, int size)  // funkcja do wypisywania macierzy rozszerzonej
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < (size + 1); j++)
		{
			cout << Tab[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void ShowTab2(float** Tab, int size)  // funkcja do wypisywania macierzy 
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < (size); j++)
		{
			cout << Tab[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
int main()
{
	// odczytanie z pliku tekstowego danych 
	fstream read;
	int size = 0;
	read.open("RURL_2.txt"); // otwarcie pliku tekstowego
	read >> size; // rozmiar macierzy

	float x,z;

	float** Tab = new float* [size]; // przygotowana tablica dla macierzy rozszerzonej

	for (int i = 0; i < size; i++)
	{
		Tab[i] = new float[size + 1];
	}

	// wczytanie wartości do tablicy - macierz rozszerzona
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < (size + 1); j++)
		{
			read >> x;
			Tab[i][j] = x;
		}
	}
	
	read.close(); // zamknięcie pliku tekstowego

	float** TabToCalc = new float* [size]; // macierz do obliczeń - podstawowa macierz bez kolumny z wynikami

	for (int i = 0; i < size; i++)
	{
		TabToCalc[i] = new float[size];
	}


	for (int i = 0; i < size; i++) // przepisanie wartości z macierzy rozszerzonej do tablicy TabToCalc (bez ostatniej kolumny)
	{
		for (int j = 0; j < size; j++)
		{
			TabToCalc[i][j] = Tab[i][j]; 
		}
	}

	float** Tab_D = new float* [size]; // przygotowana tablica dla macierzy diagonalnej D
	for (int i = 0; i < size; i++)
	{
		Tab_D[i] = new float[size];
	}

	

	float** Tab_L = new float* [size];  // przygotowana tablica dla macierzy L
	for (int i = 0; i < size; i++)
	{
		Tab_L[i] = new float[size];
	}

	float** Tab_U = new float* [size];  // przygotowana tablica dla macierzy U
	for (int i = 0; i < size; i++)
	{
		Tab_U[i] = new float[size];
	}

	float** Tab_LU = new float* [size];  // przygotowana tablica dla macierzy L+U
	for (int i = 0; i < size; i++)
	{
		Tab_LU[i] = new float[size];
	}

	for (int i = 0; i < size; i++) // wypełnienie tablic D, L, U, LU zarami
	{
		for (int j = 0; j < size; j++)
		{
			Tab_D[i][j] = 0;
			Tab_L[i][j] = 0;
			Tab_U[i][j] = 0;
			Tab_LU[i][j] = 0;
		}
	}
	
	// Rozdzielenie macierzy rozszerzonej na macierz D, L, U
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (j == i)  // warunek określający indeksy diagonali
			{
				// uzupełniane są macierze D, L, U
				Tab_D[i][j] = TabToCalc[i][j];
			}
			
			else if( i > j) // elementy pod przekątną 
			{
				Tab_L[i][j] = TabToCalc[i][j];
			}
			else if(i < j) // elementy nad przekątną
			{
				Tab_U[i][j] = TabToCalc[i][j];
			}
			
		}
	}

	// wpisanie wartości do tablicy LU z dwóch tablic: L, U
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (i > j) // elementy pod przekątną   
			{
				Tab_LU[i][j] = Tab_L[i][j];
			}

			else if (i < j)// elementy nad przekątną
			{
				Tab_LU[i][j] = Tab_U[i][j];

			}
			else
			{
				Tab_LU[i][j] = 0;

			}
			
		}
	}

	float** Tab_D_Odwr = new float* [size]; // przygotowana tablica dla macierzy odwrotnej D
	for (int i = 0; i < size; i++)
	{
		Tab_D_Odwr[i] = new float[size];
	}


	for (int i = 0; i < size; i++) // wpisanie wartości do macierzy odwróconej D
	{
		for (int j = 0; j < size; j++)
		{
			if (i == j)
			{
				Tab_D_Odwr[i][j] = 1 / Tab_D[i][j];
			}
			else
			{
				Tab_D_Odwr[i][j] = 0;
			}
		}
	}


	// Wypisanie macierzy rozszerzonej przed obliczeniami 
	cout << "Macierz rozszerzona przed obliczeniami:" << endl;
	ShowTab(Tab, size);

	// Wypisanie macierzy do obliczeń bez kolumny z wynikamu przed obliczeniami 
	//cout << "Macierz podstawowa do obliczen (bez kolumny z wynikami) przed obliczeniami:" << endl;
	//ShowTab2(TabToCalc, size);


	// Wypisanie macierzy D, L, U, LU
	//cout << "Macierz L:" << endl;
	//ShowTab2(Tab_L, size);
	//cout << "Macierz diagonalna D:" << endl;
	//ShowTab2(Tab_D, size);
	//cout << "Macierz U :" << endl;
	//ShowTab2(Tab_U, size);
	/*cout << "Macierz LU :" << endl;
	ShowTab2(Tab_LU, size);*/


	float k; 
	float suma; 
	float m;
	// warunki macierzy diagonalnie słabo dominującej 
	for (int i = 0; i < size; i++)
	{
		k = Tab[i][i];
		suma = 0;
		m = 0;
		for (int j = 0; j < size; j++)
		{
			if (j == i) // na przekątnej macierzy
			{
				continue;
			}
			suma += Tab[i][j];
			if (k > Tab[i][j])
			{
				m = 1;
			}
		}
		if (k < suma || m == 0)
		{
			cout << "Macierz ta nie jest macierza diagonalnie slabo dominujaca" << endl;
			return 0;
		}
	}



	//cout << "Podaj ilosc iteracji" << endl;
	int il_it;
	//cin >> il_it;

	
	 il_it = 100;// ustalona maksymalna liczba iteracji do zadania 2

	float** ResultTab = new float* [size]; // stworzenie tablicy wynikowej

	for (int i = 0; i < 2; i++)
	{
		ResultTab[i] = new float[size];
	}

	for (int j = 0; j < size; j++)
	{
		ResultTab[0][j] = 0;
	}

	float blad = 0.0001f;
	float l; 
	float n;
	float p;

	for (int k = 0; k < il_it; k++)
	{
		for (int i = 0; i < size; i++)
		{
			l = 0;
			for (int j = 0; j < size; j++)
			{
				l += -Tab_D_Odwr[i][i] * Tab_LU[i][j] * ResultTab[0][j];
			}
			ResultTab[1][i] = l + Tab_D_Odwr[i][i] * Tab[i][size];
		}
	
		
		p =0;
		for (int i = 0; i < size; i++)
		{
			n = ResultTab[1][i] - ResultTab[0][i];

			if (abs(n) > blad)
			{
				p = 1;
			}
		}
		if (p == 0)
		{
			cout << "Blad jest mniejszy po " << k << " iteracjach" << endl;
			for (int i = 0; i < size; i++)
			{
				cout << "dla x" << i << ": ";
				cout << ResultTab[1][i] - ResultTab[0][i] << endl;
			}
			cout << endl;
			break;
		}

		for (int i = 0; i < size; i++)
		{
			ResultTab[0][i] = ResultTab[1][i];
		}

	}

	// Wypisanie macierzy rozszerzonej po obliczeniach 
	//cout << "Macierz rozszerzona po obliczeniach:" << endl;
	//ShowTab(Tab, size);

	

	
	cout << "Macierz diagonalna odwrotna:" << endl;
	ShowTab2(Tab_D_Odwr, size);

	cout << "Macierz LU :" << endl;
	ShowTab2(Tab_LU, size);

	
	cout << "Rozwiazanie po " << il_it << " iteracjach" << endl;
	for (int i = 0; i < size; i++)
	{
		cout << "x" << i << ": " << ResultTab[1][i] << " " << endl;
	}
	
}