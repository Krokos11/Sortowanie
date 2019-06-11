#ifndef QUICK_H_
#define SORTOWANIE_H_

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Quick{

	template<class T>
	T Podzial(T tab[], T low, T high);

	template<class T>
	void Zamiana(T tab[], T i, T j);

public:

	template<class T>
	void SortowanieQuicksort(T tab[],  T low, T high);


};

template<class T>
T Quick::Podzial(T tab[], T low, T high){

	int mid_index = low + (high - low)/2; // element do Podzialu tablicy
	int mid_value = tab[mid_index];

	Zamiana(tab, mid_index, high); //przeniesienie elementu na koniec tablicy

	int aktualna_pozycja = low;

	for(int i=low; i < high; ++i){
		if(tab[i]<mid_value){
			Zamiana(tab,i,aktualna_pozycja);
			++aktualna_pozycja;
		}
	}
	Zamiana(tab,aktualna_pozycja,high);

	return(aktualna_pozycja);

}
template<class T>
void Quick::Zamiana(T tab[], T i, T j){

	T temp;
 	temp=tab[i];
 	tab[i]=tab[j];
 	tab[j]=temp;

}

template<class T>
void Quick::SortowanieQuicksort(T tab[],  T low, T high){ //dzielenie tablicy na czesci

	while(low < high){
		
		int mid = Podzial(tab, low, high); //dzielenie, punkt podzialu
	
	if( (mid-low) <= (high-mid)){
		SortowanieQuicksort(tab, low, mid); //lewa czesc
		low = mid+1;
	}
	else{
		SortowanieQuicksort(tab, mid+1, high); //prawa czesc
		high = mid-1;
	}
	
	}
	return;
}
	

#endif