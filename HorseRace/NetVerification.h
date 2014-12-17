#pragma once
//检测网络，无法连接网络返回 真，连接成功返回假
typedef bool (WINAPI * CheckNet)( );
//登陆和注册
typedef bool (WINAPI * LoginAndRegister)
	(
	int nType,//调用类型，1.注册 2.登陆
	TCHAR UserName[],//账号
	TCHAR PassWord[],//密码
	TCHAR QQ[]		//QQ号	
	);
//到期时间查询
typedef TCHAR * (WINAPI * QueryTime)(TCHAR UserName[]);

//充值
typedef int (WINAPI * SaveMoney)(TCHAR UserName[],TCHAR cKey[]);