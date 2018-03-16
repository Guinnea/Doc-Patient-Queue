#pragma once
template < class ItemType >
struct NodeType
{
	ItemType info;
	NodeType *next;
};

template < class ItemType >
class Queue
{
private:
	NodeType < ItemType >* front;
	NodeType < ItemType >* rear;
public:
	Queue();
	~Queue();
	void Purge();
	void Enqueue(ItemType);
	void Dequeue(ItemType&);
	bool IsEmpty() const;
	bool IsFull() const;
};
