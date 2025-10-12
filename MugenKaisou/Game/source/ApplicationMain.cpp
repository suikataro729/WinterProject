
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeGame.h"
#include "ModeTitle.h"
#include "ModeFade.h"

// ����
ApplicationMain				g_oApplicationMain;

bool ApplicationMain::Initialize(HINSTANCE hInstance) {
	if (!base::Initialize(hInstance)) { return false; }

	// ���[�h�̓o�^
	// ModeGame����̃��C���[�ɓo�^����
	ModeServer::GetInstance()->Add(new ModeFade("IN"), 998, "fade");
	ModeServer::GetInstance()->Add(new ModeTitle(), 997, "title");

	ModeServer::GetInstance()->Add(new ModeGame(), 1, "game");

	return true;
}

bool ApplicationMain::Terminate() {
	base::Terminate();
	return true;
}


bool ApplicationMain::Input() {
	base::Input();
	return true;
}

bool ApplicationMain::Process() {
	base::Process();
	return true;
}

bool ApplicationMain::Render() {
	base::Render();
	
	return true;
}

