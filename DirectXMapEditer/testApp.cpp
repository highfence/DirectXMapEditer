#include "stdafx.h"
#include "testApp.h"

namespace DirectXFramework
{
	// TODO :: 렌더를 어떻게 처리하지?
	void TestApp::Render()
	{
		float clearColor[4] = { 0.f, 0.125f, 0.3f, 1.0f };

		m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, clearColor);

		m_pImmediateContext->IASetInputLayout(m_pVertexLayout);
		m_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		UINT stride = sizeof(MyVertex);
		UINT offset = 0;
		m_pImmediateContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

		m_pImmediateContext->VSSetShader(m_pVertexShader, NULL, 0);
		m_pImmediateContext->PSSetShader(m_pPixelShader, NULL, 0);
		m_pImmediateContext->Draw(3, 0);

		m_pSwapChain->Present(0, 0);
	}

	void TestApp::CreateShader()
	{
		D3D11_INPUT_ELEMENT_DESC layout[] = 
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"COLOR", 1, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};
		UINT layoutSize = ARRAYSIZE(layout);

		DirectXApp::CreateShader(L"MyShader.fx", layout, layoutSize);

		DirectXApp::CreateVertexBuffer();
	}
}