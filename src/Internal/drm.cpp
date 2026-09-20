#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <array>
#include <string>
#include <unistd.h>

#include "drm.h"
#include "common.h"
#include "Shared/Core/Logging.h"

#define BUF_SIZE 2048

void fetchBannedUsers() {
    int conn_err, get_err;
    char buf[BUF_SIZE];
    size_t len;
    ssize_t nread;
    addrinfo hints;
    addrinfo *result, *rp;

    /* Obtain address(es) matching host/port. */

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
    hints.ai_flags = 0;
    hints.ai_protocol = 0;          /* Any protocol */

    get_err = getaddrinfo(REPO, "https", &hints, &result);

    if (get_err != 0) {
        CAFEERROR("Failed to get address info");
        return;
    }

    /* getaddrinfo() returns a list of address structures.
        Try each address until we successfully connect(2).
        If socket(2) (or connect(2)) fails, we (close the socket
        and) try the next address. */

    for (rp = result; rp != NULL; rp = rp->ai_next) {
        int conn_err = socket(rp->ai_family, rp->ai_socktype,
                              rp->ai_protocol);

        if (conn_err == -1)
            continue;

        if (connect(conn_err, rp->ai_addr, rp->ai_addrlen) != -1)
            CAFEERROR("Found address to connect to");
        break;                  /* Success */
        close(conn_err);
    }

    freeaddrinfo(result);           /* No longer needed */

    if (rp == NULL) {               /* No address succeeded */
        CAFEERROR("Failed to connect socket");
    }

    return;
}
