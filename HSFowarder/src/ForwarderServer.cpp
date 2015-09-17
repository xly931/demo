#include "ForwardServer.h"
#include <exception>

CHSFowarderServer::CHSFowarderServer()
{
	SetProtocol("tcp");
	SetServerAddr("10.100.5.2",9995);
}
CHSFowarderServer::~CHSFowarderServer()
{

}

bool CHSFowarderServer::start(int argc, char* argv[], int&)
{
	Ice::PropertiesPtr props = Ice::createProperties();
	//props->load("E:\\config.cfg");
	props->load("config.cfg");
	//props->setProperty("Ice.Config","E:\\config.cfg");
	//props->setProperty("Ice.ThreadPool.Server.Size","10");
	//props->setProperty("Ice.ThreadPool.Server.SizeMax","20");
	//cout<<props->getProperty("Ice.Config")<<endl;
	//cout<<props->getProperty("Ice.ThreadPool.Server.Size")<<endl;
	Ice::InitializationData tInitData;
	tInitData.properties = props;
	
	cout<<props->getProperty("Ice.Config")<<endl;
	cout<<props->getProperty("Ice.ThreadPool.Server.Size")<<endl;
	cout<<props->getProperty("Ice.ThreadPool.Server.SizeMax")<<endl;
	if (!Init())
	{
		return false;
	}

	try
	{
		m_comm_ptr = Ice::initialize(tInitData);
		if (m_comm_ptr==NULL)
		{
			m_err_msg = "³õÊ¼»¯ICEÊ§°Ü";
			return false;
		}

		string sEndpoint = MakeEndpointStr();
		cout<<"endpoint£º"<<sEndpoint<<endl;
		m_adpt_ptr = m_comm_ptr->createObjectAdapterWithEndpoints("HSProxyWAdpt", sEndpoint);
		if(NULL == m_adpt_ptr)
		{
			m_err_msg = "´´½¨ÊÊÅäÆ÷Ê§°Ü";
			return false;
		}

		m_proc_ptr = new IHSbnsProc;
		m_adpt_ptr->add(m_proc_ptr, m_comm_ptr->stringToIdentity("HSProxyW"));

		m_adpt_ptr->activate();
		m_comm_ptr->waitForShutdown();
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

	cout<<"Chsvr'ice module has ready!"<<endl;
	return true;
}

bool  CHSFowarderServer::stop()
{
	cout<<"chsvr begin stop !"<<endl;
	m_adpt_ptr->deactivate();
	m_adpt_ptr->destroy();
	m_comm_ptr->shutdown();
	m_proc_ptr = NULL;

	Uninit();
	return Ice::Service::stop();
}
bool  CHSFowarderServer::shutdown()
{
	return true;
}
void  CHSFowarderServer::interrupt()
{
	
}
bool CHSFowarderServer::Init()
{
	return true;
}

bool CHSFowarderServer::Uninit()
{
	return true;
}
bool CHSFowarderServer::SetProtocol(const string& szProc)
{
	if (szProc.compare("udp") == 0
		|| szProc.compare("UDP") == 0
		|| szProc.compare("tcp") == 0
		|| szProc.compare("TCP") == 0)
	{
		m_protc = szProc;
		return true;
	}
	return false;
}
bool CHSFowarderServer::SetServerAddr(const string& IPstr, const unsigned short port )
{
	//check ip ,todo
	m_szIP  = IPstr;
	m_wport = port;
	return true;
}

const string& CHSFowarderServer::GetLastErr()const
{
	return m_err_msg;
}
string CHSFowarderServer::MakeEndpointStr()
{
	ostringstream oss;
	oss<<m_protc << " " <<" -h " << m_szIP << " -p " << m_wport;
	return oss.str();
}