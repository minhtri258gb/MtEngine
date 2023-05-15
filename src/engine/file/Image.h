#ifndef __MT_IMAGE_H__
#define __MT_IMAGE_H__

namespace mt {

class Image
{
public:

	// Variable
	bool flip;

	// Forwards
	Image();
	~Image();
	void load(std::string filepath);

	// Natives
	int getWidth();
	int getHeight();
	int getChannel();
	unsigned char* getDataPtr();

	// Operators
	unsigned char operator [] (unsigned int) const;

private:

	// Variables
	unsigned char *data;
	int width, height, nrChannels;
};

}

#endif
