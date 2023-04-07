#include "other.h"

#include <unordered_map>
#include <sstream>

#include "sot.h"
#include "cheat.h"

namespace cheat
{
	struct ActorOtherInfo
	{
		std::string _text;
		ImColor _draw_color;
	};

	constexpr const ImColor _player_drawing_color{ 1.0f, 0.1f, 0.1f };

	/*const std::unordered_map<SOT::ActorType, const ActorOtherInfo> _player_drawing_info
	{
		{ SOT::ActorType::PLAYER_PIRATE,				ActorOtherInfo{ _player_drawing_color } }

	};*/

	Other::Other()
	{
		this->_other_font = ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 15.0f);
	}

	void Other::draw_text(float x, float y, const char* text, ImColor color)
	{
		auto draw_list = ImGui::GetBackgroundDrawList();
		draw_list->AddText(ImVec2{ x, y }, color, text);
	}

	void Other::tick()
	{
		ImGui::PushFont(this->_other_font);

		const auto actors = game()->world().persistent_level().actors();
		auto actor_list = actors.get_data(actors.array_num());

		std::vector<const std::unordered_map<SOT::ActorType, const ActorOtherInfo>*> other_info_list;

		//if (settings()->other_esp) other_info_list.push_back(&_player_drawing_color);

		for (sdk::AActor& actor : actor_list)
		{
			const auto actor_type = game()->get_actor_type(actor.id());

			for (const auto other_info : other_info_list)
			{
				/*if (other_info->count(actor_type))
				{
					const auto& draw_info = other_info->at(actor_type);
					this->draw_text(0 + 1.0f, 50 + 1.0f, draw_info._text.c_str(), ImColor{ 0.0f, 0.0f, 0.0f });
				}*/
			}

			if (settings()->other_esp)
			{
				if (actor_type == SOT::ActorType::PLAYER_PIRATE)
				{
					sdk::AAthenaCharacter character{ actor.instance() };
					float oxygen = character.drowning_component().oxygen_level();

					std::string oxygen_str = std::to_string(static_cast<int>(oxygen * 100)) + "%";
					oxygen_str = "Oxygen: " + oxygen_str;
					//std::string oxygen_str = std::to_string((oxygen * 100));

					sdk::Vector2 screen_coords{10, 250};
					//std::string conv = oxygen;
					this->draw_text(screen_coords._x, screen_coords._y, oxygen_str.c_str(), {255.0f, 255.0f, 255.0f});
				}
			}
		}
		ImGui::PopFont();
	}
}