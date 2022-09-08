#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverse(char *str)
{
    char *p0 = str;
    char *p1 = str + strlen(str) - 1;
    char ch = 0;
    printf("p0(%p) p1(%p), (%d)\r\n", p0, p1, (int)(p1 - p0));

    int i = 0;
    while (p0 != p1)
    {
        printf("%d ", i++);
        if (i % 16 == 0)
            printf("\r\n");
        ch = *p1;
        *p1 = *p0;
        *p0 = ch;
        p0++;
        if (p0 == p1)
            break;
        p1--;
    }
    printf("\r\n");
}

void skip_space_reverse(char *str)
{
    char *start = str;
    while (*str)
    {
        if (*str != ' ')
        {
            str++;
        }
        else
        {
            *str = '\0';
            reverse(start);
            *str = ' ';
            while (*str == ' ')
                str++;
            start = str;
        }
    }
    if (*str == '\0' && str > start)
    {
        reverse(start);
    }
}

int main(void)
{
    const char *a = "world health organization!";
    char *str = (char *)calloc(strlen(a) + 1, 1);
    memcpy(str, a, strlen(a));
    reverse(str);
    skip_space_reverse(str);
    printf("%s\r\n", str);
}