#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include<iomanip>
#include "merge.h"
#include "quick.h"
#include "introspective.h"

using namespace std;

void MENU(){

cout<<"Ładowanie..."<<endl;

	Merge M;
	Quick Q;
	Introspective I;
	system("clear");
	
	int roz;
	int wybor;
	cout<<"Wybierz rozmiar tablicy: \n1. 10000 \n2. 50000 \n3. 100000 \n4. 50000 \n5. 1000000"<<endl;
	cout<<"Wybor: ";
	cin>>wybor;
	cout<<endl;

	const int wybor1 = wybor;
	switch(wybor1){

		case 1: roz = 10000; 
		break;
		case 2: roz = 50000; 
		break;
		case 3: roz = 100000; 
		break;
		case 4: roz = 500000; 
		break;
		case 5: roz = 1000000; 
		break;
	}
	static const int rozmiar = roz;
	

	int ** tab = new int*[100];
	for(int i=0;i<100;++i)
		tab[i] = new int[rozmiar];


	

	int low = 0;
	int high = rozmiar-1;
	cout<<"Przypadki sortowania: \n1. Wszystkie elementy tablicy losowe \n2. 25% poczatkowych elementow posortowanych \n3. 50% poczatkowych elementow posortowanych \n4. 75% poczatkowych elementow posortowanych \n5. 95% poczatkowych elementow posortowanych \n6. 99% poczatkowych elementow posortowanych \n7. 99,7% poczatkowych elementow posortowanych \n8. Posortowane w odwrotnej kolejnosci \nWybor: ";

	cin>>wybor;
	
	const int wybor2 = wybor;

	float proc;
	
	switch(wybor2){
	case 1:
		proc = 0;
	break;

	case 2:
		proc = 0.25;
	break;

	case 3:
		proc = 0.5;
	break;

	case 4:
		proc = 0.75;
	break;

	case 5:
		proc = 0.95;
	break;

	case 6:
		proc = 0.99;
	break;

	case 7:
		proc = 0.997;
	break;

	case 8:
		proc = 1;
	break;

	}

	for(int j=0;j<100;++j)
		for(int i=0;i<rozmiar;++i){
			if(proc==1)
				tab[j][i]=rozmiar-i; // wypelnianie tablicy od tylu 
			else if(i<rozmiar*proc)
				tab[j][i]=i;
			else
				tab[j][i]=(rand() % rozmiar) + 1;  // MNIEJ WIECEJ LOSOWE
		}

	int nr_sortowania;

	cout<<"Wybierz rodaj sortowania: \n1.Sortowanie przez scalanie \n2.Quicksort \n3.Introsort"<<endl;
	cout<<"Wybor: ";
	cin>>nr_sortowania;


	switch(nr_sortowania){

		case 1:	
		for(int j=0;j<100;++j){
			int * c = new int[100000000];
			clock_t begin = clock();
			M.SortowaniePubliczne<int>(tab[j], low, high, c);
			clock_t end = clock();

			double CzasAlgorytmu = double(end - begin) / CLOCKS_PER_SEC;
			cout<< "Czas wykonywania algorytmu: " <<CzasAlgorytmu<< " s" << endl;
			delete [] c;
		}
		break;

		case 2:
		for(int j=0;j<100;++j){
		
			clock_t begin = clock();
			Q.SortowanieQuicksort<int>(tab[j], low, high);
			clock_t end = clock();
		
			double CzasAlgorytmu = double(end - begin) / CLOCKS_PER_SEC;
			
			cout<< "Czas wykonywania algorytmu quicksort: " <<CzasAlgorytmu<< " s" << endl;
		}
		break;

		case 3:
		for(int j=0;j<100;++j){
			clock_t begin = clock();
			//I.Introsort<int>(tab[0], low, high);
			I.HybridIntrospectiveSort(tab[j], high+1);
			clock_t end = clock();
		
			double CzasAlgorytmu = double(end - begin) / CLOCKS_PER_SEC;
			
			cout<< "Czas wykonywania algorytmu introsort: " <<setprecision(3)<<CzasAlgorytmu<< " s" << endl;
		}
		break;


	}
	delete [] tab;
	/*for(int i=0;i<rozmiar;++i)
		cout<<tab[i][j]<<" ";
	cout<<endl<<endl;*/
return;

}


bool Check(int tab[], int rozmiar){ //Sprawdza czy wyraz poprzedni jest mniejszy od nastepnego

	for (int i = 0; i < rozmiar-1; ++i)
		{
			if(tab[i]>tab[i+1]){ 
				return 1;
			}
		}

	return 0;
}

