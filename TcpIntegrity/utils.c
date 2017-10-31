/*
** utils.c for TcpSocket in /home/guilhem/Bureau/testUdp/C/
**
** Made by Guilhem Fulcrand
** Login   <guilhem.fulcrand@epitech.eu>
**
** Started on  Fri Sep 22 16:28:59 2017 Guilhem Fulcrand
** Last update Tue Oct 17 10:26:08 2017 Guilhem Fulcrand
*/

#include "include.h"

void    help()
{
    fprintf(stderr, "USAGE:\n");
    fprintf(stderr, "\t-l : listener mode\n");
    fprintf(stderr, "\t-c : client mode\n");
    fprintf(stderr, "\t-m : address (default: localhost)\n");
    fprintf(stderr, "\t-p : port (default: 1230)\n");
    fprintf(stderr, "\t-s : number of slots (default: 8)\n");
    fprintf(stderr, "\t-v : verbose mode on (default off)\n");
    exit(1);
}

void    parse_args(t_args *args, int ac, char **av)
{
    int opt;

    args->addr = DEFAULT_ADDR;
    args->port = DEFAULT_PORT;
    args->client_mode = 0;
    args->server_mode = 0;
    args->verbose = 0;
    args->slots = MAX_SLOTS;
    while ((opt = getopt(ac, av, "a:m:p:t:s:clv")) != -1)
    {
        switch (opt)
        {
            case 'm':
                args->addr = optarg;
                break;
            case 'p':
                args->port = atoi(optarg);
                break;
            case 'c':
                args->client_mode++;
                break;
            case 'l':
                args->server_mode++;
                break;
            case 's':
                args->slots = atoi(optarg);
                break;
            case 'v':
                args->verbose++;
                break;
            case '?':
                if (optopt == 'm' || optopt == 'p' || optopt == 't' || optopt == 's')
                    fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                help();
        }
    }
    if (args->client_mode && args->server_mode)
    {
        fprintf(stderr, "Options -c and -l can't be active at the same time\n");
        help();
    }
    if (!args->client_mode && !args->server_mode)
    {
        fprintf(stderr, "Options -c or -l needed\n");
        help();
    }
}
