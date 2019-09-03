typedef struct node
{
    int id;
    int x;
}node;
node arr[SIZE];
node tmp[SIZE];
bool comp(const node *a, const node *b)
{
    return (a->x < b->x);
}
void merge_sort(int s, int e)
{
    int m = (s + e) >> 1, L = s, R = m + 1, K = s;
    if (s >= e) return;
    merge_sort(s, m);
    merge_sort(m + 1, e);
    while ((L <= m) && (R <= e))
    {
        if (comp(&arr[L], &arr[R])) tmp[K++] = arr[L++];
        else tmp[K++] = arr[R++];
    }
    while (L <= m)tmp[K++] = arr[L++];
    while (R <= e) tmp[K++] = arr[R++];
    for (int k = s; k <= e; k++) arr[k] = tmp[k];
}
