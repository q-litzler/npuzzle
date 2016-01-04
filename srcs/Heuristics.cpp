/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Heuristics.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: p <p@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/26 18:51:25 by p                 #+#    #+#             */
/*   Updated: 2015/07/29 17:59:59 by p                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <iostream>
#include <Exceptions.hpp>
#include <Heuristics.hpp>

/*******************************************
	Constructors
*******************************************/

Heuristics::Heuristics(void)
{
	return;
}

/*******************************************
	Destructor
*******************************************/

Heuristics::~Heuristics(void)
{
	return;
}

/*******************************************
	Static functions
*******************************************/

int			Heuristics::getHeuristic(s_tile * state, int size, int rows)
{
	return ptr(state, size, rows);
}

void		Heuristics::setHeuristic(char const * heuristic)
{
	s_tab	tab[4] = { 
		{"m", &Heuristics::Manhattan}, 
		{"lc", &Heuristics::LinearConflict}, 
		{"ms", &Heuristics::Misplaced},
		{"rc", &Heuristics::RowColumn},
	};

	for (int i = 0; i < 4; ++i)
	{
		if (!std::strcmp(tab[i].type, heuristic))
		{
			Heuristics::ptr = tab[i].ptr;
			return;
		}
	}
	throw InvalidHeuristicException();
}

int			Heuristics::Manhattan(s_tile * state, int size, int rows)
{
	int		h = 0;

	(void)rows;
	for (int i = 0; i < size; ++i)
	{
		h += std::abs(state[i].pos.x - state[i].final.x) + std::abs(state[i].pos.y - state[i].final.y);
	}
	return (h);
}

int			Heuristics::LinearConflict(s_tile * state, int size, int rows)
{
	int		conflicts = 0;
	for (int i = 0; i < size; ++i)
	{
		for (int j = state[i].pos.y * rows; j < state[i].pos.y * rows + rows; ++j) // check just the same row
		{
			if (state[i].value != state[j].value			// jump itself
				&& state[i].pos.y == state[i].final.y 		// i is in its goal row
				&& state[j].pos.y == state[j].final.y 		// j is in its goal row
				&& state[i].pos.x > state[j].pos.x			// i is to the right of j
				&& state[i].final.x <= state[j].final.x)	// i goal is to the left of j position (or in j position)
			{
				++conflicts;
			}
		}
		for (int j = state[i].pos.x * rows; j < state[i].pos.x * rows + rows; j += rows) // check just the same col
		{
			if (state[i].value != state[j].value			// jump itself
				&& state[i].pos.x == state[i].final.x 		// i is in its goal col
				&& state[j].pos.x == state[j].final.x 		// j is in its goal col
				&& state[i].pos.y > state[j].pos.y			// i is under j
				&& state[i].final.y <= state[j].final.y)	// i goal is over j position (or in j position)
			{
				++conflicts;
			}
		}
	}
	return Heuristics::Manhattan(state, size, rows) + 2 * conflicts;
}

int			Heuristics::Misplaced(s_tile * state, int size, int rows)
{
	int		misplaced = 0;

	(void)rows;
	for (int i = 0; i < size; ++i)
	{
		if (state[i].pos.x != state[i].final.x || state[i].pos.y != state[i].final.y)
		{
			++misplaced;
		}
	}
	return misplaced;
}

int			Heuristics::RowColumn(s_tile * state, int size, int rows)
{
	int		row = 0;
	int		column = 0;

	(void)rows;
	for (int i = 0; i < size; ++i)
	{
		if (state[i].pos.x != state[i].final.x)
		{
			++column;
		}
		if (state[i].pos.y != state[i].final.y)
		{
			++row;
		}
	}
	return row + column;
}

f		Heuristics::ptr = nullptr;