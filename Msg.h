#pragma once

// CMsg ÃüÁîÄ¿±ê

class CMsg : public CObject
{
public:
	CMsg();
	virtual ~CMsg();
	CString m_strBuf;
	BOOL m_bClose;
	virtual void Serialize(CArchive& ar);
};


