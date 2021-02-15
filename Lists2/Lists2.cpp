#include <iostream>

struct Node {
	int data;
	Node* prev;
	Node* next;
};

Node* front{ nullptr };
void push_front(int value) {
	Node* current = new Node;
	current->data = value;
	current->next = front;
	current->prev = nullptr;
	front = current;
}
void push_back(int value) {
	Node* last = front;
	Node* current = new Node;
	current->data = value;
	current->next = nullptr;
	if (last == nullptr) {
		current->prev = nullptr;
		front = current;
	}
	else {
		while (last->next != nullptr) {
			last = last->next;
		}
		last->next = current;
		current->prev = last;
	}
}
void delete_list() {
	Node* last = front;
	if (front != nullptr) { //For more then 0 element
		while (last->next != nullptr) {
			last = last->next;
		}
		while (last->prev != nullptr) {
			last = last->prev;
			delete last->next;
		}
		delete last;
	}
	front = nullptr;
}
void pop_front() {
	if (front == nullptr)
		throw std::exception("ERROR: List is already empty");
	Node* temp = front;
	if (temp->next != nullptr) {
		temp = temp->next;
		temp->prev = nullptr;
	}
	else
		temp = nullptr;
	delete front;
	front = temp;
}
void pop_back() {
	if (front == nullptr)
		throw std::exception("ERROR: List is already empty");
	Node* temp = front;
	Node* current{ nullptr };
	if (temp->next != nullptr) {
		while (temp->next != nullptr) {
			temp = temp->next;
		}
		current = temp->prev;
		current->next = nullptr;
		delete temp;
	}
	else {
		delete front;
		front = nullptr;
	}
}
void delete_elem(int position) {
	if (front == nullptr || position < 1)
		throw std::exception("ERROR: A non-existent position is specified");
	Node* temp = front;
	Node* current = new Node;
	for (int i{ 1 }; i < position; ++i) {
		if (temp->next == nullptr) {
			if (front == nullptr || position < 1)
				throw std::exception("ERROR: A non-existent position is specified");
		}
		temp = temp->next;
	}
	current = temp->next;
	temp->next = temp->next->next;
	temp->next->prev = temp;
	delete current;
}
void insert_to_position(int position, int value) {
	if (front == nullptr || position < 1)
		throw std::exception("ERROR: A non-existent position is specified");
	Node* temp = front;
	if (front != nullptr && position > 0) { //For more then 0 element
		if (front->next != nullptr) { //For more then 1 element
			for (int i{ 2 }; i < position; ++i) {
				if (temp->next == nullptr) {
					throw std::exception("ERROR: A non-existent position is specified");
				}
				temp = temp->next;
			}
			Node* insert = new Node;
			insert->data = value;
			insert->next = temp->next;
			insert->prev = temp;
			temp->next = insert;
		}
	}
}
Node* insert_array(int* array, int size) {
	Node* current{ nullptr };
	Node* arr{ nullptr };
	Node* last{ nullptr };
	for (int i{ 0 }; i < size; ++i) {
		current = new Node;
		current->data = array[i];
		current->next = nullptr;
		if (i == 0) {
			current->prev = nullptr;
			arr = current;
			current = new Node;
			arr->next = current;
			last = arr;
		}
		else {
			current->prev = last;
			last->next = current;
			last = current;
		}
	}
	front = arr; //Write to external variable (optional)
	return arr;
}
void nodeOut() { //Output
	for (Node* current{ front }; current != nullptr; current = current->next)
		std::cout << current->data << " ";
	std::cout << std::endl;
}
void swap(int i, int j) {
	if (i > j) { //i<j
		int temp{ 0 };
		temp = i;
		i = j;
		j = temp;
	}
	if (i < 1)
		throw std::exception("ERROR: A non-existent position is specified");
	if (i < j) {
		Node* current = front;
		Node* temp = front;
		for (int k{ 1 }; k < i; ++k) {
			if (current->next == nullptr)
				throw std::exception("ERROR: A non-existent position is specified");
			current = current->next;
		}
		Node* first = current;
		if (i > 1)
			first->prev->next = first->next;
		else
			front = first->next;
		first->next->prev = first->prev;
		//избавился от first в цепи
		for (int k{ i }; k < j; ++k) {
			if (current->next == nullptr)
				throw std::exception("ERROR: A non-existent position is specified");
			current = current->next;
		}
		Node* second = current;
		if (second->prev != nullptr)
			second->prev->next = second->next;
		else
			front = second->next;
		if (second->next != nullptr)
			second->next->prev = second->prev;
		//избавился от second в цепи
		first->next = second->next;
		first->prev = second->prev;
		if (i > 1)
			first->prev->next = first;
		else
			front = first;
		if (first->next != nullptr)
			first->next->prev = first;
		//first поместил на место second
		current = front;
		for (int k{ 1 }; k < i; ++k) {
			if (current->next == nullptr)
				throw std::exception("ERROR: A non-existent position is specified");
			current = current->next;
		}
		//Повторно прохожу список и встаю на бывшее место first
		second->next = current;
		if (i > 1) {
			current->prev->next = second;
			second->prev = current->prev->prev;
		}
		else {
			front = second;
			second->prev = nullptr;
		}
		current->prev = second;
		//Помещаю second на место first
	}
}
int main()
{
	using namespace std;
	for (int i{ 1 }; i < 10; ++i) {
		//push_front(i);
		push_back(i);
	}
	//delete_list();
	//push_front(2);
	const int size = 5;
	int array[size]{ 5, 25, 0, 79, 222 };
	pop_back();
	pop_front();
	delete_elem(2);
	insert_to_position(6, 250);
	//insert_array(array, size);
	//nodeOut();
	//swap(4, 5);
	nodeOut();
	delete_list();
	return 0;
}