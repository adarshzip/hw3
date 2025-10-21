#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below
  int m_; 
  PComparator comp_;
  std::vector<T> data_; 
};

// Add implementation of member functions here
template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c = PComparator()) {
  m_ = m; 
  comp_ = c; 
}

template <typename T, typename PComparator>
Heap<T, PComparator>::~Heap() {
}

template <typename T, typename PComparator>
void Heap<T, PComparator>::push(const T& item) {
  size_t item_pos = this->data_.size(); 
  data_.push_back(item); 

  while (item_pos > 0 && comp_(data_[item_pos], data_[(item_pos - 1)/m_])){
    std::swap(data_[item_pos], data_[(item_pos - 1)/m_]);
    item_pos = (item_pos - 1)/m_; 
  }
}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap is empty"); 

  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return this->data_.front(); 
}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap is empty"); 
  }

  if(this->data_.size() == 1){
    data_.pop_back(); 
    return; 
  }

  std::swap(data_[0], data_[data_.size() - 1]);
  data_.pop_back();

  size_t item_pos = 0; 
  size_t bestChild = 1; 

  while(true){
    if (item_pos * m_ + 1 >= data_.size()){ // no children
      break; 
    }

    bestChild = item_pos * m_ + 1; 

    for (int i = 2; i <= m_; i++){
      if (item_pos * m_ + i >= data_.size()){
        break; 
      }

      if (comp_(data_[item_pos * m_ + i], data_[bestChild])) {
        bestChild = item_pos * m_ + i;
      }
    }

    if (comp_(data_[bestChild], data_[item_pos])){
      std::swap(this->data_[bestChild], data_[item_pos]);
      item_pos = bestChild; 
    }
    else {
      break; 
    }
  }
}

template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const {
  return (this->data_.size() == 0);
}

template <typename T, typename PComparator>
size_t Heap<T,PComparator>::size() const {
  return (this->data_.size());
}


#endif

