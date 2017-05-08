#pragma once
#include <Windows.h>
class GameTimer;

namespace DirectXFramework
{

	class DirectXApp
	{
	public:

		DirectXApp() = default;
		virtual ~DirectXApp() = default;

		virtual bool Init(HWND hWnd, const int width, const int height);
		virtual void Release();
		virtual void Render(float deltaTime) = 0;
		GameTimer* GetTimer() { return m_pTimer; };

	protected :

		bool InitDevice();
		void SetWindowSize(const int width, const int height);
		bool CreateShader(const wchar_t* shaderPath, D3D11_INPUT_ELEMENT_DESC* layout, UINT layoutSize);
		bool CreateVertexBuffer(MyVertex* vertices, UINT verticesNumber);
		bool CreateIndexBuffer(UINT* indices, UINT indicesSize);
		bool CreateConstantBuffer();

		HWND m_hWnd = nullptr;
		IDXGISwapChain* m_pSwapChain = nullptr;
		ID3D11Device* m_pD3dDevice = nullptr;
		ID3D11DeviceContext* m_pImmediateContext = nullptr;
		ID3D11RenderTargetView* m_pRenderTargetView = nullptr;
		ID3D11VertexShader* m_pVertexShader = nullptr;
		ID3D11InputLayout* m_pVertexLayout = nullptr;
		ID3D11Buffer* m_pVertexBuffer = nullptr;
		ID3D11PixelShader* m_pPixelShader = nullptr;
		ID3D11Buffer* m_pIndexBuffer = nullptr;

		D3D_FEATURE_LEVEL m_FeatureLevel = D3D_FEATURE_LEVEL_11_0;

		XMMATRIX m_World;
		XMMATRIX m_View;
		XMMATRIX m_Projection;
		ID3D11Buffer* m_pConstantBuffer = nullptr;

	private :

		GameTimer* m_pTimer;
		int m_Width = 0;
		int m_Height = 0;

	};
}