#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#define	STDIN  0
#define	STDOUT  1
#define	TRUE  1
#define	FALSE 0

int main(void)
{
    int pid;
    int p[2];
    int q[2];
    char c[80];
    int count = 0;
    FILE *fdopen(), *fp;
    pipe(p);
    pipe(q);

    switch(pid = fork())
    {

    case 0:  /*  ПОТОМОК  */
        close(p[STDOUT]);
        close(STDIN); dup(p[STDIN]); close(p[STDIN]);

        close(q[STDIN]);
        close(STDOUT); dup(q[STDOUT]); close(q[STDOUT]);
        execl("filter", "filter", 0);

    case -1: /* ОШИБКА в fork()  */
        printf("Ошибка при вызове fork() \n");
        exit(1);
    default:   /* РОДИТЕЛЬ   */
        close(p[STDIN]);close(q[STDOUT]);
        fp = fdopen(p[STDOUT], "w");
        gets(c);
        while (strncmp(c, "end", 80) != 0)
        {
            fprintf(fp, "%s\n", c);
            gets(c);

        }
        fprintf(fp, "%s\n", "end");
        fclose(fp);
        printf("%s\n", "Look at this:");

        close(STDIN); dup(q[STDIN]); close(q[STDIN]);

        int i = 0;
        gets(c);
        while (strncmp(c, "end", 80) != 0)
        {
            i++;
            printf("%d %s\n", i, c);
            gets(c);

        }

        exit(0);
    }
}
