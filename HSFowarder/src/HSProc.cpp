#include "HSProc.h"


void Statictics::CallCount()
{
	++m_count;
}
void Statictics::print_data()
{
	std::cout<<"call count:"<<m_count<<std::endl;
}
Statictics g_stcs;
//Job::Job(HSFoward::AMD_HSBnsProc_amdfunPtr cb_ptr,::Ice::Int num, const ::std::string& str)
//{
//	m_cb = cb_ptr;
//	m_num = num;
//	m_str = str;
//}
//
//void Job::execute()
//{
//	std::cout<<"CallBack, execute,here,we are in a async function"<<std::endl;
//	m_cb->ice_response(m_str+"<=========");
//}
/*===================================================*/
bool IHSbnsProc::Procedure(const ::HSPW::TagProxySvr& tagIn, ::HSPW::TagProxySvr& tagOut, const ::Ice::Current&)
{
	std::cout<<"cmd:"<<tagIn.cmd<<", seri:"<<tagIn.serial<<", data:"<<tagIn.data<<std::endl;
	//Sleep(30);//每次处理耗时30ms
	//g_stcs.CallCount();
	tagOut.cmd = tagIn.cmd +1;
	tagOut.status = 0;
	tagOut.serial = tagIn.serial + 1;
	//tagOut.data = "back data===" + tagIn.data;
	tagOut.data = "{\
		\"syspm1\": \"orgnize id\",\
		\"syspm2\": \"fund account\"\
		}";
	std::cout<<"back data========>\n"<<tagOut.data<<std::endl;
	return true;
}