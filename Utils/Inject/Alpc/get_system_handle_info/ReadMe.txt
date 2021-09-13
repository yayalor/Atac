Handle用法：
获取进程句柄信息
processName, PID, handleType, TypeIndex, HandleName

最主要的是TypeIndex， pchunter不能用了，暂时还没找到能查看ALPC PORT值得工具，就改了改这个。

使用：

1.获取系统所有句柄信息(不加任何参数)

.\Handle.exe 

2.获取指定进程的句柄信息 (参数为进程名或者PID)

.\Handle.exe 进程名|PID

3.获取指定进程的特定类型句柄信息 (参数为进程名或者PID + /t + 类型名)

.\Handle.exe 进程名|PID /t alpc

4.获取指定进程的特定类型句柄信息，不需要显示句柄名称(参数为进程名或者PID + /t + 类型名)

.\Handle.exe 进程名|PID /n 