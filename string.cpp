#include <cstring>
#include "string.h"

String::String() : array_() {};
String::String(const char* cstring) : array_(cstring, sizeof(cstring)) {};
String::String(char* cstring) : array_(cstring, strlen(cstring)) {};
String::String(char symbol, int amount_symbols) : array_(symbol, amount_symbols) {};
String::String(const String& string) : array_(string.array_) {};

const String& String::operator=(const String& other)
{
    array_ = other.array_;

    return *this;
}

char& String::operator[](int idx)
{
    return array_[idx];
}

char String::operator[](int idx) const
{
    return array_[idx];
}

size_t String::length() const
{
    return array_.size();
}

void String::pushBack(char symbol)
{
    array_.pushBack(symbol);
}

void String::popBack()
{
    array_.popBack();
}

char& String::Front()
{
    return array_.Front();
}

char& String::Back()
{
    return array_.Back();
}

const String& String::operator+=(char symbol)
{
    array_.pushBack(symbol);

    return *this;
}

const String& String::operator+=(const String& other)
{
    array_.pushBack(other.array_);

    return *this;
}

String String::operator+(char symbol) const
{
    String new_string(*this);

    new_string += symbol;

    return new_string;
}

String operator+(char symbol, const String& string)
{
    String new_string(string);

    new_string += symbol;

    return new_string;
}

String operator+(const String& first, const String& second)
{
    String new_string(first);

    new_string += second;

    return new_string;
}

Array<char>::Iterator String::end() const
{
    return array_.end(); 
}

Array<char>::Iterator String::begin() const
{
    return array_.begin();
}

Array<char>::Iterator String::Find(const String& substring) const
{   
    for (auto main_iter = begin(); main_iter < end(); ++main_iter)
    {   
        auto haystack = main_iter;
        auto needle = substring.begin();

        for (; haystack < end() && needle < substring.end(); 
               ++haystack, ++needle)
        {
            if (*haystack != *needle)
            {
                break;
            }
        }
        if (needle == substring.end())
        {
            return haystack;
        }
    }
    return end();
}


Array<char>::Iterator String::RFind(const String& substring) const
{   
    for (auto main_iter = end() - substring.length() - 1; main_iter >= begin(); --main_iter)
    {
        auto haystack = main_iter;
        auto needle = --substring.end();

        for (; haystack >= begin() && needle >= substring.begin(); 
               --haystack, --needle)
        {
            if (*haystack != *needle)
            {
                break;
            }
        }
        if (needle == substring.begin() - 1)
        {
            return haystack;
        }
    }
    return end();
}

String String::getSubstring(int start, size_t amount_symbols) const
{   
    if (start < 0 || start + amount_symbols > array_.size()) 
    {
        throw std::range_error("start < 0 || start + amount_symbols > array_.size()");
    }

    String substring('\0', amount_symbols);
    for (int i = 0; i < amount_symbols; ++i)
    {
        substring.array_[i] = array_[i + start];
    }

    return substring;
}

bool String::isEmpty() const
{
    return array_.isEmpty();
}

void String::Clear()
{
    array_.Clear();
}

std::ostream& operator<<(std::ostream& output, const String& string)
{
    for (auto& symbol : string)
    {
        output << symbol;
    }

    return output;
}

std::istream& operator>>(std::istream& input, String& string)
{   
    char symbol = '\0';

    input.get(symbol);
    while (!isspace(symbol))
    {
        string.pushBack(symbol);
        
        input.get(symbol);
    }

    return input;
}

Array<char>::Iterator begin(const String& string)
{
    return string.begin();
}


Array<char>::Iterator begin(String& string)
{
    return string.begin();
}


Array<char>::Iterator end(const String& string)
{
    return string.end();
}


Array<char>::Iterator end(String& string)
{
    return string.end();
}