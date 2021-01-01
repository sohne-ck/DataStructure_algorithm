//
// Created by sohne on 2020/12/19.
//

class MatrixUDG {
#define MAX    100
#define INF    (~(0x1<<31))        // 无穷大(即0X7FFFFFFF)
private:
    char mVexs[MAX];    // 顶点集合
    int mVexNum;             // 顶点数
    int mEdgNum;             // 边数
    int mMatrix[MAX][MAX];   // 邻接矩阵

public:
    // 创建图(自己输入数据)
    MatrixUDG();
    // 创建图(用已提供的矩阵)
    //MatrixUDG(char vexs[], int vlen, char edges[][2], int elen);
    MatrixUDG(char vexs[], int vlen, int matrix[][9]);
    ~MatrixUDG();

    // 深度优先搜索遍历图
    void DFS();
    // 广度优先搜索（类似于树的层次遍历）
    void BFS();
    // prim最小生成树(从start开始生成最小生成树)
    void prim(int start);
    // 打印矩阵队列图
    void print();

private:
    // 读取一个输入字符
    char readChar();
    // 返回ch在mMatrix矩阵中的位置
    int getPosition(char ch);
    // 返回顶点v的第一个邻接顶点的索引，失败则返回-1
    int firstVertex(int v);
    // 返回顶点v相对于w的下一个邻接顶点的索引，失败则返回-1
    int nextVertex(int v, int w);
    // 深度优先搜索遍历图的递归实现
    void DFS(int i, int *visited);

};


//MatrixUDG是邻接矩阵对应的结构体。
//mVexs用于保存顶点，mVexNum是顶点数，mEdgNum是边数；
// mMatrix则是用于保存矩阵信息的二维数组。
// 例如，mMatrix[i][j]=1，则表示"顶点i(即mVexs[i])"
// 和"顶点j(即mVexs[j])"是邻接点；mMatrix[i][j]=0，
// 则表示它们不是邻接点。


/*
 * prim最小生成树
 *
 * 参数说明：
 *   start -- 从图中的第start个元素开始，生成最小树
 */
void MatrixUDG::prim(int start)
{
    int min,i,j,k,m,n,sum;
    int index=0;         // prim最小树的索引，即prims数组的索引
    char prims[MAX];     // prim最小树的结果数组
    int weights[MAX];    // 顶点间边的权值

    // prim最小生成树中第一个数是"图中第start个顶点"，因为是从start开始的。
    prims[index++] = mVexs[start];

    // 初始化"顶点的权值数组"，
    // 将每个顶点的权值初始化为"第start个顶点"到"该顶点"的权值。
    for (i = 0; i < mVexNum; i++ )
        weights[i] = mMatrix[start][i];
    // 将第start个顶点的权值初始化为0。
    // 可以理解为"第start个顶点到它自身的距离为0"。
    weights[start] = 0;

    for (i = 0; i < mVexNum; i++)
    {
        // 由于从start开始的，因此不需要再对第start个顶点进行处理。
        if(start == i)
            continue;

        j = 0;
        k = 0;
        min = INF;
        // 在未被加入到最小生成树的顶点中，找出权值最小的顶点。
        while (j < mVexNum)
        {
            // 若weights[j]=0，意味着"第j个节点已经被排序过"(或者说已经加入了最小生成树中)。
            if (weights[j] != 0 && weights[j] < min)
            {
                min = weights[j];
                k = j;
            }
            j++;
        }

        // 经过上面的处理后，在未被加入到最小生成树的顶点中，权值最小的顶点是第k个顶点。
        // 将第k个顶点加入到最小生成树的结果数组中
        prims[index++] = mVexs[k];
        // 将"第k个顶点的权值"标记为0，意味着第k个顶点已经排序过了(或者说已经加入了最小树结果中)。
        weights[k] = 0;
        // 当第k个顶点被加入到最小生成树的结果数组中之后，更新其它顶点的权值。
        for (j = 0 ; j < mVexNum; j++)
        {
            // 当第j个节点没有被处理，并且需要更新时才被更新。
            if (weights[j] != 0 && mMatrix[k][j] < weights[j])
                weights[j] = mMatrix[k][j];
        }
    }

    // 计算最小生成树的权值
    sum = 0;
    for (i = 1; i < index; i++)
    {
        min = INF;
        // 获取prims[i]在mMatrix中的位置
        n = getPosition(prims[i]);
        // 在vexs[0...i]中，找出到j的权值最小的顶点。
        for (j = 0; j < i; j++)
        {
            m = getPosition(prims[j]);
            if (mMatrix[m][n]<min)
                min = mMatrix[m][n];
        }
        sum += min;
    }
    // 打印最小生成树
    cout << "PRIM(" << mVexs[start] << ")=" << sum << ": ";
    for (i = 0; i < index; i++)
        cout << prims[i] << " ";
    cout << endl;
}