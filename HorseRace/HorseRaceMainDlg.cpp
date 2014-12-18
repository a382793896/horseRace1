// HorseRaceMainDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HorseRace.h"
#include "HorseRaceMainDlg.h"
#include "afxdialogex.h"



// CHorseRaceMainDlg �Ի���

IMPLEMENT_DYNAMIC(CHorseRaceMainDlg, CDialogEx)

	CHorseRaceMainDlg::CHorseRaceMainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHorseRaceMainDlg::IDD, pParent)
	, m_UserName(_T(""))
	, m_PassWord(_T(""))
	, m_Code(_T(""))
	, m_PinCode(_T(""))
	//, m_UserName(_T("8602hp"))
	//, m_PassWord(_T("aabb778899="))
	//, m_Code(_T(""))
	//, m_PinCode(_T("778899"))
	, m_DownS(0)
{
	m_bDown = false;
	m_ImgCode = NULL;
	m_bStopQTrade = TRUE;
	m_bStopQpTrade = TRUE;
	m_bStopOneKey = TRUE;
	//m_UserName = _T("8607hp");
	//m_PassWord = _T("aabb112233,,");
	//m_PinCode = _T("112233");
}

CHorseRaceMainDlg::~CHorseRaceMainDlg()
{
}

void CHorseRaceMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_UserName);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_PassWord);
	DDX_Text(pDX, IDC_EDIT_CODE, m_Code);
	DDX_Text(pDX, IDC_EDIT_PIN, m_PinCode);
	DDX_Control(pDX, IDC_LIST_Q1, m_ListQ[0]);
	DDX_Control(pDX, IDC_LIST_Q4, m_ListQ[1]);
	DDX_Control(pDX, IDC_LIST_Q2, m_TradeRecord);

	DDX_Control(pDX, IDC_CHECK1, m_Qcheck);
	DDX_Control(pDX, IDC_CHECK2, m_QpCheck);
	DDX_Control(pDX, IDC_CHECK3, m_DownStopCheck);
	DDX_Text(pDX, IDC_EDIT8, m_DownS);
}


BEGIN_MESSAGE_MAP(CHorseRaceMainDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CHorseRaceMainDlg::OnBnClickedButton1)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON2, &CHorseRaceMainDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CHorseRaceMainDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CHorseRaceMainDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CHorseRaceMainDlg::OnBnClickedButton5)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON8, &CHorseRaceMainDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON6, &CHorseRaceMainDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON13, &CHorseRaceMainDlg::OnBnClickedButton13)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CHorseRaceMainDlg::OnCbnSelchangeCombo2)
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON14, &CHorseRaceMainDlg::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON7, &CHorseRaceMainDlg::OnBnClickedButton7)
END_MESSAGE_MAP()


// CHorseRaceMainDlg ��Ϣ�������

