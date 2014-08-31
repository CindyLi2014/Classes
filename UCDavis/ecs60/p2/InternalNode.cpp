#include <iostream>
#include <climits>
#include "InternalNode.h"

using namespace std;

InternalNode::InternalNode(int ISize, int LSize,
													 InternalNode *p, BTreeNode *left, BTreeNode *right) :
BTreeNode(LSize, p, left, right), internalSize(ISize)
{
	keys = new int[internalSize]; // keys[i] is the minimum of children[i]
	children = new BTreeNode* [ISize];
} // InternalNode::InternalNode()

BTreeNode* InternalNode::addPtr(BTreeNode *ptr, int pos)
{ // called when original was full, pos is where the node belongs.
	if(pos == internalSize)
		return ptr;

	BTreeNode *last = children[count - 1];

	for(int i = count - 2; i >= pos; i--)
	{
		children[i + 1] = children[i];
		keys[i + 1] = keys[i];
	} // shift things to right to make room for ptr, i can be -1!

	children[pos] = ptr;  // i will end up being the position that it is inserted
	keys[pos] = ptr->getMinimum();
	ptr->setParent(this);
	return last;
} // InternalNode:: addPtr()


void InternalNode::addToLeft(BTreeNode *last)
{
	((InternalNode*)leftSibling)->insert(children[0]);

	for(int i = 0; i < count - 1; i++)
	{
		children[i] = children[i + 1];
		keys[i] = keys[i + 1];
	}

	children[count - 1] = last;
	keys[count - 1] = last->getMinimum();
	last->setParent(this);
	if(parent)
		parent->resetMinimum(this);
} // InternalNode::ToLeft()

void InternalNode::addToRight(BTreeNode *ptr, BTreeNode *last)
{
	((InternalNode*) rightSibling)->insert(last);
	if(ptr == children[0] && parent)
		parent->resetMinimum(this);
} // InternalNode::addToRight()



void InternalNode::addToThis(BTreeNode *ptr, int pos)
{  // pos is where the ptr should go, guaranteed count < internalSize at start
	int i;

	for(i = count - 1; i >= pos; i--)
	{
		children[i + 1] = children[i];
		keys[i + 1] = keys[i];
	} // shift to the right to make room at pos

	children[pos] = ptr;
	keys[pos] = ptr->getMinimum();
	count++;
	ptr->setParent(this);

	if(pos == 0 && parent)
		parent->resetMinimum(this);
} // InternalNode::addToThis()


int InternalNode::getMaximum() const
{
	if(count > 0) // should always be the case
		return children[count - 1]->getMaximum();
	else
		return INT_MAX;
}  // getMaximum();


int InternalNode::getMinimum()const
{
	if(count > 0)   // should always be the case
		return children[0]->getMinimum();
	else
		return 0;
} // InternalNode::getMinimum()


InternalNode* InternalNode::insert(int value)
{  // count must always be >= 2 for an internal node
	int pos; // will be where value belongs

	for(pos = count - 1; pos > 0 && keys[pos] > value; pos--);

	BTreeNode *last, *ptr = children[pos]->insert(value);
	if(!ptr)  // child had room.
		return NULL;

	if(count < internalSize)
	{
		addToThis(ptr, pos + 1);
		return NULL;
	} // if room for value

	last = addPtr(ptr, pos + 1);

	if(leftSibling && leftSibling->getCount() < internalSize)
	{
		addToLeft(last);
		return NULL;
	}
	else // left sibling full or non-existent
		if(rightSibling && rightSibling->getCount() < internalSize)
		{
			addToRight(ptr, last);
			return NULL;
		}
		else // both siblings full or non-existent
			return split(last);
} // InternalNode::insert()

void InternalNode::insert(BTreeNode *oldRoot, BTreeNode *node2)
{ // Node must be the root, and node1
	children[0] = oldRoot;
	children[1] = node2;
	keys[0] = oldRoot->getMinimum();
	keys[1] = node2->getMinimum();
	count = 2;
	children[0]->setLeftSibling(NULL);
	children[0]->setRightSibling(children[1]);
	children[1]->setLeftSibling(children[0]);
	children[1]->setRightSibling(NULL);
	oldRoot->setParent(this);
	node2->setParent(this);
} // InternalNode::insert()

