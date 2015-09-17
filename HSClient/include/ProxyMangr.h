#pragma once
#include "HSProxy.h"
#include <vector>
#include <list>
#include <queue>
#ifdef WIN32
#define hs_sleep Sleep
#include <PROCESS.H>  
#include <windows.h>  
#else
#include <pthread.h>
#define hs_sleep usleep
#endif


#ifdef WIN32
// 高精度计时器
class CTickCount
{
public:
	inline CTickCount()
	{
		QueryPerformanceFrequency(&Frequency);
	}

	// 计时开始
	inline void Begin()
	{
		QueryPerformanceCounter(&nTickBegin);
	}

	// 计时结束，单位us
	inline unsigned int End()
	{
		QueryPerformanceCounter(&nTickEnd);
		return static_cast<unsigned int>(1000000 * ( nTickEnd.QuadPart- nTickBegin.QuadPart) / Frequency.QuadPart);
	};
	inline double EndMs()
	{
		return double(End())/1000.0;
	};

	inline double Endf()
	{
		return double(End());
	};

	inline string Endstr()
	{
		char fmt[1024]={0};
		double fValue = Endf();
		sprintf_s(fmt,"%.3f", fValue);
		return string(fmt);
	};
protected:
private:
	LARGE_INTEGER Frequency;
	LARGE_INTEGER nTickBegin;
	LARGE_INTEGER nTickEnd;
};
#else
class CTickCount
{
public:
	inline CTickCount()
	{
	}

	//inline unsigned INT64 tick()
	//{
	//	gettimeofday(&btv,NULL);
	//	return 1000000 * btv.tv_sec+btv.tv_usec;
	//}

	inline void Begin()
	{
		gettimeofday(&btv,NULL);
	}

	//inline unsigned INT64 end()
	//{
	//	gettimeofday(&etv,NULL);
	//	return 1000000 * (etv.tv_sec - btv.tv_sec)+ (etv.tv_usec-btv.tv_usec) ;
	//}

	inline double Endf()
	{
		gettimeofday(&etv,NULL);
		return (double)(1000000 * (etv.tv_sec - btv.tv_sec)+ (etv.tv_usec-btv.tv_usec)) ;
	}
protected:
private:
	struct timeval btv;
	struct timeval etv;
};

#endif
/*=========================================================================
类描述：封装一个线程，以及其执行的ice proxy
接口  ：
备注  ：一个线程中有一个proxy列表，根据指定的时间间隔，轮询执行每隔proxy的接口
日期  ：2015.7 xly
=========================================================================*/
class TestServver
{
public:
	TestServver();
	~TestServver();
	void start(const int num, const int interval);
	void stop();
	void print_max_time();
private:
#ifdef WIN32
	static void CallBack(void* arg);
#else
	static void* CallBack(void* arg);
#endif
private:
	int			m_proxy_num;		//proxy的个数
	int			m_send_interval;	//发送请求的频率，间隔毫秒
	bool		m_thread_flag;
#ifdef WIN32
	uintptr_t	m_thread;
#else
	pthread_t	m_thread;
#endif
	std::vector<HSProxy> m_prx_vec;
	CTickCount m_tic_cnt;
	priority_queue<double, vector<double>, greater<double> > m_heap_que; //比较函数执行时间的小根堆，只保留执行时间最长的数据，故选择使用小根堆结构
};
/*=========================================================================
类描述：创建测试线程的类
接口  ：
备注  ：
日期  ：2015.7 xly
=========================================================================*/
class Manager
{
public:
	void start();
	void stop();
private:
	std::list<TestServver> _test_list;//需要将this传给线程回调，因此不能使用vector
};

