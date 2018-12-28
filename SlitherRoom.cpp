#include "SlitherRoom.h"
#include "Server.h"
#include <iostream>


using namespace std;
extern  Server * s;

void SlitherRoom::AddPlayer(RakNet::RakNetGUID uuid, RakNet::SystemAddress address)
{
	Client * p = new Client(128, 128, uuid, address);
	players.push_back(p);
}

Client * SlitherRoom::GetPlayer(RakNet::RakNetGUID uuid)
{
	for (auto &p : players) {
		if (p->getUUID() == uuid) {
			return p;
		}
	}
	return nullptr;
}

void SlitherRoom::process()
{
	for (auto& p : players) {
		p->process();
	}


	for (auto& p : players) {


		for (int i = players.size() - 1; i >= 0; i--) {
			cout << players[i]->timer << endl;
			if (players[i]->timer >= 1.0f) {

				unsigned long uuid = RakNet::RakNetGUID::ToUint32(players[i]->getUUID());
				players.erase(players.begin() + i);
				//
				RakNet::BitStream bitStream;
				bitStream.Write((RakNet::MessageID) ID_PLAYER_QUIT);
				bitStream.Write(uuid);
				for (auto &players : players) {

					s->getPeerInterface()->Send(&bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, players->getUUID(), false);

				}


			}

		}
	}
}
