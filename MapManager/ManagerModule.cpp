// ManagerModule.cpp : implementation file
//

#include "stdafx.h"
#include "MapManager.h"
#include "ManagerModule.h"
#include "Top.h"
#include "OpenFile.h"
#include "stdlib.h"

extern RoadRecord road[700000];
extern int nsizecount;
int i = 0;//指向当前所操作的记录
CString temp;  //临时字符串

int cmp_Link_Id(const void *a,const void *b){
	return (*(RoadRecord *)a).ullinkId -  (*(RoadRecord *)b).ullinkId;
}

// CManagerModule dialog

IMPLEMENT_DYNAMIC(CManagerModule, CDialog)

CManagerModule::CManagerModule(CWnd* pParent /*=NULL*/)
	: CDialog(CManagerModule::IDD, pParent)
	, m_Link_Id(0)
	, m_name(_T(""))
	, m_class(0)
	, m_brunch(0)
{
	is_openfile = 0;
}

CManagerModule::~CManagerModule()
{
}

void CManagerModule::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ADMIN_ROAD_INFO, m_admin_road_info);
	DDX_Text(pDX, IDC_EDIT_ADMIN_LINKID, m_Link_Id);
	DDX_Text(pDX, IDC_EDIT_ADMIN_NAME, m_name);
	DDX_Text(pDX, IDC_EDIT_ADMIN_CLASS, m_class);
	DDX_Text(pDX, IDC_EDIT_ADMIN_BRUNCH, m_brunch);
}


BEGIN_MESSAGE_MAP(CManagerModule, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ADMIN_SEARRCH, &CManagerModule::OnBnClickedButtonAdminSearrch)
	ON_BN_CLICKED(IDC_BUTTON_ADMIN_OPEN_FILE, &CManagerModule::OnBnClickedButtonAdminOpenFile)
	ON_BN_CLICKED(IDC_BUTTON_ADMIN_ADD, &CManagerModule::OnBnClickedButtonAdminAdd)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, &CManagerModule::OnBnClickedButtonModify)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CManagerModule::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_VIEW_INFO, &CManagerModule::OnBnClickedButtonViewInfo)
END_MESSAGE_MAP()


// CManagerModule message handlers

void CManagerModule::OnBnClickedButtonAdminSearrch()
{
	// TODO: Add your control notification handler code here
	
	//int nsizecount = 0;//存放道路记录的总条数
	//FILE* pfp = NULL; //打开文件的文件指针
	
	if(!is_openfile)  //保证用户在其它操作之前先打开数据文件 （下同）
	{
		AfxMessageBox("请先打开数据文件！");
	}
	else //else1
	{
		UpdateData(true);

		for(i=0;i<nsizecount;i++)
		{
			if(road[i].ullinkId == m_Link_Id)
			{
				AfxMessageBox("找到！");
				break;	
			}
		}
		if(i>=nsizecount)
			AfxMessageBox("找不到！您可以添加道路信息。");
		else //else2
		{
			m_admin_road_info.DeleteAllItems();
			m_admin_road_info.InsertItem(1,_T(""));  //插入一行空行

			temp.Format(_T("%ld"),road[i].ullinkId);
			LPCTSTR linkid = (LPCTSTR)temp;
			m_admin_road_info.SetItemText(0,0,linkid); //将道路的linkId进行格式转换，并输出。（下同）
	
			temp.Format(_T("%s"),road[i].roadname);
			LPCTSTR roadName = (LPCTSTR)temp;
			m_admin_road_info.SetItemText(0,1,roadName);  //将道路的名称进行格式转换，并输出。（下同）

			temp.Format(_T("%d"),road[i].usdispclass);
			LPCTSTR dispcLass = (LPCTSTR)temp;
			m_admin_road_info.SetItemText(0,2,dispcLass);  //将道路的番号进行格式转换，并输出。（下同）

			temp.Format(_T("%d"),road[i].usbrunch);
			LPCTSTR brunch = (LPCTSTR)temp;
			m_admin_road_info.SetItemText(0,3,brunch);  //将道路的岔路数进行格式转换，并输出。（下同）

			m_Link_Id = road[i].ullinkId;
			temp.Format(_T("%s"),road[i].roadname);
			m_name = temp;
			m_class = road[i].usdispclass;
			m_brunch = road[i].usbrunch;

			UpdateData(false);  //显示到编辑框中
		} //end of else2
	
	}//end of else1
}

