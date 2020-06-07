#pragma once

#include<iostream>
#include<conio.h>

// ����� �.�. �8118-09.03.04������(2)

template<typename T>
class MyList {
	/**
	 * ������� ������, �������� ������������� �������� � ��������� �� ��������� �������
	 */
private:
	class elem {
	private:
		T data;
		elem* next;
	public:
		/**
		 * ����������� ����.
		 * @param data - �����, ������� ����� ��������� � ����.
		 * @param next - ��������� �� ��������� ����.
		 */
		elem(T data, elem* next = NULL) {
			this->data = data;
			this->next = next;
		}
		/**
		 * @return �����, ������� �������� ������ �������.
		 */
		T get_data() {
			return this->data;
		}
		/**
		 * @param _data - �����, ������� ����� ��������� � ������ ��������.
		 */
		void set_data(T _data) {
			this->data = _data;
		}
		/**
		 * @return - ��������� �� ��������� ������� ������.
		 */
		elem* getPointer() {
			return this->next;
		}
		/**
		 * @param _next - ����� ��������� �� ��������� �������.
		 */
		void setPointer(elem* _next) {
			this->next = _next;
		}

	};
	/**
	 * ��������� �� ������ ������� ������ (������).
	 */
	elem* head;
public:
	/**
	 * ����������� ������. ���������� ������ �� ������ ����� ���������,
	 * ������� ��������� �� ������ ������ ��������������� �������.
	 */
	MyList() {
		head = NULL;
	}
	/**
	 * ���������� ������. ���� ������ ��������������� ���������, ������� � head.
	 */
	~MyList() {
		elem* temp = head;
		elem* buffer = head;
		while (temp->getPointer() != buffer){
			head = (temp->getPointer());
			delete temp;
			temp = head;
		}
		head = NULL;;
	}
	/**
	 * ���������� �������� � ����� ������.
	 * 1) ���� ������ ����, �� ������ ��������� ���������� ������.
	 * 2) ���� ����� ������� ������ �� ������, �� ������ ����� �������.
	 * 3) � ��������� ������� ������ ����� ������� � ����� ������.
	 *
	 * @param _data - ����� ������� ����� ������� ����� �������.
	 */
	void push(T _data)
	{

		/**
		 * ���� ������ ����, �� _data ��������� � ������ ������, � ������ � ���� ������� ��������� �� ���� ����.
		 */
		if (isEmpty()){
			head = new elem(_data);
			head->setPointer(head);

		}
		/**
		 *  ���� ������ ��������� �� ���� ����, �� ������ ����� ������� ��
		 * ��������� _data � ������� ������ �� ����� �������, � ����� ������� �� ������.
		 */
		else if (head == head->getPointer()) {
			elem* temp = head;
			head = new elem(_data);
			head->setPointer(temp);
			temp->setPointer(head);
			head->set_data(temp->get_data());
			temp->set_data(_data);
		}

		/**
		 * � ��������� ������� ������ ����� ������� � ����� ������.
		 */
		else {
			elem* temp = head; //���������� ������ �� ������ ������ ������
			head = new elem(_data); // ������ ����� ������ �� ��������� _data
			head->setPointer(temp->getPointer()); //������� ������ �� ������ ������� ������
			int a = temp->get_data(); // ��������� ����� �� ������ ������ ������ ������
			temp->set_data(head->get_data()); //�������� ��������, ���������� � ������ ������ ������ ������ �� _data
			head->set_data(a); // ���������� � ����� ������ �������� ������
			temp->setPointer(head); // ������� ������ ������ ������ �� ����� ������

		}
	}
	/**
	 * @return true, ���� ������ - ������, ����� - false.
	 */
	bool isEmpty() {
		return head == NULL;
	}
	/**
	 * @return ������� ���������� ��������� ������.
	 */
	int get_size()
	{
		if (isEmpty()) return 0;
		else {
			elem* temp = head;
			int i = 1;
			while (temp->getPointer() != head) {
				temp = temp->getPointer();
				i++;
			}
			return i;
		}
	}
	
	void Delete(T data) {
		elem* temp = head;
		elem* buffer;
		int i = 0;
		int size = this->get_size();
		if (size == 1 && temp->get_data() == data) {
			delete temp;
			head = NULL;
		}
		while (i < size) {
			i++;
			if (temp->get_data() == data) {
				buffer = temp->getPointer();
				temp->set_data(buffer->get_data());
				temp->setPointer(buffer->getPointer());
				delete buffer;
			}
			temp = temp->getPointer();
		}
	}
	/**
	 *������� �������� �������
	 * @param number - ����� ���������� ��������
	 */
	void DeleteByIndex(T number) {
		if (number < get_size()-1 && number>=0){  //���� �������� ������� �� ���������
			int i = 0;
			elem* temp = head;
			while (i != number)	{
				temp = temp->getPointer();
				i++;
			}
			elem* buffer = temp->getPointer();
			temp->setPointer(buffer->getPointer());
			temp->set_data(buffer->get_data());
			delete buffer;
		}
		else
			if (number == get_size()-1){//���� �������� ������� ���������
			
				int i = 0;
				elem* temp = head;
				while (i != number){
					temp = temp->getPointer();
					i++;
				}
				elem* buffer = temp->getPointer();
				temp->setPointer(buffer->getPointer());
				temp->set_data(buffer->get_data());
				head = temp;
				delete buffer;
			}
	}
	 
	/*T* Find(T t) {
		elem* temp = head; 
		i = 0;
		while (i < this->get_size()) {
			i++;
			if(temp->get_data()==t)
				return    
		}
	}*/
};
