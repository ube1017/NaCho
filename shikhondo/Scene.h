#pragma once
#include "GameNode.h"
class Scene : public GameNode
{
public:
	Scene() : isShake(false), shackeMoveX(0), shackeMoveY(0), revision(0){}
	HRESULT Init() { return S_OK; }
	void Release() { GameNode::Release(); }

	void SetIsShake(bool value) { this->isShake = value; }
	bool GetIsShake() { return this->isShake; }

	void SetSideShake(int strength = 1,float time = 0 , bool isRight = true);
	// 강도 보정 시간
	void SetAllShaek(int strength = 1, int revision = -1,float time = 0);

	int GetShackeMoveX() const { return this->shackeMoveX; }
	int GetShackeMoveY() const { return this->shackeMoveY; }

	int GetRandomShackeMove() const { return rand() % (this->strength * 2) - 1; }

	int GetRevision() { return this->revision; }
	
private:
	void OffShake();
protected:
	bool isShake;
	TimerHandle ShakeingTimer;
	int strength;
	int revision;
	int shackeMoveX;
	int shackeMoveY;
};

