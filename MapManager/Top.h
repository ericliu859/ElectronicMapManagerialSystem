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
	unsigned long ullinkId;   //��·��LinkId
	unsigned short usroadnamesize;  //��·���ֵĴ�С
	
	unsigned short usdispclass;    //��·����
	unsigned short usbrunch;   //��·��
	unsigned short usroadnameflag;  //�Ƿ�������

	char roadname[22];  //��·��
};
