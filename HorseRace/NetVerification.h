#pragma once
//������磬�޷��������緵�� �棬���ӳɹ����ؼ�
typedef bool (WINAPI * CheckNet)( );
//��½��ע��
typedef bool (WINAPI * LoginAndRegister)
	(
	int nType,//�������ͣ�1.ע�� 2.��½
	TCHAR UserName[],//�˺�
	TCHAR PassWord[],//����
	TCHAR QQ[]		//QQ��	
	);
//����ʱ���ѯ
typedef TCHAR * (WINAPI * QueryTime)(TCHAR UserName[]);

//��ֵ
typedef int (WINAPI * SaveMoney)(TCHAR UserName[],TCHAR cKey[]);