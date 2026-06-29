#pragma once
#include<iostream>
#include<assert.h>
using namespace std;


//namespace mystring 
//{
//	class string
//	{
//	public:
//		/*string()
//			:_str(new char[1])
//		{
//			_str[0] = '\0';
//		}
//		string(const char* str)
//			:_str(new char[strlen(str)+1])
//		{
//			memcpy(_str, str,strlen(s._str) + 1);
//		}*/
//		string(const char* str = "")
//			:_str(new char[strlen(str) + 1])
//		{
//			memcpy(_str, str, strlen(s._str) + 1);
//		}
//		~string()
//		{
//			delete[] _str;
//			_str = nullptr;
//		}
//		string(const string& s)
//			:_str(new char[strlen(s._str)+1])
//		{
//			memcpy(_str, s._str, sstrlen(s._str) + 1);
//		}
//		string& operator=(const string& s)
//		{
//			if (this != &s)
//			{
//				char* tmp = new char[strlen(s._str) + 1];
//				memcpy(_str, s._str, strlen(s._str) + 1);
//				delete[]_str;
//				_str = tmp;
//			}
//			
//			return *this;
//		}
//		char& operator[](size_t i)
//		{
//			return _str[i];
//		}
//		size_t size()
//		{
//			return strlen(_str);
//		}
//		const char* c_str()
//		{
//			return _str;
//		}
//	private:
//		char* _str;
//	};
//	void test_string1()
//	{
//		string s1("hello");
//		for (int i = 0; i < s1.size(); i++)
//		{
//			cout << s1[i];
//		}
//	}
//}

namespace mystring
{
	class string
	{
	public:
		typedef char* iterator;
		iterator begin()
		{
			return _str;
		}
		iterator end()
		{
			return _str+_size;
		}
		string(const char* str = "")
		{
			npos = -1;
			_size = strlen(str);
			_capacity = _size;
			_str = new char[_capacity+1];
			memcpy(_str, str, sizeof(str)+1);
		}
		~string()
		{
			delete[]_str;
			_size = _capacity = 0;
			_str = nullptr;
		}
		string(const string& s)
			:_str(new char[strlen(s._str)+1])
		{
			memcpy(_str, s._str, sizeof(s._str) + 1);
		}
		size_t size()const
		{
			return _size;
		}
		size_t capacity() const
		{
			return _capacity;
		}
		char& operator[](size_t i)
		{
			assert(i < _size);
			return _str[i];
		}

		const char& operator[](size_t i)const
		{
			assert(i < _size);
			return _str[i];
		}
		const char* c_str()
		{
			return _str;
		}
		void reserve(size_t n)
		{
			char* tmp = new char[n + 1];
			memcpy(tmp, _str, sizeof(_str));
			delete[]_str;
			_str = tmp;
			_capacity = n;
		}
		void push_back(char ch)
		{
			if (_capacity == _size)
			{
				size_t newcapacity = _capacity ==0?2:_capacity *2;
				reserve(newcapacity);
			}
			_str[_size] = ch;
			++_size;
			_str[_size] = '\0';
		}
		void append(const char* str)
		{
			size_t len = strlen(str);
			if (_size+len>_capacity)
			{
				size_t newcapacity = _size+len;
				reserve(newcapacity);
			}
			memcpy(_str+_size, str, strlen(str));
			_size += len;
		}
		string& operator+=(char ch)
		{
			this->push_back(ch);
			return *this;
		}
		string& operator+=(const char* str)
		{
			this->append(str);
			return *this;
		}
		void resize(size_t n, char ch = '\0')
		{
			if (n < _size)
			{
				_str[n] = '/0';
				_size = n;
			}
			else
			{
				if (n > _capacity)
				{
					reserve(n);
				}
				for (size_t i = _size; i < n; i++)
				{
					_str[i] = ch;
				}
				_size = n;
				_str[_size] = '\0';
			}
		}
		string& insert(size_t pos, char ch)
		{
			assert(pos < _size);
			if (_size == _capacity)
			{
				size_t newcapacity = _capacity == 0 ? 2 : _capacity * 2;
				reserve(newcapacity);
			}
			int end = _size;
			while (end >= pos)
			{
				_str[end+1] = _str[end];
				end--;
			}
			_str[pos] = ch;
			++_size;
			return *this;
		}
		string& insert(size_t pos, const char* str)
		{
			assert(pos < _size);
			size_t len = strlen(str);
			if (_size + len > _capacity)
			{
				reserve(_size + len);
			}
			int end = _size;
			while (end >= pos)
			{
				_str[end + len] = _str[end];
				end--;
			}
			for (size_t i = 0; i < len; i++)
			{
				_str[pos++] = str[i++];
			}
			return *this;
		}
		string& erase(size_t pos, size_t len = npos)
		{
			assert(pos < _size);
			if (len > _size - pos)
			{
				_str[pos] = '\0';
				_size = pos;
			}
			else
			{
				size_t i = pos + len;
				while (i <= _size)
				{
					_str[i - len] = _str[i];
					++i;
				}
				_size -= len;
			}
			return *this;
		}
		size_t find(char ch, size_t pos = 0)
		{
			for (size_t i = pos; i < _size; ++i)
			{
				if (_str[i] == ch)
				{
					return i;
				}
			}
			return npos;
		}
		size_t find(const char* str, size_t pos = 0)
		{
			char* p = strstr(_str, str);
			if (p == nullptr)
			{
				return npos;
			}
			else
			{
				return p - _str;
			}
		}
		bool operator<(const string& s)
		{
			int ret = strcmp(_str, s._str);
			return ret < 0;
		}
		bool operator==(const string& s)
		{
			int ret = strcmp(_str, s._str);
			return ret == 0;
		}
		bool operator<=(const string& s)
		{
			return *this < s || *this == s;
		}
		bool operator>(const string& s)
		{
			return !(*this <= s);
		}
		bool operator>=(const string& s)
		{
			return !(*this < s);
		}
		bool operator !=(const string& s)
		{
			return !(*this == s);
		}
	private:
		char* _str;
		size_t _size;
		size_t _capacity;
		static size_t npos;
	};
	ostream& operator<<(ostream& out, const string& s)
	{
		for (size_t i = 0; i < s.size(); i++)
		{
			out << s[i];
		}
		return out;
	}
	istream& operator>>(istream& in,string&s)
	{
		while (1)
		{
			char ch;
			ch = in.get();
			if (ch == ' ' || ch == '\n')
			{
				break;
			}
			else
			{
				s += ch;
			}
		}
		return in;
	}
}
