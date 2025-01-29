#include "keyboardManager.h"

// KeyEvents
KeyboardManager::Event::Event() noexcept
	: type(Type::Invalid), code(0u) {}

KeyboardManager::Event::Event(Type type, unsigned char code) noexcept
	: type(type), code(code) {}

bool KeyboardManager::Event::isPress() const noexcept {
	return type == Type::Press;
}

bool KeyboardManager::Event::isRelease() const noexcept {
	return type == Type::Release;
}

bool KeyboardManager::Event::isValid() const noexcept {
	return type != Type::Invalid;
}

unsigned char KeyboardManager::Event::getCode() const noexcept {
	return code;
}


// KeyboardManager
KeyboardManager::keyIsPressed(unsigned char keycode) const noexcept {
	return this->keyStates[keycode];
}

KeyboardManager::Event KeyboardManager::readKey() noexcept {
	if (this->keyBuffer.empty())
		return Event();// Invalid Event
	Event e = this->keyBuffer.front();
	this->keyBuffer.pop();
	return e;
}

bool KeyboardManager::keyIsEmpty() const noexcept {
	return this->keyBuffer.empty();
}

void KeyboardManager::clearKey() noexcept {
	this->keyBuffer = std::queue<Event>();
}

char KeyboardManager::readChar() noexcept {
	if (this->charBuffer.empty())
		return 0;// /0
	unsigned char charCode = this->charBuffer.front();
	this->charBuffer.pop();
	return charCode;
}

bool KeyboardManager::charIsEmpty() const noexcept {
	return this->charBuffer.empty();
}

void KeyboardManager::clearChar() noexcept {
	this->charBuffer = std::queue<char>();
}

void KeyboardManager::clearAll() noexcept {
	this->clearKey();
	this->clearChar();
}

void KeyboardManager::enableAutorepeat() noexcept {
	this->autorepeatEnabled = true;
}

void KeyboardManager::disableAutorepeat() noexcept {
	this->autorepeatEnabled = false;
}

bool KeyboardManager::autorepeatIsEnabled() const noexcept {
	return this->autorepeatEnabled;
}

void KeyboardManager::onKeyPressed(unsigned char keycode) noexcept {
	this->keyStates[keycode] = true;
	this->keyBuffer.push(Event(Event::Type::Press, keycode));
	trimBuffer(this->keyBuffer);
}

void KeyboardManager::onKeyReleased(unsigned char keycode) noexcept {
	this->keyStates[keycode] = false;
	this->keyBuffer.push(Event(Event::Type::Release, keycode));
	trimBuffer(this->keyBuffer);
}

void KeyboardManager::onChar(char character) noexcept {
	this->charBuffer.push(character);
	trimBuffer(this->charBuffer);
}

void KeyboardManager::clearState() noexcept {
	this->keyStates.reset();
}

template <typename T> void KeyboardManager::trimBuffer(std::queue<T>& buffer) noexcept {
	while (buffer.size() > bufferSize)
		buffer.pop();
}