// CSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "IM_CsocketClient.h"
#include "CSocket.h"
#include "IM_CsocketClientDlg.h"

IMPLEMENT_DYNAMIC(CCSocket,CSocket)//动态类声明

// CCSocket

CCSocket::CCSocket(CIM_CsocketClientDlg* pDlg)
{
	m_pDlg = pDlg;
}

CCSocket::~CCSocket()
{
}


// CCSocket 成员函数


void CCSocket::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	CSocket::OnReceive(nErrorCode);
	//调用对话框类的相应函数处理
	if (nErrorCode == 0) m_pDlg->OnReceive();
}
