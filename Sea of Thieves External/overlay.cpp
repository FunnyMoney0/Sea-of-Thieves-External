#include "overlay.h"

#include <dwmapi.h>

#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace gui
{
	constexpr int listen_keys[] = { VK_DELETE, VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT, VK_RETURN };
	bool quit_requested = false;

	Overlay::Overlay(HINSTANCE instance, const std::string &title, HWND target_window, int cmd_show)
		: _title(title)
		, _target_window(target_window)
		, _menu(title, 30.0f, 30.0f)
	{
		this->setup_window(instance);
		this->setup_direct3D();
		ShowWindow(this->_window, cmd_show);
		UpdateWindow(this->_window);
		ImGui::CreateContext();
		this->_menu.setup_fonts();
		ImGui_ImplWin32_Init(this->_window);
		ImGui_ImplDX11_Init(this->_device, this->_context);
	}

	Menu &Overlay::menu()
	{
		return this->_menu;
	}

	void Overlay::add_draw_callback(DrawCallbackFn callback_fn)
	{
		this->_callbacks.push_back(callback_fn);
	}

	void Overlay::window_loop()
	{
		while (!quit_requested)
		{
			MSG msg{ };
			while (PeekMessageA(&msg, this->_window, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}

			RECT target_rect{ };
			GetWindowRect(this->_target_window, &target_rect);
			MoveWindow(this->_window, target_rect.left, target_rect.top, target_rect.right - target_rect.left, target_rect.bottom - target_rect.top, TRUE);
			ImGui_ImplWin32_NewFrame();
			ImGui_ImplDX11_NewFrame();
			ImGui::NewFrame();
			if (GetForegroundWindow() == this->_target_window)
			{
				for (int key_code : listen_keys)
				{
					if (GetAsyncKeyState(key_code) & 1) this->_menu.process_key_input(key_code);
				}
				this->_menu.draw();
				for (const DrawCallbackFn &callback_fn : this->_callbacks)
				{
					callback_fn();
				}
			}
			ImGui::Render();
			this->_context->OMSetRenderTargets(1, &this->_rt_view, nullptr);
			this->_context->ClearRenderTargetView(this->_rt_view, this->_clear_color);
			ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
			this->_swap_chain->Present(1, 0);
			Sleep(1);
		}

		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
		if (this->_swap_chain) this->_swap_chain->Release();
		if (this->_device) this->_device->Release();
		if (this->_context) this->_context->Release();
		if (this->_rt_view) this->_rt_view->Release();
		DestroyWindow(this->_window);
		UnregisterClassA(this->_window_class.lpszClassName, this->_window_class.hInstance);
		exit(0);
	}

	LRESULT Overlay::window_procedure(HWND window, UINT msg, WPARAM param1, LPARAM param2)
	{
		LRESULT result = ImGui_ImplWin32_WndProcHandler(window, msg, param1, param2);
		if (result) return result;

		switch (msg)
		{
		case WM_DESTROY:
			quit_requested = true;
			PostQuitMessage(0);
			return 0;
		}

		return DefWindowProcA(window, msg, param1, param2);
	}

	void Overlay::setup_window(HINSTANCE instance)
	{
		auto size = sizeof(this->_window_class);
		memset(&this->_window_class, 0, size);
		this->_window_class.cbSize = static_cast<UINT>(size);
		this->_window_class.style = CS_HREDRAW | CS_VREDRAW;
		this->_window_class.lpfnWndProc = Overlay::window_procedure;
		this->_window_class.hInstance = instance;
		this->_window_class.lpszClassName = "1337";
		RegisterClassExA(&this->_window_class);
		this->_window = CreateWindowExA(
			WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED, this->_window_class.lpszClassName,
			this->_title.c_str(), 
			WS_POPUP,
			0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
			nullptr, nullptr, instance, nullptr
		);
		SetLayeredWindowAttributes(this->_window, RGB(0, 0, 0), 255, LWA_ALPHA);
		RECT window_rect{ };
		GetWindowRect(this->_window, &window_rect);
		RECT client_rect{ };
		GetClientRect(this->_window, &client_rect);
		POINT offset{ 0, 0 };
		ClientToScreen(this->_window, &offset);
		MARGINS margins{ offset.x, offset.y, client_rect.top, client_rect.bottom };
		DwmExtendFrameIntoClientArea(this->_window, &margins);
	}

	void Overlay::setup_direct3D()
	{
		DXGI_SWAP_CHAIN_DESC desc{ };
		desc.BufferDesc.RefreshRate.Numerator = 60;
		desc.BufferDesc.RefreshRate.Denominator = 1;
		desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.SampleDesc.Count = 1;
		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.BufferCount = 2;
		desc.OutputWindow = this->_window;
		desc.Windowed = true;
		desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		
		D3D_FEATURE_LEVEL levels[] = { D3D_FEATURE_LEVEL_11_0 };
		D3D_FEATURE_LEVEL level{ };

		D3D11CreateDeviceAndSwapChain(
			nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, levels, 1, D3D11_SDK_VERSION, 
			&desc, &this->_swap_chain, &this->_device, &level, &this->_context
		);
		ID3D11Texture2D *back_buffer = nullptr;
		this->_swap_chain->GetBuffer(0, IID_PPV_ARGS(&back_buffer));
		this->_device->CreateRenderTargetView(back_buffer, nullptr, &this->_rt_view);
		back_buffer->Release();
	}
}