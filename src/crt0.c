#include <glenda/glenda.h>
#include <glenda/ipc.h>
#include <glenda/protocol.h>
#include <glenda/cap/endpoint.h>
#include <glenda/sys.h>

extern char __bss_start[];
extern char __bss_end[];
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
    // 1. Clear BSS
    size_t bss_len = (size_t)__bss_end - (size_t)__bss_start;
    local_memset(__bss_start, 0, bss_len);

    // 2. Initialize process environment
    glenda_sys_init();

    // 3. Initialize console
    glenda_console_init(CAP_KERNEL);

    // 4. Call main
    int ret = main(0, NULL);

    // 5. Exit
    glenda_sys_exit(ret);
}
