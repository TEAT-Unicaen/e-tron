#pragma once 
#include <queue>
#include <bitset>

class KeyboardManager {
	friend class Window;// Window can access private members of KeyboardManager
public:
	class Event {
	public:
		enum class Type {
			Press,
			Release,
			Invalid
		};
	public:
		Event() noexcept;
		Event(Type type, unsigned char code) noexcept;
		bool isPress() const noexcept;
		bool isRelease() const noexcept;
		bool isValid() const noexcept;
		unsigned char getCode() const noexcept;
	private:
		Type type;
		unsigned char code;
	};

	KeyboardManager() = default;
	KeyboardManager(const KeyboardManager&) = delete;
	KeyboardManager& operator=(const KeyboardManager&) = delete;

	bool keyIsPressed(unsigned char keycode) const noexcept;
	Event readKey() noexcept;
	bool keyIsEmpty() const noexcept;
	void clearKey() noexcept;

	char readChar() noexcept;
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
	template <typename T> static void trimBuffer(std::queue<T>& buffer) noexcept;

	static constexpr unsigned int nKeys = 256u;
	static constexpr unsigned int bufferSize = 16u;
	bool autorepeatEnabled = false;
	std::bitset<nKeys> keyStates;
	std::queue<Event> keyBuffer;
};

