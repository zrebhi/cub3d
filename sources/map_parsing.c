# include "../includes/cub3d.h"

int	get_to_the_map(char *cub_file)
{
	char	*str;
	int		fd;

	fd = open(cub_file, O_RDONLY);
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			return (1);
		if (!ft_strncmp(str, "C", 1))
			break ;
	}
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			return (1);
		if (ft_strcmp(str, "\n"))
			break ;
	}
	if (str)
		printf("%s", str);
	return (0);
}

int	main()
{
	get_to_the_map("maps/test.cub");
}