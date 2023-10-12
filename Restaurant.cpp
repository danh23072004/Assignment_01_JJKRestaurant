#include "main.h"

class imp_res : public Restaurant
{
public:
	class TableList
	{
	public: 
		class MyCustomer : public customer
		{

		};
	public:
		TableList();
		~TableList();
		bool addCustomer(customer*);
		int getCount();
		bool isDuplicate(const customer&);
		customer* findRes();
		void traverse(int);
		void reverse();
		bool swap(customer*, customer*);
		//void setCount();
	private:
		customer* head;
		int count;
		customer* currentX;
	};

	class CustomerTimeList
	{
	public:
		class CustomerTimeNode
		{
		public:
			CustomerTimeNode();
			CustomerTimeNode(customer* const, CustomerTimeNode*);
			customer* customerData;
			CustomerTimeNode* next;
		private:
		};
	private:
		CustomerTimeNode* head;
	public:
		CustomerTimeList();
		void addCustomerTime(customer*);
	};

	class WaitingQueue
	{
	private:
		int MaxSize;
		int count;
	public:
		class WaitingQueueNode
		{
		public:
			WaitingQueueNode(customer*, WaitingQueueNode*);
			customer* customerData;
			WaitingQueueNode* next;
		};
	public:
		WaitingQueueNode* head;
		WaitingQueue();
		void addCustomerToQueue(customer*);
		bool isFull();
		void changeCount(bool);
		void traverse();
		int operator[](int);
	};

private:
	TableList table;
	CustomerTimeList customerTime;
	WaitingQueue waitingQueue;
public:	
	imp_res();

	void RED(string name, int energy)
	{
		cout << name << " " << energy << endl; // to show that the command has been executed
		customer* newCust = new customer(name, energy, nullptr, nullptr);
		if (table.addCustomer(newCust) == true)
		{
			customerTime.addCustomerTime(newCust);
		}
		else if (waitingQueue.isFull() == false)
		{
			waitingQueue.addCustomerToQueue(newCust);
		}
	}
	void BLUE(int num)
	{
		cout << "blue "<< num << endl;
	}
	void PURPLE()
	{
		cout << "purple"<< endl;
	}
	void REVERSAL()
	{
		cout << "reversal" << endl;
		table.reverse();
	}
	void UNLIMITED_VOID()
	{
		cout << "unlimited_void" << endl;
	}
	void DOMAIN_EXPANSION()
	{
		cout << "domain_expansion" << endl;
	}
	void LIGHT(int num)
	{
		cout << "light " << num << endl;
		if (num != 0) // print customers in the restaurant
		{
			table.traverse(num);
		}
		else // print customers in the waiting queue
		{
			waitingQueue.traverse();
		}
	}
};

/// TableList implementation

imp_res::TableList::TableList()
{
	head = nullptr;
	count = 0;
	currentX = nullptr;
}

imp_res::TableList::~TableList()
{
}

bool imp_res::TableList::addCustomer(customer* newCustomer)
{
	// circular doubly linked list
	customer* newCust;
	if (newCustomer->energy == 0 || isDuplicate(*newCustomer) == true)
		return false;
	if (head == nullptr && count < MAXSIZE)
	{
		newCust = newCustomer;
		head = newCust;
		newCust->next = newCust;
		newCust->prev = newCust;
		currentX = newCust;
		count++;
		return true;
	}
	else if (count < MAXSIZE)
	{
		if (count >= MAXSIZE / 2)
		{
			currentX = findRes();
		}
		newCust = newCustomer; // prevent change of newCustomer
		if (newCustomer->energy > currentX->energy) // newCust will be inserted at the left
		{
			newCust->next = currentX->next;

			newCust->prev = currentX;

			// CurrentX's next's prev will be new node
			currentX->next->prev = newCust;

			// CurrentX's next will be new node
			currentX->next = newCust;
		}
		else // newCust will be inserted at the right
		{
			newCust->next = currentX;

			newCust->prev = currentX->prev;

			// CurrentX's prev's next will be new node
			currentX->prev->next = newCust;

			// CurrentX's prev will be new node
			currentX->prev = newCust;
		}
		currentX = newCust;
		count++;
		return true;
	}
	return false;
}

int imp_res::TableList::getCount()
{
	return count;
}

bool imp_res::TableList::isDuplicate(const customer& newCustomer)
{
	if (head == nullptr)
	{
		return false;
	}
	else
	{
		customer* iterate = head;
		do
		{
			if (iterate->name == newCustomer.name)
			{
				return true;
			}
			iterate = iterate->next;
		} while (iterate != head);
	}
	return false;
}

Restaurant::customer* imp_res::TableList::findRes()
{
	int maxRes = 0;
	customer* maxResCustomer = nullptr;
	if (head == nullptr)
	{
		return maxResCustomer;
	}
	else
	{
		customer* iterate = currentX->next;
		do
		{
			if (abs(currentX->energy - iterate->energy) > maxRes)
			{
				maxRes = abs(currentX->energy - iterate->energy);
				maxResCustomer = iterate;
			}
		} while (iterate != head);
	}
	return maxResCustomer;
}

void imp_res::TableList::traverse(int num)
{
	if (head == nullptr)
	{
		return;
	}
	else if (num > 0)
	{
		customer* iterate = currentX;
		do
		{
			//cout << iterate->name << " " << iterate->energy << endl;
			iterate->print();
			iterate = iterate->next;
		} while (iterate != currentX);
	}
	else if (num < 0)
	{
		int index = 0;
		customer* iterate = currentX;
		do
		{
			//cout << iterate->name << " " << iterate->energy << endl;
			iterate->print();
			iterate = iterate->prev;
		} while (iterate != head);
	}
}

