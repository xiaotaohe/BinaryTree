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
	//����
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
	Node* Find(T key)//�ǵݹ����
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
	bool NRSearch(T key)//�ǵݹ������
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
	bool RSearch(T key)//�ݹ�����
	{
		Node* cur = root;
		return _RSearch(cur,key);
	}
	int NBSearch(T key)//��bool�ĵݹ�����,0Ϊ�ҵ���-1Ϊû�ҵ�
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
	bool NRErase(T key)//�ǵݹ�ɾ��
	{
		//1.����
		//��Ϊ�ա���Ϊ�ա����Ҷ���Ϊ��
		Node* cur = root;
		Node* parent = NULL;
		//��Ҫɾ���Ľڵ�
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
		//��Ϊ��
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
		//��Ϊ��
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
		//���Ҷ���Ϊ�գ��������������
		//�滻��ɾ��
		else
		{
			Node* del = cur->left;
			Node* delparent = NULL;
			while (del->right)//�������������
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
	bool RErase(T key)//�ݹ�ɾ��
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
			//��Ϊ��
			if (cur->left == NULL)
			{
				root = cur->right;
			}
			//��Ϊ��
			else if (root->right == NULL)
			{
				root = cur->left;
			}
			//���Ҳ�Ϊ��
			else
			{
				Node* del = cur->right;
				Node* delparent = NULL;
				//���Һ�����С����
				while (del->left)
				{
					delparent = del;
					del = del->left;
				}
				//�滻ɾ��
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
	bool _RSearch(Node* root, T key)//�ݹ�����
	{
		if (root == NULL)
			return false;
		if (root->data == key)
			return true;
		else
			return _RSearch(root->left, key) || _RSearch(root->right, key);
	}
	int _NBSearch(Node* root, T key)//��bool�ĵݹ�����
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