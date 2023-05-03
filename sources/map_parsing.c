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

void	get_map_height(t_cub *data, char *filename, int *fd)
{
	char	*str;

	get_to_the_map(filename, fd);
	data->m_height = 0;
	data->m_mwidth = 0;
	while (1)
	{
		str = get_next_line(*fd);
		if (!str || !ft_strcmp("\n", str))
			break ;
		data->m_height++;
		if ((int)ft_strlen(str) > data->m_mwidth)
		{
			data->m_mwidth = (int) ft_strlen(str);
		}
	}
	close(*fd);
}

void	parse_map(t_cub *data, char *filename)
{
	int		i;
	int 	fd;

	get_map_height(data, filename, &fd);
	get_to_the_map(filename, &fd);
	data->map = ft_calloc(sizeof(char *), data->m_height + 1);
	if (!data->map)
		exit (1);
	i = -1;
	while (++i < data->m_height)
	{
		data->map[i] = get_next_line(fd);
		if (!data->map[i])
			exit(1);
	}
	data->map[i] = 0;
}

void	ft_data_init(t_cub *data, char **argv)
{
	char	*filename;

	filename = argv[1];
	parse_map(data, filename);
}

int	main(int argc, char **argv)
{
	t_cub	data;
	int		i;

	i = -1;
	if (argc != 2)
		return (ft_putstr_fd("Invalid number of arguments.\n", 2), 1);
	ft_data_init(&data, argv);
	printf("\nheight: %d\nmax width: %d\n", data.m_height, data.m_mwidth);
	while(data.map[++i])
		printf("%s", data.map[i]);
	create_window(&data);
}