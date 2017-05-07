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
		m_pImmediateContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

		m_pImmediateContext->VSSetShader(m_pVertexShader, NULL, 0);
		m_pImmediateContext->PSSetShader(m_pPixelShader, NULL, 0);
		m_pImmediateContext->DrawIndexed(6, 0, 0);

		m_pSwapChain->Present(0, 0);
	}

	void TestApp::CreateShaderAndVertex()
	{
		D3D11_INPUT_ELEMENT_DESC layout[] = 
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};
		UINT layoutSize = ARRAYSIZE(layout);

		DirectXApp::CreateShader(L"MyShader.fx", layout, layoutSize);

		MyVertex vertices[] =
		{
			{ XMFLOAT3(-0.5f, 0.5f, 1.f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
			{ XMFLOAT3(0.5f, 0.5f, 1.f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
			{ XMFLOAT3(0.5f, -0.5f, 0.f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
			{ XMFLOAT3(-0.5f, -0.5f, 1.f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f) },
		};
		DirectXApp::CreateVertexBuffer(vertices, sizeof(vertices));

		UINT indices[] =
		{
			0, 1, 2,
			0, 2, 3
		};
		DirectXApp::CreateIndexBuffer(indices, sizeof(indices));
	}
}