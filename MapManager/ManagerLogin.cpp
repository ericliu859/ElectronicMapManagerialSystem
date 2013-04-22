// ManagerLogin.cpp : implementation file
//

#include "stdafx.h"
#include "MapManager.h"
#include "ManagerLogin.h"
#include "ManagerModule.h"

// CManagerLogin dialog

IMPLEMENT_DYNAMIC(CManagerLogin, CDialog)

CManagerLogin::CManagerLogin(CWnd* pParent /*=NULL*/)
	: CDialog(CManagerLogin::IDD, pParent)
	, username(_T(""))
	, password(_T(""))
{

}

CManagerLogin::~CManagerLogin()
{
}

void CManagerLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_USERNAME, username);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, password);
}


BEGIN_MESSAGE_MAP(CManagerLogin, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CManagerLogin::OnBnClickedButtonLogin)
END_MESSAGE_MAP()


// CManagerLogin message handlers

void CManagerLogin::OnBnClickedButtonLogin()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(username == "ldg" && password == "123"){
		//AfxMessageBox("Success!");
		CManagerModule manager_module;
		manager_module.DoModal();
	}
	else{
		AfxMessageBox("用户名或密码错误！");
	}
	password = "";  //密码清空
	UpdateData(FALSE);
}
