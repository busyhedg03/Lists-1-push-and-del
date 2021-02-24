#include <iostream>
template <typename T>
struct Node {
	T data;
	Node* next;
};
template <typename T>
Node<T>* front{ nullptr };
template <typename T>
void push_front(T value) {
	Node<T>* current = new Node<T>;
	current->data = value;
	current->next = front<T>;
	front<T> = current;
}
template <typename T>
void push_back(T value) {
	Node<T>* last = front<T>;
	Node<T>* current = new Node<T>;
	current->data = value;
	current->next = nullptr;
	if (last == nullptr) {
		front<T> = current;
	}
	else {
		while (last->next != nullptr) {
			last = last->next;
		}
		last->next = current;
	}
}
template <typename T>
void delete_list() {
	Node<T>* first = front<T>;
	if (front<T> != nullptr) { //For more then 0 element
		if (front<T>->next != nullptr) { //For more then 1 element
			Node<T>* second = front<T>->next;
			while (second != nullptr) {
				delete first;
				first = second;
				second = second->next;
			}
		}
		delete first;
	}
	front<T> = nullptr;
}
template <typename T>
void pop_front() {
	if (front<T> != nullptr) {
		Node<T>* temp = front<T>;
		if (temp->next != nullptr) {
			temp = temp->next;
		}
		else
			temp = nullptr;
		delete front;
		front<T> = temp;
	}
	else
		throw std::exception("ERROR: List is already empty");
}
template <typename T>
void pop_back() {
	if (front<T> != nullptr) {
		Node<T>* temp = front<T>;
		Node<T>* current{ nullptr };
		if (temp->next != nullptr) {
			while (temp->next->next != nullptr) {
				temp = temp->next;
			}
			current = temp->next;
			delete current;
			temp->next = nullptr;
		}
		else {
			delete front<T>;
			front<T> = nullptr;
		}
	}
	else
		throw std::exception("ERROR: List is already empty");
}
template <typename T>
void delete_elem(int position) {
	if (front<T> == nullptr || position < 1)
		throw std::exception("ERROR: A non-existent position is specified");
	Node<T>* temp = front<T>;
	Node<T>* current = new Node<T>;
	for (int i{ 1 }; i < position; ++i) {
		if (temp->next == nullptr)
			throw std::exception("ERROR: A non-existent position is specified");
		temp = temp->next;
	}
	current = temp->next;
	temp->next = current->next;
	delete current;
}
template <typename T>
void insert_to_position(int position, T value) {
	Node<T>* temp = front<T>;
	if (position < 1)
		throw std::exception("ERROR: A non-existent position is specified");
	Node<T>* insert = new Node<T>;
	insert->data = value;
	if (front<T> != nullptr) { //For more then 0 element
		if (front<T>->next != nullptr) { //For more then 1 element
			for (int i{ 2 }; i < position; ++i) {
				if (temp->next == nullptr) {
					throw std::exception("ERROR: A non-existent position is specified");
				}
				temp = temp->next;
			}
			insert->next = temp->next;
			temp->next = insert;
		}
	}
	else {
		front<T> = insert;
		front<T>->next = nullptr;
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
			arr = current;
			current = new Node<T>;
			arr->next = current;
			last = arr;
		}
		else {
			last->next = current;
			last = last->next;
		}
	}
	front<T> = arr; //Write to external variable (optional)
	return arr;
}
template <typename T>
void nodeOut() { //Output
	for (Node<T>* current{ front<T> }; current != nullptr; current = current->next)
		std::cout << current->data << " ";
}
int main()
{
	using namespace std;
	for (int i{ 1 }; i < 10; ++i) {
		//push_front(i);
		push_back<int>(i);
	}
	/*push_front<int>(2);
	const int size = 5;
	int array[size]{5, 25, 0, 79, 222};*/
	//pop_back();
	//pop_front();
	delete_elem<int>(2);
	insert_to_position<int>(1, 250);
	//insert_array<int>(array, size);
	nodeOut<int>();
	delete_list<int>();
	return 0;
}