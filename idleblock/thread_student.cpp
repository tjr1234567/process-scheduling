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

void current_thread_blocked()
{
	// ��Ӧ�Ĵ���ʵ��
	blocked_queue.push_back(current_thread);
	if (!ready_queue.empty()) {
		current_thread = ready_queue.front();
		ready_queue.pop_front();
	}
	else {
		current_thread = &idle_thread;
	}
}

void notify()
{
	// ��Ӧ�Ĵ���ʵ��
	if (blocked_queue.empty()) { return; }
	thread* thread = blocked_queue.front();
	blocked_queue.pop_front();
	ready_queue.push_back(thread);
}

void notify_all()
{
	thread* thread = NULL;
	// ��Ӧ�Ĵ���ʵ��
	while (!blocked_queue.empty()) {
		thread = blocked_queue.front();
		blocked_queue.pop_front();
		ready_queue.push_back(thread);
	}
}