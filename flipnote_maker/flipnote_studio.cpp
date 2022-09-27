#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>

int	return_error(void)
{
	std::cout << "Error" << std::endl;
	return (1);
}

int		valid_args(std::string const &file_name)
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

size_t	count_frame(std::string const &file)
{
	std::ifstream	ifs(file);
	std::string		line;
	size_t			nb_frame = 0;

	while (getline(ifs, line))
		if (line == "")
			nb_frame++;
	return (++nb_frame);
}

void	stock_frame(std::string const &file, size_t const &nb_frame)
{
	std::ifstream				ifs(file);

	for (size_t i = 0; i < nb_frame; i++)
	{
		std::string		line;
		std::ofstream	new_frame("frame_" + std::to_string(i + 1));
		while (getline(ifs, line))
		{
			if (line == "")
				break;
			new_frame << line << std::endl;
		}
	}
}

void	uninstall(size_t nb_frame)
{
	std::ofstream	script("uninstall.sh");
	script << "#!/bin/sh" << std::endl;
	for (size_t i = 0; i < nb_frame; i++)
		script << "rm frame_" + std::to_string(i + 1) << std::endl;
	script << "rm uninstall.sh" << std::endl;
	script.close();
}

void	print_flipnote(size_t nb_frame, int ac, char **av)
{
	size_t	i = 0;
	size_t	speed = 200000;
	if (ac == 3)
		speed = std::stoi(av[2]) * 100000;
	while (1)
	{
		std::string	cmd("clear && cat frame_" + std::to_string(i + 1));
		system(cmd.c_str());
		i++;
		i %= nb_frame;
		usleep(speed);
	}
}

int	main(int ac, char **av)
{
	if ((ac != 2 && ac != 3) || !valid_args(av[1]))
		return (return_error());

	std::string	file(av[1]);
	size_t	nb_frame = count_frame(file);

	stock_frame(file, nb_frame);
	uninstall(nb_frame);
	print_flipnote(nb_frame, ac, av);

	return (0);
}

//	clear && c++ flipnote_studio.cpp && ./a.out flipnote
