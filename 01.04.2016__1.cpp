#include <iostream>

<<<<<<< HEAD
//class List;
//template <typename T>
=======
//template <typename T>
//class List;
>>>>>>> 78b930d2fed11c63cb0209fddb7a26e614ff3757

template <class TNode>
class Iterator
{
	/* Helper class to provide pointer like facilities around a node */
	friend class List<typename TNode::value_type>;
	TNode* pNode;

	Iterator(TNode* _pNode) : pNode(_pNode) {}
public:
<<<<<<< HEAD
	
=======
>>>>>>> 78b930d2fed11c63cb0209fddb7a26e614ff3757
	//operators
};

template <typename T>
class Node
{
	friend class List<T>;
	friend class Iterator<Node<T> >;
private:
	T data;
	T* next;
	T* prev;
public:
	typedef T value_type;

	Node()
	{
		data = new value_type;
		next = NULL;
		prev = NULL;
	}

	~Node()
	{
		delete value_type;
	}
};

template <typename T>
class List
{
	Node<T>* first;
	Node<T>* last;

public:
	typedef Iterator<Node<T>> iterator;
	typedef T value_type;

	List()
	{
		first = new Node<value_type>();
		last = NULL;
	}

	void push_back(T data)
	{
		if (last = NULL)
		{
			first.data = data;
			last = first;
		}
		else if (last == first)
		{
			last = new Node<value_type>();
			last.data = data;
<<<<<<< HEAD
			last.prev = firs;
=======
>>>>>>> 78b930d2fed11c63cb0209fddb7a26e614ff3757
			first.next = last;
		}
		else
		{
			Node<value_type>* new_node = new Node<value_type>();
			last.next = new_node;
			new_node.data = data;
<<<<<<< HEAD
			new_node.prev = last;
			last = new_node;
=======
>>>>>>> 78b930d2fed11c63cb0209fddb7a26e614ff3757
		}
	};

	void push_front(T data)
	{
		if (last = NULL)
		{
			first.data = data;
			last = first;
		}
		else if (last == first)
		{
			first = new Node<value_type>();
			first.data = data;
			last.prev = first;
		}
		else
		{
<<<<<<< HEAD
			Node<value_type>* new_node = new Node<value_type>();
			new_node.data = data;
			new_node.next = first;
			first.prev = new_node;
			first = new_node;
=======
			
>>>>>>> 78b930d2fed11c63cb0209fddb7a26e614ff3757
		}
	}

	iterator begin(){}
	iterator end(){}

	bool erase(iterator& _iNode) //True for success, vice versa
	{

	}

	~List()
	{
		while (first.next != NULL)
		{
			Node<T>* new_first = first;
			first = first.next;
			delete new_first;
		}
	}
};

int main(void)
{
	List<int> list;
	list.push_back(3);
	list.push_back(4);
	list.push_front(2);
	list.push_front(1);

	/*Print all elements*/
	for (List<int>::iterator iter = list.begin(); iter != list.end(); ++iter)
	{
		std::cout << (*iter) << std::endl;
	}

	/*Delete second element and reprint*/
	List<int>::iterator tmp = list.begin() + 1;
	list.erase(tmp);

	for (List<int>::iterator iter = list.begin(); iter != list.end(); ++iter)
	{
		std::cout << (*iter) << std::endl;
	}

	/*Now delete first node and print again*/
	tmp = list.begin();
	list.erase(tmp);

	for (List<int>::iterator iter = list.begin();
	     iter != list.end(); ++iter)
	{
		std::cout << (*iter) << std::endl;
	}

	//List object takes care of deletion for us.
	return 0;
}
