
// HorseRaceDlg.h : 头文件
//

#pragma once
#include "ScriptObject.h"
#include "Http.h"
#include "afxwin.h"

// CHorseRaceDlg 对话框

#define  M_LOGIN_SUCCESS		(WM_USER + 1000)
class CHorseRaceDlg : public CDialog
{
// 构造
public:
	CHorseRaceDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_HORSERACE_LOGIN };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

private:

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void Execute();
	CString m_UserName;
	CString m_PassWord;
	CString m_Code;
	afx_msg void OnBnClickedButton1();
	afx_msg LRESULT OnLoginSuccess(WPARAM wParam,LPARAM lParam);
	CString m_QQ;
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnStnClickedStaticstatus();
};
