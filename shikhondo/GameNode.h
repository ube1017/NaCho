#pragma once
#include "pch.h"

/*
	������ ������� ������ ���� �⺻���� ������ �Ǵ� Ŭ����

*/
class GameNode
{
protected:
	typedef list<GameNode*> GameNodeList;
	typedef list<GameNode*>::iterator GameNodeListiterator;
public:
	GameNode();
	virtual ~GameNode();

	//  ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	virtual HRESULT Init();
	// �޸� ����
	virtual void Release();
	// ������ ���� ���� ���� ���� ( ������ ����)
	virtual void Update();
	// ������ ���� ��� (�̹���, �ؽ�Ʈ)
	virtual void Render(HDC hdc);

	// ������Ʈ ����
	template<class T>
	inline T* CreateObject(bool isRender = true)
	{
		GameNode* newObject = new T;
		newObject->SetParentsObject(this);
		newObject->Init();
		if (isRender)
			object.insert(pair<ZOrder,GameNode*>(zOrder , newObject));
		newObject->UPdateListAdd(this->object_UPdateList);
		allClass.push_back(newObject);
		return Cast<T>(newObject);
	}
	inline void UPdateListAdd(list<GameNode*>& object_UPdateList) {if (!isNotUPdate) object_UPdateList.push_back(this);}
	// z ���� ����
	void SetZOrder(ZOrder z);
	// �ڽĵ��� ���� ������Ʈ ��� ����
	multimap<ZOrder, GameNode*, greater<ZOrder>>* GetRenderChilds() { return &object; };
	// �ڽĵ��� ������Ʈ ������Ʈ ��� ����
	list<GameNode*>* GetUpdateChilds() { return &object_UPdateList; }
	// ��� �ڽĵ� ���� ����
	list<GameNode*>* GetChilds() { return &allClass; }

	void SetIsValid(bool value);
	inline bool GetIsValid()					{ return isValid; }

	void SetIsRender(bool value);
private:
	void SetParentsObject(GameNode* object) { parentsObject = object; }
protected:
	// ��� �ڽ� Ŭ����
	list<GameNode*> allClass;
	// �ڽ��� ������Ʈ ����Ʈ
	list<GameNode*> object_UPdateList;
	// �ڽ��� ���� ������Ʈ ����Ʈ
	multimap<ZOrder, GameNode*, greater<ZOrder>>object;
	// �θ� ��ü
	GameNode* parentsObject;
	// z��
	ZOrder zOrder;
	// Ȱ��ȭ
	bool isValid;
	// ������Ʈ ���� ����
	bool isNotUPdate;
	//���������� ����
	bool isRender;

};

