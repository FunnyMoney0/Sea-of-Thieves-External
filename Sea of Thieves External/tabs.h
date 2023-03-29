#pragma once
#include "tab.h"

#include "cheat.h"

namespace cheat
{
	class ESPTab : public gui::Tab
	{
	public:
		ESPTab()
			: Tab("ESP")
		{
			this->add_item(gui::TabItem{ "Players", &settings()->player_esp });
			this->add_item(gui::TabItem{ "Creatures", &settings()->creature_esp });
			this->add_item(gui::TabItem{ "Ships", &settings()->ship_esp });
			this->add_item(gui::TabItem{ "Treasure", &settings()->treasure_esp });
			this->add_item(gui::TabItem{ "NPCs", &settings()->npc_esp });
			this->add_item(gui::TabItem{ "Debug", &settings()->debug_esp });
		}
	};
}