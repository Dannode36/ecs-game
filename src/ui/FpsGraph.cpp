#include "ui/FpsGraph.h"
#include <imgui.h>

void MetricGraph::Render(std::string label, float value)
{
	if (frames.size() > 100) { //Max number of frames to show
		for (size_t i = 1; i < frames.size(); i++)
		{
			frames[i - 1] = frames[i];
		}
		frames[frames.size() - 1] = value;
	}
	else {
		frames.push_back(value);
	}

	ImGui::Text((label + ": %f").c_str(), value);

	ImGui::PlotHistogram(label.c_str(), &frames[0], (int)frames.size(), 0, NULL, graphMin, graphMax, ImVec2(300, 100));
}
