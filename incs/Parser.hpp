/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: p <p@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/16 13:06:03 by qlitzler          #+#    #+#             */
/*   Updated: 2015/07/28 11:52:31 by p                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_CLASS_HPP
# define PARSER_CLASS_HPP

#include <fstream>
#include <Grid.hpp>

class Parser
{
	public:
		Parser(char const * path, char const * heurisitc, Grid & grid);
		~Parser(void);

	private:
		Parser(void);

		void					parse(void);
		void					checkPath(char const * path);
		void					checkSize(int rows);
		void					checkTile(int value);		
		void					checkGrid(void);

		Grid &					_grid;
		int						_rows;
		int						_totalTiles;	
		int						_count;
		bool *					_controlBuffer;
		std::ifstream			_file;
};

#endif /* ! PARSER_CLASS_HPP */
