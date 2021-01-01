#include <stdio.h>
#include <stdlib.h>

typedef struct User_Info *Ptr_User_Info;
struct User_Info {
    int total_score;    // �ܷ֣�-1��ʾû���ύ���������ύ��δͨ������
    int score[5];   // ����÷֣�-1��ʾ�ύ��δͨ�����룬-2��ʾδ�ύ
    int perfect_num;    // ����ύ��Ŀ��
};
typedef Ptr_User_Info User_Info_Arr;

int user_num, problem_num;
User_Info_Arr info_arr;
int problem_mark[5];    // �洢����Ŀ�ܷ�

/* ������������Ͱ�����������ݽṹ���忪ʼ������������ */
/* ͰԪ�ؽ�� */
typedef struct Node *PtrToNode;
struct Node {
    int key;
    PtrToNode next;
};

/* Ͱͷ��� */
struct HeadNode {
    PtrToNode head, tail;
};
typedef struct HeadNode *Bucket;
/* ������������Ͱ�����������ݽṹ������������������� */

void solve();

void ReadData();    // ��ȡ���벢��ʼ��������
void LSDRadixSort_Print();    // ��λ���ȵĻ��������ȶ���Ѵ��������������ٶ��ֽܷ�������֮��������

int main()
{
    solve();

    return 0;
}

void solve()
{
    ReadData();
    LSDRadixSort_Print();
    free(info_arr);
}

void ReadData()
{
    int submission_num, i, j, user_id, problem_id, partial_score_obtained;

    scanf("%d %d %d", &user_num, &problem_num, &submission_num);
    for (i = 0; i < problem_num; ++i)
        scanf("%d", &problem_mark[i]);
    info_arr = (User_Info_Arr)malloc(user_num * sizeof(struct User_Info));
    // ��ʼ�����û��ĸ���Ŀ�÷�Ϊ-2���ܷ�Ϊ-1����δ�ύ״̬
    for (i = 0; i < user_num; ++i) {
        for (j = 0; j < problem_num; ++j)
            info_arr[i].score[j] = -2;
        info_arr[i].total_score = -1;
        info_arr[i].perfect_num = 0;
    }
    for (i = 0; i < submission_num; ++i) {
        scanf("%d %d %d", &user_id, &problem_id, &partial_score_obtained);
        --user_id; --problem_id;
        if (info_arr[user_id].score[problem_id] == -2) { // �������Ŀδ�ύ������ֻҪ����Ŀ���ύ��¼�������ʼ��Ϊ�ύ��δ����ͨ��״̬
            info_arr[user_id].score[problem_id] = -1;
        }
        if (info_arr[user_id].score[problem_id] < partial_score_obtained) {    // �ύ����ͨ��
            if (info_arr[user_id].total_score < 0)  // �����û�֮ǰû���ύ��¼��û���κα���ͨ���ύ��������Ϊ�б���ͨ���ύ�����ֲܷ�С��0
                info_arr[user_id].total_score = 0;
            if (info_arr[user_id].score[problem_id] == -1)  // �����û�������ύ֮ǰδ����ͨ������˴�������Ϊ0��
                info_arr[user_id].score[problem_id] = 0;
            info_arr[user_id].total_score += (partial_score_obtained - info_arr[user_id].score[problem_id]);
            if (partial_score_obtained == problem_mark[problem_id] && info_arr[user_id].score[problem_id] != partial_score_obtained)
                ++(info_arr[user_id].perfect_num);
            info_arr[user_id].score[problem_id] = partial_score_obtained;
        }
    }
}

void LSDRadixSort_Print()
{
    int i, j, total_score, rank, parallel_num;
    Bucket perfectBucket, scoreBucket;
    PtrToNode tmp;

    // 1. �ȶ���Ѵ�������Ͱ����
    perfectBucket = (Bucket)malloc((problem_num + 1) * sizeof(struct HeadNode));
    for (i = 0; i <= problem_num; ++i)
        perfectBucket[i].head = perfectBucket[i].tail = NULL;
    for (i = 0; i < user_num; ++i) {
        if (info_arr[i].total_score < 0) continue;  // ������û��ܷ�С��0����û���ύ��û�б���ͨ�����ύ���򲻼�������
        tmp = (PtrToNode)malloc(sizeof(struct Node));
        tmp->key = i;
        tmp->next = NULL;
        if (perfectBucket[info_arr[i].perfect_num].head == NULL)
            perfectBucket[info_arr[i].perfect_num].head = perfectBucket[info_arr[i].perfect_num].tail = tmp;
        else {
            perfectBucket[info_arr[i].perfect_num].tail->next = tmp;
            perfectBucket[info_arr[i].perfect_num].tail = tmp;
        }
    }

    // 2. �ٶ��ܵ÷ֽ�Ͱ����
    total_score = 0;
    for (i = 0; i < problem_num; ++i)   // �������ַ���
        total_score += problem_mark[i];
    scoreBucket = (Bucket)malloc((total_score + 1) * sizeof(struct HeadNode));
    for (i = 0; i <= total_score; ++i)
        scoreBucket[i].head = scoreBucket[i].tail = NULL;
    for (i = problem_num ; i >= 0; --i) {
        while (perfectBucket[i].head) {
            tmp = perfectBucket[i].head;
            perfectBucket[i].head = perfectBucket[i].head->next;
            tmp->next = NULL;
            if (scoreBucket[info_arr[tmp->key].total_score].head == NULL)
                scoreBucket[info_arr[tmp->key].total_score].head = scoreBucket[info_arr[tmp->key].total_score].tail = tmp;
            else {
                scoreBucket[info_arr[tmp->key].total_score].tail->next = tmp;
                scoreBucket[info_arr[tmp->key].total_score].tail = tmp;
            }
        }
    }

    // 3. ������
    rank = 1;
    for (i = total_score; i >= 0; --i) {
        parallel_num = 0;   // ����ͬ���ε�����
        while (scoreBucket[i].head) {
            tmp = scoreBucket[i].head;
            scoreBucket[i].head = scoreBucket[i].head->next;
            printf("%d %05d %d", rank, tmp->key + 1, info_arr[tmp->key].total_score);
            for (j = 0; j < problem_num; ++j) {
                if (info_arr[tmp->key].score[j] == -2)
                    printf(" -");
                else if (info_arr[tmp->key].score[j] == -1)
                    printf(" 0");
                else
                    printf(" %d", info_arr[tmp->key].score[j]);
            }
            printf("\n");
            free(tmp);
            ++parallel_num;
        }
        rank += parallel_num;
    }

    free(perfectBucket);
    free(scoreBucket);
}
