# include "../includes/cub3d.h"


int	get_to_the_map(t_cub *data)
{
	char	*str;

	data->fd = open(data->file, O_RDONLY);
	while (1)
	{
		str = get_next_line(data->fd);
		if (!str)
			return (1);
		if (!ft_strncmp(str, "C", 1))
			break ;
	}
	while (1)
	{
		str = get_next_line(data->fd);
		if (!str)
			return (1);
		if (ft_strcmp(str, "\n"))
			break ;
	}
	return (0);
}

void	get_map_height(t_cub *data)
{
	char	*str;

	get_to_the_map(data);
	data->map_height = 0;
	while (1)
	{
		str = get_next_line(data->fd);
		if (!str || !ft_strcmp("\n", str))
			break ;
		data->map_height++;
	}
	close(data->fd);
}

void	parse_map(t_cub *data)
{
	int		i;

	get_map_height(data);
	get_to_the_map(data);
	data->map = ft_calloc(sizeof(char *), data->map_height);
	if (!data->map)
		exit (1);
	i = -1;
	while (++i < data->map_height)
	{
		data->map[i] = get_next_line(data->fd);
		if (!data->map[i])
			exit(1);
	}
	data->map[i] = 0;
}

void	ft_data_init(t_cub *data, char **argv)
{
	data->file = argv[1];
	parse_map(data);
}

int	main(int argc, char **argv)
{
	t_cub	data;
	int		i;

	i = -1;
	if (argc != 2)
		return (ft_putstr_fd("Invalid number of arguments.\n", 2), 1);
	ft_data_init(&data, argv);
	while(data.map[++i])
		printf("%3s", data.map[i]);
}