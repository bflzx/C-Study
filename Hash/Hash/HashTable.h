#pragma once

#include<vector>
using namespace std;

namespace CLOSE
{
	enum State
	{
		EMPTY,
		EXITS,
		DELETE,
	};

	template<class T>
	struct HashData
	{
		T _data;
		State _state;
	};

	template<class K, class T, class KeyOfT>
	class HashTable
	{
		typedef HashData<T> HashData;
	public:
		bool Insert(const T& d)
		{
			//负载因子 = 表中数据个数/表的大小 衡量哈希表满的程度
			//表接近满,插入数据越容易冲突,冲突越多,效率越低
			//哈希表并不是满了才增容,一般是负载因子到了0.7左右开始增容
			//负载因子越小,冲突概率越低,整体效率越高,但是负载因子越小,浪费的空间越大
			//所以负载因子一般取一个折中值
			if (_tables.size() == 0 || _num * 10 / _tables.size() >= 7)
			{
				//增容
				//vector<HashData> newtables;
				//size_t newsize = _tables.size() == 0:10 ? _num * 2;
				//newtables.resize(newsize);
				//for (size_t i = 0; i < _tables.size(); i++)
				//{
				//	if (_tables[i]._state == EXITS)
				//	{
				//		size_t index = koft(_tables[i]._data) % newsize;
				//		while (newtables[index]._state == EXITS)
				//		{
				//			++index;
				//			if (index == _tables.size())
				//			{
				//				index = 0;
				//			}
				//		}
				//		newtables[index] = _tables[i];
				//	}
				//}
				//_tables.swap(newtables);

				HashTable<HashData> newht;
				size_t nwesize = _tables.size() == 0 ? 10 : _tables.size() * 2;
				for (size_t i = 0; i < _tables.size(); i++)
				{
					if (_tables[i]._state == EXITS)
					{
						newht.Insert(_tables[i]);
					}
				}

				_tables.swap(newht._tables);
			}



			//计算d在表中映射的位置
			size_t index = d % _tables->size();
			while (_tables[index]._state == EXITS)
			{
				if (_tables[index]._data == d)
				{
					return false;
				}
				++index;
				if (index == _tables->size())
				{
					index = 0;
				}
			}
			_tables[index]._data = d;
			_tables[index]._state = EXITS;
			_num++;

			return true;
		}

		HashData* Find(const K& key)
		{

			size_t index = key % _tables.size();
			while (_tables[index]._state != EMPTY)
			{
				if (koft(_tables[index]._data) == key)
				{
					if (_tables[index]._state == EXITS)
					{
						return &_tables[index];

					}
					else if (_tables[index]._state == DELETE)
					{
						return nullptr;
					}
				}

				index++;
				if (index == _tables.size())
				{
					index = 0;
				}
			}
			return nullptr;
		}

		bool Erase(const K& key)
		{
			HashData* ret = Find(key);
			if (ret)
			{
				ret->_state = DELETE;
				--_num;
				return true;
			}
			else
			{
				return false;
			}
		}
	private:
		vector<HashData> _tables;
		size_t _num = 0;
	};
}

namespace OPEN_HASH
{
	template<class T>
	struct HashNode
	{
		T _data;
		HashNode<T>* _next;

		HashNode(const T& data)
			:_data(data)
			,_next(nullptr)
		{ }
	};

	template<class K,class T,class KeyOfT>
	class HashTable
	{
		~HashTable()
		{
			Clear();
		}

		void Clear()
		{
			for (size_t i = 0; i < _tables.size(); i++)
			{
				Node* cur = _tables[i];
				while (cur)
				{
					Node* next = cur->_next;
					delete cur;
					cur = next;
				}
				_tables[i] = nullptr;
			}
		}

		typedef HashNode<T> Node;
	public:
		bool Insert(const T& data)
		{
			KeyOfT koft;
			
			//控制负载因子,如果等于1,则增容,避免大量的哈希冲突
			//当单个链表过长时,效率会降低

			if (_tables.size() == _num)
			{
				vector<Node*> newtables;
				size_t newsize = _tables.size() == 0:10 ? _tables.size() * 2;
				newtables.resize(newsize);
				for (size_t i = 0; i < _tables.size(); i++)
				{
					//将旧表中的节点取下来重新计算在新表中的位置,并插入进去
					Node* cur = _tables[index];
					while (cur)
					{
						Node* next = cur->_next;
						size_t index = koft(data) % newtables.size();
						cur->_next = newtables[index];
						newtables[index] = cur;

						cur = next;
					}
					_tables[i] = nullptr;
				}
				_tables[i].swap(newtables);
			}

			//计算数据在表中映射的位置
			size_t index = koft(data) % _tables.size();
			
			//1.先看这个值在不在表中
			Node* cur = _tables[index];
			while (cur)
			{
				if (koft(cur->_data) == koft(data))
				{
					return false;
				}
				else
				{
					cur = cur->_next;
				}
			}
			//2.头插到挂的链表中(尾插也可以)
			Node* newnode = nwe Node(data);
			newnode->_next = _tables[index];
			_tables[index] = newnode;

			++_num;
			return true;
		}
		Node* Find(const K& key)
		{
			KeyOfT koft;
			size_t index = key & _tables.size();
			Node* cur = _tables[index];
			while (cur)
			{
				if (koft(cur->_data) == key)
				{
					return cur;
				}
				else
				{
					cur = cur->_next;
				}
			}

			return nullptr;
		}

		bool Erase(const K& key)
		{
			KeyOfT koft;
			size_t index = key % _tables.size();
			Node* prev = nullptr;
			Node* cur = _tables[index];
			while (cur)
			{
				if (koft(cur->_data) == key)
				{
					if (prev == nullptr)
					{
						//表示要删的是第一个节点
						_tables[index] = cur->_next;
					}
					else
					{
						prev->_next = cur->_next;
						delete cur;
					}

					return true;
				}
				else
				{
					prev = cur;
					cur = cur->_next;
				}
			}
			
			return false;
		}
	private:
		vector<Node*> _tables;
		size_t _num = 0;
	};
}