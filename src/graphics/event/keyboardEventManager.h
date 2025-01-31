#pragma once 
#include <queue>
#include <bitset>
#include <optional>

#include "eventManager.h"

class KeyboardEventManager : EventManager {
	friend class Window;// Window can access private members of KeyboardEventManager
public:
	class Event {
	public:
		enum class Type {
			Press,
			Release,
		};
	public:
		Event(Type type, unsigned char code) noexcept;
		bool isPress() const noexcept;
		bool isRelease() const noexcept;
		unsigned char getCode() const noexcept;
	private:
		Type type;
		unsigned char code;
	};

	KeyboardEventManager() = default;
	KeyboardEventManager(const KeyboardEventManager&) = delete;
	KeyboardEventManager& operator=(const KeyboardEventManager&) = delete;

	bool keyIsPressed(unsigned char keycode) const noexcept;
	std::optional<KeyboardEventManager::Event> readKey() noexcept;
	bool keyIsEmpty() const noexcept;
	void clearKey() noexcept;

	std::optional<char> readChar() noexcept;
	bool charIsEmpty() const noexcept;
	void clearChar() noexcept;

	void clearAll() noexcept;

	void enableAutorepeat() noexcept;
	void disableAutorepeat() noexcept;
	bool autorepeatIsEnabled() const noexcept;

private:
	void onKeyPressed(unsigned char keycode) noexcept;
	void onKeyReleased(unsigned char keycode) noexcept;
	void onChar(char character) noexcept;
	void clearState() noexcept;

	static constexpr unsigned int nKeys = 256u;
	bool autorepeatEnabled = false;
	std::bitset<nKeys> keyStates;
	std::queue<Event> eventBuffer;
	std::queue<char> charBuffer;
};

