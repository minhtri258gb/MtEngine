#define __MT_PERLIN_NOISE_CPP__

#include "common.h"
#include "engine/Log.h"
#include "PerlinNoise.h"

using namespace mt::engine;


PerlinNoise::PerlinNoise() {
	LOG("PerlinNoise");
	try {
		m_persistence = 0.3;
		m_frequency = 1.0;
		m_amplitude  = 75.0;
		m_octaves = 3;
		m_seed = 19990309;
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
PerlinNoise::~PerlinNoise() {
	LOG("~PerlinNoise");
}

double PerlinNoise::getPersistence() const {
	return m_persistence;
}
double PerlinNoise::getFrequency() const {
	return m_frequency;
}
double PerlinNoise::getAmplitude() const {
	return m_amplitude;
}
int PerlinNoise::getOctaves() const {
	return m_octaves;
}
int PerlinNoise::getSeed() const {
	return m_seed;
}
double PerlinNoise::calHeight(double x, double y) const {
	return m_amplitude * this->total(x, y);
}

void PerlinNoise::setPersistence(double persistence) {
	m_persistence = persistence;
}
void PerlinNoise::setFrequency(double frequency) {
	m_frequency = frequency;
}
void PerlinNoise::setAmplitude(double amplitude) {
	m_amplitude = amplitude;
}
void PerlinNoise::setOctaves(int octaves) {
	m_octaves = octaves;
}
void PerlinNoise::setSeed(int seed) {
	m_seed = seed;
}

double PerlinNoise::total(double i, double j) const {
	//properties of one octave (changing each loop)
	double t = 0.0f;
	double amplitude = 1;
	double freq = m_frequency;

	for (int k = 0; k < m_octaves; k++) {
		t += this->getValue(j * freq + m_seed, i * freq + m_seed) * amplitude;
		amplitude *= m_persistence;
		freq *= 2;
	}

	return t;
}
double PerlinNoise::getValue(double x, double y) const {
	int iX = (int)x;
	int iY = (int)y;
	double Xfrac = x - iX;
	double Yfrac = y - iY;

	//noise values
	double n01 = noise(iX-1, iY-1);
	double n02 = noise(iX+1, iY-1);
	double n03 = noise(iX-1, iY+1);
	double n04 = noise(iX+1, iY+1);
	double n05 = noise(iX-1, iY);
	double n06 = noise(iX+1, iY);
	double n07 = noise(iX, iY-1);
	double n08 = noise(iX, iY+1);
	double n09 = noise(iX, iY);

	double n12 = noise(iX+2, iY-1);
	double n14 = noise(iX+2, iY+1);
	double n16 = noise(iX+2, iY);

	double n23 = noise(iX-1, iY+2);
	double n24 = noise(iX+1, iY+2);
	double n28 = noise(iX, iY+2);

	double n34 = noise(iX+2, iY+2);

	//find the noise values of the four corners
	double x0y0 = 0.0625*(n01+n02+n03+n04) + 0.125*(n05+n06+n07+n08) + 0.25*(n09);
	double x1y0 = 0.0625*(n07+n12+n08+n14) + 0.125*(n09+n16+n02+n04) + 0.25*(n06);
	double x0y1 = 0.0625*(n05+n06+n23+n24) + 0.125*(n03+n04+n09+n28) + 0.25*(n08);
	double x1y1 = 0.0625*(n09+n16+n28+n34) + 0.125*(n08+n14+n06+n24) + 0.25*(n04);

	//interpolate between those values according to the x and y fractions
	double v1 = interpolate(x0y0, x1y0, Xfrac); //interpolate in x direction (y)
	double v2 = interpolate(x0y1, x1y1, Xfrac); //interpolate in x direction (y+1)
	double fin = interpolate(v1, v2, Yfrac);  //interpolate in y direction

	return fin;
}
double PerlinNoise::interpolate(double x, double y, double a) const {
	double negA = 1.0 - a;
	double negASqr = negA * negA;
	double fac1 = 3.0 * (negASqr) - 2.0 * (negASqr * negA);
	double aSqr = a * a;
	double fac2 = 3.0 * aSqr - 2.0 * (aSqr * a);

	return x * fac1 + y * fac2; //add the weighted factors
}
double PerlinNoise::noise(int x, int y) const {
	int n = x + y * 57;
	n = (n << 13) ^ n;
	int t = (n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff;
	return 1.0 - double(t) * 0.931322574615478515625e-9;/// 1073741824.0);
}
