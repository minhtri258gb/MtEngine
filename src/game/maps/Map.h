#ifndef __MT_MAP_H__
#define __MT_MAP_H__

namespace mt {
namespace game {

class Map
{

public:

	// Variable
	// newton::NewtonWorld* world;

	// Forward
	Map();
	virtual ~Map();
	virtual void load();
	virtual void clear();
	virtual void update();
	virtual void render();

	// Native
	void setNeedLoad(bool);

protected:

	// Variable
	bool needLoading;

};

}}

#endif
