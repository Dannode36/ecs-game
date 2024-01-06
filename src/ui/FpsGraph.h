#pragma once
#include <vector>

using namespace std;

class FPSGraph
{
public:
	void Render(float dt);
private:
	vector<float> frames;
};
