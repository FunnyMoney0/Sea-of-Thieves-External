#include "tab_item.h"

#include "imgui/imgui.h"
#include <Windows.h>

#include "colors.h"

namespace gui
{	
	void TabItem::draw(float x, float y, bool selected) const
	{
		bool state = this->_state ? *this->_state : false;
		auto highlight_color = state ? colors::enabled_color : colors::control_color;
		if (selected) highlight_color = colors::accent_color;
		auto draw_list = ImGui::GetForegroundDrawList();
		draw_list->AddRectFilled({ x, y }, { x + 190, y + 30 }, highlight_color, 1.0f);
		draw_list->AddText({ x + 5, y + 3 }, IM_COL32_WHITE, this->_name.c_str());
		if (state) draw_list->AddText({ x + 175, y + 3 }, IM_COL32_WHITE, "*");
	}

	void TabItem::toggle()
	{
		if (!this->_state) return;
		*this->_state = !*this->_state;
	}
}