void imp_res::TableList::reverse()
{
	if (head == nullptr)
	{
		return;
	}
	customer* iterate1 = currentX;
	customer* iterate2 = currentX->next;
	int index1 = 0;
	int index2 = count - 1;
	int countSwapped = 0;

	// first stage: swap nodes having positive energy 
	do
	{
		while (iterate1->energy < 0)
		{
			/* iterate1 chạy theo hướng ngược chiều kim
			* tìm khách + kế tiếp
			*/
			iterate1->print();
			iterate1 = iterate1->prev;
			index1++;
		}
		while (iterate2->energy < 0)
		{
			/* iterate2 chạy theo hướng cùng chiều kim
			* tìm khách - kế tiếp
			*/
			iterate2->print();
			iterate2 = iterate2->next;
			index2--;
		}
		if (index1 < index2)
		{
			swap(iterate1, iterate2);
			iterate1 = iterate1->prev;
			iterate2 = iterate2->next;
			index1++;
			index2--;
		}
	} while (index1 < index2);

	// second stage: swap nodes having negative energy
	do
	{
		while (iterate1->energy > 0)
		{
			/* iterate1 chạy theo hướng ngược chiều kim
			* tìm khách + kế tiếp
			*/
			iterate1->print();
			iterate1 = iterate1->prev;
			index1++;
		}
		while (iterate2->energy > 0)
		{
			/* iterate2 chạy theo hướng cùng chiều kim
			* tìm khách - kế tiếp
			*/
			iterate2->print();
			iterate2 = iterate2->next;
			index2--;
		}
		if (index1 < index2)
		{
			swap(iterate1, iterate2);
			iterate1 = iterate1->prev;
			iterate2 = iterate2->next;
			index1++;
			index2--;
		}
	} while (index1 < index2);
}

bool imp_res::TableList::swap(customer* a, customer* b)
{
	customer* backup_a = a;
	customer* backup_b = b;
	// swap two nodes in a circular doubly linked list
	if (a == nullptr || b == nullptr || a == b)
		return false;
	if (a->next == b) // a kề với b
	{
		//a->next = b->next;
		//b->prev = a->prev;
		//a->prev = b;
		//b->next = a;
		customer* a_prev = a->prev;
		customer* b_next = b->next;
		a->next = nullptr;
		a->prev = nullptr;
		b->next = nullptr;
		b->prev = nullptr;
		a_prev->next = nullptr;
		b_next->prev = nullptr;
		a_prev->next = b;
		b_next->prev = a;
		a->next = b_next;
		a->prev = b;
		b->next = a;
		b->prev = a_prev;
	}
	else // a không kề b
	{
		customer* temp = a->next;
		a->next = b->next;
		b->next = temp;
		temp = a->prev;
		a->prev = b->prev;
		b->prev = temp;
	}
	//if (a->prev != nullptr)
	//{
	//	a->prev->next = b;
	//}
	//if (b->next != nullptr)
	//{
	//	b->next->prev = a;
	//}
	//a = backup_a;
	//b = backup_b;
	return true;
}


// imp_res implementation

imp_res::imp_res()
{
}

/// CustomerTimeList implementation

imp_res::CustomerTimeList::CustomerTimeList()
{
	head = nullptr;
}

void imp_res::CustomerTimeList::addCustomerTime(customer* newCustomer)
{
	if (newCustomer == nullptr)
		return;
	CustomerTimeNode* newNode = new CustomerTimeNode(newCustomer, nullptr);
	if (head == nullptr)
	{
		head = newNode;
	}
	else
	{
		CustomerTimeNode* current = head;
		while (current->next != nullptr)
		{
			current = current->next;
		}
		current->next = newNode;
	}
}

// customerTimeNode implementation

imp_res::CustomerTimeList::CustomerTimeNode::CustomerTimeNode()
{
	this->customerData = nullptr;
	this->next = nullptr;
}

imp_res::CustomerTimeList::CustomerTimeNode::CustomerTimeNode(customer* const newCustomer, CustomerTimeNode* nextPtr)
{
	// customer* const newCustomer means that the pointer is constant, but the data it points to is not constant
	this->customerData = newCustomer;
	this->next = nextPtr;
}

// / WaitingQueue implementation

imp_res::WaitingQueue::WaitingQueueNode::WaitingQueueNode(customer* customerData = nullptr, WaitingQueueNode* next = nullptr)
{
	this->customerData = customerData;
	this->next = next;
}

imp_res::WaitingQueue::WaitingQueue()
{
	head = nullptr;
	MaxSize = MAXSIZE;
	count = 0;
}

void imp_res::WaitingQueue::addCustomerToQueue(customer* newCustomer)
{
	if (newCustomer == nullptr)
		return;
	WaitingQueueNode* newNode = new WaitingQueueNode(newCustomer, nullptr);
	if (head == nullptr)
	{
		head = newNode;
	}
	else
	{
		WaitingQueueNode* current = head;
		while (current->next != nullptr)
		{
			current = current->next;
		}
		current->next = newNode;
	}
}

bool imp_res::WaitingQueue::isFull()
{
	return count == MaxSize;
}

void imp_res::WaitingQueue::changeCount(bool check)
{
	if (check == true)
	{
		count++;
	}
	else
	{
		count--;
	}
}

void imp_res::WaitingQueue::traverse()
{
	if (head == nullptr)
	{
		return;
	}
	else
	{
		WaitingQueueNode* iterate = head;
		do
		{
			iterate->customerData->print();
			iterate = iterate->next;
		} while (iterate != nullptr);
	}
}

int imp_res::WaitingQueue::operator[](int index)
{
	WaitingQueueNode* iterate = head;
	for (int i = 0; i < index; i++)
	{
		iterate = iterate->next;
	}
	return iterate->customerData->energy;
}
