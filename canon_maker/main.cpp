/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zminhas <zminhas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 17:48:23 by zminhas           #+#    #+#             */
/*   Updated: 2022/04/30 16:58:04 by zminhas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "canon_maker.hpp"

std::string	upper_string(std::string str)
{
	std::string	ret = str;

	for (int i = 0; i < (int)str.length(); i++)
		ret[i] = (char)toupper(ret[i]);
	return (ret);
}

int	return_error(void)
{
	std::cout << "Error" << std::endl;
	return (1);
}

int	main(int ac, char **av)
{
	if (ac != 2)
		return (return_error());
	canon_maker	make(av[2]);
	if (make.canon())
		return (return_error());
	return (0);
}

// la commande : c++ -Wall -Werror -Wextra main.cpp canon_maker.cpp
