
// IM_CsocketClientDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "CSocket.h"

class CCSocket;

// CIM_CsocketClientDlg �Ի���
class CIM_CsocketClientDlg : public CDialogEx
{
// ����
public:
	CIM_CsocketClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IM_CSOCKETCLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_strCName;
	CString m_strSName;
	CString m_strMsg;
	int m_nPort;
	CButton m_btnConn;
	CButton m_btnClose;
	CListBox m_listMsg;
	CButton m_Send;
	//afx_msg void OnEnChangeEditCname();
	afx_msg void OnSend();
	afx_msg void OnButtonConn();
	afx_msg void OnButtonClose();

	void OnReceive();//������Ϣ
	void ReceiveMsg();//���շ�����������
	void SendMsg(CString& strText, bool st);//���������������
	void OnDestroy();//��ֹ����ʱ���еĺ�������
	//ָ�����
	CCSocket* m_pSocket;
	CSocketFile* m_pFile;
	CArchive* m_pArchiveIn;//����
	CArchive* m_pArchiveOut;
};
