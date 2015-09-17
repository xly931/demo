#pragma once
#include "ProxySvr.h"
#include <Ice/Ice.h>
using namespace Ice;
using namespace std;
using namespace HSPW;

/*=========================================================================
类描述：封装ICE的客户端代理
接口  ：
备注  ：
日期  ：2015.7 xly
=========================================================================*/
class HSProxy
{
public:
	HSProxy();
	~HSProxy();
	/*=========================================================================
	功能  ：初始化ICE代理对象
	参数  ：依次为ice对象id，通信协议，服务端ip，服务端端口
	返回值：
	备注  ：
	日期  ：2015.7 xly
	=========================================================================*/
	bool Init(const string& szProtocol,const string szIP, unsigned short port);
	/*=========================================================================
	功能  ：断开服务器
	参数  ：
	返回值：
	备注  ：
	日期  ：2015.7 xly
	=========================================================================*/
	void DisConnect();
	/*=========================================================================
	功能  ：获得最后一次错误信息
	参数  ：
	返回值：
	备注  ：
	日期  ：2015.7 xly
	=========================================================================*/
	const string& GetLastErr()const;


	void do_func(const ::HSPW::TagProxySvr& tagIn, ::HSPW::TagProxySvr& tagOut);
	void do_sync();
private:
	//构造服务器端点字符串表示方式
	string MakeEndpointStr();
private:
	CommunicatorPtr	m_comm_ptr;		//ice主句柄，todo：是否可初始化两次
	ProxySvrPrx		m_proxy;		//ice对象的代理

	string			m_protocol;		//通信协议
	string			m_srv_obj_idf;	//服务端ice对象id标识
	string			m_srv_IP;		//服务端ip地址
	unsigned short	m_srv_port;		//服务端端口

	string			m_err_msg;		//保存最后一次错误信息
};
