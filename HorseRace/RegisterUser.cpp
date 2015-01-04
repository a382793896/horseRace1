// RegisterUser.cpp : 实现文件
//
  
#include "stdafx.h"
#include "HorseRace.h"
#include "RegisterUser.h"
#include "afxdialogex.h"
#include "NetVerification.h"

extern LoginAndRegister		Allyz;
// CRegisterUser 对话框

IMPLEMENT_DYNAMIC(CRegisterUser, CDialogEx)

CRegisterUser::CRegisterUser(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRegisterUser::IDD, pParent)
	, m_userName(_T(""))
	, m_Pwd(_T(""))
	, m_pwd2(_T(""))
	, m_phone(_T(""))
{

}

CRegisterUser::~CRegisterUser()
{
}

void CRegisterUser::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_userName);
	DDX_Text(pDX, IDC_EDIT4, m_Pwd);
	DDX_Text(pDX, IDC_EDIT5, m_pwd2);
	DDX_Text(pDX, IDC_EDIT9, m_phone);
}


BEGIN_MESSAGE_MAP(CRegisterUser, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CRegisterUser::OnBnClickedButton1)
END_MESSAGE_MAP()


// CRegisterUser 消息处理程序


void CRegisterUser::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(m_phone.GetLength() < 7 )
	{
		MessageBox(_T("注册失败,手机号长度必须大于6"));
		return ;
	}
	if(m_userName.GetLength() < 7)
	{
		MessageBox(_T("注册失败，用户名长度必须大于6"));
		return ;
	}
	if(m_Pwd.GetLength() < 7)
	{
		MessageBox(_T("注册失败，密码长度必须大于6"));
		return ;
	}
	if(m_pwd2.Compare(m_Pwd) !=0)
	{
		MessageBox(_T("两次密码输入不相同"));
		return ;
	}
	if(Allyz(1,(TCHAR*)m_userName.GetString(),(TCHAR*)m_pwd2.GetString(),(TCHAR*)m_phone.GetString()))
	{
		MessageBox(_T("注册成功"));
	}
	else
	{

		MessageBox(_T("注册失败"));
	}
}
