#pragma once
#include <Ice/Ice.h>
#include <Ice/Service.h>
#include "HSProc.h"
#include <string>
using namespace std;
using namespace Ice;
using namespace HSPW;
/*=========================================================================
类描述：实现转发服务的服务器类
接口  ：
备注  ：
日期  ：2015.7 xly
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
	功能  ：设置服务器与客户端通信协议，默认使用ice的默认设置tcp
	参数  ：szProc取值： tcp  udp全大写或者全小写
	返回值：成功返回true，传入不支持的协议字符串则返回false
	备注  ：目前支持tcp
	日期  ：2015.7 xly
	=========================================================================*/
	bool SetProtocol(const string& szProc);
	/*=========================================================================
	功能  ：设置转发服务的接收地址和端口
	参数  ：
	返回值：成功返回true，如果参数不合法则返回false。
	备注  ：
	日期  ：2015.7 xly
	=========================================================================*/
	bool SetServerAddr(const string& IPstr, const unsigned short port );
	/*=========================================================================
	功能  ：获得最后一次错误信息
	参数  ：
	返回值：返回错误信息文字描述
	备注  ：
	日期  ：2015.7 xly
	=========================================================================*/
	const string& GetLastErr()const;
private:
	//构造端点字符串
	string MakeEndpointStr();
protected:
	CommunicatorPtr		m_comm_ptr;		//ice主句柄指针
	ObjectAdapterPtr	m_adpt_ptr;		//服务端适配器指针
	ProxySvrPtr			m_proc_ptr;		//业务处理对象指针

	string				m_protc;		//通信使用的协议
	string				m_szIP;			//监听ip地址
	unsigned short		m_wport;		//监听端口

	string				m_err_msg;		//错误信息
};