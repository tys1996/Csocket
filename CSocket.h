#pragma once
#include "IM_CsocketClientDlg.h"

// CCSocket ����Ŀ��

class CIM_CsocketClientDlg;//�Ի����������

class CCSocket : public CSocket
{
	DECLARE_DYNAMIC(CCSocket);//��̬�������
public:
	CCSocket(CIM_CsocketClientDlg* pDlg);//������ڲ���
	virtual ~CCSocket();
	CIM_CsocketClientDlg* m_pDlg;

protected:
	virtual void OnReceive(int nErrorCode);

	
};


