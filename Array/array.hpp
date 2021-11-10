#include <sys/types.h>
#include <ostream>
#include <istream>
#include <exception>

template <typename elem_t>
void Copy(const elem_t* data_from, elem_t* data_to, int amount_elements)
{
    for (int i = 0; i < amount_elements; ++i)
    {
        data_to[i] = data_from[i];
    }
}

template <typename elem_t>
void Fill(elem_t* data_from, const elem_t& filling_element, int amount_elements)
{
    for (int i = 0; i < amount_elements; ++i)
    {
        data_from[i] = filling_element;
    }
}


template <typename elem_t>
class Array
{
private:

    size_t size_ = 0;
    size_t capacity_ = 0;

    elem_t* data_ = nullptr;

private:

    void reallocData(size_t new_capacity)
    {
        elem_t* new_data = new elem_t[new_capacity];

        if (new_data == nullptr) throw std::overflow_error("result of realloc is nullptr");

        Copy(data_, new_data, std::min(new_capacity, capacity_));

        if (capacity_ < new_capacity)
        {
            Fill(new_data + capacity_, elem_t(), new_capacity - capacity_);
        }

        delete[] data_;

        data_ = new_data;
        capacity_ = new_capacity;
    }


public:

    // RandomAccessIterator
    class Iterator;

    Array() = default;    
    Array(const elem_t* elements, int amount_elements) : size_(amount_elements)
    {   
        reallocData(amount_elements);

        Copy(elements, data_, amount_elements);
    }
    Array(const elem_t& element, int amount_elements) : size_(amount_elements)
    {   
        size_ = amount_elements;
        reallocData(amount_elements);

        Fill(data_, element, amount_elements);
    }

    Array(const Array& other) : size_(other.size())
    {
        reallocData(other.capacity_);

        Copy(other.data_, data_, size_);
    }

    const Array& operator=(const Array& other)
    {   
        size_ = other.size();
        
        reallocData(other.capacity_);

        Copy(other.data_, data_, size_);

        return *this;
    }

    elem_t& operator[](int idx)
    {   
        if (idx < 0 || idx >= size_) throw std::out_of_range("exceeding the boundaries");

        return  data_[idx]; 
    }

    elem_t operator[](int idx) const
    {
        if (idx < 0 || idx >= size_) throw std::out_of_range("exceeding the boundaries");

        return  data_[idx]; 
    }

    void Set(const elem_t& element, int idx)
    {
        if (idx < 0 || idx >= size_) throw std::out_of_range("exceeding the boundaries");

        data_[idx] = element;
    }

    elem_t Get(int idx) const
    {
        if (idx < 0 || idx >= size_) throw std::out_of_range("exceeding the boundaries");

        return data_[idx];
    }

    size_t size() const {return size_;}    

    void pushBack(const elem_t* elements, int amount_elements)
    {
        if (size_ + amount_elements > capacity_)
        {
            reallocData((capacity_ + 1) * 2);
        }
        Copy(elements, data_ + size_, amount_elements);

        size_ += amount_elements;
    }

    void pushBack(const Array& other)
    {
        pushBack(other.data_, other.size_);
    }

    void pushBack(const elem_t& element)
    {
        pushBack(&element, 1);
    }
    
    void popBack()
    {   
        if (size_ < 1) throw std::underflow_error("size is equals to zero");

        --size_;

        if (size_ < 2 * capacity_ / 3)
        {
            reallocData(2 * capacity_ / 3);
        }
    }

    elem_t& Front() 
    {   
        if (data_ == nullptr || size_ == 0) throw std::underflow_error("size is equals to zero");

        return *data_;
    }
    
    elem_t& Back() 
    {
        if (data_ == nullptr || size_ == 0) throw std::underflow_error("size is equals to zero");;

        return data_[size_ - 1];
    }

    Iterator end() const {return Iterator(&data_[size_]);}
    Iterator begin() const {return Iterator(&data_[0]);}

    bool isEmpty() const {return size_ == 0;}
    void Clear()
    {
        size_ = 0;

        Fill(data_, elem_t(), capacity_);
    }

    template <typename T>
    friend std::ostream& operator<<(std::ostream& output, const Array<T>& array);

    ~Array()
    {
        size_ = 0;
        capacity_ = 0;

        delete[] data_;

        data_ = nullptr;
    }

    class Iterator
    {
    private:

        elem_t* element_ = nullptr;

    public:

        Iterator() = default;
        Iterator(elem_t* element) : element_(element) {};
        Iterator(const Iterator& other) : element_(other.element_) {};

        const Iterator& operator=(const Iterator& other)
        {
            element_ = other.element_;

            return *this;
        }

        const Iterator& operator+=(int idx)
        {
            if (element_ != nullptr)
            {
                element_ += idx; 
            }
            return *this;
        }

        const Iterator& operator-=(int idx)
        {
            return *this += (-1) * idx;
        }

        const Iterator& operator++()    // prefix
        {      
            return *this += 1;
        }

        const Iterator& operator++(int) // postfix
        {
            Iterator iterator = *this;
            
            ++*this;
            
            return iterator;
        }

        const Iterator& operator--()
        {
            return *this -= 1;
        }

        const Iterator& operator--(int)
        {
            Iterator iterator = *this;
            
            --*this;
            
            return iterator;
        }

        Iterator operator+(int offset)
        {
            Iterator new_iter(*this);

            new_iter += offset;

            return new_iter;
        }

        Iterator operator-(int offset)
        {
            Iterator new_iter(*this);

            new_iter -= offset;

            return new_iter;
        }

        int operator+(const Iterator& rhs)
        {
            return element_ + rhs.element_;
        }

        int operator-(const Iterator& rhs)
        {
            return element_ - rhs.element_;
        }

        bool operator<(const Iterator& other)
        {
            return element_ < other.element_;
        }

        bool operator>(const Iterator& other)
        {
            return element_ > other.element_;
        }

        bool operator<=(const Iterator& other)
        {
            return element_ <= other.element_;
        }

        bool operator>=(const Iterator& other)
        {
            return element_ >= other.element_;
        }

        bool operator!=(const Iterator& other)
        {
            return element_ != other.element_;
        }

        bool operator==(const Iterator& other)
        {
            return element_ == other.element_;
        }
        
        elem_t& operator*()
        {
            return *element_;
        }
    };
};

template<class elem_t> 
auto begin(const Array<elem_t>& array)
{
    return array.begin();
}

template<class elem_t> 
auto begin(Array<elem_t>& array)
{
    return array.begin();
}

template<class elem_t> 
auto end(const Array<elem_t>& array)
{
    return array.end();
}

template<class elem_t> 
auto end(Array<elem_t>& array)
{
    return array.end();
}

template <typename elem_t>
std::ostream& operator<<(std::ostream& output, const Array<elem_t>& array)
{   
    output << "Array" << " content: " << std::endl;


    output << "\tinitialized array cells: " << std::endl;
    
    if (array.size_ == 0) 
    {
        output << "\t(empty)" << std::endl;
    }

    for (int i = 0; i < array.size_; ++i)
    {
        output << "\t\t[" << i << "]: " << array.data_[i] << std::endl; 
    }

    output << std::endl << "\tfree array cells: " << std::endl;

    if (array.size_ == array.capacity_)
    {
        output << "\t(no free array cells)" << std::endl;
    }

    for (int i = array.size_; i < array.capacity_; ++i)
    {
        output << "\t\t[" << i << "]: " << array.data_[i] << std::endl; 
    }


    return output;
}