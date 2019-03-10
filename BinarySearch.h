#include<iostream>
using namespace std;

template<class T>
struct TreeNode
{
	TreeNode(int& num)
		:data(num)
		, left(NULL)
		, right(NULL)
	{}
	T data;
	TreeNode* left;
	TreeNode* right;
};

template<class T>
class BinarySearch
{
public:
	typedef TreeNode<T> Node;
	BinarySearch()
	:root(NULL)
	{}
	//插入
	bool Insert(T& num)
	{
		if (root == NULL)
		{
			root = new Node(num);
			return true;
		}
		else
		{
			Node* temp = new Node(num);
			Node* cur = root;
			Node* parent = cur;
			while (cur)
			{
				parent = cur;
				if (cur->data > num)
					cur = cur->left;
				else if (cur->data < num)
					cur = cur->right;
				else
					return false;
			}
			if (parent->data < num)
				parent->right = temp;
			else
				parent->left = temp;
			return true;
		}
	}
	Node* Find(T key)//非递归查找
	{
		Node* cur = root;
		if (cur == nullptr)
			return cur;
		while (cur)
		{
			if (cur->data == key)
				return cur;
			else if (cur->data > key)
				cur = cur->left;
			else
				cur = cur->right;
		}
		return cur;
	}
	bool NRSearch(T key)//非递归的搜索
	{
		if (root == NULL)
			return false;
		Node* cur = root;
		while (cur)
		{
			if (cur->data == key)
				return true;
			else if (cur->data > key)
				cur = cur->left;
			else
				cur = cur->right;
		}
		return false;
	}
	bool RSearch(T key)//递归搜索
	{
		Node* cur = root;
		return _RSearch(cur,key);
	}
	int NBSearch(T key)//非bool的递归搜索,0为找到，-1为没找到
	{
		Node* cur = root;
		return _NBSearch(cur, key);
	}
	void print()
	{
		Node* cur = root;
		_print(cur);
		cout << endl;
	}
	bool NRErase(T key)//非递归删除
	{
		//1.查找
		//左为空、右为空、左右都不为空
		Node* cur = root;
		Node* parent = NULL;
		//找要删除的节点
		while (cur)
		{
			if (cur->data == key)
				break;
			parent = cur;
			if (cur->data > key)
				cur = cur->left;
			else
				cur = cur->right;
		}
		if (cur == NULL)
			return false;
		//左为空
		else if (cur->left == NULL)
		{
			if (parent == NULL)
			{
				root = cur->right;
				delete cur;
			}
			else
			{
				if (parent->left == cur)
					parent->left = cur->right;
				else
					parent->right = cur->right;
				delete cur;
			}
		}
		//右为空
		else if (cur->right == NULL)
		{
			if (parent == NULL)
			{
				root = cur->left;
				delete cur;
			}
			else
			{
				if (parent->left == cur)
					parent->left = cur->left;
				else
					parent->right = cur->left;
			}
		}
		//左右都不为空，找左树的最大孩子
		//替换法删除
		else
		{
			Node* del = cur->left;
			Node* delparent = NULL;
			while (del->right)//找左树的最大孩子
			{
				delparent = del;
				del = del->right;
			}
			cur->data = del->data;
			if (delparent == NULL)
			{
				cur->left = del->left;
				delete del;
			}
			else
				delparent->right = del->left;
		}
		return true;
	}
	bool RErase(T key)//递归删除
	{
		Node* cur = root;
		return _RErase(cur,key);
	}
	bool _RErase(Node* root, T key)
	{
		if (root == NULL)
			return false;
		if (key < root->data)
			return _RErase(root->left, key);
		else if (key>root->data)
			return _RErase(root->right, key);
		else
		{
			Node* cur = root;
			//左为空
			if (cur->left == NULL)
			{
				root = cur->right;
			}
			//右为空
			else if (root->right == NULL)
			{
				root = cur->left;
			}
			//左右不为空
			else
			{
				Node* del = cur->right;
				Node* delparent = NULL;
				//找右孩子最小孩子
				while (del->left)
				{
					delparent = del;
					del = del->left;
				}
				//替换删除
				cur->data = del->data;
				if (delparent == NULL)
				{
					cur->right = del->right;
				}
				else
				{
					delparent->left = del->right;
				}

			}
			return true;
		}
	}
private:
	bool _RSearch(Node* root, T key)//递归搜索
	{
		if (root == NULL)
			return false;
		if (root->data == key)
			return true;
		else
			return _RSearch(root->left, key) || _RSearch(root->right, key);
	}
	int _NBSearch(Node* root, T key)//非bool的递归搜索
	{
		if (root == NULL)
			return -1;
		if (root->data == key)
			return 0;
		else
			return 0-abs(_NBSearch(root->left, key) && _NBSearch(root->right, key));
	}
	void _print(Node* cur)
	{
		if (cur == NULL)
			return;
		_print(cur->left);
		cout << cur->data << " ";
		_print(cur->right);
	}
	Node* root;
};

void test_saerch()
{
	int array[] = { 10, 19, 8, 16, 5, 2, 1, 98, 30 };
	BinarySearch<int> b;
	for (int i = 0; i < sizeof(array) / sizeof(array[0]); i++)
	{
		b.Insert(array[i]);
	}
	b.print();
	cout << b.NRSearch(98) << endl;
	cout << b.NRSearch(0) << endl;
	cout << b.RSearch(98) << endl;
	cout << b.RSearch(0) << endl;
	cout << b.NBSearch(98) << endl;
	cout << b.NBSearch(0) << endl;
}
void test_Earse()
{
	int array[] = {5,3,8,1,4,6,9,2,7};
	BinarySearch<int> c;
	for (int i = 0; i < sizeof(array) / sizeof(array[0]); i++)
	{
		c.Insert(array[i]);
	}
	/*cout << c.NRErase(5) << endl;
	c.print();
	cout << c.NRErase(4) << endl;
	c.print();
	cout << c.NRErase(3) << endl;
	c.print();*/
	cout << c.RErase(5) << endl;
	c.print();
	cout << c.RErase(4) << endl;
	c.print();
	cout << c.RErase(3) << endl;
	c.print();
	if (c.Find(7))
		cout << "find 7 in tree" << endl;
}