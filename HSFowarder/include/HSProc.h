#pragma once
#include <list>
#include <Ice/Ice.h>
#include <IceUtil/IceUtil.h>
#include "ProxySvr.h"
using namespace Ice;

//class Job:public IceUtil::Shared
//{
//public:
//	Job(HSFoward::AMD_HSBnsProc_amdfunPtr cb_ptr,::Ice::Int num, const ::std::string& str);
//private:
//	void execute();
//private:
//	HSFoward::AMD_HSBnsProc_amdfunPtr m_cb;
//	int				m_num;
//	std::string		m_str;
//};
//typedef IceUtil::Handle<Job> JobPtr;
class IHSbnsProc:virtual public HSPW::ProxySvr
{
	 virtual bool Procedure(const ::HSPW::TagProxySvr&, ::HSPW::TagProxySvr&, const ::Ice::Current& = ::Ice::Current());
	//std::list<JobPtr> m_job_list;
};

//ͳ�Ʒ���˵Ĵ�������
class Statictics
{
public:
	void CallCount();
	void print_data();

public:
	unsigned long m_count;	//ͳ���������

};
extern Statictics g_stcs;