
// HorseRace.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CHorseRaceApp:
// �йش����ʵ�֣������ HorseRace.cpp
//

class CHorseRaceApp : public CWinAppEx
{
public:
	CHorseRaceApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CHorseRaceApp theApp;