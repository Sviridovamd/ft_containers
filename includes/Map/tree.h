#pragma once
#ifndef TREE_H
#define TREE_H

#include <iostream>
#include "tree_iterator.h"
#include "../tree_u.h"

namespace ft {
	template<class Key, class Val, class KeyOfValue, class Compare,
			class Allocator = std::allocator<Val> >
	class RbTree {
		typedef typename Allocator::template rebind<rb_tree_node<Val> >::other
				_node_allocator;
	private:
		rb_tree_node_base header;
		allocator_type m_alloc;
		_node_allocator m_node_alloc;
		key_compare m_comp;
		size_t m_node_count;
	public:
		typedef Key key_type;
		typedef Val value_type;
		typedef value_type *pointer;
		typedef const value_type *const_pointer;
		typedef const rb_tree_node<Val> *_const_link_type;
		typedef Compare key_compare;
		typedef size_t size_type;
		typedef rb_tree_node<Val> *_link_type;
		typedef std::ptrdiff_t difference_type;
		typedef const value_type &const_reference;
		typedef RbTreeConstIterator<value_type> const_iterator;
		typedef ft::ReverseIterator<iterator> reverse_iterator;
		typedef Allocator allocator_type;
		typedef RbTreeIterator<value_type> iterator;
		typedef value_type &reference;
		typedef ft::ReverseIterator<const_iterator> const_reverse_iterator;

		RbTree(const Compare &comp = key_compare(), const Allocator &alloc = allocator_type())
				: m_comp(comp), m_alloc(alloc) {
			m_node_count = 0;
			header.left = &header;
			header.right = &header;
			header.parent = NULL;
			header.color = false;
		}

		RbTree(const RbTree &obj, const Compare &comp = key_compare(), const Allocator &alloc = allocator_type())
				: m_comp(comp), m_alloc(alloc) {
			m_node_count = 0;
			header.left = &header;
			header.right = &header;
			header.parent = NULL;
			header.color = false;
			if (obj.header.parent)
				M_root() = M_copy(obj);
		}

		~RbTree() {
			clear();
		}

	protected:
		typedef rb_tree_node_base *_base_ptr;
		typedef const rb_tree_node_base *_const_base_ptr;

		_base_ptr &M_leftmost() {
			return this->header.left;
		}

		_const_base_ptr M_leftmost() const {
			return this->header.left;
		}

		_base_ptr &M_rightmost() {
			return this->header.right;
		}

		_const_base_ptr M_rightmost() const {
			return this->header.right;
		}

		static const_reference S_value(_const_link_type obj) {
			return *obj->val_ptr();
		}

		static const_reference S_value(_const_base_ptr obj) {
			return *static_cast<_const_link_type>(obj)->val_ptr();
		}

		static const Key &S_key(_const_link_type obj) {
			return KeyOfValue()(S_value(obj));
		}

		static const Key &S_key(_const_base_ptr obj) {
			return KeyOfValue()(S_value(obj));
		}

		static _link_type S_left(_base_ptr obj) {
			return static_cast<_link_type>(obj->left);
		}

		static _const_link_type S_left(_const_base_ptr obj) {
			return static_cast<_const_link_type>(obj->left);
		}

		static _link_type S_right(_base_ptr obj) {
			return static_cast<_link_type>(obj->right);
		}

		static _const_link_type S_right(_const_base_ptr obj) {
			return static_cast<_const_link_type>(obj->right);
		}

		static _base_ptr MAP_S_minimum(_base_ptr obj) {
			return rb_tree_node_base::MAP_S_minimum(obj);
		}

		static _const_base_ptr MAP_S_minimum(_const_base_ptr obj) {
			return rb_tree_node_base::MAP_S_minimum(obj);
		}

		static _base_ptr MAP_S_maximum(_base_ptr obj) {
			return rb_tree_node_base::MAP_S_maximum(obj);
		}

