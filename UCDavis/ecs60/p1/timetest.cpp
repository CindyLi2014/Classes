//Cindy Li

#include "CPUTimer.h"
#include "LinkedList.h"
#include "CursorList.h"
#include "StackAr.h"
#include "StackLi.h"
#include "QueueAr.h"
#include "SkipList.h"
#include "vector.h"

#include <iostream>
#include <fstream>

using namespace std;

const int LINE_LENGTH = 512;//first line's length
const int ELEMENT_MAXSIZE = 250000;
vector<CursorNode <int> > cursorSpace(ELEMENT_MAXSIZE);

int getChoice()
{
  int n;
  cout << "      ADT Menu" << endl
       << "0. Quit" << endl
       << "1. LinkedList" << endl
       << "2. CursorList" << endl
       << "3. StackAr" << endl
       << "4. StackLi" << endl
       << "5. QueueAr" << endl
       << "6. SkipList" << endl
       << "Your choice >> ";
  cin >> n;
	cout << endl;
  if( n < 0 || n > 6 )
	{
		cout << "Invalid choice: " << n << endl;
    throw n;
	}
  else
    return n;
}

void RunList(char *filename)
{
  ifstream inFile(filename);
  List <int> list;
  ListItr<int> it = list.zeroth();
  char c, ln[LINE_LENGTH];
  int v;

  inFile.getline(ln, LINE_LENGTH);
  while(inFile >> c >> v)
  {
    if(c == 'i' )
      list.insert(v, it);
    else
      list.remove(v);
  }
}

void RunCursorList(char *filename)
{
  ifstream inFile(filename);
  CursorList<int> clist( cursorSpace );
  CursorListItr<int> it = clist.zeroth();

  char c, ln[LINE_LENGTH];
  int v;

  inFile.getline(ln, LINE_LENGTH);
  while(inFile >> c >> v)
  {
    if(c == 'i' )
    {
			clist.insert(v, it);
    }
    else
    {
      clist.remove(v);
    }
  }
}

void RunStackAr(char *filename)
{
  ifstream inFile(filename);
  StackAr<int> stack(ELEMENT_MAXSIZE);

  char c, ln[LINE_LENGTH];
  int v;

  inFile.getline(ln, LINE_LENGTH);
  while(inFile >> c >> v)
  {
    if(c == 'i')
			stack.push(v);
    else
      stack.pop();
  }
}

void RunStackLi(char *filename)
{
  ifstream inFile(filename);
  StackLi<int> stack;

  char c, ln[LINE_LENGTH];
  int v;

  inFile.getline(ln, LINE_LENGTH);
  while(inFile >> c >> v)
  {
    if(c == 'i')
			stack.push(v);
    else
      stack.pop();
  }
}

void RunQueueAr(char *filename)
{
  ifstream inFile(filename);
  Queue<int> que(ELEMENT_MAXSIZE);

  char c, ln[LINE_LENGTH];
  int v;

  inFile.getline(ln, LINE_LENGTH);
  while(inFile >> c >> v)
  {
    if(c == 'i')
      que.enqueue(v);
    else
      que.dequeue();
  }
}

void RunSkipList(char *filename)
{
  ifstream inFile(filename);
	SkipList<int> skiplist(0, ELEMENT_MAXSIZE);

  char c, ln[LINE_LENGTH];
  int v;

  inFile.getline(ln, LINE_LENGTH);
  while(inFile >> c >> v)
  {
    if(c == 'i')
      skiplist.insert(v);
    else
      skiplist.deleteNode(v);
  }
}

int main( )
{
  char filename[FILENAME_MAX];
  int choice;
  CPUTimer ct;

  cout << "Filename >> ";
  cin >> filename;

  do
  {
    choice = getChoice();
		ct.reset();

    switch( choice )
    {
      case 1: RunList( filename ); break;
      case 2: RunCursorList( filename ); break;
      case 3: RunStackAr( filename ); break;
      case 4: RunStackLi( filename ); break;
      case 5: RunQueueAr( filename ); break;
      case 6: RunSkipList( filename ); break;
    }
    cout << "CPU time: " << ct.cur_CPUTime() << endl;
  } while( choice > 0 );

	return 0;
}

