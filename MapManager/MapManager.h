// MapManager.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMapManagerApp:
// �йش����ʵ�֣������ MapManager.cpp
//

class CMapManagerApp : public CWinApp
{
public:
	CMapManagerApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMapManagerApp theApp;