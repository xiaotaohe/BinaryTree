#pragma once
#include <iostream>
using namespace std;
enum opiontertig{LINK,THREAD};

template<class T>
struct ThreadBanaryNode
{
	T data;
	struct ThreadBanaryNode* left;
	struct ThreadBanaryNode* right;
	opiontertig ltig,rtig;
	ThreadBanaryNode(const T& data)
		:data(data)
		,left(NULL)
		,right(NULL)
		,ltig(LINK)
		,rtig(LINK)
	{}
};



//迭代器
template<class T, class Ref, class Ptr>
class Iterator{
public:
	typedef ThreadBanaryNode<T> Node;
	typedef Iterator<T, Ref, Ptr> self;
	Iterator(Node* node)
		:node(node)
	{}
	Ref operator*()
	{
		return node->data;
	}
	Ptr operator->()
	{
		return node;
	}
	bool operator!=(const self& s)
	{
		return this->node != s.node;
	}
	bool operator ==(const self& s)
	{
		return this->node == s.node;
	}
	Node* node;
};

//前序线索化,迭代器
template<class T,class Ref,class Ptr>
class PreIterator : public Iterator<T,Ref,Ptr>
{
public:
	typedef PreIterator<T, Ref, Ptr> self;

	PreIterator(Node* node)
		:Iterator(node)
	{}
	self& operator++()//后置加加
	{
		if (node->ltig == LINK)
			node = node->left;
		else
			node = node->right;
		return *this;
	}
};
//中序线索化的迭代器
template<class T,class Ref,class Ptr>
class InIterator : public Iterator<T, Ref, Ptr>
{
public:
	typedef InIterator<T, Ref, Ptr> self;
	InIterator(Node* node)
		:Iterator(node)
	{}
	self& operator++()
	{
		if (node->rtig == THREAD)
			node = node->right;
		else
		{
			node = node->right;
			while (node->ltig == LINK)
			{
				node = node->left;
			}
		}
		return *this;
	}
};
template<class T>
class ThreadBanaryTree
{
public:
	typedef ThreadBanaryNode<T> Node;
	typedef PreIterator<T, T&, T*> PreIterator;
	typedef InIterator<T, T&, T*> InIterator;
	ThreadBanaryTree(T* a,size_t size, const T& invilad)
		:root(NULL)
	{
		size_t index = 0;
		root = CreateTree(a,size,index,invilad);
	}
	void InOrder()
	{
		_InOrder(root);
		cout<<endl;
	}


	void InThread()//中序线索化
	{
		Node* pre = NULL;
		_InThread(root,pre);
		pre->rtig = THREAD;//最后一个线索化
	}


	void InOrderThread()//中序线索化遍历
	{
		Node* cur = root;
		while(cur)
		{
			//在左子树中找第一个要访问的
			while(cur->ltig == LINK)
			{
				cur = cur->left;
				if(cur == NULL)
					break;
			}
			cout<<cur->data<<" ";
			//从第一个开始访问如果有子树为线索直接访问
			//如果是空，说明走到终点
			//如果是link是子问题
			while(cur -> rtig == THREAD)
			{
				cur = cur->right;
				if(cur == NULL)
					break;
				cout<<cur->data<<" ";
			}
			//子问题
			if(cur)
				cur = cur->right;
		}
		cout<<endl;
	}


	void PreThread()//前序线索化
	{
		Node* pre = NULL;
		_PreThread(root,pre);
		pre->rtig = THREAD;
	}


	void PreOrderThread()//前序线索化访问
	{
		Node* cur = root;
		//前序先访问做孩子
		//知道最后一个thread，即它的又孩子为接下来要访问的
		while(cur)
		{
			while(cur ->ltig == LINK)
			{
				cout<<cur->data<<" ";
				cur = cur->left;
			}
			cout<<cur->data<<" ";
			cur = cur->right;
			//while(cur->rtig == THREAD)//这段会跳过右子树中rtig == link的
			//{
			//	cur = cur->right;
			//	if(cur == NULL)
			//		break;
			//	cout<<cur->data<<" ";
			//}
			////子问题
			//if(cur)
			//	cur = cur = cur->right;
		}
		cout<<endl;
	}
	PreIterator PreBegin()
	{
		return PreIterator(root);
	}
	PreIterator PreEnd()
	{
		return PreIterator(NULL);
	}
	InIterator InBegin()
	{
		Node* left = root;
		while (left&&left->ltig == LINK)
		{
			left = left->left;
		}
		return InIterator(left);
	}
	InIterator InEnd()
	{
		return InIterator(NULL);
	}
private:
	Node* CreateTree(T* a,size_t size,size_t& index,const T& invilad )
	{
		Node* root = NULL;
		if(index<size&&a[index]!=invilad)
		{
			root = new Node(a[index]);
			root->left = CreateTree(a,size,++index,invilad);
			root->right = CreateTree(a,size,++index,invilad);
		}
		return root;
	}


	void _InOrder(Node* root)
	{
		if(root == NULL)
			return;
		_InOrder(root->left);
		cout<<root->data<<" ";
		_InOrder(root->right);
	}


	void _InThread(Node* root,Node*& pre)//中序线索化
	{
		if(root == NULL)
			return;
		_InThread(root->left,pre);
		if(root->left == NULL)
		{
			root->ltig = THREAD;
			root->left = pre;
		}
		if(pre&&pre->right == NULL)
		{
			pre->right = root;
			pre->rtig = THREAD;
		}
		pre = root;
		_InThread(root->right,pre);
	}


	void _PreThread(Node* root,Node*& pre)//前序线索化
	{
		if(root == NULL) return;
		if(root->left == NULL)//root前驱线索化
		{
			root->left = pre;
			root->ltig = THREAD;
		}
		if(pre&&pre->right == NULL)//pre后继线索化
		{
			pre->right = root;
			pre->rtig = THREAD;
		}
		pre = root;
		if (root->ltig == LINK)
			_PreThread(root->left,pre);
		if (root->rtig == LINK)
			_PreThread(root->right,pre);
	}
private:
	Node* root;
};
void testThreadBanaryTree()
{
	int a[10] = {1,2,'#',4,'#','#',7,8,'#',10};
	ThreadBanaryTree<int> b(a,sizeof(a)/sizeof(a[0]),'#');
	/*b.InOrder();
	b.InThread();
	b.InOrderThread();*/
	b.PreThread();
	b.PreOrderThread();
	ThreadBanaryTree<int> ::PreIterator it = b.PreBegin();//前序线索化的迭代器
	while (it != b.PreEnd())
	{
		cout << *it << " ";
		it++;
	}
	cout << endl;
	b.InOrder();
	b.InThread();
	b.InOrderThread();
	ThreadBanaryTree<int> ::InIterator it2 = b.InBegin();
	while (it2 != b.InEnd())
	{
		cout << *it2 << " ";
		it2++;
	}
	cout << endl;
}
