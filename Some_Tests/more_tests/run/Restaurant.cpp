#include "main.h"

template <class T>
class SupportClass
{
public:
	static void swapData(T& a, T& b);
};

class imp_res : public Restaurant
{
public:
	class CustomerTimeList;
	class CustomerTimeNode;
	class WaitingQueue;
	class MyCustomer : public customer
	{
	public:
		MyCustomer();
		MyCustomer(string name, int energy, MyCustomer* prev, MyCustomer* next);
		~MyCustomer();
		//string name;
		//int energy;
		MyCustomer* prev;
		MyCustomer* next;
		CustomerTimeNode* timeNode;
	};
	class CustomerTimeNode
	{
	public:
		CustomerTimeNode();
		CustomerTimeNode(MyCustomer* const, CustomerTimeNode*);
		MyCustomer* MyCustomerData;
		CustomerTimeNode* next;
		static void swap(CustomerTimeNode*, CustomerTimeNode*);
	private:
	};
	class PrintStack
	{
	private:
		MyCustomer* head;
	public:
		PrintStack();
		~PrintStack();
		void push(MyCustomer*);
		void print();
	};
	class TableList
	{
	public:
		TableList();
		~TableList();
		bool addCustomer(MyCustomer*);
		void addCustomerFromQueue(int, WaitingQueue&, CustomerTimeList&);
		int getCount();
		bool isDuplicate(const MyCustomer&);
		MyCustomer* findRes(MyCustomer*);
		MyCustomer* getCurrentX();
		MyCustomer* findMinInsideSublist(MyCustomer*, MyCustomer*);
		void traverseAllTable(int);
		void traversePartialTable(MyCustomer*, MyCustomer*);
		void reverse();
		bool swap(MyCustomer*, MyCustomer*);
		void insertCustomerLeftX(MyCustomer*, MyCustomer*);
		void insertCustomerRightX(MyCustomer*, MyCustomer*);
		void deleteCustomerInOrderStepInRes(int, CustomerTimeList&);
		void deleteOneTypeOfCustomers(CustomerTimeList&, WaitingQueue&, PrintStack& , bool);
		void deleteSpecificCustomer(MyCustomer*);
		int calculateEnergyOfWizard(WaitingQueue&);
		int calculateEnergyOfSpirit(WaitingQueue&);
		bool isFull();

