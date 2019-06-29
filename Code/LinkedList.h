#ifndef LinkedList_H
#define LinkedList_H

#include <iostream>
using namespace std;

template <typename T>
struct Node{
	T data;
	Node<T>* next;
};

template <typename T>
class LinkedList{
	private:
		Node<T>* head;
		Node<T>* tail;
	public:
		LinkedList();
		~LinkedList();
		T getData(int index);
		void addNode(T input);
		void editNode(int index, T data);
		void deleteNode(int index);
		
		class Iterator{
			public:
				Node<T>* current;
				
				Iterator(){
					this->current = NULL;
				}
				
				Iterator(Node<T>* n){
					current = n;
				}
				
				T& operator*() const{
					return current->data;
				}
			
				Iterator operator++(int){
					current = current->next;
					return *this;
				}
				
				Iterator operator--(int){
					current = current->prev;
					return *this;
				}
				
				bool operator!=(const Iterator &right){
					return current != right.current;
				}			
		};
		
		Iterator begin(){
			return Iterator(this->head);
		}
		
		Iterator end(){
			return Iterator(NULL);
		}
};

template <typename T>
LinkedList<T>::LinkedList(){
	head = tail = NULL;
}

template <typename T>
LinkedList<T>::~LinkedList(){
	Node<T>* temp;
	while (head != NULL){
		temp = head;
		head = head->next;
		delete temp;
	}
}

template <typename T>
T LinkedList<T>::getData(int index){
	Node<T>* temp;
	temp = head;
	if (index == 0){
		return head->data;
	} else {
		for (int i = 0; i < index; i++){
			temp = temp->next;
		}
		return temp->data;
	}
}

template <typename T>
void LinkedList<T>::addNode(T input){
	Node<T>* newnode = new Node<T>;
	newnode->data = input;
	newnode->next = NULL;
	
	if (head == NULL){
		head = tail = newnode;
	} else {
		tail->next = newnode;
		tail = newnode;
	}
}

template <typename T>
void LinkedList<T>::editNode(int index, T data){
	Node<T>* temp;
	temp = head;
	int counter = 0;
	
	if (index == 0){
		head->data = data;	
	} else {
		for (int i = 0; i < index; i++){
			temp = temp->next;
		}
		temp->data = data;
	}
}


template <typename T>
void LinkedList<T>::deleteNode(int index){
	Node<T>* temp;
	temp = head;
	
	if (index == 0){
		head = head->next;
		delete temp;
	} else {
		for (int i = 0; i < index-1; i++){
			temp = temp->next;
		}
		Node<T>* target = temp->next;
		if (target->next == NULL){
			tail = temp;
			temp->next = NULL;
			delete target;
		} else {
			temp->next = target->next;
			delete target;
		}
	}
}

#endif
