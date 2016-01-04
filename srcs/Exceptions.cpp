/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exceptions.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: p <p@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/16 14:18:17 by qlitzler          #+#    #+#             */
/*   Updated: 2015/07/28 12:20:35 by p                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Exceptions.hpp>
#include <NPuzzle.hpp>

/*******************************************
	NPUZZLE EXCEPTION ABSTRACT BASE CLASS
*******************************************/

NpuzzleException::NpuzzleException(void) : std::exception()
{
	return;
}

NpuzzleException::NpuzzleException(NpuzzleException const & model) : std::exception()
{
	*this = model;
	return;
}

NpuzzleException::~NpuzzleException(void) throw()
{
	return;
}

NpuzzleException &	NpuzzleException::operator=(NpuzzleException const & rhs)
{
	if (this != &rhs)
	{

	}
	return *this;
}

/*******************************************
	GRID SIZE EXCEPTION
*******************************************/

GridSizeException::GridSizeException(void): NpuzzleException()
{
	return;
}

char const *	GridSizeException::what(void) const throw()
{
	return "Grid row size must be within 3 and 50.";
}

/*******************************************
	TILE COUNT EXCEPTION
*******************************************/

TileCountException::TileCountException() : NpuzzleException()
{

}

char const *	TileCountException::what(void) const throw()
{
	return "Incorrect tiles number.";
}

/*******************************************
	DUPLICATE TILE EXCEPTION
*******************************************/

TileDuplicateException::TileDuplicateException(void) : NpuzzleException()
{
	return;
}

char const *	TileDuplicateException::what(void) const throw()
{
	return "Duplicated tiles are not allowed";
}

/*******************************************
	MISSING TILE EXCEPTION
*******************************************/

TileMissingException::TileMissingException(void) : NpuzzleException()
{
	return;
}

char const *	TileMissingException::what(void) const throw()
{
	return "Tile is missing";
}


/*******************************************
	TILE VALUE OUT OF RANGE
*******************************************/

TileValueOutOfRangeException::TileValueOutOfRangeException(void) : NpuzzleException()
{
	return;
}

char const *	TileValueOutOfRangeException::what(void) const throw()
{
	return "Tiles value is out of range";
}

/*******************************************
	UNSOLVABLE NPUZZLE
*******************************************/

UnsolvableNpuzzle::UnsolvableNpuzzle(void) : NpuzzleException()
{
	return;
}

char const *	UnsolvableNpuzzle::what(void) const throw()
{
	return  "This Npuzzle is not solvable";
}

/*******************************************
	UNKNOWN EXCEPTION
*******************************************/

UnknownException::UnknownException(void) : NpuzzleException()
{
	return;
}

char const *	UnknownException::what(void) const throw()
{
	return  "Unknwon Exception";
}

/*******************************************
	INVALID HEURISTICS EXCEPTION
*******************************************/

InvalidHeuristicException::InvalidHeuristicException(void) : NpuzzleException()
{
	return;
}

char const *	InvalidHeuristicException::what(void) const throw()
{
	return  "Invalid heuristc";
}
