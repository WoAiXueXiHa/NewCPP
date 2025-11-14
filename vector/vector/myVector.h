#pragma once
#include <iostream>
using namespace std;

namespace myVector {

	class DArray{
	private:
		double* m_Data = nullptr;  // 动态数组指针
		int m_Size = 0;            // 当前元素个数
		int m_Max = 0;             // 当前分配的容量

	private:
		inline bool InvalidateIndex(int nIndex)	{ return nIndex < 0 || nIndex >= m_Size; }

	public:

		DArray() = default;

		DArray(int nSize, double dValue = 0)
			: m_Size(0),
			m_Max(0), 
			m_Data(nullptr)
		{
			for (int i = 0; i < nSize; i++) {
				PushBack(dValue);
			}
		}

		DArray(const DArray& arr){
			m_Max = arr.m_Max;
			m_Size = arr.m_Size;
			m_Data = nullptr;

			if (m_Max > 0){
				m_Data = new double[m_Max];
				for (int i = 0; i < m_Size; i++) {
					m_Data[i] = arr.m_Data[i];
				}
			}
		}

		DArray& operator=(const DArray& arr){
			if (this == &arr) return *this;

			if (m_Max > 0) delete[] m_Data;

			m_Max = arr.m_Max;
			m_Size = arr.m_Size;

			if (m_Max > 0){
				m_Data = new double[m_Max];
				for (int i = 0; i < m_Size; i++)
					m_Data[i] = arr.m_Data[i];
			}
			else{
				m_Data = nullptr;
			}

			return *this;
		}

		~DArray() { if (m_Max > 0) delete[] m_Data; }

		void Print(){
			for (int i = 0; i < m_Size; i++) {
				cout << m_Data[i] << " ";
			}
			cout << endl;
		}

		int GetSize(){
			return m_Size;
		}

		void SetSize(int nSize){
			if (nSize <= 0){
				if (m_Max > 0) delete[] m_Data;

				m_Data = nullptr;
				m_Size = 0;
				m_Max = 0;
				return;
			}

			if (nSize <= m_Max){
				if (nSize > m_Size){
					for (int i = m_Size; i < nSize; i++) {
						m_Data[i] = 0;
					}
				}
				m_Size = nSize;
				return;
			}

			// 扩容
			double* newData = new double[nSize];
			for (int i = 0; i < m_Size; i++) {
				newData[i] = m_Data[i];
			}
			for (int i = m_Size; i < nSize; i++) {
				newData[i] = 0;
			}

			if (m_Max > 0) delete[] m_Data;

			m_Data = newData;
			m_Size = nSize;
			m_Max = nSize;
		}

		double GetAt(int nIndex){
			if (InvalidateIndex(nIndex)) return 0;
			return m_Data[nIndex];
		}

		void SetAt(int nIndex, double dValue){
			if (!InvalidateIndex(nIndex))
				m_Data[nIndex] = dValue;
		}

		void PushBack(double dValue){
			if (m_Size == m_Max){
				int newMax = (m_Max == 0 ? 1 : m_Max * 2);
				SetSize(newMax);
				m_Size--; 
			}

			m_Data[m_Size++] = dValue;
		}

		void DeleteAt(int nIndex){
			if (InvalidateIndex(nIndex)) return;

			for (int i = nIndex; i < m_Size - 1; i++) {
				m_Data[i] = m_Data[i + 1];
			}

			m_Size--;
		}

		void InsertAt(int nIndex, double dValue){
			if (nIndex < 0) nIndex = 0;
			if (nIndex > m_Size) nIndex = m_Size;

			if (m_Size == m_Max){
				int newMax = (m_Max == 0 ? 1 : m_Max * 2);
				SetSize(newMax);
				m_Size--;
			}

			for (int i = m_Size; i > nIndex; i--) {
				m_Data[i] = m_Data[i - 1];
			}

			m_Data[nIndex] = dValue;
			m_Size++;
		}

		double operator[](int nIndex) const{ return m_Data[nIndex]; }
	};

	void TestDArray(){
		cout << "-----  开始测试  -----" << endl;

		DArray arr;
		arr.PushBack(1.1);
		arr.PushBack(2.2);
		arr.PushBack(3.3);

		cout << "初始: ";
		arr.Print();

		arr.InsertAt(1, 9.9);
		cout << "插入 9.9: ";
		arr.Print();

		arr.DeleteAt(2);
		cout << "删除下标 2: ";
		arr.Print();

		arr.SetAt(1, 5.5);
		cout << "SetAt(1,5.5): ";
		arr.Print();

		cout << "arr[0] = " << arr[0] << endl;

		DArray b = arr; 
		cout << "拷贝构造 b: ";
		b.Print();

		DArray c;
		c = arr;       
		cout << "拷贝赋值 c: ";
		c.Print();

	}
}
