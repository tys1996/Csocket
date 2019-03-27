#pragma once

// CMsg 命令目标

class CMsg : public CObject
{
	DECLARE_DYNAMIC(CMsg);//动态类声明

public:
	CMsg();
	virtual ~CMsg();
	CString m_strBuf;//字符串成员
	BOOL m_bClose;//是否关闭状态
	virtual void Serialize(CArchive& ar);//序列化函数
};


