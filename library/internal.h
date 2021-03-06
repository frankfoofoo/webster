#ifndef WEBSTER_INTERNAL_HH
#define WEBSTER_INTERNAL_HH


#include "http.h"
#include <webster/api.h>


#if defined(_WIN32) || defined(WIN32)
#define WB_WINDOWS
#endif


#define WEBSTER_MAX_CONNECTIONS     1000
#define WEBSTER_MAX_HEADER          (1024 * 4) // 4KB
#define WEBSTER_READ_TIMEOUT        10000

#define WBMT_UNKNOWN    0x00
#define WBMT_REQUEST    0x01
#define WBMT_RESPONSE   0x02


struct webster_client_t_
{
	void *channel;
	char *host;
	int port;
    char *resource;
    uint32_t bufferSize;
};


struct webster_server_t_
{
    void *channel;
    char *host;
    int port;
    int maxClients;
    uint32_t bufferSize;
};


struct webster_message_t_
{
    int state;
    void *channel;

    /**
     * @brief Message type (WBMT_REQUEST or WBMT_RESPONSE).
     */
    int type;
    struct
    {
        /**
         * @brief Buffer capacity.
         */
        int size;

        /**
         * @brief Message expected size.
         *
         * This value is less than zero if using chunked transfer encoding.
         */
        int expected;
    } body;
    struct
    {
        uint8_t *data;
        int size;
        uint8_t *current;
        int pending;
    } buffer;
    webster_header_t header;
};


#endif // WEBSTER_INTERNAL_HH
