#include "esp.h"

#include <unordered_map>
#include <sstream>

#include "sot.h"
#include "cheat.h"

namespace cheat
{
	struct ActorESPInfo
	{
		std::string _text;
		ImColor _draw_color;
	};

	constexpr const ImColor _player_color{ 1.0f, 0.1f, 0.1f };

	constexpr const ImColor _creature_color{ 1.0f, 1.0f, 1.0f };
	constexpr const ImColor _ship_color{ 0.3f, 1.0f, 0.3f };
	constexpr const ImColor _treasure_color{ 1.0f, 1.0f, 0.3f };

	constexpr const ImColor _oos_color{ 1.0f, 0.4f, 1.0f };
	constexpr const ImColor _ghd_color{ 1.0f, 0.75f, 0.3f };
	constexpr const ImColor _mch_color{ 0.0f, 0.6f, 1.0f };
	constexpr const ImColor _cgr_color{ 1.0f, 0.3f, 0.3f };
	constexpr const ImColor _special_npc_color{ 0.1f, 1.0f, 0.6f };

	const std::unordered_map<SOT::ActorType, const ActorESPInfo> _creature_esp_info
	{
		{ SOT::ActorType::MERMAID,				ActorESPInfo{ "[Mermaid]", _creature_color } },
		{ SOT::ActorType::PIG,					ActorESPInfo{ "[Pig]", _creature_color } },
		{ SOT::ActorType::CHICKEN,				ActorESPInfo{ "[Chicken]", _creature_color } },
		{ SOT::ActorType::SNAKE,				ActorESPInfo{ "[Snake]", _creature_color } },
		{ SOT::ActorType::SHARK,				ActorESPInfo{ "[Shark]", _creature_color } },
		{ SOT::ActorType::SKELETON,				ActorESPInfo{ "[Skeleton]", _creature_color } },
		{ SOT::ActorType::PHANTOM,				ActorESPInfo{ "[Phantom]", _creature_color } },
		{ SOT::ActorType::SIREN,				ActorESPInfo{ "[Siren]", _creature_color } },
		{ SOT::ActorType::OCEAN_CRAWLER_HERMIT,	ActorESPInfo{ "[Hermit OC]", _creature_color } },
		{ SOT::ActorType::OCEAN_CRAWLER_CRAB,	ActorESPInfo{ "[Crab OC]", _creature_color } },
	};

	const std::unordered_map<SOT::ActorType, const ActorESPInfo> _ship_esp_info
	{
		{ SOT::ActorType::S_SHIP_TEMPLATE, ActorESPInfo{ "[Sloop]", _ship_color } },
		{ SOT::ActorType::M_SHIP_TEMPLATE, ActorESPInfo{ "[Brigantine]", _ship_color } },
		{ SOT::ActorType::L_SHIP_TEMPLATE, ActorESPInfo{ "[Galleon]", _ship_color } },
	};

