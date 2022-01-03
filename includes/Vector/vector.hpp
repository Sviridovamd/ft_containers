#pragma once
#ifndef FT_VECTOR_H__
#define FT_VECTOR_H__

//#include "vector_iterator.hpp"
#include "../tree_u.h"
#include <iostream>

namespace ft {
	///Iterator
	//is the base class provided to simplify definitions of the required types for iterators.
	template<typename Iterator>
	class VectorIterator {
	protected:
		Iterator m_it_c;
		typedef typename ft::iterator_traits<Iterator> traits_type;
	public:
		typedef Iterator iterator_type;
		typedef typename traits_type::iterator_category iterator_category;
		typedef typename traits_type::value_type value_type;
		typedef typename traits_type::difference_type difference_type;
		typedef typename traits_type::reference reference;
		typedef typename traits_type::pointer pointer;

		VectorIterator() : m_it_c(Iterator()) {}

		VectorIterator(const Iterator &i) : m_it_c(i) {}

		// Allow iterator to const_iterator conversion
		template<typename _Iter>
		VectorIterator(const VectorIterator<_Iter> &src) : m_it_c(src.base()) {}

		// Forward iterator requirements
		reference operator*() const {
			return *m_it_c;
		}

		pointer operator->() const {
			return m_it_c;
		}

		VectorIterator &operator++() {
			++m_it_c;
			return *this;
		}

		VectorIterator operator++(int) {
			return VectorIterator(m_it_c++);
		}

		// Bidirectional iterator requirements
		VectorIterator &operator--() {
			--m_it_c;
			return *this;
		}

		VectorIterator operator--(int) {
			return VectorIterator(m_it_c--);
		}

		// Random access iterator requirements
		reference operator[](difference_type it) const {
			return m_it_c[it];
		}

		VectorIterator &operator+=(difference_type it) {
			m_it_c += it;
			return *this;
		}

		VectorIterator operator+(difference_type it) const {
			return VectorIterator(m_it_c + it);
		}

		VectorIterator &operator-=(difference_type it) {
			m_it_c -= it;
			return *this;
		}

		VectorIterator operator-(difference_type it) const {
			return VectorIterator(m_it_c - it);
		}

		const Iterator &base() const {
			return m_it_c;
		}
	};

	template<typename L_Iterator, typename R_Iterator>
	bool operator==(const VectorIterator<L_Iterator> &lhs,
					const VectorIterator<R_Iterator> &rhs) {
		return lhs.base() == rhs.base();
	}

	template<typename BASE_Iterator>
	bool operator==(const VectorIterator<BASE_Iterator> &lhs,
					const VectorIterator<BASE_Iterator> &rhs) {
		return lhs.base() == rhs.base();
	}

	template<typename L_Iterator, typename R_Iterator>
	bool operator!=(const VectorIterator<L_Iterator> &lhs,
					const VectorIterator<R_Iterator> &rhs) {
		return lhs.base() != rhs.base();
	}

	template<typename BASE_Iterator>
	bool operator!=(const VectorIterator<BASE_Iterator> &lhs,
					const VectorIterator<BASE_Iterator> &rhs) {
		return lhs.base() != rhs.base();
	}

	template<typename L_Iterator, typename R_Iterator>
	bool operator<(const VectorIterator<L_Iterator> &lhs,
				   const VectorIterator<R_Iterator> &rhs) {
		return lhs.base() < rhs.base();
	}

	template<typename BASE_Iterator>
	bool operator<(const VectorIterator<BASE_Iterator> &lhs,
				   const VectorIterator<BASE_Iterator> &rhs) {
		return lhs.base() < rhs.base();
	}

	template<typename L_Iterator, typename R_Iterator>
	bool operator>(const VectorIterator<L_Iterator> &lhs,
				   const VectorIterator<R_Iterator> &rhs) {
		return lhs.base() > rhs.base();
	}

	template<typename BASE_Iterator>
	bool operator>(const VectorIterator<BASE_Iterator> &lhs,
				   const VectorIterator<BASE_Iterator> &rhs) {
		return lhs.base() > rhs.base();
	}

