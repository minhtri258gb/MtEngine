#ifndef __MT_MAP_H__
#define __MT_MAP_H__

#include "../player/Player.h"


namespace mt {
namespace game {

class Map
{

public:

	// Variable
	Player player;

	// Forward
	Map();
	virtual ~Map();

	virtual void load();
	virtual void clear();
	virtual void update();

	// Native
	void setNeedLoad(bool);

protected:

	// Variable
	bool needLoading;

};

}}

#endif