void CManagerModule::OnBnClickedButtonAdminOpenFile()
{
	// TODO: Add your control notification handler code here
	COpenFile open_file;
	open_file.GetData();
	AfxMessageBox("数据文件打开成功！");
	qsort(road,nsizecount,sizeof(RoadRecord),cmp_Link_Id); //对数据排序
	is_openfile = 1;  //设置文件打开标志位为 "1" ，表明文件已打开
}

void CManagerModule::OnBnClickedButtonAdminAdd()
{
	// TODO: Add your control notification handler code here
	if(!is_openfile)
	{
		AfxMessageBox("请先打开数据文件！");
	}
	else
	{
		UpdateData(true);
		
		int j;
		for(j=0;j<nsizecount;j++)
		{
			if(road[j].ullinkId == m_Link_Id)
				break;	 //如果找到就跳出 for 循环
		}

		if(j<nsizecount)  //没找到
			AfxMessageBox("您输入的道路编号已经存在，不可重复添加！请重新输入。");
		else
		{
			road[nsizecount].ullinkId = m_Link_Id;
		
			char *tempchar =  m_name.GetBuffer(30);
			strcpy(road[nsizecount].roadname,tempchar);
			//road[nsizecount].roadname = tempchar;
			road[nsizecount].usdispclass = m_class;
			road[nsizecount].usbrunch =m_brunch;
			UpdateData(false);
			nsizecount++;
			
			UpdateData(true);

			for(i=0;i<nsizecount;i++)
			{
				if(road[i].ullinkId == m_Link_Id)
				{
					//AfxMessageBox("找到！");
					break;	
				}
			}
			m_admin_road_info.DeleteAllItems();
			m_admin_road_info.InsertItem(1,_T(""));

/*****************数据格式转换，并输出到列表框第一行*****************/
			temp.Format(_T("%ld"),road[i].ullinkId);
			LPCTSTR linkid = (LPCTSTR)temp;
			m_admin_road_info.SetItemText(0,0,linkid);

			temp.Format(_T("%s"),road[i].roadname);
			LPCTSTR roadName = (LPCTSTR)temp;
			m_admin_road_info.SetItemText(0,1,roadName);

			temp.Format(_T("%d"),road[i].usdispclass);
			LPCTSTR dispcLass = (LPCTSTR)temp;
			m_admin_road_info.SetItemText(0,2,dispcLass);

			temp.Format(_T("%d"),road[i].usbrunch);
			LPCTSTR brunch = (LPCTSTR)temp;
			m_admin_road_info.SetItemText(0,3,brunch);
/*****************数据格式转换，并输出并输出到列表框第一行*****************/


			m_Link_Id = road[i].ullinkId;
			temp.Format(_T("%s"),road[i].roadname);
			m_name = temp;
			m_class = road[i].usdispclass;
			m_brunch = road[i].usbrunch;
			AfxMessageBox("添加成功！");
			UpdateData(false);
			
			m_Link_Id = 0;
			m_name = "";
			m_class = 0;
			m_brunch = 0;
			UpdateData(false);
			
		}
	}
}

