#ifndef CONTEINERS2_MY_STACK_H
#define CONTEINERS2_MY_STACK_H

#include "vector.hpp"

namespace ft {
	template<class T, class Container = ft::vector<T> >
	// Stacks are a type of container adaptor, specifically designed to operate in a LIFO context (last-in first-out), where elements are inserted and extracted only from one end of the container.
	//
	//stacks are implemented as container adaptors, which are classes that use an encapsulated object of a specific container class as its underlying container, providing a specific set of member functions to access its elements. Elements are pushed/popped from the "back" of the specific container, which is known as the top of the stack.
	class stack {
	public:
		Container container;
	private:
		typedef typename Container::value_type container_value_type;
	public:
		typedef typename Container::value_type value_type; //The first template parameter (T)
		typedef Container container_type; //The second template parameter (Container)
		typedef typename Container::size_type size_type; //	an unsigned integral type
		typedef typename Container::reference reference;
		typedef typename Container::const_reference const_reference;

		//constructs the stack
		explicit stack(const Container m_c = Container()) : container(m_c) {}

		//destructs the stack
		~stack() {
		}

		stack &operator=(const stack &other) {
			if (this == &other)
				return *this;
			this->container = other.container;
			return *this;
		}

		bool empty() const {
			return container.empty();
		}

		size_type size() const {
			return container.size();
		}

		reference top() {
			return container.back();
		}

		const_reference top() const {
			return container.back();
		}

		void push(const value_type &obj) {
			container.push_back(obj);
		}

		void pop() {
			container.pop_back();
		}

		//assigns values to the container adaptor
		friend bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
			return lhs.container == rhs.container;
		}

		friend bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
			return lhs.container < rhs.container;
		}
	};


	template<typename T, typename Container>
	bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return lhs.container < rhs.container;
	}

	// operator >
	template<typename T, typename Container>
	bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return rhs.container < lhs.container;
	}

	// operator <=
	template<typename T, typename Container>
	bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return !(rhs.container < lhs.container);
	}

	// operator >=
	template<typename T, typename Container>
	bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return !(lhs.container < rhs.container);
	}

	//lexicographically compares the values in the stack
	// operator !=
	template<typename T, typename Container>
	bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return lhs.container != rhs.container;
	}

	// operator ==
	template<typename T, typename Container>
	bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return lhs.container == rhs.container;
	}
}

#endif //CONTEINERS2_MY_STACK_H

//https://www.cplusplus.com/reference/stack/stack/?kw=stack
//https://en.cppreference.com/w/cpp/container/stack
