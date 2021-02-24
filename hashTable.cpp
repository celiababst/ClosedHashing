#include "hashTable.h"
#include <string>
#include <iostream>

using namespace std;

hashTable::hashTable(int size)
{
  table = new int[size];
  m_size = size;
}

hashTable::~hashTable()
{
  for(int i=0; i<m_size; i++)
  {
    if(table[i]!=NULL)
    {
      table[i] = NULL;
    }
  }
  //delete[] table; this gets rid of many memory leaks; however, my program starts grabbing garbage values if I do so.
}

void hashTable::insertQuadProbe(int val)
{
  int originalHashNum;
  originalHashNum = hashFunc(val);
  bool found = findQuadProbe(val);
  if(found)
  {
    cout<<"That number is already in the Quadratic Probing table!\n";
  }
  else
  {
    double loadSize = calcLoad();

    if(loadSize > 0.5)
    {
      rehashQuadProbe();
    }

      int hashNum = originalHashNum;
      int k = m_size;
      for(int i = 0; i < k; i++)
      {
        if(table[hashNum]!=NULL)
        {
          hashNum = ((originalHashNum + (i * i)) % m_size);
        }
      }
      if(table[hashNum]==NULL)
      {
        table[hashNum] = val;
        cout<<val<<" has successfully been inserted at location "<<hashNum<<" using quadratic probing.\n";
      }
      else
      {
        cout<<val<<" could not be inserted using quadratic probing.\n";
      }
  }
}

void hashTable::insertDoubleHash(int val)
{
  int originalHashNum;
  originalHashNum = hashFunc(val);
  bool found = findDoubleHash(val);
  if(found)
  {
    cout<<"That number is already in the Double Hashing table!\n";
  }
  else
  {
    double loadSize = calcLoad();
    if(loadSize > 0.5)
    {
      rehashDoubleHash();
    }
      int hashNum = originalHashNum;
      int k = m_size;
      for(int i = 0; i < k; i++)
      {
        if(table[hashNum]!=NULL)
        {
          hashNum = (originalHashNum + i*(5 - (val % 5))) % m_size;
        }
      }
      if(table[hashNum]==NULL)
      {
        table[hashNum] = val;
        cout<<val<<" has successfully been inserted at location "<<hashNum<<" using double hashing.\n";
      }
      else
      {
        cout<<val<<" could not be inserted using double hashing.\n";
      }
  }
}


void hashTable::deleteQuadProbe(int val)
{
  bool deleted = false;
  int hashNum;
  int originalHashNum;
  bool found = findQuadProbe(val);
  if(found)
  {
    originalHashNum = hashFunc(val);
    hashNum = originalHashNum;
    while(deleted == false)
    {
      for(int i = 0; i < m_size; i++)
      {
        if(table[hashNum]==val)
        {
          table[hashNum]=NULL;
          deleted = true;
          cout<<val<<" was successfully deleted.\n";
          break;
        }
        else
        {
          hashNum = ((originalHashNum + (i * i)) % m_size);
        }
      }
    }
  }
  else
  {
    cout<<"The value is not in the table!\n";
  }
}

void hashTable::deleteDoubleHash(int val)
{
  bool deleted = false;
  int hashNum;
  int originalHashNum;
  bool found = findDoubleHash(val);
  if(found)
  {
    originalHashNum = hashFunc(val);
    hashNum = originalHashNum;
    while(deleted == false)
    {
      for(int i = 0; i < m_size; i++)
      {
        if(table[hashNum]==val)
        {
          table[hashNum]=NULL;
          deleted = true;
          cout<<val<<" was successfully deleted.\n";
          break;
        }
        else
        {
          hashNum = (originalHashNum + i*(5 - (val % 5))) % m_size;
        }
      }
    }
  }
  else
  {
    cout<<"The value is not in the table!\n";
  }
}


int hashTable::hashFunc(int val)
{
  int index	=	val % m_size;
  return index;
}


void hashTable::printTable()
{
  for(int i=0;i<m_size;i++)
  {
    cout<<i<<": "<<table[i]<<"\n";
  }
  cout<<"\n";
}


bool hashTable::findQuadProbe(int val)
{
  int bucketNum = hashFunc(val);
  bool found = false;
  if(table[bucketNum]==val)
  {
    found = true;
  }
  else
  {
    int hashNum = bucketNum;
    int k = m_size;
    for(int i = 0; i < k; i++)
    {
      if(table[hashNum]!=NULL)
      {
        if(table[hashNum]==val)
        {
          found = true;
        }
        hashNum = (bucketNum + (i * i)) % m_size;
      }
    }
  }
  return found;
}

bool hashTable::findDoubleHash(int val)
{
  int bucketNum = hashFunc(val);
  bool found = false;
  if(table[bucketNum]==val)
  {
    found = true;
  }
  else
  {
    int hashNum = bucketNum;
    int k = m_size;
    for(int i = 0; i < k; i++)
    {
      if(table[hashNum]!=NULL)
      {
        if(table[hashNum]==val)
        {
          found = true;
        }
        hashNum = (bucketNum + i*(5 - (val % 5))) % m_size;
      }
    }
  }
  return found;
}

double hashTable::calcLoad()
{
  int n = 0; //number of elements in the hash table
  for(int i=0;i<m_size;i++)
  {
    if (table[i]!=NULL)
    {
      n++;
    }
  }
  double loadSize = n/m_size;
  return loadSize;
}

void hashTable::rehashQuadProbe()
{
  int newSize = m_size * 2;
   for(int i = 2; i <= newSize/2; i++)
   {
       if (newSize % i == 0)
       {
         newSize++;
       }
   }
  hashTable newTable = hashTable(newSize);
  for(int i = 0; i < m_size; i++)
  {
    if(table[i]!=NULL)
    {
    int val = table[i];
    newTable.insertQuadProbe(val);
    }
  }
  m_size = newSize;
  table = new int[m_size];

  for(int i = 0; i < m_size; i++)
  {
    table[i] = newTable.table[i];
  }
  newTable.~hashTable();
}

void hashTable::rehashDoubleHash()
{
  int newSize = m_size * 2;
   for(int i = 2; i <= newSize/2; i++)
   {
       if(newSize % i == 0)
       {
         newSize++;
       }
   }
  hashTable newTable = hashTable(newSize);
  for(int i = 0; i < m_size; i++)
  {
    if(table[i]!=NULL)
    {
    int val = table[i];
    newTable.insertDoubleHash(val);
    }
  }
  m_size = newSize;
  table = new int[m_size];

  for(int i = 0; i < m_size; i++)
  {
    table[i] = newTable.table[i];
  }
  newTable.~hashTable();
}
