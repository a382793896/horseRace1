#pragma once
#include "Http.h"
#include "ScriptObject.h"
#include "IniFile.h"
#include <list>
#define  APPNAME _T("BASE")
#define  CONDITIONNAME _T("CONDITION")

typedef struct tagQData
{
	int race;//场
	int horse1;//马1
	int horse2;//马2
	int ticket;//票数
	int limit; //限额
	int amount;//%
}QDATA;
typedef struct tagTrade
{
	CString TradeTicket;//交易票数
	CString TradeType;//交易类型
	CString race;
	CString horse;
	CString horse2;
	CString ticket;
	CString amount;
	CString limit;
	CString shui;//连赢查找到的位置Q交易折扣
	CString zongshu;//总数
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
	BOOL InitLogin();//初始化登陆功能
	CString ExecuteMask(CString msg);//执行js加密脚本
	CImage* GetCodeImage();//获取验证码图片
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

