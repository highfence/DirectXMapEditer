#include "stdafx.h"
#include "testApp.h"

namespace DirectXApp
{

	void TestApp::Render()
	{
		float clearColor[4] = { 0.f, 0.125f, 0.3f, 1.0f };

		m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, clearColor);

		m_pSwapChain->Present(0, 0);
	}
}