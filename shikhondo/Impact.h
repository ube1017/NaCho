#pragma once
#include "BaseUI.h"
class Impact : public BaseUI
{
public:
	HRESULT Init()		 override;				// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	void Release()		 override;				// �޸� ����
	void Update()		 override;				// ������ ���� ���� ���� ���� (������ ����)
	void Render(HDC hdc) override;		// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)


	void SpawnImpact(string name, FPOINT pos, SIZE size, float framdelay = 0.02f);


private:
	void idle();
private:
	ImageDrawInfo impactimageinfo;
	TimerHandle idleTimer;
};