		static _const_base_ptr MAP_S_maximum(_const_base_ptr obj) {
			return rb_tree_node_base::MAP_S_maximum(obj);
		}

		_base_ptr &M_root() {
			return this->header.parent;
		}

		_const_base_ptr M_root() const {
			return this->header.parent;
		}

		_link_type M_begin() {
			return (static_cast<_link_type>(header.parent));
		}

		_const_link_type M_begin() const {
			return (static_cast<_const_link_type>(header.parent));
		}

		_base_ptr M_end() {
			return (&header);
		}

		_const_base_ptr M_end() const {
			return (&header);
		}

		iterator M_lower_bound(_link_type obj, _base_ptr a_obj,
							   const Key &k) {
			while (obj != 0)
				if (!m_comp(S_key(obj), k))
					a_obj = obj, obj = S_left(obj);
				else
					obj = S_right(obj);
			return iterator(a_obj);
		}

		const_iterator M_lower_bound(_const_link_type obj, _const_base_ptr a_obj,
									 const Key &k) const {
			while (obj != 0)
				if (!m_comp(S_key(obj), k))
					a_obj = obj, obj = S_left(obj);
				else
					obj = S_right(obj);
			return const_iterator(a_obj);
		}

		iterator M_upper_bound(_link_type obj, _base_ptr a_obj,
							   const Key &k) {
			while (obj != 0)
				if (m_comp(k, S_key(obj)))
					a_obj = obj, obj = S_left(obj);
				else
					obj = S_right(obj);
			return iterator(a_obj);
		}

		const_iterator M_upper_bound(_const_link_type obj, _const_base_ptr a_obj,
									 const Key &k) const {
			while (obj != 0)
				if (m_comp(k, S_key(obj)))
					a_obj = obj, obj = S_left(obj);
				else
					obj = S_right(obj);
			return const_iterator(a_obj);
		}

		void M_reset() {
			header.parent = 0;
			header.left = &header;
			header.right = &header;
			m_node_count = 0;
		}

		void M_move_data(RbTree &from) {
			header.color = from.header.color;
			header.parent = from.header.parent;
			header.left = from.header.left;
			header.right = from.header.right;
			header.parent->parent = &header;
			m_node_count = from.m_node_count;
			from.M_reset();
		}

		void M_drop_node(_link_type p) {
			_node_alloc.destroy(p);
			_node_alloc.deallocate(p, 1);
		}

		void M_erase_aux(const_iterator position) {
			_link_type a_obj = static_cast<_link_type>(rb_tree_rebalance_for_erase
					(const_cast<_base_ptr>(position.node),
					 this->header));
			M_drop_node(a_obj);
			--m_node_count;
		}

		void M_erase(_link_type obj) {
			while (obj != 0) {
				M_erase(S_right(obj));
				_link_type a_obj = S_left(obj);
				M_drop_node(obj);
				obj = a_obj;
			}
		}

		void M_erase_aux(const_iterator first, const_iterator last) {
			if (first == begin() && last == end())
				clear();
			else
				while (first != last)
					M_erase_aux(first++);
		}

		_link_type M_clone_node(_const_link_type obj) {
			_link_type tmp = _node_alloc.allocate(1);
			_node_alloc.construct(tmp, *obj);
			tmp->color = obj->color;
			tmp->left = 0;
			tmp->right = 0;
			return tmp;
		}

		_link_type M_copy(_const_link_type obj, _base_ptr p) {
			_link_type top = M_clone_node(obj);
			top->parent = p;
			if (obj->right)
				top->right = M_copy(S_right(obj), top);
			p = top;
			obj = S_left(obj);
			while (obj != 0) {
				_link_type a_obj = M_clone_node(obj);
				p->left = a_obj;
				a_obj->parent = p;
				if (obj->right)
					a_obj->right = M_copy(S_right(obj), a_obj);
				p = a_obj;
				obj = S_left(obj);
			}
			return top;
		}

