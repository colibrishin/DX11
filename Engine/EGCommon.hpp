#pragma once

#include <SimpleMath.h>

constexpr DirectX::SimpleMath::Vector3 up = {0.0f, 1.0f, 0.0f};
constexpr DirectX::SimpleMath::Vector3 down = {0.0f, -1.0f, 0.0f};
constexpr DirectX::SimpleMath::Vector3 left = {-1.0f, 0.0f, 0.0f};
constexpr DirectX::SimpleMath::Vector3 right = {1.0f, 0.0f, 0.0f};

constexpr float fov = DirectX::XM_PI / 4;
constexpr float nearZ = 0.3f;
constexpr float farZ = 1000.0f;