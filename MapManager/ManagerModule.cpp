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
int i = 0;//ָ��ǰ�������ļ�¼
CString temp;  //��ʱ�ַ���

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
	
	//int nsizecount = 0;//��ŵ�·��¼��������
	//FILE* pfp = NULL; //���ļ����ļ�ָ��
	
	if(!is_openfile)  //��֤�û�����������֮ǰ�ȴ������ļ� ����ͬ��
	{
		AfxMessageBox("���ȴ������ļ���");
	}
	else //else1
	{
		UpdateData(true);

		for(i=0;i<nsizecount;i++)
		{
			if(road[i].ullinkId == m_Link_Id)
			{
				AfxMessageBox("�ҵ���");
				break;	
			}
		}
		if(i>=nsizecount)
			AfxMessageBox("�Ҳ�������������ӵ�·��Ϣ��");
		else //else2
		{
			m_admin_road_info.DeleteAllItems();
			m_admin_road_info.InsertItem(1,_T(""));  //����һ�п���

			temp.Format(_T("%ld"),road[i].ullinkId);
			LPCTSTR linkid = (LPCTSTR)temp;
			m_admin_road_info.SetItemText(0,0,linkid); //����·��linkId���и�ʽת���������������ͬ��
	
			temp.Format(_T("%s"),road[i].roadname);
			LPCTSTR roadName = (LPCTSTR)temp;
			m_admin_road_info.SetItemText(0,1,roadName);  //����·�����ƽ��и�ʽת���������������ͬ��

			temp.Format(_T("%d"),road[i].usdispclass);
			LPCTSTR dispcLass = (LPCTSTR)temp;
			m_admin_road_info.SetItemText(0,2,dispcLass);  //����·�ķ��Ž��и�ʽת���������������ͬ��

			temp.Format(_T("%d"),road[i].usbrunch);
			LPCTSTR brunch = (LPCTSTR)temp;
			m_admin_road_info.SetItemText(0,3,brunch);  //����·�Ĳ�·�����и�ʽת���������������ͬ��

			m_Link_Id = road[i].ullinkId;
			temp.Format(_T("%s"),road[i].roadname);
			m_name = temp;
			m_class = road[i].usdispclass;
			m_brunch = road[i].usbrunch;

			UpdateData(false);  //��ʾ���༭����
		} //end of else2
	
	}//end of else1
}

void CManagerModule::OnBnClickedButtonAdminOpenFile()
{
	// TODO: Add your control notification handler code here
	COpenFile open_file;
	open_file.GetData();
	AfxMessageBox("�����ļ��򿪳ɹ���");
	qsort(road,nsizecount,sizeof(RoadRecord),cmp_Link_Id); //����������
	is_openfile = 1;  //�����ļ��򿪱�־λΪ "1" �������ļ��Ѵ�
}

void CManagerModule::OnBnClickedButtonAdminAdd()
{
	// TODO: Add your control notification handler code here
	if(!is_openfile)
	{
		AfxMessageBox("���ȴ������ļ���");
	}
	else
	{
		UpdateData(true);
		
		int j;
		for(j=0;j<nsizecount;j++)
		{
			if(road[j].ullinkId == m_Link_Id)
				break;	 //����ҵ������� for ѭ��
		}

		if(j<nsizecount)  //û�ҵ�
			AfxMessageBox("������ĵ�·����Ѿ����ڣ������ظ���ӣ����������롣");
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
					//AfxMessageBox("�ҵ���");
					break;	
				}
			}
			m_admin_road_info.DeleteAllItems();
			m_admin_road_info.InsertItem(1,_T(""));

/*****************���ݸ�ʽת������������б���һ��*****************/
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
/*****************���ݸ�ʽת�����������������б���һ��*****************/


			m_Link_Id = road[i].ullinkId;
			temp.Format(_T("%s"),road[i].roadname);
			m_name = temp;
			m_class = road[i].usdispclass;
			m_brunch = road[i].usbrunch;
			AfxMessageBox("��ӳɹ���");
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
		AfxMessageBox("���ȴ������ļ���");
	}
	else if(m_Link_Id <= 0){
		AfxMessageBox("��ѡ��Ҫ���ĵĵ�·��Ϣ��");
	}
	else
	{
		UpdateData(true);
		for(int j = 0;j<nsizecount;j++){
			if(j==i) continue;
			if(road[j].ullinkId == m_Link_Id){
				AfxMessageBox("��LinkId�Ѿ���ʹ�ã�");
				return ;
			}
		}
		road[i].ullinkId = m_Link_Id;
		char *tempchar =  m_name.GetBuffer(30);
		strcpy(road[i].roadname,tempchar);
		road[i].usdispclass = m_class;
		road[i].usbrunch =m_brunch;
		AfxMessageBox("�޸ĳɹ���");

		m_admin_road_info.DeleteAllItems();
		m_admin_road_info.InsertItem(1,_T(""));

/*****************���ݸ�ʽת�����������������б���һ��*****************/
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
/*****************���ݸ�ʽת�����������������б���һ��*****************/

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
		AfxMessageBox("���ȴ������ļ���");
	}
	else if(m_Link_Id <= 0){
		AfxMessageBox("��ѡ��Ҫɾ���ĵ�·��Ϣ��");
	}
	else
	{
		for(;i<nsizecount;i++)
		{
		
			road[i] = road[i+1];

		}
		nsizecount--;
		AfxMessageBox("ɾ���ɹ���");
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
	CDialog::OnInitDialog();  //��ʼ���Ի���ͬʱ��ʼ���б��

	// TODO:  Add extra initialization here

	DWORD dwStyle = m_admin_road_info.GetExtendedStyle();//����б���������
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	m_admin_road_info.SetExtendedStyle(dwStyle);
	m_admin_road_info.InsertColumn(0,"LinkId",LVCFMT_LEFT,120);
	m_admin_road_info.InsertColumn(1,"����",LVCFMT_LEFT,120);
	m_admin_road_info.InsertColumn(2,"��·����",LVCFMT_LEFT,120);
	m_admin_road_info.InsertColumn(3,"��·��",LVCFMT_LEFT,120);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CManagerModule::OnBnClickedButtonViewInfo()
{
	// TODO: Add your control notification handler code here
	if(!is_openfile)
	{
		AfxMessageBox("���ȴ������ļ���");
	}
	else  //�����еĵ�·��Ϣ�����
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
