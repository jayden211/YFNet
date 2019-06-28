//
// AutoPtr.h
//
// $Id: //poco/1.3/Foundation/include/Poco/AutoPtr.h#2 $
//
// Library: Foundation
// Package: Core
// Module:  AutoPtr
//
// Definition of the AutoPtr template class.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#ifndef Foundation_AutoPtr_INCLUDED
#define Foundation_AutoPtr_INCLUDED



#include <algorithm>


template <class C>
class AutoPtr
{
public:
	AutoPtr(): _ptr(NULL)
	{
	}
	
	AutoPtr(C* ptr): _ptr(ptr)
	{
	}
	
	AutoPtr(C* ptr, bool shared): _ptr(ptr)
	{
		if (shared && _ptr) _ptr->duplicate();
	}
	
	AutoPtr(const AutoPtr& ptr): _ptr(ptr._ptr)
	{
		if (_ptr) _ptr->duplicate();
	}
	
	// 	template <class Other> 
	// 	AutoPtr(const AutoPtr<Other>& ptr): _ptr(const_cast<Other*>(ptr.get()))
	// 	{
	// 		if (_ptr) _ptr->duplicate();
	// 	}
	
	~AutoPtr()
	{
		if (_ptr) _ptr->release();
	}
	
	AutoPtr& assign(C* ptr)
	{
		if (_ptr != ptr)
		{
			if (_ptr) _ptr->release();
			_ptr = ptr;
		}
		return *this;
	}
	
	AutoPtr& assign(C* ptr, bool shared)
	{
		if (_ptr != ptr)
		{
			if (_ptr) _ptr->release();
			_ptr = ptr;
			if (shared && _ptr) _ptr->duplicate();
		}
		return *this;
	}
	
	AutoPtr& assign(const AutoPtr& ptr)
	{
		if (&ptr != this)
		{
			if (_ptr) _ptr->release();
			_ptr = ptr._ptr;
			if (_ptr) _ptr->duplicate();
		}
		return *this;
	}
	
	// 	template <class Other> 
	// 	AutoPtr& assign(const AutoPtr<Other>& ptr)
	// 	{
	// 		if (ptr.get() != _ptr)
	// 		{
	// 			if (_ptr) _ptr->release();
	// 			_ptr = const_cast<Other*>(ptr.get());
	// 			if (_ptr) _ptr->duplicate();
	// 		}
	// 		return *this;
	// 	}
	
	AutoPtr& operator = (C* ptr)
	{
		return assign(ptr);
	}
	
	AutoPtr& operator = (const AutoPtr& ptr)
	{
		return assign(ptr);
	}
	
	// 	template <class Other> 
	// 	AutoPtr& operator = (const AutoPtr<Other>& ptr)
	// 	{
	// 		return assign<Other>(ptr);
	// 	}
	
	void swap(AutoPtr& ptr)
	{
		std::swap(_ptr, ptr._ptr);
	}
	
	template <class Other> 
		AutoPtr<Other> cast() const
		/// Casts the AutoPtr via a dynamic cast to the given type.
		/// Returns an AutoPtr containing NULL if the cast fails.
		/// Example: (assume class Sub: public Super)
		///    AutoPtr<Super> super(new Sub());
		///    AutoPtr<Sub> sub = super.cast<Sub>();
		///    poco_assert (sub.get());
	{
		Other* pOther = dynamic_cast<Other*>(_ptr);
		return AutoPtr<Other>(pOther, true);
	}
	
	template <class Other> 
		AutoPtr<Other> unsafeCast() const
		/// Casts the AutoPtr via a static cast to the given type.
		/// Example: (assume class Sub: public Super)
		///    AutoPtr<Super> super(new Sub());
		///    AutoPtr<Sub> sub = super.unsafeCast<Sub>();
		///    poco_assert (sub.get());
	{
		Other* pOther = static_cast<Other*>(_ptr);
		return AutoPtr<Other>(pOther, true);
	}
	
	C* operator -> ()
	{
		return _ptr;
	}
	
	const C* operator -> () const
	{
		return _ptr;
	}
	
	C** operator &()
	{
		return &_ptr;
	}

	C& operator * ()
	{
		return *_ptr;
	}
	
	const C& operator * () const
	{
		return *_ptr;
	}
	
	C* get()
	{
		return _ptr;
	}
	
	const C* get() const
	{
		return _ptr;
	}
	
	operator C* ()
	{
		return _ptr;
	}
	
	operator const C* () const
	{
		return _ptr;
	}
	
	bool operator ! () const
	{
		return _ptr == 0;
	}
	
	bool isNull() const
	{
		return _ptr == 0;
	}
	
	C* duplicate()
	{
		if (_ptr) _ptr->duplicate();
		return _ptr;
	}
	
	bool operator == (const AutoPtr& ptr) const
	{
		return _ptr == ptr._ptr;
	}
	
	bool operator == (const C* ptr) const
	{
		return _ptr == ptr;
	}
	
	bool operator == (C* ptr) const
	{
		return _ptr == ptr;
	}
	
	bool operator != (const AutoPtr& ptr) const
	{
		return _ptr != ptr._ptr;
	}
	
	bool operator != (const C* ptr) const
	{
		return _ptr != ptr;
	}
	
	bool operator != (C* ptr) const
	{
		return _ptr != ptr;
	}
	
	bool operator < (const AutoPtr& ptr) const
	{
		return _ptr < ptr._ptr;
	}
	
	bool operator < (const C* ptr) const
	{
		return _ptr < ptr;
	}
	
	bool operator < (C* ptr) const
	{
		return _ptr < ptr;
	}
	
	bool operator <= (const AutoPtr& ptr) const
	{
		return _ptr <= ptr._ptr;
	}
	
	bool operator <= (const C* ptr) const
	{
		return _ptr <= ptr;
	}
	
	bool operator <= (C* ptr) const
	{
		return _ptr <= ptr;
	}
	
	bool operator > (const AutoPtr& ptr) const
	{
		return _ptr > ptr._ptr;
	}
	
	bool operator > (const C* ptr) const
	{
		return _ptr > ptr;
	}
	
	bool operator > (C* ptr) const
	{
		return _ptr > ptr;
	}
	
	bool operator >= (const AutoPtr& ptr) const
	{
		return _ptr >= ptr._ptr;
	}
	
	bool operator >= (const C* ptr) const
	{
		return _ptr >= ptr;
	}
	
	bool operator >= (C* ptr) const
	{
		return _ptr >= ptr;
	}
	
private:
	C* _ptr;
};


template <class C>
inline void swap(AutoPtr<C>& p1, AutoPtr<C>& p2)
{
	p1.swap(p2);
}

#endif 
