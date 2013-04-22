// UserModule.cpp : implementation file
//

#include "stdafx.h"
#include "MapManager.h"
#include "UserModule.h"
#include "BubbleSort.h"
#include "QuickSort.h"
#include "InsertSort.h"
#include "OpenFile.h"
#include "Top.h"
#include <stdlib.h>
#include <algorithm>
// CUserModule dialog

//RoadRecord *opened_file;xS
extern RoadRecord  road[70000];
extern RoadRecord Sroad[70000];
extern int nsizecount;

int cmp_linkid(const void *a,const void *b){
	return (*(RoadRecord *)a).ullinkId -  (*(RoadRecord *)b).ullinkId;
}
int cmp_dispclass(const void *a,const void *b){
	return (*(RoadRecord *)a).usdispclass -  (*(RoadRecord *)b).usdispclass;
}
int cmp_brunch(const void *a,const void *b){
	return (*(RoadRecord *)a).usbrunch -  (*(RoadRecord *)b).usbrunch;
}
int cmp_roadname(const void *a,const void *b){
	return strcmp((*(RoadRecord *)a).roadname , (*(RoadRecord *)b).roadname);
}

struct Node{
	int val;
	char str[22];
}node[130];



IMPLEMENT_DYNAMIC(CUserModule, CDialog)

CUserModule::CUserModule(CWnd* pParent /*=NULL*/)
	: CDialog(CUserModule::IDD, pParent)
	, showtime(0)
	, strKey(_T(""))
	, show_search_time(0)
{
	is_openfile = 0;
}

CUserModule::~CUserModule()
{
}

void CUserModule::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SORT_TIME, showtime);
	DDX_Text(pDX, IDC_EDIT_SEARCH_KEY, strKey);
	DDX_Text(pDX, IDC_EDIT_SEARCH_TIME, show_search_time);
	DDX_Control(pDX, IDC_LIST_SHOW_MESSAGE, show_message_list);
}


BEGIN_MESSAGE_MAP(CUserModule, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_OPENFILE, &CUserModule::OnBnClickedButtonOpenfile)
	ON_BN_CLICKED(IDC_BUTTON_BUBBLE_SORT, &CUserModule::OnBnClickedButtonBubbleSort)
	ON_BN_CLICKED(IDC_BUTTON_QUICK_SORT, &CUserModule::OnBnClickedButtonQuickSort)
	ON_BN_CLICKED(IDC_BUTTON_INSERT_SORT, &CUserModule::OnBnClickedButtonInsertSort)
	ON_BN_CLICKED(IDC_RADIO_CHOOSE_LINKID, &CUserModule::OnBnClickedRadioChooseLinkid)
	ON_BN_CLICKED(IDC_RADIO_CHOOSE_LINKDISPCLASS, &CUserModule::OnBnClickedRadioChooseLinkdispclass)
	ON_BN_CLICKED(IDC_RADIO_CHOOSE_BRUNCH, &CUserModule::OnBnClickedRadioChooseBrunch)
	ON_BN_CLICKED(IDC_RADIO_CHOOSE_ROADNAME, &CUserModule::OnBnClickedRadioChooseRoadname)
	ON_BN_CLICKED(IDC_BUTTON_ORDER_SERACH, &CUserModule::OnBnClickedButtonOrderSerach)
	ON_BN_CLICKED(IDC_BUTTON_BIANRY_SEARCH, &CUserModule::OnBnClickedButtonBianrySearch)
	ON_BN_CLICKED(IDC_BUTTON_BLOCK_SEARCH, &CUserModule::OnBnClickedButtonBlockSearch)
END_MESSAGE_MAP()


// CUserModule message handlers

void CUserModule::OnBnClickedButtonOpenfile()
{
	// TODO: Add your control notification handler code here
	//数据类 数据对象
	//打开文件类 打开文件对象
	//数据对象 = 打开文件.获得数据
	COpenFile open_file;
	open_file.GetData();
	AfxMessageBox("数据文件打开成功！");
	is_openfile = 1;
}

void CUserModule::OnBnClickedButtonBubbleSort()
{
	// TODO: Add your control notification handler code here
	//冒泡排序对象
	//冒泡排序对象.排序
	if(!is_openfile){
		AfxMessageBox("请先打开数据文件！");
		return ;
	}
	UpdateData(TRUE);
	CBubbleSort bubble_sort;
	showtime = bubble_sort.GetSort();
	UpdateData(FALSE);
}

