#include "consumer_queue.h"
#include "common.h"
#include "sample.h"
#include "send_buffer.h"
#include <chrono>

using namespace lsl;

consumer_queue::consumer_queue(std::size_t max_capacity, send_buffer_p registry)
	: registry_(registry), buffer_(max_capacity) {
	if (registry_) registry_->register_consumer(this);
}

consumer_queue::~consumer_queue() {
	try {
		if (registry_) registry_->unregister_consumer(this);
	} catch (std::exception &e) {
		LOG_F(ERROR,
			"Unexpected error while trying to unregister a consumer queue from its registry: %s",
			e.what());
	}
}

void consumer_queue::push_sample(const sample_p &sample) {
	while (!buffer_.push(sample)) {
		sample_p dummy;
		buffer_.pop(dummy);
	}
	cv_.notify_one();
}

sample_p consumer_queue::pop_sample(double timeout) {
	sample_p result;
	if (timeout <= 0.0) {
		buffer_.pop(result);
	} else {
		if (!buffer_.pop(result)) {
			// wait untill for a new sample until the thread calling push_sample delivers one, or until timeout
			std::unique_lock<std::mutex> lk(lock_);
			std::chrono::duration<double> sec(timeout);
			cv_.wait_for(lk, sec, [&]{ return this->buffer_.pop(result); });
		}
	}
	return result;
}

bool consumer_queue::empty() { return buffer_.empty(); }