		_link_type M_copy(const RbTree &obj) {
			_link_type root = M_copy(obj.M_begin(), M_end());
			M_leftmost() = MAP_S_minimum(root);
			M_rightmost() = MAP_S_maximum(root);
			m_node_count = obj.m_node_count;
			return root;
		}

		rb_tree_node_base *rb_tree_rebalance_for_erase(rb_tree_node_base *const z,
													   rb_tree_node_base &header) throw() {
			rb_tree_node_base *&root = header.parent;
			rb_tree_node_base *&leftmost = header.left;
			rb_tree_node_base *&rightmost = header.right;
			rb_tree_node_base *a_obj = z;
			rb_tree_node_base *obj = 0;
			rb_tree_node_base *x_parent = 0;
			if (a_obj->left == 0)
				obj = a_obj->right;
			else if (a_obj->right == 0)
				obj = a_obj->left;
			else {
				a_obj = a_obj->right;
				while (a_obj->left != 0)
					a_obj = a_obj->left;
				obj = a_obj->right;
			}
			if (a_obj != z) {
				z->left->parent = a_obj;
				a_obj->left = z->left;
				if (a_obj != z->right) {
					x_parent = a_obj->parent;
					if (obj) obj->parent = a_obj->parent;
					a_obj->parent->left = obj;
					a_obj->right = z->right;
					z->right->parent = a_obj;
				} else
					x_parent = a_obj;
				if (root == z)
					root = a_obj;
				else if (z->parent->left == z)
					z->parent->left = a_obj;
				else
					z->parent->right = a_obj;
				a_obj->parent = z->parent;
				ft::swap(a_obj->color, z->color);
				a_obj = z;
			} else {
				x_parent = a_obj->parent;
				if (obj)
					obj->parent = a_obj->parent;
				if (root == z)
					root = obj;
				else if (z->parent->left == z)
					z->parent->left = obj;
				else
					z->parent->right = obj;
				if (leftmost == z) {
					if (z->right == 0)
						leftmost = z->parent;
					else
						leftmost = rb_tree_node_base::MAP_S_minimum(obj);
				}
				if (rightmost == z) {
					if (z->left == 0)
						rightmost = z->parent;
					else
						rightmost = rb_tree_node_base::MAP_S_maximum(obj);
				}
			}
			if (a_obj->color != false) {
				while (obj != root && (obj == 0 || obj->color == true))
					if (obj == x_parent->left) {
						rb_tree_node_base *w = x_parent->right;
						if (w->color == false) {
							w->color = true;
							x_parent->color = false;
							rotate_left(x_parent, root);
							w = x_parent->right;
						}
						if ((w->left == 0 ||
							 w->left->color == true) &&
							(w->right == 0 ||
							 w->right->color == true)) {
							w->color = false;
							obj = x_parent;
							x_parent = x_parent->parent;
						} else {
							if (w->right == 0
								|| w->right->color == true) {
								w->left->color = true;
								w->color = false;
								rotate_right(w, root);
								w = x_parent->right;
							}
							w->color = x_parent->color;
							x_parent->color = true;
							if (w->right)
								w->right->color = true;
							rotate_left(x_parent, root);
							break;
						}
					} else {
						rb_tree_node_base *w = x_parent->left;
						if (w->color == false) {
							w->color = true;
							x_parent->color = false;
							rotate_right(x_parent, root);
							w = x_parent->left;
						}
						if ((w->right == 0 ||
							 w->right->color == true) &&
							(w->left == 0 ||
							 w->left->color == true)) {
							w->color = false;
							obj = x_parent;
							x_parent = x_parent->parent;
						} else {
							if (w->left == 0 || w->left->color == true) {
								w->right->color = true;
								w->color = false;
								rotate_left(w, root);
								w = x_parent->left;
							}
							w->color = x_parent->color;
							x_parent->color = true;
							if (w->left)
								w->left->color = true;
							rotate_right(x_parent, root);
							break;
						}
					}
				if (obj) obj->color = true;
			}
			return a_obj;
		}

