#pragma once
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

/**
@brief Класс, описывающий линейный двусвязный список
*/
template<typename T>
class DLList
{
public:
	/**
	* @brief  Создает пустой объект класса DLList
	*/
	DLList();

	/**
	* @brief  Создает объект класса DLList по исходным данным
	* @param list Элементы списка
	*/
	DLList(const std::initializer_list<T> list);

	/**
	* @brief Конструктор копирования
	* @param list Список для копирования
	*/
	DLList(DLList<T>&& list);

	/**
	* @brief Конструктор перемещения
	* @param list Список для перемещения
	*/
	DLList(const DLList<T>& list);

	/**
	* @brief Деструктор класса, чистит память при удалении объекта
	*/
	~DLList();

	/**
	* @brief Оператор копирования
	* @param list Список для копирования
	* @return Скопированный объект типа DLList
	*/
	DLList<T>& operator=(const DLList<T>& list);

	/**
	* @brief Оператор перемещение
	* @param list Список для перемещения
	* @return Перемещенный объект типа DLList
	*/
	DLList<T>& operator=(DLList<T>&& list) noexcept;

	/**
	* @brief Проверяет наличие эелементов в списке
	* @return true если есть, false если нет
	*/
	bool has_elements() const noexcept;

	/**
	* @brief Проверяет отсутствие эелементов в списке
	* @return true если есть, false если нет
	*/
	bool is_empty() const noexcept;

	/**
	* @brief Функция для преобразования списка в строку
	* @return Строка, построенная по списку
	*/
	std::string to_string() const noexcept;

	/**
	* @brief Получение длины списка
	* @return Длина списка
	*/
	size_t get_size() const noexcept;

	/**
	* @brief Поиск элемента в списке
	* @param element Элемент для поиска
	* @return true - есть в спике, false - нет в списке
	*/
	bool find(size_t element) const noexcept;

	/**
	* @brief Получение элемента находящегося на смещенни равном index от начала списка
	* @param index Смещение относительно начала спика, на котором стоит искомый элемент
	* @return Значение элемента, что находится на смещении index от начала
	*/
	T get(size_t index) const;

	/**
	* @brief Очистка списка
	*/
	void clean();

	/**
	* @brief Добавления элемента в конец списка
	* @param value Элемент для добавления
	*/
	void push_back(const T& value);

	/**
	* @brief Добавления элемента в начало списка
	* @param value Элемент для добавления
	*/
	void push_forward(const T& value);

	/**
	* @brief Удаление элемента с конца списка
	*/
	void pop_back();

	/**
	* @brief Удаление элемента с начала списка
	*/
	void pop_forward();

	

private:

	template<typename T>
	class Node
	{
	public:
		/**
		@brief  Инициализирует новый экземпляр класса Node
		@param value Значение элемента
		@param previous Предыдущий элемент
		@param next Следующий элемент
		*/
		explicit Node(const T& value) 
			:value{ value }, next{ nullptr }, previous{ nullptr }
		{
		};

		Node<T>* next;
		Node<T>* previous;

		T value;
	};

	Node<T>* head;
	Node<T>* tail;
	size_t size;
};

template<typename T>
inline DLList<T>::DLList()
	: head{ nullptr }, tail{ nullptr }, size{ 0 }

{
}

template<typename T>
inline DLList<T>::DLList(const std::initializer_list<T> list)
	: head{ nullptr }, tail{ nullptr }, size{ 0 }
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
	{
		pop_forward();
	}
	tail = nullptr;
	head = nullptr;
}

template<typename T>
inline std::string DLList<T>::to_string() const noexcept
{
	std::stringstream result_string;
	result_string << "[ ";
	auto temp = this->head;
	while (temp != nullptr)
	{
		result_string << temp->value << " ";
		temp = temp->next;
	}
	result_string << "]";
	return result_string.str();
}

template<typename T>
inline size_t DLList<T>::get_size() const noexcept
{
	return this->size;
}

template<typename T>
inline bool DLList<T>::find(size_t element) const noexcept
{
	auto current = this->head;
	while (current != nullptr)
	{
		if (current->value == element)
		{
			return true;
		}
		current = current->next;
	}
	return false;
}

template<typename T>
inline void DLList<T>::push_back(const T& value)
{
	Node<T>* ptr(new Node<T>(value));
	ptr->previous = this->tail;
	if (this->has_elements())
	{
		this->tail->next = ptr;
	}
	else
	{
		this->head = ptr;
	}
	this->tail = ptr;
	this->size++;
}

template<typename T>
inline void DLList<T>::push_forward(const T& value)
{
	Node<T>* ptr(new Node<T>(value));

	if (this->has_elements())
	{
		this->head->previous = ptr;
		ptr->next = this->head;
		this->head = ptr;
	}
	else
	{
		this->tail = ptr;
		this->head = ptr;
	}
	this->size++;
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
			Node<T>* previous = this->tail->previous;
			delete this->tail;
			previous->next = nullptr;
			this->tail = previous;
		}
		this->size--;
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
			next->previous = nullptr;
			this->head = next;
		}
		this->size--;
	}
}

template<typename T>
inline T DLList<T>::get(size_t index) const
{
	if (this->is_empty() || (index + 1) > this->size) 
	{
		throw std::out_of_range("Incorrect index");
	}

	Node<T>* temp = this->head;
	for (size_t i = 0; i < index; i++)
	{
		temp = head->next;
	}
	return temp->value;
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
		std::exchange(this->size, temp.size);
	}
	return *this;
}

template<typename T>
inline DLList<T>& DLList<T>::operator=(DLList<T>&& list) noexcept
{
	if (*this != list)
	{
		std::swap(this->head, list.head);
		std::swap(this->tail, list.tail);
		std::exchange(this->size, list.size);
	}
	return *this;
}

template<typename T>
inline DLList<T>::DLList(DLList<T>&& list)
	: head{ nullptr }, tail{ nullptr }
{
	std::swap(this->head, list.head);
	std::swap(this->tail, list.tail);
	std::exchange(this->size, list.size);
}

template<typename T>
inline DLList<T>::DLList(const DLList<T>& list)
	: head{ nullptr }, tail{ nullptr }
{
	DLList temp;
	auto current = list.head;
	while (current != nullptr)
	{
		temp.push_back(current->value);
		current = current->next;
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
	if (&lha == &rha) 
	{
		return true;
	}
	return (lha.to_string() == rha.to_string());
}

template<typename T>
inline bool operator!=(const DLList<T>& rha, const DLList<T>& lha) noexcept
{
	return !(lha == rha);
}