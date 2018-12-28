#include "Client.h"
#include "Server.h"
#include <iostream>
extern Server * s;

Client::Client(int x, int y, RakNet::RakNetGUID uuid, RakNet::SystemAddress address) : Player(x, y)
{
	inStream = new InStream(this);
	outStream = new OutStream(this);
	this->uuid = uuid;
	this->clientAddress = address;
	std::vector<Vector2<double>> bodyPositions;
	for (int i = 0; i < 8; i++) {
		bodyPositions.push_back(Vector2<double>(x, y + (16 * i)));
	}
	this->bodyPositions = bodyPositions;
}

Client::~Client()
{
	SAFERELEASE(inStream);
	SAFERELEASE(outStream);
}

void Client::process()
{
	float oldHeadX = position.x;
	float oldHeadY = position.y;
	//calc movement
	float fX = sin(DegToRad(headAngle));
	float fY = cos(DegToRad(headAngle));
	position.x += (fX * GetMoveSpeed()) * 0.2f; //0.2f to account for 200ms tick time
	position.y -= (fY * GetMoveSpeed()) * 0.2f;

	timer += 0.04f;

	for (int i = bodyPositions.size() - 1; i >= 1; i--) {
		bodyPositions[i].x = bodyPositions[i - 1].x;
		bodyPositions[i].y = bodyPositions[i - 1].y;
	}

	bodyPositions[0].x = oldHeadX;
	bodyPositions[0].y = oldHeadY;

	//send update
	for (auto &p : s->room->players) {
		p->getOutStream()->SendPlayerUpdate(RakNet::RakNetGUID::ToUint32(uuid), position.x, position.y, headAngle);
	}


}

InStream * Client::getInStream() const
{
	return inStream;
}

OutStream * Client::getOutStream() const
{
	return outStream;
}
