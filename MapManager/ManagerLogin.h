#pragma once


// CManagerLogin dialog

class CManagerLogin : public CDialog
{
	DECLARE_DYNAMIC(CManagerLogin)

public:
	CManagerLogin(CWnd* pParent = NULL);   // standard constructor
	virtual ~CManagerLogin();

// Dialog Data
	enum { IDD = IDD_DIALOG_MANAGER_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString username;
	CString password;
	afx_msg void OnBnClickedButtonLogin();
};
