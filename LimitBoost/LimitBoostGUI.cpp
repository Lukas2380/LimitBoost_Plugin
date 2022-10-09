#include "pch.h"
#include "LimitBoost.h"

/* Plugin Settings Window code here*/
std::string LimitBoost::GetPluginName() {
	return "LimitBoost";
}

// Render the plugin settings here
// This will show up in bakkesmod when the plugin is loaded at
//  f2 -> plugins -> LimitBoost
void LimitBoost::RenderSettings() {
	ImGui::TextUnformatted("LimitBoost plugin settings");

	

	CVarWrapper pluginenableCvar = cvarManager->getCvar("limit_boost");
	bool pluginenabled = pluginenableCvar.getBoolValue();
	if (ImGui::Checkbox("Enable plugin", &pluginenabled)) {
		pluginenableCvar.setValue(pluginenabled);
		if (pluginenabled == true) {
			cvarManager->log("LimitBoost plugin enabled");
		}
		else if (pluginenabled == false) {
			cvarManager->log("LimitBoost plugin disabled");
		}
	}
	if (ImGui::IsItemHovered()) {
		if (pluginenabled == true) {
			ImGui::SetTooltip("Disable this plugin (don't click this) :/");
		}
		else if (pluginenabled == false) {
			ImGui::SetTooltip("Enable this plugin!");
		}
	}


	CVarWrapper freeplayActiveCvar = cvarManager->getCvar("freeplay_active");
	bool freeplayActive = freeplayActiveCvar.getBoolValue();
	if (ImGui::Checkbox("Activate in Freeplay", &freeplayActive)) {
		freeplayActiveCvar.setValue(freeplayActive);
		if (freeplayActive == true) {
			cvarManager->log("LimitBoost in Freeplay enabled");
		}
		else if (freeplayActive == false) {
			cvarManager->log("LimitBoost in Freeplay disabled");
		}
	}
	if (ImGui::IsItemHovered()) {
		if (freeplayActive == true) {
			ImGui::SetTooltip("Deactivate LimitBoost in Freeplay");
		}
		else if (freeplayActive == false) {
			ImGui::SetTooltip("Activate LimitBoost in Freeplay");
		}
	}

	CVarWrapper customTrainingActiveCvar = cvarManager->getCvar("customTraining_active");
	bool customTrainingActive = customTrainingActiveCvar.getBoolValue();
	if (ImGui::Checkbox("Activate in Custom Training", &customTrainingActive)) {
		customTrainingActiveCvar.setValue(customTrainingActive);
		if (customTrainingActive == true) {
			cvarManager->log("LimitBoost in Custom Training enabled");
		}
		else if (customTrainingActive == false) {
			cvarManager->log("LimitBoost in Custom Training disabled");
		}
	}
	if (ImGui::IsItemHovered()) {
		if (customTrainingActive == true) {
			ImGui::SetTooltip("Deactivate LimitBoost in Custom Training");
		}
		else if (customTrainingActive == false) {
			ImGui::SetTooltip("Activate LimitBoost in Custom Training");
		}
	}
}


// Do ImGui rendering here
void LimitBoost::Render()
{
	if (!ImGui::Begin(menuTitle_.c_str(), &isWindowOpen_, ImGuiWindowFlags_None))
	{
		// Early out if the window is collapsed, as an optimization.
		ImGui::End();
		return;
	}

	ImGui::End();

	if (!isWindowOpen_)
	{
		cvarManager->executeCommand("togglemenu " + GetMenuName());
	}
}

// Name of the menu that is used to toggle the window.
std::string LimitBoost::GetMenuName()
{
	return "LimitBoost";
}

// Title to give the menu
std::string LimitBoost::GetMenuTitle()
{
	return menuTitle_;
}

// Don't call this yourself, BM will call this function with a pointer to the current ImGui context
void LimitBoost::SetImGuiContext(uintptr_t ctx)
{
	ImGui::SetCurrentContext(reinterpret_cast<ImGuiContext*>(ctx));
}

// Should events such as mouse clicks/key inputs be blocked so they won't reach the game
bool LimitBoost::ShouldBlockInput()
{
	return ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantCaptureKeyboard;
}

// Return true if window should be interactive
bool LimitBoost::IsActiveOverlay()
{
	return true;
}

// Called when window is opened
void LimitBoost::OnOpen()
{
	isWindowOpen_ = true;
}

// Called when window is closed
void LimitBoost::OnClose()
{
	isWindowOpen_ = false;
}

