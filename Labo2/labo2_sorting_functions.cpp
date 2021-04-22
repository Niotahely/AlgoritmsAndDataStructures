#include "labo2_sort.h"


void scambia(vector<int>& v, int i, int j)
{ 
  int tmp = v[j];
  v[j] = v[i];
  v[i] = tmp;
}


/**************************************************************************************
				SELECTION SORT
***************************************************************************************/
void selectionSort(vector<int>& v)
{
   int current_min_index;
   unsigned int size = v.size();
   for (unsigned int i=0; i<size; ++i)
   { 
     current_min_index = i;
     for (unsigned int j=i+1;j<size; ++j)
        if (v[current_min_index] > v[j])
            current_min_index = j;
     scambia(v, i, current_min_index);
   }
}



/**************************************************************************************
				INSERTION SORT
***************************************************************************************/
void insertionSort(vector<int>& v)
{
   int current, prev;
   unsigned int size = v.size();
   for (unsigned int i=1; i<size; ++i)
   { current=i; 
     prev=i-1;
     while(prev>=0 && v[current]<v[prev])
        {
         scambia(v, current, prev);
         --current;
         --prev;
        }
   }
}


/**************************************************************************************
				BUBBLESORT
***************************************************************************************/
void bubbleSort(vector<int>& v)
{
   unsigned int size = v.size();
   bool scambiati;
   for (unsigned int i=1; i<size; ++i)
      {
      scambiati = false;
      for (unsigned int j=0; j<size-i; ++j)
          if(v[j]>v[j+1])
            { 
              scambia(v, j, j+1);
              scambiati = true;
            }
      if (!scambiati) return;
      }
}



/**************************************************************************************
				   MERGESORT
***************************************************************************************/
void fondi(vector<int>& v, unsigned int inizio, unsigned int centro, unsigned int fine)
{
   vector<int> vsinistra, vdestra;

   for (unsigned int i=inizio; i<=centro; ++i)
      vsinistra.push_back(v[i]);

   for (unsigned int i=centro+1; i<=fine; ++i)
      vdestra.push_back(v[i]);

   unsigned int indicesinistra = 0;
   unsigned int maxsin = vsinistra.size();
   unsigned int indicedestra = 0;
   unsigned int maxdes = vdestra.size();
   
   for (unsigned int i=inizio; i<=fine; ++i)
   {
      if (indicesinistra < maxsin && indicedestra < maxdes)
         {
         if (vsinistra[indicesinistra]<vdestra[indicedestra])
            {
             v[i] = vsinistra[indicesinistra];
             indicesinistra++; continue;
             }
         else
            { 
            v[i] = vdestra[indicedestra];
            indicedestra++; continue;
            }
         } 
      
      if (indicesinistra == maxsin && indicedestra < maxdes)
         { 
            v[i] = vdestra[indicedestra];
            indicedestra++; continue;
         }

       if (indicedestra == maxdes && indicesinistra < maxsin)
         { 
            v[i] = vsinistra[indicesinistra];
            indicesinistra++; continue;
         }         
   } 
}

void ms(vector<int>& v, unsigned int inizio, unsigned int fine)
{
    if (inizio < fine)
      {
          unsigned int centro = (inizio+fine)/2;
          ms(v, inizio, centro);
          ms(v, centro+1, fine);
          fondi(v, inizio, centro, fine);
      }
}


void mergeSort(vector<int>& v)
{
   if (v.size() != 0)
      ms(v, 0, v.size()-1);
}


/**************************************************************************************
				QUICKSORT CON SCELTA "BANALE" DEL PIVOT
***************************************************************************************/
int TrivialPartition(vector<int> &v,int start,int end )
{
   int pivot = v.at(start); // dichiaro che il pivot sara la psizione 0 del vector

   int pvt_index = start+1; 
   //Indico la posizione del pivot all-interno del-vettore, ci servra per indicare sx<pvt<dx
  

   /*Ora andremo a scandire il vettore con un ciclo for
    e se il pivot e maggiore dell-elemento i-esimo allora chiameremo la 
    funzione : scambia e andremo a aumentare pvt_index di uno*/

    for (int i = start+1; i < end; i++)
    {
       if ( v[start] > v.at(i))
       {
          scambia(v,pivot,v.at(i));
          pvt_index++;
       }
       
    }

    //Ora vado a scabiare il valore del pivot con quello del suo indice
    scambia(v,pvt_index,v.at(start));

    // Ora return l-indice del pvt che ci servira' per la funzione del QuickSort
    return pvt_index-1;
    


}

void qsTrivial(vector<int>& v, int start , int end)
{
   if (start<end)
   {
      int pvt_index=TrivialPartition(v,start,end);
      qsTrivial(v,start,pvt_index-1);// scamsiona il vettore dalla posizione 0 fino al pivot-1
      qsTrivial(v,pvt_index+1,end); // scansiona ol vettore dal pvt+1 alla fine del vect
   }
   

}

void quickSortTrivial(vector<int>& v)
{
   qsTrivial(v,0,v.size()-1);
}




/**************************************************************************************
				QUICKSORT RANDOMIZZATO
***************************************************************************************/
int RandomPartition(vector<int> &v, int start , int end)
{
   //La funzione e' pressoche la stessa , solo che alla dichiarazione del pvt andremo a
   //chiamare la f.random
   int pivot = start + rand()%(end-start+1); // dichiaro che il pivot prendera sara in una posizione casuale
   // tra v.at(0) e size;

   int pvt_index = start+1; 
   //Indico la posizione del pivot all-interno del-vettore, ci servra per indicare sx<pvt<dx
  

   /*Ora andremo a scandire il vettore con un ciclo for
    e se il pivot e maggiore dell-elemento i-esimo allora chiameremo la 
    funzione : scambia e andremo a aumentare pvt_index di uno*/

    for (int i = start+1; i < end; i++)
    {
       if ( v[start] > v.at(i))
       {
          scambia(v,pivot,v.at(i));
          pvt_index++;
       }
       
    }

    //Ora vado a scabiare il valore del pivot con quello del suo indice
    scambia(v,pvt_index,v.at(start));

    // Ora return l-indice del pvt che ci servira' per la funzione "main" del QuickSort
    return pvt_index-1;
    

}
void qsRandom(vector<int>& v, int start , int end)
{
   if (start<end)
   {
      int pvt_index=RandomPartition(v,start,end);
      qsRandom(v,start,pvt_index-1);// scansiona il vettore dalla posizione 0 fino al pivot-1
      qsRandom(v,pvt_index+1,end); // scansiona ol vettore dal pvt+1 alla fine del vect
   }
}

void quickSortRandom(vector<int> v)
{
   qsRandom(v,0,v.size()-1);
}
