#pragma once
#include "IM_CsocketClientDlg.h"

// CCSocket 命令目标

class CIM_CsocketClientDlg;//对话框类的声明

class CCSocket : public CSocket
{
public:
	CCSocket();
	virtual ~CCSocket();
	virtual void OnReceive(int nErrorCode);

	CIM_CsocketClientDlg* m_pDlg;
};


