#include "mouseEventManager.h"

// MouseEvents
MouseEventManager::Event::Event(MouseEventManager::Event::Type type, MouseEventManager::Button button, int x, int y) noexcept
	: type(type), buttonPressed(button), coords({ x, y }) {}

bool MouseEventManager::Event::isPress() const noexcept {
	return this->type == Type::Press;
}

bool MouseEventManager::Event::isRelease() const noexcept {
	return this->type == Type::Release;
}

bool MouseEventManager::Event::isWheelUp() const noexcept {
	return this->type == Type::WheelUp;
}

bool MouseEventManager::Event::isWheelDown() const noexcept {
	return this->type == Type::WheelDown;
}

bool MouseEventManager::Event::isMove() const noexcept {
	return this->type == Type::Move;
}

MouseEventManager::Event::Type MouseEventManager::Event::getType() const noexcept {
	return this->type;
}

MouseEventManager::Button MouseEventManager::Event::getButton() const noexcept {
		return this->buttonPressed;
}

MouseEventManager::GraphicCoords MouseEventManager::Event::getCoords() const noexcept {
		return this->coords;
}

// MouseEventManager
bool MouseEventManager::buttonIsPressed(MouseEventManager::Button button) const noexcept {
	return this->buttonStates[static_cast<int>(button)];
}

bool MouseEventManager::isInWindow() const noexcept {
	return this->inWindow;
}


std::optional<MouseEventManager::Event> MouseEventManager::read() noexcept {
	if (this->eventBuffer.empty())
		return std::nullopt;
	Event e = this->eventBuffer.front();
	this->eventBuffer.pop();
	return e;
}

bool MouseEventManager::isEmpty() const noexcept {
	return this->eventBuffer.empty();
}

void MouseEventManager::clearButton() noexcept {
	this->eventBuffer = std::queue<Event>();
}

void MouseEventManager::onButtonPressed(MouseEventManager::Button button, int x, int y) noexcept {
	this->buttonStates[static_cast<int>(button)] = true;
	this->eventBuffer.push(MouseEventManager::Event(MouseEventManager::Event::Type::Press, button, x, y));
	trimBuffer(this->eventBuffer);
}

void MouseEventManager::onButtonReleased(MouseEventManager::Button button, int x, int y) noexcept {
	this->buttonStates[static_cast<int>(button)] = false;
	this->eventBuffer.push(Event(Event::Type::Release, button, x, y));
	trimBuffer(this->eventBuffer);
}

void MouseEventManager::onWheelUp(int x, int y) noexcept {
	this->eventBuffer.push(MouseEventManager::Event(MouseEventManager::Event::Type::WheelUp, MouseEventManager::Button::None, x, y));
	trimBuffer(this->eventBuffer);
}

void MouseEventManager::onWheelDown(int x, int y) noexcept {
	this->eventBuffer.push(MouseEventManager::Event(MouseEventManager::Event::Type::WheelDown, MouseEventManager::Button::None, x, y));
	trimBuffer(this->eventBuffer);
}

void MouseEventManager::onMouseMove(int x, int y) noexcept {
	this->eventBuffer.push(MouseEventManager::Event(MouseEventManager::Event::Type::Move, MouseEventManager::Button::None, x, y));
	trimBuffer(this->eventBuffer);
}

void MouseEventManager::onMouseEnter(int x, int y) noexcept {
	this->inWindow = true;
	this->eventBuffer.push(MouseEventManager::Event(MouseEventManager::Event::Type::Enter, MouseEventManager::Button::None, x, y));
	trimBuffer(this->eventBuffer);
}

void MouseEventManager::onMouseLeave(int x, int y) noexcept {
	this->inWindow = false;
	this->eventBuffer.push(MouseEventManager::Event(MouseEventManager::Event::Type::Leave, MouseEventManager::Button::None, x, y));
	trimBuffer(this->eventBuffer);
}

void MouseEventManager::onWheelDelta(int x, int y, int delta) noexcept {
	this->wheelDelat += delta;
	// generate events for every 120 delta
	while (this->wheelDelat >= WHEEL_DELTA) {
		this->onWheelUp(x, y);
		this->wheelDelat -= WHEEL_DELTA;
	}
	while (this->wheelDelat <= -WHEEL_DELTA) {
		this->onWheelDown(x, y);
		this->wheelDelat += WHEEL_DELTA;
	}
}
