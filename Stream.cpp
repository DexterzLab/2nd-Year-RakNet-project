#include "Stream.h"
#include "Server.h"
#include <BitStream.h>
#include <string>

extern Server * s;

void InStream::ReceiveLoginRequest(unsigned char * data, int size)
{
	RakNet::BitStream bitStream(data, size, false);
	RakNet::RakString name;
	bitStream.IgnoreBytes(sizeof(RakNet::MessageID));
	bitStream.Read(name);
	p->username = name;
	int response = 0; //accept login reuqest
	//send response
	p->getOutStream()->SendLoginResponse(response, RakNet::RakNetGUID::ToUint32(p->uuid), name.C_String());
	//Hint: Send an update to all players in the game to tell them about this new client
	
	
	//for (int i = 0; i < s->room->players.size(); i++) {
		//s->room->players[i]->getOutStream()->SendAddPlayer(RakNet::RakNetGUID::ToUint32(p->getUUID()), p->getUsername(), p->position, p->bodyPositions);
		//p->getOutStream()->SendAddPlayer(RakNet::RakNetGUID::ToUint32(s->room->players[i]->getUUID()), s->room->players[i]->getUsername(), s->room->players[i]->position, s->room->players[i]->bodyPositions);
	//}

	for (auto &players : s->room->players)
	{
		players->getOutStream()->SendAddPlayer(RakNet::RakNetGUID::ToUint32(players->getUUID()), players->getUsername(), players->position, players->bodyPositions);
	}



}

void InStream::ReceivePlayerUpdate(unsigned char * data, int size)
{
	float angle;
	int mouseDown;
	RakNet::BitStream bitStream(data, size, false);
	bitStream.IgnoreBytes(sizeof(RakNet::MessageID));
	bitStream.Read(angle);
	bitStream.Read(mouseDown);
	p->SetHeadAngle(angle);

	p->timer = 0.0f;
}

void OutStream::SendLoginResponse(int result, unsigned long playerId, std::string name)
{
	//initial player settings
	float angle = 0;
	int length = 8;
	double positionX = 128;
	double positionY = 128;
	RakNet::RakString RSname = name.c_str();
	RakNet::BitStream bitStream;
	bitStream.Write((RakNet::MessageID) ID_LOGIN_RESPONSE);
	bitStream.Write(result);
	bitStream.Write(playerId);
	bitStream.Write(RSname);
	bitStream.Write(angle);
	bitStream.Write(length);
	bitStream.Write(positionX);
	bitStream.Write(positionY);
	
#if _DEBUG
	printf("Player %s - Login response: result. \n", name, result);
#endif
	s->getPeerInterface()->Send(&bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, p->getUUID(), false);
}

void OutStream::SendPlayerUpdate(unsigned long uuid, double x, double y, float headAngle)
{
	//Hint: Send a packet to the client here
	RakNet::BitStream bsOut;

	bsOut.Write((RakNet::MessageID) ID_SERVER_SEND_PLAYER_UPDATE);
	bsOut.Write(uuid);
	bsOut.Write(x);
	bsOut.Write(y);
	bsOut.Write(headAngle);

	for (auto &players : s->room->players) {

		s->getPeerInterface()->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, players->getUUID(), false);

	}
}

void OutStream::SendAddPlayer(unsigned long uuid, std::string name, Vector2<double> position, std::vector<Vector2<double>> bodyPositions)
{
	//Hint: Send a message to tell the client to add a player
	int Lobby;
	RakNet::BitStream bsOut;
	RakNet::RakString RSname = name.c_str();


	bsOut.Write((RakNet::MessageID) ID_PLAYER_ADD);
	bsOut.Write(uuid);
	bsOut.Write(RSname);
	bsOut.Write(position.x);
	bsOut.Write(position.y);
	bsOut.Write(bodyPositions.size());
	for (int i = 0; i < bodyPositions.size(); i++) {

		bsOut.Write(bodyPositions[i].x);
		bsOut.Write(bodyPositions[i].y);


	}

	for (auto &players : s->room->players) {

		s->getPeerInterface()->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, players->getUUID(), false);

	}
}

//Receive information that a player has left
void InStream::ReceivePlayerQuit(unsigned char * data, int size)
{

	RakNet::BitStream bsIn(data, size, false);
	unsigned long uuid;

	bsIn.Read(uuid);
	p->getOutStream()->SendPlayerQuit(uuid);

}

//Tell the other players that a player has left
void OutStream::SendPlayerQuit(unsigned long uuid)
{

	RakNet::BitStream bsOut;
	bsOut.Write((RakNet::MessageID) ID_PLAYER_QUIT);
	bsOut.Write(uuid);

	for (auto &p : s->room->players) {

		s->getPeerInterface()->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, p->getUUID(), false);

	}
}




