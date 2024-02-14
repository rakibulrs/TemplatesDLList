#pragma once
#include <iostream>
#include <sstream>

template<typename T> class DLList;

/**
* @brief The output operator
* @param os Output Stream
* @param list Output list
* @return Modified output stream
*/
template<typename T>
std::ostream& operator<< (std::ostream& os, const DLList<T>& list);

/**
* @brief Overloading the comparison operator
* @param rha The first argument for comparison
* @param lha The second argument for comparison
* @return true - equal, false are not equal
*/
template<typename T>
bool operator==(const DLList<T>& rha, const DLList<T>& lha) noexcept;

/**
@brief Operator overloading is not equal to
@param rha The first argument for comparison
@param lha The second argument for comparison
@return false - equal, true are not equal
*/
template<typename T>
bool operator!=(const DLList<T>& rha, const DLList<T>& lha) noexcept;

/*
@brief A class describing a linear doubly connected list
*/
template<typename T>
class DLList
{
public:
	/**
	* @brief Creates an empty object of the DLList class
	*/
	DLList();

	/**
	* @brief Creates an object of the DLList class based on the source data
	* @param list List Items
	*/
	DLList(const std::initializer_list<T> list);

	/**
	* @brief The move constructor
	* @param list The list to move
	*/
	DLList(DLList<T>&& list);

	/**
	* @brief Copy Constructor
	* @param list The list to copy
	*/
	DLList(const DLList<T>& list);

	/**
	* @brief A class destructor that cleans memory when an object is deleted
	*/
	~DLList();

	/**
	* @brief The copy operator
	* @param list The list to copy
	* @return The copied object of the DLList type
	*/
	DLList<T>& operator=(const DLList<T>& list);

	/**
	* @brief The move operator
	* @param list The list to move
	* @return A moved object of the DLList type
	*/
	DLList<T>& operator=(DLList<T>&& list) noexcept;

	/**
	* @brief Checks for the presence of items in the list
	* @return true if there is, false if not
	*/
	bool has_elements() const noexcept;

	/**
	* @brief Checks for the absence of items in the list
	* @return true if there is, false if not
	*/
	bool is_empty() const noexcept;

	/**
	* @brief A function for converting a list to a string
	* @return A string based on a list
	*/
	std::string to_string() const noexcept;

	/**
	* @brief Getting the size of the list
	* @return The size of the list
	*/
	size_t get_size() const noexcept;

	/**
	* @brief Searching for an item in the list
	* @param element The element to search for
	* @return true - is in the list, false - is not in the list
	*/
	bool find(const T& element) const noexcept;

	/**
	* @brief Getting an element located at an offset equal to index from the beginning of the list
	* @param index Offset relative to the beginning of the list where the desired item is located
	* @return The value of the element that is at the index offset from the beginning
	*/
	T get(size_t index) const;

	/**
	* @brief Clearing the list
	*/
	void clean();

	/**
	* @brief Adding an item to the end of the list
	* @param value Element to add
	*/
	void push_back(const T& value);

	/**
	* @brief Adding an item to the top of the list
	* @param value Element to add
	*/
	void push_forward(const T& value);

	/**
	* @brief Deleting an item from the end of the list
	*/
	void pop_back();

	/**
	* @brief Deleting an item from the beginning of the list
	*/
	void pop_forward();

	

private:

	template<typename T>
	class Node
	{
	public:
		/**
		* @brief Initializes a new instance of the Node class
		* @param value  The value of the element
		*/
		explicit Node(const T& value) 
			:value{ value }, next{ nullptr }, previous{ nullptr }
		{
		};

		Node<T>* next;
		Node<T>* previous;

		T value;
	};

	/**
	* @brief Moving private fields of the current class with an external one
	* @param list A list for moving fields
	*/
	void swap(DLList<T>& list);

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
	: DLList()
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
inline bool DLList<T>::find(const T& element) const noexcept
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
inline void DLList<T>::swap(DLList<T>& list)
{
	std::swap(this->head, list.head);
	std::swap(this->tail, list.tail);
	std::exchange(this->size, list.size);
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
		temp = temp->next;
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
		this->swap(temp);
	}
	return *this;
}

template<typename T>
inline DLList<T>& DLList<T>::operator=(DLList<T>&& list) noexcept
{
	if (*this != list)
	{
		this->swap(list);
	}
	return *this;
}

template<typename T>
inline DLList<T>::DLList(DLList<T>&& list)
	: DLList()
{
	this->swap(list);
}

template<typename T>
inline DLList<T>::DLList(const DLList<T>& list)
	: DLList()
{
	DLList temp;
	auto current = list.head;
	while (current != nullptr)
	{
		temp.push_back(current->value);
		current = current->next;
	}
	this->swap(temp);
}

template<typename T>
inline std::ostream& operator<<(std::ostream& os, const DLList<T>& list)
{
	return os << list.to_string();
}

template<typename T>
inline bool operator==(const DLList<T>& rha, const DLList<T>& lha) noexcept
{
	return (&lha == &rha) || (lha.to_string() == rha.to_string());
}

template<typename T>
inline bool operator!=(const DLList<T>& rha, const DLList<T>& lha) noexcept
{
	return !(lha == rha);
}