#pragma once
#include "IM_CsocketClientDlg.h"

// CCSocket ����Ŀ��

class CIM_CsocketClientDlg;//�Ի����������

class CCSocket : public CSocket
{
public:
	CCSocket();
	virtual ~CCSocket();
	virtual void OnReceive(int nErrorCode);

	CIM_CsocketClientDlg* m_pDlg;
};