void CUserModule::OnBnClickedButtonQuickSort()
{
	// TODO: Add your control notification handler code here
	if(!is_openfile){
		AfxMessageBox("请先打开数据文件！");
		return ;
	}
	UpdateData(TRUE);
	CQuickSort quick_sort;
	showtime = quick_sort.GetSort();
	UpdateData(FALSE);
}

void CUserModule::OnBnClickedButtonInsertSort()
{
	// TODO: Add your control notification handler code here
	if(!is_openfile){
		AfxMessageBox("请先打开数据文件！");
		return ;
	}
	UpdateData(TRUE);
	CInsertSort insert_sort;
	showtime = insert_sort.GetSort();
	UpdateData(FALSE);
}

void CUserModule::OnBnClickedRadioChooseLinkid()
{
	// TODO: Add your control notification handler code here
	is_linkid = 1;
	is_dispclass = 0;
	is_brunch = 0;
	is_roadname = 0;
}

void CUserModule::OnBnClickedRadioChooseLinkdispclass()
{
	// TODO: Add your control notification handler code here
	is_linkid = 0;
	is_dispclass = 1;
	is_brunch = 0;
	is_roadname = 0;
}

void CUserModule::OnBnClickedRadioChooseBrunch()
{
	// TODO: Add your control notification handler code here
	is_linkid = 0;
	is_dispclass = 0;
	is_brunch = 1;
	is_roadname = 0;
}

void CUserModule::OnBnClickedRadioChooseRoadname()
{
	// TODO: Add your control notification handler code here
	is_linkid = 0;
	is_dispclass = 0;
	is_brunch = 0;
	is_roadname = 1;
}

