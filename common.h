#ifndef COMMON_H
#define COMMON_H

#define ID_LEN   12
#define NAME_LEN 50
#define TEXT_LEN 40

void   readLine(const char *prompt, char *buf, int size);
void   readNonEmpty(const char *prompt, char *buf, int size);
int    readInt(const char *prompt, int min, int max);
double readMoney(const char *prompt);
void   toLowerStr(const char *src, char *dst, int size);
int    equalsIgnoreCase(const char *a, const char *b);
int    containsIgnoreCase(const char *text, const char *needle);
void   printLine(char c, int n);
void   pauseScreen(void);

#endif
