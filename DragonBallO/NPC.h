#pragma once

#include "Sprite.h"

class NPC : public Sprite {
public:
	//Base class destructor is ALWAYS implicitly called...
	NPC() { mCanBePushedBack = false; }
	virtual ~NPC() override {}

	void Update() override;

private:
	void Move();
	void Brain();
	int HorizDirection;
	int VertDirection;
};