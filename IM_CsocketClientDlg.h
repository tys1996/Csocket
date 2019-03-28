
// IM_CsocketClientDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "CSocket.h"

class CCSocket;

// CIM_CsocketClientDlg 对话框
class CIM_CsocketClientDlg : public CDialogEx
{
// 构造
public:
	CIM_CsocketClientDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IM_CSOCKETCLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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

	void OnReceive();//接收信息
	void ReceiveMsg();//接收服务发来的数据
	void SendMsg(CString& strText, bool st);//向服务器发送数据
	void OnDestroy();//终止运行时进行的后续处理
	//指针对象
	CCSocket* m_pSocket;
	CSocketFile* m_pFile;
	CArchive* m_pArchiveIn;//输入
	CArchive* m_pArchiveOut;
};
