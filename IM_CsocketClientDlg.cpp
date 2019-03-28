
// IM_CsocketClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "IM_CsocketClient.h"
#include "IM_CsocketClientDlg.h"
#include "afxdialogex.h"
#include "Msg.h"
#include "CSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CIM_CsocketClientDlg �Ի���



CIM_CsocketClientDlg::CIM_CsocketClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_IM_CSOCKETCLIENT_DIALOG, pParent)
	//��ʼ������
	, m_strCName(_T(""))
	, m_strSName(_T(""))
	, m_strMsg(_T(""))
	, m_nPort(0)
	, m_pSocket(NULL)
	, m_pFile(NULL)
	, m_pArchiveIn(NULL)
	, m_pArchiveOut(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIM_CsocketClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CNAME, m_strCName);
	DDX_Text(pDX, IDC_EDIT_SNAME, m_strSName);
	DDX_Text(pDX, IDC_EDIT_MSG, m_strMsg);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPort);
	DDX_Control(pDX, IDC_BUTTON_CONN, m_btnConn);
	DDX_Control(pDX, IDC_BUTTON_CLOSE, m_btnClose);
	DDX_Control(pDX, IDC_LIST_MSG, m_listMsg);
	DDX_Control(pDX, IDOK, m_Send);
}

BEGIN_MESSAGE_MAP(CIM_CsocketClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_EN_CHANGE(IDC_EDIT_CNAME, &CIM_CsocketClientDlg::OnEnChangeEditCname)
	ON_BN_CLICKED(IDOK, &CIM_CsocketClientDlg::OnSend)
	ON_BN_CLICKED(IDC_BUTTON_CONN, &CIM_CsocketClientDlg::OnButtonConn)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CIM_CsocketClientDlg::OnButtonClose)
END_MESSAGE_MAP()


// CIM_CsocketClientDlg ��Ϣ�������

BOOL CIM_CsocketClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_strCName = "�ͻ�1";
	m_nPort = 8000;
	m_strSName = _T("localhost");
	GetDlgItem(IDC_EDIT_MSG)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(FALSE);
	UpdateData(FALSE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CIM_CsocketClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CIM_CsocketClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CIM_CsocketClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




//������ͣ�ִ�д˺������������������Ϣ
void CIM_CsocketClientDlg::OnSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
	UpdateData(TRUE);//ȡ���û��������Ϣ
	if (!m_strMsg.IsEmpty())
	{
		this->SendMsg(m_strCName + ":" + m_strMsg, FALSE);
		m_strMsg = _T("");
		UpdateData(FALSE);//�����û����棬���ͻ��������Ϣɾ��
	}
}

//��������ʱ��ִ�дκ��������������������
void CIM_CsocketClientDlg::OnButtonConn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_pSocket = new CCSocket(this);//�����׽��ֶ���
	if(!m_pSocket->Create())//�����׽��ֶ���ĵײ��׽���
	{
		delete m_pSocket;//������
		m_pSocket = NULL;
		AfxMessageBox(L"�׽��ִ�������");
		return;
	}
	if (!m_pSocket->Connect(m_strSName,m_nPort))
	{
		delete m_pSocket;//������
		m_pSocket = NULL;
		AfxMessageBox(L"�޷����ӷ���������");
		return;
	}
	//����CSocketFile�����
	m_pFile = new CSocketFile(m_pSocket);
	//�ֱ𴴽�������������������CArchive�����
	m_pArchiveIn = new CArchive(m_pFile, CArchive::load);
	m_pArchiveOut = new CArchive(m_pFile, CArchive::store);
	//����SenMsg�������������������Ϣ�������ÿͻ�������������
	UpdateData(TRUE);
	CString strTemp;
	strTemp = m_strCName + L"������������";
	SendMsg(strTemp, FALSE);
	GetDlgItem(IDC_EDIT_MSG)->EnableWindow(TRUE);
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(TRUE);

	GetDlgItem(IDC_EDIT_CNAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_SNAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_PORT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CONN)->EnableWindow(FALSE);
}

