#ifndef __MT_PERLIN_NOISE_H__
#define __MT_PERLIN_NOISE_H__

namespace mt {
namespace engine {

class PerlinNoise {
public:

	// Constructor
	PerlinNoise();
	~PerlinNoise();

	// Generals
	double calHeight(double x, double y) const;

	// Get / Set
	double getPersistence() const;
	void setPersistence(double persistence);
	double getFrequency() const;
	void setFrequency(double frequency);
	double getAmplitude() const;
	void setAmplitude(double amplitude);
	int getOctaves() const;
	void setOctaves(int octaves);
	int getSeed() const;
	void setSeed(int seed);

private:

	// Variables
	double m_persistence, m_frequency, m_amplitude;
	int m_octaves, m_seed;

	// Generals
	double total(double i, double j) const;
	double getValue(double x, double y) const;
	double interpolate(double x, double y, double a) const;
	double noise(int x, int y) const;
};

}}

#endif
