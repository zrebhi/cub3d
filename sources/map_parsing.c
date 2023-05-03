# include "cub3d.h"

int	get_to_the_map(char *filename, int *fd)
{
	char	*str;

	*fd = open(filename, O_RDONLY);
	while (1)
	{
		str = get_next_line(*fd);
		if (!str)
			return (1);
		if (!ft_strncmp(str, "C", 1))
			break ;
	}
	while (1)
	{
		str = get_next_line(*fd);
		if (!str)
			return (1);
		if (ft_strcmp(str, "\n"))
			break ;
	}
	return (0);
}

void	get_map_height(t_map *data, char *filename, int *fd)
{
	char	*str;

	get_to_the_map(filename, fd);
	data->height = 0;
	data->width = 0;
	while (1)
	{
		str = get_next_line(*fd);
		if (!str || !ft_strcmp("\n", str))
			break ;
		data->height++;
		if ((int)ft_strlen(str) > data->width)
		{
			data->width = (int) ft_strlen(str);
		}
	}
	close(*fd);
}

void	parse_map(t_map *data, char *filename)
{
	int		i;
	int 	fd;

	get_map_height(data, filename, &fd);
	get_to_the_map(filename, &fd);
	data->map = ft_calloc(sizeof(char *), data->height + 1);
	if (!data->map)
		exit (1);
	i = -1;
	while (++i < data->height)
	{
		data->map[i] = get_next_line(fd);
		if (!data->map[i])
			exit(1);
	}
	data->map[i] = 0;
}

void	ft_data_init(t_map *data, char **argv)
{
	char	*filename;

	filename = argv[1];
	parse_map(data, filename);
}