void InternalNode::insert(BTreeNode *newNode)
{ // called by sibling so either at beginning or end
	int pos;

	if(newNode->getMinimum() <= keys[0]) // from left sibling
		pos = 0;
	else // from right sibling
		pos = count;

	addToThis(newNode, pos);
} // InternalNode::insert(BTreeNode *newNode)

void InternalNode::print(Queue <BTreeNode*> &queue)
{
	int i;

	cout << "Internal: ";
	for (i = 0; i < count; i++)
		cout << keys[i] << ' ';
	cout << endl;

	for(i = 0; i < count; i++)
		queue.enqueue(children[i]);

} // InternalNode::print()

//move nodes from left sibling
InternalNode* InternalNode::_borrowValFromLeftSibling()
{
	InternalNode* leftSibIntn = dynamic_cast<InternalNode*>(leftSibling);
	insert(leftSibIntn->removeChild(leftSibling->getCount() - 1));

	if(parent)
		parent->resetMinimum(this);

	return NULL;
}

//merge with left sibling
InternalNode* InternalNode::_mergeWithLeftSibling()
{
	InternalNode* leftSibIntn = dynamic_cast<InternalNode*>(leftSibling);
	for(int i = 0; i < count; i++)
		leftSibIntn->insert(children[i]);

	leftSibling->setRightSibling(rightSibling);

	if(rightSibling)
		rightSibling->setLeftSibling(leftSibling);

	return this;
}

InternalNode* InternalNode::_borrowValFromRightSibling(int pos)
{
	InternalNode* rightSibIntn = dynamic_cast<InternalNode*>(rightSibling);
	insert(rightSibIntn->removeChild(0));
	if(pos == 0)
		parent->resetMinimum(this);

	return NULL;
}

InternalNode* InternalNode::_mergeWithRightSibling()
{
	InternalNode* rightSibIntn = dynamic_cast<InternalNode*>(rightSibling);
	for(int i = count - 1; i >= 0; i--)
		rightSibIntn->insert(children[i]);

	rightSibling->setLeftSibling(leftSibling);

	if(leftSibling)
		leftSibling->setRightSibling(rightSibling);

	return this;
}

BTreeNode* InternalNode::remove(int value)
{ // to be written by students
	//Cindy Li
	int pos = 0;
	for (pos = count - 1; pos > 0 && keys[pos] > value; pos--);
	BTreeNode *ptrRemove = children[pos]->remove(value);

	int LBound = (internalSize + 1) / 2;
  if(ptrRemove)
  {
    delete ptrRemove;
    count--;

    for(int i = pos; i < count; i++)
    {
      children[i] = children[i + 1];
      keys[i] = keys[i + 1];
    }

		if(count < LBound || count == 1)
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

    if(parent && pos == 0 && count > 0)
      parent->resetMinimum(this);
  }

	if(count == 1 && parent==NULL)
		return children[0];

	return NULL; // filler for stub
} // InternalNode::remove(int value)


void InternalNode::resetMinimum(const BTreeNode* child)
{
	for(int i = 0; i < count; i++)
		if(children[i] == child)
		{
			keys[i] = children[i]->getMinimum();
			if(i == 0 && parent)
				parent->resetMinimum(this);
			break;
		}
} // InternalNode::resetMinimum()


InternalNode* InternalNode::split(BTreeNode *last)
{
	InternalNode *newptr = new InternalNode(internalSize, leafSize,
		parent, this, rightSibling);


	if(rightSibling)
		rightSibling->setLeftSibling(newptr);

	rightSibling = newptr;

	for(int i = (internalSize + 1) / 2; i < internalSize; i++)
	{
		newptr->children[newptr->count] = children[i];
		newptr->keys[newptr->count++] = keys[i];
		children[i]->setParent(newptr);
	}

	newptr->children[newptr->count] = last;
	newptr->keys[newptr->count++] = last->getMinimum();
	last->setParent(newptr);
	count = (internalSize + 1) / 2;
	return newptr;
} // split()

BTreeNode* InternalNode::removeChild(int pos)
{
	BTreeNode* ptrRet = children[pos];
	count--;
	for (int i = pos; i < count; i++) 
	{
		children[i] = children[i + 1];
		keys[i] = keys[i+1];
	}

  if(pos == 0 && parent)
    parent->resetMinimum(this);

	return ptrRet;
}