#include "managers/AssetManager.h"
#include "imgui.h" // necessary for ImGui::*, imgui-SFML.h doesn't include imgui.h
#include "imgui-SFML.h" // for ImGui::SFML::* functions and SFML-specific overloads

void AssetManager::RenderDebugMetricsUI(bool* open)
{
	if(ImGui::Begin("Asset Cache Metrics", open)) {
		//ImGui::Text("Texture Cache Size: %d", textureCache.validAssetCount());
		//ImGui::Text("Sound Cache Size: %d", soundCache.validAssetCount());
		//ImGui::Text("Music Cache Size: %d", musicCache.validAssetCount());
	}
	ImGui::End();
}
