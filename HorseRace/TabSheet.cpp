// TabSheet.cpp : implementation file
//

#include "stdafx.h"
#include "TabSheet.h"


// CTabSheet

IMPLEMENT_DYNAMIC(CTabSheet, CTabCtrl)

CTabSheet::CTabSheet()
{
	m_nNumOfPages = 0;
	m_nCurrentPage = 0;
}

CTabSheet::~CTabSheet()
{
}


BEGIN_MESSAGE_MAP(CTabSheet, CTabCtrl)
	ON_NOTIFY_REFLECT(TCN_SELCHANGE, &CTabSheet::OnTcnSelchange)
END_MESSAGE_MAP()



// CTabSheet message handlers



BOOL CTabSheet::AddPage(CString szTitle, CDialog * pDialog, UINT ID)
{
	if (MAX_PAGES == m_nNumOfPages){
		return FALSE;
	}
	m_nNumOfPages++;
	m_pPages[m_nNumOfPages-1] = pDialog;
	m_IDD[m_nNumOfPages-1] = ID;
	m_Title[m_nNumOfPages-1] = szTitle;

	return TRUE;
}

void CTabSheet::Show(UINT nIdx)
{
	ASSERT(nIdx < m_nNumOfPages);

	UINT idx = 0;
	for (idx = 0; idx < m_nNumOfPages; idx++){
		m_pPages[idx]->Create(m_IDD[idx], this);
		InsertItem(idx, m_Title[idx]);
	}
	SetRect(nIdx);
	SetCurFocus(nIdx);
}

void CTabSheet::SetRect(UINT nIdx)
{
	CRect tabRect, itemRect;
	int nX = 0, nY = 0, nXc = 0, nYc = 0;
	UINT nCount = 0;

	GetClientRect(&tabRect);
	GetItemRect(0, &itemRect);
	nX = itemRect.left;
	nY = itemRect.bottom + 1;
	nXc = tabRect.right - itemRect.left - 2;
	nYc = tabRect.bottom - nY - 2;

	for (nCount = 0; nCount < m_nNumOfPages; nCount++){
		if ( nCount == nIdx ) {
			m_pPages[nCount]->SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_SHOWWINDOW);
		}else{
			m_pPages[nCount]->SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_HIDEWINDOW);
		}
	}
}

void CTabSheet::OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (m_nCurrentPage != GetCurFocus()){
		m_pPages[m_nCurrentPage]->ShowWindow(SW_HIDE);
		m_nCurrentPage = GetCurFocus();
		m_pPages[m_nCurrentPage]->ShowWindow(SW_SHOW);
	}

	*pResult = 0;
}
