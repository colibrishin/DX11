#pragma once
#include "EGGameObject.hpp"

namespace Engine::Object
{
	using namespace DirectX;
	class Camera : public Abstract::GameObject
	{
	public:
		Camera(const std::wstring& name);
		Camera(const Camera&) = default;
		~Camera() override;

		void SetPosition(SimpleMath::Vector3 position);
		void SetRotation(SimpleMath::Vector3 rotation);

		void Render() override;
		void GetViewMatrix(XMMATRIX& view) const;

	private:
		XMMATRIX m_view_matrix_;
	};
}
