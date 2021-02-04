#include <iostream>

struct Node {
	int data;
	Node* next;
};

Node* front{nullptr};
void push_front(int value){
	Node* current = new Node;
	current->data = value;
	current->next = front;
	front = current;
}
void push_back(int value) {
	Node* last = front;
	Node* current = new Node;
	current->data = value;
	current->next = nullptr;
	if (last == nullptr) {
		front = current;
	}
	else {
		while (last->next != nullptr) {
			last = last->next;
		}
		last->next = current;
	}
}
void delete_list() {
	Node* first = front;
	if (front != nullptr) { //For more then 0 element
		if (front->next != nullptr){ //For more then 1 element
			Node* second = front->next;
			while (second != nullptr) {
				delete first;
				first = second;
				second = second->next;
			}
		}
		delete first;
	}
}
void pop_front() {
	if (front != nullptr) {
		Node* temp = front;
		if (temp->next != nullptr) {
			temp = temp->next;
		}
		else
			temp = nullptr;
		delete front;
		front = temp;
	}
	else
		std::cout << std::endl << "ERROR: List is already empty" << std::endl;
}
void pop_back() {
	if (front != nullptr) {
		Node* temp = front;
		Node* current{ nullptr };
		if (temp->next != nullptr) {
			while (temp->next->next != nullptr) {
				temp = temp->next;
			}
			current = temp->next;
			delete current;
			temp->next = nullptr;
		}
		else {
			delete front;
			front = nullptr;
		}
	}
	else
		std::cout << std::endl << "ERROR: List is already empty" << std::endl;
}
int delete_elem(int position) {
	if (front != nullptr && position > 0) {
		Node* temp = front;
		Node* current = new Node;
		for (int i{ 1 }; i < position; ++i) {
			if (temp->next == nullptr) {
				std::cout << std::endl << "ERROR: A non-existent position is specified" << std::endl;
				return -1;
			}
			temp = temp->next;
		}
		current = temp->next;
		temp->next = current->next;
		delete current;
		return 0;
	}
	std::cout << std::endl << "ERROR: A non-existent position is specified" << std::endl;
	return -1;
}
int insert_to_position(int position, int value) {
	Node* temp = front;
	if (front != nullptr && position > 0) { //For more then 0 element
		if (front->next != nullptr) { //For more then 1 element
			for (int i{ 2 }; i < position; ++i) {
				if (temp->next == nullptr) {
					std::cout << std::endl << "ERROR: A non-existent position is specified" << std::endl;
					return -1;
				}
				temp = temp->next;
			}
			Node* insert = new Node;
			insert->data = value;
			insert->next = temp->next;
			temp->next = insert;
			return 0;
		}
	}
	std::cout << std::endl << "ERROR: A non-existent position is specified" << std::endl;
	return -1;
}
Node* insert_array(int *array, int size) {
	Node* current{ nullptr };
	Node* arr{ nullptr };
	Node* last { nullptr };
	for (int i{ 0 }; i < size; ++i) {
		current = new Node; 
		current->data = array[i];
		current->next = nullptr;
		if (i == 0) {
			arr = current;
			current = new Node;
			arr->next = current;
			last = arr;
		}
		else {
			last->next = current;
			last = last->next;
		}
	}
	front = arr; //Write to external variable (optional)
	return arr;
}
void nodeOut() { //Output
	for (Node* current{ front }; current != nullptr; current = current->next)
		std::cout << current->data << " ";
}
int main()
{
	using namespace std;
	for (int i{1}; i < 10; ++i) {
		//push_front(i);
		//push_back(i);
	}
	push_front(2);
	const int size = 5;
	int array[size]{5, 25, 0, 79, 222};
	pop_back();
	//pop_front();
	delete_elem(2);
	//insert_to_position(4, 250);
	//insert_array(array, size);
	nodeOut();
	delete_list();
	return 0;
}
