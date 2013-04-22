#pragma once
#include <time.h>
#include <stdio.h>
#include <iostream>
#include <string>
#define MCGETCHAR(data)  (*((char *)(data)))
#define MCGETSHORT(data)  ((unsigned short)(( ((unsigned short)(*((char *)(data))))<<8 )|( ((unsigned short)(*((char *)(data)+1)))&0x00ff )))
#define MCGETLONG(data)  ( ( ((unsigned long)MCGETSHORT((data)))<<16 )|( ((unsigned long)MCGETSHORT((char *)(data)+2))&0x0000ffff ) )
#define MCGET3BN(data)  ( ( ((unsigned long)MCGETCHAR((data)))<<16 )|( ((unsigned long)MCGETSHORT((char *)(data)+1))&0x0000ffff ) )
using namespace std;

struct RoadRecord{
	unsigned short ussize;  
	unsigned long ullinkId;   //道路的LinkId
	unsigned short usroadnamesize;  //道路名字的大小
	
	unsigned short usdispclass;    //道路番号
	unsigned short usbrunch;   //岔路数
	unsigned short usroadnameflag;  //是否有名字

	char roadname[22];  //道路名
};
