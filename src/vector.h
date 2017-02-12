//
// Created by 이형욱 on 12/02/2017.
//

#ifndef SRC_VECTOR_H
#define SRC_VECTOR_H

#endif //SRC_VECTOR_H

template <class T>
class VectorForwardIterator{
private:
    size_t n;
    int index;
    T *ptr;
    typedef T         value_type;
    typedef Distance  difference_type;
    typedef Pointer   pointer;
    typedef Reference reference;
    typedef Category  iterator_category;

public:
    VectorForwardIterator();
    VectorForwardIterator(int index, T *ptr, size_t n);
    ~VectorForwardIterator();

    // ========== Iterator operations ===========
    template <typename T>
    void advance (Distance n); //    Advance iterator (function template )

    // Iterator to beginning (function template )
    // VectorForwardIterator begin();

    // Iterator to end (function template )
    // VectorForwardIterator end();

    // Get iterator to previous element (function template )
    template <typename T>
    VectorForwardIterator& prev();

    // Get iterator to next element (function template )
    template <typename T>
    VectorForwardIterator& next();

    // Iterator generators:
    //            back_inserter
    //    Construct back insert iterator (function template )
    //    front_inserter
    //            Constructs front insert iterator (function template )
    //    inserter
    //            Construct insert iterator (function template )
    //    make_move_iterator
    //            Construct move iterator (function template )

    // Operator assignment
    void operator++();
    void operator--();
    VectorForwardIterator& operator+(int n);
    VectorForwardIterator& operator-(int n);
};


VectorForwardIterator::VectorForwardIterator()
{
    this->index = 0;
    this->ptr = nullptr;
    this->n = 0;
}

VectorForwardIterator::VectorForwardIterator(int index, T *ptr, size_t n)
{
    this->index = index;
    this->ptr = ptr;
    this->n = n;
}

VectorForwardIterator::~VectorForwardIterator(){};

// ========== Iterator operations ===========
void VectorForwardIterator::advance (Distance n)
{
    for (int i=0; i < abs(n); i++){
        if (n > 0) this->next();
        else    this->prev();
    }
}

// Get iterator to previous element (function template )
template <typename T>
VectorForwardIterator& VectorForwardIterator::prev()
{
    ptr += sizeof(T);

    if (index < 0)
        throw Exception("Low IndexError");
    if (index >= n)
        throw Exception("High IndexError");
    return this;
}

// Get iterator to next element (function template )
template <typename T>
VectorForwardIterator& VectorForwardIterator::next()
{
    ptr -= sizeof(T);

    if (index < 0)
        throw Exception("Low IndexError");
    if (index >= n)
        throw Exception("High IndexError");
    return this;
}

// Operator assignment
void VectorForwardIterator::operator++()
{
    this->next();
}

void VectorForwardIterator::operator--()
{
    this->prev();
}

VectorForwardIterator& VectorForwardIterator::operator+ (int n)
{
    this->advance(n);
    return this;
}

VectorForwardIterator& VectorForwardIterator::operator- (int n)
{
    this->advance(-n);
    return this;
}


template <class T>
class vector{
public:
    // Member functinos
    vector();
    ~vector();
    operator=();

    //    Iterators:
    iterator begin();
    const iterator begin() const;
    //    Return iterator to beginning (public member function )
    end
    //            Return iterator to end (public member function )
//    rbegin
//    //            Return reverse iterator to reverse beginning (public member function )
//            rend
//    //            Return reverse iterator to reverse end (public member function )
//    cbegin
//    //            Return const_iterator to beginning (public member function )
//            cend
//    //            Return const_iterator to end (public member function )
//    crbegin
//    //            Return const_reverse_iterator to reverse beginning (public member function )
//            crend
//    //            Return const_reverse_iterator to reverse end (public member function )

    //    Capacity:
            size
    //    Return size (public member function )
//            max_size
//    //            Return maximum size (public member function )
//    resize
//    //            Change size (public member function )
//            capacity
//    //            Return size of allocated storage capacity (public member function )
//    empty
//    //            Test whether vector is empty (public member function )
//            reserve
//    //            Request a change in capacity (public member function )
//    shrink_to_fit
//    //            Shrink to fit (public member function )

    //    Element access:
    operator[]
    //    Access element (public member function )
    at
    //            Access element (public member function )
//            front
//    //            Access first element (public member function )
//    back
//    //            Access last element (public member function )
//            data
//    //            Access data (public member function )

    //    Modifiers:
            assign
    //    Assign vector content (public member function )
    push_back
    //            Add element at the end (public member function )
            pop_back
    //                Delete last element (public member function )
//            insert
//    //            Insert elements (public member function )
//    erase
//    //            Erase elements (public member function )
//            swap
//    //            Swap content (public member function )
//    clear
//    //            Clear content (public member function )
//            emplace
//    //            Construct and insert element (public member function )
//    emplace_back
//    //            Construct and insert element at the end (public member function )

    //    Allocator:
//            get_allocator
//    //    Get allocator (public member function )

    //    Non-member function overloads
//    relational operators
//    //            Relational operators for vector (function template )
//    swap
//    //            Exchange contents of vectors (function template )
//
//    //    Template specializations
//            vector<bool>
//    //            Vector of bool (class template specialization )
};

