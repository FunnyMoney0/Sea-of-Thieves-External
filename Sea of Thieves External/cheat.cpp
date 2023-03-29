#include "cheat.h"

namespace cheat
{
	Settings _settings{ };

	Settings *settings()
	{
		return &_settings;
	}

	void CheatManager::add_cheat(std::shared_ptr<Cheat> cheat)
	{
		this->_cheats.push_back(cheat);
	}

	void CheatManager::tick()
	{
		for (std::shared_ptr<Cheat> &cheat : this->_cheats)
		{
			cheat->tick();
		}
	}

	CheatManager _cheat_manager{ };

	CheatManager *cheat_manager()
	{
		return &_cheat_manager;
	}
}