//
// Created by sohne on 2020/12/17.
//

//void BFS ( Vertex S )
//{ visited[S] = true;
//    Enqueue(S, Q);
//    while(!IsEmpty(Q)){
//        V = Dequeue(Q);
//        for ( V 的每个邻接点 W )
//            if ( !visited[W] ) {
//                visited[W] = true;
//                Enqueue(W, Q);
//            }
//    }
//}


//void Unweighted ( Vertex S )
//{ Enqueue(S, Q);
//    while(!IsEmpty(Q)){
//        V = Dequeue(Q);
//        for ( V 的每个邻接点 W )
//            if ( dist[W]==-1 ) {
//                dist[W] = dist[V]+1;
//                path[W] = V;
//                Enqueue(W, Q);
//            }
//    }
//} //T = O( |V| + |E| )

//dist[W] = S到W的最短距离; 
//dist[S] =0;
//path[W] = S到的路上经过的某顶点;



//https://juejin.cn/post/6844903665103273992
//https://blog.csdn.net/winbobob/article/details/38314821