#include <stdio.h>
#include <stdlib.h>

void solve();

int main()
{
    solve();

    return 0;
}

void solve()
{
    int i, n, tmp, num, *arr;

    scanf("%d", &n);
    arr = (int *)malloc(n * sizeof(int));

    for (i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }

    num = 0; i = 0;
    if (arr[0] == 0) i = 1;
    for (; i < n; ++i) {
        if (arr[i] != i) {
            ++num;  // ����0���ڻ����˴���Ҫ��0���⻻��û��У���˶�ִ��һ��swap
            while (arr[i] != i) {
                if (arr[i] == 0)    // ˵��0��������������⻻�뻷�У���������+1���������ұ��������ټ�1����Ϊ����0�Ļ������������ڻ����ȼ�1
                    --num;
                else
                    ++num;
                tmp = arr[i];
                arr[i] = i;
                i = tmp;
            }
        }
    }

    printf("%d", num);
    free(arr);
}
