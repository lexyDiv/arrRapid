#pragma once
#include "rand.h"

using namespace std;

template <typename T>
class rapid
{
public:
	rapid();
	~rapid();
	T pop();
	T shift();
	void backForce(int force);
	void frontForce(int force);
	void push(T item);
	void unshift(T item);
	void norm();
	void print();
	void printArr();
	rapid<T> *filter(function<bool(T item, int index)> fn);
	rapid<T> *sort(function<bool(T a, T b)> fn);
	T min(function<int(T item)> fn);
	T max(function<int(T item)> fn);
	void forEach(function<void(T item, int index, T **arr)> fn);
	void forEach(function<void(T item, int index)> fn);
	void forEach(function<void(T item)> fn);
	int indexOf(T item);
	int getLength();
	void clear();

	T &getItem(int index)
	{
		return this->arr[index];
	};



	class too
	{
	public:
		T item;
		int koof;
		too(T item, int koof)
		{
			this->item = item;
			this->koof = koof;
		};
	};

private:
	int length = 0;
	T *arr = new T[0];
	int left = 0;
	int right = 0;
	T *frontCopy(T *newArr);
	T *backCopy(T *newArr);
	T *createNewArr(int force);
	void copy(T *newArr);
	rapid<T> *createRapid();
};

template <typename T>
inline rapid<T>::rapid()
{
};

template <typename T>
inline rapid<T>::~rapid()
{
	delete[] this->arr;
	this->arr = nullptr;
};

template <typename T>
inline T rapid<T>::pop()
{
	int index = this->length - 1;
	this->length--;
	this->right++;
	return this->arr[index];
};

template <typename T>
inline T rapid<T>::shift()
{
	int index = this->left;
	this->left++;
	this->length--;
	return this->arr[index];
};

template <typename T>
inline void rapid<T>::backForce(int force)
{
	this->right = force;
	this->copy(this->frontCopy(this->createNewArr(force)));
};

template <typename T>
inline void rapid<T>::frontForce(int force)
{
	this->left = force;
	this->copy(this->backCopy(this->createNewArr(force)));
};

template <typename T>
inline void rapid<T>::push(T item)
{ // delete this->arr[this->length];
	this->arr[this->length] = item;
	this->length++;
	this->right--;
};

template <typename T>
inline void rapid<T>::unshift(T item)
{
	this->left--;
	this->length++;
	this->arr[this->left] = item;
};

template <typename T>
inline void rapid<T>::norm()
{
	if (this->right)
	{
		this->copy(this->frontCopy(this->createNewArr(0)));
		this->right = 0;
	}
	else if (this->left)
	{
		this->copy(this->backCopy(this->createNewArr(0)));
		this->left = 0;
	}
};

template <typename T>
inline void rapid<T>::print()
{
	cout << "===========================================" << endl;
	cout << " length = " << this->length << endl;
	cout << " left = " << this->left << endl;
	cout << " right = " << this->right << endl;
	cout << " first = " << this->arr[0] << endl;
	cout << " last = " << this->arr[this->length - 1] << endl;
	cout << "===========================================" << endl;
};

template <typename T>
inline void rapid<T>::printArr()
{
	int index = this->length + this->left + this->right;
	for (int i = 0; i < index; i++)
	{
		cout << " i = " << i << " : " << this->arr[i] << endl;
	}
};

template <typename T>
inline rapid<T> *rapid<T>::filter(function<bool(T item, int index)> fn)
{
	rapid *newRapid = this->createRapid();
	for (int i = 0; i < this->length; i++)
	{
		T item = this->arr[i];
		if (fn(item, i))
		{
			newRapid->push(item);
		}
	}
	newRapid->norm();
	return newRapid;
};

template <typename T>
inline rapid<T> *rapid<T>::sort(function<bool(T a, T b)> fn)
{
	rapid<T> *newRapid = this->createRapid();
	newRapid->backForce(this->length);
	for (int i = 0; i < this->length; i++)
	{
		newRapid->push(this->arr[i]);
	}

	std::sort(&newRapid->arr[0], &newRapid->arr[this->length], fn);
	return newRapid;
};

template <typename T>
inline T rapid<T>::min(function<int(T item)> fn)
{

	too min(this->arr[0], fn(this->arr[0]));
	for (int i = 0; i < this->length; i++)
	{
		T item = this->arr[i];
		int res = fn(item);
		if (res < min.koof)
		{
			min.item = item;
			min.koof = res;
		}
	}
	return min.item;
};

template <typename T>
inline T rapid<T>::max(function<int(T item)> fn)
{
	too min(this->arr[0], fn(this->arr[0]));
	for (int i = 0; i < this->length; i++)
	{
		T item = this->arr[i];
		int res = fn(item);
		if (res > min.koof)
		{
			min.item = item;
			min.koof = res;
		}
	}
	return min.item;
};

template <typename T>
inline void rapid<T>::forEach(function<void(T item)> fn)
{
	for (int i = 0; i < this->length; i++)
	{
		fn(this->arr[i]);
	}
}

template <typename T>
inline int rapid<T>::indexOf(T item)
{
	for (int i = 0; i < this->length; i++)
	{
		T el = this->arr[i];
		if (el == item)
		{
			return i;
		}
	}
	return -1;
}
template <typename T>
inline int rapid<T>::getLength()
{
    return this->length;
}

template <typename T>
inline void rapid<T>::clear() {
	this->length = 0;
	this->norm();
	this->left = 0;
	this->right = 0;
 
};

template <typename T>
inline void rapid<T>::forEach(function<void(T item, int index)> fn)
{
	for (int i = 0; i < this->length; i++)
	{
		fn(this->arr[i], i);
	};
};

template <typename T>
inline void rapid<T>::forEach(function<void(T item, int index, T **arr)> fn)
{
	for (int i = 0; i < this->length; i++)
	{
		fn(this->arr[i], i, this->arr);
	};
};

template <typename T>
inline T *rapid<T>::frontCopy(T *newArr)
{
	for (int i = 0; i < this->length; i++)
	{
		newArr[i] = this->arr[i];
	};
	return newArr;
};

template <typename T>
inline T *rapid<T>::backCopy(T *newArr)
{
	for (int i = this->length - 1; i >= 0; i--)
	{
		newArr[i] = this->arr[this->left + i];
	};
	return newArr;
};

template <typename T>
inline T *rapid<T>::createNewArr(int force)
{
	return new T[this->length + force];
};

template <typename T>
inline void rapid<T>::copy(T *newArr)
{
	delete[] this->arr;
	this->arr = newArr;
	// cout << this->arr << endl;
};

template <typename T>
inline rapid<T> *rapid<T>::createRapid()
{
	rapid<T> *newRapid = new rapid<T>;
	newRapid->backForce(this->length);
	return newRapid;
};
