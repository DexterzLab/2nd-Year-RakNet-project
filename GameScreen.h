#pragma once
#include <vector>
#include "Client.h"
#include "MathUtil.h"
#include "Player.h"

//The gamescreen class represents all of the game data. The functionality of this class is called from the Client.
class GameScreen {
	friend class InStream;
	friend class OutStream;
	friend class Player;
public:
	//default
	GameScreen();
	//deconstructor
	virtual ~GameScreen();
	//!Detect if a key has been pressed
	void KeyDown(int keyId);
	//!Updates the game screen
	bool Update();
	//!Draws the game screen
	void Draw();

	//!Adds a player to the game screen. This should be called when the server sends a message to add a player
	/**
	* \param mainPlayer - set to true to add the main player
	* \param uuid - a unique number to identify the player
	* \param name - the name of the player
	* \param x - the starting X position of the player
	* \param y - the starting Y position of the player
	* \param bodyPositions - a vector of co-ordinates for the snakes body positions
	*/
	void AddPlayer(bool mainPlayer, unsigned long uuid, std::string name, double x, double y, std::vector<Vector2<double>> bodyPositions);

	//!Returns the instace of a player by the id
	/**
	* \ param uuid - the id of the player to obtain a pointer to
	*/
	Player * getPlayer(unsigned long uuid);
private:
	//all of the players in the game
	std::vector<Player*> players;
	//pointer to main player, this player is also in the players vector
	Player * mainPlayer;

	//camera co-ordinates.
	Vector2<int> cameraPosition;

	//timer for sending updates. This is done every 200ms.
	long lastHeadUpdate;
};