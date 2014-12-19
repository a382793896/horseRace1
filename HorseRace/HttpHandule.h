#pragma once
#include "Http.h"
#include "ScriptObject.h"
#include "IniFile.h"
#include <list>
#define  APPNAME _T("BASE")
#define  CONDITIONNAME _T("CONDITION")

typedef struct tagQData
{
	int race;//��
	int horse1;//��1
	int horse2;//��2
	int ticket;//Ʊ��
	int limit; //�޶�
	int amount;//%
}QDATA;
typedef struct tagTrade
{
	CString TradeTicket;//����Ʊ��
	CString TradeType;//��������
	CString race;
	CString horse;
	CString horse2;
	CString ticket;
	CString amount;
	CString limit;
	CString shui;//��Ӯ���ҵ���λ��Q�����ۿ�
	CString zongshu;//����
	CString TraceAmount;
}TRADE_DATA;
typedef struct tagTime
{
	CString RunTime;
	CString TimeRemaining;
}TIME_DATA;
class CHttpHandule
{
public:
	CHttpHandule(void);
	~CHttpHandule(void);
	CIniFile m_iniFile;
private:
	CScriptObject m_ScriptObj;
	CHttp m_http;
	CDialogEx * m_MainDlg;
	CString m_Host,m_DataHost;
	CString m_valid;
	CString m_UserName;
	CString m_R1,m_R2;
	CString m_Head,m_DataHead;
	std::list<QDATA> m_list_Q1,m_list_Q4;
	std::list<TRADE_DATA> m_List_Trade;
	CString m_RunTime;
public:
	BOOL InitLogin();//��ʼ����½����
	CString ExecuteMask(CString msg);//ִ��js���ܽű�
	CImage* GetCodeImage();//��ȡ��֤��ͼƬ
	BOOL Login(CString UserName,CString PassWord,CString code,CString PinCode);
	BOOL SetParentHwnd(CDialogEx * MainDlg);
	std::list<QDATA> * GetQData(int nQ = 1);
	std::list<TRADE_DATA>*  GetTimeData(CString & time_data,CString strRc,CString & strWin,CString & StrRace);
	int QTrade( TRADE_DATA * condition);
	int QpTrade( TRADE_DATA * condition);
	void SetCurStatus(CString msg);
	std::list<TRADE_DATA>* GetRcord();
	int BetQTrade( TRADE_DATA * condition);
};

