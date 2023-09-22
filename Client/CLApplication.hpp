#pragma once
#include <Keyboard.h>
#include <memory>
#include <windows.h>

#pragma comment(lib, "Engine.lib")

namespace Client
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		virtual void Initialize(HWND hwnd, UINT width, UINT height);
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();
		void Resize(UINT width, UINT height);

		static DirectX::Keyboard::State GetKeyState();

		void SetWindow(HWND hwnd, UINT width, UINT height);

		UINT GetWidth() { return m_width_; }
		UINT GetHeight() { return m_height_; }
		HWND GetHwnd() { return m_hwnd_; }

	private:
		bool initialized_ = false;
		inline static std::unique_ptr<DirectX::Keyboard> m_input_{};

		HWND m_hwnd_;
		UINT m_width_;
		UINT m_height_;
	};
}
