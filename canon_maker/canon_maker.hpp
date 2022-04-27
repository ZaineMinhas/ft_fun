/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canon_maker.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zminhas <zminhas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 17:43:16 by zminhas           #+#    #+#             */
/*   Updated: 2022/04/27 18:13:59 by zminhas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CANON_MAKER
# define CANON_MAKER

# include <iostream>
# include <fstream>

std::string	upper_string(std::string str);

class canon_maker
{
private:
	const std::string	_name;

	void	creat_hpp(std::string name) const;
	void	creat_cpp(std::string name) const;

public:
	canon_maker();
	canon_maker(const std::string _name);
	~canon_maker();

	int	canon(void);
};

#endif