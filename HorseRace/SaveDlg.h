#pragma once


// CSaveDlg �Ի���

class CSaveDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSaveDlg)

public:
	CSaveDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSaveDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_SAVE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_UserName;
	CString m_Key;
	afx_msg void OnBnClickedButton1();
};
