#pragma once
#include <Windows.h>

#include <string>
#include <vector>
#include <memory>

#include "imgui/imgui.h"

#include "tab.h"

namespace gui
{
	class Menu
	{
	public:
		Menu(const std::string &title, float x, float y);

		void setup_fonts();
		void set_position(float x, float y);
		void draw() const;
		void process_key_input(int key_code);
		void add_tab(std::shared_ptr<Tab> tab);

	private:
		std::shared_ptr<Tab> get_selected_tab();
		void select_next_tab();
		void select_previous_tab();

		std::string _title;
		float _x;
		float _y;
		float _width = 200.0f;
		float _height = 300.0f;
		std::vector<std::shared_ptr<Tab>> _tabs{ };
		int _selected_tab = 0;
		bool _tab_opened = false;
		bool _visible = false;
		ImFont *_title_font = nullptr;
		ImFont *_tab_font = nullptr;
	};
}