double Czas(int *tab[], int rozmiar, int k){ //Wykonuje polecenie sortowania i zwraca sredni czas algorytmu oraz wywoluje poleceie sprawdzenia sortowania, tutaj k to 1.2.3

	Merge M;
	Quick Q;
	Introspective I;

	int low = 0;
	int high = rozmiar-1;
	double elapsed_secs = 0;

	if(k==0){
		for(int j=0;j<100;++j){
			
			int * c = new int[100000000]; // tworzenie tablicy pomocniczej
			
			clock_t begin = clock();  //rozpoczecie odliczania
			M.SortowaniePubliczne<int>(tab[j], low, high, c); 
			clock_t end = clock();
			
			delete [] c;

			elapsed_secs += double(end - begin) / CLOCKS_PER_SEC;
		}
			cout<< "Czas wykonywania algorytmu merge("<<high<<"): " <<elapsed_secs/100<< " s" << endl;
			for(int j=0;j<100;++j)
			if(Check(tab[j],rozmiar)==1) {cout<<"Nie dziala"<<endl; return 1;}
			return elapsed_secs/100;
		
	}

	if (k==1)
	{
		
		for(int j=0;j<100;++j){
		
		clock_t begin = clock();
		Q.SortowanieQuicksort<int>(tab[j], low, high);
		clock_t end = clock();
	
		elapsed_secs += double(end - begin) / CLOCKS_PER_SEC;
	}	
		cout<< "Czas wykonywania algorytmu quicksort: " <<elapsed_secs/100<< " s" << endl;
		for(int j=0;j<100;++j)
		if(Check(tab[j],rozmiar)==1) {cout<<"Nie dziala"<<endl; return 1;}
		return elapsed_secs/100;
		
	}

	if (k==2)
	{
	for(int j=0;j<100;++j){
		clock_t begin = clock();
		//I.Introsort<int>(tab[0], low, high);
		I.HybridIntrospectiveSort(tab[j], high+1);
		clock_t end = clock();
	
		elapsed_secs += double(end - begin) / CLOCKS_PER_SEC;
	}
		cout<< "Czas wykonywania algorytmu introsort: " <<elapsed_secs/100<< " s" << endl;
		for(int j=0;j<100;++j)
		if(Check(tab[j],rozmiar)==1) {cout<<"Nie dziala"<<endl; return 1;}
		return elapsed_secs/100;
		
	}
	return 0;
}

template <class T>
T **FarykaTablic(int n, float m){ // tworzenie tablic dwuwymiarowych dynamicznych 

    int **tab_main = new int*[100];
    for(int q = 0 ; q < 100 ; ++q){
        tab_main[q] = new int[n];
    }

    for(int j = 0 ; j < 100 ; ++j)
       	for(int i=0 ; i<n ; ++i){
            if(m==1)
				tab_main[j][i]=n-i;
			else if(i<n*m)
				tab_main[j][i]=i;
			else
				tab_main[j][i]=(rand() % n) + 1;  // MNIEJ WIECEJ LOSOWE
        }
    
    return tab_main;
}

void BezMENU(){

	ofstream file_m, file_q, file_i;
	file_m.open("czasy sortowania merge.txt");
	file_q.open("czasy sortowania quick.txt");
	file_i.open("czasy sortowania intro.txt");

	double czasy[3][40]; //3x rodzaje sortowania , 40x warianty(rozmiary i posortowanie poczatkowe)
	int k=0; //numer wariantu z 40
	int rozmiar[5] = {10000, 50000, 100000, 500000, 1000000};
	float poziom[8] = {0, 0.25, 0.5, 0.75, 0.95, 0.99, 0.997, 1};
	int **tab_m, **tab_q, **tab_i; // tworzenie "tymczasowych" tablic, do ktorych bede przypisane wypelnione tablice z funkcji FabrykaTablic

	for(int i = 0 ; i < 8 ; i++)
        for(int j = 0 ; j < 5 ; j++){

        	tab_m = FarykaTablic<int>(rozmiar[j],poziom[i]); //wysylam do funkcji FabrykaTablic rozmiar i poziom sortowania, a ta funkcja przypisuje jej gotowa tablice

		    czasy[0][k]=Czas(tab_m,rozmiar[j],0); //wywolanie funkcji czas, ktora wykonuje polecenia sortowania i mierzy sredni czas ich wykonywania w zaleznosci od parametru k

		    if(czasy[0][k]==1) return; //Jesli funkcja Czas zostanie blednie posortowana to zwroci wartosc 1
		    for(int i = 0; i < 100; ++i)
    			delete [] tab_m[i];
		    delete[] tab_m;
		    
        	tab_q = FarykaTablic<int>(rozmiar[j],poziom[i]); //To samo co wyzej ale dla innych sortowann
		    czasy[1][k]=Czas(tab_q,rozmiar[j],1);
		    for(int i = 0; i < 100; ++i)
    			delete [] tab_q[i];
		    delete[] tab_q;

		    tab_i = FarykaTablic<int>(rozmiar[j],poziom[i]);
		    czasy[2][k]=Czas(tab_i,rozmiar[j],2);
		    for(int i = 0; i < 100; ++i)
    			delete [] tab_i[i];
		    delete[] tab_i;

		    k++;
        }

    for (int i = 0; i < 3; ++i) //zapis do plikow
    {
    	for (int j = 0; j < 40; ++j)
    		if (i==0) file_m << czasy[i][j] << ";\n";
    	for (int j = 0; j < 40; ++j)
    		if (i==1) file_q << czasy[i][j] << ";\n";
    	for (int j = 0; j < 40; ++j)
    		if (i==2) file_i << czasy[i][j] << ";\n";
    }
    file_m.close();
    file_q.close();
    file_i.close();

}

int main(){
	system("clear");
	cout<<"Wybierz wariant: \n1.Menu \n2.Bez Menu"<<endl;

	int wybor;
	cin >> wybor;

	switch(wybor){

		case 1:
		MENU();
		break;

		case 2:
		BezMENU();
		break;
	}

	
return 0;
}