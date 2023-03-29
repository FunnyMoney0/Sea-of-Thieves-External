#pragma once
#include "cheat.h"

#include <string>

#include "imgui/imgui.h"

#include "sdk.h"

namespace cheat
{
	class ESP : public Cheat
	{
	public:
		ESP();

		void tick() override;

	private:
		std::string convert_wide_string(const wchar_t *wide_string) const;

		void draw_text(float x, float y, const char *text, ImColor color);

		float _t = 0.0f;
		ImFont *_esp_font = nullptr;
	};
}