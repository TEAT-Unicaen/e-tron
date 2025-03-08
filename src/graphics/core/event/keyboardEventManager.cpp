#include "KeyboardEventManager.h"

// KeyEvents
KeyboardEventManager::Event::Event(Type type, unsigned char code) noexcept
	: type(type), code(code) {}

bool KeyboardEventManager::Event::isPress() const noexcept {
	return type == Type::Press;
}

bool KeyboardEventManager::Event::isRelease() const noexcept {
	return type == Type::Release;
}

unsigned char KeyboardEventManager::Event::getCode() const noexcept {
	return code;
}

// KeyboardEventManager
bool KeyboardEventManager::keyIsPressed(unsigned char keycode) const noexcept {
	return this->keyStates[keycode];
}

std::optional<KeyboardEventManager::Event> KeyboardEventManager::readKey() noexcept {
	if (this->eventBuffer.empty())
		return std::nullopt;
	Event e = this->eventBuffer.front();
	this->eventBuffer.pop();
	return e;
}

bool KeyboardEventManager::keyIsEmpty() const noexcept {
	return this->eventBuffer.empty();
}

void KeyboardEventManager::clearKey() noexcept {
	this->eventBuffer = std::queue<Event>();
}

std::optional<char> KeyboardEventManager::readChar() noexcept {
	if (this->charBuffer.empty())
		return {};
	unsigned char charCode = this->charBuffer.front();
	this->charBuffer.pop();
	return charCode;
}

bool KeyboardEventManager::charIsEmpty() const noexcept {
	return this->charBuffer.empty();
}

void KeyboardEventManager::clearChar() noexcept {
	this->charBuffer = std::queue<char>();
}

void KeyboardEventManager::clearAll() noexcept {
	this->clearKey();
	this->clearChar();
}

void KeyboardEventManager::enableAutorepeat() noexcept {
	this->autorepeatEnabled = true;
}

void KeyboardEventManager::disableAutorepeat() noexcept {
	this->autorepeatEnabled = false;
}

bool KeyboardEventManager::autorepeatIsEnabled() const noexcept {
	return this->autorepeatEnabled;
}

void KeyboardEventManager::onKeyPressed(unsigned char keycode) noexcept {
	this->keyStates[keycode] = true;
	this->eventBuffer.push(Event(Event::Type::Press, keycode));
	trimBuffer(this->eventBuffer);
}

void KeyboardEventManager::onKeyReleased(unsigned char keycode) noexcept {
	this->keyStates[keycode] = false;
	this->eventBuffer.push(Event(Event::Type::Release, keycode));
	trimBuffer(this->eventBuffer);
}

void KeyboardEventManager::onChar(char character) noexcept {
	this->charBuffer.push(character);
	trimBuffer(this->charBuffer);
}

void KeyboardEventManager::clearState() noexcept {
	this->keyStates.reset();
}