/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Grid.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: p <p@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/16 14:07:47 by qlitzler          #+#    #+#             */
/*   Updated: 2015/07/27 19:21:33 by p                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <Grid.hpp>
#include <Exceptions.hpp>

/*******************************************
	Constructors
*******************************************/

Grid::Grid(void) : _initialState(nullptr), _goal(nullptr), _rows(0), _size(0), _blankPosition(0)
{
	return;
}

/*******************************************
	Destructor
*******************************************/

Grid::~Grid(void)
{
	return ;
}

/*******************************************
	Member functions
*******************************************/

void			Grid::initialize(int rows, int size)
{
	this->_rows = rows;
	this->_size = size;
	this->_initialState = new s_tile[this->_size]();
	this->_goal = new int[this->_size]();
	this->calculateGoal(this->_rows);
}


void			Grid::addTile(int value, int startPos)
{
	static int 	i = 0;
	int			finalPos = getFinalPosition(value);

	this->_initialState[i].value = value;
	this->_initialState[i].pos.x = startPos % this->_rows;
	this->_initialState[i].pos.y = startPos / this->_rows;
	this->_initialState[i].final.x = finalPos % this->_rows;
	this->_initialState[i].final.y = finalPos / this->_rows;
	++i;
	if (value == 0)
	{
		this->_blankPosition = startPos;
	}
}


void			Grid::calculateGoal(int period)
{
	int		offset[4] = {1, this->_rows, -1, -this->_rows};
	int		index = -1;
	int		i, count, value, loop;
	
	i = count = 0;
	value = loop = 1;
	while (value < this->_size)
	{
		if (count < period)
		{
			index += offset[i];
			this->_goal[index] = value++;
			++count;
			continue;
		}
		++loop;
		count = 0;
		period -= loop % 2 ? 0: 1;
		i += i == 3 ? -3 : 1;
	}
}

int				Grid::getFinalPosition(int value) const
{
	for (int i = 0; i < this->_size; ++i)
	{
		if (this->_goal[i] == value)
		{
			return i;
		}
	}
	throw UnknownException();
}