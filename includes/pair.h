#pragma once
#ifndef CONTEINERS2_MY_PAIR_H
#define CONTEINERS2_MY_PAIR_H

#include "tree_u.h"
#include "rev_iter.h"
#include <sstream>
#include <string>

namespace ft {

	template<class arg, class result>
	struct unary_function {
		typedef arg argument_type;
		typedef result result_type;
	};

	template<class Pair>
	struct Select1st : public unary_function<Pair,
			typename Pair::first_type> {
		typename Pair::first_type &operator()(Pair &obj) const {
			return obj.first;
		}

		const typename Pair::first_type &operator()(const Pair &obj) const {
			return obj.first;
		}
	};

	template<class Pair>
	struct Select2nd : public unary_function<Pair,
			typename Pair::second_type> {
		typename Pair::second_type &operator()(Pair &obj) const {
			return obj.second;
		}

		const typename Pair::second_type &operator()(const Pair &obj) const {
			return obj.second;
		}
	};


	template<class T1, class T2>
	struct pair {
		typedef T1 first_type;
		typedef T2 second_type;
		first_type first;
		second_type second;

		pair() : first(), second() {

		}

		pair(const T1 &a, const T2 &b) : first(a), second(b) {}

		template<class U1, class U2>
		pair(const pair<U1, U2> &p): first(p.first), second(p.second) {}

		pair &operator=(const pair &p) {
			this->first = p.first;
			this->second = p.second;
			return *this;
		}

		template<class U1, class U2>
		pair &operator=(const pair<U1, U2> &p) {
			first = p.first;
			second = p.second;
			return *this;
		}

		bool operator==(const pair<T1, T2> &a_obj) const {
			return this->first == a_obj.first && this->second == a_obj.second;
		}

		bool operator<(const pair<T1, T2> &a_obj) const {
			return this->first < a_obj.first
				   || ((a_obj.first > this->first) && this->second < a_obj.second);
		}

		bool operator!=(const pair<T1, T2> &a_obj) const {
			return (this != a_obj);
		}

		bool operator>(const pair<T1, T2> &a_obj) const {
			return a_obj < this;
		}

		bool operator<=(const pair<T1, T2> &a_obj) const {
			return (a_obj > this);
		}

		bool operator>=(const pair<T1, T2> &a_obj) const {
			return (this > a_obj);
		}
	};

	template<class T1, class T2>
	ft::pair<T1, T2> make_pair(T1 obj, T2 a_obj) {
		return pair<T1, T2>(obj, a_obj);
	}

	template<class T>
	void swap(T &a, T &b) {
		T c(a);
		a = b;
		b = c;
	}
}

#endif //CONTEINERS2_MY_PAIR_H
