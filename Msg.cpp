// Msg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "IM_CsocketClient.h"
#include "Msg.h"


// CMsg

CMsg::CMsg()
{//������ʼ��
	m_strBuf = _T("");
	m_bClose = FALSE;
}

CMsg::~CMsg()
{
}


// CMsg ��Ա����


void CMsg::Serialize(CArchive& ar)
{
	if (ar.IsStoring())//�������ͷ�������
	{
		ar << (WORD)m_bClose;
		ar << m_strBuf;
	}
	else {//�������ͽ�������
		WORD wd;
		ar >> wd;
		m_bClose = (BOOL)wd;
		ar >> m_strBuf;
	}
}
IMPLEMENT_DYNAMIC(CMsg,CObject)