		//void setCount();
	private:
		int count;
		MyCustomer* currentX;
	};
	class CustomerTimeList
	{
		// Danh sách liên kết đơn
		// Class này lưu thứ tự vào nhà hàng tính từ head (vào sớm nhất).
		// Từ SỚM NHẤT -> TRỄ NHẤT (GẦN ĐÂY NHẤT) - tương ứng với thứ tự của BLUE
	private:
		CustomerTimeNode* head;
		CustomerTimeNode* tail;
		int count;
	public:
		CustomerTimeList();
		CustomerTimeNode* getFirstCustomer();
		void deleteFirstCustomer();
		void deleteSpecificCustomer(CustomerTimeNode*);
		void addCustomerTime(MyCustomer*);
		/*void findCurrentIndex(MyCustomer*);*/
	};
	class WaitingQueue
	{
	/// <summary>
	/// Đây là hàng đợi
	/// </summary>
	public:
		class WaitingQueueNode
		{
		public:
			WaitingQueueNode(MyCustomer*, WaitingQueueNode*);
			~WaitingQueueNode();
			MyCustomer* MyCustomerData;
			WaitingQueueNode* next;
		};
	private:
		int count;
		WaitingQueueNode* head;
	public:
		WaitingQueue();
		WaitingQueueNode* getFirstCustomer();
		WaitingQueueNode* getCustomer(int);
		void deleteFirstCustomer();
		void deleteSpecificCustomer(WaitingQueueNode*);
		void addCustomerToQueue(MyCustomer*);
		//WaitingQueueNode* findCustomerInQueue(MyCustomer*);
		void deleteOneTypeOfCustomers(CustomerTimeList&, PrintStack&, bool);
		bool comparison(WaitingQueueNode* a, WaitingQueueNode* b);
		int calculateEnergyOfWizard();
		int calculateEnergyOfSpirit();
		int findMaxEnergy();
		int shellSort(int);
		int insertSionSort(int, int, int);
		bool isFull();
		bool isDuplicate(const MyCustomer&);
		void changeCount(bool);
		void traverse();
		int getCount();
	};

private:
	TableList table;
	CustomerTimeList myCustomerTime;
	WaitingQueue waitingQueue;
public:	
	imp_res();
	int countDebug = 0;
	void RED(string name, int energy)
	{
		countDebug++;
		//cout << name << " " << energy << endl; // to show that the command has been executed
		
		MyCustomer* newCust = new MyCustomer(name, energy, nullptr, nullptr);
		if (energy == 0 || table.isDuplicate(*newCust) || waitingQueue.isDuplicate(*newCust) == true 
			&& waitingQueue.isFull() == false)
		{
			delete newCust;
			return;
		}
		if (waitingQueue.isFull() == false && table.addCustomer(newCust) == false)
		{
			waitingQueue.addCustomerToQueue(newCust);
		}
		myCustomerTime.addCustomerTime(newCust); // chỉ add 1 lần duy nhất ở đây
	}
	void BLUE(int num)
	{
		countDebug++;
		//cout << "blue "<< num << endl;
		table.deleteCustomerInOrderStepInRes(num, myCustomerTime);
		table.addCustomerFromQueue(num, waitingQueue, myCustomerTime);
	}
	void PURPLE()
	{
		countDebug++;
		//cout << "purple"<< endl;
		int size = waitingQueue.findMaxEnergy();
		int countSwap = waitingQueue.shellSort(size);
		BLUE(countSwap % MAXSIZE);
	}
	void REVERSAL()
	{
		countDebug++;
		//cout << "reversal" << endl;
		table.reverse();
	}
	void UNLIMITED_VOID()
	{
		countDebug++;
		//cout << "unlimited_void" << endl;
		if (table.getCount() <= 3)
		{
			return;
		}
		int minEnergy = 2147483647;
		MyCustomer* head = nullptr, * tail = nullptr;
		MyCustomer* iterate_i = table.getCurrentX();
		for (unsigned i = 0; i < table.getCount(); i++)
		{
			int sumEnergy = 0;
			MyCustomer* iterate_j = iterate_i;
			for (unsigned j = 0; j < table.getCount(); j++)
			{
				sumEnergy += iterate_j->energy;
				if ((j >= 3) && sumEnergy <= minEnergy)
				{
					// j >= 3 tức là khi này đếm được 4 phần tử
					head = iterate_i;
					tail = iterate_j;
					minEnergy = sumEnergy;
				}
				iterate_j = iterate_j->next;
			}
			iterate_i = iterate_i->next;
		}

		MyCustomer* min = table.findMinInsideSublist(head, tail);
		table.traversePartialTable(min, tail);
		table.traversePartialTable(head, min->prev);
	}
	void DOMAIN_EXPANSION()
	{
		countDebug++;
		//cout << "domain_expansion" << endl;
		bool chooseSide = table.calculateEnergyOfWizard(waitingQueue) >= table.calculateEnergyOfSpirit(waitingQueue) ? true : false;
		PrintStack printStack;
		table.deleteOneTypeOfCustomers(myCustomerTime, waitingQueue, printStack, chooseSide);
	}
	void LIGHT(int num)
	{
		countDebug++;
		cout << "light " << num << endl;
		if (num != 0) // print MyCustomers in the restaurant
		{
			table.traverseAllTable(num);
		}
		else // print MyCustomers in the waiting queue
		{
			waitingQueue.traverse();
		}
	}
};

/// TableList implementation

imp_res::TableList::TableList()
{
	count = 0;
	currentX = nullptr;
}

imp_res::TableList::~TableList()
{
}

bool imp_res::TableList::addCustomer(MyCustomer* newCustomer)
{
	// circular doubly linked list
	MyCustomer* newCust;
	if (newCustomer->energy == 0 || isDuplicate(*newCustomer) == true || isFull() == true)
		return false;
	if (currentX == nullptr && count < MAXSIZE)
	{
		newCust = newCustomer;
		currentX = newCust;
		newCust->next = newCust;
		newCust->prev = newCust;
		count++;
		return true;
	}
	else if (count < MAXSIZE)
	{
		newCust = newCustomer; // prevent change of newCustomer
		if (count < MAXSIZE / 2)
		{
			if (newCustomer->energy >= currentX->energy)
			{
				insertCustomerRightX(newCust, currentX);
			}
			else // newCust will be inserted at the right
			{
				insertCustomerLeftX(newCust, currentX);
			}
		}
		else
		{
			currentX = findRes(newCust);
			if (newCust->energy - currentX->energy > 0)
			{
				insertCustomerRightX(newCust, currentX);
			}
			else
			{
				insertCustomerLeftX(newCust, currentX);
			}
		}
		currentX = newCust;
		count++;
		return true;
	}
	return false;
}

