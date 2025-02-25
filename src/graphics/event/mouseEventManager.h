#pragma once

#include <queue>
#include <bitset>
#include <optional>

#include "eventManager.h"

class MouseEventManager : EventManager {
	friend class Window;// Window can access private members of KeyboardEventManager
public:
	enum class Button { // Use for index of bitset
		None,
		Left,
		Right,
		Middle,
		Button4,
		Button5
	};

	typedef struct GCoords {
		int x;
		int y;
	} GraphicCoords;

	class Event {
	public:
		enum class Type {
			Press,
			Release,
			WheelUp,
			WheelDown,
			Move,
			Enter,
			Leave
		};


		Event(MouseEventManager::Event::Type type, MouseEventManager::Button button, int x, int y) noexcept;
		bool isPress() const noexcept;
		bool isRelease() const noexcept;
		bool isWheelUp() const noexcept;
		bool isWheelDown() const noexcept;
		bool isMove() const noexcept;
		MouseEventManager::Event::Type getType() const noexcept;
		MouseEventManager::Button getButton() const noexcept;
		GraphicCoords getCoords() const noexcept;
	private:
		MouseEventManager::Event::Type type;
		MouseEventManager::Button buttonPressed;
		MouseEventManager::Event::GraphicCoords coords;
	};

	MouseEventManager() = default;
	MouseEventManager(const MouseEventManager&) = delete;
	MouseEventManager& operator=(const MouseEventManager&) = delete;

	bool buttonIsPressed(MouseEventManager::Button button) const noexcept;
	bool isInWindow() const noexcept;

	std::optional<MouseEventManager::Event> read() noexcept;
	bool isEmpty() const noexcept;
	void clearButton() noexcept;

private:
	void onButtonPressed(MouseEventManager::Button button, int x, int y) noexcept;
	void onButtonReleased(MouseEventManager::Button button, int x, int y) noexcept;
	void onWheelUp(int x, int y) noexcept;
	void onWheelDown(int x, int y) noexcept;
	void onMouseMove(int x, int y) noexcept;
	void onMouseEnter(int x, int y) noexcept;
	void onMouseLeave(int x, int y) noexcept;
	void onWheelDelta(int x, int y, int delta) noexcept;

	std::bitset<6> buttonStates;
	std::queue<MouseEventManager::Event> eventBuffer;
	int wheelDelat = 0;
	bool inWindow = false;
};

