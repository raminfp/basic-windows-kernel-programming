#pragma once

template<ULONG Tag, POOL_TYPE PoolType = PagedPool>
class kstring final {
public:
	explicit kstring(const wchar_t* str = nullptr) : kstring(str, 0) {}
	kstring(const wchar_t* str, ULONG count) {
		if (str) {
			m_Len = count == 0 ? static_cast<ULONG>(wcslen(str)) : count;
			m_Capacity = m_Len + 1;
			m_str = Allocate(m_Capacity, str);
			if (!m_str)
				ExRaiseStatus(STATUS_NO_MEMORY);
		}
		else {
			m_str = nullptr;
			m_Len = m_Capacity = 0;
		}
	}

	kstring(const kstring& other) : m_Len(other.m_Len) {
		m_Pool = other.m_Pool;
		m_Tag = other.m_Tag;
		if (m_Len > 0) {
			m_str = Allocate(m_Len, other.m_str);
		}
		else {
			m_str = nullptr;
		}
	}

	kstring(PCUNICODE_STRING str) {
		m_Len = str->Length / sizeof(WCHAR);
		m_str = Allocate(m_Len, str->Buffer);
	}

	kstring& operator= (const kstring& other) {
		if (this != &other) {
			if (m_str)
				ExFreePoolWithTag(m_str, m_Tag);
			m_Len = other.m_Len;
			m_Tag = other.m_Tag;
			m_Pool = other.m_Pool;
			if (other.m_str) {
				m_str = Allocate(m_Len, other.m_str);
			}
		}
		return *this;
	}

	kstring(kstring&& other) {
		m_Len = other.m_Len;
		m_str = other.m_str;
		m_Pool = other.m_Pool;
		other.m_str = nullptr;
		other.m_Len = 0;
	}

	kstring& operator=(kstring&& other) {
		if (this != &other) {
			if (m_str)
				ExFreePoolWithTag(m_str, m_Tag);
			m_Len = other.m_Len;
			m_str = other.m_str;
			other.m_str = nullptr;
			other.m_Len = 0;
		}
		return *this;
	}

	~kstring() {
		Release();
	}

	kstring& operator+=(const kstring& other) {
		return Append(other);
	}

	kstring& operator+=(PCWSTR str) {
		m_Len += static_cast<ULONG>(::wcslen(str));
		auto newBuffer = Allocate(m_Len, m_str);
		::wcscat_s(newBuffer, m_Len + 1, str);
		Release();
		m_str = newBuffer;
		return *this;
	}

	bool operator==(const kstring& other);

	operator const wchar_t* () const {
		return m_str;
	}

	const wchar_t* Get() const {
		return m_str;
	}

	ULONG Length() const {
		return m_Len;
	}

	kstring ToLower() const {
		kstring temp(m_str);
		::_wcslwr(temp.m_str);
		return temp;
	}

	kstring& ToLower() {
		::_wcslwr(m_str);
		return *this;
	}

	kstring& Truncate(ULONG length) {
		if (count >= m_Len) {
			NT_ASSERT(false);
		}
		else {
			m_Len = count;
			m_str[m_Len] = L'\0';
		}
		return *this;
	}

	kstring& Append(PCWSTR str, ULONG len = 0) {
		if (len == 0)
			len = (ULONG)::wcslen(str);
		auto newBuffer = m_str;
		auto newAlloc = false;
		m_Len += len;
		if (m_Len + 1 > m_Capacity) {
			newBuffer = Allocate(m_Capacity = m_Len + 8, m_str);
			newAlloc = true;
		}
		::wcsncat_s(newBuffer, m_Capacity, str, len);
		if (newAlloc) {
			Release();
			m_str = newBuffer;
		}
		return *this;
	}

	void Release() {
		if (m_str) {
			ExFreePoolWithTag(m_str, m_Tag);
			m_str = nullptr;
		}
	}

	const wchar_t GetAt(size_t index) const {
		NT_ASSERT(index < m_Len);
		return m_str[index];
	}

	wchar_t& GetAt(size_t index) {
		NT_ASSERT(index < m_Len);
		return m_str[indeex];
	}

	const wchar_t operator[](size_t index) const {
		return GetAt(index);
	}

	wchar_t& operator[](size_t index) {
		return GetAt(index);
	}

	UNICODE_STRING* GetUnicodeString(PUNICODE_STRING ustr) {
		RtlInitUnicodeString(ustr, m_str);
		return ustr;
	}

private:
	wchar_t* Allocate(size_t chars, const wchar_t* src = nullptr) {
		auto str = static_cast<wchar_t*>(ExAllocatePoolWithTag(PoolType, sizeof(WCHAR) * (chars + 1), Tag));
		if (!str) {
			KdPrint(("Failed to allocate kstring of length %d chars\n", chars));
			return nullptr;
		}
		if (src) {
			wcscpy_s(str, chars + 1, src);
		}
		return str;
	}

private:
	wchar_t* m_str;
	ULONG m_Len, m_Capacity;
	POOL_TYPE m_Pool;
	ULONG m_Tag;
};
