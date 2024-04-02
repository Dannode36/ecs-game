#include "ui/imgui/MetricGraph.h"
#include <imgui.h>

void MetricGraph::Render(std::string label, float value)
{
	float avg = 0.0f;
	float max = 0.0f;

	if (frames.size() > bufferSize) { //Max number of frames to show
		for (size_t i = 1; i < frames.size(); i++)
		{
			frames[i - 1] = frames[i];
		}
		frames[frames.size() - 1] = value;
	}
	else {
		frames.push_back(value);
	}

	//Calculate average value (could be done in above loop but wtf)
	for (size_t i = 0; i < frames.size(); i++)
	{
		avg += frames[i];
		max = fmaxf(max, frames[i]);
	}
	avg = avg / (float)bufferSize;

	ImGui::Text((label + ": %f | max %f |").c_str(), value, max);
	
	float histogramMax = fmaxf(avg * 2.71f, max); //magic number lmfao (almost e)
	ImGui::PlotHistogram(label.c_str(), &frames[0], (int)frames.size(), 0, NULL, graphMin, histogramMax, ImVec2(300, 100));
}
