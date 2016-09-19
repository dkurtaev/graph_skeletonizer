#include "include/sets_separator.hpp"

#include <vector>

SetsSeparator::SetsSeparator(unsigned n_sets)
  : parents(n_sets), ranks(n_sets, 0) {
  for (unsigned i = 0; i < n_sets; ++i) {
    parents[i] = i;
  }
}

unsigned SetsSeparator::GetSetDestination(unsigned set_id) {
  unsigned parent_id = parents[set_id];
  while (parent_id != parents[parent_id]) {
    parent_id = parents[parent_id];
  }

  // Paths compression.
  unsigned id = parents[set_id];
  parents[set_id] = parent_id;
  while (id != parent_id) {
    unsigned next_id = parents[id];
    parents[id] = parent_id;
    id = next_id;
  }

  return parent_id;
}

bool SetsSeparator::Merge(unsigned first_set_id, unsigned second_set_id) {
  unsigned first_parent_id = GetSetDestination(first_set_id);
  unsigned second_parent_id = GetSetDestination(second_set_id);

  if (first_parent_id == second_parent_id) return false;

  unsigned first_rank = ranks[first_parent_id];
  unsigned second_rank = ranks[second_parent_id];

  if (first_rank < second_rank) {
    parents[first_parent_id] = second_parent_id;
  } else if (first_rank > second_rank) {
    parents[second_parent_id] = first_parent_id;
  } else {
    parents[first_parent_id] = second_parent_id;
    ++ranks[second_parent_id];
  }
  return true;
}