void CUserModule::OnBnClickedButtonOrderSerach()
{
	// TODO: Add your control notification handler code here
	

	UpdateData(TRUE);
	clock_t start,finish;
	double time;
	if(!is_openfile){
		AfxMessageBox("请先打开数据文件！");
		return ;
	}
	for(int i=0;i<nsizecount;i++){
		Sroad[i] = road[i];
	}
	int res = 0;
	start = clock();

	show_message_list.DeleteAllItems();
	
	if(is_linkid && !is_dispclass && !is_brunch && !is_roadname){
		int linkid = atoi(strKey);
		
		for(int i=0;i<nsizecount;i++){
			if(linkid == Sroad[i].ullinkId){
				//AfxMessageBox("Success！");

				show_message_list.InsertItem(res,_T(""));
					
				temp.Format(_T("%ld"),Sroad[i].ullinkId);
				LPCTSTR linkid = (LPCTSTR)temp;
				show_message_list.SetItemText(res,0,linkid);

				temp.Format(_T("%d"),Sroad[i].usdispclass);
				LPCTSTR dispclass = (LPCTSTR)temp;
				show_message_list.SetItemText(res,1,dispclass);

				temp.Format(_T("%d"),Sroad[i].usbrunch);
				LPCTSTR brunch = (LPCTSTR)temp;
				show_message_list.SetItemText(res,2,brunch);

				temp.Format(_T("%s"),Sroad[i].roadname);
				LPCTSTR roadname = (LPCTSTR)temp;
				show_message_list.SetItemText(res,3,roadname);
				res++;
			}
		}
	}
	else if(!is_linkid && is_dispclass && !is_brunch && !is_roadname){
		int dispclass = atoi(strKey);
		for(int i=0;i<nsizecount;i++){
			if(dispclass == Sroad[i].usdispclass){
				//AfxMessageBox("Success！");

				//show_message_list.DeleteAllItems();

				show_message_list.InsertItem(res,_T(""));
					
				temp.Format(_T("%ld"),Sroad[i].ullinkId);
				LPCTSTR linkid = (LPCTSTR)temp;
				show_message_list.SetItemText(res,0,linkid);

				temp.Format(_T("%d"),Sroad[i].usdispclass);
				LPCTSTR dispclass = (LPCTSTR)temp;
				show_message_list.SetItemText(res,1,dispclass);

				temp.Format(_T("%d"),Sroad[i].usbrunch);
				LPCTSTR brunch = (LPCTSTR)temp;
				show_message_list.SetItemText(res,2,brunch);

				temp.Format(_T("%s"),Sroad[i].roadname);
				LPCTSTR roadname = (LPCTSTR)temp;
				show_message_list.SetItemText(res,3,roadname);
				res++;
			}
		}
	}
	else if(!is_linkid && !is_dispclass && is_brunch && !is_roadname){
		int brunch = atoi(strKey);
		for(int i=0;i<nsizecount;i++){
			if(brunch == Sroad[i].usbrunch){
				//AfxMessageBox("Success！");
				
				//show_message_list.DeleteAllItems();
				show_message_list.InsertItem(res,_T(""));
					
				temp.Format(_T("%ld"),Sroad[i].ullinkId);
				LPCTSTR linkid = (LPCTSTR)temp;
				show_message_list.SetItemText(res,0,linkid);

				temp.Format(_T("%d"),Sroad[i].usdispclass);
				LPCTSTR dispclass = (LPCTSTR)temp;
				show_message_list.SetItemText(res,1,dispclass);

				temp.Format(_T("%d"),Sroad[i].usbrunch);
				LPCTSTR brunch = (LPCTSTR)temp;
				show_message_list.SetItemText(res,2,brunch);

				temp.Format(_T("%s"),Sroad[i].roadname);
				LPCTSTR roadname = (LPCTSTR)temp;
				show_message_list.SetItemText(res,3,roadname);
				res++;

			}
		}
	}
	else if(!is_linkid && !is_dispclass && !is_brunch && is_roadname){
		char roadname[1000];
		strncpy(roadname,(LPCTSTR)strKey,sizeof(roadname));
		for(int i=0;i<nsizecount;i++){
			if(strcmp(roadname,Sroad[i].roadname)==0){
				//AfxMessageBox("Success！");
				//show_message_list.DeleteAllItems();
				show_message_list.InsertItem(res,_T(""));
					
				temp.Format(_T("%ld"),Sroad[i].ullinkId);
				LPCTSTR linkid = (LPCTSTR)temp;
				show_message_list.SetItemText(res,0,linkid);

				temp.Format(_T("%d"),Sroad[i].usdispclass);
				LPCTSTR dispclass = (LPCTSTR)temp;
				show_message_list.SetItemText(res,1,dispclass);

				temp.Format(_T("%d"),Sroad[i].usbrunch);
				LPCTSTR brunch = (LPCTSTR)temp;
				show_message_list.SetItemText(res,2,brunch);

				temp.Format(_T("%s"),Sroad[i].roadname);
				LPCTSTR roadname = (LPCTSTR)temp;
				show_message_list.SetItemText(res,3,roadname);
				res++;
			}
		}
	}
	else{
		AfxMessageBox("请选择关键字类型！");
	}
	finish = clock();
	time = (double)(finish - start)/CLOCKS_PER_SEC;
	show_search_time = time;

	UpdateData(FALSE);

}

