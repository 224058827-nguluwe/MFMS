#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "common.h"

/* Read one line safely; exits cleanly on end-of-input. */
void readLine(const char *prompt, char *buf, int size)
{
    printf("%s", prompt);
    if (fgets(buf, size, stdin) == NULL) {
        printf("\nInput closed. Exiting.\n");
        exit(0);
    }
    if (strchr(buf, '\n') == NULL) {          /* line too long: discard rest */
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
    }
    buf[strcspn(buf, "\n")] = '\0';

    /* trim trailing spaces */
    int n = (int)strlen(buf);
    while (n > 0 && isspace((unsigned char)buf[n - 1])) buf[--n] = '\0';
    /* trim leading spaces */
    int start = 0;
    while (buf[start] != '\0' && isspace((unsigned char)buf[start])) start++;
    if (start > 0) memmove(buf, buf + start, strlen(buf + start) + 1);
}

/* Keep asking until the user types something non-empty. */
void readNonEmpty(const char *prompt, char *buf, int size)
{
    do {
        readLine(prompt, buf, size);
        if (strlen(buf) == 0)
            printf("  [!] This field cannot be empty.\n");
    } while (strlen(buf) == 0);
}

/* Integer within [min, max]. */
int readInt(const char *prompt, int min, int max)
{
    char line[64], *end;
    long v;
    for (;;) {
        readLine(prompt, line, sizeof line);
        if (strlen(line) == 0) { printf("  [!] Please enter a number.\n"); continue; }
        v = strtol(line, &end, 10);
        if (*end != '\0')       { printf("  [!] '%s' is not a valid whole number.\n", line); continue; }
        if (v < min || v > max) { printf("  [!] Enter a value between %d and %d.\n", min, max); continue; }
        return (int)v;
    }
}

/* Non-negative amount of money. */
double readMoney(const char *prompt)
{
    char line[64], *end;
    double v;
    for (;;) {
        readLine(prompt, line, sizeof line);
        if (strlen(line) == 0) { printf("  [!] Please enter an amount.\n"); continue; }
        v = strtod(line, &end);
        if (*end != '\0' || !isfinite(v)) { printf("  [!] '%s' is not a valid amount.\n", line); continue; }
        if (v < 0)               { printf("  [!] Amount cannot be negative.\n"); continue; }
        if (v > 1000000000.0)    { printf("  [!] Amount is unrealistically large.\n"); continue; }
        return v;
    }
}

void toLowerStr(const char *src, char *dst, int size)
{
    int i;
    for (i = 0; src[i] != '\0' && i < size - 1; i++)
        dst[i] = (char)tolower((unsigned char)src[i]);
    dst[i] = '\0';
}

int equalsIgnoreCase(const char *a, const char *b)
{
    char la[128], lb[128];
    toLowerStr(a, la, sizeof la);
    toLowerStr(b, lb, sizeof lb);
    return strcmp(la, lb) == 0;
}

int containsIgnoreCase(const char *text, const char *needle)
{
    char lt[128], ln[128];
    toLowerStr(text, lt, sizeof lt);
    toLowerStr(needle, ln, sizeof ln);
    return strstr(lt, ln) != NULL;
}

void printLine(char c, int n)
{
    int i;
    for (i = 0; i < n; i++) putchar(c);
    putchar('\n');
}

void pauseScreen(void)
{
    char tmp[8];
    readLine("\nPress Enter to continue...", tmp, sizeof tmp);
}
