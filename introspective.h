#ifndef INTROSPECTIVE_H_
#define SORTOWANIE_H_

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;
class Introspective{

	template <class T>
	void IntroSort (T tab[], T high, T M);
	
	template <class T>
	T Partition (T tab[], T L, T R);
	
	template <class T>
	void MedianOfThree (T tab[], T &L, T &R);
	
	template <class T>
	void Exchange (T tab[], T i, T j);
	
	template <class T>
	void HeapSort (T tab[], T high);
	
	template <class T>
	void Heapify (T tab[], T i, T high);
	
	template <class T>
	void InsertionSort (T tab[], T high);

public:

	template <class T>
	void HybridIntrospectiveSort (T tab[], T high);

};

template <class T>
void Introspective::HybridIntrospectiveSort (T tab[], T high){ //Wywolanie Introsorta i wstawiania

  IntroSort(tab,high,(int)floor(2*log(high)/M_LN2));
  InsertionSort(tab,high);

}
 
template <class T>
void Introspective::IntroSort (T tab[], T high, T M){ //sprawdza czy jest najgorszy wariant sortowania, jesli tak to przeprowadza sortowanie przez kopcowanie HeapSort, jesli nie to przeprowadza QuickSort

  if (M<=0)
  {
    HeapSort(tab,high-1);
    return;
  }

  int mid = Partition(tab,0,high);  //dzielenie tablicy na mniejsze - rekursywnie
  
  if (mid>9)
    IntroSort(tab,mid,M-1);
  if (high-1-mid>9)
    IntroSort(tab+mid+1,high-1-mid,M-1);

}


template <class T>
T Introspective::Partition (T tab[], T low, T high){ //dzielenie tablicy na mniejsze

  int i, j;

  if (high>=3)
    MedianOfThree(tab,low,high);

  for (i=low, j=high-2; ; )
  {
    for ( ; tab[i]<tab[high-1]; ++i);
    for ( ; j>=low && tab[j]>tab[high-1]; --j);
    if (i<j)
      Exchange(tab,i++,j--);
    else break;
  }
  
  Exchange(tab,i,high-1);

  return i;

}
 
template <class T>
void Introspective::MedianOfThree (T tab[], T &L, T &H){ //wybieranie najlepszego Pivota

  if (tab[++L-1]>tab[--H])
    Exchange(tab,L-1,H);
  if (tab[L-1]>tab[H/2])
    Exchange(tab,L-1,H/2);
  if (tab[H/2]>tab[H])
    Exchange(tab,H/2,H);
  Exchange(tab,H/2,H-1);

}
 
template <class T>
void Introspective::Exchange (T tab[], T i, T j){ //zamienia pozycje tablicy

  T temp;
  temp=tab[i];
  tab[i]=tab[j];
  tab[j]=temp;

}

template<class T>
void Introspective::Heapify(T* heap, T i, T n) //Kopcowanie
{
    int left = 2*i;
    int right = 2*i+1;
    int smallest = i;
 
    if( left <= n && heap[left]<heap[i])
        smallest = left;
    if( right <= n && heap[right]<heap[smallest])
        smallest = right;
 
    if(smallest != i)
    {
        int temp = heap[smallest];
        heap[smallest] = heap[i];
        heap[i] = temp;
        Heapify(heap,smallest,n);
    }
}
 
template<class T>
void Introspective::HeapSort(T* heap,T n)
{
    for(int i=n/2;i>=1;i--)
        Heapify(heap,i,n);
}


template <class T>
void Introspective::InsertionSort (T tab[], T high){ //sortowanie przez wstawianie, wykonywane na samym koncu do uporadzadkowania tablicy

  int i, j;
  T temp;
  
  for (i=1; i<high; ++i)
  {
    temp=tab[i];
    for (j=i; j>0 && temp<tab[j-1]; --j)
      tab[j]=tab[j-1];
    tab[j]=temp;
  }

}

#endif