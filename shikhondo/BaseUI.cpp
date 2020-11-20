#include "BaseUI.h"

HRESULT BaseUI::Init()
{
	return E_NOTIMPL;
}

void BaseUI::Release()
{
}

void BaseUI::Update()
{
}

void BaseUI::Render(HDC hdc)
{
	GameNode::Render(hdc);
}