//��¼
void CHorseRaceMainDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	UserLogin();
	//CloseHandle(CreateThread(NULL,NULL,ThreadLoin,this,NULL,NULL));
	return;
}
void CHorseRaceMainDlg::UserLogin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	if(m_HttpHandule.Login(m_UserName,m_PassWord,m_Code,m_PinCode))
	{
		//MessageBox(_T("��½�ɹ�"));
		m_bLogined = TRUE;
		GetDlgItem(IDC_BUTTON5)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON8)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
	}
	else
	{
		MessageBox(_T("��½ʧ��"));
		GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
		CloseHandle(CreateThread(NULL,NULL,ThreadInit,this,NULL,NULL));
	}
	return;
}
void CHorseRaceMainDlg::RefreshQData()
{
	int nSize;
	for (int i = 0; i < 2 ; ++i)
	{
		std::list<QDATA> *  list_data = m_HttpHandule.GetQData(i+1);
		CString tem;
		if(list_data) 
		{
			if(!m_bInit)
			{
				nSize = list_data->size();
				for (int j = 0; j< nSize;++j)
				{
					tem.Format(_T("%d"),list_data->front().race);
					m_ListQ[i].InsertItem(j,tem);

					tem.Format(_T("%d-%d"),list_data->front().horse1,list_data->front().horse2);
					m_ListQ[i].SetItemText(j,1,tem);

					tem.Format(_T("%d"),list_data->front().ticket);
					m_ListQ[i].SetItemText(j,2,tem);

					tem.Format(_T("%d"),list_data->front().amount);
					m_ListQ[i].SetItemText(j,3,tem);

					tem.Format(_T("%d"),list_data->front().limit);
					m_ListQ[i].SetItemText(j,4,tem);

					list_data->pop_front();
				}
			}else
			{
				nSize = m_ListQ[i].GetItemCount();
				//m_ListQ1.DeleteAllItems()
				for (int j = 0; j< nSize;++j)
				{

					if(!IsExist(i,j,list_data))//�����µ������У�
					{
						m_ListQ[i].DeleteItem(j);
						--j;
						--nSize;
					}
					else//�����µ����ݣ���ô���޸�
					{
						tem.Format(_T("%d"),list_data->front().race);
						m_ListQ[i].SetItemText(j,0,tem);

						tem.Format(_T("%d-%d"),list_data->front().horse1,list_data->front().horse2);
						m_ListQ[i].SetItemText(j,1,tem);

						tem.Format(_T("%d"),list_data->front().ticket);
						m_ListQ[i].SetItemText(j,2,tem);

						tem.Format(_T("%d"),list_data->front().amount);
						m_ListQ[i].SetItemText(j,3,tem);

						tem.Format(_T("%d"),list_data->front().limit);
						m_ListQ[i].SetItemText(j,4,tem);

						list_data->pop_front();
					}

				}
				nSize = list_data->size();
				for (int j = 0; j< nSize;++j)
				{
					int nTem = m_ListQ[i].GetItemCount();
					tem.Format(_T("%d"),list_data->front().race);
					m_ListQ[i].InsertItem(nTem,tem);

					tem.Format(_T("%d-%d"),list_data->front().horse1,list_data->front().horse2);
					m_ListQ[i].SetItemText(nTem,1,tem);

					tem.Format(_T("%d"),list_data->front().ticket);
					m_ListQ[i].SetItemText(nTem,2,tem);

					tem.Format(_T("%d"),list_data->front().amount);
					m_ListQ[i].SetItemText(nTem,3,tem);

					tem.Format(_T("%d"),list_data->front().limit);
					m_ListQ[i].SetItemText(nTem,4,tem);

					list_data->pop_front();
				}
			}

		}

	}

	m_bInit = true;

}
bool CHorseRaceMainDlg::IsExist(int nQ,int nIndex,std::list<QDATA> * q_list )
{
	std::list<QDATA>::iterator iter;	
	for ( iter = q_list->begin(); iter != q_list->end(); ++iter)
	{
		CString tem =  m_ListQ[nQ].GetItemText(nIndex,0);
		if(iter->race == atoi(tem))//�����
		{
			tem =  m_ListQ[nQ].GetItemText(nIndex,1);
			CString tem2;
			tem2.Format(_T("%d-%d"),iter->horse1,iter->horse2);
			if(tem.Compare(tem2) == 0)//�����
			{
				tem =  m_ListQ[nQ].GetItemText(nIndex,3);
				if(iter->amount == atoi(tem))//�ۿ�
				{
					tem =  m_ListQ[nQ].GetItemText(nIndex,4);
					if(iter->limit == atoi(tem))
					{
						return true;
					}
					continue;
				}
				continue;
			}
			continue;
		}
	}
	return false;
}
BOOL CHorseRaceMainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	for (int i = 0 ; i < 2; ++i)
	{
		m_ListQ[i].InsertColumn(0,_T("��"),LVCFMT_CENTER,30);
		m_ListQ[i].InsertColumn(1,_T("��"),LVCFMT_CENTER,40);
		m_ListQ[i].InsertColumn(2,_T("Ʊ��"),LVCFMT_CENTER,60);
		m_ListQ[i].InsertColumn(3,_T("%"),LVCFMT_CENTER,40);
		m_ListQ[i].InsertColumn(4,_T("�޶�"),LVCFMT_CENTER,60);

		DWORD dwStyle = m_ListQ[i].GetExtendedStyle();

		dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
		dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��

		m_ListQ[i].SetExtendedStyle(dwStyle); //������չ���
	}

	m_TradeRecord.InsertColumn(0,_T("��"),LVCFMT_CENTER,80);
	m_TradeRecord.InsertColumn(1,_T("��"),LVCFMT_CENTER,80);
	m_TradeRecord.InsertColumn(2,_T("Ʊ��%"),LVCFMT_CENTER,80);
	m_TradeRecord.InsertColumn(3,_T("%"),LVCFMT_CENTER,80);
	m_TradeRecord.InsertColumn(4,_T("�޶�"),LVCFMT_CENTER,80);
	m_TradeRecord.InsertColumn(5,_T("��ʽ"),LVCFMT_CENTER,80);

	DWORD dwStyle = m_TradeRecord.GetExtendedStyle();

	dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
	dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��

	m_TradeRecord.SetExtendedStyle(dwStyle); //������չ���


	((CComboBox*)(GetDlgItem(IDC_COMBO1)))->SetCurSel(0);
	((CComboBox*)(GetDlgItem(IDC_COMBO2)))->SetCurSel(0);
	m_Qcheck.SetCheck(BST_CHECKED);
	m_QpCheck.SetCheck(BST_CHECKED);
	m_HttpHandule.SetParentHwnd(this);
	m_bInit = false;
	m_bLogined = FALSE;
	m_bThreadExit = FALSE;
	m_bTradeRecord = FALSE;
	m_bStopOneKey = TRUE;
	m_hThread =  CreateThread(NULL,NULL,ThreadProc,this,NULL,NULL);
	m_hThreadTrade =  CreateThread(NULL,NULL,ThreadQTrade,this,NULL,NULL);
	m_hThreadTrade =  CreateThread(NULL,NULL,ThreadQpTrade,this,NULL,NULL);
	CloseHandle(CreateThread(NULL,NULL,ThreadInit,this,NULL,NULL));
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CHorseRaceMainDlg::ReadConfig()
{

}

void CHorseRaceMainDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	//m_test.Draw(dc,0,0,m_test.GetWidth(),m_test.GetHeight(),0,0,m_test.GetWidth(),m_test.GetHeight());
	if(m_ImgCode)
	{
		CDC* codeDc = GetDlgItem(IDC_STATIC_CODE)->GetDC();
		if(codeDc != NULL)
			m_ImgCode->Draw(codeDc->GetSafeHdc(),0,0,m_ImgCode->GetWidth(),m_ImgCode->GetHeight());
		GetDlgItem(IDC_STATIC_CODE)->SetWindowPos(&CWnd::wndTop,0,0,m_ImgCode->GetWidth(),m_ImgCode->GetHeight(),SWP_NOMOVE|SWP_NOZORDER);
	}

}

//ˢ�½��׼�¼
void CHorseRaceMainDlg::RefreshTradeRcord()
{

}
//ˢ����֤��
void CHorseRaceMainDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//m_code =  m_http.GetImg(m_Host+_T("img.jpg?0.5589080715097631"));



	m_ImgCode = m_HttpHandule.GetCodeImage();
	if(m_ImgCode)
	{
		CDC* codeDc = GetDlgItem(IDC_STATIC_CODE)->GetDC();
		if(codeDc != NULL)
			m_ImgCode->Draw(codeDc->GetSafeHdc(),0,0,m_ImgCode->GetWidth(),m_ImgCode->GetHeight());
		if(!m_bThreadExit)
			GetDlgItem(IDC_STATIC_CODE)->SetWindowPos(&CWnd::wndTop,0,0,m_ImgCode->GetWidth(),m_ImgCode->GetHeight(),SWP_NOMOVE|SWP_NOZORDER);
	}
	else
	{
		MessageBox(_T("��֤���ȡʧ�ܡ�"));
	}
	Invalidate(FALSE);
	//RedrawWindow();
}

