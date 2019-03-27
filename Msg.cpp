// Msg.cpp : 实现文件
//

#include "stdafx.h"
#include "IM_CsocketClient.h"
#include "Msg.h"


// CMsg

CMsg::CMsg()
{
	m_strBuf = _T("");
}

CMsg::~CMsg()
{
}


// CMsg 成员函数


void CMsg::Serialize(CArchive& ar)
{
}
