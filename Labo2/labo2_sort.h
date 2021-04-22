#include <vector> 
#include <stdlib.h>     // srand, rand, per quickSortRandom() da implementare

using namespace std;


void selectionSort(vector<int>&);
void insertionSort(vector<int>&);
void bubbleSort(vector<int>&);
void mergeSort(vector<int>&);
int TrivialPartition(vector<int> &,int,int );
int RandomPartition(vector<int> &,int,int);
void quickSortTrivial(vector<int>&,);
void quickSortRandom(vector<int>&);
void qsTrivial(vector<int>&,int,int);
void qsRandom(vector<int>&,int,int);
