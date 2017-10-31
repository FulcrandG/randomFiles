/*
** UdpMulticastSocket.c for UdpMulticast in /home/guilhem/Bureau/testUdp/C/
**
** Made by Guilhem Fulcrand
** Login   <guilhem.fulcrand@epitech.eu>
**
** Started on  Fri Sep 22 09:50:19 2017 Guilhem Fulcrand
** Last update Fri Sep 22 16:34:53 2017 Guilhem Fulcrand
*/

#include "include.h"

int         main(int ac, char **av)
{
    t_info  info;

    parse_args(&info, ac, av);
    printf("multi: %s\nport: %i\n", info.mul_addr, info.port);
    if (info.server_mode)
        listener(&info);
    else if (info.client_mode)
        sender(&info);
    return (EXIT_S);
}
