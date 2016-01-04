/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NPuzzle.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: p <p@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/16 13:02:25 by qlitzler          #+#    #+#             */
/*   Updated: 2015/07/28 18:08:20 by p                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NPUZZLE_H
# define NPUZZLE_H

# define RED		"\x1b[31m"
# define WHITE		"\x1b[0m"
# define CYAN		"\x1b[36m"
# define GREEN		"\x1b[32m"

#define MIN_ROWS	3
#define MAX_ROWS	50

struct				s_coord
{
	int				x;
	int				y;
};

struct				s_tile
{
	int				value;
	s_coord			pos;
	s_coord			final;
};
#endif