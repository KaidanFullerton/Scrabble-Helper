#include <stdexcept>
using std::pair;
using std::runtime_error;
using std::vector;

template <typename K, typename V> LinearDictionary<K, V>::LinearDictionary() {
// nothing special to do in constructor
}

template <typename K, typename V> LinearDictionary<K, V>::~LinearDictionary() {
// nothing special to do in deconstructor
}

template <typename K, typename V> int LinearDictionary<K, V>::getSize() {
  return this->items.size();
}

template <typename K, typename V> bool LinearDictionary<K, V>::isEmpty() {
  return (this->items.size() == 0);
}

template <typename K, typename V>
void LinearDictionary<K, V>::insert(K key, V value) {
  // linear scan of vector to check for duplicate, if found throw error and exit
  for(int i = 0; i < this->getSize(); i++){
    if(this->items[i].first == key){
      throw runtime_error("Key already exists within dictionary");
    }
  }
    this->items.push_back(pair<K, V>(key, value));
}

template <typename K, typename V>
void LinearDictionary<K, V>::update(K key, V value) {
  // linear scan of vector to check for key to update
  for(int i = 0; i < this->getSize(); i++){
    if(this->items[i].first == key){
      this->items[i].second = value;
      return;
    }
  }
  // if key isn't found, we reach this point and throw a runtime error
  throw runtime_error("Key is not found in the dictionary");
}

template <typename K, typename V> V LinearDictionary<K, V>::get(K key) {
  // linear scan of vector to check for key to get
  for(int i = 0; i < this->getSize(); i++){
    if(this->items[i].first == key){
      return this->items[i].second;
    }
  }
  // if key isn't found, we reach this point and throw a runtime error
  throw runtime_error("Key is not found in the dictionary");
}

template <typename K, typename V> bool LinearDictionary<K, V>::contains(K key) {
  // linear scan of vector to search for presence of the desired key
  for(int i = 0; i < this->getSize(); i++){
    if(this->items[i].first == key){
      return true;
    }
  }
  // if key isn't found, we reach this point and return false
  return false;
}

template <typename K, typename V> void LinearDictionary<K, V>::remove(K key) {
  // linear scan of vector to search for key to remove
  for(int i = 0; i < this->getSize(); i++){
    if(this->items[i].first == key){
      removeFromVector(this->items, i);
      return;
    }
  }
  // lf key isn't found, we reach this point and throw a runtime error
  throw runtime_error("Key was not found within dictionary");
}

template <typename K, typename V> vector<K> LinearDictionary<K, V>::getKeys() {
  vector<K> keys;
  // loop through vector of pairs to strip off the values; thus, giving us a
  // vector of only keys
  for(int i = 0; i < this->getSize(); i++){
    keys.push_back(this->items[i].first);
  }
  return keys;
}

template <typename K, typename V>
vector<pair<K, V>> LinearDictionary<K, V>::getItems() {
  // items is already implemented as a vector of key-value pairs
  return this->items;
}

template <typename T> void removeFromVector(vector<T> &list, int index){
  if(index < 0 || index >= list.size()){
    throw runtime_error("index out of range in removeFromVector");
  }
  list.erase(list.begin()+index, list.begin()+index+1);
}

