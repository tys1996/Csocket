// CSocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "IM_CsocketClient.h"
#include "CSocket.h"
#include "IM_CsocketClientDlg.h"

IMPLEMENT_DYNAMIC(CCSocket,CSocket)//��̬������

// CCSocket

CCSocket::CCSocket(CIM_CsocketClientDlg* pDlg)
{
	m_pDlg = pDlg;
}

CCSocket::~CCSocket()
{
}


// CCSocket ��Ա����


void CCSocket::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���

	CSocket::OnReceive(nErrorCode);
	//���öԻ��������Ӧ��������
	if (nErrorCode == 0) m_pDlg->OnReceive();
}
