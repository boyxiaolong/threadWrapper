对于线程的简单封装。
工作原理是：创建线程时需要传入逻辑处理回调；
threadWrapper::start会启动一个线程，通过threadWrapper:send向线程投递数据；
逻辑层响应回调，这里只是实现了个简单的工作线程，很方便做扩展。
具体示例可以参考main.cpp.这里可以快速封装一个异步日志库。
A simple wrapper for thread.
