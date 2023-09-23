#pragma once

#include <SimpleMath.h>

// LHS
constexpr DirectX::SimpleMath::Vector3 RIGHT = { 1.0f, 0.0f, 0.0f };
constexpr DirectX::SimpleMath::Vector3 UP = { 0.0f, 1.0f, 0.0f };
constexpr DirectX::SimpleMath::Vector3 FORWARD = { 0.0f, 0.0f, 1.0f };

constexpr float fov = DirectX::XM_PI / 4;
constexpr float nearZ = 0.3f;
constexpr float farZ = 1000.0f;