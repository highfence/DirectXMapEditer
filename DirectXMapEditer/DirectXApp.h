#pragma once
#include <Windows.h>

namespace DirectXApp
{

	class DirectXApp
	{
	public:

		DirectXApp() = default;
		virtual ~DirectXApp() = default;

		virtual bool Init(HWND hWnd, const int width, const int height);
		virtual void Release();
		virtual void Render() = 0;

	protected :

		bool InitDevice();
		void SetWindowSize(const int width, const int height);

		HWND m_hWnd = nullptr;
		IDXGISwapChain* m_pSwapChain = nullptr;
		ID3D11Device* m_pD3dDevice = nullptr;
		ID3D11DeviceContext* m_pImmediateContext = nullptr;
		ID3D11RenderTargetView* m_pRenderTargetView = nullptr;

		D3D_FEATURE_LEVEL m_FeatureLevel = D3D_FEATURE_LEVEL_11_0;

	private:

		int m_Width = 0;
		int m_Height = 0;

	};
}