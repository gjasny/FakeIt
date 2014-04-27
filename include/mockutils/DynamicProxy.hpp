/*
 * Copyright (c) 2014 Eran Pe'er.
 *
 * This program is made available under the terms of the MIT License.
 *
 * Created on Mar 10, 2014
 */

#ifndef DynamicProxy_h__
#define DynamicProxy_h__

#include <functional>
#include <type_traits>
#include <vector>
#include <array>
#include <new>

#ifdef _WIN32
#include "mockutils/mscpp/VirtualTable.hpp"
#else
#include "mockutils/gcc/VirtualTable.hpp"
#endif

#include "mockutils/MethodProxy.hpp"
#include "mockutils/VirtualOffestSelector.hpp"
#include "mockutils/union_cast.hpp"
#include "mockutils/MethodInvocationHandler.hpp"

namespace fakeit {

static VirtualOffsetSelector offsetSelctor;

template<typename C, typename ... baseclasses>
struct DynamicProxy {
	static_assert(std::is_polymorphic<C>::value, "DynamicProxy requires a polymorphic type");

	DynamicProxy(std::function<void()> unmockedMethodCallHandler) :
			vtable(), methodMocks(), unmockedMethodCallHandler { unmockedMethodCallHandler } {
		initVirtualTable<C>(&vtable);
		initializeDataMembersArea();
	}

	~DynamicProxy() {
	}

	C& get() {
		return reinterpret_cast<C&>(*this);
	}

	void Reset() {
		methodMocks = {};
		members = {};
		initVirtualTable<C>(&vtable);
		initializeDataMembersArea();
	}

	template<typename R, typename ... arglist>
	void stubMethod(R (C::*vMethod)(arglist...), std::shared_ptr<MethodInvocationHandler<R, arglist...>> methodInvocationHandler) {
		std::shared_ptr<MethodProxy<R, arglist...>> methodProxy = MethodProxyCreator<R, arglist...>::createMethodProxy(vMethod);
		bind(methodProxy, methodInvocationHandler);
	}

	template<typename R, typename ... arglist>
	bool isStubbed(R (C::*vMethod)(arglist...)) {
		auto offset = MethodProxyCreator<R, arglist...>::getOffset(vMethod);
		std::shared_ptr<Destructable> ptr = methodMocks[offset];
		return ptr.get() != nullptr;
	}

	template<typename R, typename ... arglist>
	Destructable * getMethodMock(R (C::*vMethod)(arglist...)) {
		auto offset = MethodProxyCreator<R, arglist...>::getOffset(vMethod);
		std::shared_ptr<Destructable> ptr = methodMocks[offset];
		return ptr.get();
	}

	template<typename DATA_TYPE, typename ... arglist>
	void stubDataMember(DATA_TYPE C::*member, const arglist&... initargs) {
		DATA_TYPE C::*theMember = (DATA_TYPE C::*) member;
		C& mock = get();
		DATA_TYPE *memberPtr = &(mock.*theMember);
		members.push_back(
				std::shared_ptr<DataMemeberWrapper<DATA_TYPE, arglist...>> { new DataMemeberWrapper<DATA_TYPE, arglist...>(memberPtr,
						initargs...) });
	}

	template<typename DATA_TYPE>
	void getMethodMocks(std::vector<DATA_TYPE>& into) const {
		for (std::shared_ptr<Destructable> ptr : methodMocks) {
			DATA_TYPE p = dynamic_cast<DATA_TYPE>(ptr.get());
			if (p)
				into.push_back(p);
		}
	}

private:

	template<typename R, typename ... arglist>
	class MethodProxyCreator {
	private:

		template<unsigned int OFFSET>
		struct VirtualMethodProxy: public MethodProxy<R, arglist...> {
			unsigned int getOffset() override {
				return OFFSET;
			}

			void * getProxy() override {
				return union_cast<void *>(&VirtualMethodProxy::methodProxy);
			}

		private:
			R methodProxy(arglist ... args) {
				DynamicProxy<C, baseclasses...> * dynamicProxy = union_cast<DynamicProxy<C, baseclasses...> *>(this);
				MethodInvocationHandler<R, arglist...> * methodMock = dynamicProxy->getMethodMock<MethodInvocationHandler<R, arglist...> *>(
						OFFSET);
				return methodMock->handleMethodInvocation(args...);
			}
		};

