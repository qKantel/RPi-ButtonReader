/**
 * @file    conveyer_storage.h
 * @author  Matthew Robinson
 */

#ifndef EG_VIDEOPLAYER_CONVEYER_STORAGE_H_
#define EG_VIDEOPLAYER_CONVEYER_STORAGE_H_

#include <deque>

/**
 * ConveyerStorage is a limited container. It can only store the amount
 * specified, but for good reason. Like a conveyer belt, if the client wishes
 * to add an item to the end, the item on the front will fall off.
 * A deque fulfills all requirements by ConveyerStorage.
 */
template <class T, class Container = std::deque<T>>
class ConveyerStorage {
public:
  typedef T                      value_type;
  typedef Container              container_type;
  typedef typename Container::size_type   size_type;

  typedef typename Container::const_iterator const_iterator;

  /**
   * @info    Constructor, the definition of ConveyerStorage must have a
   *          specified size.
   * @param   num_items   Number of items allowed in the conveyer.
   */
  explicit ConveyerStorage(size_type num_items);

  // Iterators for the client to peak into the container.
  const_iterator begin() const { return belt_.begin(); }
  const_iterator end()   const { return belt_.end(); }

  size_type size() const { return belt_.size(); }

  /**
   * @info    Changes the size of the belt. Refer to the underlying container's
   *          resize function for specifics.
   */
  void resize(size_type num_items) { belt_.resize(num_items); }

  /**
  * @info    Pushes an item to the end of the conveyer, and pushes the first
  *          item off. Logistically, pops first, then pushes.
  *          NOTE: If you need static memory allocation, rework the
  *          implementation.
  * @param   item    item to be added onto the conveyer
  */
  void push(T item);

  /**
  * @info   Removes all elements in the container but retains container size
  *         in order to not disrupt push functionality.
  */
  void clear();

private:
  Container belt_;
};

#endif  // !EG_VIDEOPLAYER_CONVEYER_STORAGE_H_