int	controller(int char_p, t_master *master)
{
	if (char_p == W_KEY)
		; //su
	else if (char_p == S_KEY)
		; //giu
	else if (char_p == A_KEY)
		; //sinistra
	else if (char_p == D_KEY)
		; //destra
	else if (char_p == LEFT_KEY)
		; //sinistra visuale
	else if (char_p == RIGHT_KEY)
		; //destra visuale
	else if (char_p == ESC_KEY)
		close_game(master);
	return (1);
}
