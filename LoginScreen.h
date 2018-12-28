#pragma once
#include <string>

class LoginScreen {
	friend class Client;
public:
	void KeyDown(int keyId);
	bool Update();
	void Draw();
private:
	std::string loginMessage = "Enter a username to play!";
	std::string usernameText = "";
	std::string loginButtonText = "Play";
	bool loginButtonHover = false;
};