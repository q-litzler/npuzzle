/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Heuristics.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: p <p@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/26 18:51:46 by p                 #+#    #+#             */
/*   Updated: 2015/07/29 17:56:53 by p                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEURISTICS_CLASS_HPP
# define HEURISTICS_CLASS_HPP

#include <NPuzzle.hpp>

typedef int	(*f)(s_tile *, int, int);

struct		s_tab
{
	char const * 	type;
	f				ptr;
};

class Heuristics
{
	public:
		Heuristics(void);
		~Heuristics(void);
		
		Heuristics &		operator=(Heuristics const & rhs);

		static void			setHeuristic(char const * heuristic);
		static int			getHeuristic(s_tile * state, int size, int rows);

	private:
		static int			Manhattan(s_tile * state, int size, int rows);
		static int			LinearConflict(s_tile * state, int size, int rows);
		static int			Misplaced(s_tile * state, int size, int rows);
		static int			RowColumn(s_tile * state, int size, int rows);
		static f			ptr;

};

#endif /* ! HEURISTICS_CLASS_HPP */
