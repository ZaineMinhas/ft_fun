/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zminhas <zminhas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 17:48:23 by zminhas           #+#    #+#             */
/*   Updated: 2022/04/30 16:24:14 by zminhas          ###   ########.fr       */
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
	if (ac != 3)
		return (return_error());
	canon_maker	make(av[2]);
	if (make.canon())
		return (return_error());
	std::string	hpp = "mv " + (std::string)av[2] + ".hpp " + av[1];
	std::string	cpp = "mv " + (std::string)av[2] + ".cpp " + av[1];
	system(hpp.c_str());
	system(cpp.c_str());
	return (0);
}

// la commande : c++ -Wall -Werror -Wextra main.cpp canon_maker.cpp
