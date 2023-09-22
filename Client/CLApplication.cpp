#include "pch.h"
#include "CLApplication.hpp"
#include "CLDefaultScene.hpp"
#include "../Engine/EGRenderer.h"
#include "../Engine/EGDeltaTime.hpp"
#include "../Engine/EGD3DDevice.hpp"
#include "../Engine/EGSceneManager.hpp"

Client::Application::Application() : m_hwnd_(nullptr), m_width_(0), m_height_(0)
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

void Client::Application::Initialize(HWND hwnd, UINT width, UINT height)
{
	m_hwnd_ = hwnd;
	m_width_ = width;
	m_height_ = height;

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
	if(dev->IsResized())
	{
		dev->Resize(m_width_, m_height_);
	}

	dev->Clear();
	dev->AdjustViewport();
	Engine::Manager::SceneManager::Render();
	dev->Present();
}

void Client::Application::Resize(UINT width, UINT height)
{
	Engine::Graphics::D3DDevice::GetDevice()->SetResized();
	Engine::Graphics::D3DDevice::GetDevice()->SetWidth(width);
	Engine::Graphics::D3DDevice::GetDevice()->SetHeight(height);
	m_width_ = width;
	m_height_ = height;
}

DirectX::Keyboard::State Client::Application::GetKeyState()
{
	return m_input_->GetState();
}
