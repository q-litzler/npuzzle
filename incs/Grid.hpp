/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Grid.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: p <p@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/16 14:08:05 by qlitzler          #+#    #+#             */
/*   Updated: 2015/07/27 19:21:11 by p                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRID_CLASS_HPP
# define GRID_CLASS_HPP

#include <vector>
#include <sstream>
#include <NPuzzle.hpp>

class Grid
{
	friend class Solver;

	public:
		Grid(void);
		~Grid(void);

		void			initialize(int rows, int size);
		void			addTile(int value, int pos);

	private:
		int				getFinalPosition(int value) const;
		void			calculateGoal(int rows);

		s_tile *		_initialState;
		int *			_goal;
		int				_rows;
		int				_size;
		int				_blankPosition;
};

#endif /* ! GRID_CLASS_HPP */
