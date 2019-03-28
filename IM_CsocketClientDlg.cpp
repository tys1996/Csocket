
// IM_CsocketClientDlg.cpp : 实现文件
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


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CIM_CsocketClientDlg 对话框



CIM_CsocketClientDlg::CIM_CsocketClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_IM_CSOCKETCLIENT_DIALOG, pParent)
	//初始化代码
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


// CIM_CsocketClientDlg 消息处理程序

BOOL CIM_CsocketClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_strCName = "客户1";
	m_nPort = 8000;
	m_strSName = _T("localhost");
	GetDlgItem(IDC_EDIT_MSG)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(FALSE);
	UpdateData(FALSE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CIM_CsocketClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CIM_CsocketClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




//点击发送，执行此函数，向服务器发送消息
void CIM_CsocketClientDlg::OnSend()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	UpdateData(TRUE);//取回用户输入的信息
	if (!m_strMsg.IsEmpty())
	{
		this->SendMsg(m_strCName + ":" + m_strMsg, FALSE);
		m_strMsg = _T("");
		UpdateData(FALSE);//更新用户界面，将客户输入的消息删除
	}
}

//单击连接时，执行次函数，向服务器请求连接
void CIM_CsocketClientDlg::OnButtonConn()
{
	// TODO: 在此添加控件通知处理程序代码
	m_pSocket = new CCSocket(this);//创建套接字对象
	if(!m_pSocket->Create())//创建套接字对象的底层套接字
	{
		delete m_pSocket;//错误处理
		m_pSocket = NULL;
		AfxMessageBox(L"套接字创建错误！");
		return;
	}
	if (!m_pSocket->Connect(m_strSName,m_nPort))
	{
		delete m_pSocket;//错误处理
		m_pSocket = NULL;
		AfxMessageBox(L"无法连接服务器错误！");
		return;
	}
	//创建CSocketFile类对象
	m_pFile = new CSocketFile(m_pSocket);
	//分别创建用于输入和用于输出的CArchive类对象
	m_pArchiveIn = new CArchive(m_pFile, CArchive::load);
	m_pArchiveOut = new CArchive(m_pFile, CArchive::store);
	//调用SenMsg函数，向服务器发送消息，表明该客户机进入聊天室
	UpdateData(TRUE);
	CString strTemp;
	strTemp = m_strCName + L"：进入聊天室";
	SendMsg(strTemp, FALSE);
	GetDlgItem(IDC_EDIT_MSG)->EnableWindow(TRUE);
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(TRUE);

	GetDlgItem(IDC_EDIT_CNAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_SNAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_PORT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CONN)->EnableWindow(FALSE);
}

//断开时执行，做客户机退出聊天室的相关处理
void CIM_CsocketClientDlg::OnButtonClose()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strTemp;
	strTemp = m_strCName + L":离开聊天室！";
	SendMsg(strTemp, TRUE);

	//删除输出、输入、套接字对象
	delete m_pArchiveOut;
	m_pArchiveOut = NULL;
	delete m_pArchiveIn;
	m_pArchiveIn = NULL;
	delete m_pFile;
	m_pFile = NULL;
	m_pSocket->Close();
	delete m_pSocket;
	m_pSocket = NULL;

	//清楚列表框
	while (m_listMsg.GetCount() != 0)
	{
		m_listMsg.DeleteString(0);
	}
	//清楚列表框
	GetDlgItem(IDC_EDIT_MSG)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(FALSE);

	GetDlgItem(IDC_EDIT_CNAME)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_SNAME)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_PORT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CONN)->EnableWindow(TRUE);
}

//当套接字收到FD_READ消息时，执行
void CIM_CsocketClientDlg::OnReceive()
{
	do {
		ReceiveMsg();
		if (m_pSocket == NULL)  return;
	} while (!m_pArchiveIn->IsBufferEmpty());
}

//实际接收消息的函数
void CIM_CsocketClientDlg::ReceiveMsg()
{
	CMsg msg;
		TRY
	{
		//调用消息对象的序列化函数，接收消息
		msg.Serialize(*m_pArchiveIn);
		m_listMsg.AddString(msg.m_strBuf);//将消息显示于列表框
	}
	CATCH(CFileException,e)//错误处理
	{
		//显示处理服务器关闭的消息
		CString strTemp;
		strTemp = L"服务器重置连接，连接关闭";
		m_listMsg.AddString(strTemp);
		msg.m_bClose = TRUE;
		m_pArchiveOut->Abort;
		//删除相应的对象
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

//实际执行发送的函数
void CIM_CsocketClientDlg::SendMsg(CString& strText,bool st)
{
	if (m_pArchiveOut != NULL)
	{
		CMsg msg;//创建一个消息对象
		//将要发送的信息文本赋给消息对象的成员变量
		msg.m_strBuf = strText;
		msg.m_bClose = st;
		//调用消息对象的系列化函数，发送消息
		msg.Serialize(*m_pArchiveOut);
		//将CArchive对象中的数据强制存储到CSocketFile对象中
		m_pArchiveOut->Flush();
	}
}

//对话框类终止运行的后续处理
void  CIM_CsocketClientDlg::OnDestroy()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnDestroy();
	
	if ((m_pSocket != NULL) && (m_pFile != NULL) && (m_pArchiveOut != NULL))
	{
		//发送客户机离开聊天室的消息
		CMsg msg;
		CString strTemp;
		strTemp = L"DDDD:离开聊天室！";
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
