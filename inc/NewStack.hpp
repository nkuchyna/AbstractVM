/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NewStack.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 12:12:12 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/11/23 12:12:15 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NEWSTACK_HPP
#define NEWSTACK_HPP
#include "AbstractVM.hpp"

template <typename T>

class NewStack: public std::stack<T> {

private:
	typedef		std::stack<T>	_stack;
	static 		int 			_size;

public:
	NewStack();
	~NewStack();
	NewStack(const NewStack &obj);

	std::stack<T>		getStack(void) const;
	void				setStack(const std::stack<T> st);
	using				_stack::operator=;
	typedef typename	_stack::container_type::iterator	iterator;
	iterator			begin(void);
	iterator			end(void);

	int					size(void);
};

#endif
