#include "Queue.h"


template <class ItemType>
Queue<ItemType>::Queue()
{
	front = NULL;
	rear = NULL;
}

template <class ItemType>
Queue<ItemType>::~Queue()
{
	delete front;
	delete rear;
}

template<class ItemType>
void Queue<ItemType>::Purge()
{
	NodeType < ItemType>* tempPtr;
	while (front != NULL)
	{
		tempPtr = front;
		front = front->next;
		delete tempPtr;
	}
	rear = NULL;
}

template<class ItemType>
void Queue<ItemType>::Enqueue(ItemType item)
{
	if (!IsFull())
	{
		NodeType < ItemType >* tmpNode;

		tmpNode = new NodeType < ItemType >;
		tmpNode->info = item;
		tmpNode->next = NULL;
		if (rear == NULL)
			front = tmpNode;
		else
			rear->next = tmpNode;
		rear = tmpNode;
		delete tmpNode;
	}
}

template<class ItemType>
void Queue<ItemType>::Dequeue(ItemType &item)
{
	if (!IsEmpty())
	{
		NodeType < ItemType >* tempPtr;

		tempPtr = front;
		item = front->info;
		front = front->next;

		if (front == NULL)
			rear = NULL;

		delete tempPtr;
	}
}

template<class ItemType>
bool Queue<ItemType>::IsEmpty() const
{
	return(front == NULL);
}

template<class ItemType>
bool Queue<ItemType>::IsFull() const
{
	return false; //No limit to number of patients
}
