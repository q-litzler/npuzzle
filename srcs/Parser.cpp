/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: p <p@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/16 13:05:45 by qlitzler          #+#    #+#             */
/*   Updated: 2015/07/28 12:31:28 by p                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <regex>
#include <iterator>
#include <Parser.hpp>
#include <Heuristics.hpp>
#include <Exceptions.hpp>

/*******************************************
	Constructors
*******************************************/

Parser::Parser(char const * path, char const * heuristic, Grid & grid) : _grid(grid), _rows(0), _totalTiles(0), _count(0), _controlBuffer(nullptr)
{
	Heuristics::setHeuristic(heuristic);
	this->checkPath(path);
	this->parse();
	this->checkGrid();
	return;
}

/*******************************************
	Destructor
*******************************************/

Parser::~Parser( void )
{
	return ;
}

/*******************************************
	Member functions
*******************************************/

void			Parser::checkPath(char const * path)
{
	this->_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	this->_file.open(path);
	this->_file.exceptions(std::ifstream::badbit);
}

void			Parser::parse(void)
{
	std::string			line;
	std::smatch			captured;
	std::regex const	pattern("\\d+");

	while (std::getline(this->_file, line))
	{
		auto begin = std::sregex_iterator(line.begin(), line.end(), pattern);
		auto end = std::sregex_iterator();		
		for (std::sregex_iterator it = begin; it != end; ++it)
		{
			if (!this->_rows)
			{
				this->checkSize(std::atoi((*it).str().c_str()));
				continue;
			}
			this->checkTile(std::atoi((*it).str().c_str()));
		}
	} 
}

void			Parser::checkSize(int rows)
{
	this->_rows = rows;
	if (this->_rows < MIN_ROWS || this->_rows > MAX_ROWS)
	{
		throw GridSizeException();
	}
	this->_totalTiles = this->_rows * this->_rows;
	this->_controlBuffer = new bool[this->_totalTiles]();
	this->_grid.initialize(this->_rows, this->_totalTiles);
}

void			Parser::checkTile(int value)
{
	if (value < 0 || value > this->_totalTiles - 1)
	{
		throw TileValueOutOfRangeException();
	}
	if (this->_controlBuffer[value])
	{
		throw TileDuplicateException();
	}
	this->_controlBuffer[value] = true;
	this->_grid.addTile(value, this->_count);
	this->_count += 1;
}

void			Parser::checkGrid(void)
{
	for (int i = 0; i < this->_totalTiles; ++i)
	{
		if (!this->_controlBuffer[i])
		{
			throw TileMissingException();
		}
	}
	if (this->_count != this->_totalTiles)
	{
		throw TileCountException();
	}
}