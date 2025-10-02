#include <iostream>
#include <cassert>
#include <list>
#include <string>

namespace Vect {
	// ������
	template <class T>
	struct list_node {
		list_node* _next;
		T _val;

		list_node(const T& val = T())
			:_next(nullptr)
			,_val(val)
		{ }
	};

	// ������
	template <class T>
	class mini_queue {
	private:
		list_node<T>* _head; // ����
		list_node<T>* _tail; // ��β
		size_t _size;

	public:
		// ����
		mini_queue()
			:_head(nullptr)
			,_tail(nullptr)
			,_size(0)
		{ }
		
		// �������죨�����
		mini_queue(const mini_queue& other)
			:_head(nullptr)
			, _tail(nullptr)
			, _size(0)
		{
			// ���� other ������ÿ��Ԫ�ض�����һ��
			list_node<T>* cur = other._head;
			while (cur) {
				enqueue(cur->_val); // �������е� enqueue ʵ��
				cur = cur->_next;
			}
		}

		// ����
		~mini_queue() { clear(); }

		//  ��� β��
		void enqueue(const T& val) {
			list_node<T>* new_node = new list_node<T>(val);
			// �ն��� ��Ԫ�ؼ��Ƕ��� Ҳ�Ƕ�β
			if (_head == nullptr) {
				_head = _tail = new_node;
			}
			else {
				_tail->_next = new_node;
				_tail = new_node;
			}
			++_size;
		}

		// ���� ͷɾ
		void dequeue() {
			assert(!empty());

			// ���浱ǰ���׽ڵ㣨��ɾ����
			list_node<T>* tmp = _head;

			// ����ֻ��һ��Ԫ��
			if (_head == _tail) {
				_head = _tail = nullptr;  // ɾ�����пգ�ͷβ���ÿ�
			}
			else {
				// ���Ԫ�أ�ͷָ����Ƶ���һ���ڵ�
				_head = _head->_next;
			}

			delete tmp;  // ɾ��ԭ���Ķ��׽ڵ�
			--_size;     // ���д�С��1
		}

		// ��ȡ���׶�βԪ��
		const T& front() const { assert(!empty()); return _head->_val; }
		const T& back() const { assert(!empty()); return _tail->_val; }

		// �п�
		const bool empty() const { return _size == 0; }

		// ����Ԫ�ظ���
		const size_t size() const { return _size; }

		// ��ն���
		void clear() { while (!empty()) dequeue(); }

		// ��ӡ����
		void print_queue() {
			if (empty()) {
				std::cout << "�˶���Ϊ��" << std::endl;
				return;
			}

			list_node<T>* cur = _head;
			while (cur) {
				std::cout << cur->_val << " ";
				cur = cur->_next;
			}
			std::cout << std::endl;
		}
	};

	void test_mini_queue() {
		mini_queue<std::string> q;

		std::cout << "===== ���Զ��� =====" << std::endl;

		std::cout << "===== 1. ��������� =====" << std::endl;

		q.enqueue("kunkun");
		q.enqueue("abc");
		q.enqueue("lili");
		q.enqueue("ahha");
		q.print_queue();

		std::cout << "===== 2. ��ȡ��ͷ����βԪ�� =====" << std::endl;
		std::cout << "���ף� " << q.front() << std::endl;
		std::cout << "��β�� " << q.back() << std::endl;

		std::cout << "===== 3. ��ȡ����Ԫ�ظ��� =====" << std::endl;
		std::cout << "����Ԫ�ظ����� " << q.size() << std::endl;


		std::cout << "===== 4. ���Գ����� =====" << std::endl;
		q.dequeue();
		q.dequeue();
		q.print_queue();


		std::cout << "===== 4. ������ն��� =====" << std::endl;
		q.clear();
		if (q.empty()) std::cout << "����������" << std::endl;
		else std::cout << "��������쳣" << std::endl;

	}
}