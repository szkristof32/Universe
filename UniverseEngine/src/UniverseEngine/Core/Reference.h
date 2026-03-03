#pragma once

#include <memory>

namespace UniverseEngine {

	template<typename _Ty>
	class Reference
	{
	public:
		Reference() = default;
		Reference(_Ty* ptr) : m_Ptr(ptr) {}
		Reference(const Reference& other) : m_Ptr(other.m_Ptr) {}
		Reference(Reference&& other) : m_Ptr(other.m_Ptr) {}
		Reference(const std::unique_ptr<_Ty>& other) : m_Ptr(other.get()) {}
		Reference(const std::shared_ptr<_Ty>& other) : m_Ptr(other.get()) {}

		Reference& operator=(_Ty* ptr) { m_Ptr = ptr; return *this; }
		Reference& operator=(const Reference& other) { m_Ptr = other.m_Ptr; return *this; }
		Reference& operator=(Reference&& other) { m_Ptr = other.m_Ptr; return *this; }
		Reference& operator=(const std::unique_ptr<_Ty>& other) { m_Ptr = other.get(); return *this; }
		Reference& operator=(const std::shared_ptr<_Ty>& other) { m_Ptr = other.get(); return *this; }

		template<typename _T2>
		inline Reference<_T2> As() { return Reference<_T2>(static_cast<_T2*>(m_Ptr)); }

		_Ty* Get() const { return m_Ptr; }
		_Ty* operator->() const { return Get(); }
		_Ty& operator*() { return *Get(); }
		const _Ty& operator*() const { return *Get(); }
	private:
		_Ty* m_Ptr = nullptr;
	};

}
