#include "studentsHashtableforstrings.h"
#include <assert.h>




const char* nameOfStudent(){
    return "Linus Jönsson";
}


HashtableForStrings::HashtableForStrings(int initialCapacity, bool isFixedCapacity)
    : _capacity( initialCapacity ), _isFixedCapacity(isFixedCapacity) {

    _theTable = new HashCell[_capacity];
    for (int i=0; i<_size; i++)
    {
        _theTable[i]._status = free;
        _theTable[i]._key = nullptr;
        _theTable[i]._value = nullptr;
        _theTable[i]._hash = NULL;
    }
}

void HashtableForStrings::insert(const std::string &key, const std::string &value){

    int hash = hashFromKey(key);
    int hashIndex = indexLocatedForKey(key, hash);

    if(_theTable[hashIndex]._status == free)
    {
        _theTable[hashIndex]._value = value;
        _theTable[hashIndex]._status = busy;
    }

    else if (_theTable[hashIndex]._status != free || _theTable[hashIndex]._status == deleted)
    {
        hashIndex++;
    }

}

bool HashtableForStrings::contains(const std::string &key){

    int hash = hashFromKey(key);
    int hashIndex = indexLocatedForKey(key, hash);

    while (_theTable != nullptr)
    {
        _theTable[hashIndex]._key == key;
        return true;
    }

    return false;
}

void HashtableForStrings::remove(const std::string &key){

    int hash = hashFromKey(key);
    int hashIndex = indexLocatedForKey(key, hash);

    while (_theTable != nullptr)
    {
        _theTable[hashIndex]._key = deleted;
        _theTable[hashIndex]._value = deleted;
    }
}

std::string& HashtableForStrings::valueFromKey(const std::string &key){

    int hash = hashFromKey(key);
    int hashIndex = indexLocatedForKey(key, hash);
    return _theTable[hashIndex]._value;
}


int HashtableForStrings::size(){

    return _size;
}

int HashtableForStrings::capacity(){

    return _capacity;
}

unsigned int HashtableForStrings::hashFromKey(const std::string &key){

    unsigned int hashVal = 0;
    for (int i=0; i<key.size(); i++)
        hashVal = 37*hashVal + key[i];
    return hashVal;
}

unsigned int HashtableForStrings::indexLocatedForKey(const std::string &key, unsigned int hash){

    hash = hashFromKey(key);
    int hashIndex = hash % 10;
    return hashIndex;
}



