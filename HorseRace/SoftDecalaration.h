#pragma once

  
// CSoftDecalaration �Ի���

class CSoftDecalaration : public CDialogEx
{
	DECLARE_DYNAMIC(CSoftDecalaration)

public:
	CSoftDecalaration(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSoftDecalaration();

// �Ի�������
	enum { IDD = IDD_DIALOG_TAB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton9();
};
