/*
** main.c for TcpSocket in /home/guilhem/Bureau/testUdp/C/
**
** Made by Guilhem Fulcrand
** Login   <guilhem.fulcrand@epitech.eu>
**
** Started on  Fri Sep 22 09:50:19 2017 Guilhem Fulcrand
** Last update Tue Oct 17 14:24:25 2017 Guilhem Fulcrand
*/

#include "include.h"

int         main(int ac, char **av)
{
    t_args  args;

    srand(time(NULL));
    parse_args(&args, ac, av);
    if (args.verbose)
        printf("Target : %s:%d\n", args.addr, args.port);
    if (args.server_mode)
        listener(&args);
    else if (args.client_mode)
        client_threading_loop(&args);
    return (EXIT_S);
}
