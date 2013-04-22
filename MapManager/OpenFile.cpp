/*打开文件的类*/

#include "StdAfx.h"
#include "OpenFile.h"
#include "Top.h"

COpenFile::COpenFile(void)
{
}

COpenFile::~COpenFile(void)
{
}

extern RoadRecord road[70000];
extern int nsizecount;
void COpenFile::GetData()   //将文件中的数据读入内存
{
	nsizecount = 0;
	char actotalsize[2];
	char aclinkId[4];
	char acroadnamesize[2];
	char acNodeInfo[4];
	FILE* pfp;
	pfp = fopen("GTBL.dat","rb+");
	while(fread(actotalsize,sizeof(actotalsize),1,pfp)!=NULL){
		fread(aclinkId,sizeof(aclinkId),1,pfp);
		fread(acroadnamesize,sizeof(acroadnamesize),1,pfp);
		fread(acNodeInfo,sizeof(acNodeInfo),1,pfp);
	
		unsigned short ustotalsize    = MCGETSHORT(actotalsize);
		unsigned long  ullinkId       = MCGETLONG(aclinkId);
		unsigned short usroadnamesize = MCGETSHORT(acroadnamesize);

		road[nsizecount].ussize = ustotalsize;
		road[nsizecount].ullinkId = ullinkId;
		road[nsizecount].usroadnamesize = usroadnamesize;
		
		int m=(int)acNodeInfo[3]&255;
		road[nsizecount].usdispclass = m&15;
		road[nsizecount].usbrunch    = (m&112)/16;
		road[nsizecount].usroadnameflag = (m&128)/128;

		fread(&road[nsizecount].roadname,sizeof(char),ustotalsize-12,pfp);
	
		nsizecount ++;	
	}
	fclose(pfp);
}