/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbroggi <pbroggi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/16 12:57:43 by qlitzler          #+#    #+#             */
/*   Updated: 2015/10/17 16:07:26 by pbroggi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include <Exceptions.hpp>
#include <NPuzzle.hpp>
#include <Parser.hpp>
#include <Solver.hpp>

static void		exceptionsHandler( std::exception & e )
{
	if (typeid(e) == typeid(std::ifstream::failure))
	{
		std::cerr << RED << "Npuzzle error" << ": " << std::strerror(errno) << std::endl;
	}
	else
	{
		std::cerr << RED << "Npuzzle error" << ": " << e.what() << std::endl;
	}
}

int				main( int argc, char **argv )
{
	if (argc != 3)
	{
		std::cerr << "Usage: " << "./npuzzle <file> <heuristic>" << std::endl;
		std::cerr << "Available heuristics: " << std::endl;
		std::cerr << "- linear conflict [lc]" << std::endl;
		std::cerr << "- manhattan [m]" << std::endl;
		std::cerr << "- row/column [rc]" << std::endl;
		std::cerr << "- misplaced [ms]" << std::endl;
		return (EXIT_FAILURE);
	}
	try
	{
		Grid				grid;
		Parser				parser(argv[1], argv[2], grid);
		Solver				solver(grid);
	}
	catch ( std::exception & e)
	{
		exceptionsHandler(e);
	}
	return (EXIT_SUCCESS);
}