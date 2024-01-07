#pragma once
#include <vector>
#include <string>

class MetricGraph
{
public:
	void Render(std::string label, float value);
	float graphMin = 0.f;
	float graphMax = 200.f;
private:
	std::vector<float> frames;
};
