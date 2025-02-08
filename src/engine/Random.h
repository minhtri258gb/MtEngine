#ifndef __MT_RANDOM_H__
#define __MT_RANDOM_H__

namespace mt {
namespace engine {

class Random {
public:

  // Static
	static Random ins;

	// Constructor
	Random();
	~Random();

	// General
	bool probability(unsigned int n);
	unsigned int rand(unsigned int n);
	int range(int, int);
	float rangeF(float, float);

private:

  class RandomImpl;
  RandomImpl* impl;

};

}}

#endif
