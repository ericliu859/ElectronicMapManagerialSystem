#include "StdAfx.h"
#include "BubbleSort.h"
#include "time.h"
#include "top.h"
CBubbleSort::CBubbleSort(void)
{
}

CBubbleSort::~CBubbleSort(void)
{
}
extern RoadRecord Broad[70000];
extern RoadRecord  road[70000];
extern int nsizecount;

double CBubbleSort::GetSort(){

	clock_t start,finish;
	double time;
	for(int i=0;i<nsizecount;i++){
		Broad[i] = road[i];
	}
	printf("Bubble Begin~\n");
	start = clock();
	for(int i=0;i<nsizecount;i++){
		for(int j=i+1;j<nsizecount;j++){
			//printf("%d %d\n",i,j);
			if(Broad[i].ullinkId>Broad[j].ullinkId){
				RoadRecord ultemp = Broad[i];
					  Broad[i] = Broad[j];
			        	  Broad[j] = ultemp;
			}
		}
	}
	finish = clock();
	time = (double)(finish - start)/CLOCKS_PER_SEC;
	printf("Bubble End~\n");	
	return time;
}