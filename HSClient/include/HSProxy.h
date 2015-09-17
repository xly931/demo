#pragma once
#include "ProxySvr.h"
#include <Ice/Ice.h>
using namespace Ice;
using namespace std;
using namespace HSPW;

/*=========================================================================
����������װICE�Ŀͻ��˴���
�ӿ�  ��
��ע  ��
����  ��2015.7 xly
=========================================================================*/
class HSProxy
{
public:
	HSProxy();
	~HSProxy();
	/*=========================================================================
	����  ����ʼ��ICE�������
	����  ������Ϊice����id��ͨ��Э�飬�����ip������˶˿�
	����ֵ��
	��ע  ��
	����  ��2015.7 xly
	=========================================================================*/
	bool Init(const string& szProtocol,const string szIP, unsigned short port);
	/*=========================================================================
	����  ���Ͽ�������
	����  ��
	����ֵ��
	��ע  ��
	����  ��2015.7 xly
	=========================================================================*/
	void DisConnect();
	/*=========================================================================
	����  ��������һ�δ�����Ϣ
	����  ��
	����ֵ��
	��ע  ��
	����  ��2015.7 xly
	=========================================================================*/
	const string& GetLastErr()const;


	void do_func(const ::HSPW::TagProxySvr& tagIn, ::HSPW::TagProxySvr& tagOut);
	void do_sync();
private:
	//����������˵��ַ�����ʾ��ʽ
	string MakeEndpointStr();
private:
	CommunicatorPtr	m_comm_ptr;		//ice�������todo���Ƿ�ɳ�ʼ������
	ProxySvrPrx		m_proxy;		//ice����Ĵ���

	string			m_protocol;		//ͨ��Э��
	string			m_srv_obj_idf;	//�����ice����id��ʶ
	string			m_srv_IP;		//�����ip��ַ
	unsigned short	m_srv_port;		//����˶˿�

	string			m_err_msg;		//�������һ�δ�����Ϣ
};