//ȷ�����׳���
void CHorseRaceMainDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CComboBox* pcombox = (CComboBox*)(GetDlgItem(IDC_COMBO2));
	pcombox->GetLBText(pcombox->GetCurSel(),m_TradeRace);
	TRACE(m_TradeRace);
	return ;
}
bool CHorseRaceMainDlg::RefreshAllData()
{
	RefreshQData();

	RefreshTime();
	return true;
}
void CHorseRaceMainDlg::RefreshTime()
{
	CString TemTime,TemRace;
	CString strWin;
	std::list<TRADE_DATA>* list_data = NULL;
	list_data = m_HttpHandule.GetTimeData(TemTime,m_TradeRace,strWin,TemRace);

	if(TemTime.IsEmpty())
	{
		GetDlgItem(IDC_STATIC_TIME)->SetWindowText(TemTime+_T("ˢ��ʱ��ʧ��"));
	}
	else
	{
		CString strRc;
		
		GetDlgItem(IDC_STATIC_TIME)->SetWindowText(TemRace+ _T("   ") + TemTime+_T("���Ӻ���"));
			if( (m_DownS == atoi(TemTime) &&  m_bDown ) || atoi(TemTime) ==0)
			{
				OnBnClickedButton13();
			}
	}

	//�ҵ���Ӯ
	if(strWin.IsEmpty())
	{
		GetDlgItem(IDC_STATIC_WINNING)->SetWindowText(_T("��ȡʧ��"));
	}
	else
	{
		GetDlgItem(IDC_STATIC_WINNING)->SetWindowText(_T("HK")+strWin);
	}

	if(list_data)
	{
		std::list<TRADE_DATA>::iterator iter;
		for (std::list<TRADE_DATA>::iterator iter2 = m_list_trade_record[2].begin() ; iter2 != m_list_trade_record[2].end(); ++iter2)
		{
			for(iter = list_data->begin(); iter != list_data->end(); ++iter);
			{
				if(iter2->race.Compare(iter->race) == 0 && iter->horse.Compare (iter2->horse + _T("-") + iter2->horse2) == 0 )
				{
					
					m_list_trade_record[0].push_back(*iter2);
					m_list_trade_record[2].erase(iter2);
				}
			}
		}
	}
	

	
	CString tem;
	if(!m_bTradeRecord)
	{
		if(list_data)
		{
			int nSize = list_data->size();
			int i = 0,j = 0; 
			m_TradeRecord.DeleteAllItems();
			//m_list_trade_record.clear();
			for (i = 0,j = 0 ; i < nSize ; ++i)
			{
				if(!m_RcordRace.IsEmpty() && m_RcordRace.Compare(_T("ÿ��")) != 0 && m_RcordRace.Compare(list_data->front().race) != 0)
				{
					list_data->pop_front();
					continue;
				}

				m_TradeRecord.InsertItem(j,list_data->front().race);

				m_TradeRecord.SetItemText(j,1,list_data->front().horse);

				m_TradeRecord.SetItemText(j,2,list_data->front().ticket);

				m_TradeRecord.SetItemText(j,3,list_data->front().amount);

				m_TradeRecord.SetItemText(j,4,list_data->front().limit);

				m_TradeRecord.SetItemText(j,5,list_data->front().TradeType);
				if(!list_data->front().TradeTicket.IsEmpty())//��Ϊ�ղ���������ܶ�
				{
					++i;
					m_TradeRecord.InsertItem(++j,_T(""));
					m_TradeRecord.SetItemText(j,2,list_data->front().TradeTicket);
					++nSize;
				}
				//m_list_trade_record.push_back(list_data->front());//�õ����׼�¼
				++j;
				list_data->pop_front();
			}
			m_bTradeRecord = TRUE;
		}
	}
	else
	{
		if(list_data)
		{
			int nSize = list_data->size();
			int i = 0,j=0,n = 0; 
			int nCurSize = m_TradeRecord.GetItemCount();
			//m_list_trade_record.clear();
			for (i = 0,j = 0 ; i < nSize ; ++i)
			{
				//�ж�Ҫ��ʾ�ĳ���
				if(!m_RcordRace.IsEmpty() && m_RcordRace.Compare(_T("ÿ��")) != 0 && m_RcordRace.Compare(list_data->front().race) != 0)
				{
					list_data->pop_front();
					continue;
				}
				if(j < nCurSize )
				{
					m_TradeRecord.SetItemText(j,0,list_data->front().race);
				}
				else
				{
					m_TradeRecord.InsertItem(j,list_data->front().race);
					nCurSize++;
				}
				m_TradeRecord.SetItemText(j,1,list_data->front().horse);

				m_TradeRecord.SetItemText(j,2,list_data->front().ticket);

				m_TradeRecord.SetItemText(j,3,list_data->front().amount);

				m_TradeRecord.SetItemText(j,4,list_data->front().limit);

				m_TradeRecord.SetItemText(j,5,list_data->front().TradeType);
				if(!list_data->front().TradeTicket.IsEmpty())//��Ϊ�ղ���������ܶ�
				{

					++j;
					++i;
					if(j < nCurSize )
					for (n = 0 ; n < 6; ++n)
					{
						m_TradeRecord.SetItemText(j,n,_T(""));
					}
					else
					{
						m_TradeRecord.InsertItem(j,_T(""));
						nCurSize++;
					}
					m_TradeRecord.SetItemText(j,2,list_data->front().TradeTicket);
					++nSize;
				}
				//m_list_trade_record.push_back(list_data->front());//�õ����׼�¼
				++j;
				list_data->pop_front();
			}
		}
	}
}

//��ʼ������
void CHorseRaceMainDlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	InitNet();
}
bool CHorseRaceMainDlg::InitNet()
{
	SetCurStastua(_T("���ڳ�ʼ�����磬��ȴ�������"));

	if(!m_HttpHandule.InitLogin())
	{
		SetCurStastua(_T("��վ����ʧ�ܣ������´򿪱����"));
		return  false;
	}
	else
	{
		OnBnClickedButton2();
		GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);

		SetCurStastua(_T("��ʼ������ɹ������¼"));
	}
	return true;
}
void CHorseRaceMainDlg::RefreshTradeRecord()
{

}

