#define	STDIN  0
#define	STDOUT  1
#define	TRUE  1
#define	FALSE 0
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
int main(void)  /*  FILTER.C  */
{
    int count=0;
    char c[80];
    char* echo_f = "echo ";	      // Вызов echo
    char* sed_f = " | sed 'G;G'";    // Добавление пустых строк. КОНВЕЕР
    gets(c);
    while (strncmp(c, "end", 80) != 0)
    {
        char* buff = calloc(strlen(echo_f)+strlen(sed_f)+81, 1);
        strcat(buff, echo_f);
        strcat(buff, c);
        strcat(buff, sed_f);
        system(buff);
        free(buff);
        gets(c);
    }
    printf("%s\n", "end");
    exit(0);				// Завершение работы программы
}
