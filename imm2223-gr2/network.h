/**
* \file network.h
* \brief Gestion du reseau par socket client et serveur
* \author Andoni Iparraguirre
* \version 0.1
*/

#ifndef ABALONE_NETWORK
#define ABALONE_NETWORK

#ifdef __WIN32__
#include <winsock2.h>
#include <ws2tcpip.h>
#include <ws2spi.h>
#else
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h> 
#include <netinet/in.h>
#endif

#include <sys/types.h>
#include <errno.h>

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * /definition d'alias pour les sockets
 */
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

/**
 * \brief definition de variable pour socket invalide
 */
#define INVALID_SOCKET -1

/**
 * \brief definition de variable pour erreur sur socket
 */
#define SOCKET_ERROR -1


/**
 * \fn TCP_Create_Client(char* severName,short service)
 * \brief Créé une socket en tcp, lié a un serveur par un port, tout deux passé en paramètre 
 * \param string addresse IP du serveur à joindre
 * \param entier port utilisé en entrée
 * \return une socket à utilisé pour un client
 */
SOCKET TCP_Create_Client(char* severName,short service);

/**
 * \fn TCP_Create_Server(short service)
 * \brief Crée un socket en tcp, se mettant en écoute sur n'importe quelle addresse IP entrante et sur le port indiqué
 * \param entier port d'écoute 
 * \return une socket utilisable pour une ecoute serveur
 */
SOCKET TCP_Create_Server(short service);



#endif //ABALONE_NETWORK