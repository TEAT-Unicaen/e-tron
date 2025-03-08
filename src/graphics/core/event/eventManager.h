#pragma once

#include "../../utils/setUpWindows.h"

#include <queue>
#include <bitset>
#include <optional>

class EventManager {
public:
	EventManager() = default;
	EventManager(const EventManager&) = delete;
	EventManager& operator=(const EventManager&) = delete;
	virtual ~EventManager() = default;

protected:
	template <typename T>
	void trimBuffer(std::queue<T>& buffer) noexcept {
		while (buffer.size() > EventManager::bufferSize) {
			buffer.pop();
		}
	}

	static constexpr unsigned int bufferSize = 16u;
};