	template<typename L_Iterator, typename R_Iterator>
	bool
	operator<=(const VectorIterator<L_Iterator> &lhs,
			   const VectorIterator<R_Iterator> &rhs) {
		return lhs.base() <= rhs.base();
	}

	template<typename BASE_Iterator>
	bool
	operator<=(const VectorIterator<BASE_Iterator> &lhs,
			   const VectorIterator<BASE_Iterator> &rhs) {
		return lhs.base() <= rhs.base();
	}

	template<typename L_Iterator, typename R_Iterator>
	bool
	operator>=(const VectorIterator<L_Iterator> &lhs,
			   const VectorIterator<R_Iterator> &rhs) {
		return lhs.base() >= rhs.base();
	}

	template<typename BASE_Iterator>
	bool
	operator>=(const VectorIterator<BASE_Iterator> &lhs,
			   const VectorIterator<BASE_Iterator> &rhs) {
		return lhs.base() >= rhs.base();
	}

	template<typename L_Iterator, typename R_Iterator>
	typename VectorIterator<L_Iterator>::difference_type
	operator-(const VectorIterator<L_Iterator> &lhs,
			  const VectorIterator<R_Iterator> &rhs) {
		return lhs.base() - rhs.base();
	}

	template<typename BASE_Iterator>
	typename VectorIterator<BASE_Iterator>::difference_type
	operator-(const VectorIterator<BASE_Iterator> &lhs,
			  const VectorIterator<BASE_Iterator> &rhs) {
		return lhs.base() - rhs.base();
	}

	template<typename BASE_Iterator>
	VectorIterator<BASE_Iterator>
	operator+(typename VectorIterator<BASE_Iterator>::difference_type
			  it, const VectorIterator<BASE_Iterator> &i) {
		return VectorIterator<BASE_Iterator>(i.base() + it);
	}

	template<class T>
	VectorIterator<T> operator+(typename VectorIterator<T>::difference_type i, VectorIterator<T> &tmp) {
		return tmp.base() + i;
	}

	template<class T>
	VectorIterator<T> operator+(VectorIterator<T> &tmp, typename VectorIterator<T>::difference_type i) {
		return tmp.base() + i;
	}

	///VECTOR
	//https://www.cplusplus.com/reference/vector/vector/?kw=vector
	//Vectors are sequence containers representing arrays that can change in size.
	template<class T, class Alloc = std::allocator<T> >
	class vector {
	private:
		T *m_array;
		size_t m_size;
		size_t m_capacity;
		Alloc m_alloc;
	public:
		//Member types
		//	The first template parameter (T)
		typedef T value_type;
		// 	The second template parameter (Alloc)
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		//	a signed integral type, identical to: iterator_traits<iterator>::difference_type
		typedef std::ptrdiff_t difference_type;
		//	an unsigned integral type that can represent any non-negative value of difference_type
		typedef size_t size_type;
		typedef VectorIterator<pointer> iterator;
		typedef VectorIterator<const_pointer> const_iterator;
		typedef ft::ReverseIterator<iterator> reverse_iterator;
		typedef ft::ReverseIterator<const_iterator> const_reverse_iterator;

		explicit vector(const allocator_type &alloc = allocator_type()) :
				m_array(),
				m_size(0),
				m_capacity(0),
				m_alloc(alloc) {

		}

		explicit vector(size_type it, const value_type &val = value_type(),
						const allocator_type &alloc = allocator_type()) {
			m_alloc = alloc;
			m_size = it;
			m_capacity = m_size;
			m_array = m_alloc.allocate(it);
			for (size_t i = 0; i < m_size; i++) {
				m_alloc.construct(m_array + i, val);
			}
		}

		vector(const vector &obj) : m_size(), m_capacity() {
			*this = obj;
		}

