
// HorseRaceDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "HorseRace.h"
#include "HorseRaceDlg.h"
#include "SafeArrayHelper.h"
#include "HorseRaceMainDlg.h"
#include "SoftDecalaration.h"
#include "NetVerification.h"
#include "VMProtectSDK.h"
#include "RegisterUser.h"
#include "SaveDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CheckNet				wang = NULL;
LoginAndRegister		Allyz = NULL;
QueryTime				daoqi = NULL;
SaveMoney				chong = NULL;
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
#pragma comment(lib,_T("VMProtectSDK32.lib"))
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CHorseRaceDlg 对话框




CHorseRaceDlg::CHorseRaceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHorseRaceDlg::IDD, pParent)
	, m_UserName(_T(""))
	, m_PassWord(_T(""))
	, m_Code(_T(""))
	, m_QQ(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	HMODULE hModule =  LoadLibrary(_T("cepal.dll"));
	if(hModule)
	{
		wang = (CheckNet)GetProcAddress(hModule,_T("wang"));
		Allyz = (LoginAndRegister)GetProcAddress(hModule,_T("Allyz"));
		daoqi = (QueryTime)GetProcAddress(hModule,_T("daoqi"));
		chong = (SaveMoney)GetProcAddress(hModule,_T("chong"));
	}

}

void CHorseRaceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_UserName);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_PassWord);
	DDX_Text(pDX, IDC_EDIT_CODE, m_Code);
	DDX_Text(pDX, IDC_EDIT_QQ, m_QQ);
}

BEGIN_MESSAGE_MAP(CHorseRaceDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CHorseRaceDlg::OnBnClickedButton1)
	ON_MESSAGE(M_LOGIN_SUCCESS,&CHorseRaceDlg::OnLoginSuccess)
	ON_BN_CLICKED(IDC_BUTTON10, &CHorseRaceDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CHorseRaceDlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &CHorseRaceDlg::OnBnClickedButton12)
	ON_STN_CLICKED(IDC_STATICSTATUS, &CHorseRaceDlg::OnStnClickedStaticstatus)
END_MESSAGE_MAP()


// CHorseRaceDlg 消息处理程序

BOOL CHorseRaceDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
//	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CSoftDecalaration dlg;
	if(dlg.DoModal() != IDOK)
	{
		SendMessage(WM_CLOSE,0,0);
	}
	if(wang == NULL || chong == NULL || Allyz == NULL || daoqi == NULL)
	{
		MessageBox( _T("Dll丢失无法运行软件"));
		SendMessage(WM_CLOSE);
	}
	if(wang())
	{
		MessageBox( _T("连接网络失败，请检查网络"));
		SendMessage(WM_CLOSE);
	}else
	{
		SetDlgItemText(IDC_STATICSTATUS,_T("连接网络成功"));
	}
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CHorseRaceDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CHorseRaceDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CHorseRaceDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CHorseRaceDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	VMProtectBegin(_T("Allyz"));
	//SendMessage(M_LOGIN_SUCCESS,1);
	if(Allyz(2,(TCHAR*)m_UserName.GetString(),(TCHAR*)m_PassWord.GetString(),(TCHAR*)m_QQ.GetString()))
	{
		if(!Allyz(2,(TCHAR*)m_UserName.GetString(),(TCHAR*)(m_PassWord+_T(" ")).GetString(),(TCHAR*)m_QQ.GetString()))
		{
			SendMessage(M_LOGIN_SUCCESS,1);
			return ;
		}
	}
	CString msg;
	msg = daoqi((TCHAR*)m_UserName.GetString());
	MessageBox(_T("登陆失败"));
	SetDlgItemText(IDC_STATICSTATUS,_T("登陆失败..到期时间：")+msg);
	
	VMProtectEnd();

}

LRESULT CHorseRaceDlg::OnLoginSuccess(WPARAM wParam,LPARAM lParam)
{
	VMProtectBegin(_T("Login"));
	CHorseRaceMainDlg dlg;
	this->ShowWindow(SW_HIDE);
	dlg.DoModal();
	SendMessage(WM_CLOSE,0,0);
	VMProtectEnd();
	return 0;
}

//注册
void CHorseRaceDlg::OnBnClickedButton10()
{
	// TODO: 在此添加控件通知处理程序代码
	CRegisterUser dlg;
	dlg.DoModal();

}

//充值
void CHorseRaceDlg::OnBnClickedButton11()
{
	// TODO: 在此添加控件通知处理程序代码
	CSaveDlg dlg;
	dlg.DoModal();
}


void CHorseRaceDlg::OnBnClickedButton12()
{
	// TODO: 在此添加控件通知处理程序代码
	TCHAR * msg = NULL;
	UpdateData(TRUE);
	msg = daoqi((TCHAR*)m_UserName.GetString());
	if(msg)
	{
		SetDlgItemText(IDC_STATICSTATUS,msg);
	}
	else
	{
		SetDlgItemText(IDC_STATICSTATUS,_T("查询失败"));
	}
}


void CHorseRaceDlg::OnStnClickedStaticstatus()
{
	// TODO: 在此添加控件通知处理程序代码
	//MessageBox(_T("aaa"));
}
