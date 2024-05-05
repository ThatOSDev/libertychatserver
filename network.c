
#include <winsock2.h>
#include <ws2tcpip.h>

#define ISVALIDSOCKET(s) ((s) != INVALID_SOCKET)
#define CLOSESOCKET(s) closesocket(s)
#define GETSOCKETERRNO() (WSAGetLastError())

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "network.h"

#include <iphlpapi.h>

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))

#include "stringmanager.h"

WSAEVENT       NewEvent;
SOCKET         socket_listen;
fd_set         master;
SOCKET         max_socket;
struct timeval timeout;

/* Variables used by GetIpAddrTable */
DWORD dwSize = 0;
DWORD dwRetVal = 0;
IN_ADDR IPAddress;

/* Variables used to return error message */
LPVOID lpMsgBuf;
PMIB_IPADDRTABLE pIPAddrTable;

void that_updateIPTable()
{
    // Before calling AddIPAddress we use GetIpAddrTable to get
    // an adapter to which we can add the IP.
    pIPAddrTable = (MIB_IPADDRTABLE *) MALLOC(sizeof (MIB_IPADDRTABLE));

    if (pIPAddrTable)
    {
        // Make an initial call to GetIpAddrTable to get the
        // necessary size into the dwSize variable
        if (GetIpAddrTable(pIPAddrTable, &dwSize, 0) == ERROR_INSUFFICIENT_BUFFER)
        {
            FREE(pIPAddrTable);
            pIPAddrTable = (MIB_IPADDRTABLE *) MALLOC(dwSize);
        }
        if (pIPAddrTable == NULL)
        {
            printf("Memory allocation failed for GetIpAddrTable\n");
            exit(1);
        }
    }
    // Make a second call to GetIpAddrTable to get the
    // actual data we want
    if ( (dwRetVal = GetIpAddrTable( pIPAddrTable, &dwSize, 0 )) != NO_ERROR )
    {
        printf("GetIpAddrTable failed with error %lu\n", dwRetVal);
        if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
                          FORMAT_MESSAGE_IGNORE_INSERTS, NULL, dwRetVal,
                           MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),       // Default language
                          (LPTSTR) & lpMsgBuf, 0, NULL))
        {
            printf("\tError: %s", (char*)lpMsgBuf);
            LocalFree(lpMsgBuf);
        }
        exit(1);
    }
}

void that_listIPAddresses()
{
    that_updateIPTable();
    printf("\tNum Entries: %ld\n", pIPAddrTable->dwNumEntries);
    for (int i = 0; i < (int)pIPAddrTable->dwNumEntries; i++)
    {
        printf("\n\tInterface Index[%d]:\t%ld\n", i, pIPAddrTable->table[i].dwIndex);
        IPAddress.S_un.S_addr = (u_long) pIPAddrTable->table[i].dwAddr;
        printf("\tIP Address[%d]:     \t%s\n", i, inet_ntoa(IPAddress) );
        IPAddress.S_un.S_addr = (u_long) pIPAddrTable->table[i].dwMask;
        printf("\tSubnet Mask[%d]:    \t%s\n", i, inet_ntoa(IPAddress) );
        IPAddress.S_un.S_addr = (u_long) pIPAddrTable->table[i].dwBCastAddr;
        printf("\tBroadCast[%d]:      \t%s (%ld)\n", i, inet_ntoa(IPAddress), pIPAddrTable->table[i].dwBCastAddr);
        printf("\tReassembly size[%d]:\t%ld\n", i, pIPAddrTable->table[i].dwReasmSize);
        printf("\tType and State[%d]:", i);
        if (pIPAddrTable->table[i].wType & MIB_IPADDR_PRIMARY)
            printf("\tPrimary IP Address");
        if (pIPAddrTable->table[i].wType & MIB_IPADDR_DYNAMIC)
            printf("\tDynamic IP Address");
        if (pIPAddrTable->table[i].wType & MIB_IPADDR_DISCONNECTED)
            printf("\tAddress is on disconnected interface");
        if (pIPAddrTable->table[i].wType & MIB_IPADDR_DELETED)
            printf("\tAddress is being deleted");
        if (pIPAddrTable->table[i].wType & MIB_IPADDR_TRANSIENT)
            printf("\tTransient address");
        printf("\n");
    }

    if (pIPAddrTable) {
        FREE(pIPAddrTable);
        pIPAddrTable = NULL;
    }
}

void that_initNetwork()
{
    that_checkSettings("LIBERTY SERVER");
    WSADATA d;
    if (WSAStartup(MAKEWORD(2, 2), &d))
    {
        that_addString("Failed to initialize Network Adapter.");
    }

    that_addString("Configuring local address...");

    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    struct addrinfo *bind_address;
    getaddrinfo(0, "8080", &hints, &bind_address);

    that_addString("Creating socket...");
    socket_listen = socket(bind_address->ai_family, bind_address->ai_socktype, bind_address->ai_protocol);
    if (!ISVALIDSOCKET(socket_listen))
    {
        that_addString("Socket() failed.");
    }

   unsigned long int on = 1;
   int result = ioctlsocket(socket_listen, FIONBIO, &on);
   if (result < 0)
   {
       that_addString("ioctlsocket() failed.");
   }

    that_addString("Binding socket to local address...");
    if (bind(socket_listen, bind_address->ai_addr, bind_address->ai_addrlen))
    {
        that_addString("Bind() failed.");
    }
    freeaddrinfo(bind_address);

    NewEvent = WSACreateEvent();
    that_addString("Event Created...");

    WSAEventSelect( socket_listen, NewEvent, FD_ACCEPT | FD_CLOSE);

    that_addString("Listening...");
    if (listen(socket_listen, 10) < 0)
    {
        that_addString("Listen() failed.");
    }

    FD_ZERO(&master);
    FD_SET(socket_listen, &master);
    max_socket = socket_listen;

    that_addString("Waiting for connections...");

    timeout.tv_sec  = 0;
    timeout.tv_usec = 1;
}

