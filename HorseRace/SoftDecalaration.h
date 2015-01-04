#pragma once

  
// CSoftDecalaration 对话框

class CSoftDecalaration : public CDialogEx
{
	DECLARE_DYNAMIC(CSoftDecalaration)

public:
	CSoftDecalaration(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSoftDecalaration();

// 对话框数据
	enum { IDD = IDD_DIALOG_TAB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton9();
};
