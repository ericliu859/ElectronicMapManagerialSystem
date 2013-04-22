#pragma once
#include "afxcmn.h"


// CUserModule dialog

class CUserModule : public CDialog
{
	DECLARE_DYNAMIC(CUserModule)
private:
	bool is_openfile;

	bool is_linkid;
	bool is_dispclass;
	bool is_brunch;
	bool is_roadname;
	CString temp;
public:
	CUserModule(CWnd* pParent = NULL);   // standard constructor
	virtual ~CUserModule();

// Dialog Data
	enum { IDD = IDD_DIALOG_USER_MODULE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOpenfile();
	afx_msg void OnBnClickedButtonBubbleSort();
	double showtime;
	afx_msg void OnBnClickedButtonQuickSort();
	afx_msg void OnBnClickedButtonInsertSort();
	afx_msg void OnBnClickedRadioChooseLinkid();
	afx_msg void OnBnClickedRadioChooseLinkdispclass();
	afx_msg void OnBnClickedRadioChooseBrunch();
	afx_msg void OnBnClickedRadioChooseRoadname();
	afx_msg void OnBnClickedButtonOrderSerach();
	afx_msg void OnBnClickedButtonBianrySearch();
	afx_msg void OnBnClickedButtonBlockSearch();
	CString strKey;
	double show_search_time;
	CListCtrl show_message_list;
	virtual BOOL OnInitDialog();
};
