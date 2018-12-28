#include "Client.h"

Client * c;

int main(int argc, char* argv[]) {
	c = new Client();
	c->CreateSDLWindow();
	c->LoadAssets();
	bool exit = false;
	while (!exit) {
		long startTime = GetTime();
		exit = c->Update();
		c->Draw();
		long endTime = GetTime();
		long sleepTime = 20 - (endTime - startTime);
		SDL_Delay(sleepTime > 0 ? sleepTime : 0); //50fps
		long seconds = 1000 - sleepTime;
		float deltaTime = 1.0f - ((float)(seconds) / 1000);
		c->SetDeltaTime(deltaTime);
	}
	delete c;
	return 0;
}