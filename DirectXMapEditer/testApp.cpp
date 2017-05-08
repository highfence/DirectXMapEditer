#include "stdafx.h"
#include "testApp.h"

namespace DirectXFramework
{
	void TestApp::Render(float deltaTime)
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
		CalculateMatrixForBox(deltaTime);
		m_pImmediateContext->DrawIndexed(36, 0, 0);

		m_pSwapChain->Present(0, 0);
	}

	void TestApp::ShaderSetting()
	{
		CreateShader();

		CreateVertexBuffer();

		CreateIndexBuffer();

		InitMatrix();
	}

	void TestApp::CreateShader()
	{
		D3D11_INPUT_ELEMENT_DESC layout[] = 
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};
		UINT layoutSize = ARRAYSIZE(layout);

		DirectXApp::CreateShader(L"MyShader.fx", layout, layoutSize);
	}

	void TestApp::CreateVertexBuffer()
	{
		MyVertex vertices[] =
		{
			{ XMFLOAT3(-1.0f,  1.0f, -1.0f),      XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
			{ XMFLOAT3(1.0f,  1.0f, -1.0f),       XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
			{ XMFLOAT3(1.0f,  1.0f,  1.0f),       XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f) },
			{ XMFLOAT3(-1.0f,  1.0f,  1.0f),      XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
			{ XMFLOAT3(-1.0f, -1.0f, -1.0f),     XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f) },
			{ XMFLOAT3(1.0f, -1.0f, -1.0f),     XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f) },
			{ XMFLOAT3(1.0f, -1.0f,  1.0f),      XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
			{ XMFLOAT3(-1.0f, -1.0f,  1.0f),      XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) },

		};
		DirectXApp::CreateVertexBuffer(vertices, sizeof(vertices));
	}

	void TestApp::CreateIndexBuffer()
	{
		UINT indices[] =
		{
			3, 1, 0,
			2, 1, 3,
			0, 5, 4,
			1, 5, 0,
			3, 4, 7,
			0, 4, 3,
			1, 6, 5,
			2, 6, 1,
			2, 7, 6,
			3, 7, 2,
			6, 4, 5,
			7, 4, 6,
		};
		DirectXApp::CreateIndexBuffer(indices, sizeof(indices));
	}

	void TestApp::InitMatrix()
	{
		DirectXApp::CreateConstantBuffer();
		m_World = XMMatrixIdentity();

		XMVECTOR pos = XMVectorSet(0.0f, 0.0f, -8.0f, 1.0f);
		XMVECTOR target = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
		XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
		m_View = XMMatrixLookAtLH(pos, target, up);

		// PPT 4장 공간 변환 47 페이지.
		m_Projection = XMMatrixPerspectiveFovLH(
			XM_PIDIV2, 800.f / (FLOAT)600.f, 0.3f, 1000.0f);

	}

	void TestApp::CalculateMatrixForBox(float deltaTime)
	{
		XMMATRIX mat = XMMatrixRotationY(deltaTime);
		mat *= XMMatrixRotationX(-deltaTime);
		m_World = mat;

		XMMATRIX wvp = m_World * m_View * m_Projection;
		ConstantBuffer cb;
		cb.wvp = XMMatrixTranspose(wvp);

		m_pImmediateContext->UpdateSubresource(m_pConstantBuffer, 0, 0, &cb, 0, 0);
		m_pImmediateContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	}
}
