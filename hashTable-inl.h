#include <stdexcept>

#include "hashFunctions.h"

using std::pair;
using std::runtime_error;
using std::vector;

template <typename K, typename V> HashTable<K, V>::HashTable() {
  this->size = 0;
  this->capacity = 5;
  this->table = new LinearDictionary<K, V> [capacity];
  this->maxLoadFactor = 0.75; // default load factor of 75%
}

template <typename K, typename V>
HashTable<K, V>::HashTable(float maxLoadFactor) {
  this->size = 0;
  this->capacity = 5;
  this->table = new LinearDictionary<K, V> [capacity];
  this->maxLoadFactor = maxLoadFactor;
}

template <typename K, typename V> HashTable<K, V>::~HashTable() {
  // clean up the dynamically allocated array of linearDictionary objects
  delete []table;
  this->table = nullptr;
}

template <typename K, typename V> int HashTable<K, V>::getSize() {
  return this->size;
}

template <typename K, typename V> bool HashTable<K, V>::isEmpty() {
  return (this-size == 0);
}

template <typename K, typename V> void HashTable<K, V>::insert(K key, V value) {
  // hash the key to determine where in the table to insert the value
  int bucket = hash(key, capacity);
  this->table[bucket].insert(key, value);
  size++;

  // check if our insertion has put us over our maxLoadFactor
  if(size/(float)capacity > maxLoadFactor){
    this->expandCapacity();
  }
}

template <typename K, typename V> void HashTable<K, V>::update(K key, V value) {
  // hash the given key to find where in the table the key is stored
  int bucket = hash(key, capacity);
  this->table[bucket].update(key, value);
}

template <typename K, typename V> V HashTable<K, V>::get(K key) {
  int bucket = hash(key, capacity);
  return this->table[bucket].get(key);
}

template <typename K, typename V> bool HashTable<K, V>::contains(K key) {
  int bucket = hash(key, capacity);
  return this->table[bucket].contains(key);
}

template <typename K, typename V> void HashTable<K, V>::remove(K key) {
  int bucket = hash(key, capacity);
  this->table[bucket].remove(key);
  // make sure to decrement size after removing a value
  size--;
}

template <typename K, typename V> vector<K> HashTable<K, V>::getKeys() {
  vector<K> ret;
  vector<K> temp;
  // since our table is an array of linearDictionaries that are implented as
  // vectors, we simply grab all vectors of keys and concatenate them
  // into one singular vector
  for(int i = 0; i < capacity; i++){
    temp = table[i].getKeys();
    ret.insert(end(ret), begin(temp), end(temp));
  }
  return ret;
}

template <typename K, typename V>
vector<pair<K, V>> HashTable<K, V>::getItems() {
  vector<pair<K, V>> ret;
  vector<pair<K, V>> temp;
  // since our table is an array of linearDictionaries that are implented as
  // vectors, we simply grab all linearDictionaries and concatenate them
  // into one singular vector
  for(int i = 0; i < capacity; i++){
    temp = table[i].getItems();
    ret.insert(end(ret), begin(temp), end(temp));
  }
  return ret;
}

template <typename K, typename V> void HashTable<K, V>::expandCapacity() {
  // create a pointer to the old table and allocate the new one before updating
  LinearDictionary<K, V>* oldTable = table; 
  int oldCapacity = this->capacity;
  this->capacity *= 2;
  this->table = new LinearDictionary<K, V> [capacity];

  // loop through the entire table and re-hash each key-value pair into our
  // newly allocated array
  vector<pair<K, V>> temp;
  int vecSize;
  for(int i = 0; i < oldCapacity; i++){
    temp = oldTable[i].getItems();
    vecSize = temp.size();  
      for(int j = 0; j < vecSize; j++){
        table[hash(temp[j].first, capacity)].insert(temp[j].first, temp[j].second);
      }
    }
  // clean up the previous table
  delete []oldTable;
  oldTable = nullptr;
}
