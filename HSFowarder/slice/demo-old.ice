module WtOrder
{
	struct tagOrderRet
	{
		int retcode;	// 错误码
		int wth;		// 委托号
		int packid;		// 发来的包号,不重复
	};
	
	sequence<string>	strque;
	
	interface OrderProc
	{
		["amd"] tagOrderRet SendOrder(int packid, long userid, int zjzh, byte mmbz, byte market, string code, int wtjg, int wtsl);
		["amd"] tagOrderRet OptSendOrder(int packid, long userid, int zjzh, byte mmbz, byte market, string code, int wtjg, int wtsl, byte wtfs, string stkcode, byte stkmarket);
		["amd"] tagOrderRet CancelOrder(int packid, long userid, int zjzh, int wth, byte mmbz, byte market, string code);
		int		SettlingAccounts();
		int		GetSvrStatus();								// 得到服务器目前所处的状态
		int		ReportSvrStats(string user, string pass);	// 报告服务器统计数据
		
		// 维护类------------
		// 报告订单状态
		strque	ReportOrderStatus(int wth, int zjzh, long fullcode);
		// 日志中输出所有的本股票订单
		void	ReportOrderStatusByStock(int fullcode);
		// 重新加载订单
		int		ReloadOrder(int wth);
	};
};