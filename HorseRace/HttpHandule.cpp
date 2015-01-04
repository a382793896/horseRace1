#include "StdAfx.h"
#include "HttpHandule.h"
#include "SafeArrayHelper.h"
#include "resource.h"
#include "HorseRaceMainDlg.h"
CHttpHandule::CHttpHandule(void)
{
	m_MainDlg = NULL;
	m_ScriptObj.Reset();
	m_ScriptObj.SetLanguage(LANGUAGE_DEFAULT);
	if(!m_ScriptObj.LoadScriptResource(MAKEINTRESOURCE(IDR_JS1),_T("JS"),GetModuleHandle(NULL)))
	{

		MessageBox(NULL,m_ScriptObj.GetErrorString(),_T("aa"),MB_OK);
	}
	m_valid = _T("&valid=");
	m_Head = _T("Accept-Language: zh-CN\nUser-Agent: Mozilla/5.0 (compatible; MSIE 9.0; Windows NT 6.1; WOW64; Trident/5.0)\nHost: secure.ctb988.net\nConnection: Keep-Alive");
	m_DataHead = _T("Accept-Language: zh-CN\nUser-Agent: Mozilla/5.0 (compatible; MSIE 9.0; Windows NT 6.1; WOW64; Trident/5.0)\nHost: data.ctb988.net\nConnection: Keep-Alive\nPragma: no-cache");
}


CHttpHandule::~CHttpHandule(void)
{
}
BOOL CHttpHandule::InitLogin()
{

	m_Host = m_iniFile.GetString(_T("BASE"),_T("host"));
	CString url = m_Host;
	CString Head = _T("Accept: text/html, application/xhtml+xml, */*\nReferer: http://www.ctb988.net\nAccept-Language: zh-CN\nUser-Agent: Mozilla/5.0 (compatible; MSIE 9.0; Windows NT 6.1; WOW64; Trident/5.0)\nHost: www.ctb988.net\nConnection: Keep-Alive");
	//m_http.get(url,Head);
	CString content;
	int nLoopCount = 3;
	while(nLoopCount --)
	{
		content =  m_http.get(url);
		TRACE(_T("111:")+content);
		if(content.IsEmpty() || content.Compare(_T("throw_erorr")) == 0)
		{
			continue;
		}
		else
		{
			break;
		}
	}
	nLoopCount = 3;
	int pos1,pos2;
	if(content.Find(_T("<script>location.replace('")) >= 0)
	{
		pos1 = content.Find('?');
		pos2 = content.Find(_T("')"));
		content = content.Mid(pos1,pos2 - pos1);
		content = m_http.get(url+_T("login.jsp")+content);
	}
	else if(content.Find(_T("_index.jsp")) < 0)
	{
		return FALSE;
	}
	TRACE(_T("222:")+content,Head);
	content = m_http.get(url+_T("tlbcp"));
	TRACE(_T("333:")+content);
	while(nLoopCount--)
	{
		content = m_http.get(url+_T("_index.jsp"),Head);
		if(content.IsEmpty()||content.Compare(_T("throw_erorr")) == 0)
		{
			continue;
		}
		break;
	}
	TRACE(_T("444:")+content);
	//CFile file;
	//file.Open("1.txt",CFile::modeCreate | CFile::modeWrite);
	//file.Write(content,content.GetLength());
	pos1 =  content.Find(_T("id=\"valid\" value=\""));
	pos1 = pos1 + strlen(_T("id=\"valid\" value=\""));
	pos2 = content.Find(_T("\"/>"),pos1);
	m_valid = _T("&valid=");
	m_valid = m_valid + content.Mid(pos1,pos2-pos1);

	return TRUE;
}

CString CHttpHandule::ExecuteMask(CString msg)
{
	CString strRet = "", strProc = _T("mask");


	CSafeArrayHelper sfHelper;
	try{
		_variant_t var;
		if (strProc.IsEmpty())
			sfHelper.Create(VT_VARIANT, 1, 0, 0);	// (void) parameter
		else
		{
			sfHelper.Create(VT_VARIANT, 1, 0, 1);	// 1 parameter
			var = _bstr_t(msg);
		}
		sfHelper.PutElement(0, (void*)&var);	// parameter1 -> index 0
		LPSAFEARRAY sa =  sfHelper.GetArray();
		_variant_t varRet;
		if (m_ScriptObj.RunProcedure(strProc, &sa, &varRet))
			strRet = ( (LPCTSTR)(_bstr_t(varRet)) );
		else
		{
			CString strError = m_ScriptObj.GetErrorString();
			strRet = ( strError );
		}
	}
	catch(...)
	{
		strRet = m_ScriptObj.GetErrorString();

	}
	return strRet;
}

