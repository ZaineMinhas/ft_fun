/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canon_maker.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zminhas <zminhas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 17:47:30 by zminhas           #+#    #+#             */
/*   Updated: 2022/04/27 18:46:46 by zminhas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "canon_maker.hpp"

canon_maker::canon_maker() {}

canon_maker::canon_maker(std::string name) : _name(name) {}

canon_maker::~canon_maker() {}

void	canon_maker::creat_hpp(const std::string name) const
{
	std::ofstream   hpp(name + ".hpp");
	hpp << "#ifndef " << upper_string(name) << "_HPP" << std::endl;
	hpp << "# define " << upper_string(name) << "_HPP" << std::endl << std::endl;
	hpp << "# include <iostream>" << std::endl << std::endl;
	hpp << "class " << name << std::endl << "{" << std::endl;;
	hpp << "private:" << std::endl << "	" << std::endl;
	hpp << "public:" << std::endl;
	hpp << "	" << name << "(void);" << std::endl;
	hpp << "	" << name << "(const " << name << " &src);" << std::endl;
	hpp << "	~" << name << "(void);" << std::endl << std::endl;
	hpp << "	" << name << "	&operator=(const " << name << " &rhs);" << std::endl << std::endl;
	hpp << "};" << std::endl << std::endl;
	hpp << "#endif" << std::endl;
	hpp.close();
}

void	canon_maker::creat_cpp(std::string name) const
{
	std::ofstream   cpp(name + ".cpp");
	cpp << "#include \"" << name << ".hpp\"" << std::endl << std::endl;
	cpp << name << "::" << name << "() {}" << std::endl << std::endl;
	cpp << name << "::" << name << "(const " << name << " &src) {" << std::endl;
	cpp << "	*this = src;" << std::endl << "}" << std::endl << std::endl;
	cpp << name << "::~" << name << "() {}" << std::endl << std::endl;
	cpp << name << "	&" << name << "::operator=(const " << name << " &rhs) {" << std::endl;
	cpp << "	" << std::endl << "	return (*this);" << std::endl << "}" << std::endl;
	cpp.close();
}

int	canon_maker::canon(void)
{
	if (this->_name == "")
		return (1);
	this->creat_hpp(this->_name);
	this->creat_cpp(this->_name);
	return (0);
}
