/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Solver.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: p <p@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/23 16:35:03 by qlitzler          #+#    #+#             */
/*   Updated: 2015/07/30 11:11:12 by p                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SOLVER_CLASS_HPP
# define SOLVER_CLASS_HPP

#include <queue>
#include <list>
#include <map>
#include <set>
#include <NPuzzle.hpp>
#include <Grid.hpp>

struct						s_node
{
	s_node *				parent;
	s_tile *				state;
	std::string				hash;
	int						blank;
	int						h;
	int						g;
	int						f;
	std::vector<s_node>		children;
};

struct s_compare : public std::binary_function<s_node, s_node, bool>
{
	bool	operator()(s_node const & lhs, s_node const & rhs) const
	{
		return (lhs.f > rhs.f);
	}
};

class Solver
{
	public:
		Solver(Grid & grid);
		~Solver(void);

	private:
		Solver(void);
		
		void				AStar(void);
		void				generateStates(s_node & parent);
		std::string	const 	generateHash(s_tile * state);
		void				pushState(s_node & parent, int blank, int pos);
		void				swapTiles(s_tile & blank, s_tile & other);
		bool				find(std::map<std::string, int> & map, s_node & child);
		bool				isErased(std::string hash);
		void				finish(s_node * node);
		std::string			print(s_tile * state);
		void				printTiles(s_tile * state);

		Grid &						_grid;
		int							_selectedStates;
		int							_statesInMemory;
		int							_maxCoexistentStates;
		int							_moves;
		std::set<std::string>		_erased;
		std::list<std::string>		_output;
		std::map<std::string, int>	_open;
		std::map<std::string, int>	_closed;
		std::priority_queue<s_node, std::vector<s_node>, s_compare>	_queue;
};

#endif /* ! SOLVER_CLASS_HPP */