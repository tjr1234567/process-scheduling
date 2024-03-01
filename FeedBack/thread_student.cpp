#include "thread_hdr.h"
unsigned int first_time_ticks;
unsigned int second_time_ticks;
unsigned int clock;
void add_ready_thread(thread* ready_thread)
{
	// 相应的代码实现
	ready_thread->max_clock_times = first_time_ticks;
	first_ready_queue.push_back(ready_thread);
}

void schedule()
{
	// 相应的代码实现
	if (current_thread != &idle_thread) {
		current_thread->max_clock_times = second_time_ticks;
		second_ready_queue.push_back(current_thread);
	}
	if (!first_ready_queue.empty()) {
		current_thread = first_ready_queue.front();
		first_ready_queue.pop_front();
	}
	else {
		if (!second_ready_queue.empty()) {
			current_thread = second_ready_queue.front();
			second_ready_queue.pop_front();
		}
	}
}

void current_thread_finished()
{
    // 相应的代码实现
	if (!first_ready_queue.empty()) {
		current_thread = first_ready_queue.front();
		first_ready_queue.pop_front();
	}
	else {
		if (!second_ready_queue.empty()) {
			current_thread = second_ready_queue.front();
			second_ready_queue.pop_front();
		}
		else {
			current_thread = &idle_thread;
		}
	}
}

void current_thread_blocked()
{
    // 相应的代码实现
	current_thread->clock_times = 0;
	blocked_queue.push_back(current_thread);
	if (!first_ready_queue.empty()) {
		current_thread = first_ready_queue.front();
		first_ready_queue.pop_front();
	}
	else {
		if (!second_ready_queue.empty()) {
			current_thread = second_ready_queue.front();
			second_ready_queue.pop_front();
		}
		else {
			current_thread = &idle_thread;
		}
	}
}

void notify()
{
    // 相应的代码实现
	if (blocked_queue.empty()) { return; }
	thread* thread = blocked_queue.front();
	blocked_queue.pop_front();
	thread->clock_times = 0;
	thread->max_clock_times = first_time_ticks;
	first_ready_queue.push_back(thread);
}

void notify_all()
{
    // 相应的代码实现
	thread* thread = NULL;
	// 相应的代码实现
	while (!blocked_queue.empty()) {
		thread = blocked_queue.front();
		thread->clock_times = 0;
		thread->max_clock_times = first_time_ticks;
		blocked_queue.pop_front();
		first_ready_queue.push_back(thread);
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
		if (current_thread->clock_times >= current_thread->max_clock_times) {
			current_thread->clock_times = 0;
			schedule();
			//current_thread->clock_times = 0;
		}
		if (current_thread->max_clock_times == second_time_ticks && !first_ready_queue.empty()) {
			current_thread->clock_times = 0;
			schedule();
		}
	}
}

void set_first_time_ticks(unsigned int ticks)
{
    // 相应的代码实现
	first_time_ticks = ticks;
}

void set_second_time_ticks(unsigned int ticks)
{
    // 相应的代码实现
	second_time_ticks = ticks;
}

void set_time_interval(unsigned int interval)
{
    // 相应的代码实现
	clock = interval;
}