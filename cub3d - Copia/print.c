#include "cub3d.h"

static int	ri(t_master *m)
{
	if (ft_mlen(m->map) => MD)
		return ((int)(m->yp) - MD);
	else
		return (0);
}

static int	rb(t_master *m, int i)
{
	if (ft_strlen(m->map[i]) => MD)
		return ((int)(m->xp) - MD);
	else
		return (0);
}

static void	finalc(int i, int b)
{
	int 	i2;

	i2 = 0;
	while (i2 != i)
	{
		mlx_put_image_to_window(m->mlx, m->win, m->mc, i2 * MG, b * MG);
		i2++;
	}
}

void	print_map(char **map, t_master *m)
{
	int		i;
	int		b;

	i = ri(m);
	mlx_clear_window(m->mlx, m->win);
	while (map[i] != NULL && (int)(m->yp) + MD != i)
	{
		b = rb(m, i);
		while (map[i][b] != '\0' && (int)(m->xp) + MD != b)
		{
			if (map[i][b] == '1')
				mlx_put_image_to_window(m->mlx, m->win, m->mwall,
					(b - rb(m)) * MG, (i - ri(m)) * MG);
			if (map[i][b] == '0')
				mlx_put_image_to_window(m->mlx, m->win, m->mfloor,
					(b - rb(m)) * MG, (i - ri(m)) * MG);
            b++;
		}
		mlx_put_image_to_window(m->mlx, m->win, m->mc, i * MG, (b + 1) * MG);
        i++;
	}
	finalc(i - ri(m), b - rb(m, i));
	mlx_put_image_to_window(m->mlx, m->win, m->mplayer, m->yp * MG, m->xp * MG);
}
