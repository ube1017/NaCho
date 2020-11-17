#pragma once

#define _INTERFACE struct

template <bool Const, typename Class, typename FuncType>
struct TMemFunPtrType;

template <typename Class, typename RetType, typename... ArgTypes>
struct TMemFunPtrType<false, Class, RetType(ArgTypes...)>
{
	// �Լ� ������ ������
	typedef RetType(Class::* Type)(ArgTypes...);
};

template <typename Class, typename RetType, typename... ArgTypes>
struct TMemFunPtrType<true, Class, RetType(ArgTypes...)>
{
	// �Լ� ������ ������
	typedef RetType(Class::* Type)(ArgTypes...) const;
};

template <typename RetType, typename... ParamTypes>
_INTERFACE IDelegate
{
	virtual RetType Execute(ParamTypes... param) = 0;
	virtual void UnBind() = 0;
};

template <typename RetType, typename... ParamTypes>
class Delegate
{
	template<typename UserClass >
	struct TDelegate : public IDelegate<RetType, ParamTypes...>
	{
		typedef typename TMemFunPtrType<false, UserClass, RetType(ParamTypes...)>::Type MethodPtr;


		IDelegate<RetType, ParamTypes...>* Bind(UserClass* object, MethodPtr methodPtr)
		{
			this->object = object;
			this->methodPtr = methodPtr;
			return this;
		}

		void UnBind() override
		{
			methodPtr = nullptr;
			object = nullptr;
		}

		RetType Execute(ParamTypes... param) override
		{
			if (methodPtr)
				return (object->*methodPtr)(param...);
		}

		MethodPtr methodPtr;
		UserClass* object;
	};

public:
	Delegate() : Tdelegate(nullptr) {}
	~Delegate()
	{
		if (Tdelegate != nullptr)
		{
			this->UnBind();
			delete Tdelegate;
		}
	}

	template <typename UserClass>
	inline void BindObject(UserClass* InUserObject, typename TMemFunPtrType<false, UserClass, RetType(ParamTypes...)>::Type InFunc)
	{
		if (Tdelegate == nullptr)
		{
			TDelegate<UserClass>* delegate = new TDelegate<UserClass>;
			Tdelegate = delegate->Bind(InUserObject, InFunc);
		}
		else
		{
			TDelegate<UserClass>* delegate = dynamic_cast<TDelegate<UserClass>*>(Tdelegate);
			Tdelegate = delegate->Bind(InUserObject, InFunc);
		}
	}

	void UnBind()
	{
		if (Tdelegate)
		{
			Tdelegate->UnBind();
		}
	}

	RetType Execute(ParamTypes... param) 
	{
		if (Tdelegate)
			return Tdelegate->Execute(param...);
		return RetType();
	}

private:
	IDelegate<RetType,ParamTypes...>* Tdelegate;
};

// �⺻
#define DELEGATE_BODY(delegateName,...) typedef Delegate<__VA_ARGS__> delegateName

#define DELEGATE(delegateName) DELEGATE_BODY(delegateName,void)
#define DELEGATE_OneParam(delegateName, paramType ) DELEGATE_BODY(delegateName, void , paramType)
#define DELEGATE_TwoParam(delegateName, paramType1, paramType2 ) DELEGATE_BODY(delegateName, void , paramType1 , paramType2)

#define DELEGATE_RetVal(retval,delegateName) DELEGATE_BODY(delegateName,retval)