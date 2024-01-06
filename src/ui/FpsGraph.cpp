#include "FpsGraph.h"
#include <imgui.h>

void FPSGraph::Render(float dt)
{
	float fps = 1.f / dt;
	if (frames.size() > 100) { //Max number of frames to show
		for (size_t i = 1; i < frames.size(); i++)
		{
			frames[i - 1] = frames[i];
		}
		frames[frames.size() - 1] = fps;
	}
	else {
		frames.push_back(fps);
	}

	ImGui::Text("FPS: %f", fps);

	ImGui::PlotHistogram("Framerate", &frames[0], frames.size(), 0, NULL, 0.0f, 200.0f, ImVec2(300, 100));
}
