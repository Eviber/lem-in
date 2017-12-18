#include "cookielem-in.h"

int main(int argc, char **argv){
	t_map map;
	(void)argc;
	(void)argv;

	if ((ft_memset(&map, 0, sizeof(t_map))) == NULL)
		{
			ft_putendl("erreur à l'allocation mem\n");
			exit(-1);
		}


	parser(&map);//attention parse stdin

	//ecrire fonction qui lis fichier parse et si ok : Print OK
//	resolver();
//	display();

	return(0);
}
