#pragma once

#include <glm/glm.hpp>
#include <glm/ext/scalar_constants.hpp>

namespace UniverseEngine {

	template<typename _Ty>
	class SmoothValue
	{
	public:
		SmoothValue() = default;
		SmoothValue(_Ty initialValue, float agility = 1.0f)
			: m_Target(initialValue), m_Actual(initialValue), m_Agility(agility)
		{
		}

		void Update(float delta)
		{
			_Ty offset = m_Target - m_Actual;
			_Ty change = offset * delta * m_Agility;
			m_Actual += change;
		}

		void Force(const _Ty& value) { m_Target = value; m_Actual = value; }

		void IncreaseTarget(const _Ty& delta) { m_Target += delta; }
		void SetTarget(const _Ty& target) { m_Target = target; }
		const _Ty& GetTarget() const { return m_Target; }

		float& GetAgility() { return m_Agility; }
		void SetAgility(float agility) { m_Agility = agility; }

		_Ty& Get() { return m_Actual; }
		const _Ty& Get() const { return m_Actual; }

		inline operator _Ty() { return Get(); }
		inline operator const _Ty() const { return Get(); }

		inline _Ty& operator->() { return Get(); }
		inline const _Ty& operator->() const { return Get(); }
	private:
		_Ty m_Target = _Ty();
		_Ty m_Actual = _Ty();

		float m_Agility = 1.0f;
	};

}
