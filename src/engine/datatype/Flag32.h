#ifndef __MT_FLAG_32_H__
#define __MT_FLAG_32_H__

namespace mt {
namespace engine {

typedef class Flag32
{
public:

	// Forwards
	Flag32();
	Flag32(unsigned int);
	~Flag32();

	// Get / Set
	bool check(unsigned int);
	void setOn(unsigned int rhs);
	void setOff(unsigned int rhs);
	void setFlip(unsigned int rhs);

	unsigned int get();

private:

	// Variable
	unsigned int core;

} flag;

}}

#endif
