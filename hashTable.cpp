#include "iostream"
#include "hashTable.h"
#include "math.h"
using namespace std;

size_t HashTable::hash_function(const KeyType &key) const {
    unsigned long int res ;
    unsigned long int k = 0;
    for (int j = 0; j < key.size(); j++) {
        k += key[j];
    }
    static double A = (sqrt(5) - 1) / 2;
    res = static_cast<unsigned long int>(_capacity * fmod(k * A, 1));
    return res;
}

HashTable::HashTable(size_t size) noexcept : _capacity(size), _filled(0){
    table = {};
    table.resize(_capacity);
}

HashTable::~HashTable() {}

void HashTable::insert(const KeyType &key, const ValueType &value) {
    pair<KeyType, ValueType> new_it = {key, value};
    _filled++;
    if (_capacity == 0) {
        _capacity = 1;
        table = {{new_it}};
        return;
    }

    if (getLoadFactor() > 0.75) {
        _capacity *= 2;

        vector<std::list<std::pair<KeyType, ValueType>>> table_new = {};
        table_new.resize(_capacity);
        for (size_t i = 0; i < table.size(); i++) {
            list<std::pair<KeyType, ValueType>> list_tmp = table[i];
            while (!list_tmp.empty()) {
                size_t ind = hash_function(list_tmp.back().first);
                table_new[ind].push_back(list_tmp.back());
                list_tmp.pop_back();
            }
        }
        table = table_new;
    }
    size_t ind = hash_function(key);
    table[ind].push_back(new_it);
}

bool HashTable::find(const KeyType &key, ValueType &value) const {
    size_t ind = hash_function(key);
    if (table[ind].empty()) {
        return false;
    }
    list<std::pair<KeyType, ValueType>> list_tmp = table[ind];
    while (!list_tmp.empty()) {
         if (list_tmp.back().first == key) {
             value = list_tmp.back().second;
             return true;
         }
         list_tmp.pop_back();
    }
    return false;
}

void HashTable::remove(const KeyType &key) {
    ValueType val;
    if (!find(key, val)) {
        cout << "This key isn't exists";
        return;
    }
    int ind = hash_function(key);
    list<std::pair<KeyType, ValueType>> list_tmp = table[ind];
    list<std::pair<KeyType, ValueType>> list_new;
    while (!list_tmp.empty()) {
        if (list_tmp.back().first != key) {
            list_new.push_back(list_tmp.back());
        }
        list_tmp.pop_back();
    }
    table[ind] = list_new;
    _filled--;
}

ValueType& HashTable::operator[](const KeyType &key) {
    ValueType val;
    if (!find(key, val)) {
        throw out_of_range("Key is not exist");
    }
    list<std::pair<KeyType, ValueType>> list_tmp = table[hash_function(key)];
    while (!list_tmp.empty()) {
        if (list_tmp.back().first == key) {
            return list_tmp.back().second;
        }
        list_tmp.pop_back();
    }
}

double HashTable::getLoadFactor() {
    return static_cast<double> (_filled) / _capacity;
}

void HashTable::print() {
    for (size_t i = 0; i < table.size(); i++) {
        list<std::pair<KeyType, ValueType>> list_tmp = table[i];
        while (!list_tmp.empty()) {
            cout << "Key:" << list_tmp.front().first << " Value:" << list_tmp.front().second << endl;
            list_tmp.pop_front();
        }
    }
}