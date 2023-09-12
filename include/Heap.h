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
    using SizeType  = std::size_t;

    /**
     * @brief Constructor 
     */ 
    Heap() = default;

    /**
     * @brief Destructor 
     */ 
    ~Heap() = default;

    /**
     * @brief Copy constructor 
     */ 
    Heap(const Heap& other) = default;

    /**
     * @brief Copy assignment operator 
     */ 
    Heap& operator=(const Heap& other) = default;

    /**
     * @brief Move constructor
     */ 
    Heap(Heap&& other) = default;

    /**
     * @brief Move assignment operator 
     */ 
    Heap& operator=(Heap&& other) noexcept = default;

    /**
     * @brief Access the top element
     * @returns Const reference to the top element
     */ 
    DataConstRef Top() const;

    /**
     * @brief Check if heap is empty
     * @returns true iff heap is empty
     */ 
    bool IsEmpty() const;

    /**
     * @brief Check heap size
     * @returns Number of elements in the heap
     */ 
    SizeType Size() const;

    /**
     * @brief Emplace element in heap. 
     * @param arguments to create new object and insert to heap
     */ 
    template< class... Args >
    void Emplace(Args&&... args);

    /**
     * @brief Push element in heap. 
     * @param data to push
     */ 
    void Push(DataConstRef data);

    /**
     * @brief Pop top element from heap
     */ 
    void Pop();


private:
    ContainerType mContainer;

private:
    void heapify(size_t index);
};

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

template <typename DataType>
template< typename... Args >
void Heap<DataType>::Emplace(Args&&... args)
{
    mContainer.emplace_back(std::forward<Args>(args)...);

    auto index = mContainer.size() - 1;

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
            break;
        }
    }
}

} // namespace heap