#define __MT_HEIGHTMAP_DATA_CPP__

// #include <stb_image.h>

#include "common.h"
#include "engine/Log.h"
#include "HeightmapData.h"

// #include "engine/file/BTFile.h"
#include "engine/file/Image.h"

#define MAXHEIGHTTERR 8.0f

using namespace std;
using namespace mt;
using namespace mt::engine;


class HeightmapData::HeightmapDataImpl {
public:

	// Struct
	enum HeightmapType {
		ARRAY = 1,
		IMAGE,
		NOISE
	};

	// Properties
	bool m_infinity;
	int m_depth;
	int m_width;
	float m_baseScale;
	float m_scale;
	float m_offset;

	// Object Data
	vector<float> data;
	PerlinNoise noise;
};


HeightmapData::HeightmapData() {
	LOG("HeightmapData");
	try {

		// Implement
		impl = new HeightmapDataImpl();
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
HeightmapData::~HeightmapData() {
	LOG("~HeightmapData");

	// Implement
	delete impl;
}

void HeightmapData::loadArray(float* pData, int depth, int width, vec2 range, float scale) {
	LOG("loadArray");
	try {

		// Validate
		if (scale == 0.0f)
			throw error("HEIGHT_SCALE_ZERO", "heightScale ko hop le!");

		// Convert data
		impl->data = vector(depth * width, 0.0f);
		for (int z = 0; z < width; z++) {
			for (int x = 0; x < depth; x++) {
				int index = (z*width + x);
				impl->data[index] = ((float)pData[index] / range.y + range.x) * scale;
			}
		}

		impl->m_infinity = false;
		impl->m_baseScale = 1.0f;
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
void HeightmapData::loadImage(std::string filepath, float scale) {
	LOG("loadImage");
	try {

		// Validate
		if (scale == 0.0f)
			throw error("HEIGHT_SCALE_ZERO", "heightScale ko hop le!");

		Image image;
		image.load(filepath);

		impl->m_depth = image.getWidth();
		impl->m_width = image.getHeight();

		// Convert data
		impl->data = vector(impl->m_depth * impl->m_width, 0.0f);
		for (int z = 0; z < impl->m_width; z++) {
			for (int x = 0; x < impl->m_depth; x++) {
				int index = (z*impl->m_width + x);
				// Màu từ 0 - 255, Chuyển thành 0 - 1, Nhân với độ cao địa hình
				impl->data[index] = (float)image[index] / 255.0f * scale;
			}
		}

		impl->m_infinity = false;
		impl->m_baseScale = 1.0f;
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
void HeightmapData::loadNoise(PerlinNoise& noise, int depth, int width, float scale) {
	LOG("loadNoise");
	try {
		impl->m_depth = depth;
		impl->m_width = width;
		impl->noise = noise;

		impl->m_infinity = true;
		impl->m_baseScale = scale;
		impl->m_scale = 1.0f;
		impl->m_offset = 0.0f;
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}

float HeightmapData::get(int z, int x) {
	LOG("get");
	try {

		if (impl->m_infinity) {
			return (float)(impl->noise.calHeight(x, z) + impl->noise.getAmplitude());
		}
		else {
			int index = (z*impl->m_width + x);
			return impl->data[index];
		}
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
float HeightmapData::getDepth() {
	return impl->m_depth;
}
float HeightmapData::getWidth() {
	return impl->m_width;
}
float HeightmapData::getScale() {
	return impl->m_baseScale * impl->m_scale;
}
float HeightmapData::getOffset() {
	return impl->m_offset;
}

vector<float> HeightmapData::getHeightData() {
	LOG("getDataTextureFromNoise");
	try {

		if (!impl->m_infinity)
			throw error("NOT_NOISE_TYPE", "HeightmapData ko phai du lieu Noise");

		int size = impl->m_depth * impl->m_width;
		vector<float> res(size, 0.0f);

		int nMax = -999999, nMin = 999999;
		for (int z = 0; z < impl->m_width; z++) {
			for (int x = 0; x < impl->m_depth; x++) {
				int index = (z*impl->m_width + x);
				float height = this->get(z, x);
				if (nMax < height) nMax = height;
				if (nMin > height) nMin = height;
				res[index] = height;
			}
		}

		impl->m_offset = nMin;
		impl->m_scale = nMax - nMin;

		for (int z = 0; z < impl->m_width; z++) {
			for (int x = 0; x < impl->m_depth; x++) {
				int index = (z*impl->m_width + x);
				res[index] = (res[index] - impl->m_offset) / impl->m_scale;
			}
		}

		return res;
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
