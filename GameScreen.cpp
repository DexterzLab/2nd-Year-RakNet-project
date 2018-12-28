#include "GameScreen.h"
#include <sstream>

extern Client * c;

GameScreen::GameScreen()
{
	cameraPosition.x = 0;
	cameraPosition.y = 0;
}

GameScreen::~GameScreen()
{
	for (auto &p : players) {
		SAFERELEASE(p);
	}
}

void GameScreen::KeyDown(int keyId)
{
}

bool GameScreen::Update()
{
	//send a server an update of the players input every 200ms
	if (GetTime() - lastHeadUpdate > 200) {
		if (mainPlayer != nullptr) {
			c->getOutStream().SendPlayerUpdate(mainPlayer->headAngle, c->getMouseDown());
		}
	}

	if (mainPlayer != nullptr) {
		int deltaX = 400 - c->getMouseX();
		int deltaY = 240 - (480 - c->getMouseY());
		float angle = (atan2(deltaX, deltaY) * 180.0f) / 3.14159;
		angle += 180.0f;

		float diff = (angle - 180.0f) - mainPlayer->headAngle;

		while (diff < 0.0f) {
			diff += 360.0f;
		}

		if (diff > 182.0f) {
			mainPlayer->headAngle += 180.0f * c->GetDeltaTime();
		}
		else if (diff < 178.0f) {
			mainPlayer->headAngle -= 180.0f * c->GetDeltaTime();
		}

		
	}

	for (auto&p : players) {
		p->Update();
	}
	//since the player doesn't actually move, the camera position is updated.
	if (mainPlayer != nullptr) {
		cameraPosition.x = mainPlayer->position.x - 377;
		cameraPosition.y = mainPlayer->position.y - 217;
	}

	return false;

}

void GameScreen::Draw()
{
	std::stringstream ss;
	ss << "Frame Delta Time: ";
	ss << c->GetDeltaTime();
	//draw game background
	c->DrawSprite(7, 0 - cameraPosition.x, 0 - cameraPosition.y);

	//draw delta time
	c->DrawString(0, ss.str(), 10, 10);

	//draw player
	//c->DrawSprite(4, 377, 217);
	//c->DrawRotatedSprite(4, 377, 217, mainPlayer->headAngle, mainPlayer->headRadius*2, mainPlayer->headRadius*2);
	for (auto & p : players) {
		p->Draw();
	}

	//Leaderboard code
	/*std::stringstream string_players;

	for (auto &p : players) {
		string_players << "" << p->name;

	}

	c->DrawString(0, string_players.str(), 30, 30);
	*/

	for (int i = 0; i < players.size(); i++)
	{
		std::stringstream snake_length;

		snake_length << players[i]->orbs;
		snake_length << " - ";
		snake_length << players[i]->name;

		c->DrawString(0, snake_length.str(), 700, 10 + (15 * i)); // Every I (player), move down.

	}


}

void GameScreen::AddPlayer(bool mainPlayer, unsigned long uuid, std::string name, double x, double y, std::vector<Vector2<double>> bodyPositions)
{
	for (auto &p : players) {
		if (p->uuid == uuid) {
			return;
		}
	}
	Player * p = new Player(uuid, name, x, y);
	p->bodyPositions = bodyPositions;
	players.push_back(p);
	if (mainPlayer) {
		this->mainPlayer = p;
	}
}

Player * GameScreen::getPlayer(unsigned long uuid)
{
	for (auto & p : players) {
		if (p->uuid == uuid) {
			return p;
		}
	}
	return nullptr;
}
