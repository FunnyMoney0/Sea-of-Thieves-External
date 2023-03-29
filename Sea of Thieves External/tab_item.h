#pragma once
#include <string>

namespace gui
{
	class TabItem
	{
	public:
		TabItem(const std::string &name, bool *state)
			: _name(name)
			, _state(state)
		{
		}

		void draw(float x, float y, bool selected) const;
		void toggle();

	private:
		std::string _name;
		bool *_state;
	};
}