	const std::unordered_map<SOT::ActorType, const ActorESPInfo> _treasure_esp_info
	{
		{ SOT::ActorType::SIREN_TRIDENT,				ActorESPInfo{ "[Trident of Dark Tides]", _treasure_color } },
		{ SOT::ActorType::B_GUNPOWDER_BARREL,			ActorESPInfo{ "[Stronghold Gunpowder Barrel]", _treasure_color } },
		{ SOT::ActorType::LOW_VALUE_GIFT,				ActorESPInfo{ "[Humble Gift]", _treasure_color } },
		{ SOT::ActorType::RITUAL_SKULL,					ActorESPInfo{ "[Ritual Skull]", _treasure_color } },
		{ SOT::ActorType::MY_BOUNTY_REWARD_SKULL,		ActorESPInfo{ "[Villainous Bounty Skull]", _treasure_color } },
		{ SOT::ActorType::SKELETON_ORDERS,				ActorESPInfo{ "[Skeleton's Orders]", _treasure_color } },
		{ SOT::ActorType::GOLD_POUCH,					ActorESPInfo{ "[Gold Pouch]", _treasure_color } },
		{ SOT::ActorType::MY_TREASURE_CHEST,			ActorESPInfo{ "[Captain's Chest]", _treasure_color } },
		{ SOT::ActorType::RA_TREASURE_CHEST,			ActorESPInfo{ "[Seafarer's Chest]", _treasure_color } },
		{ SOT::ActorType::COLLECTORS_CHEST,				ActorESPInfo{ "[Treasure Chest]", _treasure_color } },
		{ SOT::ActorType::ANCIENT_COLLECTORS_CHEST,		ActorESPInfo{ "[Chest of Ancient Tributes]", _treasure_color } },
		{ SOT::ActorType::ASHEN_CHEST_COLLECTORS_CHEST,	ActorESPInfo{ "[Ashen Chest]", _treasure_color } },
		{ SOT::ActorType::ASHEN_KEY,					ActorESPInfo{ "[Ashen Key]", _treasure_color } },
		{ SOT::ActorType::MERMAID_GEM_RUBY,				ActorESPInfo{ "[Ruby Mermaid Gem]", _treasure_color } },
		{ SOT::ActorType::MERMAID_GEM_EMERALD,			ActorESPInfo{ "[Emerald Mermaid Gem]", _treasure_color } },
		{ SOT::ActorType::MERMAID_GEM_SAPPHIRE,			ActorESPInfo{ "[Sapphire Mermaid Gem]", _treasure_color } },
		{ SOT::ActorType::MERMAID_GEM_RUBY,				ActorESPInfo{ "[Ammo Pouch]", _treasure_color } },
		{ SOT::ActorType::RA_BOUNTY_REWARD_SKULL,		ActorESPInfo{ "[Disgraced Bounty Skull]", _treasure_color } },
		{ SOT::ActorType::CORAL_MESSAGE_IN_A_BOTTLE,	ActorESPInfo{ "[Coral Message in a Bottle]", _treasure_color } },
		{ SOT::ActorType::MESSAGE_IN_A_BOTTLE,			ActorESPInfo{ "[Message in a Bottle]", _treasure_color } },
		{ SOT::ActorType::SUNKEN_CURSE_RUBY,			ActorESPInfo{ "[Ruby Cursed Mermaid Statue]", _treasure_color } },
		{ SOT::ActorType::SUNKEN_CURSE_EMERALD,			ActorESPInfo{ "[Emerald Cursed Mermaid Statue]", _treasure_color } },
		{ SOT::ActorType::SUNKEN_CURSE_SAPPHIRE,		ActorESPInfo{ "[Sapphire Cursed Mermaid Statue]", _treasure_color } },
		{ SOT::ActorType::BANANA_CRATE,					ActorESPInfo{ "[Fruit Crate]", _treasure_color } },
		{ SOT::ActorType::TREASURE_ARTIFACT_VASE_01,	ActorESPInfo{ "[Mysterious Vessel]", _treasure_color } },
		{ SOT::ActorType::TREASURE_ARTIFACT_VASE_02,	ActorESPInfo{ "[Elaborate Flagon]", _treasure_color } },
		{ SOT::ActorType::TREASURE_ARTIFACT_BOX_01,		ActorESPInfo{ "[Bronze Secret-Keeper]", _treasure_color } },
		{ SOT::ActorType::TREASURE_ARTIFACT_DVR_COMMON,	ActorESPInfo{ "[Roaring Goblet]", _treasure_color } },
	};

