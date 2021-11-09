#include "array.hpp"

class String
{
private:

    Array<char> array_;

public:

    // RandomAccessIterator
    class Iterator;

    String();
    String(const char* cstring);
    String(char* cstring);
    String(char symbol, int amount_symbols);
    String(const String& string);

    const String& operator=(const String& other);

    char& operator[](int idx);
    char operator[](int idx) const;

    size_t length() const;
    
    void pushBack(char symbol);
    void popBack();

    char& Front();
    char& Back();

    const String& operator+=(char symbol);
    const String& operator+=(const String& other);    

    String operator+(char symbol) const;
    friend String operator+(char symbol, const String& string);
    friend String operator+(const String& first, const String& second);
    
    Array<char>::Iterator end() const;
    Array<char>::Iterator begin() const;

    Array<char>::Iterator Find(const String& substring) const;
    Array<char>::Iterator RFind(const String& substring) const;

    String getSubstring(int start, size_t amount_symbols) const;

    bool isEmpty() const;
    void Clear();

    friend std::ostream& operator<<(std::ostream& output, const String& string);
    friend std::istream& operator>>(std::istream& input, String& string);

    ~String() = default;
};



String operator+(char symbol, const String& string);
String operator+(const String& first, const String& second);

std::ostream& operator<<(std::ostream& output, const String& string);
std::istream& operator>>(std::istream& input, String& string);

Array<char>::Iterator begin(const String& string);
Array<char>::Iterator begin(String& string);
Array<char>::Iterator end(const String& string);
Array<char>::Iterator end(String& string);