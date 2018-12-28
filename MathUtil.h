#pragma once
#include <cmath>
#include <ctime>

//Release a pointer from memory safely
#define SAFERELEASE(x) { if (x) { delete x; x = NULL;} }

//! A template struct which can construct a Vector2 with any data type
template <typename T>
struct Vector2 {
	T x;
	T y;
	Vector2(T x = 0, T y = 0) :x(x), y(y) {}

	Vector2 operator+(Vector2 v2) {
		return Vector2(x + v2.x, y + v2.y);
	}
};

//! A struct which holds a position and radius to represent a circle
struct Circle {
	Vector2<int> position;
	int radius;
	//! detects if a collision between two circles has occured
	bool CollisionWithCircle(Circle& c) const {
		int diffX = c.position.x > position.x ? c.position.x - position.x : position.x - c.position.x;
		int diffY = c.position.y > position.y ? c.position.y - position.y : position.y - c.position.y;
		int vectorLength = sqrt(diffX * diffX + diffY * diffY);
		return vectorLength < (radius + c.radius);
	}
};

//! check if a point is inside a box
inline bool PointInBox(int px, int py, int boxX, int boxY, int boxW, int boxH) {
	if (px > boxX && px < boxX + boxW) {
		if (py > boxY && py < boxY + boxH) {
			return true;
		}
	}
	return false;
}

//! get the clock time
inline long GetTime() {
	return clock();
}

//! convert degrees to radians
inline float DegToRad(float deg) {
	return deg * 3.14159 / 180.0f;
}

//! creates a random number of 0-range (exclusive)
inline int RandomNumber(int range) {
	return rand() % range;
}

