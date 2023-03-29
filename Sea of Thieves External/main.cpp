#include "overlay.h"
#include "tabs.h"
#include "sot.h"
#include "esp.h"

#include <iostream>

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prev_instance, PSTR cmd_line, int cmd_show)
{
	if (!cheat::game()->init()) 
	{ 
		MessageBoxA(nullptr, "Initialization failed.", "Error", MB_OK); 
		return 0;
	}

	auto overlay = gui::Overlay{ instance, "Overlay", FindWindowA(nullptr, "Sea of Thieves"), cmd_show };

	overlay.menu().add_tab(std::make_shared<cheat::ESPTab>());

	cheat::cheat_manager()->add_cheat(std::make_shared<cheat::ESP>());

	overlay.add_draw_callback([]() { cheat::cheat_manager()->tick(); });
	overlay.window_loop();
	return 0;
}