
#ifndef CONTEINERS2_MY_REV_ITER_H
#define CONTEINERS2_MY_REV_ITER_H

#include "pair.h"
#include "tree_u.h"

namespace ft {


	template<typename First, typename Second, typename Result>
	struct binary_function {
		typedef First first_argument_type;
		typedef Second second_argument_type;
		typedef Result result_type;
	};


	struct input_iterator_tag {
	};
	struct output_iterator_tag {
	};
	struct forward_iterator_tag : public input_iterator_tag {
	};
	struct bidirectional_iterator_tag : public forward_iterator_tag {
	};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {
	};

	template<class Iterator>
	struct iterator_traits {
		typedef typename Iterator::iterator_category iterator_category;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::difference_type difference_type;
		typedef difference_type distance_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
	};

	template<typename Tp>
	struct iterator_traits<Tp *> {
		typedef ft::random_access_iterator_tag iterator_category;
		typedef Tp value_type;
		typedef std::ptrdiff_t difference_type;
		typedef Tp *pointer;
		typedef Tp &reference;
	};

	template<typename Tp>
	struct iterator_traits<const Tp *> {
		typedef ft::random_access_iterator_tag iterator_category;
		typedef Tp value_type;
		typedef std::ptrdiff_t difference_type;
		typedef const Tp *pointer;
		typedef const Tp &reference;
	};

	template<class Category, class T, class Distance = std::ptrdiff_t,
			class Pointer = T *, class Reference = T &>
	struct iterator {
		typedef T value_type;
		typedef Distance difference_type;
		typedef Pointer pointer;
		typedef Reference reference;
		typedef Category iterator_category;
	};

	template<class It>
	typename ft::iterator_traits<It>::difference_type
	do_distance(It first, It last, ft::input_iterator_tag) {
		typename ft::iterator_traits<It>::difference_type result = 0;
		while (first != last) {
			++first;
			++result;
		}
		return result;
	}

	template<class It>
	typename ft::iterator_traits<It>::difference_type
	do_distance(It first, It last, ft::random_access_iterator_tag) {
		return last - first;
	}

	template<class It>
	typename ft::iterator_traits<It>::difference_type
	distance(It first, It last) {
		return ft::do_distance(first, last,
							   typename ft::iterator_traits<It>::iterator_category());
	}

	template<bool, typename Tp = void>
	struct enable_if {
	};
	template<typename Tp>
	struct enable_if<true, Tp> {
		typedef Tp type;
	};

	template<typename Tp, Tp v>
	struct integral_constant {
		static const Tp value = v;
		typedef Tp value_type;
		typedef integral_constant<Tp, v> type;

		operator value_type() { return value; }
	};

	typedef ft::integral_constant<bool, true> true_type;
	typedef ft::integral_constant<bool, false> false_type;

	template<typename, typename>
	struct are_same {
		enum {
			value = 0
		};
		typedef false_type type;
	};

	template<bool>
	struct truth_type {
		typedef false_type type;
	};

	template<>
	struct truth_type<true> {
		typedef true_type type;
	};

	template<typename>
	struct is_integral_helper : public false_type {
	};

	template<typename Tp>
	struct is_integer {
		enum {
			value = 0
		};
		typedef false_type type;
	};

	template<>
	struct is_integer<bool> {
		enum {
			value = 1
		};
		typedef true_type type;
	};
	template<>
	struct is_integer<char> {
		enum {
			value = 1
		};
		typedef true_type type;
	};
	template<>
	struct is_integral_helper<wchar_t> {
		const static bool value = true;
	};
	template<>
	struct is_integer<signed char> {
		enum {
			value = 1
		};
		typedef true_type type;
	};
	template<>
	struct is_integer<unsigned char> {
		enum {
			value = 1
		};
		typedef true_type type;
	};
	template<>
	struct is_integer<short> {
		enum {
			value = 1
		};
		typedef true_type type;
	};

