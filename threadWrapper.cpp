#include "threadWrapper.h"

threadWrapper::threadWrapper(){}

threadWrapper::threadWrapper(int n32BlockSize, int n32BufferSize): m_PendingWorkNum(0), m_ThreadID(0), m_BeginInThreadCallback(NULL)
, m_IfUpdate(false), m_IsStop(false){
}

threadWrapper::~threadWrapper() {
	stop();
}

void threadWrapper::send(Buffer* apBuffer){
	if (m_IsStop)
	{
		return;
	}

	if (NULL != apBuffer){
        m_IOMutex.lock();
		bool bNeedSig = m_Queue.empty();
		m_Queue.push(apBuffer);
		m_IOMutex.unlock();
		++m_PendingWorkNum;
		if (bNeedSig){
			m_ConditionVar.notify_one();
		}
	}
}

void threadWrapper::Run() {
	if (m_BeginInThreadCallback){
		m_BeginInThreadCallback();
	}
	while (true){
		Consume();
	}
}

threadWrapper* threadWrapper::createThread(Callback aCallBack, int n32BlockSize, int n32BufferSize){
	threadWrapper* aPtr = new threadWrapper(n32BlockSize, n32BufferSize);
	aPtr->m_Callback = aCallBack;
	return aPtr;
}

void threadWrapper::setCallBack(Callback aCallBack){
	m_Callback = aCallBack;
}

bool threadWrapper::IfEmpty(){
	return m_Queue.empty();  
}

void threadWrapper::Consume(){
    std::unique_lock<std::mutex> lock(m_IOMutex);
	while(m_Queue.empty()){
		m_ConditionVar.wait(lock);
	}

	m_SwapQueue.swap(m_Queue);
	lock.unlock();

	while(!m_SwapQueue.empty()){
		Buffer* pBuffer = m_SwapQueue.front();
		m_SwapQueue.pop();

		m_Callback(pBuffer);
		--m_PendingWorkNum;
		if (pBuffer){
            delete pBuffer;
		}
	}
}

void threadWrapper::stop(){
	if (m_IsStop)
	{
		return;
	}
	printf("thread %u is try to stop\n", m_ThreadID);
	m_IsStop = true;
	m_ConditionVar.notify_one();
}


unsigned threadWrapper::getThreadID(){
	return m_ThreadID;
}

void threadWrapper::RunWithUpdate(){
	bool ifNotify = false;
	bool ifQueueEmpty = false;
	while(true){
		ifNotify = false;
		ifQueueEmpty = false;
	}
}

void threadWrapper::start(){
    m_Thread = std::thread(&threadWrapper::Run, this);
}

void threadWrapper::setThreadStartCallback(BeginInThreadCallback pBeginInThreadCallback){
	m_BeginInThreadCallback = pBeginInThreadCallback;
}

int Buffer::GetMaxLength(){
	return m_MaxLength;
}