void imp_res::TableList::addCustomerFromQueue(int count, WaitingQueue& waitingQueue, CustomerTimeList& myCustomerTime)
{
	if (waitingQueue.getCount() == 0)
	{
		return;
	}
	else
	{
		// this is the same as RED
		// Chỗ này phải thêm cái vòng lặp while cho đến khi queue trống hoặc table đầy
		while (waitingQueue.getFirstCustomer() != nullptr && isFull() == false)
		{
			MyCustomer* newCustomer = waitingQueue.getFirstCustomer()->MyCustomerData;
			waitingQueue.deleteFirstCustomer();
			// Ở đây không cần add vô time list nữa vì ở RED đã thêm vào và chỉ thêm
			// 1 lần duy nhất ở RED
			//if (waitingQueue.isFull() == false && addCustomer(newCustomer) == false)
			//{
			//	waitingQueue.addCustomerToQueue(newCustomer);
			//}
			if (addCustomer(newCustomer) == false)
			{
				break;
			}
		}
	}
}

int imp_res::TableList::getCount()
{
	return count;
}

bool imp_res::TableList::isDuplicate(const MyCustomer& newCustomer)
{
	if (currentX == nullptr)
	{
		return false;
	}
	else
	{
		MyCustomer* iterate = currentX;
		do
		{
			if (iterate->name == newCustomer.name)
			{
				return true;
			}
			iterate = iterate->next;
		} while (iterate != currentX);
	}
	return false;
}

imp_res::MyCustomer* imp_res::TableList::findRes(MyCustomer* newCustomer)
{
	int maxRes = 0;
	MyCustomer* maxResCustomer = nullptr;
	if (currentX == nullptr)
	{
		return maxResCustomer;
	}
	else
	{
		MyCustomer* iterate = currentX;
		int res = 0;
		do
		{
			res = abs(newCustomer->energy - iterate->energy);
			if (res > maxRes)
			{
				maxRes = abs(newCustomer->energy - iterate->energy);
				maxResCustomer = iterate;
			}
			iterate = iterate->next;
		} while (iterate != currentX);
	}
	return maxResCustomer;
}

imp_res::MyCustomer* imp_res::TableList::getCurrentX()
{
	return currentX;
}

imp_res::MyCustomer* imp_res::TableList::findMinInsideSublist(MyCustomer* begin, MyCustomer* end)
{
	if (begin == nullptr || end == nullptr)
	{
		return nullptr;
	}
	MyCustomer* temp = begin, * min = begin;
	int minEnergy = begin->energy;
	while (temp != end->next)
	{
		if (temp->energy < minEnergy)
		{
			min = temp;
		}
		temp = temp->next;
	}
	return min;
}

void imp_res::TableList::traverseAllTable(int num)
{
	if (currentX == nullptr)
	{
		return;
	}
	else if (num > 0)
	{
		MyCustomer* iterate = currentX;
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
		MyCustomer* iterate = currentX;
		do
		{
			//cout << iterate->name << " " << iterate->energy << endl;
			iterate->print();
			iterate = iterate->prev;
		} while (iterate != currentX);
	}
}

void imp_res::TableList::traversePartialTable(MyCustomer* begin, MyCustomer* end)
{
	if (begin == nullptr || end == nullptr)
	{
		return;
	}
	else if (begin == end)
	{
		begin->print();
	}
	else
	{
		MyCustomer* iterate = begin;
		while (iterate != end->next)
		{
			//cout << iterate->name << " " << iterate->energy << endl;
			iterate->print();
			iterate = iterate->next;
		}
	}
}

