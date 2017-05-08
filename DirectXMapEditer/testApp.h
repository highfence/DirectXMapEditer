#pragma once
#include "DirectXApp.h"

namespace DirectXFramework
{
	class TestApp : public DirectXApp
	{
	public :

		TestApp() = default;
		~TestApp() = default;

		void Render(float deltaTime) override;
		void ShaderSetting();

	private :

		void CreateShader();
		void CreateVertexBuffer();
		void CreateIndexBuffer();
		void InitMatrix();
		void CalculateMatrixForBox(float deltaTime);

	};
}