void CUserModule::OnBnClickedButtonBianrySearch()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	clock_t start,finish;
	double time;
	if(!is_openfile){
		AfxMessageBox("请先打开数据文件！");
		return ;
	}
	for(int i=0;i<nsizecount;i++){
		Sroad[i] = road[i];
	}

	int res=0;
	show_message_list.DeleteAllItems();

	if(is_linkid && !is_dispclass && !is_brunch && !is_roadname){
		qsort(Sroad,nsizecount,sizeof(RoadRecord),cmp_linkid);
		start = clock();
		unsigned long linkid = atoi(strKey);
		int l=0,r=nsizecount,mid;
		while(l<r){
			mid = (l+r)/2;
			if(Sroad[mid].ullinkId == linkid){
				//AfxMessageBox("Success！");
				break;
			}
			else if(Sroad[mid].ullinkId > linkid){
				r = mid ;
			}
			else{
				l = mid + 1;
			}
		}
		finish = clock();

		int i = mid;
		while(Sroad[i].ullinkId == linkid){
			show_message_list.InsertItem(res,_T(""));
					
			temp.Format(_T("%ld"),Sroad[i].ullinkId);
			LPCTSTR linkid = (LPCTSTR)temp;
			show_message_list.SetItemText(res,0,linkid);

			temp.Format(_T("%d"),Sroad[i].usdispclass);
			LPCTSTR dispclass = (LPCTSTR)temp;
			show_message_list.SetItemText(res,1,dispclass);

			temp.Format(_T("%d"),Sroad[i].usbrunch);
			LPCTSTR brunch = (LPCTSTR)temp;
			show_message_list.SetItemText(res,2,brunch);

			temp.Format(_T("%s"),Sroad[i].roadname);
			LPCTSTR roadname = (LPCTSTR)temp;
			show_message_list.SetItemText(res,3,roadname);
			i--;
			res++;
		}
		i = mid + 1;
		while(Sroad[i].ullinkId == linkid){
			show_message_list.InsertItem(res,_T(""));
					
			temp.Format(_T("%ld"),Sroad[i].ullinkId);
			LPCTSTR linkid = (LPCTSTR)temp;
			show_message_list.SetItemText(res,0,linkid);

			temp.Format(_T("%d"),Sroad[i].usdispclass);
			LPCTSTR dispclass = (LPCTSTR)temp;
			show_message_list.SetItemText(res,1,dispclass);

			temp.Format(_T("%d"),Sroad[i].usbrunch);
			LPCTSTR brunch = (LPCTSTR)temp;
			show_message_list.SetItemText(res,2,brunch);

			temp.Format(_T("%s"),Sroad[i].roadname);
			LPCTSTR roadname = (LPCTSTR)temp;
			show_message_list.SetItemText(res,3,roadname);
			i++;
			res++;
		}

	}
	else if(!is_linkid && is_dispclass && !is_brunch && !is_roadname){
		qsort(Sroad,nsizecount,sizeof(RoadRecord),cmp_dispclass);
		start = clock();
		int dispclass = atoi(strKey);
		int l=0,r=nsizecount,mid;
		while(l<r){
			mid = (l+r)/2;
			if(Sroad[mid].usdispclass == dispclass){
				//AfxMessageBox("Success！");
				break;
			}
			else if(Sroad[mid].usdispclass > dispclass){
				r = mid;
			}
			else{
				l = mid + 1;
			}
		}
		finish = clock();
		int i = mid;
		while(Sroad[i].usdispclass == dispclass){
			show_message_list.InsertItem(res,_T(""));
					
			temp.Format(_T("%ld"),Sroad[i].ullinkId);
			LPCTSTR linkid = (LPCTSTR)temp;
			show_message_list.SetItemText(res,0,linkid);

			temp.Format(_T("%d"),Sroad[i].usdispclass);
			LPCTSTR dispclass = (LPCTSTR)temp;
			show_message_list.SetItemText(res,1,dispclass);

			temp.Format(_T("%d"),Sroad[i].usbrunch);
			LPCTSTR brunch = (LPCTSTR)temp;
			show_message_list.SetItemText(res,2,brunch);

			temp.Format(_T("%s"),Sroad[i].roadname);
			LPCTSTR roadname = (LPCTSTR)temp;
			show_message_list.SetItemText(res,3,roadname);
			i--;
			res++;
		}
		i = mid + 1;
		while(Sroad[i].usdispclass == dispclass){
			show_message_list.InsertItem(res,_T(""));
					
			temp.Format(_T("%ld"),Sroad[i].ullinkId);
			LPCTSTR linkid = (LPCTSTR)temp;
			show_message_list.SetItemText(res,0,linkid);

			temp.Format(_T("%d"),Sroad[i].usdispclass);
			LPCTSTR dispclass = (LPCTSTR)temp;
			show_message_list.SetItemText(res,1,dispclass);

			temp.Format(_T("%d"),Sroad[i].usbrunch);
			LPCTSTR brunch = (LPCTSTR)temp;
			show_message_list.SetItemText(res,2,brunch);

			temp.Format(_T("%s"),Sroad[i].roadname);
			LPCTSTR roadname = (LPCTSTR)temp;
			show_message_list.SetItemText(res,3,roadname);
			i++;
			res++;
		}
		
	}
	else if(!is_linkid && !is_dispclass && is_brunch && !is_roadname){
		qsort(Sroad,nsizecount,sizeof(RoadRecord),cmp_brunch);
		start = clock();
		int brunch = atoi(strKey);
		int l=0,r=nsizecount,mid;
		while(l<r){
			mid = (l+r)/2;
			if(Sroad[mid].usbrunch == brunch){
				//AfxMessageBox("Success！");
				break;
			}
			else if(Sroad[mid].usbrunch > brunch){
				r = mid;
			}
			else{
				l = mid + 1;
			}
		}
		finish = clock();
		int i = mid;
		while(Sroad[i].usbrunch == brunch){
			show_message_list.InsertItem(res,_T(""));
					
			temp.Format(_T("%ld"),Sroad[i].ullinkId);
			LPCTSTR linkid = (LPCTSTR)temp;
			show_message_list.SetItemText(res,0,linkid);

			temp.Format(_T("%d"),Sroad[i].usdispclass);
			LPCTSTR dispclass = (LPCTSTR)temp;
			show_message_list.SetItemText(res,1,dispclass);

			temp.Format(_T("%d"),Sroad[i].usbrunch);
			LPCTSTR brunch = (LPCTSTR)temp;
			show_message_list.SetItemText(res,2,brunch);

			temp.Format(_T("%s"),Sroad[i].roadname);
			LPCTSTR roadname = (LPCTSTR)temp;
			show_message_list.SetItemText(res,3,roadname);
			i--;
			res++;
		}
		i = mid + 1;
		while(Sroad[i].usbrunch == brunch){
			show_message_list.InsertItem(res,_T(""));
					
			temp.Format(_T("%ld"),Sroad[i].ullinkId);
			LPCTSTR linkid = (LPCTSTR)temp;
			show_message_list.SetItemText(res,0,linkid);

			temp.Format(_T("%d"),Sroad[i].usdispclass);
			LPCTSTR dispclass = (LPCTSTR)temp;
			show_message_list.SetItemText(res,1,dispclass);

			temp.Format(_T("%d"),Sroad[i].usbrunch);
			LPCTSTR brunch = (LPCTSTR)temp;
			show_message_list.SetItemText(res,2,brunch);

			temp.Format(_T("%s"),Sroad[i].roadname);
			LPCTSTR roadname = (LPCTSTR)temp;
			show_message_list.SetItemText(res,3,roadname);
			i++;
			res++;
		}
		
	}
	else if(!is_linkid && !is_dispclass && !is_brunch && is_roadname){
		qsort(Sroad,nsizecount,sizeof(RoadRecord),cmp_roadname);
		start = clock();
		char roadname[1000];
		strncpy(roadname,(LPCTSTR)strKey,sizeof(roadname));
		
		
		int l=0,r=nsizecount,mid;
		while(l<r){
			mid = (l+r)/2;
			if(strcmp(Sroad[mid].roadname,roadname)==0){
				//AfxMessageBox("Success！");
				break;
			}
			else if(strcmp(Sroad[mid].roadname,roadname) > 0){
				r = mid;
			}
			else{
				l = mid + 1;
			}
		}
		finish = clock();
		int i = mid;
		while(strcmp(Sroad[i].roadname,roadname)==0){
			show_message_list.InsertItem(res,_T(""));
					
			temp.Format(_T("%ld"),Sroad[i].ullinkId);
			LPCTSTR linkid = (LPCTSTR)temp;
			show_message_list.SetItemText(res,0,linkid);

			temp.Format(_T("%d"),Sroad[i].usdispclass);
			LPCTSTR dispclass = (LPCTSTR)temp;
			show_message_list.SetItemText(res,1,dispclass);

			temp.Format(_T("%d"),Sroad[i].usbrunch);
			LPCTSTR brunch = (LPCTSTR)temp;
			show_message_list.SetItemText(res,2,brunch);

			temp.Format(_T("%s"),Sroad[i].roadname);
			LPCTSTR roadname = (LPCTSTR)temp;
			show_message_list.SetItemText(res,3,roadname);
			i--;
			res++;
		}
		i = mid + 1;
		while(strcmp(Sroad[i].roadname,roadname)==0){
			show_message_list.InsertItem(res,_T(""));
					
			temp.Format(_T("%ld"),Sroad[i].ullinkId);
			LPCTSTR linkid = (LPCTSTR)temp;
			show_message_list.SetItemText(res,0,linkid);

			temp.Format(_T("%d"),Sroad[i].usdispclass);
			LPCTSTR dispclass = (LPCTSTR)temp;
			show_message_list.SetItemText(res,1,dispclass);

			temp.Format(_T("%d"),Sroad[i].usbrunch);
			LPCTSTR brunch = (LPCTSTR)temp;
			show_message_list.SetItemText(res,2,brunch);

			temp.Format(_T("%s"),Sroad[i].roadname);
			LPCTSTR roadname = (LPCTSTR)temp;
			show_message_list.SetItemText(res,3,roadname);
			i++;
			res++;
		}
	}
	else{
		AfxMessageBox("请选择关键字类型！");
		return ;

	}
	
	time = (double)(finish - start)/CLOCKS_PER_SEC;
	show_search_time = time;
	UpdateData(FALSE);
}

