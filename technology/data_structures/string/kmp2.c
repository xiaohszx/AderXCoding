#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define DEBUG

#ifdef DEBUG
    #define debug printf
#else
    #define debug 0 && printf
#endif



/*  通过计算返回子串T的next数组  */
void GetNext(char *str, int *next)
{
    int i = 0, j = -1;          /*  i, j分别为前缀和后缀的下标  */

    next[i] = -1;               /*  由next[0] == -1开始进行递推  */
    printf("next[%d] = %2d\n", i, next[i]);

    while(i < strlen(str) - 1)  /*  数组next的下标范围为0~strlen(str) - 1*/
    {
        printf("i = %d, j = %d\n", i, j);
        if(j == -1)
        {
            i++;
            j++
            next[i] = j;
            printf("j == -1, next[%d] = %d\n", i, 0);
        }
        else if(str[i] == str[j])
        {
            i++;
            j++;
            /* 此时next[i] = next[i] + 1
             * 由于str[i] == str[j]
             * 所以next[i] = next[i - 1] + 1 = j*/
            next[i] = j;
            printf("str[%d] == str[%d], next[%d] = %d\n", i - 1, j - 1, i, j);
        }
        else
        {
            printf("str[%d] != str[%d], j = next[j]\n", i, j, j);
            j = next[j];        /*  若字符不相等, 则j回溯  */
        }
        printf("next[%d] = %2d\n", i, next[i]);
    }

#ifdef DEBUG
    printf("\n");
    for(int i = 0; i < strlen(str); i++)
    {
        printf("%d  ", next[i]);
    }
    printf("\n");
#endif
}


int KMPIndex(char *str, char *sub, int pos)
{
    int i = pos, j = 0;
    int next[255];

    GetNext(str, next);     /*  分析子串sub的next数组  */
    while(i < strlen(str) && j < strlen(sub))
    {
        if(j == -1 || str[i] == sub[j])  /*  两字符相等, 则继续匹配  */
        {
            debug("[%d]%c, [%d]%c\n", i, str[i], j, sub[j]);
            i++;
            j++;
        }
        else                            /*  否则的话, 返回合适位置重新匹配  */
        {
            j = next[j];                /*  子串退回到合适位置, 主串不变  */
        }
    }

    debug("%d %d\n", i, j);
    if(j >= strlen(sub))
    {
        return i - j; // j = strlen(sub);
    }
    else
    {
        return -1;
    }
}

int main(int argc, char *argv[])
{
    char    str[81];
    int     next[81];
    strcpy(str, "abaabcac");
    GetNext(str, next);

    //printf("%d\n", KMPIndex("aaaaacefghij", "aaac", 0));
    return EXIT_SUCCESS;
}


