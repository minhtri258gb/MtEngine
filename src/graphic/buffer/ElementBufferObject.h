#ifndef __MT_ELEMENT_BUFFER_OBJECT_H__
#define __MT_ELEMENT_BUFFER_OBJECT_H__

namespace mt {
namespace graphic {

class ElementBufferObject
{

public:

	// Variable
	unsigned int gl_EBO;

	// Forward
	ElementBufferObject();
	~ElementBufferObject();
	void init(std::vector<unsigned int> indices);

	// Native

};

}}

#endif