		template<class InputIterator>
		vector(InputIterator first,
			   typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last,
			   const allocator_type &alloc = allocator_type()) : m_alloc(alloc) {
			difference_type len = ft::distance(first, last);
			m_array = m_alloc.allocate(len);
			m_size = len;
			m_capacity = len;

			for (size_type i = 0; i < m_size; i++) {
				m_alloc.construct(m_array + i, *(first + i));
			}
		}

		~vector() {
			for (size_t i = 0; i < m_size; i++)
				m_alloc.destroy(m_array + i);
			m_alloc.deallocate(m_array, m_capacity);
		}


		vector &operator=(const vector &obj);

		const_reference operator[](size_t index) const {
			return (m_array[index]);
		}

		reference operator[](size_t index) {
			return (m_array[index]);
		}

		iterator begin() {
			return (iterator(m_array));
		}

		iterator end() {
			return (iterator(m_array + m_size));
		}

		const_iterator begin() const {
			return (const_iterator(m_array));
		}

		const_iterator end() const {
			return (const_iterator(m_array + m_size));
		}

		reverse_iterator rbegin() {
			return (reverse_iterator(this->end()));
		}

		reverse_iterator rend() {
			return (reverse_iterator(this->begin()));
		}

		const_reverse_iterator rbegin() const {
			return (const_reverse_iterator(end()));
		}

		const_reverse_iterator rend() const {
			return (const_reverse_iterator(begin()));
		}

		size_t size() const {
			return (this->m_size);
		}

		size_t capacity() {
			return (this->m_capacity);
		}

		size_type max_size() {
			return (m_alloc.max_size());
		}

		allocator_type get_allocator() {
			return (Alloc());
		}

		bool empty() const {
			return (!m_size);
		}

//		iterator insert(iterator pos, const T &value);
//
//		void insert(iterator pos, size_type count, const T &value);

		iterator insert(iterator pos, const T &value);

		void insert(iterator pos, size_type count, const T &value);

		template<class InputIt>
		void insert(iterator pos, InputIt first, typename enable_if<!is_integral<InputIt>::value, InputIt>::type last);

		void swap(vector &src);

		void reserve(size_type new_cap);

		void resize(size_type it, T value = value_type());

		void assign(size_type count, const T &value);

		void push_back(const T &value);

		void pop_back();

		void clear();

		template<class InputIt>
		void assign(InputIt first, typename enable_if<!is_integral<InputIt>::value, InputIt>::type last);

		iterator erase(iterator pos);

		iterator erase(iterator first, iterator last);

		reference at(size_t index);

		const_reference at(size_t index) const;

		reference front() {
			return m_array[0];
		}

		const_reference front() const {
			return m_array[0];
		}

		reference back() {
			return m_array[m_size - 1];
		}

		const_reference back() const {
			return m_array[m_size - 1];
		}

	private:
		void reAlloc(size_t newCapacity);

		class OutOfBoundsException : public std::exception {
			virtual const char *what() const throw() { return ("Out of bounds"); }
		};

		class MaxSizeException : public std::exception {
			virtual const char *what() const throw() { return ("Maximum size exceeded"); }
		};

	};


	template<class T, class Alloc>
	ft::vector<T, Alloc> &ft::vector<T, Alloc>::operator=(const vector &obj) {
		if (this != &obj) {
			this->m_alloc = obj.m_alloc;
			this->m_size = obj.m_size;
			this->m_capacity = obj.m_capacity;
			this->m_array = this->m_alloc.allocate(m_capacity);
			for (size_t i = 0; i < obj.m_size; i++) {
				m_alloc.construct(this->m_array + i, *(obj.m_array + i));
			}
		}
		return *this;
	}

	template<class T, class Alloc>
	typename ft::vector<T, Alloc>::reference ft::vector<T, Alloc>::at(size_t index) {
		if (index >= m_size)
			throw OutOfBoundsException();
		return (m_array[index]);
	}

	template<class T, class Alloc>
	typename ft::vector<T, Alloc>::const_reference ft::vector<T, Alloc>::at(size_t index) const {
		if (index >= m_size)
			throw OutOfBoundsException();
		return (m_array[index]);
	}

