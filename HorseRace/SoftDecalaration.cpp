// SoftDecalaration.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HorseRace.h"
#include "SoftDecalaration.h"
#include "afxdialogex.h"


// CSoftDecalaration �Ի���

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


// CSoftDecalaration ��Ϣ�������


void CSoftDecalaration::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	__super::OnOK();
}


BOOL CSoftDecalaration::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CString strContent;
	strContent.Format(_T("��Ӣ��ʦ�ǿ�������ߡ�\r\n\r\n�������ߵĶ��壺�Ը��������ϷΪĿ�ĵģ�ʵ�ָ��ӿ�ݷ��������Ϸ����Ҫ��Ϊ���ڵ���Ϸ����\r\n\r\n���ڸ��ӣ����ڵ�����ʹ������Ƕ�����Ҫ��ôһ��������������Ϸ���ù��߲������޸���Ϸ����\r\n\r\n������Ϸ���ܡ���������ڸ������ߣ��ϸ���ѭ�л����񹲺͹��������������������"));
	SetDlgItemText(IDC_EDIT1,strContent);
	strContent.Format(_T("һ����ʹ�ñ����������ʾ��Ը�����������Լ��\r\n\r\n1.��Ӧ�ö�ʹ�þ�Ӣ��ʦ�Ľ�����ге����գ������о�Ӣ��ʦ�������ֲ������ʱ����Ӣ��ʦ����Ų������಻�е��κη������Ρ�\r\n\r\n2.��Ӣ��ʦֻ��һ����Ϸ��������������ǰ�����Ҹ��ӿ�ݷ��������Ϸ���������ʹ�ù������紥�����ط��ɵȣ��ڱ����һ���޹أ���Ӣ��ʦ����Ų������಻�е��κη������Ρ�"));
	SetDlgItemText(IDC_EDIT4,strContent);
		return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CSoftDecalaration::OnBnClickedButton9()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	__super::OnCancel();
}
