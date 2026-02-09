#include <glenda/glenda.h>
#include <glenda/ipc.h>
#include <glenda/protocol.h>
#include <glenda/cap/endpoint.h>
#include <glenda/sys.h>

extern int main(int argc, char **argv);

// Simple memset for BSS clearing
static void *local_memset(void *s, int c, size_t n)
{
    unsigned char *p = s;
    while (n--)
        *p++ = (unsigned char)c;
    return s;
}

void glenda_start(void)
{
    // 1. Initialize process environment
    int init_ret = glenda_sys_init();
    if (init_ret != 0)
        glenda_sys_exit(__UINT64_MAX__);

    // 2. Call main
    int ret = main(0, NULL);

    // 3. Exit
    glenda_sys_exit(ret);
}
