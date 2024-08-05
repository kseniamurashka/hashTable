#include <iostream>
#include "hashTable.h"

using namespace std;

int main() {
    HashTable test(5);
    test.insert("1", 1);
    test.insert("2", 123);
    test.insert("13", 678);
    test.insert("6", 0);
    test.insert("10", -123);
    test.insert("cat", 12.33);
    test.insert("hello", 2);
    test.insert("and", 23);
    test.insert("hi", 123);
    test.insert("hi", 3);
    test.insert("0", 134);
    test.print();

    test.remove("hi");
    cout << endl;
    //ValueType y = test["2"];
    //bool t = test.find("2", y);
    //cout << y << endl;
    test.print();
    return 0;
}