	public:

		static MethodProxy<R,arglist...>* createMethodProxy(unsigned int offset){
			MethodProxy<R,arglist...>* proxy = nullptr;
			switch (offset){
			case 0:
				proxy = new VirtualMethodProxy<0>();
				break;
			case 1:
				proxy = new VirtualMethodProxy<1>();
				break;
			case 2:
				proxy = new VirtualMethodProxy<2>();
				break;
			case 3:
				proxy = new VirtualMethodProxy<3>();
				break;
			case 4:
				proxy = new VirtualMethodProxy<4>();
				break;
			case 5:
				proxy = new VirtualMethodProxy<5>();
				break;
			case 6:
				proxy = new VirtualMethodProxy<6>();
				break;
			case 7:
				proxy = new VirtualMethodProxy<7>();
				break;
			case 8:
				proxy = new VirtualMethodProxy<8>();
				break;
			case 9:
				proxy = new VirtualMethodProxy<9>();
				break;
			case 10:
				proxy = new VirtualMethodProxy<10>();
				break;
			case 11:
				proxy = new VirtualMethodProxy<11>();
				break;
			case 12:
				proxy = new VirtualMethodProxy<12>();
				break;
			case 13:
				proxy = new VirtualMethodProxy<13>();
				break;
			case 14:
				proxy = new VirtualMethodProxy<14>();
				break;
			case 15:
				proxy = new VirtualMethodProxy<15>();
				break;
			case 16:
				proxy = new VirtualMethodProxy<16>();
				break;
			case 17:
				proxy = new VirtualMethodProxy<17>();
				break;
			case 18:
				proxy = new VirtualMethodProxy<18>();
				break;
			case 19:
				proxy = new VirtualMethodProxy<19>();
				break;
			case 20:
				proxy = new VirtualMethodProxy<20>();
				break;
			case 21:
				proxy = new VirtualMethodProxy<21>();
				break;
			case 22:
				proxy = new VirtualMethodProxy<22>();
				break;
			case 23:
				proxy = new VirtualMethodProxy<23>();
				break;
			case 24:
				proxy = new VirtualMethodProxy<24>();
				break;
			case 25:
				proxy = new VirtualMethodProxy<25>();
				break;
			case 26:
				proxy = new VirtualMethodProxy<26>();
				break;
			case 27:
				proxy = new VirtualMethodProxy<27>();
				break;
			case 28:
				proxy = new VirtualMethodProxy<28>();
				break;
			case 29:
				proxy = new VirtualMethodProxy<29>();
				break;
			case 30:
				proxy = new VirtualMethodProxy<30>();
				break;
			case 31:
				proxy = new VirtualMethodProxy<31>();
				break;
			case 32:
				proxy = new VirtualMethodProxy<32>();
				break;
			case 33:
				proxy = new VirtualMethodProxy<33>();
				break;
			case 34:
				proxy = new VirtualMethodProxy<34>();
				break;
			case 35:
				proxy = new VirtualMethodProxy<35>();
				break;
			case 36:
				proxy = new VirtualMethodProxy<36>();
				break;
			case 37:
				proxy = new VirtualMethodProxy<37>();
				break;
			case 38:
				proxy = new VirtualMethodProxy<38>();
				break;
			case 39:
				proxy = new VirtualMethodProxy<39>();
				break;
			case 40:
				proxy = new VirtualMethodProxy<40>();
				break;
			case 41:
				proxy = new VirtualMethodProxy<41>();
				break;
			case 42:
				proxy = new VirtualMethodProxy<42>();
				break;
			case 43:
				proxy = new VirtualMethodProxy<43>();
				break;
			case 44:
				proxy = new VirtualMethodProxy<44>();
				break;
			case 45:
				proxy = new VirtualMethodProxy<45>();
				break;
			case 46:
				proxy = new VirtualMethodProxy<46>();
				break;
			case 47:
				proxy = new VirtualMethodProxy<47>();
				break;
			case 48:
				proxy = new VirtualMethodProxy<48>();
				break;
			case 49:
				proxy = new VirtualMethodProxy<49>();
				break;
			}
			return proxy;
		}

