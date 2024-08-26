#ifndef REF_COUNT_PTR_H
#define REF_COUNT_PTR_H

template<class T>
class RefCountPtr
{
public:
	RefCountPtr() noexcept = default;
	RefCountPtr(T* ptr) noexcept;
	RefCountPtr(const RefCountPtr&) noexcept;
	RefCountPtr(RefCountPtr&&) noexcept;      // TODO - swap ptrs

	~RefCountPtr();

	T* Get() const;
	T** GetAddressOf() const;
	T** ReleaseAndGetAddressOf();

	unsigned long Reset();
	void Swap(RefCountPtr& other);

	template<typename U>
	void As(RefCountPtr<U>& other) const;

	T* operator->() const;
	T** operator&();
	bool operator!() const;

	RefCountPtr& operator=(const RefCountPtr&) noexcept;

private:
	void InternalAddRef() const;
	void InternalRelease();

	T* m_ptr{ nullptr };
};

/*
Initializes the smart pointer with the provided raw pointer 'ptr' and increments the pointer's reference count.
*/
template<class T>
inline RefCountPtr<T>::RefCountPtr(T* ptr) noexcept
	: m_ptr{ ptr }
{
	InternalAddRef();
}

template<class T>
inline RefCountPtr<T>::RefCountPtr(const RefCountPtr<T>& other) noexcept
	: m_ptr{ other.m_ptr }
{
	InternalAddRef();
}

template<class T>
inline RefCountPtr<T>::RefCountPtr(RefCountPtr&& refCountPtr) noexcept
{
	//Swap(refCountPtr);
}

template<class T>
inline RefCountPtr<T>::~RefCountPtr()
{
	InternalRelease();
}

template<class T>
inline T* RefCountPtr<T>::Get() const
{
	return m_ptr;
}

template<class T>
inline T** RefCountPtr<T>::GetAddressOf() const
{
	return &m_ptr;
}

template<class T>
inline T** RefCountPtr<T>::ReleaseAndGetAddressOf()
{
	InternalRelease();
	return &m_ptr;
}

template<class T>
inline unsigned long RefCountPtr<T>::Reset()
{
	return InternalRelease();
}

template<class T>
inline void RefCountPtr<T>::Swap(RefCountPtr& other)
{
	T* tmp = other.m_ptr;
	other.m_ptr = m_ptr;
	m_ptr = tmp;
}

template<class T>
template<typename U>
inline void RefCountPtr<T>::As(RefCountPtr<U>& other) const
{
	m_ptr->QueryInterface(__uuidof(U), reinterpret_cast<void**>(other.ReleaseAndGetAddressOf()));
}

template<class T>
inline T* RefCountPtr<T>::operator->() const
{
	return m_ptr;
}

template<class T>
inline T** RefCountPtr<T>::operator&()
{
	return ReleaseAndGetAddressOf();
}

template<class T>
inline bool RefCountPtr<T>::operator!() const
{
	return !m_ptr;
}

template<class T>
inline RefCountPtr<T>& RefCountPtr<T>::operator=(const RefCountPtr& rhs) noexcept
{
	m_ptr = rhs.m_ptr;
	InternalAddRef();

	return *this;
}

template<class T>
inline void RefCountPtr<T>::InternalAddRef() const
{
	if (m_ptr != nullptr)
	{
		m_ptr->AddRef();
	}
}

template<class T>
inline void RefCountPtr<T>::InternalRelease()
{
	// For testing only.
	unsigned long refCount = 0;

	if (m_ptr != nullptr)
	{
		refCount = m_ptr->Release();
		m_ptr = nullptr;
	}
}

#endif // !REF_COUNT_PTR_H
