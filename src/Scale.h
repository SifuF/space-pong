#ifndef SCALE_H
#define SCALE_H

struct Scale {
	const int screenWidth = 1500;
	const int screenHeight = 844;

	const float radius = screenHeight / 50.0f;
	const float speed = screenWidth / 1000.0f;
	const float offScreen = screenWidth / 20.0f;

	const float width = screenWidth / 80.f;
	const float height = screenHeight / 5.0f;
	const float fromWall = screenWidth / 25.f;
	const float moveIncrement = screenHeight / 1000.0f;
	const float rebound = screenHeight/50.0f;

	const float PI = 3.14159;

	float textSize = screenHeight / 80.0f;

	bool AI_left = false;
	bool AI_right = false;
	int varyUnit = 150;
	double delay = 0.0;
	double delayIncrement = 0.000001;
	bool debug = false;
};

#endif