#include <zephyr/kernel.h>

void board_early_init_hook(void)
{
    printk("Board initialized\n");
}
