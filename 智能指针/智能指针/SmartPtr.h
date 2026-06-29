#pragma once
#include<iostream>
#include<mutex>
using namespace std;

namespace MyPoint
{
	//RAII + 像指针一样
	template<class T>
	class SmartPtr
	{
	public:
		SmartPtr(T* ptr)
			:_ptr(ptr)
		{
		}

		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}

		~SmartPtr()
		{
			if (_ptr)
			{
				delete _ptr;
			}
		}
	private:
		T* _ptr;
	};

	//管理权转移,早期设计缺陷,一般不允许使用,若管理权转移后,可能发生空指针访问
	template<class T>
	class auto_ptr
	{
	public:
		auto_ptr(T* ptr)
			:_ptr(ptr)
		{
		}

		auto_ptr(auto_ptr<T>& ap)
			:_ptr(ap._ptr)
		{
			ap._ptr = nullptr;
		}

		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}

		auto_ptr<T>& operator=(const auto_ptr<T>& ap)
		{
			if (this != &ap)
			{
				if (_ptr)
				{
					delete _ptr;
				}
				_ptr = ap._ptr;
				ap._ptr = nullptr;
			}
			return *this;
		}

		~auto_ptr()
		{
			delete _ptr;
		}
	private:
		T* _ptr;
	};

	//防拷贝
	template<class T>
	class unique_ptr
	{
	public:
		unique_ptr(T* ptr)
			:_ptr(ptr)
		{
		}

		unique_ptr(unique_ptr<T>& ap) = delete;
		unique_ptr<T>& operator=(unique_ptr<T>& ap) = delete;

		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}

		unique_ptr<T>& operator=(const unique_ptr<T>& ap)
		{
			if (this != &ap)
			{
				if (_ptr)
				{
					delete _ptr;
				}
				_ptr = ap._ptr;
				ap._ptr = nullptr;
			}
			return *this;
		}

		~unique_ptr()
		{
			delete _ptr;
		}
	private:
		T* _ptr;
	};

	template<class T>
	class shared_ptr
	{
	public:
		shared_ptr(T* ptr)
			:_ptr(ptr)
			,_pcount(new int(1))
			,_pmtx(new mutex)
		{
		}

		shared_ptr(const shared_ptr<T>& sp)
			:_ptr(sp._ptr)
			,_pcount(sp._pcount)
			,_pmtx(sp._pmtx)
		{
			add_ref_count();
		}

		shared_ptr(shared_ptr<T>& ap)
			:_ptr(ap._ptr)
		{
			ap._ptr = nullptr;
		}
		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}

		void release()
		{
			_pmtx->lock();
			bool falg = false;
			if (--(*_pcount) == 0 && _ptr)
			{
				delete _ptr;
				_ptr = nullptr;
				delete _pcount;
				_pcount = nullptr;
				falg = true;
			}
			_pmtx->unlock();
			if (falg)
			{
				delete _pmtx;
			}
		}

		void add_ref_count()
		{
			_pmtx->lock();
			++(*_pcount);
			_pmtx->unlock();
		}

		shared_ptr<T>& operator=(const shared_ptr<T>& ap)
		{
			if (this != &ap)
			{
				release();
				ap._ptr = _ptr;
				ap._pcount = _pcount;
				add_ref_count();
			}
			return *this;
		}

		~shared_ptr()
		{
			release();
		}
	private:
		T* _ptr;

		int* _pcount;
		mutex* _pmtx;
	};

	//weak_ptr不是智能指针,没有RAII
	//专门解决shard_ptr的循环引用问题
	template<class T>
	class weak_ptr
	{
	public:
		weak_ptr() = default;
		weak_ptr(const shared_ptr<T>& sp)
			:_ptr(sp._ptr)
		{}

		weak_ptr<T>& operator=(const shared_ptr<T>& sp)
		{
			_ptr = sp._shared_ptr;
			return *this;
		}

		T& operator*()
		{
			return *_ptr;
		}
		T* operator->()
		{
			return _ptr;
		}
	private:
		T* _ptr;
	};
}