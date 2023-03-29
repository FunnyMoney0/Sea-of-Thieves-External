#include "tab.h"

#include "colors.h"

namespace gui
{

	void Tab::select()
	{
		this->_selected = true;
	}

	void Tab::deselect()
	{
		this->_selected = false;
	}

	void Tab::open()
	{
		this->_opened = true;
	}

	void Tab::close()
	{
		this->_selected_item = 0;
		this->_opened = false;
	}

	void Tab::add_item(const TabItem &item)
	{
		this->_items.push_back(item);
	}

	void Tab::draw(float x, float y, int index) const
	{
		const auto &highlight_color = this->_selected ? colors::accent_color : colors::control_color;
		auto draw_list = ImGui::GetForegroundDrawList();
		auto tab_x = x + 5;
		auto tab_y = y + 60 + index * 35;
		draw_list->AddRectFilled({ tab_x, tab_y }, { tab_x + 190, tab_y + 30 }, highlight_color, 1.0f);
		draw_list->AddText({ tab_x + 5, tab_y + 3 }, IM_COL32_WHITE, this->_name.c_str());
		char indicator = this->_selected && this->_opened ? '<' : '>';
		draw_list->AddText({ tab_x + 175, tab_y + 3 }, IM_COL32_WHITE, &indicator, &indicator + 1);
		if (this->_selected && this->_opened) this->draw_content(x + 210, y);
	}

	void Tab::draw_content(float x, float y) const
	{
		auto draw_list = ImGui::GetForegroundDrawList();
		draw_list->AddRectFilled({ x, y }, { x + 200, y + 300 }, colors::background_color, 1.0f);
		draw_list->AddRect({ x, y }, { x + 200, y + 300 }, colors::foreground_color, 1.0f);
		for (int i = 0; i < this->_items.size(); ++i)
		{
			const auto &item = this->_items[i];			
			auto item_x = x + 5;
			auto item_y = y + 5 + i * 35;
			bool is_selected = i == this->_selected_item;
			item.draw(item_x, item_y, is_selected);
		}
	}

	void Tab::process_key_input(int key_code)
	{
		switch (key_code)
		{
		case VK_DOWN:
			this->next_item();
			break;
		case VK_UP:
			this->previous_item();
			break;
		case VK_RIGHT:
			this->_items[this->_selected_item].toggle();
		}
	}

	void Tab::next_item()
	{
		++this->_selected_item;
		if (this->_selected_item > this->_items.size() - 1) this->_selected_item = 0;
	}

	void Tab::previous_item()
	{
		--this->_selected_item;
		if (this->_selected_item < 0) this->_selected_item = this->_items.size() - 1;
	}
}