void CManagerModule::OnBnClickedButtonModify()
{
	// TODO: Add your control notification handler code here
	if(!is_openfile)
	{
		AfxMessageBox("请先打开数据文件！");
	}
	else if(m_Link_Id <= 0){
		AfxMessageBox("请选择要更改的道路信息！");
	}
	else
	{
		UpdateData(true);
		for(int j = 0;j<nsizecount;j++){
			if(j==i) continue;
			if(road[j].ullinkId == m_Link_Id){
				AfxMessageBox("该LinkId已经被使用！");
				return ;
			}
		}
		road[i].ullinkId = m_Link_Id;
		char *tempchar =  m_name.GetBuffer(30);
		strcpy(road[i].roadname,tempchar);
		road[i].usdispclass = m_class;
		road[i].usbrunch =m_brunch;
		AfxMessageBox("修改成功！");

		m_admin_road_info.DeleteAllItems();
		m_admin_road_info.InsertItem(1,_T(""));

/*****************数据格式转换，并输出并输出到列表框第一行*****************/
		temp.Format(_T("%ld"),road[i].ullinkId);
		LPCTSTR linkid = (LPCTSTR)temp;
		m_admin_road_info.SetItemText(0,0,linkid);

		temp.Format(_T("%s"),road[i].roadname);
		LPCTSTR roadName = (LPCTSTR)temp;
		m_admin_road_info.SetItemText(0,1,roadName);

		temp.Format(_T("%d"),road[i].usdispclass);
		LPCTSTR dispcLass = (LPCTSTR)temp;
		m_admin_road_info.SetItemText(0,2,dispcLass);

		temp.Format(_T("%d"),road[i].usbrunch);
		LPCTSTR brunch = (LPCTSTR)temp;
		m_admin_road_info.SetItemText(0,3,brunch);
/*****************数据格式转换，并输出并输出到列表框第一行*****************/

		m_Link_Id = road[i].ullinkId;
		temp.Format(_T("%s"),road[i].roadname);
		m_name = temp;
		m_class = road[i].usdispclass;
		m_brunch = road[i].usbrunch;
		UpdateData(false);
	}
}

void CManagerModule::OnBnClickedButtonDelete()
{
	// TODO: Add your control notification handler code here
	if(!is_openfile)
	{
		AfxMessageBox("请先打开数据文件！");
	}
	else if(m_Link_Id <= 0){
		AfxMessageBox("请选择要删除的道路信息！");
	}
	else
	{
		for(;i<nsizecount;i++)
		{
		
			road[i] = road[i+1];

		}
		nsizecount--;
		AfxMessageBox("删除成功！");
		m_admin_road_info.DeleteAllItems();
		m_Link_Id = 0;
		m_name = "";
		m_class = 0;
		m_brunch = 0;
		UpdateData(false);
	}
}

BOOL CManagerModule::OnInitDialog()
{
	CDialog::OnInitDialog();  //初始化对话框同时初始化列表框

	// TODO:  Add extra initialization here

	DWORD dwStyle = m_admin_road_info.GetExtendedStyle();//添加列表框的网格线
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	m_admin_road_info.SetExtendedStyle(dwStyle);
	m_admin_road_info.InsertColumn(0,"LinkId",LVCFMT_LEFT,120);
	m_admin_road_info.InsertColumn(1,"名称",LVCFMT_LEFT,120);
	m_admin_road_info.InsertColumn(2,"道路番号",LVCFMT_LEFT,120);
	m_admin_road_info.InsertColumn(3,"岔路数",LVCFMT_LEFT,120);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CManagerModule::OnBnClickedButtonViewInfo()
{
	// TODO: Add your control notification handler code here
	if(!is_openfile)
	{
		AfxMessageBox("请先打开数据文件！");
	}
	else  //将所有的道路信息都输出
	{
		m_admin_road_info.DeleteAllItems();

		int nindex = 0;
		for(int i = 0;i<nsizecount;i++)
		{
			nindex = m_admin_road_info.InsertItem(i,_T(""));
			temp.Format(_T("%ld"),road[nindex].ullinkId);
			LPCTSTR linkid = (LPCTSTR)temp;
			m_admin_road_info.SetItemText(nindex,0,linkid);
	
			temp.Format(_T("%s"),road[nindex].roadname);
			LPCTSTR roadName = (LPCTSTR)temp;
			m_admin_road_info.SetItemText(nindex,1,roadName);

			temp.Format(_T("%d"),road[nindex].usdispclass);
			LPCTSTR dispcLass = (LPCTSTR)temp;
			m_admin_road_info.SetItemText(nindex,2,dispcLass);

			temp.Format(_T("%d"),road[nindex].usbrunch);
			LPCTSTR brunch = (LPCTSTR)temp;
			m_admin_road_info.SetItemText(nindex,3,brunch);
		}
	}
}
