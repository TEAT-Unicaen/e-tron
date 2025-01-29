#pragma once

class IUpdatable {
	public: 
		virtual ~IUpdatable() = default;
		virtual void update() = 0;
};