#include "pch.h"
#include "LimitBoost.h"


BAKKESMOD_PLUGIN(LimitBoost, "Limit Boost", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

bool limitBoostEnabled = true;
bool freeplayActive = false;
bool customTrainingActive = false;

void LimitBoost::onLoad()
{
	gameWrapper->HookEvent("Function Engine.GameViewportClient.Tick", bind(&LimitBoost::onTick, this, std::placeholders::_1));

	_globalCvarManager = cvarManager;

	cvarManager->registerCvar("limit_boost", "1", "Enable Limit Boost", true, true, 0, true, 1)
		.addOnValueChanged([this](std::string oldValue, CVarWrapper cvar) {
		limitBoostEnabled = cvar.getBoolValue();
			});

	cvarManager->registerCvar("freeplay_active", "0", "Enable LimitBoost in Freeplay", true, true, 0, true, 1)
		.addOnValueChanged([this](std::string oldValue, CVarWrapper cvar) {
		freeplayActive = cvar.getBoolValue();
		if (!freeplayActive && !isBoostUnlimited)
		{
			cvarManager->executeCommand("boost set unlimited");
			isBoostUnlimited = true;
		}
			});
	
	cvarManager->registerCvar("customTraining_active", "0", "Enable LimitBoost in Custom Training", true, true, 0, true, 1)
		.addOnValueChanged([this](std::string oldValue, CVarWrapper cvar) {
		customTrainingActive = cvar.getBoolValue();
		if (!customTrainingActive && !isBoostUnlimited)
		{
			cvarManager->executeCommand("boost set unlimited");
			isBoostUnlimited = true;
		}
			});
}

void LimitBoost::onTick(std::string eventName)
{
	if (gameWrapper->IsInFreeplay() && freeplayActive || gameWrapper->IsInCustomTraining() && customTrainingActive) {

		if (!limitBoostEnabled) { return; }

		CarWrapper car = gameWrapper->GetLocalCar();
		if (car.IsNull())
		{
			return;
		}

		bool isCarOnGround = car.GetLocation().Z <= 35 && car.IsOnGround() && !car.IsOnWall(); 
		// IsOnGround and !IsOnWall alone dont work since you still get infinite boost when on ceiling/getting a flip reset so I also gave it a min height 

		if (isCarOnGround && !isBoostUnlimited)
		{
			cvarManager->executeCommand("boost set unlimited");
			isBoostUnlimited = true;
		}
		else if (!isCarOnGround && isBoostUnlimited)
		{
			cvarManager->executeCommand("boost set limited");
			isBoostUnlimited = false;
		}
	}
}