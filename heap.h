#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>

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
  
  void swap(size_t pos); 
};

// Add implementation of member functions here
template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m=2, PComparator c = PComparator()) {
  m_ = m; 
  comp_ = c; 
}

template <typename T, typename PComparator>
Heap<T, PComparator>::~Heap() {
}

template <typename T, typename PComparator>
void Heap<T, PComparator>::push(const T& item) {
  size_t item_pos = data_.size(); 
  data_.push_back(item); 

  while (item_pos > 0 && comp_(data_[item_pos], data_[(item_pos - 1)/m])){
    std::swap(data_[item_pos], data_[(item_pos - 1)/m]);
    item_pos = (item_pos - 1)/m; 
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
  return data_.front(); 
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

  if(data_.size() == 1){
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

    size_t max_bound = data_.size() - (item_pos * m_ + m_); 
    if (max_bound > m_){ // checks how many children. 
      max_bound = m_; 
    }

    for(int i = 1; i < max_bound; i++){
      if(! comp_(data_[item_pos*m_ + bestChild], data_[item_pos*m_ + i])){
        bestChild = i; 
      }
    }

    if(item_pos < data_.size() && comp_(data_[item_pos * m_ + bestChild], data_[item_pos])){
      std::swap(data_[item_pos], data_[item_pos * m_ + bestChild]); 
      item_pos = item_pos * m_ + bestChild; 
    }
    else {
      break; 
    }
  }

}



#endif

