/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Solver.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbroggi <pbroggi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/23 16:34:34 by qlitzler          #+#    #+#             */
/*   Updated: 2015/10/17 16:22:58 by pbroggi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <sstream>
#include <Solver.hpp>
#include <Heuristics.hpp>
#include <Exceptions.hpp>
#include <NPuzzle.hpp>

/*******************************************
	Constructors
*******************************************/

Solver::Solver(Grid & grid): _grid(grid), _selectedStates(0), _statesInMemory(0), _maxCoexistentStates(0), _moves(0)
{
	s_node		startNode;

	startNode.parent = nullptr;
	startNode.state = this->_grid._initialState;
	startNode.hash = this->generateHash(startNode.state);
	startNode.blank = this->_grid._blankPosition;
	startNode.h = startNode.f = Heuristics::getHeuristic(startNode.state, this->_grid._size, this->_grid._rows);
	startNode.g = 0;
	this->_queue.push(startNode);
	this->AStar();
	return;
}

/*******************************************
	Destructor
*******************************************/

Solver::~Solver(void)
{
	return ;
}

/*******************************************
	Member functions
*******************************************/

void				Solver::AStar(void)
{
	s_node							current;
	std::vector<s_node>::iterator	it;
	int								stateCount = 0;

	while (!this->_queue.empty())
	{
		do
		{
			current = this->_queue.top();
			this->_queue.pop();
			--this->_statesInMemory;
		}
		while (this->isErased(current.hash) && !this->_queue.empty());
		++this->_selectedStates;
		if (!current.h)
		{
			this->finish(&current);
			return ;
		}
		this->generateStates(current);
		for (it = current.children.begin(); it != current.children.end(); ++it)
		{
			if (!find(this->_closed, *it) && !find(this->_open, *it))
			{
				(*it).parent = new s_node(current);
				this->_queue.push(*it);
				this->_open[(*it).hash] = (*it).f;
				++this->_statesInMemory;
			}
		}
		this->_closed[current.hash] = current.f;
		stateCount = this->_open.size();
		this->_maxCoexistentStates = stateCount > this->_maxCoexistentStates ? stateCount : this->_maxCoexistentStates;
	}
	throw UnsolvableNpuzzle();
}

void				Solver::generateStates(s_node & parent)
{
	int	up = parent.blank - this->_grid._rows;
	int	down = parent.blank + this->_grid._rows;

	if (up >= 0)
	{
		this->pushState(parent, parent.blank, up);
	}
	if ((parent.blank % this->_grid._rows) != this->_grid._rows - 1)
	{
		this->pushState(parent, parent.blank, parent.blank + 1);
	}
	if (down < this->_grid._size)
	{
		this->pushState(parent, parent.blank, down);
	}
	if ((parent.blank % this->_grid._rows) != 0)
	{
		this->pushState(parent, parent.blank, parent.blank - 1);
	}
}

void				Solver::pushState(s_node & parent, int blank, int pos)
{
	s_tile *	state = new s_tile[this->_grid._size];
	s_node		node;
	
	std::copy(parent.state, parent.state + this->_grid._size, state);
	this->swapTiles(state[blank], state[pos]);
	node.parent = nullptr;
	node.state = state;
	node.hash = this->generateHash(state);
	node.blank = pos;
	node.h = Heuristics::getHeuristic(state, this->_grid._size, this->_grid._rows);
	node.g = parent.g + 1;
	node.f = node.g + node.h;
	parent.children.push_back(node);
}

void				Solver::swapTiles(s_tile & blank, s_tile & other)
{
	s_coord	tmp = blank.final;

	blank.value = other.value;
	other.value = 0;
	blank.final = other.final;
	other.final = tmp;
}

std::string	const	Solver::generateHash(s_tile * state)
{
	std::string		hash;

	for (int i = 0; i < this->_grid._size; ++i)
	{
		hash += state[i].value + '0';
	}
	return hash;
}

bool				Solver::find(std::map<std::string, int> & map, s_node & node)
{
	std::map<std::string, int>::iterator	it;

	it = map.find(node.hash);
	if (it != map.end())
	{
		if (node.f < (*it).second)
		{
			map.erase(it);
			this->_erased.insert((*it).first);
			return false;
		}
		return true;
	}
	return false;
}

bool				Solver::isErased(std::string hash)
{
	std::set<std::string>::iterator	it;

	it = this->_erased.find(hash);
	if (it != this->_erased.end())
	{
		return true;
	}
	return false;
}

std::string			Solver::print(s_tile * state)
{
	std::stringstream	out;

	for (int i = 0; i < this->_grid._size; ++i)
	{
		(i % this->_grid._rows) ? out << "\t" : out << std::endl;
		if (!state[i].value)
		{
			out << " ";
		}
		else
		{
			out << state[i].value;
		}
	}
	return (out.str());
}

void				Solver::finish(s_node * node)
{
	std::list<std::string>::iterator	it;

	while (node->parent)
	{
		++this->_moves;
		this->_output.push_front(this->print(node->state));
		node = node->parent;
	}
	for ( it = this->_output.begin(); it != this->_output.end(); ++it)
	{
		std::cout << *it << std::endl;
	}
	std::cout
		<< std::endl 
		<< WHITE << "Space complexity (max states allocated in memory at same time): " << CYAN << this->_maxCoexistentStates << std::endl
		<< WHITE << "Time complexity (Total states selected in the open set): " << CYAN << this->_selectedStates << std::endl
		<< WHITE << "Total moves to solve: " << CYAN << this->_moves << std::endl
		<< WHITE << "Details: " << std::endl;
}