#pragma once


// CRegisterUser �Ի���

class CRegisterUser : public CDialogEx
{
	DECLARE_DYNAMIC(CRegisterUser)

public:
	CRegisterUser(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRegisterUser();

// �Ի�������
	enum { IDD = IDD_DIALOG_REG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_userName;
	CString m_Pwd;
	CString m_pwd2;
	CString m_phone;
	afx_msg void OnBnClickedButton1();
};
