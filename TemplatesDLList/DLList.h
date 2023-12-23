﻿#pragma once
#include <iostream>
#include <sstream>

template<typename T>
class Node;

template<typename T> class DLList;

/**
* @brief Опрератор вывода.
* @param os Поток вывода.
* @param list Список для вывода.
* @return Изменённый поток вывода.
*/
template<typename T>
std::ostream& operator<< (std::ostream& os, const DLList<T>& list);

/**
* @brief Перегрузка оператора сравнения
* @param rha Первый аргумент для сравнения
* @param lha Второй аргумент для сравнения
* @return true - равны, false не равны
*/
template<typename T>
bool operator==(const DLList<T>& rha, const DLList<T>& lha) noexcept;

/**
@brief Перегрузка оператора не равно
@param rha Первый аргумент для сравнения
@param lha Второй аргумент для сравнения
@return false - равны, true не равны
*/
template<typename T>
bool operator!=(const DLList<T>& rha, const DLList<T>& lha) noexcept;

template<typename T>
/*
@brief Класс, описывающий линейный двусвязный список
*/
class DLList
{
public:
	/*
	* @brief  Создает пустой объект класса DLList
	*/
	DLList();
	/*
	* @brief  Создает объект класса DLList по исходным данным
	* @param list Элементы списка
	*/
	DLList(const std::initializer_list<T> list);

	/*
	* @brief Деструктор класса, чистит память при удалении объекта
	*/
	~DLList();

	/*
	* @brief Очистка списка
	*/
	void clean();

	/*
	* @brief Добавления элемента в конец списка
	* @param value Элемент для добавления
	*/
	void push_back(const T& value);

	/*
	* @brief Добавления элемента в начало списка
	* @param value Элемент для добавления
	*/
	void push_forward(const T& value);

	/*
	* @brief Удаление элемента с конца списка
	*/
	void pop_back();

	/*
	* @brief Удаление элемента с начала списка
	*/
	void pop_forward();

	/*
	* @brief Проверяет наличие эелементов в списке
	* @return true если есть, false если нет
	*/
	bool has_elements() const noexcept;

	/*
	* @brief Проверяет отсутствие эелементов в списке
	* @return true если есть, false если нет
	*/
	bool is_empty() const noexcept;

	/*
	* @brief Функция для преобразования списка в строку
	* @return Строка, построенная по списку
	*/
	std::string to_string() const noexcept;

	/*
	* @brief Оператор копирования
	* @param list Список для копирования
	* @return Скопированный объект типа DLList
	*/
	DLList<T>& operator=(const DLList<T>& list);

	/*
	* @brief Оператор перемещение
	* @param list Список для перемещения
	* @return Перемещенный объект типа DLList
	*/
	DLList<T>& operator=(DLList<T>&& list) noexcept;

	/*
	* @brief Конструктор копирования
	* @param list Список для копирования
	*/
	DLList(DLList<T>&& list);
	/*
	* @brief Конструктор перемещения
	* @param list Список для перемещения
	*/
	DLList(const DLList<T>& list);

private:
	Node<T>* head;
	Node<T>* tail;


};



template<typename T>
class Node
{
public:
	/*
	@brief  Инициализирует новый экземпляр класса Node
	@param value Значение элемента
	@param prev Предыдущий элемент
	@param next Следующий элемент
	*/
	Node(T value);

	Node<T>* next;
	Node<T>* prev;

	T value;
};

template<typename T>
inline Node<T>::Node(T value)
	:value(value), prev(nullptr), next(nullptr)
{
}

template<typename T>
inline DLList<T>::DLList()
	: head(nullptr), tail(nullptr)
{
}




template<typename T>
inline DLList<T>::DLList(const std::initializer_list<T> list)
	: head(nullptr), tail(nullptr)
{
	for (auto item : list)
	{
		this->push_back(item);
	}
}

template<typename T>
inline DLList<T>::~DLList()
{
	this->clean();
}

template<typename T>
inline void DLList<T>::clean()
{
	while (this->has_elements())
		pop_forward();
	tail = nullptr;
	head = nullptr;
}

template<typename T>
inline std::string DLList<T>::to_string() const noexcept
{
	std::stringstream result_string;
	result_string << "[ ";
	auto curr = this->head;
	while (curr != nullptr)
	{
		result_string << curr->value << " ";
		curr = curr->next;
	}
	result_string << "]";
	return result_string.str();
}

template<typename T>
inline void DLList<T>::push_back(const T& value)
{
	Node<T>* ptr(new Node<T>(value));
	ptr->prev = this->tail;
	if (this->has_elements())
	{
		this->tail->next = ptr;
	}
	else
	{
		this->head = ptr;
	}
	this->tail = ptr;
}

template<typename T>
inline void DLList<T>::push_forward(const T& value)
{
	Node<T>* ptr(new Node<T>(value));

	if (this->has_elements())
	{
		this->head->prev = ptr;
		ptr->next = this->head;
		this->head = ptr;
	}
	else
	{
		this->tail = ptr;
		this->head = ptr;
	}
}

template<typename T>
inline void DLList<T>::pop_back()
{
	if (this->has_elements())
	{
		if (this->head == this->tail)
		{
			delete this->head;
			this->head = nullptr;
			this->tail = nullptr;
		}
		else
		{
			Node<T>* prev = this->tail->prev;
			delete this->tail;
			prev->next = nullptr;
			this->tail = prev;
		}

	}
}

template<typename T>
inline void DLList<T>::pop_forward()
{
	if (this->has_elements())
	{
		if (this->head == this->tail)
		{
			delete this->head;
			this->head = nullptr;
			this->tail = nullptr;
		}
		else
		{
			Node<T>* next = this->head->next;
			delete this->head;
			next->prev = nullptr;
			this->head = next;
		}
	}
}

template<typename T>
inline bool DLList<T>::has_elements() const noexcept
{
	return !(this->is_empty());
}

template<typename T>
inline bool DLList<T>::is_empty() const noexcept
{
	return this->head == nullptr;
}

template<typename T>
inline DLList<T>& DLList<T>::operator=(const DLList<T>& list)
{
	if (*this != list)
	{
		DLList temp(list);
		std::swap(this->head, temp.head);
		std::swap(this->tail, temp.tail);
		return *this;
	}
}

template<typename T>
inline DLList<T>& DLList<T>::operator=(DLList<T>&& list) noexcept
{
	if (*this != list)
	{
		std::swap(this->head, list.head);
		std::swap(this->tail, list.tail);
		return *this;
	}

}

template<typename T>
inline DLList<T>::DLList(DLList<T>&& list)
	: head(nullptr), tail(nullptr)
{
	std::swap(this->head, list.head);
	std::swap(this->tail, list.tail);
}

template<typename T>
inline DLList<T>::DLList(const DLList<T>& list)
	: head(nullptr), tail(nullptr)
{
	DLList temp;
	auto curr = list.head;
	while (curr != nullptr)
	{
		temp.push_back(curr->value);
		curr = curr->next;
	}
	std::swap(this->head, temp.head);
	std::swap(this->tail, temp.tail);
}

template<typename T>
inline std::ostream& operator<<(std::ostream& os, const DLList<T>& list)
{
	return os << list.to_string();
}

template<typename T>
inline bool operator==(const DLList<T>& rha, const DLList<T>& lha) noexcept
{
	return (lha.to_string() == rha.to_string());
}

template<typename T>
inline bool operator!=(const DLList<T>& rha, const DLList<T>& lha) noexcept
{
	return !(lha == rha);
}