// SaveDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HorseRace.h"
#include "SaveDlg.h"
#include "afxdialogex.h"
#include "NetVerification.h"

extern SaveMoney				chong ;
// CSaveDlg �Ի���

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


// CSaveDlg ��Ϣ�������


void CSaveDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	int nRet = chong((TCHAR*)m_UserName.GetString(),(TCHAR*)m_Key.GetString());
	CString strRet;
	switch(nRet)
	{
	case  6:
		{
			strRet.Format(_T("��ֵ�ɹ�"));
		}break;
	case 5:
		{
			strRet.Format(_T("�ǰ󶨻���"));
		}break;
	case 4:
		{
			strRet.Format(_T("�û�������"));
		}break;
	case 3:
		{
			strRet.Format(_T("Key ��ʹ��"));
		}break;
	case 2:
		{
			strRet.Format(_T("key������"));
		}break;
	case 1:
		{
			strRet.Format(_T("��ֵʧ��"));
		}break;
	default:
		{
			strRet.Format(_T("δ֪����"));
		}break;
	}
	MessageBox(strRet);
}
