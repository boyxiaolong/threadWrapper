threadWrapper是对于线程操作的简单封装。  
工作原理是：创建线程时需要传入逻辑处理回调；threadWrapper::start会启动一个线程，通过threadWrapper:send向线程投递数据；threadWrapper内部会在线程里
不停消费数据，当然因为创建时设置了处理回调，最终数据如何处理还是逻辑层handle。  
具体示例可以参考main.cpp，这里可以快速封装一个异步日志库。  
A simple wrapper for thread.
