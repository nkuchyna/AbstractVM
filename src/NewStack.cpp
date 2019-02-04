/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NewStack.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 12:11:51 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/11/23 12:12:05 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NewStack.hpp"

template <typename T>
NewStack<T>::NewStack() : std::stack<T>() {
}

template <typename T>
NewStack<T>::NewStack(NewStack const &obj) : std::stack<T>() {
	*this = obj;
	return;
}

template <typename T>
NewStack<T>::~NewStack() {
}

template <typename T>
std::stack<T> NewStack<T>::getStack(void) const {
	return(this->_stack);
}

template <typename T>
void NewStack<T>::setStack(const std::stack<T> st) {
	this->_stack = st;
	return;
}

template <typename T>
typename    NewStack<T>::iterator NewStack<T>::end(void) {
	return(this->_stack::c.end());
}

template <typename T>
typename    NewStack<T>::iterator NewStack<T>::begin(void) {
	return (this->_stack::c.begin());
}

template <typename T>
int	NewStack<T>::size(void) {
	NewStack<T>::iterator it = this->begin();
	NewStack<T>::iterator ite = this->end();
	return(ite - it);
}
