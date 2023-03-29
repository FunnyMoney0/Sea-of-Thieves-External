#pragma once
#include <Windows.h>
#include <d3d11.h>

#include <string>
#include <vector>

#include "menu.h"

namespace gui
{
	class Overlay
	{
	public:
		Overlay(HINSTANCE instance, const std::string &title, HWND target_window, int cmd_show);
		void window_loop();
		Menu &menu();

		using DrawCallbackFn = void(*)();
		void add_draw_callback(DrawCallbackFn callback_fn);

	private:
		static LRESULT window_procedure(HWND window, UINT msg, WPARAM param1, LPARAM param2);

		void setup_window(HINSTANCE instance);
		void setup_direct3D();

		const float _clear_color[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

		std::string _title;
		HWND _target_window;
		WNDCLASSEXA _window_class;
		HWND _window;
		IDXGISwapChain *_swap_chain;
		ID3D11Device *_device;
		ID3D11DeviceContext *_context;
		ID3D11RenderTargetView *_rt_view;
		Menu _menu;
		std::vector<DrawCallbackFn> _callbacks{ };
	};
}