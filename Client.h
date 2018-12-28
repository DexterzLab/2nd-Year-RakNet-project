#pragma once
#include <RakPeerInterface.h>
#include <MessageIdentifiers.h>
#include <BitStream.h>
#include <string>
#include "Stream.h"
#include "MathUtil.h"
#include "Stream.h"
#include "Player.h"

class InStream;
class OutStream;

//! Client class represents the network data going to and from one game client
class Client : public Player {
	friend class InStream;
	friend class OutStream;
public:
	//Constructor
	/**
	* \param x - the x position to start at
	* \param y - the y position to start at
	* \param uuid - Raknets unique identifier
	* \param address - the system address of the client
	*/
	Client(int x, int y, RakNet::RakNetGUID uuid, RakNet::SystemAddress address);
	//deconstructor
	virtual ~Client();
	//! Updates the players game and sends updates
	void process();
	//! Return the uuid of the player
	RakNet::RakNetGUID getUUID() const { return uuid; }
	//! Incoming network data
	InStream * getInStream() const;
	//! Outgoing network data
	OutStream * getOutStream() const;

	float timer = 0.0f;

private:
	RakNet::RakNetGUID uuid;
	RakNet::SystemAddress clientAddress;
	InStream * inStream;
	OutStream * outStream;


};