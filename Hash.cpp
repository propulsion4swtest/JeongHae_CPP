#include <stdio.h>
//double list///////////////////////////////////////////////////////
#define SIZE 1000
int arr_index = 0;
typedef struct NODE {
    char str[7];
    NODE *prev, *next;
}NODE;
NODE a[SIZE];
NODE* myalloc()
{
    //초기화 후 전달
    a[arr_index].next = NULL;
    a[arr_index].prev = NULL;
    return &a[arr_index++];
}
//hash//////////////////////////////////////////////////////////////
#define MAX_TABLE 1000
unsigned long Hash(const char *str)
{
    unsigned long hash = 5381;
    int c;
    while (c = *str++)
        hash = (((hash << 5) + hash) + c) % MAX_TABLE;
    return hash % MAX_TABLE;
}
NODE HashTable[MAX_TABLE];
void str_Cpy(char *dest, char *src, int size)
{
    int i = 0;
    for (i = 0; i < size; ++i)
        dest[i] = src[i];
    dest[i] = '\0';
}
int str_Cmp(char *str_a, char *str_b) 
{//문자열 비교(앞 문자열이 크면 양수, 뒤 문자열이 크면 음수
    for (register int i = 0; str_a[i] !=NULL || str_b[i] !=NULL; i++)
    {
        if (str_a[i] == str_b[i]) continue;//동일 문자면 skip
        return str_a[i] - str_b[i];//다르면 차를 리턴
    }
    return 0;//두 문자열이 동일
}
void hash_Insert(char *str)
{
    int key = (int)Hash(str);
    NODE *p = myalloc();
    str_Cpy(p->str, str, 7);
    NODE *next = HashTable[key].next;
    NODE *prev = &HashTable[key];
    p->next = next;
    p->prev = prev;
    prev->next = p;
    if (next != NULL) next->prev = p;
}
void hash_Find(char *str)
{
    int key = (int)Hash(str);
    for (NODE *iter = HashTable[key].next; iter != NULL; iter = iter->next)
    {
        if (!str_Cmp(str, iter->str))
        {
            printf("find words\n");
            return;
        }
    }
    printf("not found\n");
}
void hash_Erase(char *str)
{
    int key = (int)Hash(str);
    for (NODE *iter = HashTable[key].next; iter != NULL; iter = iter->next)
    {
        if (!str_Cmp(str, iter->str))
        {
            NODE *prev = iter->prev;
            NODE *next = iter->next;
            prev->next = next;
            if(next != NULL) next->prev = prev;
            return;
        }
    }
}
////////////////////////////////////////////////////////////////
void INIT()
{
    arr_index = 0;
    for (int i = 0; i <= MAX_TABLE; ++i)
        HashTable[i].next = NULL;
}
int main()
{
    INIT();
    char str[7] = "abcdef";
    hash_Insert(str);
    hash_Find(str);
    hash_Erase(str);
    hash_Find(str);
    return 0;
}
