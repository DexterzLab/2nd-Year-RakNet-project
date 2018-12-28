#pragma once
#include "MathUtil.h"
#include "Server.h"

#pragma comment(lib, "ws2_32.lib")

Server * s;



#define SERVER_TICK_TIME 200

int main(void) {
	s = new Server();
	s->Start();

	while (true) {
		long startTime = GetTime();
		s->Process();
		long endTime = GetTime();
		Sleep(SERVER_TICK_TIME - (endTime - startTime));
	}

	delete s;
}