	template<class T, class Alloc>
	typename ft::vector<T, Alloc>::iterator ft::vector<T, Alloc>::erase(iterator pos) {
		size_type i = ft::distance(begin(), pos);
		m_alloc.destroy(&(*pos));
		for (; i < m_size - 1; i++)
			m_array[i] = m_array[i + 1];
		m_size--;
		return (pos);
	}

	template<class T, class Alloc>
	typename ft::vector<T, Alloc>::iterator ft::vector<T, Alloc>::erase(iterator first, iterator last) {
		size_type start = ft::distance(begin(), first);
		size_type count = ft::distance(first, last);
		for (; first != last; first++)
			m_alloc.destroy(&(*first));
		for (; start < m_size - count; start++)
			m_array[start] = m_array[start + count];
		m_size -= count;
		return (first);
	}

	template<class T, class Alloc>
	void ft::vector<T, Alloc>::resize(size_type it, value_type val) {
		if (it == this->m_size)
			return;
		else if (it > this->m_size) {
			while (it > m_size) {
				if (it > m_capacity)
					reAlloc(it);
				m_alloc.construct(this->m_array + (m_size++), val);
			}
		} else if (it < this->m_size) {
			for (size_t i = m_size; i > it; i--)
				m_alloc.destroy(m_array + i);
			m_size = it;
		}
	}

	template<class T, class Alloc>
	void ft::vector<T, Alloc>::reserve(size_type new_cap) {
		if (new_cap > max_size())
			throw MaxSizeException();
		else if (new_cap <= m_capacity)
			return;
		else
			reAlloc(new_cap);
	}

	template<class T, class Alloc>
	void ft::vector<T, Alloc>::reAlloc(size_t newCapacity) {

		T *newBlock = m_alloc.allocate(newCapacity);

		if (newCapacity < m_size)
			m_size = newCapacity;
		for (size_t i = 0; i < m_size; i++)
			newBlock[i] = m_array[i];

		m_alloc.deallocate(m_array, m_capacity);
		m_array = newBlock;
		m_capacity = newCapacity;
	}

	template<class T, class Alloc>
	void ft::vector<T, Alloc>::push_back(const T &value) {
		if (m_size >= m_capacity)
			reAlloc(m_capacity ? m_capacity * 2 : 2);
		m_alloc.construct(m_array + m_size++, value);
	}

	template<class T, class Alloc>
	void ft::vector<T, Alloc>::pop_back() {
		m_alloc.destroy(m_array + m_size);
		m_size--;
	}

	template<class T, class Alloc>
	void ft::vector<T, Alloc>::clear() {
		for (size_t i = 0; i < m_size; i++)
			m_alloc.destroy(m_array + i);
		m_size = 0;
	}

	template<class T, class Alloc>
	void ft::vector<T, Alloc>::assign(size_type count, const T &value) {
		clear();
		insert(begin(), count, value);
	}

	template<class T, class Alloc>
	template<class InputIt>
	void
	ft::vector<T, Alloc>::assign(InputIt first, typename enable_if<!is_integral<InputIt>::value, InputIt>::type last) {
		clear();
		insert(begin(), first, last);
	}

	template<class T, class Alloc>
	typename ft::vector<T, Alloc>::iterator ft::vector<T, Alloc>::insert(iterator pos, const T &value) {
		size_type it = ft::distance(this->begin(), pos);
		if (m_size + 1 > m_capacity) {
			T *newBlock;
			newBlock = m_alloc.allocate(m_capacity ? m_capacity * 2 : 2);
			size_type i;
			for (i = 0; i < it; i++)
				m_alloc.construct(newBlock + i, *(m_array + i));
			m_alloc.construct(newBlock + i++, value);
			m_size++;
			for (; i < m_size; i++) {
				m_alloc.construct(newBlock + i, *(m_array + i - 1));
				m_alloc.destroy(m_array + i);
			}
			m_alloc.deallocate(m_array, m_capacity);
			this->m_array = newBlock;
			m_capacity *= 2;
		} else {
			size_type i;
			for (i = m_size; i > it; i--)
				m_array[i] = m_array[i - 1];
			m_size++;
			m_alloc.construct(m_array + i, value);
		}
		return (iterator(m_array + it));

	}

