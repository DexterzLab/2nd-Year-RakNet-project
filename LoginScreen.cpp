#include "LoginScreen.h"
#include "Client.h"

extern Client * c;

void LoginScreen::KeyDown(int keyId)
{
	if (usernameText.size() < 22) {
		if (keyId >= 'a' && keyId <= 'z') {
			char key = keyId;
			usernameText += key;
		}
		if (keyId == ' ') {
			usernameText += ' ';
		}
	}
}

bool LoginScreen::Update()
{
	loginButtonHover = PointInBox(c->getMouseX(), c->getMouseY(), 329, 250, c->SpriteWidth(1), c->SpriteHeight(1));
	//if login button pressed
	if (c->getMousePressed() && loginButtonHover) {
		RakNet::RakString serverIp = SERVER_ADDRESS;
		c->getServerAddress().FromString(serverIp.C_String());
		RakNet::ConnectionAttemptResult result = c->getPeerInterface()->Connect(serverIp.C_String(), SERVER_PORT, 0, 0);
		loginMessage = "connecting to server...";
		std::cout << result << std::endl;
		if (result == RakNet::ConnectionAttemptResult::CONNECTION_ATTEMPT_STARTED) {
			//successful login attempt
		}
		else {
			switch (result) {
			case RakNet::ConnectionAttemptResult::CANNOT_RESOLVE_DOMAIN_NAME:
				loginMessage = "Cannot resolve server address.";
				break;
			case RakNet::ConnectionAttemptResult::SECURITY_INITIALIZATION_FAILED:
				loginMessage = "Security initialisation failed.";
				break;
			case RakNet::ConnectionAttemptResult::INVALID_PARAMETER:
				loginMessage = "RakNet has failed to start up.";
				break;
			}
		}
	}
		

	return false;
}

void LoginScreen::Draw()
{
	c->DrawSprite(0, 292, 100);//title
	c->DrawString(0, loginMessage, 342, 182); //log in message
	c->DrawSprite(3, 285, 200);//username
	c->DrawString(1, usernameText, 300, 210);
	c->DrawSprite(loginButtonHover ? 2 : 1, 329, 250);//Login button
	c->DrawString(2, "Play", 385, 260);
}
