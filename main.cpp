#include "hashTable.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{

ifstream infile;
string fileName = "data.txt";
infile.open(fileName);

hashTable quadProbe(11);
hashTable doubleHash(11);

if(infile.is_open())
{
int val;
while(infile >> val)
{
quadProbe.insertQuadProbe(val);
doubleHash.insertDoubleHash(val);
}
}
else
{
cout<<"File could not be opened!\n";
}



int choice;



while(choice!=5)
{
  cout<<"Choose one operation from the options below:\n";
  cout<<"1. Insert\n";
  cout<<"2. Delete\n";
  cout<<"3. Find\n";
  cout<<"4. Print\n";
  cout<<"5. Exit\n";

cin>>choice;
if(choice==1)
{
  int givenVal = 42;

  cout<<"Enter the value to be inserted:\n";
  cin>>givenVal;

  cout<<"\n";
  quadProbe.insertQuadProbe(givenVal);
  doubleHash.insertDoubleHash(givenVal);
  quadProbe.printTable();
  doubleHash.printTable();
}

else if(choice==2)
{
  int givenVal = 42;

  cout<<"Enter the value to be deleted:\n";
  cin>>givenVal;

  quadProbe.deleteQuadProbe(givenVal);
  doubleHash.deleteDoubleHash(givenVal);
}

else if(choice==3)
{
  int givenVal;

  cout<<"Enter the value to be searched for:\n";
  cin>>givenVal;

  bool found1 = quadProbe.findQuadProbe(givenVal);
  bool found2 = doubleHash.findDoubleHash(givenVal);

  if(found1)
  {
    cout<<givenVal<<" was found in Quadratic Probing.\n";
  }
  else
  {
    cout<<givenVal<<" was not found in Quadratic Probing.\n";
  }

  if(found2)
  {
    cout<<givenVal<<" was found in Double Hashing.\n";
  }
  else
  {
    cout<<givenVal<<" was not found in Double Hashing.\n";
  }
}

else if(choice==4)
{
  cout<<"\n";
  cout<<"Quadratic Probing\n";
  quadProbe.printTable();
  cout<<"Double Hashing\n";
  doubleHash.printTable();
}

else if(choice==5)
{
  return 0;
}

else
{
  cout<<"That was not in the list of options!\n";
}
}
}
