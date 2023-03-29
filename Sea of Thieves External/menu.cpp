#include "menu.h"

#include "colors.h"

namespace gui
{
	Menu::Menu(const std::string &title, float x, float y)
		: _title(title)
		, _x(x)
		, _y(y)
	{
	} 

	void Menu::setup_fonts()
	{
		this->_title_font = ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\verdana.ttf", 32.0f);
		this->_tab_font = ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\tahoma.ttf", 20.0f);
	}

	void Menu::set_position(float x, float y)
	{
		this->_x = x;
		this->_y = y;
	}

	void Menu::draw() const	{
		if (!this->_visible) return;
		auto draw_list = ImGui::GetForegroundDrawList();
		draw_list->AddRectFilled({ this->_x, this->_y }, { this->_x + this->_width, this->_y + this->_height }, colors::background_color, 1.0f);
		draw_list->AddRect({ this->_x, this->_y }, { this->_x + this->_width, this->_y + this->_height }, colors::foreground_color, 1.0f);
		ImGui::PushFont(this->_title_font);
		draw_list->AddText({ this->_x + 16, this->_y + 8}, IM_COL32_WHITE, "SoT External");
		ImGui::PopFont();
		draw_list->AddLine({ this->_x + 5, this->_y + 50 }, { this->_x + this->_width - 5, this->_y + 50 }, colors::foreground_color);
		ImGui::PushFont(this->_tab_font);
		for (auto i = 0; i < this->_tabs.size(); ++i)
		{
			const auto tab = this->_tabs[i];
			tab->draw(this->_x, this->_y, i);
		}
		ImGui::PopFont();
	}

	void Menu::process_key_input(int key_code)
	{
		if (key_code == VK_DELETE)
		{
			this->_visible = !this->_visible;
			return;
		}

		if (!this->_visible) return;

		if (key_code == VK_LEFT)
		{
			this->_tab_opened = false;
			this->get_selected_tab()->close();
			return;
		}

		if (this->_tab_opened)
		{
			this->get_selected_tab()->process_key_input(key_code);
			return;
		}

		switch (key_code)
		{
		case VK_DOWN:
			this->select_next_tab();
			break;
		case VK_UP:
			this->select_previous_tab();
			break;
		case VK_RIGHT:
			this->_tab_opened = true;
			this->get_selected_tab()->open();
			break;
		}
	}

	void Menu::add_tab(std::shared_ptr<Tab> tab)
	{
		this->_tabs.push_back(tab);
		if (this->_tabs.size() == 1) this->get_selected_tab()->select();
	}

	std::shared_ptr<Tab> Menu::get_selected_tab()
	{
		return this->_tabs[this->_selected_tab];
	}

	void Menu::select_next_tab()
	{
		this->get_selected_tab()->deselect();
		++this->_selected_tab;
		if (this->_selected_tab > this->_tabs.size() - 1) this->_selected_tab = 0;
		this->get_selected_tab()->select();
	}

	void Menu::select_previous_tab()
	{
		this->get_selected_tab()->deselect();
		--this->_selected_tab;
		if (this->_selected_tab < 0) this->_selected_tab = static_cast<int>(this->_tabs.size()) - 1;
		this->get_selected_tab()->select();
	}
}