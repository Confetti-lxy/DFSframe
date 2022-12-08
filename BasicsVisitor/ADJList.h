//
// Created by hp on 08/12/2022.
//

#ifndef DFSFRAME_ADJLIST_H
#define DFSFRAME_ADJLIST_H

#include "IntList.h"

class ADJList;

class GraphVisitor {
public:
    // 指访问编号为vIdx的顶点时的处理过程
    virtual void reStart(int vIdx) {};

    // 指在从vIdx开始访问时的处理过程。
    // 这个函数实际上只有在需要记住DFS的起始顶点信息时才需要设置，否则直接定义为空函数即可。
    virtual void visit(int vIdx, ADJList *graph) = 0;
};

// 邻接表
class ADJList {
private:
    int N;// 顶点的个数
    IntList **adjLists;// 邻接表数组
    int *weightOnV;// 顶点的权重数组

    static int lstLen(IntList *list);// 获取list链表的长度

public:
    static const int WHITE = 0;
    static const int GREY = 1;
    static const int BLACK = 2;

    ADJList();

    ~ADJList();

    IntList *getLeavingEdges(int vIdx);// 获取顶点vIdx的邻接链表

    int getVerCnt() const;// 获取顶点的个数

    int *getWeightOnV();// 返回权重数组

    void read_WeightOnV();// 读取数据构造邻接表和权重数组

    void read();// 读取数据构造邻接表(在顶点不存在权重的情况下使用)

    void output();// 输出邻接表

    // 图的遍历的相关函数可以写成下面的形式：
    // 这两个函数都有两个参数：preVisitor, postVisitor。分别在前序、后序位置调用该visitor的visit成员函数。
    // 另外，Travel的第三个参数是sweep各个顶点时的顺序，如果为NULL，那么它就按照顶点序号从小到大进行处理。
    void DFS(int v, int *color, GraphVisitor *preVisitor, GraphVisitor *postVisitor);// 深度优先搜索

    // 遍历所有顶点(图可能不是连通图)
    void Travel(GraphVisitor *preVisitor, GraphVisitor *postVisitor, const int *sweepSequence = nullptr);
};


#endif //DFSFRAME_ADJLIST_H
