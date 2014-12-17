#pragma once


// CRegisterUser 对话框

class CRegisterUser : public CDialogEx
{
	DECLARE_DYNAMIC(CRegisterUser)

public:
	CRegisterUser(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRegisterUser();

// 对话框数据
	enum { IDD = IDD_DIALOG_REG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_userName;
	CString m_Pwd;
	CString m_pwd2;
	CString m_phone;
	afx_msg void OnBnClickedButton1();
};
