#pragma once
#include "MathUtil.h"
#include <string>
#include <vector>

//! Player class represents one player in the game
class Player {
	friend class InStream;
	friend class OutStream;
public:
	//! Default constructor
	/**
	* \param x - the X position the start the player at
	* \param y - the Y position the start the player at
	*/
	Player(int x, int y);
	//deconstructor
	virtual ~Player();
	//! Returns the players name
	std::string getUsername() const { return username; }
	//! Returns the players head angle
	void SetHeadAngle(float angle) { this->headAngle = angle; }
	//! Returns the movement speed
	inline float GetMoveSpeed() const { return 80.0f; }
protected: 
	float headAngle;
	Vector2<double> position;
	std::vector<Vector2<double>> bodyPositions;
	std::string username;
};