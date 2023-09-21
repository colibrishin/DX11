#include "pch.h"
#include "CLApplication.hpp"
#include "CLDefaultScene.hpp"
#include "../Engine/EGRenderer.h"
#include "../Engine/EGDeltaTime.hpp"
#include "../Engine/EGD3DDevice.hpp"
#include "../Engine/EGSceneManager.hpp"

Client::Application::Application() : m_hwnd_(nullptr), m_width_(1024), m_height_(768)
{
}

Client::Application::~Application() = default;

void Client::Application::Run()
{
	Engine::DeltaTime::GetDeltaTime()->Tick([&]()
	{
		Update();
	});

	FixedUpdate();
	Render();
}

void Client::Application::Initialize()
{
	Engine::DeltaTime::Initialize();
	Engine::Graphics::D3DDevice::Initialize(m_hwnd_, m_width_, m_height_);
	Engine::Renderer::Initialize();
	Engine::Manager::SceneManager::Initialize();

	Engine::Manager::SceneManager::AddScene<DefaultScene>(L"Default");
	Engine::Manager::SceneManager::SetScene(L"Default");

	m_input_ = std::make_unique<DirectX::Keyboard>();
}

void Client::Application::Update()
{
	Engine::Manager::SceneManager::Update();
}

void Client::Application::FixedUpdate()
{
}

void Client::Application::Render()
{
	const auto dev = Engine::Graphics::D3DDevice::GetDevice();
	dev->Clear();
	dev->AdjustViewport();
	Engine::Manager::SceneManager::Render();
	dev->Present();
}

DirectX::Keyboard::State Client::Application::GetKeyState()
{
	return m_input_->GetState();
}

void Client::Application::SetWindow(HWND hwnd, UINT width, UINT height)
{
	m_hwnd_ = hwnd;
	m_width_ = width;
	m_height_ = height;
}
