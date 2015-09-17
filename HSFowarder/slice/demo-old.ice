module WtOrder
{
	struct tagOrderRet
	{
		int retcode;	// ������
		int wth;		// ί�к�
		int packid;		// �����İ���,���ظ�
	};
	
	sequence<string>	strque;
	
	interface OrderProc
	{
		["amd"] tagOrderRet SendOrder(int packid, long userid, int zjzh, byte mmbz, byte market, string code, int wtjg, int wtsl);
		["amd"] tagOrderRet OptSendOrder(int packid, long userid, int zjzh, byte mmbz, byte market, string code, int wtjg, int wtsl, byte wtfs, string stkcode, byte stkmarket);
		["amd"] tagOrderRet CancelOrder(int packid, long userid, int zjzh, int wth, byte mmbz, byte market, string code);
		int		SettlingAccounts();
		int		GetSvrStatus();								// �õ�������Ŀǰ������״̬
		int		ReportSvrStats(string user, string pass);	// ���������ͳ������
		
		// ά����------------
		// ���涩��״̬
		strque	ReportOrderStatus(int wth, int zjzh, long fullcode);
		// ��־��������еı���Ʊ����
		void	ReportOrderStatusByStock(int fullcode);
		// ���¼��ض���
		int		ReloadOrder(int wth);
	};
};