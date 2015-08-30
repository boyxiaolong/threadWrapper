#ifndef THREAD_WRAPPER_
#define THREAD_WRAPPER_

#include <thread>
#include <functional>
#include <memory>
#include <queue>
#include <mutex>
#include <string>
#include "Buffer.h"
#include <atomic>
#include <vector>
#include <set>


typedef std::function<void(Buffer*&)> Callback;
typedef std::function<void()> BeginInThreadCallback;

class threadWrapper {
private:
	threadWrapper(const threadWrapper&);
	threadWrapper& operator=(const threadWrapper&);
	threadWrapper();
	threadWrapper(int n32BlockSize, int n32BufferSize);
	void Run();
	void RunWithUpdate();
	void setCallBack(Callback aCallBack);
	bool IfEmpty();
	void Consume();
	std::queue<Buffer*> m_Queue;
	std::thread	m_Thread;
	Callback		m_Callback;
	std::mutex	m_IOMutex;
	std::condition_variable m_ConditionVar;
	std::atomic<int>		m_PendingWorkNum;
    std::atomic<bool>	m_IfNeedSig;
	unsigned		m_ThreadID;
	std::queue<Buffer*> m_SwapQueue;
	bool m_IfUpdate;
	bool m_IsStop;
public:
	~threadWrapper();
	void			send(Buffer* apBuffer);
	void			stop();
	static threadWrapper*	createThread(Callback aCallBack, int n32BlockSize, int b32BufferSize);
	int				getPendingWorkNum()const{return m_PendingWorkNum;}
	unsigned		getThreadID();

	void			start();
	void			setThreadStartCallback(BeginInThreadCallback pBeginInThreadCallback);

private:
	BeginInThreadCallback m_BeginInThreadCallback;
};

#endif