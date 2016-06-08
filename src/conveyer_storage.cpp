/**
 * @file    conveyer_storage.cpp
 * @author  Matthew Robinson
 */

#include "conveyer_storage.h"

template <class T, class Container>
ConveyerStorage<T, Container>::ConveyerStorage(size_type num_items)
  : belt_(num_items) {
  
}  // end constructor

template <class T, class Container>
void ConveyerStorage<T, Container>::push(T item) {
  belt_.pop_front();
  belt_.push_back(item);
}  // end Push

template <class T, class Container>
void ConveyerStorage<T, Container>::clear() {
  // TODO : increase efficiency by going through container to construct new elements.
  size_type size = belt_.size();
  belt_.clear();
  belt_.resize(size);
}  // end clear
