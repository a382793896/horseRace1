#pragma once

#include <afxinet.h>
#include <atlimage.h>
 


///////////////////////////////////////////////////////////////////
/*
HTTPЭ�������
���ܣ�ʵ��HTTP��GET��POST����
���ߣ������� QQ:2268190059 kjuu@yahoo.cn
ʱ�䣺2011-10-20 �� 2011-10-24
*/
////////////////////////////////////////////////////////////////////
class CHttp
{
public:
	//�ύGET����
	CString get(CString url);
	CString get(CString url, CString header);
	//�ύPOST����
	CString post(CString url, CString PostData);
	CString post(CString url, CString header, CString PostData);
	//�ύHTML����
	CString GetHTML(CString url, CString header, CString PostData, bool isPost = false);
	//��ȡͼƬ
	CImage *GetImg(CString url);
	
public:
	//������վ��cookie
	CString m_cookies;
	//������վ�ı��뷽ʽ
	int m_CodePage;
	//���ӵĻỰ����
	CInternetSession m_session;

private:
	//��ȡURL�е��������ļ�·��
	void DecomposeURL(CString &url, CString &domain, CString &path);
	//���շ��ص�HTML��Ϣ
	CString RevHTML(CHttpFile *pFile);
	//HTML���ݱ���ת��
	CString EncodeHTML(CString &str);
	//POST���ݱ���ת��
	CString EncodePOST(CString &str);
	//��ȡ���ص�cookies
	void SaveCookies(CHttpFile *pFile);

private:
	//����ͼƬ
	CImage m_img;
	//ͼƬ�ڴ����
	HGLOBAL m_hGlobal;
	IStream *m_pStream;

public:
	CHttp(void);

public:
	~CHttp(void);
};
