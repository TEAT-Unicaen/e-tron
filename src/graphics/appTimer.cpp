#include "appTimer.h"

AppTimer::AppTimer() noexcept {
	last = std::chrono::steady_clock::now();
}

float AppTimer::mark() noexcept {
	const auto old = last;
	last = std::chrono::steady_clock::now();
	const std::chrono::duration<float> frameTime = last - old;
	return frameTime.count();
}

float AppTimer::peek() const noexcept {
	return std::chrono::duration<float>(std::chrono::steady_clock::now() - last).count();
}