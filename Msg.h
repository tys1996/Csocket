#pragma once

// CMsg ����Ŀ��

class CMsg : public CObject
{
	DECLARE_DYNAMIC(CMsg);//��̬������

public:
	CMsg();
	virtual ~CMsg();
	CString m_strBuf;//�ַ�����Ա
	BOOL m_bClose;//�Ƿ�ر�״̬
	virtual void Serialize(CArchive& ar);//���л�����
};


