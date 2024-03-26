/*#include <unistd.h>
#include <stdio.h>

char *convhexadd(void *address);
void format_hex_string(char *hexString);

void ft_print_memory(void *addr, unsigned int size)
{
    if (size != 0) {
        unsigned int i;

        i = 0;
        while (i < size) {
            void *add;

            char *hexString;

            add = &addr[i];
            hexString = convhexadd(add);
            write(1, hexString, 8);
            write(1, ": ", 2);
            format_hex_string(hexString);
            write(1, hexString, 18);
            write(1, "\n", 1);
            i++;
        }
    }
}

char *convhexadd(void *address)
{
    static char hexAddress[9];

    unsigned long addr = (unsigned long)address;

    int i = 7;

    while (i >= 0)
    {
        int digit = (addr >> (i * 4)) & 0xF;
        if (digit < 10)
            hexAddress[7 - i] = digit + '0';
        else
            hexAddress[7 - i] = digit - 10 + 'a';
        i--;
    }
    hexAddress[8] = '\0';
    return hexAddress;
}

void format_hex_string(char *hexString)
{
    char formattedHex[18];
    int i, j;
    for (i = 0, j = 0; i < 8; i++, j += 3)
    {
        formattedHex[j] = hexString[i];
        formattedHex[j + 1] = hexString[i + 1];
        formattedHex[j + 2] = ' ';
    }
    formattedHex[17] = '\0';
    snprintf(hexString, 18, "%s", formattedHex);
}

int main() {
    char data[] = "Angly regna";
    ft_print_memory(data, 11);
    return 0;
}
*/