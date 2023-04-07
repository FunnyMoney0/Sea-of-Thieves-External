#pragma once
#include <Windows.h>

#include <string>
#include <vector>

#include "tab_item.h"

namespace gui
{
	class Tab abstract
	{
	public:
		Tab(const std::string &name)
			: _name(name)
		{
		}

		void select();
		void deselect();
		void open();
		void close();
		void add_item(const TabItem &item);
		void draw(float x, float y, int index) const;
		void process_key_input(int key_code);

	protected:
		void draw_content(float x, float y) const;
		void next_item();
		void previous_item();

		std::string _name;
		bool _selected = false;
		bool _opened = false;
		std::vector<TabItem> _items{ };
		int _selected_item = 0;
	};
}