		ft::pair<_base_ptr, _base_ptr> M_get_insert_hint_unique_pos(const_iterator position,
																	const key_type &k) {
			iterator pos = position.M_const_cast();
			typedef pair<_base_ptr, _base_ptr> res;
			if (pos.node == M_end()) {
				if (size() > 0
					&& m_comp(S_key(M_rightmost()), k))
					return res(0, M_rightmost());
				else
					return M_get_insert_unique_pos(k);
			} else if (m_comp(k, S_key(pos.node))) {
				iterator before = pos;
				if (pos.node == M_leftmost())
					return res(M_leftmost(), M_leftmost());
				else if (m_comp(S_key((--before).node), k)) {
					if (S_right(before.node) == 0)
						return res(0, before.node);
					else
						return res(pos.node, pos.node);
				} else
					return M_get_insert_unique_pos(k);
			} else if (m_comp(S_key(pos.node), k)) {
				iterator after = pos;
				if (pos.node == M_rightmost())
					return res(0, M_rightmost());
				else if (m_comp(k, S_key((++after).node))) {
					if (S_right(pos.node) == 0)
						return res(0, pos.node);
					else
						return res(after.node, after.node);
				} else
					return M_get_insert_unique_pos(k);
			} else
				return res(pos.node, 0);
		}

		ft::pair<_base_ptr, _base_ptr> M_get_insert_unique_pos(const key_type &k) {
			typedef pair<_base_ptr, _base_ptr> _Res;
			_link_type obj = M_begin();
			_base_ptr a_obj = M_end();
			bool comp = true;
			while (obj != 0) {
				a_obj = obj;
				comp = m_comp(k, S_key(obj));
				obj = comp ? S_left(obj) : S_right(obj);
			}
			iterator j = iterator(a_obj);
			if (comp) {
				if (j == begin())
					return _Res(obj, a_obj);
				else
					--j;
			}
			if (m_comp(S_key(j.node), k))
				return _Res(obj, a_obj);
			return _Res(j.node, 0);
		}

	public:
		bool empty() const {
			return m_node_count == 0;
		}

		size_type size() const {
			return m_node_count;
		}

		size_type max_size() const {
			return _node_alloc.max_size();
		}

		iterator lower_bound(const key_type &k) {
			return M_lower_bound(M_begin(), M_end(), k);
		}

		const_iterator lower_bound(const key_type &k) const {
			return M_lower_bound(M_begin(), M_end(), k);
		}

		iterator upper_bound(const key_type &k) {
			return M_upper_bound(M_begin(), M_end(), k);
		}

		const_iterator upper_bound(const key_type &k) const {
			return M_upper_bound(M_begin(), M_end(), k);
		}

		key_compare key_comp() const {
			return m_comp;
		}

		const_iterator begin() const {
			return (const_iterator(header.left));
		}

		const_iterator end() const {
			return (const_iterator(&header));
		}

		iterator begin() {
			return (iterator(header.left));
		}

		iterator end() {
			return (iterator(&header));
		}

		reverse_iterator rbegin() {
			return (reverse_iterator(end()));
		}

		reverse_iterator rend() {
			return (reverse_iterator(begin()));
		}

		allocator_type get_allocator() {
			return m_alloc;
		}

		allocator_type get_allocator() const {
			return m_alloc;
		}

		RbTree &operator=(const RbTree &obj) {
			clear();
			insert_unique(obj.begin(), obj.end());
		}

		void clear() {
			M_erase(M_begin());
			M_reset();
		}

		ft::pair<iterator, bool> insert_unique(const Val &v) {
			typedef pair<iterator, bool> res;
			ft::pair<_base_ptr, _base_ptr> _res = M_get_insert_unique_pos(KeyOfValue()(v));
			if (_res.second)
				return res(insert(_res.first, _res.second, v), true);
			return res(iterator(_res.first), false);
		}