CImage* CHttpHandule::GetCodeImage()
{
	m_Host = m_iniFile.GetString(APPNAME,_T("host"));
	CImage* code =  m_http.GetImg(m_Host+_T("img.jpg?0.5589080715097631"));
	if(code)
	{
		return code;
	}
	else
	{
		return NULL;
	}

}


BOOL CHttpHandule::Login(CString UserName,CString PassWord,CString code,CString PinCode)
{
	m_Host = m_iniFile.GetString(APPNAME,_T("LoginHost"));
	CString strRet = "";
	CString  strUid = _T("uid="),strPass = _T("&pass="),strCode = _T("&code="),strLang = _T("&lang=CH");
	//mask(valid+code+mask("voodoo_people_"+uid+mask(pass)));
	CString vlid =m_valid.Right(strlen(_T("c3617c79-0dc7-4d48-b560-2e38f3223e29"))) ;
	strPass = strPass + ExecuteMask(vlid+code+ExecuteMask("voodoo_people_"+UserName+ExecuteMask(PassWord)));
	strUid = strUid + UserName;
	strCode = strCode + code;

	CString data = strUid+strPass+strCode+m_valid+strLang;
	CString contenLen;
	contenLen.Format(_T("Content-Length: %d"),data.GetLength());
	CString head = _T("Accept: text/html, application/xhtml+xml, */*\nReferer: http://www.ctb988.net/_index.jsp\nAccept-Language: zh-CN\nUser-Agent: Mozilla/5.0 (compatible; MSIE 9.0; Windows NT 6.1; WOW64; Trident/5.0)\nContent-Type: application/x-www-form-urlencoded\nHost: secure.ctb988.net\nConnection: Keep-Alive\nCache-Control: no-cache\n")+contenLen;
	int  nLoopCount = 3;
	SetCurStatus(_T("正在登陆..."));
	while(nLoopCount--)
	{

		strRet = m_http.post(m_Host+_T("login"),head,data);
		if(!strRet.IsEmpty() && strRet.Compare(_T("throw_erorr")) != 0) break;
	}

	if(strRet.Find(_T("validate_pin.jsp")) >0 )
	{
		nLoopCount = 3;
		SetCurStatus(_T("登陆成功,正在验证PIN码"));
		m_UserName = UserName;
		while(1)
		{
			strRet = m_http.get(m_Host+_T("validate_pin.jsp"),m_Head);
			if(!strRet.IsEmpty() && strRet.Compare(_T("throw_erorr")) != 0)
			{
				break;
			}
		}
		  
		int pos1  = 0,pos2 = 0;
		pos1 = strRet.Find(_T("r1='"));

		pos1 = pos1 + strlen(_T("r1='"));
		pos2 = strRet.Find(_T("';"),pos1);
		m_R1 = strRet.Mid(pos1,pos2-pos1); //得到R1值
		pos1 = strRet.Find(_T("r2='"));
		pos1 = pos1 + strlen(_T("r2='"));
		pos2 = strRet.Find(_T("';"),pos1);
		m_R2 = strRet.Mid(pos1,pos2-pos1); //得到R2值
		//document.getElementById('code').value = mask(r1+r2+mask("pin_"+u+code));
		strCode = ExecuteMask(m_R1+m_R2+ExecuteMask(_T("pin_")+UserName+PinCode));
		strCode = _T("code=")+strCode;
		contenLen.Format(_T("Content-Length: %d"),strCode.GetLength());
		head = _T("Accept: text/html, application/xhtml+xml, */*\nReferer: https://secure.ctb988.net/validate_pin.jsp?sml=m\nAccept-Language: zh-CN\nUser-Agent: Mozilla/5.0 (compatible; MSIE 9.0; Windows NT 6.1; WOW64; Trident/5.0)\nContent-Type: application/x-www-form-urlencoded\nHost: secure.ctb988.net\nConnection: Keep-Alive\nCache-Control: no-cache\n")+contenLen;
		strRet = m_http.post(m_Host+_T("verifypin"),head,strCode);
		if(strRet.Find(_T("dispatch.jsp"))<0)
		{
			TRACE(strRet);
			SetCurStatus(_T("验证PIN码失败,请确认是否填写正确"));
			return FALSE;
		}
		strRet = m_http.get(m_Host+_T("dispatch.jsp"),m_Head);
		if(strRet.IsEmpty() || strRet.Compare(_T("throw_erorr")) == 0) return FALSE;
		m_Host = m_iniFile.GetString(APPNAME,_T("LoginHost"));//更换域名
		m_Head = _T("Accept-Language: zh-CN\nUser-Agent: Mozilla/5.0 (compatible; MSIE 9.0; Windows NT 6.1; WOW64; Trident/5.0)\nHost: racing.ctb988.net\nConnection: Keep-Alive");

		//CImage * img  = m_http.GetImg(m_Host+_T("/pixel.png?0.4909987307623288"));//更换cookie
		while(1)
		{
			strRet = m_http.get(m_Host+_T("terms.jsp"),m_Head);
			if(!strRet.IsEmpty() && strRet.Compare(_T("throw_erorr")) != 0)
			{
				break;
			}
		}
		//
		//strRet = m_http.get(m_Host+_T("member/announcement.jsp"),m_Head);
		//if(strRet.IsEmpty())
		//{
		//	return FALSE;
		//}
		//strRet = m_http.get(m_Host+_T("dishonest_acc.jsp"),m_Head);
		//if(strRet.IsEmpty())
		//{
		//	return FALSE;
		//}
		while(1)
		{
			strRet = m_http.get(m_Host+_T("playerhk.jsp"),m_Head);
			if(!strRet.IsEmpty() && strRet.Compare(_T("throw_erorr")) != 0)
			{
				break;
			}
		}
		SetCurStatus(_T("验证PIN码成功，可以进行一建交易"));
		pos1 = strRet.Find(_T("Q.jsp?race_type=3H&race_date="));
		if(pos1 < 0)
		{
			SetCurStatus(_T("验证PIN码成功，当前没有香港比赛。不可以进行交易"));
			return FALSE;
		}
		pos1 = pos1 + strlen(_T("Q.jsp?race_type=3H&race_date="));
		pos2 = strRet.Find("'",pos1);
		m_RunTime = strRet.Mid(pos1,pos2-pos1);
		return TRUE;
	}
	else
	{
		TRACE(_T("Login:")+strRet);
		if(strRet.Find(_T("e=3")) > 0)
		{
			SetCurStatus(_T("登陆失败,验证码错误"));
		}
		else if(strRet.Find(_T("e=5")) > 0)
		{
			SetCurStatus(_T("登陆失败,账号或密码错误"));
		}
		else
		{
			SetCurStatus(_T("登陆失败"));
		}
		return FALSE;
	}

}


