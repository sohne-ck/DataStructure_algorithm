#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

void solve();   // ��һ��Ͱ���򼴿ɽ��������

int main()
{
    solve();

    return 0;
}

void solve()
{
    int i, n, tmp, age_count[51] = {0};

    scanf("%d", &n);
    for (i = 0; i < n; ++i) {
        scanf("%d", &tmp);
        ++age_count[tmp];
    }

    for (i = 0; i < 51; ++i) {
        if (age_count[i])
            printf("%d:%d\n", i, age_count[i]);
    }
}