//����һ������
void CHorseRaceMainDlg::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(!m_bLogined)
	{
		MessageBox(_T("�˲�����Ҫ�ȵ�¼"));
		return ;
	}
	if(m_TradeRace.IsEmpty())
	{
		MessageBox(_T("�����ý��׵ĳ��Σ����ȷ��"));
		return ;
	}
	
	if(m_bStopOneKey)
	{
		
		m_bStopQTrade = FALSE;
		m_bStopQpTrade = FALSE;
		m_bStopOneKey = FALSE;
		/*if(m_DownStopCheck.GetCheck() == BST_CHECKED)
		{
		SetTimer(100,1000,NULL);
		}*/
		GetDlgItem(IDC_BUTTON5)->EnableWindow(FALSE);//��ʼ���װ�ť   ʧЧ
		GetDlgItem(IDC_COMBO2)->EnableWindow(FALSE);
		SetCurStastua(_T("��ʼ�����õ���������ɨ�衣����"));
	}
}
//��ӮQ����
bool CHorseRaceMainDlg::QTrade()
{
	TRADE_DATA szCondition ;
	BOOL bFind = FALSE;
	TRADE_DATA TradeItem;
	CString tem,tem2;
	int nQ = 0;
	if(m_Qcheck.GetCheck() != BST_CHECKED)
		return false;
	GetDlgItem(IDC_EDIT1)->GetWindowText(szCondition.ticket);
	GetDlgItem(IDC_EDIT2)->GetWindowText(szCondition.amount);
	GetDlgItem(IDC_EDIT3)->GetWindowText(szCondition.limit);
	if(szCondition.ticket.IsEmpty() || szCondition.amount.IsEmpty() || szCondition.limit.IsEmpty())
	{
		SetCurStastua(_T("��ӮQ�������ò�ȫ������"));
		return false;
	}
	int i = 0,j = 0;

	for (i = 0 ; i < m_ListQ[nQ].GetItemCount() ; ++i)
	{
		tem =  m_ListQ[nQ].GetItemText(i,3);
		if(szCondition.amount.Compare(tem) == 0)//�ۿ�
		{
			tem =  m_ListQ[nQ].GetItemText(i,4);
			if(atoi(tem) <= atoi(szCondition.limit))//�޶�
			{
				tem =  m_ListQ[nQ].GetItemText(i,0);
				if(m_TradeRace.Compare(_T("ÿ��")) != 0)
				if(m_TradeRace.IsEmpty() || m_TradeRace.Compare(tem) != 0)
				{
					continue;
				}
					//���������ҵ���ITEM�����н��ס�
					//���浱ǰ���׵�Item��Ϣ
					if(m_bStopQTrade)
					{
							return true;//��Ҫֹͣ����
					}
					int pos1 = 0;
					tem =  m_ListQ[nQ].GetItemText(i,1);//��
					pos1 = tem.Find(_T("-"));
					TradeItem.horse = tem.Left(pos1);
					TradeItem.horse2 = tem.Right(tem.GetLength()-pos1-1);

					TradeItem.race =  m_ListQ[nQ].GetItemText(i,0);//��

					TradeItem.amount = m_ListQ[nQ].GetItemText(i,3);//%

					TradeItem.limit = m_ListQ[nQ].GetItemText(i,4);//�޶�

					TradeItem.ticket = szCondition.ticket;//Ҫ�Ե�Ʊ
					if(!IsExsitCondition(1,&TradeItem))
					{
						continue;
					}
					/*if(nQ == 1)
					{
					TradeItem.horse = _T("(") + TradeItem.horse;
					TradeItem.horse2 = TradeItem.horse2 + _T(")");
					}*/
					//�жϴ�Item�Ƿ��Ѿ����׹��ˣ�
					std::list<TRADE_DATA>::iterator iter;   
					for (iter = m_list_trade_record[2].begin();iter != m_list_trade_record[2].end() ; ++iter)
					{
						if(iter->race.Compare(TradeItem.race) == 0 && iter->horse.Compare(TradeItem.horse) == 0 && iter->horse2.Compare( TradeItem.horse2) == 0)
						{
							continue;//��Ʊ���ֹ��쳣��ֱ��������
						}
					}
					if(UpdateTradeTicket(nQ,TradeItem) > 0)
					{
						//if(nQ == 0)//��Ӯ����
						//{
						//���������н���
						int nRet = m_HttpHandule.QTrade(&TradeItem);
						if(nRet == 1)//���׳ɹ�
						{
							//���׳ɹ���ӽ��׼�¼
							AddTradeRecord(nQ,TradeItem);
						}
						else if(nRet ==2)//���׳�ʱ�쳣��
						{
							AddTradeRecord(nQ+2,TradeItem);//��������쳣��¼��
							MessageBox(_T("�����쳣")+TradeItem.race + _T("ma") + TradeItem.horse + _T("-")+TradeItem.horse2);
						}

						//}
						//else
						//{
						//	if(m_HttpHandule.QTrade(&TradeItem))
						//	{
						//		
						//		AddTradeRecord(TradeItem);
						//	}
						//}
					}
			}
		}
	}
	return true;
}
bool CHorseRaceMainDlg::QpTrade()
{
	//TRADE_DATA szCondition ;
	//BOOL bFind = FALSE;
	//TRADE_DATA TradeItem;
	//CString tem,tem2;
	//int nQ = 1;
	//if(m_QpCheck.GetCheck() != BST_CHECKED)
	//	return false;
	//GetDlgItem(IDC_EDIT5)->GetWindowText(szCondition.ticket);
	//GetDlgItem(IDC_EDIT6)->GetWindowText(szCondition.amount);
	//GetDlgItem(IDC_EDIT7)->GetWindowText(szCondition.limit);
	//if(szCondition.ticket.IsEmpty() || szCondition.amount.IsEmpty() || szCondition.limit.IsEmpty())
	//{
	//	SetCurStastua(_T("λ��Q�������ò�ȫ������"));
	//	return false;
	//}
	//int i = 0,j = 0;

	//for (i = 0 ; i < m_ListQ[nQ].GetItemCount() ; ++i)
	//{
	//	tem =  m_ListQ[nQ].GetItemText(i,3);
	//	if(szCondition.amount.Compare(tem) == 0)//�ۿ�
	//	{
	//		tem =  m_ListQ[nQ].GetItemText(i,4);
	//		if(atoi(tem) <= atoi(szCondition.limit))//�޶�
	//		{
	//			tem =  m_ListQ[nQ].GetItemText(i,0);
	//			if(m_TradeRace.Compare(_T("ÿ��")) != 0)
	//			if(m_TradeRace.IsEmpty() || m_TradeRace.Compare(tem) != 0)
	//			{
	//				continue;
	//			}
	//				//���������ҵ���ITEM�����н��ס�
	//				//���浱ǰ���׵�Item��Ϣ
	//				if(m_bStopQpTrade)
	//					{
	//						
	//						return true;//��Ҫֹͣ����
	//					}
	//				int pos1 = 0;
	//				tem =  m_ListQ[nQ].GetItemText(i,1);//��
	//				pos1 = tem.Find(_T("-"));
	//				TradeItem.horse = tem.Left(pos1);
	//				TradeItem.horse2 = tem.Right(tem.GetLength()-pos1-1);

	//				TradeItem.race = tem =  m_ListQ[nQ].GetItemText(i,0);//��

	//				TradeItem.amount = m_ListQ[nQ].GetItemText(i,3);//%

	//				TradeItem.limit = m_ListQ[nQ].GetItemText(i,4);//�޶�

	//				TradeItem.ticket = szCondition.ticket;//Ҫ�Ե�Ʊ
	//				if(!IsExsitCondition(0,&TradeItem))
	//				{
	//					continue;
	//				}
	//				TradeItem.horse = _T("(") + TradeItem.horse;
	//				TradeItem.horse2 = TradeItem.horse2 + _T(")");
	//			
	//				//�жϴ�Item�Ƿ��Ѿ����׹��ˣ�
	//				if(UpdateTradeTicket(TradeItem) > 0)
	//				{
	//					//if(nQ == 0)//��Ӯ����
	//					//{
	//					//���������н���
	//					//if(m_HttpHandule.BetTrade(&TradeItem))
	//					//{
	//					//	//���׳ɹ���ӽ��׼�¼
	//					//	AddTradeRecord(TradeItem);
	//					//}
	//					//}
	//					//else
	//					//{
	//					if(m_HttpHandule.QTrade(&TradeItem))
	//					{

	//						AddTradeRecord(TradeItem);
	//					}
	//					//}
	//				}
	//		}
	//	}
	//}
	//return true;
	
	int nRet = 0;
	//��ȡ��ӮQ���׳ɹ��ļ�¼�����ݳ������ۿ� ��Ʊ��������
	//������λ��Q���ڲ����ڣ�ֱ�ӳԣ�ʧ�ܽ��ۿ�1-2.���ǲ��оͣ��Ļ�ȥ��
	TRADE_DATA szCondition ;
	GetDlgItem(IDC_EDIT5)->GetWindowText(szCondition.ticket);
	GetDlgItem(IDC_EDIT6)->GetWindowText(szCondition.amount);
	GetDlgItem(IDC_EDIT7)->GetWindowText(szCondition.limit);
	//�жϳ��κ�����Ƿ��׹�
	std::list<TRADE_DATA>::iterator iter;
	for (iter = m_list_trade_record[0].begin(); iter != m_list_trade_record[0].end(); ++iter)
	{

		//���Σ���Ρ�   iter��Ӯ���׳ɹ���¼��
		//nRet = atoi(record->ticket) - atoi(iter->ticket);
		int nLoop = 0;
		TRADE_DATA temNode = *iter;
		temNode.amount = szCondition.amount;
		temNode.limit = szCondition.limit;
		temNode.ticket = szCondition.ticket;
		nLoop = 0;
		while(nLoop < 3)
		{
			temNode.amount = szCondition.amount;
			if(UpdateTradeTicket(1,temNode)>0)//��ȡ����Ҫ�Զ���Ʊ
			{
				temNode.amount.Format(_T("%d"),atoi(szCondition.amount) -nLoop ) ;
				int nRet = m_HttpHandule.QpTrade(&temNode);
				if(nRet == 1)//���׳ɹ�
				{
					temNode.amount = szCondition.amount;
					AddTradeRecord(1,temNode);
					break;
				}
				else if(nRet == 2)//�쳣���ء�
				{
					temNode.amount = szCondition.amount;
					AddTradeRecord(1+2,temNode);
					//����쳣��¼��
					MessageBox(_T("�����쳣")+temNode.race + _T("ma") + temNode.horse + _T("-")+temNode.horse2);
				}
				++nLoop;
			}
			else
			{
				break;
			}
			
			
		}
		if(nLoop == 3)//��1-2�ۿ�û�гɹ�
		{
			temNode = *iter;
			while(atoi(temNode.amount)<100)
			{
				if(m_HttpHandule.BetQTrade(&temNode))
				{
					m_list_trade_record[0].erase(iter);//�ĳɹ���ȥ���μ�¼������´��з��ϵ�������������
					break;
				}
				temNode.amount.Format(_T("%d"),atoi(temNode.amount)+1);
			}
		}
		
	}
	return true;
}