	template<class T, class Alloc>
	void ft::vector<T, Alloc>::insert(iterator pos, size_type count, const T &value) {
		size_type it = ft::distance(this->begin(), pos);
		if (m_size + count > m_capacity) {
			T *newBlock;
			size_type newCapacity = m_capacity ? m_capacity * 2 : 2;
			while (m_size + count > newCapacity)
				newCapacity *= 2;
			newBlock = m_alloc.allocate(newCapacity);
			size_type i;
			for (i = 0; i < it; i++)
				m_alloc.construct(newBlock + i, *(m_array + i));
			for (int tmp = count; tmp > 0; tmp--, m_size++, i++)
				m_alloc.construct(newBlock + i, value);
			for (; i < m_size; i++) {
				m_alloc.construct(newBlock + i, *(m_array + i - count));
				m_alloc.destroy(m_array + i);
			}
			m_alloc.deallocate(m_array, m_capacity);
			this->m_array = newBlock;
			m_capacity = newCapacity;

		} else {
			size_type i;
			size_type stop;
			if( count > it)
				stop = count;
			else
				stop = it;
			for (i = m_size + count; i > stop; i--)
				m_array[i] = m_array[i - count];
			m_size += count;
			for (; count > 0; count--, i++)
				m_alloc.construct(m_array + i, value);

		}
	}

	template<class T, class Alloc>
	template<class InputIt>
	void ft::vector<T, Alloc>::insert(iterator pos, InputIt first,
									  typename enable_if<!is_integral<InputIt>::value, InputIt>::type last) {
		size_type it = ft::distance(this->begin(), pos);
		size_type count = ft::distance(first, last);

		if (m_size + count > m_capacity) {
			T *newBlock;
			size_type newCapacity = m_capacity ? m_capacity * 2 : 2;

			while (m_size + count > newCapacity)
				newCapacity *= 2;
			newBlock = m_alloc.allocate(newCapacity);
			size_type i;
			for (i = 0; i < it; i++)
				m_alloc.construct(newBlock + i, *(m_array + i));
			for (int tmp = count; tmp > 0; tmp--, m_size++, i++, first++)
				m_alloc.construct(newBlock + i, *first);
			for (; i < m_size; i++) {
				m_alloc.construct(newBlock + i, *(m_array + i - count));
				m_alloc.destroy(m_array + i);
			}
			m_alloc.deallocate(m_array, m_capacity);
			this->m_array = newBlock;
			m_capacity = newCapacity;
		} else {
			size_type i;
			size_type stop;
			if (count > it)
				stop = count;
			else
				stop = it;
			for (i = m_size + count; i > stop; i--)
				m_array[i] = m_array[i - count];
			m_size += count;

			for (; count > 0; count--, i++, first++)
				m_alloc.construct(m_array + i, *first);
		}
	}

	template<class T, class Alloc>
	bool operator==(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) {
		if (lhs.size() != rhs.size())
			return false;
		for (typename ft::vector<T>::size_type i = 0; i < lhs.size(); i++) {
			if (lhs[i] != rhs[i])
				return (false);
		}
		return true;
	}

	template<class T, class Alloc>
	bool operator!=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) {
		return !(lhs == rhs);
	}

	template<class T, class Alloc>
	bool operator<(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template<class T, class Alloc>
	bool operator<=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) {
		return !(rhs < lhs);
	}

	template<class T, class Alloc>
	bool operator>(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) {
		return rhs < lhs;
	}

	template<class T, class Alloc>
	bool operator>=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) {
		return !(lhs < rhs);
	}

	template<class T, class Alloc>
	void ft::vector<T, Alloc>::swap(vector &src) {
		ft::swap(m_array, src.m_array);
		ft::swap(m_size, src.m_size);
		ft::swap(m_capacity, src.m_capacity);
	}
}
#endif //CONTEINERS_MY_VECTOR_H