		iterator insert_unique(const_iterator position, const Val &v) {
			pair<_base_ptr, _base_ptr> res = M_get_insert_hint_unique_pos(position, KeyOfValue()(v));
			if (res.second)
				return insert(res.first, res.second, v);
			return iterator(res.first);
		}

		template<class II>
		void insert_unique(II first, II last) {
			for (; first != last; ++first)
				insert_unique(end(), *first);
		}

		iterator insert(_base_ptr obj, _base_ptr p, const Val &v) {
			bool insert_left = (obj != 0 || p == M_end()
								|| m_comp(KeyOfValue()(v), S_key(p)));
			_link_type z = _node_alloc.allocate(1);
			_node_alloc.construct(z, v);
			rb_tree_insert_and_rebalance(insert_left, z, p, header);
			++m_node_count;
			return iterator(z);
		}

		void rb_tree_insert_and_rebalance(const bool insert_left,
										  rb_tree_node_base *obj,
										  rb_tree_node_base *p,
										  rb_tree_node_base &header) throw() {
			rb_tree_node_base *&_root = header.parent;
			obj->parent = p;
			obj->left = 0;
			obj->right = 0;
			obj->color = false;
			if (insert_left) {
				p->left = obj;
				if (p == &header) {
					header.parent = obj;
					header.right = obj;
				} else if (p == header.left)
					header.left = obj;
			} else {
				p->right = obj;
				if (p == header.right)
					header.right = obj;
			}
			while (obj != _root
				   && obj->parent->color == false) {
				rb_tree_node_base *const xpp = obj->parent->parent;
				if (obj->parent == xpp->left) {
					rb_tree_node_base *const a_obj = xpp->right;
					if (a_obj && a_obj->color == false) {
						obj->parent->color = true;
						a_obj->color = true;
						xpp->color = false;
						obj = xpp;
					} else {
						if (obj == obj->parent->right) {
							obj = obj->parent;
							rotate_left(obj, _root);
						}
						obj->parent->color = true;
						xpp->color = false;
						rotate_right(xpp, _root);
					}
				} else {
					rb_tree_node_base *const a_obj = xpp->left;
					if (a_obj && a_obj->color == false) {
						obj->parent->color = true;
						a_obj->color = true;
						xpp->color = false;
						obj = xpp;
					} else {
						if (obj == obj->parent->left) {
							obj = obj->parent;
							rotate_right(obj, _root);
						}
						obj->parent->color = true;
						xpp->color = false;
						rotate_left(xpp, _root);
					}
				}
			}
			_root->color = true;
		}

		void rotate_left(rb_tree_node_base *const obj, rb_tree_node_base *&root) {
			rb_tree_node_base *const a_obj = obj->right;
			obj->right = a_obj->left;
			if (a_obj->left != 0)
				a_obj->left->parent = obj;
			a_obj->parent = obj->parent;
			if (obj == root)
				root = a_obj;
			else if (obj == obj->parent->left)
				obj->parent->left = a_obj;
			else
				obj->parent->right = a_obj;
			a_obj->left = obj;
			obj->parent = a_obj;
		}

		void rotate_right(rb_tree_node_base *const obj,
						  rb_tree_node_base *&root) {
			rb_tree_node_base *const a_obj = obj->left;
			obj->left = a_obj->right;
			if (a_obj->right != 0)
				a_obj->right->parent = obj;
			a_obj->parent = obj->parent;
			if (obj == root)
				root = a_obj;
			else if (obj == obj->parent->right)
				obj->parent->right = a_obj;
			else
				obj->parent->left = a_obj;
			a_obj->right = obj;
			obj->parent = a_obj;
		}

