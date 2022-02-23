#ifndef CELLULAR_AUTOMATA_NODE_H
#define CELLULAR_AUTOMATA_NODE_H

namespace CA
{
  struct Node
  {
    Node() : val(0), dirty(false) {}
    Node(uint8_t v, bool d) : val(v), dirty(d) {}
    Node(const Node &other)
    {
      val = other.val;
      dirty = other.dirty;
    }

    uint8_t val;
    bool dirty; // Does this cell need to be updated
  };

} /* namespace CA */
#endif /* CELLULAR_AUTOMATA_NODE_H */