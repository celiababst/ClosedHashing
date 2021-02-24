#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>

using namespace std;

class hashTable
{
public:
  hashTable(int size);
  ~hashTable();
  int hashFunc(int val);
  void insertQuadProbe(int val);
  void insertDoubleHash(int val);
  void printTable();
  bool findQuadProbe(int val);
  bool findDoubleHash(int val);
  void deleteQuadProbe(int val);
  void deleteDoubleHash(int val);
  double calcLoad();
  void rehashQuadProbe();
  void rehashDoubleHash();



private:
  int m_size;
  //int table[];
  int* table;

};
#endif