	template<typename Rev_Iterator>
	class ReverseIterator
			: public iterator<typename iterator_traits<Rev_Iterator>::iterator_category,
					typename iterator_traits<Rev_Iterator>::difference_type,
					typename iterator_traits<Rev_Iterator>::pointer,
					typename iterator_traits<Rev_Iterator>::value_type,
					typename iterator_traits<Rev_Iterator>::reference> {
	protected:
		Rev_Iterator rev_it;
		typedef iterator_traits<Rev_Iterator> traits_type;
	public:
		typedef Rev_Iterator iterator_type;
		typedef typename traits_type::difference_type difference_type;
		typedef typename traits_type::pointer pointer;
		typedef typename traits_type::reference reference;

		ReverseIterator() : rev_it() {}

		ReverseIterator(iterator_type obj) : rev_it(obj) {

		}

		ReverseIterator(const ReverseIterator &obj) : rev_it(obj.rev_it) {

		}

		template<typename Rev_Iter>
		ReverseIterator(const ReverseIterator<Rev_Iter> &obj) : rev_it(obj.base()) {

		}

		iterator_type
		base() const { return rev_it; }

		reference
		operator*() const {
			Rev_Iterator tmp = rev_it;
			return *--tmp;
		}

		pointer
		operator->() const { return &(operator*()); }

		ReverseIterator &
		operator++() {
			--rev_it;
			return *this;
		}

		ReverseIterator
		operator++(int) {
			ReverseIterator tmp = *this;
			--rev_it;
			return tmp;
		}

		ReverseIterator &
		operator--() {
			++rev_it;
			return *this;
		}

		ReverseIterator
		operator--(int) {
			ReverseIterator tmp = *this;
			++rev_it;
			return tmp;
		}

		ReverseIterator
		operator+(difference_type n) const {
			return ReverseIterator(rev_it - n);
		}

		ReverseIterator &
		operator+=(difference_type n) {
			rev_it -= n;
			return *this;
		}

		ReverseIterator
		operator-(difference_type n) const {
			return ReverseIterator(rev_it + n);
		}

		ReverseIterator &
		operator-=(difference_type n) {
			rev_it += n;
			return *this;
		}

		reference
		operator[](difference_type n) const {
			return *(*this + n);
		}
	};

	template<typename Rev_Iterator>
	bool
	operator!=(const ReverseIterator<Rev_Iterator> &obj,
			   const ReverseIterator<Rev_Iterator> &a_obj) {
		return (obj != a_obj);
	}

	template<typename Rev_Iterator>
	bool
	operator==(const ReverseIterator<Rev_Iterator> &obj,
			   const ReverseIterator<Rev_Iterator> &a_obj) {
		return obj.base() == a_obj.base();
	}

	template<typename Rev_Iterator>
	bool
	operator<(const ReverseIterator<Rev_Iterator> &obj,
			  const ReverseIterator<Rev_Iterator> &a_obj) {
		return a_obj.base() < obj.base();
	}

	template<typename Rev_Iterator>
	bool
	operator>(const ReverseIterator<Rev_Iterator> &obj,
			  const ReverseIterator<Rev_Iterator> &a_obj) {
		return a_obj < obj;
	}

	template<typename Rev_Iterator>
	bool
	operator>=(const ReverseIterator<Rev_Iterator> &obj,
			   const ReverseIterator<Rev_Iterator> &a_obj) {
		return !(obj < a_obj);
	}

	template<typename Rev_Iterator>
	bool
	operator<=(const ReverseIterator<Rev_Iterator> &obj,
			   const ReverseIterator<Rev_Iterator> &a_obj) {
		return !(a_obj < obj);
	}

	template<typename _IteratorL, typename _IteratorR>
	bool
	operator==(const ReverseIterator<_IteratorL> &obj,
			   const ReverseIterator<_IteratorR> &a_obj) {
		return obj.base() == a_obj.base();
	}

	template<typename _IteratorL, typename _IteratorR>
	bool
	operator<(const ReverseIterator<_IteratorL> &obj,
			  const ReverseIterator<_IteratorR> &a_obj) {
		return a_obj.base() < obj.base();
	}

	template<typename _IteratorL, typename _IteratorR>
	bool
	operator>(const ReverseIterator<_IteratorL> &obj,
			  const ReverseIterator<_IteratorR> &a_obj) {
		return a_obj < obj;
	}

	template<typename _IteratorL, typename _IteratorR>
	bool
	operator!=(const ReverseIterator<_IteratorL> &obj,
			   const ReverseIterator<_IteratorR> &a_obj) {
		return !(obj == a_obj);
	}

