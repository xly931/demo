#include "HSProxy.h"
#include "ProxyMangr.h"
#include <queue>
#include <stdlib.h>
//-----------------
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

string g_ip = "10.100.5.2";
unsigned short g_port = 9995;
std::greater<long> gt;
void test()
{
	std::priority_queue<long,vector<long>,greater<long> > heap_que;
	heap_que.push(5);
	heap_que.push(1);
	heap_que.push(7);
	heap_que.push(3);
	heap_que.push(4);
	std::cout<<heap_que.top()<<std::endl;
	heap_que.pop();
	std::cout<<heap_que.top()<<std::endl;
}
void Connect(const string& ip, unsigned short port)
{
	int cfd = socket(AF_INET, SOCK_STREAM,0); 
	if (-1 == cfd)
	{
		std::cout<<"create socket failed"<<std::endl;
	}
	struct sockaddr_in s_add,c_add;
	memset(&s_add,0,sizeof(struct sockaddr_in));  
	s_add.sin_family=AF_INET;  
	s_add.sin_addr.s_addr= inet_addr(ip.data()); /* ip转换为4字节整形，使用时需要根据服务端ip进行更改 */  
	s_add.sin_port=htons(port);

	if(-1 == connect(cfd,(struct sockaddr *)(&s_add), sizeof(struct sockaddr)))  
	{  
		printf("connect fail !\r\n");  
	}  
	printf("connect ok !\r\n");
}
int main(int argc, char* argv[])
{

	if (argc >= 2)
	{
		g_ip = argv[1];
	}
	if (argc >= 3)
	{
		string port_str = argv[2];
		g_port = atoi(port_str.c_str());
	}

	Manager mng;
	//Connect(g_ip,g_port);
	mng.start();
	char c;
	cin>>c;
	mng.stop();
	cin>>c;
	return 0;
}



