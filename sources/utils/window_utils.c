#include "window_utils.h"

void	put_pxl_img(t_data *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

static int	fill_window(t_window *window, t_cub *cub)
{
	int			x;
	int			y;
	t_data		img;

	img = window->img;
	x = 0;
	while (x < W_WIDTH)
	{
		y = 0;
		while (y < W_HEIGHT)
		{
			if (cub->map[x / W_WIDTH * cub->map_width]\
				[y / W_HEIGHT * cub->map_height] == '0')
				put_pxl_img(&img, x, y, 16843008);
			else
				put_pxl_img(&img, x, y, 0);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(window->mlx_ptr, window->win_ptr, \
		&(window->img), 0, 0);
	return (1);
}

void	init_img(t_window *window)
{
	window->img.img = mlx_new_image(window->mlx_ptr, W_WIDTH, W_HEIGHT);
	window->img.addr = mlx_get_data_addr(window->img.img, \
		&window->img.bpp, &window->img.line_length, \
		&window->img.endian);
}

int	create_window(t_cub *cub)
{
	t_window	window;

	window.cub_ptr = cub;
	window.mlx_ptr = mlx_init();
	window.win_ptr = mlx_new_window(window.mlx_ptr, W_WIDTH, W_HEIGHT, TITLE);
	init_img(&window);
	fill_window(&window, cub);
//	mlx_mouse_hook(window.win_ptr, mouse_handler, &window);
//	mlx_do_key_autorepeaton(window.mlx_ptr);
//	mlx_hook(window.win_ptr, 02, 1L << 1, key_handler, &window);
//	mlx_hook(window.win_ptr, 17, 1L << 2, exit_window, &window);
	mlx_put_image_to_window(window.mlx_ptr, window.win_ptr, \
		window.img.img, 0, 0);
	mlx_loop(window.mlx_ptr);
	return (1);
}