
// IM_CsocketClient.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CIM_CsocketClientApp: 
// �йش����ʵ�֣������ IM_CsocketClient.cpp
//

class CIM_CsocketClientApp : public CWinApp
{
public:
	CIM_CsocketClientApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CIM_CsocketClientApp theApp;