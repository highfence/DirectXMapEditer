#include "stdafx.h"
#include "DirectXApp.h"

namespace DirectXApp
{
	bool DirectXApp::Init(HWND hWnd, const int width, const int height)
	{
		if (hWnd == nullptr) return false;

		SetWindowSize(width, height);
		m_hWnd = hWnd;

		if (!InitDevice()) return false;

		return true;
	}

	bool DirectXApp::InitDevice()
	{
		HRESULT hr = S_OK;

		UINT createDeviceFlags = 0;
#ifdef _DEBUG
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
		};

		UINT numFeatureLevels = ARRAYSIZE(featureLevels);

		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.BufferCount = 1;

		sd.BufferDesc.Width = m_Width;
		sd.BufferDesc.Height = m_Height;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;

		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow = m_hWnd;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.Windowed = TRUE;
		
		hr = D3D11CreateDeviceAndSwapChain(0, D3D_DRIVER_TYPE_HARDWARE,
			0, createDeviceFlags, featureLevels, numFeatureLevels, D3D11_SDK_VERSION,
			&sd, &m_pSwapChain, &m_pD3dDevice, &m_FeatureLevel, &m_pImmediateContext);

		if (FAILED(hr)) return false;

		ID3D11Texture2D* pBackBuffer = nullptr;
		hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

		if (FAILED(hr)) return false;

		hr = m_pD3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView);
		pBackBuffer->Release();

		if (FAILED(hr)) return false;

		m_pImmediateContext->OMSetRenderTargets(1, &m_pRenderTargetView, NULL);

		D3D11_VIEWPORT vp;
		vp.Width = m_Width;
		vp.Height = m_Height;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		m_pImmediateContext->RSSetViewports(1, &vp);

		return true;
	}

	void DirectXApp::SetWindowSize(const int width, const int height)
	{
		m_Width = width;
		m_Height = height;
	}
}