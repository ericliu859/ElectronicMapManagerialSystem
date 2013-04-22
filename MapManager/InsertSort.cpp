#include "StdAfx.h"
#include "InsertSort.h"
#include "time.h"
#include "top.h"
CInsertSort::CInsertSort(void)
{
}

CInsertSort::~CInsertSort(void)
{
}
extern RoadRecord Iroad[70000];
extern RoadRecord  road[70000];
extern int nsizecount;
double CInsertSort::GetSort(){

	clock_t start,finish;
	double time;
	for(int i=0;i<nsizecount;i++){
		Iroad[i] = road[i];
	}
	printf("Insert Begin~\n");
	start = clock();
	for(int i=1;i<nsizecount;i++){
		
		RoadRecord ultemp = Iroad[i];
		int j = i;
		while(j>0 && ultemp.ullinkId < Iroad[j-1].ullinkId ){
			Iroad[j] = Iroad[j-1];

			j--;
		}
		Iroad[j] = ultemp;
	}
	finish = clock();
	time = (double)(finish - start)/CLOCKS_PER_SEC;
	printf("Insert End~\n");
	return time;
}