
// HorseRaceDlg.cpp : ʵ���ļ�
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
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
#pragma comment(lib,_T("VMProtectSDK32.lib"))
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CHorseRaceDlg �Ի���




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


// CHorseRaceDlg ��Ϣ�������

BOOL CHorseRaceDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
//	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	CSoftDecalaration dlg;
	if(dlg.DoModal() != IDOK)
	{
		SendMessage(WM_CLOSE,0,0);
	}
	if(wang == NULL || chong == NULL || Allyz == NULL || daoqi == NULL)
	{
		MessageBox( _T("Dll��ʧ�޷��������"));
		SendMessage(WM_CLOSE);
	}
	if(wang())
	{
		MessageBox( _T("��������ʧ�ܣ���������"));
		SendMessage(WM_CLOSE);
	}else
	{
		SetDlgItemText(IDC_STATICSTATUS,_T("��������ɹ�"));
	}
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CHorseRaceDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CHorseRaceDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CHorseRaceDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	MessageBox(_T("��½ʧ��"));
	SetDlgItemText(IDC_STATICSTATUS,_T("��½ʧ��..����ʱ�䣺")+msg);
	
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

//ע��
void CHorseRaceDlg::OnBnClickedButton10()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CRegisterUser dlg;
	dlg.DoModal();

}

//��ֵ
void CHorseRaceDlg::OnBnClickedButton11()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CSaveDlg dlg;
	dlg.DoModal();
}


void CHorseRaceDlg::OnBnClickedButton12()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TCHAR * msg = NULL;
	UpdateData(TRUE);
	msg = daoqi((TCHAR*)m_UserName.GetString());
	if(msg)
	{
		SetDlgItemText(IDC_STATICSTATUS,msg);
	}
	else
	{
		SetDlgItemText(IDC_STATICSTATUS,_T("��ѯʧ��"));
	}
}


void CHorseRaceDlg::OnStnClickedStaticstatus()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//MessageBox(_T("aaa"));
}
