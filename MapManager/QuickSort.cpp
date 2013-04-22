#include "StdAfx.h"
#include "QuickSort.h"
#include "time.h"
#include "Top.h"
CQuickSort::CQuickSort(void)
{
}

CQuickSort::~CQuickSort(void)
{
}
extern RoadRecord Qroad[70000];
extern RoadRecord  road[70000];
extern int nsizecount;

int Partition(RoadRecord R[],int l,int r){
	int i = l,j = r;
	RoadRecord x = R[i];
	while(i<j){
		while(i<j && R[j].ullinkId>=x.ullinkId){
			j--;
		}
		if(i<j){
			R[i] = R[j];
			i++;
		}
		while(i<j && R[i].ullinkId< x.ullinkId){
			i++;
		}
		if(i<j){
			R[j] = R[i];
			j--;
		}
	}
	R[i] = x;
	return i;
}
void QuickSort(RoadRecord R[],int l,int r){
	int mid ;
	if(l<r){
		mid = Partition(R,l,r);
		//cout << R[mid].ullinkId << endl;
		QuickSort(R,l,mid-1);
		QuickSort(R,mid+1,r);
	}
}
double CQuickSort::GetSort(){
	
	clock_t start,finish;
	double time;
	for(int i=0;i<nsizecount;i++){
		Qroad[i] = road[i];
	}
	printf("Quicksort Begin~\n");
	start = clock();
	int ll = 0,rr = nsizecount-1;
	QuickSort(Qroad,ll,rr);
	finish = clock();
	time = (double)(finish - start)/CLOCKS_PER_SEC;
	printf("Quicksort End~");	
	return time;
}