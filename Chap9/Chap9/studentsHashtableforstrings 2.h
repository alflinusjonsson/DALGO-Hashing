#ifndef HASHTABLEFORSTRINGS_H
#define HASHTABLEFORSTRINGS_H

#include <string>

const char* nameOfStudent();



class HashtableForStrings
{   
public:
    HashtableForStrings(int initialCapacity, bool isFixedCapacity=true);

    void insert(const std::string &key, const std::string &value="");
    bool contains(const std::string &key);
    void remove(const std::string &key);
    std::string &valueFromKey(const std::string& key);

    int  size();
    int  capacity();

private:
    enum Status {
        free,
        busy,
        deleted
    };

    struct HashCell{
        std::string  _key;
        std::string  _value;
        unsigned int _hash;
        Status       _status;

        HashCell() : _status( free ) {}
        HashCell(const std::string &key,  const std::string &value, unsigned int hash)
            : _key(key), _value(value), _hash(hash), _status(busy) {}
    };

    int _capacity;
    bool _isFixedCapacity;
    HashCell *_theTable;
    int _size;


    unsigned int hashFromKey(const std::string &key);
    unsigned int indexLocatedForKey(const std::string &key, unsigned int hash);



};

#endif // HASHTABLEFORSTRINGS_H
