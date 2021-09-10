by Yayale
步骤1、提权
步骤2、获取远线程句柄 openprocess
步骤3、遍历SystemHandleInformation , 根据ALPC PORT特征拿到当前进程的ALPC PORT名称(我在这里做了优化, 判断名称是否有"RPC",避免连接其他类型ALPC导致进程崩溃而注入失败)
步骤4、获取系统信息,遍历进程所有地址,根据TP_CALLBACK_OBJECT 回调结构体特征找到回调函数地址
步骤5、将payload写入远线程,并将回调函数地址设为Payload起始地址,连接端口等.
步骤6、校验回调函数是否修改成功.