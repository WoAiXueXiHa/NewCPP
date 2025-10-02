#pragma once
#include <iostream>
#include <cassert>
#include <string>

namespace Vect {
	template <class T>
	class circular_queue {
	private:
		T* _arr; // �ײ㶯̬�������
		size_t _front; // ��������
		size_t _rear; // ��β������ָ��������һ��Ԫ�ص���һ��λ��
		size_t _capacity; // ���������� ʵ��ֻ�ܴ洢_capacity - 1��Ԫ��

	
		// ����
		void resize() {
			size_t new_cap = _capacity == 0 ? 4 : 2 * _capacity;
			T* tmp = new T[new_cap];
			
			// ����ԭ����Ԫ�ظ��� ��ֹ���������
			size_t count = (_rear - _front + _capacity) % _capacity;
			size_t cur = _front;
			for (size_t i = 0; i < count; i++)
			{
				tmp[i] = _arr[cur];
				cur = (cur + 1) % _capacity;
			}

			delete[] _arr;
			_arr = tmp;
			_capacity = new_cap;
			_front = 0;
			_rear = count; // �¶��ж�βָ�����һ��Ԫ�ص���һ��λ�ã���Ԥ����λ��������ӻ��Զ�����
		}

	public:
		// ���� 
		circular_queue(size_t capacity = 4)
			:_front(0)
			, _rear(0)
			, _capacity(capacity)
		{
			_arr = new T[_capacity];
		}

		// ��������
		circular_queue(const circular_queue& other)
			:_front(other._front)
			, _rear(other._rear)
			, _capacity(other._capacity)
		{
			_arr = new T[_capacity];
			for (size_t i = 0; i < _capacity; i++)
			{
				_arr[i] = other._arr[i];
			}
		}
		// ���� 
		~circular_queue() {
			delete[] _arr;
			_arr = nullptr;
			_front = _rear = 0;
			_capacity = 0;
		}

		// ��� β��
		void enqueue(const T& val) {
			// �ж��Ƿ�����
			if ((_rear + 1) % _capacity == _front)
				resize();

			_arr[_rear] = val;
			_rear = (_rear + 1) % _capacity;
		}

		// ���� ͷɾ
		void dequeue() {
			// ȷ�����в�Ϊ��
			assert(!empty());
			// ����_front��ָ�򼴿�
			_front = (_front + 1) % _capacity;
		}

		// ��ȡ����Ԫ��
		const T& front() const { assert(!empty()); return _arr[_front]; }

		// ��ȡ��βԪ��
		const T& back() const {
			assert(!empty());
			// ���rear=0�ĸ�������
			size_t tail_idx = (_rear - 1 + _capacity) % _capacity;
			return _arr[tail_idx];
		}

		// �ж϶����Ƿ�Ϊ��
		const bool empty() const { return _front == _rear; }

		// �ж϶����Ƿ�����
		const bool full() const { return (_rear + 1) % _capacity == _front; }

		// ������ЧԪ�ظ���
		const size_t size() const { return (_rear - 1 + _capacity) % _capacity; }

		// �����������
		const size_t capacity() const { return _capacity; }

		// ��ն���
		void clear() { _front = 0; _rear = 0; }

		// ��ӡ����
		void print_circular_queue() {
			if (empty()) {
				std::cout << "����Ϊ��" << "\n";
				return;
			}
			// ����Ԫ�ظ����ٴ�ӡ
			size_t count = size();
			size_t cur = _front;

			for (size_t i = 0; i < count; i++)
			{
				std::cout << _arr[cur] << " ";
				cur = (cur + 1) % _capacity;
			}
			std::cout << "\n";
		}

	};

	void test_circular_queue() {
		std::cout << "===== ������_size��ѭ������ =====" << std::endl;
		circular_queue<std::string> cq(3); // ��ʼ����3������2��Ԫ�أ�Ԥ��1����λ��

		// ����1����ӵ���
		std::cout << "\n1. ��ӵ���������3������2����" << std::endl;
		cq.enqueue("kunkun");
		cq.enqueue("lili");
		cq.print_circular_queue(); // Ԫ�أ�kunkun lili������3��Ԫ����2��
		std::cout << "�����Ƿ�������" << (cq.full() ? "��" : "��") << std::endl; // ��

		// ����2������Ӵ������ݣ����ݺ�����6������5����
		std::cout << "\n2. ����Ӵ������ݣ�������6��" << std::endl;
		cq.enqueue("ahha");
		cq.print_circular_queue(); // Ԫ�أ�kunkun lili ahha������6��Ԫ����3��
		std::cout << "�����Ƿ�������" << (cq.full() ? "��" : "��") << std::endl; // ��

		// ����3������+�п�
		std::cout << "\n3. ����2��+�п�" << std::endl;
		cq.dequeue();
		cq.dequeue();
		cq.print_circular_queue(); // Ԫ�أ�ahha������6��Ԫ����1��
		cq.dequeue();
		std::cout << "�����Ƿ�Ϊ�գ�" << (cq.empty() ? "��" : "��") << std::endl; // ��

		// ����4����������
		std::cout << "\n4. �����������" << std::endl;
		cq.enqueue("xixi");
		circular_queue<std::string> cq2(cq);
		cq2.enqueue("haha");
		std::cout << "ԭ����cq��"; cq.print_circular_queue();  // cq��xixi
		std::cout << "��������cq2��"; cq2.print_circular_queue(); // cq2��xixi haha
	}
}
