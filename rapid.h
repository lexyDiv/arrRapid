#pragma once
#include <iostream>
#include <functional>

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
	rapid<T> *filter(function<bool(T item, int index, T *arr)> fn);

private:
	T *arr = new T[0];
	int length = 0;
	int left = 0;
	int right = 0;
	T *frontCopy(T *newArr);
	T *backCopy(T *newArr);
	T *createNewArr(int force);
	void copy(T *newArr);
};

template <typename T>
inline rapid<T>::rapid()
{
}

template <typename T>
inline rapid<T>::~rapid()
{
	delete[] this->arr;
}

template <typename T>
inline T rapid<T>::pop()
{
	int index = this->length - 1;
	this->length--;
	this->right++;
	return this->arr[index];
}

template <typename T>
inline T rapid<T>::shift()
{
	int index = this->left;
	this->left++;
	this->length--;
	return this->arr[index];
}

template <typename T>
inline void rapid<T>::backForce(int force)
{
	this->right = force;
	this->copy(this->frontCopy(this->createNewArr(force)));
}

template <typename T>
inline void rapid<T>::frontForce(int force)
{
	this->left = force;
	this->copy(this->backCopy(this->createNewArr(force)));
}

template <typename T>
inline void rapid<T>::push(T item)
{
	this->arr[this->length] = item;
	this->length++;
	this->right--;
}

template <typename T>
inline void rapid<T>::unshift(T item)
{
	this->left--;
	this->length++;
	this->arr[this->left] = item;
}

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
}

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
}

template <typename T>
inline rapid<T> *rapid<T>::filter(function<bool(T item, int index, T *arr)> fn)
{
	rapid<T> *newRapid = new rapid<T>;
	newRapid->backForce(this->length);
	for (int i = 0; i < this->length; i++)
	{
		T item = this->arr[i];
		if (fn(item, i, this->arr))
		{
			newRapid->push(item);
		}
	}
	newRapid->norm();
	return newRapid;
};

template <typename T>
inline T *rapid<T>::frontCopy(T *newArr)
{
	for (int i = 0; i < this->length; i++)
	{
		newArr[i] = this->arr[i];
	}
	return newArr;
}

template <typename T>
inline T *rapid<T>::backCopy(T *newArr)
{
	for (int i = this->length - 1; i >= 0; i--)
	{
		newArr[i] = this->arr[this->left + i];
	}
	return newArr;
}

template <typename T>
inline T *rapid<T>::createNewArr(int force)
{
	return new T[this->length + force];
}

template <typename T>
inline void rapid<T>::copy(T *newArr)
{
	delete[] this->arr;
	this->arr = newArr;
}
