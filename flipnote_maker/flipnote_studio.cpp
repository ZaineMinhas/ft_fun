#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>

int	return_error(void)
{
	std::cout << "Error" << std::endl;
	return (1);
}

int		valid_args(std::string file_name)
{
	if (file_name == "")
		return (0);
	std::ifstream	ifs(file_name);
	if (ifs.fail())
		return (0);
	std::string	first_line;
	getline(ifs, first_line);
	if (first_line == "")
		return (0);
	ifs.close();
	return (1);
}

size_t	count_frame(std::string file)
{
	std::ifstream	ifs(file);
	std::string		line;
	size_t			nb_frame = 0;

	while (getline(ifs, line))
	{
		std::cout << line << std::endl;
		if (line == "")
			nb_frame++;
	}
	return (++nb_frame);
}

void	uninstall(size_t nb_frame)
{
	std::ofstream	script("uninstall.sh");
	script << "#!/bin/sh" << std::endl;
	for (size_t i = 0; i < nb_frame; i++)
		script << "rm frame_" + std::to_string(i) << std::endl;
	script << "rm a.out" << std::endl;
	script << "rm uninstall.sh" << std::endl;
	script.close();
}

int	main(int ac, char **av)
{
	if ((ac != 2 && ac != 3) || !valid_args(av[1]))
		return (return_error());

	std::string	file(av[1]);
	size_t	nb_frame = count_frame(file);
	std::vector<std::ofstream*>	frame;

	for (size_t i = 0; i < nb_frame; i++)
		frame.push_back(new std::ofstream("frame_" + std::to_string(i)));
	

	std::cout << "nb frame = " << nb_frame << std::endl;

	// std::cout << file << std::endl;
	uninstall(nb_frame);
	return (0);
}

//	clear && c++ flipnote_studio.cpp && ./a.out flipnote
