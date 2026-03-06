#pragma once

#include <cstddef>
#include <cstring>
#include <string>

namespace UniverseEngine {

	class StringView
	{
	public:
		class Iterator : public std::iterator<std::input_iterator_tag, const char, ptrdiff_t, const char*, const char&>
		{
		public:
			const char& operator*() const { return *m_String; }
			const char* operator->() const { return m_String; }
			Iterator& operator++() { m_String++; return *this; }
			Iterator operator++(int amount) { return Iterator(m_String + amount, m_EndPtr); }
			bool equal(const Iterator& other) const { return m_String == other.m_String && m_EndPtr == other.m_EndPtr; }
			bool operator==(const Iterator& other) const { return equal(other); }
		private:
			Iterator() = default;
			Iterator(const char* string, const char* endptr) : m_String(string), m_EndPtr(endptr) {}
		private:
			const char* m_String = nullptr;
			const char* m_EndPtr = nullptr;

			friend class StringView;
		};
	public:
		StringView() = default;
		StringView(const char* string) : m_String(string), m_Length(strlen(m_String)) {}
		StringView(const std::string& string) : m_String(string.data()), m_Length(string.length()) {}
		StringView(const StringView& other) : m_String(other.m_String), m_Length(other.m_Length) {}
		StringView(StringView&& other) : m_String(other.m_String), m_Length(other.m_Length) {}

		StringView& operator=(const StringView& other)
		{
			m_String = other.m_String;
			m_Length = other.m_Length;
			return *this;
		}
		StringView& operator=(StringView&& other)
		{
			m_String = other.m_String;
			m_Length = other.m_Length;
			return *this;
		}
		StringView& operator=(const char* string)
		{
			m_String = string;
			m_Length = strlen(m_String);
			return *this;
		}
		StringView& operator=(const std::string& string)
		{
			m_String = string.data();
			m_Length = string.size();
		}

		const char* Data() const { return m_String; }
		size_t Size() const { return m_Length; }

		operator std::string() const
		{
			return std::string(m_String, m_Length);
		}

		operator bool() const { return m_String != nullptr && m_Length > 0; }
		bool operator==(const StringView& other) const { return strcmp(m_String, other.m_String) == 0; }
		bool operator!=(const StringView& other) const { return !(*this == other); }

		template<typename _Os>
		_Os& operator<<(_Os& ostream) const
		{
			ostream << m_String;
			return ostream;
		}

		Iterator begin() { return Iterator(m_String, m_String + m_Length); }
		Iterator end() { return Iterator(m_String + m_Length, m_String + m_Length); }
		const Iterator cbegin() const { return Iterator(m_String, m_String + m_Length); }
		const Iterator cend() const { return Iterator(m_String + m_Length, m_String + m_Length); }
	private:
		const char* m_String = nullptr;
		size_t m_Length = 0;
	};

	inline StringView operator""sv(const char* string) { return StringView(string); }

}

namespace std {

	template<>
	struct hash<UniverseEngine::StringView>
	{
		size_t operator()(const UniverseEngine::StringView& stringView) const
		{
			return hash<const char*>{}(stringView.Data());
		}
	};

}
