#pragma once
#include <vector>
#include <string>

class MetricGraph
{
public:
	void Render(std::string label, float value);
	float graphMin = 0.0f;
	float bufferSize = 100;
private:
	std::vector<float> frames;
};