void imp_res::TableList::reverse()
{
	if (currentX == nullptr)
	{
		return;
	}
	int backup_X = currentX->energy;
	MyCustomer* iterate1 = currentX;
	MyCustomer* iterate2 = currentX->next;
	int index1 = 0;
	int index2 = count - 1;
	int countSwapped = 0;

	// first stage: swap nodes having positive energy 
	do
	{
		while (iterate1->energy < 0 && index1 < count)
		{
			/* iterate1 chạy theo hướng ngược chiều kim
			* tìm khách + kế tiếp
			*/
			//iterate1->print();
			iterate1 = iterate1->prev;
			index1++;
		}
		while (iterate2->energy < 0 && index2 >= 0)
		{
			/* iterate2 chạy theo hướng cùng chiều kim
			* tìm khách - kế tiếp
			*/
			//iterate2->print();
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
	iterate1 = currentX;
	iterate2 = currentX->next;
	index1 = 0;
	index2 = count - 1;
	do
	{
		while (iterate1->energy > 0 && index1 < count)
		{
			/* iterate1 chạy theo hướng ngược chiều kim
			* tìm khách + kế tiếp
			*/
			//iterate1->print();
			iterate1 = iterate1->prev;
			index1++;
		}
		while (iterate2->energy > 0 && index2 >= 0)
		{
			/* iterate2 chạy theo hướng cùng chiều kim
			* tìm khách - kế tiếp
			*/
			//iterate2->print();
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

	iterate1 = currentX;
	for (int i = 0; i < this->count; i++)
	{
		if (iterate1->energy == backup_X)
		{
			currentX = iterate1;
			break;
		}
		iterate1 = iterate1->next;
	}
}

bool imp_res::TableList::swap(MyCustomer* a, MyCustomer* b)
{
	MyCustomer backup_x;
	bool isbackup_x = true;
	if (currentX == a)
	{
		backup_x = *a;
	}
	else if (currentX == b)
	{
		backup_x = *b;
	}

	SupportClass<int>::swapData(a->energy, b->energy);
	SupportClass<string>::swapData(a->name, b->name);
	CustomerTimeNode::swap(a->timeNode, b->timeNode);
	SupportClass<CustomerTimeNode*>::swapData(a->timeNode, b->timeNode);

	//if (a->name == backup_x.name)
	//{
	//	currentX = a;
	//}
	//else if (b->name == backup_x.name)
	//{
	//	currentX = b;
	//}
	return true;
}

void imp_res::TableList::insertCustomerLeftX(MyCustomer* a, MyCustomer* X)
{
	// a will be inserted at the right
	a->next = X;

	a->prev = X->prev;

	// CurrentX's next's prev will be new node
	X->prev->next = a;

	// CurrentX's next will be new node
	X->prev = a;
}

void imp_res::TableList::insertCustomerRightX(MyCustomer* a, MyCustomer* X)
{
	// a will be inserted at the right
	a->next = X->next;

	a->prev = X;

	// CurrentX's next's prev will be new node
	X->next->prev = a;

	// CurrentX's next will be new node
	X->next = a;
}

void imp_res::TableList::deleteCustomerInOrderStepInRes(int countDelete, CustomerTimeList& timeList)
{
	// Delete in order from head (SỚM NHẤT -> TRỄ NHẤT (GẦN ĐÂY NHẤT))
	CustomerTimeNode* iterate;
	if (countDelete > count)
	{
		countDelete = count;
	}
	for (unsigned i = 0; i < countDelete; i++)
	{
		iterate = timeList.getFirstCustomer();
		deleteSpecificCustomer(iterate->MyCustomerData);
		timeList.deleteFirstCustomer();
	}
}

void imp_res::TableList::deleteOneTypeOfCustomers(CustomerTimeList& customerTimeList, WaitingQueue& waitingQueue, PrintStack& printStack, bool whichSide)
{
	// whichSide = true là chú thuật sư, false là oán linh
	if (currentX == nullptr || count == 0)
	{
		return;
	}
	int countDeleteFromTable = 0;
	CustomerTimeNode* iterate = customerTimeList.getFirstCustomer(), * deleteCustomer;
	int countCheck = this->count;
	for (unsigned i = 0; i < countCheck; i++)
	{
		deleteCustomer = iterate;
		iterate = iterate->next;
		if ((deleteCustomer->MyCustomerData->energy > 0 && whichSide == true) || (deleteCustomer->MyCustomerData->energy < 0 && whichSide == false))
		{
			MyCustomer* printDeleteCutomer = new MyCustomer(deleteCustomer->MyCustomerData->name, deleteCustomer->MyCustomerData->energy, nullptr, nullptr);
			printStack.push(printDeleteCutomer);
			this->deleteSpecificCustomer(deleteCustomer->MyCustomerData); // delete in table
			customerTimeList.deleteSpecificCustomer(deleteCustomer); // delete in time list
			countDeleteFromTable++;
		}
	}
	waitingQueue.deleteOneTypeOfCustomers(customerTimeList, printStack, whichSide);

	addCustomerFromQueue(countDeleteFromTable, waitingQueue, customerTimeList);
	printStack.print();

}

int imp_res::TableList::calculateEnergyOfWizard(WaitingQueue& waitingQueue)
{
	int sumEnergy = 0;
	// calculate sum of energy of wizard in the table of restaurant
	MyCustomer* iterate = currentX;
	do
	{
		if (iterate->energy > 0)
		{
			sumEnergy += iterate->energy;
		}
	} while (iterate != currentX);

	return sumEnergy + waitingQueue.calculateEnergyOfWizard();
}

int imp_res::TableList::calculateEnergyOfSpirit(WaitingQueue& waitingQueue)
{
	int sumEnergy = 0;
	// calculate sum of energy of spirits in the table of restaurant
	MyCustomer* iterate = currentX;
	do
	{
		if (iterate->energy < 0)
		{
			sumEnergy += iterate->energy;
		}
	} while (iterate != currentX);
	// calculate sum of energy of spirits in the waiting queue
	return -sumEnergy + waitingQueue.calculateEnergyOfSpirit();
}

bool imp_res::TableList::isFull()
{
	return count == MAXSIZE;
}

void imp_res::TableList::deleteSpecificCustomer(MyCustomer* deleteCustomer)
{
	if (currentX == nullptr)
	{
		return;
	}
	else if (getCount() == 1)
	{
		delete currentX;
		currentX = nullptr;
	}
	else
	{
		if (deleteCustomer->energy > 0)
		{
			currentX = deleteCustomer->next;
		}
		else
		{
			currentX = deleteCustomer->prev;
		}
		deleteCustomer->prev->next = deleteCustomer->next;
		deleteCustomer->next->prev = deleteCustomer->prev;
		delete deleteCustomer;
	}
	count--;
}


// imp_res implementation

imp_res::imp_res()
{
}

/// CustomerTimeList implementation

imp_res::CustomerTimeList::CustomerTimeList()
{
	head = nullptr;
	tail = nullptr;
	count = 0;
}

imp_res::CustomerTimeNode* imp_res::CustomerTimeList::getFirstCustomer()
{
	return this->head;
}

void imp_res::CustomerTimeList::deleteFirstCustomer()
{
	CustomerTimeNode* deleteCustomer = head;
	head = head->next;
	delete deleteCustomer;
	count--;
}

void imp_res::CustomerTimeList::deleteSpecificCustomer(CustomerTimeNode* deleteCustomer)
{
	if (head == nullptr)
	{
		return;
	}
	else if (head == deleteCustomer)
	{
		deleteFirstCustomer();
	}
	else
	{
		CustomerTimeNode* iterate = head;
		while (iterate->next != deleteCustomer)
		{
			iterate = iterate->next;
		}
		iterate->next = deleteCustomer->next;
		delete deleteCustomer;
		count--;
	}
}

void imp_res::CustomerTimeList::addCustomerTime(MyCustomer* newCustomer)
{
	if (newCustomer == nullptr)
		return;
	CustomerTimeNode* newNode = new CustomerTimeNode(newCustomer, nullptr);
	if (head == nullptr)
	{
		head = newNode;
		tail = newNode;
	}
	else
	{
		tail->next = newNode;
		tail = newNode;
	}
	newCustomer->timeNode = newNode; // set timeNode for newCustomer
	count++;
}

//void imp_res::CustomerTimeList::findCurrentIndex(MyCustomer*)
//{
//}

// MyCustomerTimeNode implementation

imp_res::CustomerTimeNode::CustomerTimeNode()
{
	this->MyCustomerData = nullptr;
	this->next = nullptr;
}

imp_res::CustomerTimeNode::CustomerTimeNode(MyCustomer* const newCustomer, CustomerTimeNode* nextPtr)
{
	// MyCustomer* const newCustomer means that the pointer is constant, but the data it points to is not constant
	// MyCustomerData stores actual pointer point to the Customer in the table
	this->MyCustomerData = newCustomer;
	this->next = nextPtr;
}

void imp_res::CustomerTimeNode::swap(CustomerTimeNode* a, CustomerTimeNode* b)
{
	MyCustomer* temp = a->MyCustomerData;
	a->MyCustomerData = b->MyCustomerData;
	b->MyCustomerData = temp;
}

// / WaitingQueue implementation

imp_res::WaitingQueue::WaitingQueueNode::WaitingQueueNode(MyCustomer* MyCustomerData = nullptr, WaitingQueueNode* next = nullptr)
{
	this->MyCustomerData = MyCustomerData;
	this->next = next;
}

imp_res::WaitingQueue::WaitingQueueNode::~WaitingQueueNode()
{
}

imp_res::WaitingQueue::WaitingQueue()
{
	head = nullptr;
	count = 0;
}

imp_res::WaitingQueue::WaitingQueueNode* imp_res::WaitingQueue::getFirstCustomer()
{
	return head;
}

imp_res::WaitingQueue::WaitingQueueNode* imp_res::WaitingQueue::getCustomer(int index)
{
	if (index < 0 || index >= count)
	{
		return nullptr;
	}
	WaitingQueueNode* iterate = head;
	for (unsigned i = 0; i < index; i++)
	{
		iterate = iterate->next;
	}
	return iterate;
}

void imp_res::WaitingQueue::deleteFirstCustomer()
{
	WaitingQueueNode* deleteCustomer = head;
	head = head->next;
	delete deleteCustomer;
	this->count--;
}

void imp_res::WaitingQueue::deleteSpecificCustomer(WaitingQueueNode* deleteNode)
{
	if (head == nullptr)
	{
		return;
	}
	else if (head == deleteNode)
	{
		deleteFirstCustomer();
	}
	else
	{
		WaitingQueueNode* iterate = head;
		while (iterate->next != deleteNode)
		{
			iterate = iterate->next;
		}
		iterate->next = deleteNode->next;
		delete deleteNode;
		this->count--;
	}
}

void imp_res::WaitingQueue::addCustomerToQueue(MyCustomer* newCustomer)
{
	if (newCustomer == nullptr || isDuplicate(*newCustomer) == true || newCustomer->energy == 0)
		return;
	WaitingQueueNode* newNode = new WaitingQueueNode(newCustomer, nullptr);
	if (count < MAXSIZE)
	{
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
		count++;
	}
}

void imp_res::WaitingQueue::deleteOneTypeOfCustomers(CustomerTimeList& customerTimeList, PrintStack& printStack, bool whichSide)
{
	// whichSide = true là chú thuật sư, false là oán linh
	if (head == nullptr || this->count == 0)
	{
		return;
	}
	WaitingQueueNode* iterate = head, * deleteCustomer;
	int countCheck = this->count;
	for (unsigned i = 0; i < countCheck; i++)
	{
		deleteCustomer = iterate;
		iterate = iterate->next;
		if ((deleteCustomer->MyCustomerData->energy > 0 && whichSide == true) || (deleteCustomer->MyCustomerData->energy < 0 && whichSide == false))
		{
			// this part deletes the customer in the waiting queue
			MyCustomer* printDeleteCustomer = new MyCustomer(deleteCustomer->MyCustomerData->name, deleteCustomer->MyCustomerData->energy, nullptr, nullptr);
			printStack.push(printDeleteCustomer);
			customerTimeList.deleteSpecificCustomer(deleteCustomer->MyCustomerData->timeNode); // delete in time list
			delete deleteCustomer->MyCustomerData; // không dùng lệnh delete trong table bởi vì node không có prev và nexts
			this->deleteSpecificCustomer(deleteCustomer); // delete in waiting queue
		}
	}
}

bool imp_res::WaitingQueue::comparison(WaitingQueueNode* a, WaitingQueueNode* b)
{
	// true means a > b
	if (abs(a->MyCustomerData->energy) > abs(b->MyCustomerData->energy))
	{
		return true;
	}
	else if (abs(a->MyCustomerData->energy) < abs(b->MyCustomerData->energy))
	{
		return false;
	}
	else
	{
		CustomerTimeNode* test_a = a->MyCustomerData->timeNode;
		CustomerTimeNode* test_b = b->MyCustomerData->timeNode;
		while (test_a != nullptr && test_b != nullptr)
		{
			test_a = test_a->next;
			test_b = test_b->next;
		}
		if (test_a != nullptr)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

int imp_res::WaitingQueue::calculateEnergyOfWizard()
{
	// calculate sum of energy of wizard in the waiting queue
	int sumEnergy = 0;
	WaitingQueueNode* iterate = head;
	while (iterate != nullptr)
	{
		if (iterate->MyCustomerData->energy > 0)
		{
			sumEnergy += iterate->MyCustomerData->energy;
		}
		iterate = iterate->next;
	}
	return sumEnergy;
}

int imp_res::WaitingQueue::calculateEnergyOfSpirit()
{
	// calculate sum of energy of spirits in the waiting queue
	int sumEnergy = 0;
	WaitingQueueNode* iterate = head;
	while (iterate != nullptr)
	{
		if (iterate->MyCustomerData->energy < 0)
		{
			sumEnergy += iterate->MyCustomerData->energy;
		}
		iterate = iterate->next;
	}
	return -sumEnergy;
}

int imp_res::WaitingQueue::findMaxEnergy()
{
	WaitingQueueNode* max = head, * iterate = head;
	int size = 0;
	for (int i = 0; i < this->getCount() ; i++)
	{
		if (abs(iterate->MyCustomerData->energy) >= abs(max->MyCustomerData->energy))
		{
			max = iterate;
			size = i + 1;
		}
		iterate = iterate->next;
	}
	return size;
}

int imp_res::WaitingQueue::insertSionSort(int start, int size, int gap)
{
	int countSwap = 0;
	for (int i = gap; i < size; i++)
	{
		for (int j = i; (j >= gap) && (comparison(getCustomer(j), getCustomer(j - gap))); j -= gap)
		{
			WaitingQueueNode* node1 = getCustomer(j);
			WaitingQueueNode* node2 = getCustomer(j - gap);
			//SupportClass<WaitingQueueNode>::swapData(*node1, *node2);
			SupportClass<MyCustomer>::swapData(*node1->MyCustomerData, *node2->MyCustomerData);
			countSwap++;
		}
	}
	return countSwap;
}

int imp_res::WaitingQueue::shellSort(int size)
{
	if (size == 0)
	{
		return 0;
	}
	int countSwap = 0;
	for (int gap = size / 2; gap > 2; gap /= 2)
	{
		for (int j = 0; j < gap; j++)
		{
			countSwap += insertSionSort(j, size - j, gap);
		}
	}
	countSwap += insertSionSort(0, size, 1);
	return countSwap;
}

bool imp_res::WaitingQueue::isFull()
{
	return count == MAXSIZE;
}

bool imp_res::WaitingQueue::isDuplicate(const MyCustomer& newCustomer)
{
	if (head == nullptr)
	{
		return false;
	}
	else
	{
		WaitingQueueNode* iterate = head;
		do
		{
			if (iterate->MyCustomerData->name == newCustomer.name)
			{
				return true;
			}
			iterate = iterate->next;
		} while (iterate != nullptr);
	}
	return false;
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
			iterate->MyCustomerData->print();
			iterate = iterate->next;
		} while (iterate != nullptr);
	}
}

int imp_res::WaitingQueue::getCount()
{
	return count;
}

imp_res::MyCustomer::MyCustomer() : customer()
{
	this->name = "";
	this->energy = 0;
	this->prev = nullptr;
	this->next = nullptr;
	this->timeNode = nullptr;
}

imp_res::MyCustomer::MyCustomer(string name, int energy, MyCustomer* prev, MyCustomer* next) : customer(name, energy, prev, next)
{
	this->name = name;
	this->energy = energy;
	this->prev = prev;
	this->next = next;
	this->timeNode = nullptr;
}

imp_res::MyCustomer::~MyCustomer()
{
}

template<class T>
void SupportClass<T>::swapData(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}

void imp_res::PrintStack::push(MyCustomer* printCustomer)
{
	if (head == nullptr)
	{
		head = printCustomer;
	}
	else
	{
		MyCustomer* temp = head;
		head = printCustomer;
		head->next = temp;
	}
}

imp_res::PrintStack::PrintStack()
{
	head = nullptr;
}

imp_res::PrintStack::~PrintStack()
{
}

void imp_res::PrintStack::print()
{
	if (head == nullptr)
	{
		return;
	}
	else
	{
		MyCustomer* deleteCustomer;
		while (head != nullptr)
		{
			head->print();
			deleteCustomer = head;
			head = head->next;
			delete deleteCustomer;
		}
	}
}
