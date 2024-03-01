#include "thread_hdr.h"
unsigned int clock;
unsigned int limit;
void add_ready_thread(thread* ready_thread)
{
	// 相应的代码实现
	ready_queue.push_back(ready_thread);
}

void schedule()
{
	// 相应的代码实现
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
	// 实现的代码
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
	// 相应的代码实现
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
	// 相应的代码实现
	if (blocked_queue.empty()) { return; }
	thread* thread = blocked_queue.front();
	blocked_queue.pop_front();
	ready_queue.push_back(thread);
}

void notify_all()
{
	thread* thread = NULL;
	// 相应的代码实现
	while (!blocked_queue.empty()) {
		thread = blocked_queue.front();
		blocked_queue.pop_front();
		ready_queue.push_back(thread);
	}
}

void on_clock()
{
	// 相应的代码实现
	if (current_thread == &idle_thread) {
		schedule();
		current_thread->clock_times = 0;
	}
	else {
		current_thread->clock_times += clock;
		if (current_thread->clock_times >= limit) {
			schedule();
			current_thread->clock_times = 0;
		}
	}
}

void set_time_ticks(unsigned int ticks)
{
	// 相应的代码实现
	limit = ticks;
}

void set_time_interval(unsigned int interval)
{
	// 相应的代码实现
	clock = interval;
}