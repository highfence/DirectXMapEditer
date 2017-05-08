#pragma once
#include <xnamath.h>

struct MyVertex
{
	XMFLOAT3 pos;
	XMFLOAT4 color;
};

struct ConstantBuffer
{
	XMMATRIX wvp;
};
