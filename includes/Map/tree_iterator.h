#pragma once
#ifndef TREE_ITERATOR_H
#define REE_ITERATOR_H

#include "../tree_u.h"

template<class ValueType>
class RbTreeIterator :
		public ft::iterator<ft::bidirectional_iterator_tag, ValueType> {
public:
	typedef ValueType value_type;
	typedef typename ft::iterator<iterator_category, value_type>::pointer pointer;
	typedef ft::bidirectional_iterator_tag iterator_category;
	typedef typename ft::iterator<iterator_category, value_type>::difference_type difference_type;
	typedef typename ft::iterator<iterator_category, value_type>::reference reference;
	typedef RbTreeIterator<value_type> _self;
	typedef typename ft::rb_tree_node<value_type>::_base_ptr _base_ptr;
	typedef typename ft::rb_tree_node<value_type> *_link_type;

	_base_ptr node;

	RbTreeIterator() : node() {

	}

	RbTreeIterator(const RbTreeIterator &src) : node(src.base()) {

	}

	RbTreeIterator(_base_ptr obj) : node(obj) {

	}

	template<typename _Iter>
	RbTreeIterator(const RbTreeIterator<_Iter> &src) : node(src.base()) {

	}

	~RbTreeIterator() {

	};

	const _base_ptr base() const {
		return (node);
	}

	reference operator*() const {
		return *static_cast<_link_type>(node)->val_ptr();
	}

	pointer operator->() const {
		return static_cast<_link_type> (node)->val_ptr();
	}

	bool operator==(const _self &obj) const {
		node == obj.node;
	}

	bool operator!=(const _self &obj) const {
		return node != obj.node;
	}

	_self &operator++() {
		node = rb_tree_increment(node);
		return *this;
	}

	_self &operator--() {
		node = rb_tree_decrement(node);
		return *this;
	}

	_self operator++(int) {
		_self _tmp = *this;
		node = rb_tree_increment(node);
		return _tmp;
	}

	_self operator--(int) {
		_self _tmp = *this;
		node = rb_tree_decrement(node);
		return _tmp;
	}
};

template<typename ValueType>
class RbTreeConstIterator : public ft::iterator<ft::bidirectional_iterator_tag, ValueType> {
public:
	typedef ValueType value_type;
	typedef RbTreeIterator<ValueType> iterator;
	typedef const ValueType &reference;
	typedef const ValueType *pointer;
	typedef ft::bidirectional_iterator_tag iterator_category;
	typedef RbTreeConstIterator<ValueType> _self;
	typedef ft::rb_tree_node_base::_const_base_ptr _base_ptr;
	typedef const ft::rb_tree_node<ValueType> *_link_type;
	typedef typename ft::iterator<iterator_category, value_type>::difference_type difference_type;

	_base_ptr node;

	RbTreeConstIterator() : node() {

	}

	RbTreeConstIterator(_base_ptr obj) : node(obj) {

	}

	RbTreeConstIterator(const iterator &it) : node(it.node) {

	}

	bool operator==(const _self &obj) const {
		return node == obj.node;
	}

	bool operator!=(const _self &obj) const {
		return node != obj.node;
	}

	iterator M_const_cast() const {
		return iterator(const_cast<typename iterator::_base_ptr>(node));
	}

	reference operator*() const {
		return *static_cast<_link_type>(node)->val_ptr();
	}

	pointer operator->() const {
		return static_cast<_link_type>(node)->val_ptr();
	}

	_self &operator++() {
		node = rb_tree_increment(node);
		return *this;
	}

	_self &operator--() {
		node = rb_tree_decrement(node);
		return *this;
	}

	_self operator++(int) {
		_self _tmp = *this;
		node = rb_tree_increment(node);
		return _tmp;
	}

	_self operator--(int) {
		_self _tmp = *this;
		node = rb_tree_decrement(node);
		return _tmp;
	}
};

template<class ValueType>
RbTreeIterator<ValueType> operator+(int a, RbTreeIterator<ValueType> b) {
	return (b.base() + a);
}

template<class ValueType>
RbTreeConstIterator<ValueType> operator+(int a, RbTreeConstIterator<ValueType> b) {
	return (b.base() + a);
}

template<typename Val>
bool operator==(const RbTreeIterator<Val> &obj, const RbTreeConstIterator<Val> &a_obj) {
	return obj.node == a_obj.node;
}

template<typename Val>
bool operator!=(const RbTreeIterator<Val> &obj, const RbTreeConstIterator<Val> &a_obj) {
	return obj.node != a_obj.node;
}

#endif //TREE_ITERATOR_H