BOOL CHttpHandule::SetParentHwnd(CDialogEx * MainDlg)
{

	m_MainDlg = MainDlg;
	return TRUE;
}

void CHttpHandule::SetCurStatus(CString msg)
{
	if(m_MainDlg)
	{
		((CHorseRaceMainDlg*)m_MainDlg)->SetCurStastua(msg);
	}
}
std::list<TRADE_DATA>*  CHttpHandule::GetTimeData(CString & time_data,CString strRc,CString & strWin,CString & StrRace)
{
	CString tem;
	if(strRc.IsEmpty())
	{
		strRc = _T("0");
	}
	tem.Format(_T("datastore?race_date=%s&race_type=3H&rc=%s&q=q&x=0.3682902207461527&tnum=1&txnrnd=0.43144710102172645"),m_RunTime,strRc);
	m_Host = m_iniFile.GetString(APPNAME,_T("MainHost"));
	tem =  m_http.get(m_Host+tem,m_Head);
	if(tem.IsEmpty() || tem.Compare(_T("throw_erorr")) == 0)
	{
		return NULL;
	}
	int pos1,pos2;
	//开炮时间
	pos1 = tem.Find(_T("id=txtTIMER>"));
	if(pos1<0) return NULL;
	pos1 = pos1 + strlen(_T("id=txtTIMER>"));
	pos2 = tem.Find(_T("<"),pos1);
	time_data = tem.Mid(pos1,pos2-pos1);

	//开炮场次

	pos1 = tem.Find(_T("id=txtTOTE>"));
	if(pos1<0) return NULL;
	pos1 = pos1 + strlen(_T("id=txtTOTE>"));
	pos2 = tem.Find(_T("<"),pos1);
	StrRace = tem.Mid(pos1,pos2-pos1);
	//输赢
	pos1 = tem.Find(_T("color: #FF0000"));
	if(pos1 < 0)
	{
		//赢
		pos1 = tem.Find(_T("id=AC_PL>HK"));
		pos1 += strlen(_T("id=AC_PL>HK"));
		pos2 = tem.Find(_T("</pre>"),pos1);
		strWin = tem.Mid(pos1,pos2 - pos1);
	}else
	{
		//输
		pos1 = tem.Find(_T("color: #FF0000;\">"));
		pos1 += strlen(_T("color: #FF0000;\">"));
		pos2 = tem.Find(_T("</span>"),pos1);
		strWin = tem.Mid(pos1,pos2 - pos1);
	}

	m_List_Trade.clear();
	tem.Format(_T("datastore?race_date=%s&race_type=3H&rc=0&q=q&x=0.3682902207461527&tnum=1&txnrnd=0.43144710102172645"),m_RunTime);
	tem =  m_http.get(m_Host+tem,m_Head);
	if(tem.IsEmpty() || tem.Compare(_T("throw_erorr")) == 0)
	{
		return NULL;
	}
	
	pos1 = tem.Find(_T("MF#"));
	if(pos1 < 0 ) return NULL;
	while(1)
	{
		TRADE_DATA temTrade;
		pos1 = tem.Find(_T("[Q"),pos1);
		if(pos1 < 0 ) break;
		temTrade.TradeType = tem.GetAt(pos1+2);//场
		if(temTrade.TradeType.Compare(_T("P")) == 0)
		{
			temTrade.TradeType =_T("Q") + temTrade.TradeType;
			pos1 = pos1 + strlen(_T("[Qp#B#"));
		}else
		{
			temTrade.TradeType = _T("Q");
			pos1 = pos1 + strlen(_T("[Q#B#"));
		}
		
		
		pos2 =  tem.Find(_T("#"),pos1 + 1 );
		temTrade.race = tem.Mid(pos1,pos2 - pos1);//场
		pos1 = tem.Find(_T("#"),pos2+1);
		temTrade.horse = tem.Mid(pos2+1,pos1 - pos2-1);//马
		pos2 = tem.Find(_T("#"),pos1+1);
		temTrade.ticket = tem.Mid(pos1+1,pos2 - pos1-1);//票
		pos1 = tem.Find(_T("#"),pos2+1);
		temTrade.amount = tem.Mid(pos2+1,pos1 - pos2-1);//折扣
		pos2 = tem.Find(_T("]"),pos1+1);
		temTrade.limit = tem.Mid(pos1+1,pos2 - pos1-1);//限额
		
		//看下一行是什么数据，
		pos1 = tem.Find(_T("["),pos2);
		CString strTem = tem.Mid(pos1+1,1);
		if(strTem.Compare(_T("C")) == 0)
		{
			
			pos2 = tem.Find(_T("#.#"),pos1);
			pos2 = pos2 +  strlen(_T("#.#"));
			pos1 = tem.Find(_T("#"),pos2);
			temTrade.TradeTicket = tem.Mid(pos2,pos1 - pos2);
		}
		m_List_Trade.push_back(temTrade);
	}
	return &m_List_Trade;
}

