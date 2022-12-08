//
// Created by hp on 08/12/2022.
//

#ifndef DFSFRAME_CC_GRAPHVISITOR_H
#define DFSFRAME_CC_GRAPHVISITOR_H

// 求无向图的连通子图

#include "../BasicsVisitor/ADJList.h"

class CC_GraphVisitor : public GraphVisitor {
private:
    int verCnt;
    int startIdx{};
    int *ccIds;
public:
    explicit CC_GraphVisitor(int N) {
        this->verCnt = N;
        ccIds = new int[N];
    }

    ~CC_GraphVisitor() {
        delete[] ccIds;
    }

    // visit的时候，可以通过graph的接口，获取相关的信息，比如vIdx顶点的出边，
    // 这样就能处理一些复杂的问题，例如拓扑排序。
    void visit(int vIdx, ADJList *graph) override {
        this->ccIds[vIdx] = this->startIdx;
    }

    // 起始大部分情况下，这个函数不用做任何处理。
    void reStart(int vIdx) override {
        this->startIdx = vIdx;
    }

    void outputCCIds() {
        // 进行输出
        for (int i = 0; i < this->verCnt; i++)
            std::cout << this->ccIds[i] << " ";
    }
};


#endif //DFSFRAME_CC_GRAPHVISITOR_H

/*
测试Demo:
#include "DerivationVisitor/CC_GraphVisitor.h"
int main() {
    auto *graph = new ADJList;
    graph->read();
    //首先创建初始的visitor对象
    auto *visitor = new CC_GraphVisitor(graph->getVerCnt());
    //因为visitor是后序处理，因此作为第二个参数传递给函数Travel
    //因为是按照从小到大的顺序遍历的，所以第三个参数为NULL
    graph->Travel(nullptr, visitor);
    visitor->outputCCIds();
}
*/