		ft::pair<iterator, iterator> equal_range(const Key &k) {
			_link_type obj = M_begin();
			_base_ptr a_obj = M_end();
			while (obj != 0) {
				if (m_comp(S_key(obj), k))
					obj = S_right(obj);
				else if (m_comp(k, S_key(obj)))
					a_obj = obj, obj = S_left(obj);
				else {
					_link_type xu(obj);
					_base_ptr yu(a_obj);
					a_obj = obj, obj = S_left(obj);
					xu = S_right(xu);
					return ft::pair<iterator,
							iterator>(M_lower_bound(obj, a_obj, k),
									  M_upper_bound(xu, yu, k));
				}
			}
			return ft::pair<iterator, iterator>(iterator(a_obj),
												iterator(a_obj));
		}

		pair<const_iterator, const_iterator> equal_range(const Key &k) const {
			_const_link_type obj = M_begin();
			_const_base_ptr a_obj = M_end();
			while (obj != 0) {
				if (m_comp(S_key(obj), k))
					obj = S_right(obj);
				else if (m_comp(k, S_key(obj)))
					a_obj = obj, obj = S_left(obj);
				else {
					_const_link_type xu(obj);
					_const_base_ptr yu(a_obj);
					a_obj = obj, obj = S_left(obj);
					xu = S_right(xu);
					return ft::pair<const_iterator,
							const_iterator>(M_lower_bound(obj, a_obj, k),
											M_upper_bound(xu, yu, k));
				}
			}
			return ft::pair<const_iterator, const_iterator>(const_iterator(a_obj),
															const_iterator(a_obj));
		}

		void swap(RbTree &t) {
			if (M_root() == 0) {
				if (t.M_root() != 0)
					this->M_move_data(t);
			} else if (t.M_root() == 0)
				t.M_move_data(*this);
			else {
				ft::swap(M_root(), t.M_root());
				ft::swap(M_leftmost(), t.M_leftmost());
				ft::swap(M_rightmost(), t.M_rightmost());
				M_root()->parent = M_end();
				t.M_root()->parent = t.M_end();
				ft::swap(this->m_node_count, t.m_node_count);
			}
			ft::swap(this->m_comp, t.m_comp);
		}

		size_type erase(const Key &obj) {
			ft::pair<iterator, iterator> p = equal_range(obj);
			const size_type old_size = size();
			M_erase_aux(p.first, p.second);
			return old_size - size();
		}

		void erase(iterator first, iterator last) {
			M_erase_aux(first, last);
		}

		void erase(iterator position) {
			M_erase_aux(position);
		}

		void erase(const Key *first, const Key *last) {
			while (first != last)
				erase(*first++);
		}

		iterator find(const Key &k) {
			iterator j = M_lower_bound(M_begin(), M_end(), k);
			return (j == end()
					|| m_comp(k, S_key(j.node))) ? end() : j;
		}

		const_iterator find(const Key &k) const {
			const_iterator j = M_lower_bound(M_begin(), M_end(), k);
			return (j == end()
					|| m_comp(k, S_key(j.node))) ? end() : j;
		}

		size_type count(const Key &k) const {
			ft::pair<const_iterator, const_iterator> p = equal_range(k);
			const size_type n = ft::distance(p.first, p.second);
			return n;
		}

		bool operator==(const RbTree &a_obj) const {
			return size() == a_obj.size()
				   && ft::equal(begin(), end(), a_obj.begin());
		}

		bool operator<(const RbTree &a_obj) const {
			return ft::lexicographical_compare(begin(), end(),
											   a_obj.begin(), a_obj.end());
		}

		bool operator!=(const RbTree &a_obj) const {
			return !(*this == a_obj);
		}

		bool operator>(const RbTree &a_obj) const {
			return a_obj < *this;
		}

		bool operator<=(const RbTree &a_obj) const {
			return !(a_obj < *this);
		}

		bool operator>=(const RbTree &a_obj) const {
			return !(*this < a_obj);
		}
	};
};

#endif //TREE_H