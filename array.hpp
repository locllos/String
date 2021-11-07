#include <sys/types.h>
#include <exception>

template <typename elem_t>
void Copy(elem_t* data_from, elem_t* data_to, int amount_elements)
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

        Copy(data_, new_data, capacity_);
        Fill(new_data + capacity_, elem_t(), new_capacity - capacity_);

        delete[] data_;

        data_ = new_data;
        capacity_ = new_capacity;
    }


public:

    // RandomAccessIterator
    class Iterator;

    Array() = default;    
    Array(elem_t* elements, int amount_elements) : size_(amount_elements), capacity_(amount_elements)
    {   
        size_ = amount_elements;
        reallocData(amount_elements);

        Copy(data_, elements, amount_elements);
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
    
    void pushBack(const elem_t& element)
    {
        if (size_ + 1 > capacity_)
        {
            reallocData((capacity_ + 1) * 2);
        }
        data_[size_++] = element;
    }
    
    void popBack()
    {   
        if (size_ < 1) throw std::underflow_error("size is equals to zero");

        if (size_ - 1 <= 2 * capacity_ / 3)
        {
            reallocData(2 * capacity_ / 3);
        }
        data_[size_--] = elem_t();
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

    Iterator End() const {return Iterator(nullptr);}
    Iterator Begin() const {return Iterator(&Front());}

    bool isEmpty() const {return size_ == 0;}
    void Clear()
    {
        size_ = 0;

        Fill(data_, elem_t(), capacity_);
    }

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

        bool operator<(const Iterator& other)
        {
            return element_ < other.element_;
        }

        bool operator>(const Iterator& other)
        {
            return element_ > other.element_;
        }

        bool operator!=(const Iterator& other)
        {
            return element_ != other.element_;
        }
        
        elem_t& operator*()
        {
            return *element_;
        }
    };
};