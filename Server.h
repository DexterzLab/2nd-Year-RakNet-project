#pragma once

#include <RakPeerInterface.h>
#include <MessageIdentifiers.h>
#include <BitStream.h>
#include <string>

#include "SlitherRoom.h"

#define SERVER_PORT 3194
#define MAXIMUM_PLAYERS 500

class SlitherRoom;

class Server {
	friend class Client;
	friend class InStream;
	friend class OutStream;
public:
	Server();
	virtual ~Server();

	void Start();
	void Process();

	RakNet::RakPeerInterface * getPeerInterface() { return peer; }
	
private:
	RakNet::RakPeerInterface * peer = NULL;
	bool running = true;
	//instance of room that the player is in
	SlitherRoom * room = NULL;
};