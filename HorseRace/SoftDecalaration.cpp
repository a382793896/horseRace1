// SoftDecalaration.cpp : 实现文件
//

#include "stdafx.h"
#include "HorseRace.h"
#include "SoftDecalaration.h"
#include "afxdialogex.h"


// CSoftDecalaration 对话框

IMPLEMENT_DYNAMIC(CSoftDecalaration, CDialogEx)

CSoftDecalaration::CSoftDecalaration(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSoftDecalaration::IDD, pParent)
{

}

CSoftDecalaration::~CSoftDecalaration()
{
}

void CSoftDecalaration::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSoftDecalaration, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CSoftDecalaration::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON9, &CSoftDecalaration::OnBnClickedButton9)
END_MESSAGE_MAP()


// CSoftDecalaration 消息处理程序


void CSoftDecalaration::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	__super::OnOK();
}


BOOL CSoftDecalaration::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString strContent;
	strContent.Format(_T("精英大师是款纯辅助工具。\r\n\r\n辅助工具的定义：以辅助玩家游戏为目的的，实现更加快捷方便的玩游戏，主要因为现在的游戏操作\r\n\r\n过于复杂，过于单调，使用玩家们都想需要这么一款辅助软件来帮助游戏，该工具不具有修改游戏数据\r\n\r\n，损坏游戏功能。本软件属于辅助工具，严格遵循中华人民共和国《计算机保护条例》。"));
	SetDlgItemText(IDC_EDIT1,strContent);
	strContent.Format(_T("一旦您使用本软件，即表示您愿意接受以下条约。\r\n\r\n1.您应该对使用精英大师的结果自行承担风险，若运行精英大师软件后出现不良后果时，精英大师对其概不负责，亦不承担任何法律责任。\r\n\r\n2.精英大师只是一款游戏辅助软件，功能是帮助玩家更加快捷方便的玩游戏，对玩家在使用过程中如触犯当地法律等，于本软件一切无关，精英大师对其概不负责，亦不承担任何法律责任。"));
	SetDlgItemText(IDC_EDIT4,strContent);
		return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CSoftDecalaration::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	__super::OnCancel();
}