void that_checkNetwork()
{
    fd_set reads;
    reads = master;
    if (select(max_socket+1, &reads, 0, 0, &timeout) < 0)
    {
        that_addString("Select() failed.");
    }

    SOCKET i;
    for(i = 1; i <= max_socket; ++i)
    {
        if (FD_ISSET(i, &reads))
        {
            if (i == socket_listen)
            {
                struct sockaddr_storage client_address;
                socklen_t client_len = sizeof(client_address);
                SOCKET socket_client = accept(socket_listen, (struct sockaddr*) &client_address, &client_len);
                if (!ISVALIDSOCKET(socket_client))
                {
                    that_addString("Accept() failed.");
                }

                FD_SET(socket_client, &master);
                if (socket_client > max_socket)
                    max_socket = socket_client;

                char address_buffer[100];
                getnameinfo((struct sockaddr*)&client_address, client_len, address_buffer, sizeof(address_buffer), 0, 0, NI_NUMERICHOST);

                that_addString("New connection from : %s", address_buffer);
            } else {
                char read[1024];
                int bytes_received = recv(i, read, 1024, 0);
                if (bytes_received < 1)
                {
                    FD_CLR(i, &master);
                    CLOSESOCKET(i);
                    continue;
                }

                SOCKET j;
                for (j = 1; j <= max_socket; ++j)
                {
                    if (FD_ISSET(j, &master))
                    {
                        if (j == socket_listen || j == i)
                            continue;
                        else
                            send(j, read, bytes_received, 0);
                    }
                }
            }
        }
    }
}

void that_networkCleanup()
{
    that_addString("Closing event...");
    WSACloseEvent(NewEvent);

    that_addString("Closing listening socket...");
    CLOSESOCKET(socket_listen);

    WSACleanup();
    that_addString("Network Cleanup - Finished.");
    //that_printAllStrings();
}


/*
char * inet_ntoa(in_addr in);


// IP4
struct in_addr {  // IN_ADDR
  union {
    struct {
      u_char s_b1;
      u_char s_b2;
      u_char s_b3;
      u_char s_b4;
    } S_un_b;
    struct {
      u_short s_w1;
      u_short s_w2;
    } S_un_w;
    u_long S_addr;
  } S_un;
};

// IP6
typedef struct in6_addr {
  union {
    u_char  Byte[16];
    u_short Word[8];
  } u;
} IN6_ADDR, *PIN6_ADDR, FAR *LPIN6_ADDR;


typedef struct _MIB_IPADDRROW_W2K {
  DWORD          dwAddr;
  DWORD          dwIndex;
  DWORD          dwMask;
  DWORD          dwBCastAddr;
  DWORD          dwReasmSize;
  unsigned short unused1;
  unsigned short unused2;
} MIB_IPADDRROW_W2K, *PMIB_IPADDRROW_W2K;

typedef struct _MIB_IPADDRTABLE {
  DWORD         dwNumEntries;
  MIB_IPADDRROW table[ANY_SIZE];
} MIB_IPADDRTABLE, *PMIB_IPADDRTABLE;

IPHLPAPI_DLL_LINKAGE DWORD GetIpAddrTable(
  [out]     PMIB_IPADDRTABLE pIpAddrTable,
  [in, out] PULONG           pdwSize,
  [in]      BOOL             bOrder
);

typedef struct _WSAPROTOCOLCHAIN {
  int   ChainLen;
  DWORD ChainEntries[MAX_PROTOCOL_CHAIN];
} WSAPROTOCOLCHAIN, *LPWSAPROTOCOLCHAIN;

typedef struct _WSAPROTOCOL_INFOA {
  DWORD            dwServiceFlags1;
  DWORD            dwServiceFlags2;
  DWORD            dwServiceFlags3;
  DWORD            dwServiceFlags4;
  DWORD            dwProviderFlags;
  GUID             ProviderId;
  DWORD            dwCatalogEntryId;
  WSAPROTOCOLCHAIN ProtocolChain;
  int              iVersion;
  int              iAddressFamily;
  int              iMaxSockAddr;
  int              iMinSockAddr;
  int              iSocketType;
  int              iProtocol;
  int              iProtocolMaxOffset;
  int              iNetworkByteOrder;
  int              iSecurityScheme;
  DWORD            dwMessageSize;
  DWORD            dwProviderReserved;
  CHAR             szProtocol[WSAPROTOCOL_LEN + 1];
} WSAPROTOCOL_INFOA, *LPWSAPROTOCOL_INFOA;


INT WSAAPI WSAAddressToStringA(
  [in]           LPSOCKADDR          lpsaAddress,
  [in]           DWORD               dwAddressLength,
  [in, optional] LPWSAPROTOCOL_INFOA lpProtocolInfo,
  [in, out]      LPSTR               lpszAddressString,
  [in, out]      LPDWORD             lpdwAddressStringLength
);
*/
