#include <iostream>
template <typename T>
struct Node {
	T data;
	Node* prev;
	Node* next;
};
template <typename T>
Node<T>* front{ nullptr };
template <typename T>
void push_front(T value) {
	Node<T>* current = new Node<T>;
	current->data = value;
	current->next = front<T>;
	current->prev = nullptr;
	if (front<T> != nullptr)
		front<T>->prev = current;
	front<T> = current;
}
template <typename T>
void push_back(T value) {
	Node<T>* last = front<T>;
	Node<T>* current = new Node<T>;
	current->data = value;
	current->next = nullptr;
	if (last == nullptr) {
		current->prev = nullptr;
		front<T> = current;
	}
	else {
		while (last->next != nullptr) {
			last = last->next;
		}
		last->next = current;
		current->prev = last;
	}
}
template <typename T>
void delete_list() {
	Node<T>* last = front<T>;
	if (front<T> != nullptr) { //For more then 0 element
		while (last->next != nullptr) {
			last = last->next;
		}
		while (last->prev != nullptr) {
			last = last->prev;
			delete last->next;
		}
		delete last;
	}
	front<T> = nullptr;
}
template <typename T>
void pop_front() {
	if (front<T> == nullptr)
		throw std::exception("ERROR: List is already empty");
	Node<T>* temp = front<T>;
	if (temp->next != nullptr) {
		temp = temp->next;
		temp->prev = nullptr;
	}
	else
		temp = nullptr;
	delete front<T>;
	front<T> = temp;
}
template <typename T>
void pop_back() {
	if (front<T> == nullptr)
		throw std::exception("ERROR: List is already empty");
	Node<T>* temp = front<T>;
	Node<T>* current{ nullptr };
	if (temp->next != nullptr) {
		while (temp->next != nullptr) {
			temp = temp->next;
		}
		current = temp->prev;
		current->next = nullptr;
		delete temp;
	}
	else {
		delete front<T>;
		front<T> = nullptr;
	}
}
template <typename T>
void delete_elem(int position) {
	if (front<T> == nullptr || position < 1)
		throw std::exception("ERROR: A non-existent position is specified");
	Node<T>* temp = front<T>;
	Node<T>* current = new Node<T>;
	for (int i{ 1 }; i < position; ++i) {
		if (temp->next == nullptr) {
			if (front<T> == nullptr || position < 1)
				throw std::exception("ERROR: A non-existent position is specified");
		}
		temp = temp->next;
	}
	current = temp->next;
	temp->next = temp->next->next;
	temp->next->prev = temp;
	delete current;
}
template <typename T>
void insert_to_position(int position, T value) {
	if (front<T> == nullptr || position < 1)
		throw std::exception("ERROR: A non-existent position is specified");
	Node<T>* temp = front<T>;
	if (front<T> != nullptr && position > 0) { //For more then 0 element
		if (front<T>->next != nullptr) { //For more then 1 element
			for (int i{ 2 }; i < position; ++i) {
				if (temp->next == nullptr) {
					throw std::exception("ERROR: A non-existent position is specified");
				}
				temp = temp->next;
			}
			Node<T>* insert = new Node<T>;
			insert->data = value;
			insert->next = temp->next;
			insert->prev = temp;
			temp->next = insert;
		}
	}
}
template <typename T>
Node<T>* insert_array(T* array, int size) {
	Node<T>* current{ nullptr };
	Node<T>* arr{ nullptr };
	Node<T>* last{ nullptr };
	for (int i{ 0 }; i < size; ++i) {
		current = new Node<T>;
		current->data = array[i];
		current->next = nullptr;
		if (i == 0) {
			current->prev = nullptr;
			arr = current;
			current = new Node<T>;
			arr->next = current;
			last = arr;
		}
		else {
			current->prev = last;
			last->next = current;
			last = current;
		}
	}
	front<T> = arr; //Write to external variable (optional)
	return arr;
}
template <typename T>
void nodeOut() { //Output
	if (front<T> == nullptr)
		throw std::exception("ERROR: List is empty");
	for (Node<T>* current{ front<T> }; current != nullptr; current = current->next)
		std::cout << current->data << " ";
	std::cout << std::endl;
}
template <typename T>
void swap(int i, int j) {
	if (i < 1) throw std::exception("ERROR: A non-existent position is specified");
	if (i > j) { //i<j
		int temp{ 0 };
		temp = i;
		i = j;
		j = temp;
	}
	if (i < j) {
		Node<T>* current = front<T>;
		for (int k{ 1 }; k < i; ++k) {
			if (current->next == nullptr) throw std::exception("ERROR: A non-existent position is specified");
			current = current->next;
		}
		Node<T>* first = current;
		for (int k{ i }; k < j; ++k) {
			if (current->next == nullptr) throw std::exception("ERROR: A non-existent position is specified");
			current = current->next;
		}
		Node<T>* second = current;
		//избавляюсь от first в цепи:
		if (i > 1)
			first->prev->next = first->next;
		else
			front<T> = first->next;
			first->next->prev = first->prev;
		//избавляюсь от second в цепи:
		if (second->prev != nullptr)
			second->prev->next = second->next;
		if (second->next != nullptr)
			second->next->prev = second->prev;
		//first помещаю на место second:
		if (j - i != 1) { //Если не стоят рядом
			first->next = second->next;
			first->prev = second->prev;
			if (second->prev != nullptr)
				first->prev->next = first;
			if (first->next != nullptr)
				first->next->prev = first;
			//Повторно прохожу список и встаю на бывшее место first:
			current = front<T>;
			for (int k{ 1 }; k < i; ++k) {
				if (current->next == nullptr) throw std::exception("ERROR: A non-existent position is specified");
				current = current->next;
			}
			//Помещаю second на место first:
			second->next = current;
			if (i > 1) {
				current->prev->next = second;
				second->prev = current->prev->prev;
			}
			else {
				front<T> = second;
				second->prev = nullptr;
			}
			current->prev = second;
		}
		else {
			//first помещаю на место second:
			first->prev = second;
			first->next = second->next;
			//Помещаю second на место first:
			second->next = first;
			second->prev = current->prev;
			//Восстанавливаю связь:
			current->prev->next = second;
			if (first->next != nullptr)
				first->next->prev = first;
		}
	}
}

int main()
{
	using namespace std;
	//for (char i{ 50 }; i < 60; ++i) {
		//push_back<char>(i);
	//}
	//delete_list();
	push_front<string>("aa");
	push_front<string>("bb");
	push_front<string>("cc");
	push_front<string>("dd");
	push_front<string>("ee");
	const int size = 5;
	int array[size]{ 5, 25, 0, 79, 222 };
	//pop_back<int>();
	//pop_front<int>();
	//delete_elem<int>(2);
	//insert_to_position<int>(6, 250);
	//insert_array<int>(array, size);
	nodeOut<string>();
	swap<string>(1, 3);
	nodeOut<string>();
	swap<string>(2, 3);
	nodeOut<string>();
	swap<string>(2, 4);
	nodeOut<string>();
	swap<string>(1, 3);
	nodeOut<string>();
	/*swap<int>(8, 9);
	nodeOut<int>();*/
	delete_list<char>();
	return 0;
}