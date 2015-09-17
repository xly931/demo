#include "ProxyMangr.h"
extern string g_ip ;
extern unsigned short g_port;
//=====================================================
TestServver::TestServver()
{
	//m_thread = NULL;
	m_thread_flag = false;
}
TestServver::~TestServver()
{
	stop();
}
void TestServver::start(const int num, const int interval)
{
	m_proxy_num = num;
	m_send_interval = interval;
	for (int cnt = 0;cnt < num; ++cnt)
	{
		HSProxy proxy;
		proxy.Init("tcp",g_ip,g_port);
		cout<<"\t\tproxy:"<<cnt+1<<"\tcreated"<<endl;
		m_prx_vec.push_back(proxy);
	}
	m_thread_flag = true;
#ifdef WIN32
	m_thread = _beginthread(CallBack,0,this);    
#else
	int ret =  pthread_create(&m_thread, NULL, &CallBack, this);
	if (0 != ret)
	{
		cout<<"----------ouch-----------"<<endl;
	}
#endif
}
void TestServver::stop()
{
	m_thread_flag = false;
}

void TestServver::print_max_time()
{
	while(!(m_heap_que.empty()))
	{
		cout<<m_heap_que.top()<<" ";
		m_heap_que.pop();
	}
	cout<<endl;
}
#ifdef WIN32
void TestServver::CallBack(void* arg)
#else
void* TestServver::CallBack(void* arg)
#endif
{
	TestServver* pObj = (TestServver*)arg;

	HSPW::TagProxySvr srvIn;
	HSPW::TagProxySvr srvOut;
	srvIn.cmd = 100;
	srvIn.serial = 99;
	srvIn.data = "from client,try to find something to fill this string,we hope the length of this string is as long as a regular json string,i'm not sure about \
				 the normal size of a json string ,try to provide more,it can be overwhelmed but not be too few ,repeat this 999 times----- \
				 from client,try to find something to fill this string,we hope the length of this string is as long as a regular json string,i'm not sure about \
				 the normal size of a json string ,try to provide more,it can be overwhelmed but not be too few ,repeat this 999 times----- \
				 from client,try to find something to fill this string,we hope the length of this string is as long as a regular json string,i'm not sure about \
				 the normal size of a json string ,try to provide more,it can be overwhelmed but not be too few ,repeat this 999 times-----";
	srvIn.data += srvIn.data;

	while(pObj->m_thread_flag)
	{
		for (std::vector<HSProxy>::iterator it = pObj->m_prx_vec.begin();it != pObj->m_prx_vec.end();it++)
		{
			pObj->m_tic_cnt.Begin();
			it->do_func(srvIn,srvOut);
			pObj->m_heap_que.push(pObj->m_tic_cnt.Endf());
			if (pObj->m_heap_que.size() > 20 )//目前保留20个最大的时间记录
			{
				pObj->m_heap_que.pop();//删除最小的时间
			}
			hs_sleep(pObj->m_send_interval);
		}
	}
#ifdef WIN32
	_endthread();
#else
	pthread_detach(pthread_self());
	pthread_exit(NULL);
	return NULL;
#endif
}

//====================================================================
void Manager::start()
{
	int thread_num = 1;	//线程数量
	int prxNumPerThd = 5;	//每个线程创建的proxy数量
	int interval = 200;		//一个线程中，每个代理发送请求的间隔
	for (int cnt = 0;cnt < thread_num;++cnt)
	{
		cout<<"------thread:"<<cnt+1<<"\tcreated"<<endl;
		TestServver tstSrv;
		_test_list.push_back(tstSrv);
		_test_list.back().start(prxNumPerThd,interval);
	}
}

void Manager::stop()
{
	for (std::list<TestServver>::iterator it = _test_list.begin();it != _test_list.end();it++)
	{
		it->stop();
	}
	hs_sleep(500);//等待线程正常结束
	for (std::list<TestServver>::iterator it = _test_list.begin();it != _test_list.end();it++)
	{
		it->print_max_time();
	}
}

