#define __MT_COMMAND_CPP__

#include "common.h"

#include "Command.h"
#include "graphic/Graphic.h"

using namespace std;
using namespace mt::graphic;
using namespace mt::game;


void Command::setFuncMap(std::map<std::string, function>* map)
{
	map->insert({"+showscores", &Command::cmd_void});
	map->insert({"+attack", &Command::cmd_void});
	map->insert({"exit", &Command::cmd_void});
	map->insert({"jump", &Command::cmd_void});
	map->insert({"+moveup", &Command::cmd_void});
	map->insert({"buyammo1", &Command::cmd_void});
	map->insert({"buyammo2", &Command::cmd_void});
	map->insert({"+movedown", &Command::cmd_void});
	map->insert({"slot10", &Command::cmd_void});
	map->insert({"slot1", &Command::cmd_void});
	map->insert({"slot2", &Command::cmd_void});
	map->insert({"slot3", &Command::cmd_void});
	map->insert({"slot4", &Command::cmd_void});
	map->insert({"slot5", &Command::cmd_void});
	map->insert({"slot6", &Command::cmd_void});
	map->insert({"slot7", &Command::cmd_void});
	map->insert({"slot8", &Command::cmd_void});
	map->insert({"slot9", &Command::cmd_void});
	map->insert({"+mlook", &Command::cmd_void});
	map->insert({"invprev", &Command::cmd_void});
	map->insert({"invnext", &Command::cmd_void});
	map->insert({"toggleconsole", &Command::cmd_void});
	map->insert({"+moveleft", &Command::cmd_void});
	map->insert({"buy", &Command::cmd_void});
	map->insert({"radio3", &Command::cmd_void});
	map->insert({"+moveright", &Command::cmd_void});
	map->insert({"+use", &Command::cmd_void});
	map->insert({"drop", &Command::cmd_void});
	map->insert({"+commandmenu", &Command::cmd_void});
	map->insert({"cheer", &Command::cmd_void});
	map->insert({"+voicerecord", &Command::cmd_void});
	map->insert({"showbriefing", &Command::cmd_void});
	map->insert({"chooseteam", &Command::cmd_void});
	map->insert({"nightvision", &Command::cmd_void});
	map->insert({"buyequip", &Command::cmd_void});
	map->insert({"lastinv", &Command::cmd_void});
	map->insert({"+reload", &Command::cmd_void});
	map->insert({"+back", &Command::cmd_void});
	map->insert({"messagemode2", &Command::cmd_void});
	map->insert({"+forward", &Command::cmd_void});
	map->insert({"radio2", &Command::cmd_void});
	map->insert({"messagemode", &Command::cmd_void});
	map->insert({"radio1", &Command::cmd_void});
	map->insert({"+forward", &Command::cmd_void});
	map->insert({"+back", &Command::cmd_void});
	map->insert({"+left", &Command::cmd_void});
	map->insert({"+right", &Command::cmd_void});
	map->insert({"+strafe", &Command::cmd_void});
	map->insert({"+duck", &Command::cmd_void});
	map->insert({"+sprint", &Command::cmd_void});
	map->insert({"debug_origin", &Command::cmd_void});
	map->insert({"debug_noclip", &Command::cmd_void});
	map->insert({"debug_frustumcull", &Command::cmd_debug_frustumcull});
	map->insert({"debug_movezone", &Command::cmd_void});
	map->insert({"+klook", &Command::cmd_void});
	map->insert({"+lookdown", &Command::cmd_void});
	map->insert({"+lookup", &Command::cmd_void});
	map->insert({"centerview", &Command::cmd_void});
	map->insert({"invnext", &Command::cmd_void});
	map->insert({"invprev", &Command::cmd_void});
	map->insert({"+attack", &Command::cmd_void});
	map->insert({"+attack2", &Command::cmd_void});
}

void Command::cmd_void()
{
}

void Command::cmd_debug_frustumcull()
{
	Graphic::ins.camera.frustumCulling.debug();
}