std::list<QDATA>* CHttpHandule::GetQData(int nQ)
{
	m_DataHost = m_iniFile.GetString(APPNAME,_T("DataHost"));
	if(nQ >1) ++nQ;
	if(!m_DataHost.IsEmpty())
	{
		m_list_Q1.clear();
		m_list_Q4.clear();
		CString url;
		CString tem, t;
		CTime CurrentTime =  CTime::GetCurrentTime();
		tem = CurrentTime.Format(_T("%d-%m-%Y"));
		url.Format(_T("%s%d&race_date=%s&race_type=3H&rc=0&m=HK&c=2"),m_DataHost+_T("qdata?q="),nQ,m_RunTime);
		int nLoopCount = 3;
		while(nLoopCount--)
		{
			tem = m_http.get(url,m_DataHead);
			if(tem.IsEmpty() || tem.GetLength() < 300 || tem.Compare(_T("throw_erorr")) == 0)
			{
				TRACE(tem);
				continue;
			}
			break;
		}
		if(nLoopCount == 0)return NULL;
		int po1 = 0,po2 = 0,nIndex = 0,nCount = 0 ;
		t.Format(_T("FC_DATA_%d>"),nQ);
		nIndex = tem.Find(t);
		if(nIndex <0)  return NULL;
		nIndex = nIndex + t.GetLength();
		BOOL bLoop = TRUE;
		while(bLoop)
		{
			QDATA data;
			nCount = 0;
			while(nCount <= 5)// 0 1 2 3 4
			{

				TCHAR x =  tem.GetAt(nIndex);
				if(x >= '0' && x <= '9') //遇见数字，。
				{
					po1 = nIndex;
				}
				else
				{
					if(x =='<')
					{
						bLoop = FALSE;
						break;
					}
					++nIndex;
					continue;
				}
				while(1)
				{

					TCHAR x =  tem.GetAt(++nIndex);
					if(x < '0' || x > '9' )
					{
						po2 = nIndex;
						break;
					}
				}
				if(x =='<')
				{
					bLoop = FALSE;
				}
				if(nCount ==0 )
				{
					t = tem.Mid(po1,po2-po1);
					data.race = atoi(t);
				}
				else if(nCount == 1)
				{
					t = tem.Mid(po1,po2-po1);
					data.horse1 = atoi(t);
				}
				else if(nCount == 2)
				{
					t = tem.Mid(po1,po2-po1);
					data.horse2 = atoi(t);
				}
				else if(nCount == 3)
				{
					t = tem.Mid(po1,po2-po1);
					data.ticket = atoi(t);
				}
				else if(nCount == 4)
				{
					t = tem.Mid(po1,po2-po1);
					data.amount = atoi(t);
				}
				else if(nCount == 5)
				{
					t = tem.Mid(po1,po2-po1);
					data.limit = atoi(t);
				}

				++nCount;
			}

			if(!bLoop)break;
			if(nQ == 1)
			{
				m_list_Q1.push_back(data);
			}
			else if(nQ == 3)
			{
				m_list_Q4.push_back(data);
			}

		}
		if(nQ == 1)
		{
			return &m_list_Q1;
		}
		else //(nQ == 4)
		{
			return &m_list_Q4;
		}
	}
	else
		return &m_list_Q1;
}

