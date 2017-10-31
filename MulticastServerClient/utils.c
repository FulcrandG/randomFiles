/*
** utils.c for UdpMulticastSocket in /home/guilhem/Bureau/testUdp/C/
**
** Made by Guilhem Fulcrand
** Login   <guilhem.fulcrand@epitech.eu>
**
** Started on  Fri Sep 22 16:28:59 2017 Guilhem Fulcrand
** Last update Fri Oct 13 12:06:20 2017 Guilhem Fulcrand
*/

#include "include.h"

void    help()
{
    fprintf(stderr, "USAGE:\n");
    fprintf(stderr, "\t-m : adresse multicast\n");
    fprintf(stderr, "\t-p : port source\n");
    exit(1);
}

void    parse_args(t_info *info, int ac, char **av)
{
    int opt;

    info->mul_addr = DEFAULT_MUL_ADDR;
    info->port = DEFAULT_PORT;
    info->client_mode = 0;
    info->server_mode = 0;
    while ((opt = getopt(ac, av, "a:m:p:t:cs")) != -1)
    {
        switch (opt)
        {
            case 'm':
                info->mul_addr = optarg;
                break;
            case 'p':
                info->port = atoi(optarg);
                break;
            case 'c':
                info->client_mode = 1;
                break;
            case 's':
                info->server_mode = 1;
                break;
            case '?':
                if (optopt == 'm' || optopt == 'p' || optopt == 't')
                    fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                help();
        }
    }
    if (info->client_mode && info->server_mode)
    {
        fprintf(stderr, "Options -c and -s can't be active at the same time\n");
        help();
    }
    if (!info->client_mode && !info->server_mode)
    {
        fprintf(stderr, "Options -c or -s needed\n");
        help();
    }
}
