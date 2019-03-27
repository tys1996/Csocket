// Msg.cpp : 实现文件
//

#include "stdafx.h"
#include "IM_CsocketClient.h"
#include "Msg.h"


// CMsg

CMsg::CMsg()
{//变量初始化
	m_strBuf = _T("");
	m_bClose = FALSE;
}

CMsg::~CMsg()
{
}


// CMsg 成员函数


void CMsg::Serialize(CArchive& ar)
{
	if (ar.IsStoring())//如果输出就发送数据
	{
		ar << (WORD)m_bClose;
		ar << m_strBuf;
	}
	else {//如果输入就接收数据
		WORD wd;
		ar >> wd;
		m_bClose = (BOOL)wd;
		ar >> m_strBuf;
	}
}
IMPLEMENT_DYNAMIC(CMsg,CObject)