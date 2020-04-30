// ============================================================================
//     Description: This is a class which implements various functions which 
//          demonstrates the use of a Hash Table. 
// ============================================================================
#ifndef TEMPLATE_HASH_TABLE
#define TEMPLATE_HASH_TABLE
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
 
// if user doesnt define, this is the 
// default hash table size
const int HASH_SIZE = 100;
 
template <class ItemType>
class HashTable
{
public:
	HashTable(int hashSze = HASH_SIZE);
		
	bool IsEmpty(int key);
		
	bool  IsFull();
		
	int Hash(ItemType newItem);
		
	void Insert(ItemType newItem);
		
	void Append(int key, ItemType newItem);
		
	bool Remove(ItemType deleteItem, int key = -1);
		
	void Sort(int key);
		
	int TableSize();
		
	int TotalElems();
		
	int BucketSize(int key);
		
	int Count(ItemType searchItem);
		
	void MakeEmpty();
		
	~HashTable();
		
	
	//  -- ITERATOR CLASS --
	class Iterator;
		
 
	Iterator begin(int key){return(!IsEmpty(key)) ? head[key]:NULL;}
		
 
	Iterator end(int key=0){return NULL;}
		
	
private:
	struct node	
	{			
		ItemType currentItem;		
		node* next;	
	};
	node** head; // array of linked list declaration - front of each hash table cell
	int hashSize; // the size of the hash table (how many cells it has)
	int totElems; // holds the total number of elements in the entire table
	int* bucketSize; // holds the total number of elems in each specific hash table cell
};
 
//=========================  Implementation  ================================//
 
template<class ItemType>
HashTable<ItemType>::HashTable(int hashSze)
{
	hashSize = hashSze;
	head = new node*[hashSize];
	bucketSize = new int[hashSize];
	for(int x=0; x < hashSize; ++x)
	{
		head[x] = NULL;
		bucketSize[x] = 0;
	}
	totElems = 0;
}/* End of HashTable */
 
template<class ItemType>
bool HashTable<ItemType>::IsEmpty(int key)
{
	if(key >=0 && key < hashSize)
	{
		return head[key] == NULL;
	}
	return true;
}/* End of IsEmpty */
 
template<class ItemType>
bool HashTable<ItemType>::IsFull()
{
	try
	{
		node* location = new node;
		delete location;
		return false;
	}
	catch(std::bad_alloc&)
	{
		return true;
	}
}/* End of IsFull */
 
template<class ItemType>
int HashTable<ItemType>::Hash(ItemType newItem)
{	
	long h = 19937;
	std::stringstream convert;
 
	// convert the parameter to a string using "stringstream" which is done
	// so we can hash multiple datatypes using only one function
	convert << newItem;
	std::string temp = convert.str();
 
	for(unsigned x=0; x < temp.length(); ++x)
	{
		//hash funtion
		h = (h << 6) ^ (h >> 26) ^ temp[x];
	}
	return abs(h % hashSize);
} /* End of Hash */
 
template<class ItemType>
void HashTable<ItemType>::Insert(ItemType newItem)
{
	if(IsFull())
	{
        //std::cout<<"nINSERT ERROR - HASH TABLE FULLn";
	}
	else
	{
		int key = Hash(newItem);
		Append(key,newItem);
	}
}/* End of Insert */
 
template<class ItemType>
void HashTable<ItemType>::Append(int key, ItemType newItem)
{
	if(IsFull())
	{
        //std::cout<<"nAPPEND ERROR - HASH TABLE FULLn";
	}
	else
	{
		node* newNode = new node;  // adds new node
		newNode-> currentItem = newItem;
		newNode-> next = NULL;
	
		if(IsEmpty(key))
		{
			head[key] = newNode;
		}
		else
		{
			node* tempPtr = head[key];
			while(tempPtr-> next != NULL)
			{
				tempPtr = tempPtr-> next;
			}
			tempPtr-> next = newNode;
		}
		++bucketSize[key];
		++totElems;
	}
}/* End of Append */
 
template<class ItemType>
bool HashTable<ItemType>::Remove(ItemType deleteItem, int key) 
{
	bool isFound = false;
	node* tempPtr;
	if(key == -1)
	{
		key = Hash(deleteItem);
	}	
 
    if(IsEmpty(key))
    {
        //std::cout<<"nREMOVE ERROR - HASH TABLE EMPTYn";
    }
    else if(head[key]->currentItem == deleteItem)
    {
        tempPtr = head[key];
        head[key] = head[key]-> next;
        delete tempPtr;
        --totElems;
        --bucketSize[key];
        isFound = true;
    }
    else
    {        		
        for(tempPtr = head[key];tempPtr->next!=NULL;tempPtr=tempPtr->next)
        {
            if(tempPtr->next->currentItem == deleteItem)
            {
                node* deleteNode = tempPtr->next;
                tempPtr-> next = tempPtr-> next-> next;
                delete deleteNode;
                isFound = true;
                --totElems;
                --bucketSize[key];
                break;
            }
        }        
    }
	return isFound;
}/* End of Remove */
 

 
template<class ItemType>
int HashTable<ItemType>::Count(ItemType searchItem) 
{
	int key = Hash(searchItem);
	int search = 0;	
 
    if(IsEmpty(key))
    {
        //std::cout<<"nCOUNT ERROR - HASH TABLE EMPTYn";
    }
    else
    {        		
        for(node* tempPtr = head[key];tempPtr!=NULL;tempPtr=tempPtr->next)
        {
            if(tempPtr->currentItem == searchItem)
            {
                ++search;
            }
        }        
    }
	return search;
}/* End of Count */
 
 
template<class ItemType>
void HashTable<ItemType>::MakeEmpty()
{
    totElems = 0;
    for(int x=0; x < hashSize; ++x)
    {		
        if(!IsEmpty(x))
        {
            //std::cout << "Destroying nodes ...n";
            while(!IsEmpty(x))
            {
                node* temp = head[x];
                //std::cout << temp-> currentItem <<std::endl;
                head[x] = head[x]-> next;
                delete temp;
            }			
        }
        bucketSize[x] = 0;
    }
}/* End of MakeEmpty */
 
template<class ItemType>
HashTable<ItemType>::~HashTable() 
{
	MakeEmpty();
	delete[] head;
	delete[] bucketSize;
}/* End of ~HashTable */
 
#endif 