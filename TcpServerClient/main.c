/*
** main.c for TcpSocket in /home/guilhem/Bureau/testUdp/C/
**
** Made by Guilhem Fulcrand
** Login   <guilhem.fulcrand@epitech.eu>
**
** Started on  Fri Sep 22 09:50:19 2017 Guilhem Fulcrand
** Last update Thu Oct 12 17:11:23 2017 Guilhem Fulcrand
*/

#include "include.h"

int         main(int ac, char **av)
{
    t_info  info;

    parse_args(&info, ac, av);
    printf("target: %s:%i\n", info.addr, info.port);
    if (info.server_mode)
        listener(&info);
    else if (info.client_mode)
        sender(&info);
    return (EXIT_S);
}
