#include <sys/types.h>

class String
{
private:

    size_t length_;
    char* data_;

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
    friend String operator+(const String& lhs, const String& rhs);

    Iterator End() const;
    Iterator Begin() const;

    Iterator Find(const String& substring) const;
    Iterator RFind(const String& substring) const;

    String getSubstring(int start, size_t amount_symbols) const;

    bool isEmpty() const;
    void Clear();

    // learn about input/output streams

    ~String();

    class Iterator
    {
    private:

        char* element_;

    public:

        Iterator();
        Iterator(const char& element);

        const Iterator& operator=(const Iterator& other);
        const Iterator& operator=(const char& element);

        const Iterator& operator++();    // prefix
        const Iterator& operator++(int); // postfix

        const Iterator& operator--();    
        const Iterator& operator--(int); 

        bool operator!=(const Iterator& other);
        
        char operator*();
    };
};

String operator+(char symbol, const String& string);
String operator+(const String& lhs, const String& rhs);