	template<typename _IteratorL, typename _IteratorR>
	bool
	operator<=(const ReverseIterator<_IteratorL> &obj,
			   const ReverseIterator<_IteratorR> &a_obj) {
		return !(a_obj < obj);
	}

	template<typename _IteratorL, typename _IteratorR>
	bool
	operator>=(const ReverseIterator<_IteratorL> &obj,
			   const ReverseIterator<_IteratorR> &a_obj) {
		return !(obj < a_obj);
	}

	template<class Iter1, class Iter2>
	typename ReverseIterator<Iter1>::difference_type
	operator-(const ReverseIterator<Iter1> &obj, const ReverseIterator<Iter2> &a_obj) {
		return a_obj.base() - obj.base();
	}

	template<class Iter>
	ReverseIterator<Iter> operator+(typename ReverseIterator<Iter>::difference_type n,
									const ReverseIterator<Iter> &obj) {
		return ReverseIterator<Iter>(obj.base() - n);
	}

	template<>
	struct is_integer<unsigned short> {
		enum {
			value = 1
		};
		typedef true_type type;
	};
	template<>
	struct is_integer<int> {
		enum {
			value = 1
		};
		typedef true_type type;
	};
	template<>
	struct is_integer<unsigned int> {
		enum {
			value = 1
		};
		typedef true_type type;
	};
	template<>
	struct is_integer<long> {
		enum {
			value = 1
		};
		typedef true_type type;
	};
	template<>
	struct is_integer<unsigned long> {
		enum {
			value = 1
		};
		typedef true_type type;
	};
	template<>
	struct is_integer<long long> {
		enum {
			value = 1
		};
		typedef true_type type;
	};


	template<>
	struct is_integer<unsigned long long> {
		enum {
			value = 1
		};
		typedef true_type type;
	};

	template<typename Tp>
	struct remove_const {
		typedef Tp type;
	};


	template<typename Tp>
	struct remove_const<Tp const> {
		typedef Tp type;
	};

	template<typename Tp>
	struct remove_volatile {
		typedef Tp type;
	};

	template<typename Tp>
	struct remove_volatile<Tp volatile> {
		typedef Tp type;
	};

	template<typename Tp>
	struct remove_cv {
		typedef typename remove_const<typename remove_volatile<Tp>::type>::type type;
	};

	template<typename>
	struct is_pointer_helper
			: public false_type {
	};

	template<typename Tp>
	struct is_pointer_helper<Tp *>
			: public true_type {
	};

	template<typename Tp>
	struct is_pointer
			: public is_pointer_helper<typename remove_cv<Tp>::type>::type {
	};
	template<typename Tp>
	struct is_integral : public integral_constant<bool, (is_integral_helper<typename
	remove_cv<Tp>::type>::value)> {
	};

	template<>
	struct is_integral<int> : ft::true_type {
	};

	template<class InputIterator1, class InputIterator2>
	bool
	lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2) {
		while (first1 != last1) {
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
			++first1;
			++first2;
		}
		return (first2 != last2);
	}

	template<bool Bool__Type>
	struct _equal {
		template<typename Type1, typename Type2>
		static bool equal(Type1 first1, Type1 last1, Type2 first2) {
			for (; first1 != last1; ++first1, ++first2)
				if ((*first1 != *first2))
					return false;
			return true;
		}
	};

	template<typename Type1, typename Type2>
	bool equal_aux(Type1 first1, Type1 last1, Type2 first2) {
		typedef typename ft::iterator_traits<Type1>::value_type ValueType_first;
		typedef typename ft::iterator_traits<Type2>::value_type ValueType_second;
		const bool simple = ((ft::is_integer<ValueType_first>::value
							  || ft::is_pointer<ValueType_first>::value)
							 && ft::is_pointer<Type1>::value
							 && ft::is_pointer<Type2>::value
							 && ft::are_same<ValueType_first, ValueType_second>::value);
		return ft::_equal<simple>::equal(first1, last1, first2);
	}

	template<typename Type1, typename Type2>
	bool
	equal(Type1 first1, Type1 last1, Type2 first2) {
		return ft::equal_aux(first1, last1, first2);
	}

}

#endif //CONTEINERS2_MY_REV_ITER_H

