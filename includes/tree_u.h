#pragma once
#ifndef CONTEINERS2_MY_TREE_U_H
#define CONTEINERS2_MY_TREE_U_H

#include <sstream>
#include <string>
#include "pair.h"
#include "rev_iter.h"

namespace ft {

	struct rb_tree_node_base {
		typedef rb_tree_node_base *_base_ptr;
		typedef const rb_tree_node_base *_const_base_ptr;
		bool color;
		_base_ptr parent;
		_base_ptr left;
		_base_ptr right;

		static _base_ptr MAP_S_minimum(_base_ptr obj) {
			while (obj->left != 0) obj = obj->left;
			return obj;
		}

		static _const_base_ptr MAP_S_minimum(_const_base_ptr obj) {
			while (obj->left != 0) obj = obj->left;
			return obj;
		}

		static _base_ptr MAP_S_maximum(_base_ptr obj) {
			while (obj->right != 0) obj = obj->right;
			return obj;
		}

		static _const_base_ptr MAP_S_maximum(_const_base_ptr obj) {
			while (obj->right != 0) obj = obj->right;
			return obj;
		}
	};

	static rb_tree_node_base *local_Rb_tree_decrement(rb_tree_node_base *obj) throw() {
		if (obj->color == false
			&& obj->parent->parent == obj)
			obj = obj->right;
		else if (obj->left != 0) {
			rb_tree_node_base *a_obj = obj->left;
			while (a_obj->right != 0)
				a_obj = a_obj->right;
			obj = a_obj;
		} else {
			rb_tree_node_base *a_obj = obj->parent;
			while (obj == a_obj->left) {
				obj = a_obj;
				a_obj = a_obj->parent;
			}
			obj = a_obj;
		}
		return obj;
	}

	rb_tree_node_base *rb_tree_decrement(rb_tree_node_base *obj) throw() {
		return local_Rb_tree_decrement(obj);
	}

	const rb_tree_node_base *rb_tree_decrement(const rb_tree_node_base *obj) throw() {
		return local_Rb_tree_decrement(const_cast<rb_tree_node_base *>(obj));
	}

	static rb_tree_node_base *local_Rb_tree_increment(rb_tree_node_base *obj) throw() {
		if (obj->right != 0) {
			obj = obj->right;
			while (obj->left != 0)
				obj = obj->left;
		} else {
			rb_tree_node_base *a_obj = obj->parent;
			while (obj == a_obj->right) {
				obj = a_obj;
				a_obj = a_obj->parent;
			}
			if (obj->right != a_obj)
				obj = a_obj;
		}
		return obj;
	}

	rb_tree_node_base *rb_tree_increment(rb_tree_node_base *obj) throw() {
		return local_Rb_tree_increment(obj);
	}

	const rb_tree_node_base *rb_tree_increment(const rb_tree_node_base *obj) throw() {
		return local_Rb_tree_increment(const_cast<rb_tree_node_base *>(obj));
	}

	template<typename Val>
	struct rb_tree_node : public rb_tree_node_base {
		typedef rb_tree_node<Val> *_link_type;
		Val value_field;

		rb_tree_node(const Val &v) : rb_tree_node_base(), value_field(v) {}

		Val *val_ptr() { return &value_field; }

		const Val *val_ptr() const { return &value_field; }
	};
};

#endif //CONTEINERS2_MY_TREE_U_H