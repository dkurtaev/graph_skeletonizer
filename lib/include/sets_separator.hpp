#ifndef INCLUDE_SETS_SEPARATOR_HPP_
#define INCLUDE_SETS_SEPARATOR_HPP_

#include <vector>

class SetsSeparator {
 public:
  explicit SetsSeparator(unsigned n_sets);

  // If set is merged with others, return id of parent set.
  unsigned GetSetDestination(unsigned set_id);

  // Merge two sets.
  void Merge(unsigned first_set_id, unsigned second_set_id);

 private:
  std::vector<unsigned> parents;
  std::vector<unsigned> ranks;
};

#endif  // INCLUDE_SETS_SEPARATOR_HPP_