//连赢Q
int  CHttpHandule::QTrade( TRADE_DATA * condition)
{
	m_Host = m_iniFile.GetString(APPNAME,_T("MainHost"));
	CString strUrl;

	strUrl.Format(_T("%sforecast?flag=0&Tix=%s&Race=%s&Hs1=%s&Hs2=%s&fctype=0&Q=Q&type=EAT&overflow=0&amount=%s&fclmt=%s&race_type=3H&race_date=%s&show=1&rd=0.09167499654883521 "),
		m_Host,condition->ticket,condition->race,condition->horse,condition->horse2,condition->amount,condition->limit,m_RunTime);

	CString strRet =  m_http.get(strUrl,m_Head);
	if(strRet.Find(_T("已所有被证实")) < 0  )
	{
		return 0;//0代表执行失败
	}
	else if(strRet.Compare(_T("throw_erorr")) == 0)//返回异常
	{
		return 2;//
	}
	return 1;//1代表连赢交易
}
//位置Q
int  CHttpHandule::QpTrade( TRADE_DATA * condition)
{
	m_Host = m_iniFile.GetString(APPNAME,_T("MainHost"));
	CString strUrl;
	strUrl.Format(_T("%sforecast?flag=0&Tix=%s&Race=%s&Hs1=%s&Hs2=%s&fctype=1&Q=Q&type=EAT&overflow=0&amount=%s&fclmt=%s&race_type=3H&race_date=%s&show=1&rd=0.09167499654883521 "),
		m_Host,condition->ticket,condition->race,condition->horse,condition->horse2,condition->amount,condition->limit,m_RunTime);
	CString strRet =  m_http.get(strUrl,m_Head);
	if(strRet.Find(_T("已所有被证实")) < 0 )
	{
		return 0;//0代表执行失败
	}
	else if(strRet.Compare(_T("throw_erorr")) == 0)//返回异常
	{
		return 2;//
	}
	return 1;//1代表位置Q交易
}

