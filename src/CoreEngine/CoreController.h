#pragma once

// No MFC
#define WIN32_LEAN_AND_MEAN

// We need the Windows Header and the XInput Header
#include <windows.h>
#include <XInput.h>

#pragma comment(lib, "XInput.lib")

class CoreController
{
private:
	XINPUT_STATE _controllerState;
	int _controllerNum;
public:
	CoreController(int playerNumber);
	XINPUT_STATE GetState();
	bool IsConnected();
	void Vibrate(int leftVal = 0, int rightVal = 0);
};