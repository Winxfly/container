#pragma once
#include <mutex>

// HEADER

template<typename T>
class Conqu {
private:

	template<typename T>
	class Node {
	public:
		Node *pNext;
		T data;

		Node(T data = T(), Node *pNext = nullptr) {
			this->data = data;
			this->pNext = pNext;
		}

	};

	size_t size;
	Node<T> *head;
	Node<T> *tail;
	std::mutex mtx;
	std::condition_variable data_cond;

public:

	Conqu();
	~Conqu();

	void push_back(T data);
	void push_front(T data);
	void pop_back();
	void pop_front();
	T front();
	T back();
	bool empty() const;
	void wait();
	void clear();
	size_t getSize() const;

	T& operator[](const int index);
};

// IMPLEMENTATION

template<typename T>
Conqu<T>::Conqu()
{
	size = 0;
	head = nullptr;
	tail = nullptr;
}

template<typename T>
Conqu<T>::~Conqu()
{
	clear();
}

template<typename T>
void Conqu<T>::push_back(T data)
{
	std::lock_guard<std::mutex> lock(mtx);
	if (head == nullptr) {
		head = new Node<T>(data);
		tail = head;
	}
	else {
		Node<T> *current = this->head;

		while (current->pNext != nullptr)
		{
			current = current->pNext;
		}
		current->pNext = new Node<T>(data);
		tail = current->pNext;
	}

	size++;
	data_cond.notify_all();
}

template<typename T>
void Conqu<T>::push_front(T data)
{
	std::lock_guard<std::mutex> lock(mtx);
	head = new Node<T>(data, head);

	size++;
	data_cond.notify_all();
}

template<typename T>
void Conqu<T>::pop_back()
{
	std::lock_guard<std::mutex> lock(mtx);
	if (size == 0) {
		return;
	}

	Node<T> *temp = this->head;
	for (int i = 0; i < getSize() - 1; i++) {
		tail = temp;
		temp = temp->pNext;
	}

	delete temp->pNext;
	size--;
}

template<typename T>
void Conqu<T>::pop_front()
{
	std::lock_guard<std::mutex> lock(mtx);
	if (size == 0) {
		return;
	}

	Node<T> *temp = head;
	head = head->pNext;

	delete temp;
	size--;
}

template<typename T>
T Conqu<T>::front()
{
	std::lock_guard<std::mutex> lock(mtx);
	Node<T> *temp = head;
	return temp->data;
}

template<typename T>
T Conqu<T>::back()
{
	std::lock_guard<std::mutex> lock(mtx);
	Node<T> *temp = tail;
	return temp->data;;
}

template<typename T>
bool Conqu<T>::empty() const
{
	if (size > 0) {
		return true;
	}
	else {
		return false;
	}
}

template<typename T>
void Conqu<T>::wait()
{
	std::unique_lock<std::mutex> lk(mtx);
	data_cond.wait(lk, [] {return static_cast<bool>(getSize()); });
	lk.unlock();
}

template<typename T>
void Conqu<T>::clear()
{
	while (size) {
		pop_front();
	}
}

template<typename T>
size_t Conqu<T>::getSize() const
{
	return size;
}

template<typename T>
T & Conqu<T>::operator[](const int index)
{
	std::lock_guard<std::mutex> lock(mtx);
	int counter = 0;
	Node<T> *current = this->head;

	while (current != nullptr)
	{
		if (counter == index) {
			return current->data;
		}
		current = current->pNext;
		counter++;
	}
}