#pragma once
#include "afxcmn.h"


// CManagerModule dialog

class CManagerModule : public CDialog
{
	DECLARE_DYNAMIC(CManagerModule)

public:
	CManagerModule(CWnd* pParent = NULL);   // standard constructor
	virtual ~CManagerModule();

// Dialog Data
	enum { IDD = IDD_DIALOG_MANAGER_MODULE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_admin_road_info;
	long m_Link_Id;
	CString m_name;
	int m_class;
	int m_brunch;
	afx_msg void OnBnClickedButtonAdminSearrch();
	afx_msg void OnBnClickedButtonAdminOpenFile();
	bool is_openfile;
	afx_msg void OnBnClickedButtonAdminAdd();
	afx_msg void OnBnClickedButtonModify();
	afx_msg void OnBnClickedButtonDelete();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonViewInfo();
};
