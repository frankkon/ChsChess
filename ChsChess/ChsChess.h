
// ChsChess.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CChsChessApp:
// �йش����ʵ�֣������ ChsChess.cpp
//

class CChsChessApp : public CWinAppEx
{
public:
	CChsChessApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CChsChessApp theApp;