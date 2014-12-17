// SaveDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "HorseRace.h"
#include "SaveDlg.h"
#include "afxdialogex.h"
#include "NetVerification.h"

extern SaveMoney				chong ;
// CSaveDlg 对话框

IMPLEMENT_DYNAMIC(CSaveDlg, CDialogEx)

CSaveDlg::CSaveDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSaveDlg::IDD, pParent)
	, m_UserName(_T(""))
	, m_Key(_T(""))
{

}

CSaveDlg::~CSaveDlg()
{
}

void CSaveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_UserName);
	DDX_Text(pDX, IDC_EDIT4, m_Key);
}


BEGIN_MESSAGE_MAP(CSaveDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CSaveDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CSaveDlg 消息处理程序


void CSaveDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int nRet = chong((TCHAR*)m_UserName.GetString(),(TCHAR*)m_Key.GetString());
	CString strRet;
	switch(nRet)
	{
	case  6:
		{
			strRet.Format(_T("充值成功"));
		}break;
	case 5:
		{
			strRet.Format(_T("非绑定机器"));
		}break;
	case 4:
		{
			strRet.Format(_T("用户不存在"));
		}break;
	case 3:
		{
			strRet.Format(_T("Key 已使用"));
		}break;
	case 2:
		{
			strRet.Format(_T("key不存在"));
		}break;
	case 1:
		{
			strRet.Format(_T("充值失败"));
		}break;
	default:
		{
			strRet.Format(_T("未知错误"));
		}break;
	}
	MessageBox(strRet);
}
