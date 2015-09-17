#include "ForwardServer.h"
#include <stdlib.h>
int main(int argc, char* argv[])
{
	CHSFowarderServer server;
	int i = 0;
	server.start(argc,argv, i);
	cout<<server.GetLastErr()<<endl;
	g_stcs.print_data();
	system("pause");
	return 0;
}