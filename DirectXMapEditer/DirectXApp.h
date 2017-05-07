#pragma once
#include <Windows.h>

class DirectXApp
{
public :
	DirectXApp() = default;
	virtual ~DirectXApp() = default;

private :
	HWND m_hWnd = nullptr;
	

};