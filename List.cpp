#include <stdio.h>
#define SIZE 1000
int arr_index = 0;
typedef struct NODE{
    int v;
    NODE *prev, *next;
}NODE;
NODE a[SIZE];
NODE* head, *tail;
NODE* myalloc()
{
    //초기화 후 전달
    a[arr_index].next = NULL;
    a[arr_index].prev = NULL;
    a[arr_index].v = -1;
    return &a[arr_index++];
}
void INIT()
{
    arr_index = 0;
    head = myalloc();
    tail = myalloc();
    head->next = tail;
    tail->prev = head;
}
void INSERT(NODE *p, int data)
{
    NODE *prev = tail->prev;
    NODE *next = prev->next;
    p->v = data;
    p->prev = prev;
    p->next = next;
    prev->next = next->prev = p;
}
void ERASE(NODE *p)
{
    NODE *prev = p->prev;
    NODE *next = p->next;
    prev->next = next;
    next->prev = prev;
}
int main()
{
    INIT();
    NODE *p;
    //data 리스트에 삽입
    for (int i = 1; i <= 10; ++i)
    {
        p = myalloc();
        INSERT(p, i);
    }
    //데이터 출력 확인
    p = head->next;
    while (p!=tail)
    {
        printf("data : %d\n",p->v);
        p = p->next;
    }
    //데이터 삭제
    p = head->next;
    while (p != tail)
    {
        if (p->v == 5) ERASE(p);
        p = p->next;
    }
    return 0;
}