//�жϴ�Item�Ƿ���nq�б��д���
bool CHorseRaceMainDlg::IsExsitCondition(int nQ,TRADE_DATA * szNode)
{
	int nCount = m_ListQ[nQ].GetItemCount();
	int nIndex;
	CString tem;
	for (nIndex = 0 ; nIndex < nCount; ++nIndex)
	{
		tem =  m_ListQ[nQ].GetItemText(nIndex,0);
		if(szNode->race.Compare(tem) == 0)//�����
		{
			tem =  m_ListQ[nQ].GetItemText(nIndex,1);
			CString tem2;
			tem2.Format(_T("%s-%s"),szNode->horse,szNode->horse2);
			if(tem.Compare(tem2) == 0)//�����
			{
				tem =  m_ListQ[nQ].GetItemText(nIndex,3);
				if(nQ == 1)//λ��Q
					GetDlgItem(IDC_EDIT6)->GetWindowText(tem2);
				else
					GetDlgItem(IDC_EDIT2)->GetWindowText(tem2);
				if(/*szNode->amount*/tem2.Compare(tem) == 0)//�ۿ�    //����ͬ���ۿ۳�
				{
					tem =  m_ListQ[nQ].GetItemText(nIndex,4);
					if(nQ == 1)//λ��Q
					GetDlgItem(IDC_EDIT7)->GetWindowText(tem2);
					else
					GetDlgItem(IDC_EDIT3)->GetWindowText(tem2);
					if(atoi( tem2) >= atoi(tem))
					{
						return true;
					}
					continue;
				}
				continue;
			}
			continue;
		}
	}
	return false;
}