		static std::shared_ptr<MethodProxy<R, arglist...>> createMethodProxy(R (C::*vMethod)(arglist...)) {
			auto offset = getOffset(vMethod);
			MethodProxy<R, arglist...>* rv = createMethodProxy(offset);
			return std::shared_ptr<MethodProxy<R, arglist...>> { rv};
		}

		static unsigned int getOffset(R (C::*vMethod)(arglist...)) {
			auto sMethod = reinterpret_cast<unsigned int (VirtualOffsetSelector::*)()>(vMethod);
			auto selectMethod = std::bind(sMethod, &offsetSelctor);
			unsigned int offset = (unsigned int)selectMethod();
			return offset;
		}

	};

	template<typename DATA_TYPE, typename ... arglist>
	class DataMemeberWrapper: public Destructable {
	private:
		DATA_TYPE *dataMember;
	public:
		DataMemeberWrapper(DATA_TYPE *dataMember, const arglist&... initargs) :
				dataMember(dataMember) {
			new (dataMember) DATA_TYPE { initargs ... };
		}
		~DataMemeberWrapper() {
			dataMember->~DATA_TYPE();
		}
	};

	VirtualTable<50, C, baseclasses...> vtable;

	// Here we alloc too many bytes since sizeof(C) includes the pointer to the virtual table.
	// Should be sizeof(C) - ptr_size.
	// No harm is done if we alloc more space for data but don't use it.
	char instanceArea[sizeof(C)];

	std::array<std::shared_ptr<Destructable>, 50> methodMocks;
	std::vector<std::shared_ptr<Destructable>> members;
	std::function<void()> unmockedMethodCallHandler;

	void unmocked() {
		//DynamicProxy * m = this; // this should work
		unmockedMethodCallHandler();
	}

	template<typename R, typename ... arglist>
	static R defualtFunc(arglist...) {
		return R { };
	}

	template<typename ... arglist>
	static void defualtProc(arglist...) {
	}

	template<typename R, typename ... arglist>
	void bind(std::shared_ptr<MethodProxy<R, arglist...>> methodProxy,
			std::shared_ptr<MethodInvocationHandler<R, arglist...>> invocationHandler) {
		auto offset = methodProxy->getOffset();
		vtable.setMethod(offset, methodProxy->getProxy());
		methodMocks[offset] = invocationHandler;
	}

	void initializeDataMembersArea() {
		for (int i = 0; i < sizeof(instanceArea); i++)
			instanceArea[i] = (char) 0;
	}

	template<typename DATA_TYPE>
	DATA_TYPE getMethodMock(unsigned int offset) {
		std::shared_ptr<Destructable> ptr = methodMocks[offset];
		return dynamic_cast<DATA_TYPE>(ptr.get());
	}

	template<typename T>
	void initVirtualTable(VirtualTable<50, T, baseclasses...>* vtable) {
		auto mptr = union_cast<void*>(&DynamicProxy::unmocked);
		for (unsigned int i = 0; i < vtable->getSize(); i++) {
			vtable->setMethod(i, mptr);
		}
	}

//	template <typename T, typename... baseclasses>
//	void addVirtualTable(int delta)
//	{
//		auto virtTablePtr = (char *)&get() + delta;
//		VirtualTable<50, T>* baseVirtualTable = new VirtualTable<50, T, baseclasses...>();
//		initVirtualTable(*baseVirtualTable);
//		VirtualTable<50, T>* virtualTablePtrInObjectData = (VirtualTable<50, T, baseclasses...>*)virtTablePtr;
//		*virtualTablePtrInObjectData = *baseVirtualTable;
//	}

	template<typename BaseClass>
	void checkMultipleInheritance() {
		C* ptr = (C*) (unsigned int) 1;
		BaseClass* basePtr = ptr;
		int delta = (unsigned long) basePtr - (unsigned long) ptr;
		if (delta > 0) {
			// base class does not start on same position as derived class.
			// this is multiple inheritance.
			// need to create a new virtual table for base class.
			// addVirtualTable<BaseClass>(delta);
			throw std::invalid_argument(std::string("multiple inheritance is not supported"));
		}
	}
};
}
#endif // DynamicProxy_h__