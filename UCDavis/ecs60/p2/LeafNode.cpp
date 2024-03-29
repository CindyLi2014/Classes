#include <iostream>
#include <climits>
#include "LeafNode.h"
#include "InternalNode.h"
#include "QueueAr.h"

using namespace std;


LeafNode::LeafNode(int LSize, InternalNode *p,
									 BTreeNode *left, BTreeNode *right) : BTreeNode(LSize, p, left, right)
{
	values = new int[LSize];
}  // LeafNode()

void LeafNode::addToLeft(int value, int last)
{
	leftSibling->insert(values[0]);

	for(int i = 0; i < count - 1; i++)
		values[i] = values[i + 1];

	values[count - 1] = last;
	if(parent)
		parent->resetMinimum(this);
} // LeafNode::ToLeft()

void LeafNode::addToRight(int value, int last)
{
	rightSibling->insert(last);

	if(value == values[0] && parent)
		parent->resetMinimum(this);
} // LeafNode::addToRight()

void LeafNode::addToThis(int value)
{
	int i;

	for(i = count - 1; i >= 0 && values[i] > value; i--)
		values[i + 1] = values[i];

	values[i + 1] = value;
	count++;

	if(value == values[0] && parent)
		parent->resetMinimum(this);
} // LeafNode::addToThis()


void LeafNode::addValue(int value, int &last)
{
	int i;

	if(value > values[count - 1])
		last = value;
	else
	{
		last = values[count - 1];

		for(i = count - 2; i >= 0 && values[i] > value; i--)
			values[i + 1] = values[i];
		// i may end up at -1
		values[i + 1] = value;
	}
} // LeafNode:: addValue()


int LeafNode::getMaximum()const
{
	if(count > 0)  // should always be the case
		return values[count - 1];
	else
		return INT_MAX;
} // getMaximum()


int LeafNode::getMinimum()const
{
	if(count > 0)  // should always be the case
		return values[0];
	else
		return 0;

} // LeafNode::getMinimum()


LeafNode* LeafNode::insert(int value)
{
	int last;

	if(count < leafSize)
	{
		addToThis(value);
		return NULL;
	} // if room for value

	addValue(value, last);

	if(leftSibling && leftSibling->getCount() < leafSize)
	{
		addToLeft(value, last);
		return NULL;
	}
	else // left sibling full or non-existent
		if(rightSibling && rightSibling->getCount() < leafSize)
		{
			addToRight(value, last);
			return NULL;
		}
		else // both siblings full or non-existent
			return split(value, last);
}  // LeafNode::insert()

void LeafNode::print(Queue <BTreeNode*> &queue)
{
	cout << "Leaf: ";
	for (int i = 0; i < count; i++)
		cout << values[i] << ' ';
	cout << endl;
} // LeafNode::print()

//move nodes from left sibling
LeafNode* LeafNode::_borrowValFromLeftSibling()
{
	LeafNode* leftSibLeaf = dynamic_cast<LeafNode*>(leftSibling);
	insert(leftSibLeaf->getMaximum());
	leftSibling->remove(values[0]);

	if(parent)
		parent->resetMinimum(this);

	return NULL;
}

//merge with left sibling
LeafNode* LeafNode::_mergeWithLeftSibling()
{
	LeafNode* leftSibLeaf = dynamic_cast<LeafNode*>(leftSibling);
	for(int i = 0; i < count; i++)
		leftSibLeaf->insert(values[i]);

	leftSibling->setRightSibling(rightSibling);
	if(rightSibling)
		rightSibling->setLeftSibling(leftSibling);

	return this;
}

//BTree5_error.txt 2 4
LeafNode* LeafNode::_borrowValFromRightSibling(int pos)
{
	LeafNode* rightSibLeaf = dynamic_cast<LeafNode*>(rightSibling);
	insert(rightSibling->getMinimum());
	rightSibLeaf->remove(values[count - 1]);
	if(pos == 0)
		parent->resetMinimum(this);

	return NULL;
}

LeafNode* LeafNode::_mergeWithRightSibling()
{
	for(int i = 0; i < count; i++)
		rightSibling->insert(values[i]);

	rightSibling->setLeftSibling(leftSibling);
	if(leftSibling)
		leftSibling->setRightSibling(rightSibling);
	return this;
}

LeafNode* LeafNode::remove(int value)
{   // To be written by students
	int pos;
	for(pos = 0; pos < count && values[pos] != value; pos++);
	if(pos >= count)
		return NULL;

	count--;
	for(int i = pos; i < count; i++)
		values[i] = values[i + 1];

	int LBound = (leafSize + 1) / 2;
	if(count < LBound)
	{
		if(leftSibling != NULL)
		{
			if(leftSibling->getCount() > LBound)
				return _borrowValFromLeftSibling();
			else
				return _mergeWithLeftSibling();
		}
		else if(rightSibling != NULL)
		{
			if(rightSibling->getCount() > LBound)
				return _borrowValFromRightSibling(pos);
			else
				return _mergeWithRightSibling();
		}
	}

	if(pos == 0  && parent)
		parent->resetMinimum(this);

	return NULL;
}  // LeafNode::remove()


LeafNode* LeafNode::split(int value, int last)
{
	LeafNode *ptr = new LeafNode(leafSize, parent, this, rightSibling);


	if(rightSibling)
		rightSibling->setLeftSibling(ptr);

	rightSibling = ptr;

	for(int i = (leafSize + 1) / 2; i < leafSize; i++)
		ptr->values[ptr->count++] = values[i];

	ptr->values[ptr->count++] = last;
	count = (leafSize + 1) / 2;

	if(value == values[0] && parent)
		parent->resetMinimum(this);
	return ptr;
} // LeafNode::split()

