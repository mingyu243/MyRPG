#include "Title_GM.h"

#include "Title_PC.h"

ATitle_GM::ATitle_GM()
{
	PlayerControllerClass = ATitle_PC::StaticClass();
}