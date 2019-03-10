#include<iostream>
using namespace std;
#define MAX 100
template<class T>
class Greate{
public:
	bool operator()(const T& L, const T& R)
	{
		return L > R;
	}
};
	
template<class T>
class Little{
public:
	bool operator()(const T& L, const T& R)
	{
		  return L < R;
	}
};
template<class T,class com>
class Heap
{
public:
	Heap(int size)
		:_size(size)
		,heap(new T[MAX])
	{ }
	void CreatHeap(int* array,int size)
	{
		for (int i = 0; i <size; i++)
		{
			heap[i] = array[i];
		}
		//建堆
		for (int i = (_size - 2) / 2; i >= 0; i--)
		{
			AdjustDown(heap, i);
		}
	}
	void InsertHeap(int num)
	{
		heap[_size] = num;
		_size += 1;
		AdjustUp(heap, _size-1);
	}
	bool EarseHeap()
	{
		if (_size)
		{
			swap(heap[0], heap[_size - 1]);
			_size--;
			AdjustDown(heap, 0);
			return true;
		}
		return false;
	}
	//向下调整
	void AdjustDown(int* h, int root)
	{
		int parent = root;
		int lchild = parent * 2 + 1;
		while (lchild < _size)
		{
			if (lchild + 1 < _size && com(h[lchild+1] , h[lchild]))
				lchild++;
			if (com(h[lchild], h[parent]))
			{
				swap(h[parent], h[lchild]);
				parent = lchild;
				lchild = parent * 2 + 1;
			}
			else
				break;
		}
	}
	//向上调整
	void AdjustUp(int* h, int child)
	{
		int parent = (child - 1) / 2;

		while (parent >= 0)
		{
			if (com(h[child], h[parent]))
			{
				swap(h[child], h[parent]);
				child = parent;
				parent = (child - 1) / 2;
			}
			else
				break;
		}

	}
	void print()
	{
		for (int i = 0; i < _size; i++)
		{
			cout << heap[i] << " ";
		}
		cout << endl;
	}
public:
	T _size;
	T* heap;
	com com;
};

void test()
{
	int array[9] = { 53, 17, 78, 9, 45, 65, 87, 23, 31 };
	Heap<int, Greate<int>> h(9);
	h.CreatHeap(array,9);
	h.print();
	h.InsertHeap(90);
	h.print();
	h.EarseHeap();
	h.print();
}

//Top(K)求前3个最大的，用小堆，要找最大的干掉在榜的最小的
void TopK(int array[],int size,int K)
{
	Heap<int, Little<int>> h1(3);
	h1.CreatHeap(array, 3);
	for (int i = 3; i < size; i++)
	{
		if (array[i]>h1.heap[0])
			h1.heap[0] = array[i];
		h1.AdjustDown(h1.heap, 0);
	}
	h1.print();
}
void testTopK()
{
	int array[] = { 1000, 99, 78, 53, 17, 78, 9, 45, 65, 87, 23, 31 };
	int k = 3;
	TopK(array, sizeof(array) / sizeof(array[0]), k);
}
//堆排序,升序用大堆
void HeapSort(int array[],int size)
{
	Heap<int, Greate<int>> Gheap(size);
	Gheap.CreatHeap(array, size);
	//堆排序
	while (Gheap._size-1)
	{
		swap(Gheap.heap[0], Gheap.heap[Gheap._size - 1]);
		Gheap._size--;
		Gheap.AdjustDown(Gheap.heap,0);
	}
	Gheap._size = size;
	Gheap.print();
}
void test_HeapSort()
{
	int array[] = { 1000, 99, 78, 53, 17, 78, 9, 45, 65, 87, 23, 31 };
	int size = sizeof(array) / sizeof(array[0]);
	HeapSort(array, size);
}