int  CHttpHandule::BetQTrade( TRADE_DATA * condition)
{
	m_Host = m_iniFile.GetString(APPNAME,_T("MainHost"));
	CString strUrl;

	strUrl.Format(_T("%sforecast?flag=0&Tix=%s&Race=%s&Hs1=%s&Hs2=%s&fctype=0&Q=Q&type=BET&overflow=0&amount=%s&fclmt=%s&race_type=3H&race_date=%s&show=1&rd=0.09167499654883521"),
		m_Host,condition->ticket,condition->race,condition->horse,condition->horse2,condition->amount,condition->limit,m_RunTime);

	CString strRet =  m_http.get(strUrl,m_Head);
	if(strRet.Find(_T("已所有被证实")) < 0 )
	{
		return 0;//0代表执行失败
	}
	else if(strRet.Compare(_T("throw_erorr")) == 0)//返回异常
	{
		return 2;//
	}
	return 1;//1代表连赢交易
}
std::list<TRADE_DATA>* CHttpHandule::GetRcord()
{
	m_Host = m_iniFile.GetString(APPNAME,_T("MainHost"));
	CString strUrl,strRet;
	strUrl.Format(_T("%snew_history_live.jsp?uid=%s"),m_Host,m_UserName);
	strRet = m_http.get(strUrl,m_Head);
	if(!strRet.IsEmpty())
	{
		return NULL;
	}
	m_List_Trade.clear();
	int i,po1,po2,ntab = 0;
	CString strfindKey;
	for (i = 1 ; i <= 20; ++i)
	{
		strfindKey.Format(_T("q_tbl_detail_3H_%2d"),i);
		ntab = strRet.Find(strfindKey);
		if(ntab < 0)
		{
			continue;
		}
		while(1)
		{

			int CurRc = 0;
			TRADE_DATA temNode;
			CurRc = strRet.Find(_T("<!--Race below end here-->"),ntab);
			temNode.race.Format(_T("%d"),i); //场
			po1 = strRet.Find(_T("<tr"));
			if(po1 > CurRc)
			{
				break;//一个场数据获取完成
			}
			po1 += strlen(_T("<tr"));
			if(strRet.GetAt(po1) != '>')
			{
				po1 = strRet.Find(_T("<td>"),po1);
				po1 += strlen(_T("<td>"));
				po2 = strRet.Find(_T("</td>"),po1);
				temNode.horse = strRet.Mid(po1,po2 - po1);

				po1 = strRet.Find(_T("<td>"),po2);
				po1 += strlen(_T("<td>"));
				po2 = strRet.Find(_T("</td>"),po1);
				temNode.ticket = strRet.Mid(po1,po2 - po1);//票

				po1 = strRet.Find(_T("<td>"),po2);
				po1 += strlen(_T("<td>"));
				po2 = strRet.Find(_T("</td>"),po1);
				temNode.TradeType = strRet.Mid(po1,po2 - po1);//交易类型

				po1 = strRet.Find(_T("<td>"),po2);
				po1 += strlen(_T("<td>"));
				po2 = strRet.Find(_T("</td>"),po1);
				temNode.amount = strRet.Mid(po1,po2 - po1);//%

				po1 = strRet.Find(_T("<td>"),po2);
				po1 += strlen(_T("<td>"));
				po2 = strRet.Find(_T("</td>"),po1);
				temNode.limit = strRet.Mid(po1,po2 - po1);//限额

				po1 = strRet.Find(_T("<td>"),po2);
				po1 += strlen(_T("<td>"));
				po2 = strRet.Find(_T("</td>"),po1);
				temNode.shui = strRet.Mid(po1,po2 - po1);//税

				po1 = strRet.Find(_T("\">"),po2);
				po1 += strlen(_T("\">"));
				po2 = strRet.Find(_T("</span>"),po1);
				temNode.shui = strRet.Mid(po1,po2 - po1);//总额

				po1 = strRet.Find(_T("&rc="),po2);
				po1 += strlen(_T("&rc="));
				po2 = strRet.Find(_T("&"),po1);
				CurRc = atoi(strRet.Mid(po1,po2 - po1));
			}
			else
			{
				po1 = strRet.Find(_T("minus_red\">"),po1);
				po1 += strlen(_T("minus_red\">"));
				po2 =  strRet.Find(_T("</span>"));
				temNode.ticket = strRet.Mid(po1,po2 - po1);

				while(1)
				{
					TCHAR ch = strRet.GetAt(po2);
					if(ch >= '0' && ch <= '9')
					{
						break;
					}
					++po2;
				}
				po1 = strRet.Find(_T("</td>"),po2);
				temNode.shui = strRet.Mid(po2-1,po1 - po2);
			}
			m_List_Trade.push_back(temNode);
		}
	}
	return &m_List_Trade;
}

