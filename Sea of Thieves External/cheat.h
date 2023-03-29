#pragma once
#include <vector>
#include <memory>

namespace cheat
{
	struct Settings
	{
		bool player_esp = false;
		bool creature_esp = false;
		bool ship_esp = false;
		bool treasure_esp = false;
		bool npc_esp = false;
		bool debug_esp = false;
	};

	Settings *settings();

	class Cheat abstract
	{
	public:
		Cheat()
		{
		}

		virtual void tick() = 0; // Not synced with in-game ticks, just called every time the overlay is rendered
	};

	class CheatManager
	{
	public:
		CheatManager()
		{
		}

		void add_cheat(std::shared_ptr<Cheat> cheat);
		void tick();

	private:
		std::vector<std::shared_ptr<Cheat>> _cheats{ };
	};

	CheatManager *cheat_manager();
}