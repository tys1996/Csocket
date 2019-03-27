#pragma once
#include "IM_CsocketClientDlg.h"

// CCSocket 命令目标

class CIM_CsocketClientDlg;//对话框类的声明

class CCSocket : public CSocket
{
	DECLARE_DYNAMIC(CCSocket);//动态类的声明
public:
	CCSocket(CIM_CsocketClientDlg* pDlg);//增加入口参数
	virtual ~CCSocket();
	CIM_CsocketClientDlg* m_pDlg;

protected:
	virtual void OnReceive(int nErrorCode);

	
};


