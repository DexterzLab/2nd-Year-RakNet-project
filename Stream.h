#pragma once
#include <list>
#include "Client.h"
#include "MathUtil.h"
#include <vector>

class Client;

//! All Game Message IDs
//! This should be the same in server & client
enum GAME_MESSAGES {
	ID_LOGIN_REQUEST = ID_USER_PACKET_ENUM + 1,
	ID_LOGIN_RESPONSE,
	ID_ORB_POSITIONS_ADD,
	ID_ORB_POSITIONS_REMOVE,
	ID_PLAYER_ADD,
	ID_CLIENT_SEND_PLAYER_UPDATE,
	ID_SERVER_SEND_PLAYER_UPDATE,
	ID_PLAYER_CHAT,
	ID_PLAYER_QUIT
	
};

class InStream {
public:
	//! Creates an instance of this class with a reference to the player
	InStream(Client * p) : p(p) {}
	//! Receive a login request from the client
	/**
	* \param data - the payload of the packet
	* \param size - the size in bytes of the packet
	*/
	void ReceiveLoginRequest(unsigned char * data, int size);
	//! Receive a player update from the client
	/**
	* \param data - the payload of the packet
	* \param size - the size in bytes of the packet
	*/
	void ReceivePlayerUpdate(unsigned char * data, int size);

	//Receive the message the client has sent
	//void ReceivePlayerText(unsigned char * data, int size);

	//Remove the player from the game
	void ReceivePlayerQuit(unsigned char * data, int size);

private:
	Client * p;
};

class OutStream {
public:
	//! Creates an instance of this class with a reference to the player
	OutStream(Client * p) : p(p) {}
	//! Send a login response
	/**
	* \param result - the result of the login i.e 0 = login accepted
	* \param playerId - the id of the player created for this client
	* \param name - the name of the player
	*/
	void SendLoginResponse(int result, unsigned long playerId, std::string name);
	//! Send an update to a game client to update any player
	/**
	* \param uuid - the id of the player to update
	* \param x - the x position to set the player to
	* \param y - the y position to set the player to
	* \param headAngle - the direction in degrees that the players head is facing
	*/
	void SendPlayerUpdate(unsigned long uuid, double x, double y, float headAngle);
	//! Tell a game client to add a player
	/**
	* \param uuid - the uuid of the new player
	* \param flags - A bitmask of data for the players looks (not supported)
	* \param name - the name of the player
	* \param position - the x and y of the head
	* \param bodyPositions - a vector of positions for all of the players body
	*/
	void SendAddPlayer(unsigned long uuid, std::string name, Vector2<double> position, std::vector<Vector2<double>> bodyPositions);

	//Send information to the other players about the disconnection
	void SendPlayerQuit(unsigned long uuid);



private:
	Client * p;
};