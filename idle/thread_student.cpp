#include "thread_hdr.h"

void add_ready_thread(thread* ready_thread)
{
	// ��Ӧ�Ĵ���ʵ��
	ready_queue.push_back(ready_thread);
}

void schedule()
{
	// ��Ӧ�Ĵ���ʵ��
	if (current_thread != &idle_thread) {
		ready_queue.push_back(current_thread);
	}
	if (!ready_queue.empty()) {
		current_thread = ready_queue.front();
		ready_queue.pop_front();
	}
}

void current_thread_finished()
{
	// ʵ�ֵĴ���
	if (!ready_queue.empty()) {
		current_thread = ready_queue.front();
		ready_queue.pop_front();
	}
	else {
		current_thread = &idle_thread;
	}
}