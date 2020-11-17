#pragma once
#include "GameNode.h"
class Scene : public GameNode
{
public:
	HRESULT Init() { return S_OK; }
	void Release() { GameNode::Release(); }
};