//�ж��Ƿ��׹�.//���ػ���׵�Ʊ��.�Լ��ϴν��׵��ۿ�
int CHorseRaceMainDlg::UpdateTradeTicket(int nQ,TRADE_DATA & record)
{
	std::list<TRADE_DATA>::iterator iter;
	int nRet = 0;
	//�жϳ��κ�����Ƿ��׹�
	for (iter = m_list_trade_record[nQ].begin(); iter != m_list_trade_record[nQ].end(); ++iter)
	{
		if(record.race.Compare(iter->race) == 0 && iter->horse.Compare(record.horse)== 0 && record.horse2.Compare(iter->horse2) == 0)
		{
			//���׹�
			nRet = atoi(record.ticket) - atoi(iter->ticket);
			record.ticket.Format(_T("%d"),nRet);
			//record.amount = iter->amount;
			return nRet;
		}
	}
	return atoi(record.ticket);
}

//��ӽ��׼�¼
void CHorseRaceMainDlg::AddTradeRecord(int nQ,TRADE_DATA & record)
{
	std::list<TRADE_DATA>::iterator iter;
	//��ӽ��׼�¼�����֮ǰ���׹�����ôֱ�Ӽ�����εĽ���Ʊ��������
	for (iter = m_list_trade_record[nQ].begin(); iter != m_list_trade_record[nQ].end(); ++iter)
	{
		if(record.race.Compare(iter->race) == 0 && iter->horse.Compare(record.race+_T("-")+record.horse2) == 0)
		{
			CString tem;
			tem.Format(_T("%d"),(atoi(iter->ticket) + atoi(record.ticket)));
			iter->ticket = tem;
		}
	}
	if(iter == m_list_trade_record[nQ].end())//�˼�¼û�б����ҹ�
	{
		m_list_trade_record[nQ].push_back(record);
	}
	return ;
}
//��ʼ������
DWORD WINAPI CHorseRaceMainDlg::ThreadProc(_In_ LPVOID lpParameter)
{
	CHorseRaceMainDlg* dlg = (CHorseRaceMainDlg*) lpParameter;
	//dlg->InitNet();

	while(!dlg->m_bThreadExit)
	{
		if(!dlg->m_bLogined)//�ȴ���½�ɹ�
		{
			Sleep(200);
			continue;
		}
		dlg->RefreshAllData();//ˢ��ȫ������
		Sleep(1000);//1��ˢ��һ��

	}
	return 0;
}


void CHorseRaceMainDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_bThreadExit = TRUE;

	WaitForSingleObject(m_hThread,5000) ;

	CloseHandle(m_hThread);


	CDialogEx::OnClose();
}
//����
void CHorseRaceMainDlg::OnNMRClickListQ3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(pNMItemActivate->iItem >= 0)
	{
		CMenu mainMenu;
		mainMenu.LoadMenu(IDR_MENU1);
		POINT CurP;
		GetCursorPos(&CurP);
		mainMenu.GetSubMenu(0)->TrackPopupMenu( TPM_RIGHTBUTTON,CurP.x,CurP.y,this);
	}
	*pResult = 0;
}



//ˢ�½��׼�¼
void CHorseRaceMainDlg::OnBnClickedButton8()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bTradeRecord = FALSE;
}
//��Ӯ����
DWORD WINAPI CHorseRaceMainDlg::ThreadQTrade(_In_ LPVOID lpParameter)
{
	CHorseRaceMainDlg* dlg = (CHorseRaceMainDlg*) lpParameter;
	while(!dlg->m_bThreadExit)
	{
		if(dlg->m_bStopQTrade)//ֹͣ��Ӯ����
		{
			Sleep(200);
			continue;
		}
		dlg->QTrade();//��ʼ��Ӯ����
	}

	return 0;
}
//λ��Q����
DWORD WINAPI CHorseRaceMainDlg::ThreadQpTrade(_In_ LPVOID lpParameter)
{
	CHorseRaceMainDlg* dlg = (CHorseRaceMainDlg*) lpParameter;
	while(!dlg->m_bThreadExit)
	{
		if(dlg->m_bStopQpTrade)//ֹͣλ��Q����
		{
			Sleep(200);
			continue;
		}
		dlg->QpTrade();//��ʼλ�ý���
	}
	return 0;
}

//����״̬
void CHorseRaceMainDlg::SetCurStastua(CString msg)
{
	SetDlgItemText(IDC_STATIC_STASTUS,msg);
}
//��½�߳�
DWORD WINAPI CHorseRaceMainDlg::ThreadInit(_In_ LPVOID lpParameter)
{
	CHorseRaceMainDlg* dlg = (CHorseRaceMainDlg*) lpParameter;
	dlg->InitNet();
	return 0;
}

//ȷ����ʾ��¼����
void CHorseRaceMainDlg::OnBnClickedButton6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CComboBox* pcombox = (CComboBox*)(GetDlgItem(IDC_COMBO1));
	pcombox->GetLBText(pcombox->GetCurSel(),m_RcordRace);
	m_TradeRecord.DeleteAllItems();
	m_bTradeRecord = FALSE;
	TRACE(m_TradeRace);
}

//ǿ��ֹͣ����
void CHorseRaceMainDlg::OnBnClickedButton13()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	m_bStopQTrade = TRUE;
	m_bStopQpTrade = TRUE;
	m_bStopOneKey = TRUE;
	//KillTimer(100);
	GetDlgItem(IDC_BUTTON5)->EnableWindow(TRUE);
	SetCurStastua(_T("�Ѿ���������ɨ��"));
	GetDlgItem(IDC_BUTTON14)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMBO2)->EnableWindow(TRUE);
	m_bDown = false;
}


//���׵ĳ��θı�
void CHorseRaceMainDlg::OnCbnSelchangeCombo2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_TradeRace.Empty();
}

//��ʱ��
void CHorseRaceMainDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(nIDEvent == 100)
	{
		--m_DownS;
		if(m_DownS < 1)
		{
			//KillTimer(nIDEvent);
			OnBnClickedButton13();
			m_DownS = 0;
		}
		UpdateData(FALSE);
	}
	CDialogEx::OnTimer(nIDEvent);
}


HBRUSH CHorseRaceMainDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if(nCtlColor == CTLCOLOR_STATIC && pWnd->GetDlgCtrlID() == IDC_STATIC_WINNING)
	{
		CString strWin;
		GetDlgItemText(IDC_STATIC_WINNING,strWin);
		if(strWin.Find(_T("(")) >= 0 )//Ӯ
		{
			pDC->SetTextColor(RGB(255,0,0));
		}
		
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


void CHorseRaceMainDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialogEx::OnCancel();
}


void CHorseRaceMainDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	//CDialogEx::OnOK();
}

//��������ʱ
void CHorseRaceMainDlg::OnBnClickedButton14()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

		m_bDown = true;
		UpdateData(TRUE);
		GetDlgItem(IDC_BUTTON14)->EnableWindow(FALSE);
}


void CHorseRaceMainDlg::OnBnClickedButton7()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
