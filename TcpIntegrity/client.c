/*
** client.c for TcpSocket in /home/guilhem/Bureau/testTCP/
**
** Made by Guilhem Fulcrand
** Login   <guilhem.fulcrand@epitech.eu>
**
** Started on  Thu Oct 12 14:44:08 2017 Guilhem Fulcrand
** Last update Tue Oct 17 15:46:17 2017 Guilhem Fulcrand
*/

#include "include.h"

int     integrity = 0;

void                    *sender(void *args)
{
    struct sockaddr_in  addr;
    char                msg_to_send[BUFF_SIZE];
    char                msg_recv[BUFF_SIZE];
    int                 fd;
    int                 i;

    // Initialisation of buffers
    i = 0;
    while (i < BUFF_SIZE)
    {
        msg_to_send[i] = random() % 256;
        i++;
    }
    memset(msg_recv, 0, BUFF_SIZE);

    // Using a new socket for every packet sent
    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        fprintf(stderr, "Couldn't open socket\n");
        exit(1);
    }

    // Initialisation of target infos
    memset(&addr,0,sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(((t_args *)args)->addr);
    addr.sin_port = htons(((t_args *)args)->port);

    // Handling connection
    if (connect(fd, (struct sockaddr *) &addr, sizeof(addr)) < 0)
    {
        integrity++;
        close(fd);
        return (NULL);
    }

    // Sending packet
    if (send(fd, msg_to_send, BUFF_SIZE, 0) < 0)
    {
        fprintf(stderr, "send() failed \n");
        close(fd);
        exit(1);
    }

    // Receiving the echo of it
    if (recv(fd, msg_recv, BUFF_SIZE, 0) < 0)
    {
        fprintf(stderr, "Couldn't recv()\n%s\n", strerror(errno));
        close(fd);
        exit(1);
    }

    // Checking integrity
    if (memcmp(msg_to_send, msg_recv, BUFF_SIZE) != 0)
        integrity++;

    close(fd);
    return (NULL);
}

int     create_results()
{
    int results;

    if ((results = open("results_integrity.csv",  O_CREAT | O_WRONLY | O_TRUNC)) == -1)
    {
        fprintf(stderr, "Couldn't open\n%s\n", strerror(errno));
        exit(1);
    }
    return (results);
}

void    write_results(int results, int nb_slots_tested, int nb_clients_tested)
{
    dprintf(results, "%d,%d,", nb_slots_tested + 1, nb_clients_tested + 1);
    if (integrity)
        dprintf(results, "1\n");
    else
        dprintf(results, "0\n");
    integrity = 0;
}

void    write_progress(int nb_clients_tested)
{
    printf("%d%%                  \r", (nb_clients_tested * 100) / MAX_CLIENTS);
    fflush(stdout);
}

void            client_threading_loop(t_args *args)
{
    t_args      arg[args->slots];
    pthread_t   thread_id[MAX_THREADS];
    int         nb_slots_tested;
    int         num_slot;
    int         nb_clients_tested;
    int         num_client;
    int         results;

    // Opening results file
    results = create_results();

    // Copy args with different ports for threads targetting different slots
    num_slot = 0;
    while (num_slot < args->slots)
    {
        memcpy(&arg[num_slot], args, sizeof(t_args));
        arg[num_slot].port = args->port + num_slot;
        num_slot++;
    }

    // Launching nested loops from num_slot to nb_slots_tested and from num_client to nb_clients_tested
    nb_slots_tested = 0;
    while (nb_slots_tested < args->slots)
    {
        printf("Testing slot n°%d\n", nb_slots_tested + 1);
        nb_clients_tested = 0;
        while (nb_clients_tested < MAX_CLIENTS)
        {
            write_progress(nb_clients_tested);
            num_slot = 0;
            while (num_slot <= nb_slots_tested)
            {
                // Launching threads
                num_client = 0;
                while (num_client <= nb_clients_tested)
                {
                    if (pthread_create(&(thread_id[num_client]), NULL, sender, &arg[num_slot]) < 0 )
                    {
                        fprintf(stderr, "Couldn't create thread\n%s\n", strerror(errno));
                        exit(1);
                    }
                    num_client++;
                }

                // Joining threads
                num_client = 0;
                while (num_client < nb_clients_tested)
                {
                    if (pthread_join(thread_id[num_client], NULL) != 0)
                    {
                        fprintf(stderr, "Couldn't join thread\n%s\n", strerror(errno));
                        exit(1);
                    }
                    num_client++;
                }
                num_slot++;
            }
            // Waiting for kernel to release ports
            sleep(1);

            write_results(results, nb_slots_tested, nb_clients_tested);

            nb_clients_tested++;
        }
        nb_slots_tested++;
    }
    close(results);
}
