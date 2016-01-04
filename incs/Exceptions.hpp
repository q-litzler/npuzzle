/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exceptions.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: p <p@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/16 14:18:24 by qlitzler          #+#    #+#             */
/*   Updated: 2015/07/28 12:19:33 by p                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NPUZZLE_EXCEPTION_CLASS_HPP
# define NPUZZLE_EXCEPTION_CLASS_HPP

#include <exception>
#include <sstream>

/*******************************************
	EXCEPTIONS ABSTRACT BASE CLASS
*******************************************/

class NpuzzleException : public std::exception
{
	public:
		NpuzzleException(void);
		NpuzzleException(NpuzzleException const & model);
		virtual ~NpuzzleException(void) throw();

		NpuzzleException &			operator=(NpuzzleException const & rhs);

		virtual char const *	what(void) const throw() = 0;

	protected:
		std::string		_msg;
};


/*****************************************************************************/

/*******************************************
	GRID SIZE EXCEPTION
*******************************************/

class GridSizeException : public NpuzzleException
{
	public:
		GridSizeException(void);
		virtual char const * 	what(void) const throw();

};

/*******************************************
	TILE COUNT EXCEPTION
*******************************************/

class TileCountException : public NpuzzleException
{
	public:
		TileCountException(void);
		virtual char const * 	what(void) const throw();

};

/*******************************************
	DUPLICATE TILE EXCEPTION
*******************************************/

class TileDuplicateException : public NpuzzleException
{
	public:
		TileDuplicateException(void);
		virtual char const * 	what(void) const throw();

};

/*******************************************
	MISSING TILE EXCEPTION
*******************************************/

class TileMissingException : public NpuzzleException
{
	public:
		TileMissingException(void);
		virtual char const * 	what(void) const throw();

};

/*******************************************
	TILE VALUE OUT OF RANGE
*******************************************/

class TileValueOutOfRangeException : public NpuzzleException
{
	public:
		TileValueOutOfRangeException(void);
		virtual char const * 	what(void) const throw();

};

/*******************************************
	UNSOLVABLE NPUZZLE EXCEPTION
*******************************************/

class UnsolvableNpuzzle : public NpuzzleException
{
	public:
		UnsolvableNpuzzle(void);
		virtual char const * 	what(void) const throw();

};

/*******************************************
	UNKNOWN EXCEPTION
*******************************************/

class UnknownException : public NpuzzleException
{
	public:
		UnknownException(void);
		virtual char const * 	what(void) const throw();

};

/*******************************************
	INVALID HEURISTICS EXCEPTION
*******************************************/

class InvalidHeuristicException : public NpuzzleException
{
	public:
		InvalidHeuristicException(void);
		virtual char const * 	what(void) const throw();

};

#endif /* ! NPUZZLE_EXCEPTION_CLASS_HPP */
