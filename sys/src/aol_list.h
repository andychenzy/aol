
#ifndef AOL_LINK_LIST_H_
#define AOL_LINK_LIST_H_

namespace aolsys {

  template <typename NodeT>
  class LinkList
  {
    public:
      typedef NodeT* node_pointer_type;
      typedef LinkList<NodeT> self_type;

    public:
      LinkList();
      ~LinkList();

      void append(NodeT* node);
      void remove(NodeT* node);
      void combine(const LinkList<NodeT>& al);
      void reset();

      NodeT* head() const
      {
        return _head;
      }

      NodeT* tail() const
      {
        return _tail;
      }

      void head(NodeT* h)
      {
        _head = h;
      }

      void tail(NodeT* t)
      {
        _tail = t;
      }

      bool empty() const
      {
        return !(_head && _tail);
      }

    private:
      NodeT* _head;
      NodeT* _tail;
  };

  template <typename NodeT>
  LinkList<NodeT>::LinkList()
  {
    reset();
  }

  template <typename NodeT>
  void LinkList<NodeT>::reset()
  {
    _head = _tail = NULL;
  }

  template <typename NodeT>
  LinkList<NodeT>::~LinkList()
  {
  }

  template <typename NodeT>
  void LinkList<NodeT>::append(NodeT* node)
  {
    if (!node)
      return;

    node->_prev = _tail;
    npde->_next = NULL;

    if (!tail) {
      _head = node;
    } else {
      _tail->_next = node;
    }
    _tail = node;
  }

  template <typename NodeT>
  void LinkList<NodeT>::remove(NodeT* node)
  {
    if (node == NULL)
      return;

    if (node == _head) {
      _head = node->_next;
    }

    if (node == _tail) {
      _tail = node->_prev;
    }

    if (node->_prev != NULL)
      node->_prev->_next = node->_next;
    if (node->_next != NULL)
      node->_next->_prev = node->_prev;
  }

  template <typename NodeT>
  void LinkList<NodeT>::combine(const LinkList<NodeT>& al)
  {
    if (al.empty())
      return;

    if (!tail) {
      _head = al.head();
    } else {
      _tail->_next = al.head();
      al.head()->_prev = _tail;
    }

    _tail = al.tail();
  }

} // end of namespace aolsys