//�Ͽ�ʱִ�У����ͻ����˳������ҵ���ش���
void CIM_CsocketClientDlg::OnButtonClose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strTemp;
	strTemp = m_strCName + L":�뿪�����ң�";
	SendMsg(strTemp, TRUE);

	//ɾ����������롢�׽��ֶ���
	delete m_pArchiveOut;
	m_pArchiveOut = NULL;
	delete m_pArchiveIn;
	m_pArchiveIn = NULL;
	delete m_pFile;
	m_pFile = NULL;
	m_pSocket->Close();
	delete m_pSocket;
	m_pSocket = NULL;

	//����б��
	while (m_listMsg.GetCount() != 0)
	{
		m_listMsg.DeleteString(0);
	}
	//����б��
	GetDlgItem(IDC_EDIT_MSG)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(FALSE);

	GetDlgItem(IDC_EDIT_CNAME)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_SNAME)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_PORT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CONN)->EnableWindow(TRUE);
}

//���׽����յ�FD_READ��Ϣʱ��ִ��
void CIM_CsocketClientDlg::OnReceive()
{
	do {
		ReceiveMsg();
		if (m_pSocket == NULL)  return;
	} while (!m_pArchiveIn->IsBufferEmpty());
}

//ʵ�ʽ�����Ϣ�ĺ���
void CIM_CsocketClientDlg::ReceiveMsg()
{
	CMsg msg;
		TRY
	{
		//������Ϣ��������л�������������Ϣ
		msg.Serialize(*m_pArchiveIn);
		m_listMsg.AddString(msg.m_strBuf);//����Ϣ��ʾ���б��
	}
	CATCH(CFileException,e)//������
	{
		//��ʾ����������رյ���Ϣ
		CString strTemp;
		strTemp = L"�������������ӣ����ӹر�";
		m_listMsg.AddString(strTemp);
		msg.m_bClose = TRUE;
		m_pArchiveOut->Abort;
		//ɾ����Ӧ�Ķ���
		delete m_pArchiveIn;
		m_pArchiveIn = NULL;
		delete m_pArchiveOut;
		m_pArchiveOut = NULL;
		delete m_pFile;
		m_pFile = NULL;
		delete m_pSocket;
		m_pSocket = NULL;
	}
	END_CATCH
}

//ʵ��ִ�з��͵ĺ���
void CIM_CsocketClientDlg::SendMsg(CString& strText,bool st)
{
	if (m_pArchiveOut != NULL)
	{
		CMsg msg;//����һ����Ϣ����
		//��Ҫ���͵���Ϣ�ı�������Ϣ����ĳ�Ա����
		msg.m_strBuf = strText;
		msg.m_bClose = st;
		//������Ϣ�����ϵ�л�������������Ϣ
		msg.Serialize(*m_pArchiveOut);
		//��CArchive�����е�����ǿ�ƴ洢��CSocketFile������
		m_pArchiveOut->Flush();
	}
}

//�Ի�������ֹ���еĺ�������
void  CIM_CsocketClientDlg::OnDestroy()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnDestroy();
	
	if ((m_pSocket != NULL) && (m_pFile != NULL) && (m_pArchiveOut != NULL))
	{
		//���Ϳͻ����뿪�����ҵ���Ϣ
		CMsg msg;
		CString strTemp;
		strTemp = L"DDDD:�뿪�����ң�";
		msg.m_bClose = TRUE;
		msg.m_strBuf = m_strCName + strTemp;
		msg.Serialize(*m_pArchiveOut);
		m_pArchiveOut->Flush();
	}

	delete m_pArchiveOut;
	m_pArchiveOut = NULL;
	delete m_pArchiveIn;
	m_pArchiveIn = NULL;
	delete m_pFile;
	m_pFile = NULL;

	if(m_pSocket != NULL)
	{
		BYTE Buffer[50];
		m_pSocket->ShutDown();
		while (m_pSocket->Receive(Buffer, 50) > 0);
	}
	delete m_pSocket;
	m_pSocket = NULL;
}
