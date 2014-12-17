#pragma once
#include "HttpHandule.h"
#include "afxcmn.h"
#include "afxwin.h"



// CHorseRaceMainDlg 对话框

class CHorseRaceMainDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHorseRaceMainDlg)

public:
	CHorseRaceMainDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CHorseRaceMainDlg();

// 对话框数据
	enum { IDD = IDD_HORSERACE_MAIN };
private:

	CImage* m_ImgCode;
	bool m_bInit;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CHttpHandule m_HttpHandule; 	
	CString m_TradeRace,m_RcordRace;
public:
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	

	afx_msg void OnPaint();
	void  RefreshTradeRcord();
	afx_msg void OnBnClickedButton2();
	void RefreshQData();
	CString m_UserName;
	CString m_PassWord;
	CString m_Code;
	CString m_PinCode;
	CListCtrl m_ListQ[4];
	HANDLE m_hThread,m_hThreadTrade;
	BOOL m_bThreadExit,m_bLogined,m_bTradeRecord,m_bStopOneKey,m_bStopQTrade,m_bStopQpTrade;
	std::list<TRADE_DATA> m_list_condition;
	std::list<TRADE_DATA> m_list_trade_record[2];
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	void RefreshTime();//刷新时间，
	bool IsExist(int nQ,int nIndex,std::list<QDATA> * q_list );
	void RefreshTradeRecord();//刷新交易记录
	bool m_bDown;
	CListCtrl m_TradeRecord;
	static DWORD WINAPI ThreadProc(
		_In_  LPVOID lpParameter
		);
	static DWORD WINAPI ThreadQTrade(
		_In_  LPVOID lpParameter
		);
	static DWORD WINAPI ThreadQpTrade(
		_In_  LPVOID lpParameter
		);
	static DWORD WINAPI ThreadInit(
		_In_  LPVOID lpParameter
		);
	afx_msg void OnBnClickedButton5();
	afx_msg void OnClose();
	bool InitNet();
	bool RefreshAllData();
	afx_msg void OnNMRClickListQ3(NMHDR *pNMHDR, LRESULT *pResult);
	void ReadConfig();
	bool QTrade();
	void AddTradeRecord(int nQ,TRADE_DATA & record);
	int UpdateTradeTicket(int nQ,TRADE_DATA & szItem);
	afx_msg void OnBnClickedButton8();
	void SetCurStastua(CString msg);
	void UserLogin();
	afx_msg void OnBnClickedButton6();
	bool QpTrade();
	CButton m_Qcheck;
	CButton m_QpCheck;
	afx_msg void OnBnClickedButton13();
	afx_msg void OnCbnSelchangeCombo2();
	CButton m_DownStopCheck;
	int m_DownS;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	bool IsExsitCondition(int nQ,TRADE_DATA * szNode);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton7();
};
