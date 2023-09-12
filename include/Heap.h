#pragma once

#include <vector>

namespace heap
{

template <typename DataType>
class Heap
{
public:
    using ContainerType = std::vector<DataType>;
    using DataConstRef = const DataType&;
    using DataUniversalRef = DataType&&;
    using SizeType  = std::size_t;

    Heap();

    ~Heap();

    /**
     * @brief Copy constructor 
     */ 
    Heap(const Heap& other);

    /**
     * @brief Copy assignment operator 
     */ 
    Heap& operator=(const Heap& other);

    /**
     * @brief Move constructor
     */ 
    Heap(Heap&& other);

    /**
     * @brief Move assignment operator 
     */ 
    Heap& operator=(Heap&& other) noexcept;

    DataConstRef Top() const;

    bool IsEmpty() const;

    SizeType Size() const;

    void Push(DataUniversalRef data);

    void Push(DataConstRef data);

    void Pop();


private:
    ContainerType mContainer;

private:
    void heapify(size_t index);
};

template <typename DataType>
Heap<DataType>::Heap()
{

}

template <typename DataType>
Heap<DataType>::~Heap()
{

}

template <typename DataType>
typename Heap<DataType>::DataConstRef Heap<DataType>::Top() const
{
    return mContainer.at(0);
}

template <typename DataType>
bool Heap<DataType>::IsEmpty() const
{
    return mContainer.empty();
}

template <typename DataType>
void Heap<DataType>::Pop()
{
    std::swap(mContainer.front(), mContainer.back());
    mContainer.pop_back();

    heapify(0);
}

template <typename DataType>
typename Heap<DataType>::SizeType Heap<DataType>::Size() const
{
    return mContainer.size();
}

template <typename DataType>
void Heap<DataType>::heapify(size_t index) 
{
    auto largestIndex = index;
    auto leftIndex = 2 * index + 1;
    auto rightIndex = 2 * index + 2;

    if ((leftIndex < mContainer.size()) && (mContainer.at(leftIndex) > mContainer.at(largestIndex))) 
    {
        largestIndex = leftIndex;
    }

    if ((rightIndex < mContainer.size()) && (mContainer.at(rightIndex) > mContainer.at(largestIndex))) 
    {
        largestIndex = rightIndex;
    }

    if (largestIndex != index) 
    {
        std::swap(mContainer.at(index), mContainer.at(largestIndex));

        // Recursively heapify the affected sub-tree
        heapify(largestIndex);
    }
}

template <typename DataType>
void Heap<DataType>::Push(DataConstRef data)
{
    mContainer.push_back(data);
    auto index = mContainer.size() - 1;

    // Maintain the max heap property by repeatedly comparing with the parent
    while (index > 0) 
    {
        size_t parent = (index - 1) / 2;
        if (mContainer.at(index) > mContainer.at(parent)) 
        {
            std::swap(mContainer.at(index), mContainer.at(parent));
            index = parent;
        } 
        else 
        {
            break; // Stop if the parent is greater or equal
        }
    }
}

} // namespace heap