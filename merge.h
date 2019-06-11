#ifndef MERGE_H_
#define SORTOWANIE_H_

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Merge{

	template<class T>
	void SortowaniePrywatne (T tab[], T low, T high, T mid, T c[]);

public:

	template<class T>
	void SortowaniePubliczne(T tab[], T low, T high,  T c[]);

};

template<class T>
void Merge::SortowaniePrywatne (T tab[], T low, T high, T mid, T c[])
{

int i, j, k;
   
    
    i = low;
    k = low;
    j = mid + 1;
    
    while (i <= mid && j <= high)
    {
        if (tab[i] < tab[j])
        {
            c[k++] = tab[i++];
            
        }
        else
        {
            c[k++] = tab[j++];

        }
    }
    
    while (i <= mid)
    {
        c[k++] = tab[i++];

    }
    
    while (j <= high)
    {
        c[k++] = tab[j++];

    }
    for (i = low; i < k; ++i)
    {
        tab[i] = c[i];
    }



}

template<class T>
void Merge::SortowaniePubliczne (T tab[], T low, T high, T c[]){

if(low < high){

		int mid = (low + high) / 2;
	
		SortowaniePubliczne(tab, low, mid, c);
		SortowaniePubliczne(tab, mid+1, high, c);
	
		SortowaniePrywatne(tab, low, high, mid, c);
	}
}

#endif