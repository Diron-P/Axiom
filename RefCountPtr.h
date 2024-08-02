#ifndef REF_COUNT_PTR_H
#define REF_COUNT_PTR_H

template<class T>
class RefCountPtr
{
  public:
    RefCountPtr() noexcept;
    RefCountPtr(T* ptr);
    RefCountPtr(const RefCountPtr<T>&); // Copy ctor
    RefCountPtr(RefCountPtr<T>&&);      // TODO - swap ptrs

    ~RefCountPtr();

    T* Get() const;
    T** GetAddressOf();
    T** ReleaseAndGetAddressOf();
    unsigned long Reset();
    void Swap(); // TODO

    T* operator->() const;
    T** operator&();
    bool operator!() const;

  private:
    void InternalAddRef() const;
    unsigned long InternalRelease();

    T* m_ptr {nullptr};
};

template<class T>
inline RefCountPtr<T>::RefCountPtr() noexcept
{
}

/*
Initializes the smart pointer with the provided raw pointer 'ptr' and increments the pointer's reference count.
*/
template<class T>
inline RefCountPtr<T>::RefCountPtr(T* ptr) 
    : m_ptr {ptr}
{
    InternalAddRef();
}

template<class T>
inline RefCountPtr<T>::RefCountPtr(const RefCountPtr<T>& refCountPtr) 
    : m_ptr {refCountPtr.m_ptr}
{
    InternalAddRef();
}

template<class T>
inline RefCountPtr<T>::RefCountPtr(RefCountPtr<T>&&)
{
    // TODO - swap ptrs
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
inline T** RefCountPtr<T>::GetAddressOf()
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
inline void RefCountPtr<T>::Swap()
{
    // TODO
}

template<class T>
inline T* RefCountPtr<T>::operator->() const
{
    return m_ptr;
}

template<class T>
inline T** RefCountPtr<T>::operator&()
{
    InternalRelease();
    return &m_ptr;
}

template<class T>
inline bool RefCountPtr<T>::operator!() const
{
    return !m_ptr;
}

template<class T>
inline void RefCountPtr<T>::InternalAddRef() const
{
    if (m_ptr)
    {
        m_ptr->AddRef();
    }
}

template<class T>
inline unsigned long RefCountPtr<T>::InternalRelease()
{
    unsigned long test = 0;

    if (m_ptr)
    {
        test = m_ptr->Release();
        m_ptr = nullptr;
    }

    return test;
}

#endif // !REF_COUNT_PTR_H