	const std::unordered_map<SOT::ActorType, const ActorESPInfo> _npc_esp_info
	{
		{ SOT::ActorType::OOS_OPRAH,			ActorESPInfo{ "[Oprah]", _oos_color } },
		{ SOT::ActorType::OOS_OLIVE,			ActorESPInfo{ "[Olive]", _oos_color } },
		{ SOT::ActorType::OOS_MADAME_OLWEN,		ActorESPInfo{ "[Olwen]", _oos_color } },
		{ SOT::ActorType::OOS_OKSANA,			ActorESPInfo{ "[Oksana]", _oos_color } },
		{ SOT::ActorType::OOS_OLGA,				ActorESPInfo{ "[Olga]", _oos_color } },
		{ SOT::ActorType::OOS_OLIVIA,			ActorESPInfo{ "[Olivia]", _oos_color } },
		{ SOT::ActorType::OOS_OYA,				ActorESPInfo{ "[Oya]", _oos_color } },

		{ SOT::ActorType::GHD_HORACE,			ActorESPInfo{ "[Horace]", _ghd_color } },
		{ SOT::ActorType::GHD_HUMPHREY,			ActorESPInfo{ "[Humphrey]", _ghd_color } },
		{ SOT::ActorType::GHD_HERBERT,			ActorESPInfo{ "[Herbert]", _ghd_color } },
		{ SOT::ActorType::GHD_HARRY,			ActorESPInfo{ "[Harry]", _ghd_color } },
		{ SOT::ActorType::GHD_HENRY,			ActorESPInfo{ "[Henry]", _ghd_color } },
		{ SOT::ActorType::GHD_HUGH,				ActorESPInfo{ "[Hugh]", _ghd_color } },
		{ SOT::ActorType::GHD_HYDE,				ActorESPInfo{ "[Hyde]", _ghd_color } },

		{ SOT::ActorType::MCH_MANDY,			ActorESPInfo{ "[Mandy]", _mch_color } },
		{ SOT::ActorType::MCH_MOLLIE,			ActorESPInfo{ "[Mollie]", _mch_color } },
		{ SOT::ActorType::MCH_MILDRED,			ActorESPInfo{ "[Mildred]", _mch_color } },
		{ SOT::ActorType::MCH_MAUREEN,			ActorESPInfo{ "[Maureen]", _mch_color } },
		{ SOT::ActorType::MCH_MEG,				ActorESPInfo{ "[Meg]", _mch_color } },
		{ SOT::ActorType::MCH_MAVIS,			ActorESPInfo{ "[Mavis]", _mch_color } },
		{ SOT::ActorType::MCH_MATILDA,			ActorESPInfo{ "[Matilda]", _mch_color } },

		{ SOT::ActorType::CGR_CHARLOTTE,		ActorESPInfo{ "[Charlotte]", _cgr_color } },
		{ SOT::ActorType::GHOST_SHIP_CAPTAIN,	ActorESPInfo{ "[Ghost Ship Captain]", _special_npc_color } },
	};