void CUserModule::OnBnClickedButtonBlockSearch()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	clock_t start,finish;
	double time;
	if(!is_openfile){
		AfxMessageBox("请先打开数据文件！");
		return ;
	}
	for(int i=0;i<nsizecount;i++){
		Sroad[i] = road[i];
	}

	int res=0;
	show_message_list.DeleteAllItems();

	if(is_linkid && !is_dispclass && !is_brunch && !is_roadname){
		qsort(Sroad,nsizecount,sizeof(RoadRecord),cmp_linkid);
		start = clock();
		int linkid = atoi(strKey);
		int i;
		for(i=0;i<nsizecount;i+=500){
			node[i/500].val = Sroad[i].ullinkId;
		}
		node[i/500].val = Sroad[nsizecount-1].ullinkId;
		int l = 0,r = i/500 ,mid;
		int flag=0;
		while(l<r){
			mid = (l+r)/2;
			if(node[mid].val <= linkid && linkid <= node[mid+1].val  ){
				for(int j=mid*500; j<=(mid+1)*500;j++){
					if(Sroad[j].ullinkId == linkid){
						//AfxMessageBox("Success！");
						flag = 1;
						mid = j;
						break;
					}
				}
			}
			else if(node[mid].val > linkid){
				r = mid ;
			}
			else{
				l = mid + 1;
			}
			if(flag) break;
		}
		finish = clock();

		i = mid;
		while(Sroad[i].ullinkId == linkid){
			show_message_list.InsertItem(res,_T(""));
					
			temp.Format(_T("%ld"),Sroad[i].ullinkId);
			LPCTSTR linkid = (LPCTSTR)temp;
			show_message_list.SetItemText(res,0,linkid);

			temp.Format(_T("%d"),Sroad[i].usdispclass);
			LPCTSTR dispclass = (LPCTSTR)temp;
			show_message_list.SetItemText(res,1,dispclass);

			temp.Format(_T("%d"),Sroad[i].usbrunch);
			LPCTSTR brunch = (LPCTSTR)temp;
			show_message_list.SetItemText(res,2,brunch);

			temp.Format(_T("%s"),Sroad[i].roadname);
			LPCTSTR roadname = (LPCTSTR)temp;
			show_message_list.SetItemText(res,3,roadname);
			i--;
			res++;
		}
		i = mid + 1;
		while(Sroad[i].ullinkId == linkid){
			show_message_list.InsertItem(res,_T(""));
					
			temp.Format(_T("%ld"),Sroad[i].ullinkId);
			LPCTSTR linkid = (LPCTSTR)temp;
			show_message_list.SetItemText(res,0,linkid);

			temp.Format(_T("%d"),Sroad[i].usdispclass);
			LPCTSTR dispclass = (LPCTSTR)temp;
			show_message_list.SetItemText(res,1,dispclass);

			temp.Format(_T("%d"),Sroad[i].usbrunch);
			LPCTSTR brunch = (LPCTSTR)temp;
			show_message_list.SetItemText(res,2,brunch);

			temp.Format(_T("%s"),Sroad[i].roadname);
			LPCTSTR roadname = (LPCTSTR)temp;
			show_message_list.SetItemText(res,3,roadname);
			i++;
			res++;
		}
	}
	else if(!is_linkid && is_dispclass && !is_brunch && !is_roadname){
		qsort(Sroad,nsizecount,sizeof(RoadRecord),cmp_dispclass);
		start = clock();
		int dispclass = atoi(strKey);

		int i;
		for(i=0;i<nsizecount;i+=500){
			node[i/500].val = Sroad[i].usdispclass;
		}
		node[i/500].val = Sroad[nsizecount-1].usdispclass;

		int l = 0,r = i/500 ,mid;
		int flag=0;
		while(l<r){
			mid = (l+r)/2;
			if(node[mid].val <= dispclass && dispclass <= node[mid+1].val ){
				//AfxMessageBox("Success！");
				for(int j=mid*500; j<=(mid+1)*500;j++){
					if(Sroad[j].usdispclass == dispclass){
						//AfxMessageBox("Success！");
						flag = 1;
						mid = j;
						break;
					}
				}
			}
			else if(node[mid].val > dispclass){
				r = mid;
			}
			else{
				l = mid + 1;
			}
			if(flag) break;
		}
		finish = clock();
		i = mid;
		while(Sroad[i].usdispclass == dispclass){
			show_message_list.InsertItem(res,_T(""));
					
			temp.Format(_T("%ld"),Sroad[i].ullinkId);
			LPCTSTR linkid = (LPCTSTR)temp;
			show_message_list.SetItemText(res,0,linkid);

			temp.Format(_T("%d"),Sroad[i].usdispclass);
			LPCTSTR dispclass = (LPCTSTR)temp;
			show_message_list.SetItemText(res,1,dispclass);

			temp.Format(_T("%d"),Sroad[i].usbrunch);
			LPCTSTR brunch = (LPCTSTR)temp;
			show_message_list.SetItemText(res,2,brunch);

			temp.Format(_T("%s"),Sroad[i].roadname);
			LPCTSTR roadname = (LPCTSTR)temp;
			show_message_list.SetItemText(res,3,roadname);
			i--;
			res++;
		}
		i = mid + 1;
		while(Sroad[i].usdispclass == dispclass){
			show_message_list.InsertItem(res,_T(""));
					
			temp.Format(_T("%ld"),Sroad[i].ullinkId);
			LPCTSTR linkid = (LPCTSTR)temp;
			show_message_list.SetItemText(res,0,linkid);

			temp.Format(_T("%d"),Sroad[i].usdispclass);
			LPCTSTR dispclass = (LPCTSTR)temp;
			show_message_list.SetItemText(res,1,dispclass);

			temp.Format(_T("%d"),Sroad[i].usbrunch);
			LPCTSTR brunch = (LPCTSTR)temp;
			show_message_list.SetItemText(res,2,brunch);

			temp.Format(_T("%s"),Sroad[i].roadname);
			LPCTSTR roadname = (LPCTSTR)temp;
			show_message_list.SetItemText(res,3,roadname);
			i++;
			res++;
		}
	}
	else if(!is_linkid && !is_dispclass && is_brunch && !is_roadname){
		qsort(Sroad,nsizecount,sizeof(RoadRecord),cmp_brunch);
		start = clock();
		int brunch = atoi(strKey);

		int i;
		for(i=0;i<nsizecount;i+=500){
			node[i/500].val = Sroad[i].usbrunch;
		}
		node[i/500].val = Sroad[nsizecount-1].usbrunch;

		int l = 0,r = i/500 ,mid;
		int flag=0;
		while(l<r){
			mid = (l+r)/2;
			if(node[mid].val <= brunch && brunch <= node[mid+1].val ){
				//AfxMessageBox("Success！");
				for(int j=mid*500; j<=(mid+1)*500;j++){
					if(Sroad[j].usbrunch == brunch){
						//AfxMessageBox("Success！");
						flag = 1;
						mid = j;
						break;
					}
				}
			}
			else if(node[mid].val > brunch){
				r = mid;
			}
			else{
				l = mid + 1;
			}
			if(flag) break;
		}
		finish = clock();
		i = mid;
		while(Sroad[i].usbrunch == brunch){
			show_message_list.InsertItem(res,_T(""));
					
			temp.Format(_T("%ld"),Sroad[i].ullinkId);
			LPCTSTR linkid = (LPCTSTR)temp;
			show_message_list.SetItemText(res,0,linkid);

			temp.Format(_T("%d"),Sroad[i].usdispclass);
			LPCTSTR dispclass = (LPCTSTR)temp;
			show_message_list.SetItemText(res,1,dispclass);

			temp.Format(_T("%d"),Sroad[i].usbrunch);
			LPCTSTR brunch = (LPCTSTR)temp;
			show_message_list.SetItemText(res,2,brunch);

			temp.Format(_T("%s"),Sroad[i].roadname);
			LPCTSTR roadname = (LPCTSTR)temp;
			show_message_list.SetItemText(res,3,roadname);
			i--;
			res++;
		}
		i = mid + 1;
		while(Sroad[i].usbrunch == brunch){
			show_message_list.InsertItem(res,_T(""));
					
			temp.Format(_T("%ld"),Sroad[i].ullinkId);
			LPCTSTR linkid = (LPCTSTR)temp;
			show_message_list.SetItemText(res,0,linkid);

			temp.Format(_T("%d"),Sroad[i].usdispclass);
			LPCTSTR dispclass = (LPCTSTR)temp;
			show_message_list.SetItemText(res,1,dispclass);

			temp.Format(_T("%d"),Sroad[i].usbrunch);
			LPCTSTR brunch = (LPCTSTR)temp;
			show_message_list.SetItemText(res,2,brunch);

			temp.Format(_T("%s"),Sroad[i].roadname);
			LPCTSTR roadname = (LPCTSTR)temp;
			show_message_list.SetItemText(res,3,roadname);
			i++;
			res++;
		}
	}
	else if(!is_linkid && !is_dispclass && !is_brunch && is_roadname){
		qsort(Sroad,nsizecount,sizeof(RoadRecord),cmp_roadname);
		start = clock();
		char roadname[1000];
		strncpy(roadname,(LPCTSTR)strKey,sizeof(roadname));

		int l=0,r=nsizecount,mid;
		while(l<r){
			mid = (l+r)/2;
			if(strcmp(Sroad[mid].roadname,roadname)==0){
				//AfxMessageBox("Success！");
				break;
			}
			else if(strcmp(Sroad[mid].roadname,roadname) > 0){
				r = mid;
			}
			else{
				l = mid + 1;
			}
		}
		finish = clock();
		int i = mid;

		while(strcmp(Sroad[i].roadname,roadname)==0){
			show_message_list.InsertItem(res,_T(""));
					
			temp.Format(_T("%ld"),Sroad[i].ullinkId);
			LPCTSTR linkid = (LPCTSTR)temp;
			show_message_list.SetItemText(res,0,linkid);

			temp.Format(_T("%d"),Sroad[i].usdispclass);
			LPCTSTR dispclass = (LPCTSTR)temp;
			show_message_list.SetItemText(res,1,dispclass);

			temp.Format(_T("%d"),Sroad[i].usbrunch);
			LPCTSTR brunch = (LPCTSTR)temp;
			show_message_list.SetItemText(res,2,brunch);

			temp.Format(_T("%s"),Sroad[i].roadname);
			LPCTSTR roadname = (LPCTSTR)temp;
			show_message_list.SetItemText(res,3,roadname);
			i--;
			res++;
		}
		i = mid + 1;
		while(strcmp(Sroad[i].roadname,roadname)==0){
			show_message_list.InsertItem(res,_T(""));
					
			temp.Format(_T("%ld"),Sroad[i].ullinkId);
			LPCTSTR linkid = (LPCTSTR)temp;
			show_message_list.SetItemText(res,0,linkid);

			temp.Format(_T("%d"),Sroad[i].usdispclass);
			LPCTSTR dispclass = (LPCTSTR)temp;
			show_message_list.SetItemText(res,1,dispclass);

			temp.Format(_T("%d"),Sroad[i].usbrunch);
			LPCTSTR brunch = (LPCTSTR)temp;
			show_message_list.SetItemText(res,2,brunch);

			temp.Format(_T("%s"),Sroad[i].roadname);
			LPCTSTR roadname = (LPCTSTR)temp;
			show_message_list.SetItemText(res,3,roadname);
			i++;
			res++;
		}
	}
	else{
		AfxMessageBox("请选择关键字类型！");
		return ;
	}
	
	time = (double)(finish - start)/CLOCKS_PER_SEC;
	show_search_time = time;
	UpdateData(FALSE);
}

BOOL CUserModule::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	DWORD dwStyle = show_message_list.GetExtendedStyle();//添加列表框的网格线
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	show_message_list.SetExtendedStyle(dwStyle);
	show_message_list.InsertColumn(0,"LinkId",LVCFMT_LEFT,100);
	show_message_list.InsertColumn(1,"道路番号",LVCFMT_LEFT,100);
	show_message_list.InsertColumn(2,"岔路数",LVCFMT_LEFT,100);
	show_message_list.InsertColumn(3,"名称",LVCFMT_LEFT,120);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
