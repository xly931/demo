#pragma once
#include <Ice/Ice.h>
#include <Ice/Service.h>
#include "HSProc.h"
#include <string>
using namespace std;
using namespace Ice;
using namespace HSPW;
/*=========================================================================
��������ʵ��ת������ķ�������
�ӿ�  ��
��ע  ��
����  ��2015.7 xly
=========================================================================*/
class CHSFowarderServer : public Service
{
public:
	CHSFowarderServer();
	~CHSFowarderServer();

	bool start(int argc, char* argv[], int&);
	bool stop();
	bool shutdown();
	void interrupt();
	bool Init();
	bool Uninit();
	/*=========================================================================
	����  �����÷�������ͻ���ͨ��Э�飬Ĭ��ʹ��ice��Ĭ������tcp
	����  ��szProcȡֵ�� tcp  udpȫ��д����ȫСд
	����ֵ���ɹ�����true�����벻֧�ֵ�Э���ַ����򷵻�false
	��ע  ��Ŀǰ֧��tcp
	����  ��2015.7 xly
	=========================================================================*/
	bool SetProtocol(const string& szProc);
	/*=========================================================================
	����  ������ת������Ľ��յ�ַ�Ͷ˿�
	����  ��
	����ֵ���ɹ�����true������������Ϸ��򷵻�false��
	��ע  ��
	����  ��2015.7 xly
	=========================================================================*/
	bool SetServerAddr(const string& IPstr, const unsigned short port );
	/*=========================================================================
	����  ��������һ�δ�����Ϣ
	����  ��
	����ֵ�����ش�����Ϣ��������
	��ע  ��
	����  ��2015.7 xly
	=========================================================================*/
	const string& GetLastErr()const;
private:
	//����˵��ַ���
	string MakeEndpointStr();
protected:
	CommunicatorPtr		m_comm_ptr;		//ice�����ָ��
	ObjectAdapterPtr	m_adpt_ptr;		//�����������ָ��
	ProxySvrPtr			m_proc_ptr;		//ҵ�������ָ��

	string				m_protc;		//ͨ��ʹ�õ�Э��
	string				m_szIP;			//����ip��ַ
	unsigned short		m_wport;		//�����˿�

	string				m_err_msg;		//������Ϣ
};