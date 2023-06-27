#ifndef LISTNODE_HPP
#define LISTNODE_HPP

template <class T>
class ListNode {
public:
	ListNode<T>* next;
	T* data;
};

#endif // !LISTNODE_HPP