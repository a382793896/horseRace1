#pragma once

  
// CTabSheet
#define MAX_PAGES 10

class CTabSheet : public CTabCtrl
{
	DECLARE_DYNAMIC(CTabSheet)

public:
	CTabSheet();
	virtual ~CTabSheet();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult);
	BOOL AddPage(CString szTitle, CDialog * pDialog, UINT ID);
	void Show(UINT nIdx = 0);
	void SetRect(UINT nIdx);
public:
	UINT m_nNumOfPages;
	CDialog *m_pPages[MAX_PAGES];
	UINT m_IDD[MAX_PAGES];
	CString m_Title[MAX_PAGES];
	UINT m_nCurrentPage;
};