	ESP::ESP()
	{
		this->_esp_font = ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 15.0f);
	}

	std::string ESP::convert_wide_string(const wchar_t *wide_string) const
	{
		if (!wide_string) return "";
		std::stringstream result{ };
		const auto size = wcslen(wide_string);
		for (auto i = 0; i < size; ++i)
		{
			result << static_cast<char>(wide_string[i]);
		}
		return result.str();
	}

	void ESP::draw_text(float x, float y, const char *text, ImColor color)
	{
		auto draw_list = ImGui::GetBackgroundDrawList();
		draw_list->AddText(ImVec2{ x, y }, color, text);
	}

	void ESP::tick()
	{
		ImGui::PushFont(this->_esp_font);

		const auto camera_pov = game()->world().owning_game_instance().local_player().player_controller().player_camera_manager().camera_cache().pov();
		const auto actors = game()->world().persistent_level().actors();
		auto actor_list = actors.get_data(actors.array_num());

		std::vector<const std::unordered_map<SOT::ActorType, const ActorESPInfo> *> esp_info_list;
		if (settings()->ship_esp) esp_info_list.push_back(&_ship_esp_info);
		if (settings()->creature_esp) esp_info_list.push_back(&_creature_esp_info);
		if (settings()->treasure_esp) esp_info_list.push_back(&_treasure_esp_info);
		if (settings()->npc_esp) esp_info_list.push_back(&_npc_esp_info);

		for (sdk::AActor &actor : actor_list)
		{
			const auto actor_type = game()->get_actor_type(actor.id());
			
			for (const auto esp_info : esp_info_list)
			{
				if (esp_info->count(actor_type))
				{
					sdk::Vector3 pos = actor.root_component().relative_location();
					sdk::Vector2 screen_coords{ };
					if (game()->world_to_screen(camera_pov, pos, &screen_coords))
					{
						const auto &draw_info = esp_info->at(actor_type);
						this->draw_text(screen_coords._x + 1.0f, screen_coords._y + 1.0f, draw_info._text.c_str(), ImColor{ 0.0f, 0.0f, 0.0f });
						this->draw_text(screen_coords._x + 1.0f, screen_coords._y - 1.0f, draw_info._text.c_str(), ImColor{ 0.0f, 0.0f, 0.0f });
						this->draw_text(screen_coords._x - 1.0f, screen_coords._y - 1.0f, draw_info._text.c_str(), ImColor{ 0.0f, 0.0f, 0.0f });
						this->draw_text(screen_coords._x - 1.0f, screen_coords._y + 1.0f, draw_info._text.c_str(), ImColor{ 0.0f, 0.0f, 0.0f });
						this->draw_text(screen_coords._x, screen_coords._y, draw_info._text.c_str(), draw_info._draw_color);
					}
				}
			}

			if (settings()->player_esp)
			{
				if (actor_type == SOT::ActorType::PLAYER_PIRATE)
				{
					sdk::Vector3 pos = actor.root_component().relative_location();
					sdk::Vector2 screen_coords{ };
					if (game()->world_to_screen(camera_pov, pos, &screen_coords))
					{
						sdk::AAthenaCharacter character{ actor.instance() };
						const sdk::FString name = character.player_state().player_name();
						const std::string name_text = this->convert_wide_string(name.data().get_data(name.data().array_num()).data());
						std::string name_draw_text = "[" + name_text + "]";
						const float percentage = character.health_component().current_health() / character.health_component().max_health();
						ImColor name_color{ 1.0f - percentage, percentage, 0.0f };
						this->draw_text(screen_coords._x + 1.0f, screen_coords._y + 1.0f, name_draw_text.c_str(), ImColor{ 0.0f, 0.0f, 0.0f });
						this->draw_text(screen_coords._x - 1.0f, screen_coords._y + 1.0f, name_draw_text.c_str(), ImColor{ 0.0f, 0.0f, 0.0f });
						this->draw_text(screen_coords._x - 1.0f, screen_coords._y - 1.0f, name_draw_text.c_str(), ImColor{ 0.0f, 0.0f, 0.0f });
						this->draw_text(screen_coords._x + 1.0f, screen_coords._y - 1.0f, name_draw_text.c_str(), ImColor{ 0.0f, 0.0f, 0.0f });
						this->draw_text(screen_coords._x, screen_coords._y, name_draw_text.c_str(), name_color);
					}
				}
			}

			if (settings()->debug_esp)
			{
				sdk::Vector3 pos = actor.root_component().relative_location();
				sdk::Vector2 screen_coords{ };
				if (game()->world_to_screen(camera_pov, pos, &screen_coords))
				{
					std::string draw_text = game()->get_actor_name(actor.id());
					if (draw_text.find("ItemInfo") == std::string::npos)
					{
						this->draw_text(screen_coords._x + 1.0f, screen_coords._y + 1.0f, draw_text.c_str(), ImColor{ 0.0f, 0.0f, 0.0f });
						this->draw_text(screen_coords._x - 1.0f, screen_coords._y + 1.0f, draw_text.c_str(), ImColor{ 0.0f, 0.0f, 0.0f });
						this->draw_text(screen_coords._x - 1.0f, screen_coords._y - 1.0f, draw_text.c_str(), ImColor{ 0.0f, 0.0f, 0.0f });
						this->draw_text(screen_coords._x + 1.0f, screen_coords._y - 1.0f, draw_text.c_str(), ImColor{ 0.0f, 0.0f, 0.0f });
						this->draw_text(screen_coords._x, screen_coords._y, draw_text.c_str(), ImColor{ 0.0f, 1.0f, 0.75f });
					}
				}
			}
		}

		ImGui::PopFont();
	}
}
