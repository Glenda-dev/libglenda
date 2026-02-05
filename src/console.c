#include <glenda/console.h>
#include <glenda/cap/kernel.h>
#include <glenda/cap/endpoint.h>
#include <glenda/utils.h>

static glenda_cap_ptr_t global_kernel_cap = 0;

void glenda_console_init(glenda_cap_ptr_t kernel_cap)
{
    global_kernel_cap = kernel_cap;
}

void glenda_puts(const char *s)
{
    glenda_kernel_console_put_str(global_kernel_cap, s);
}

char glenda_getchar(void)
{
    char c = 0;
    while (glenda_kernel_console_get_char(global_kernel_cap, &c) != GLENDA_SUCCESS)
        ;
    return c;
}

char *glenda_gets(char *s, int size)
{
    if (size <= 0 || !s)
        return NULL;

    // Use kernel console input capability
    size_t len = 0;
    glenda_error_t err = glenda_kernel_console_get_str(global_kernel_cap, s, size, &len);

    if (err != GLENDA_SUCCESS || len == 0)
    {
        return NULL; // Error or empty input
    }

    // Ensure null termination (already handled by get_str, but safe to check)
    if (len < (size_t)size)
    {
        s[len] = '\0';
    }
    else
    {
        s[size - 1] = '\0';
    }

    return s;
}
