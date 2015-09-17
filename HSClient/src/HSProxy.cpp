#include "HSProxy.h"

HSProxy::HSProxy()
{

}
HSProxy::~HSProxy()
{

}
bool HSProxy::Init(const string& szProtocol,const string szIP, unsigned short port)
{
	m_srv_obj_idf	= "HSProxyW";
	m_protocol		= szProtocol;
	m_srv_IP		= szIP;
	m_srv_port		= port;

	string szEndpoint = MakeEndpointStr();
	try
	{
		m_comm_ptr = Ice::initialize();
		if (NULL == m_comm_ptr.get())
		{
			m_err_msg = "初始化ICE失败";
			return false;
		}
		ObjectPrx base = m_comm_ptr->stringToProxy(szEndpoint);
		m_proxy = HSPW::ProxySvrPrx::checkedCast(base);
		if (NULL == m_proxy.get())
		{
			m_err_msg = "创建ICE本地代理失败";
			return false;
		}
		static int i = 0;
		cout<<"---------------------------------------"<<++i<<"--------------------------------------"<<endl;
		cout<<"BEFORE:"<<endl;
		system("netstat -anp | grep 9995");
	}
	catch (Ice::SocketException& e)
	{
		m_err_msg = "network error, ";
		m_err_msg += e.what();
		e.ice_print(cout);
		return false;
	}
	catch (Ice::Exception& e)
	{
		m_err_msg = "ICE error,";
		m_err_msg += e.what();
		e.ice_print(cout);
		return false;
	}
	catch(std::exception& e)
	{
		m_err_msg = "System error,";
		m_err_msg += e.what();
		return false;
	}
	catch (...)
	{
		m_err_msg = "unknown erroe!";
		return false;
	}
	return true;
}
void HSProxy::DisConnect()
{
	m_comm_ptr->shutdown();
	m_comm_ptr->destroy();
	m_comm_ptr = NULL;
	std::cout<<"disconnect called\n";
}
string HSProxy::MakeEndpointStr()
{
	ostringstream oss;
	oss<<m_srv_obj_idf<<":"<<m_protocol<<" -h "<<m_srv_IP<<" -p "<<m_srv_port;
	return oss.str();
}
const string& HSProxy::GetLastErr()const
{
	return m_err_msg;
}
void HSProxy::do_func(const ::HSPW::TagProxySvr& tagIn, ::HSPW::TagProxySvr& tagOut)
{
	try
	{
		m_proxy->Procedure(tagIn,tagOut);
		//std::cout<<"---> cmd:"<<tagIn.cmd<<", seri:"<<tagIn.serial<<", data:"<<tagIn.data<<std::endl;
		//std::cout<<"<--- cmd:"<<tagOut.cmd<<", seri:"<<tagOut.serial<<", data:"<<tagOut.data<<std::endl;
	}
	catch(const Ice::TimeoutException& e)
	{
		m_err_msg = "timeout error, ";
		m_err_msg += e.what();
		cout << m_err_msg;
	}
	

	//cout << m_proxy->fun(num,str)<<endl;
}
void HSProxy::do_sync()
{
	//::Ice::AsyncResultPtr ret_ptr = m_proxy->begin_amdfun(33,"aaasssyyynnnccc");
	//cout<<"before get ret\n";
	//cout<< m_proxy->end_amdfun(ret_ptr) << endl;
	//cout<<"after get ret\n";
}
