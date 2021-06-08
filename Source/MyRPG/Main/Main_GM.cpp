#include "Main_GM.h"

#include "../Unit/Player/Player_Base.h"
#include "Main_HUD.h"
#include "Main_PC.h"

AMain_GM::AMain_GM()
{
	DefaultPawnClass = APlayer_Base::StaticClass();
	PlayerControllerClass = AMain_PC::StaticClass();
	HUDClass = AMain_HUD::StaticClass();
}