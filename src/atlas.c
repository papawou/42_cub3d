#include "cub3D.h"

void clean_atlas(t_mlx mlx, t_atlas *atlas)
{
	ftmlx_free_img(mlx, atlas->text_ea);
	atlas->text_ea = NULL;
	ftmlx_free_img(mlx, atlas->text_no);
	atlas->text_no = NULL;
	ftmlx_free_img(mlx, atlas->text_so);
	atlas->text_so = NULL;
	ftmlx_free_img(mlx, atlas->text_we);
	atlas->text_we = NULL;
}
