
// HorseRaceDlg.h : ͷ�ļ�
//

#pragma once
#include "ScriptObject.h"
#include "Http.h"
#include "afxwin.h"

// CHorseRaceDlg �Ի���

#define  M_LOGIN_SUCCESS		(WM_USER + 1000)
class CHorseRaceDlg : public CDialog
{
// ����
public:
	CHorseRaceDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_HORSERACE_LOGIN };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

private:

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
