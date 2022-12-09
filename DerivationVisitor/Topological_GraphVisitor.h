//
// Created by hp on 08/12/2022.
//

#ifndef DFSFRAME_TOPOLOGICAL_GRAPHVISITOR_H
#define DFSFRAME_TOPOLOGICAL_GRAPHVISITOR_H

#include "../BasicsVisitor/ADJList.h"

class Topological_GraphVisitor : public GraphVisitor {
private:
    int verCnt;// 顶点数
    int SerialNo{};// 用于记录
    vector<int> serials;// 用于记录答案的数组
public:
    explicit Topological_GraphVisitor(int N) {
        this->verCnt = N;
        serials.resize(N, -1);
    }

    ~Topological_GraphVisitor() {
        serials.clear();
    }

    void visit(int vIdx, ADJList *graph) override {
        SerialNo++;
        serials[vIdx] = SerialNo;
    }

    void reStart(int vIdx) override {
        // 本题中无需使用该函数
    }

    void outputCCIds() {
        // 用于输出答案
        unordered_map<int, int> m;
        for (int i = 0; i < verCnt; i++) {
            m[serials[i]] = i;
        }
        sort(serials.begin(), serials.end());
        for (int i = verCnt - 1; i >= 0; i--) {
            cout << m[serials[i]] << " ";
        }
        cout << endl;
    }
};

#endif //DFSFRAME_TOPOLOGICAL_GRAPHVISITOR_H


/*
测试Demo:
#include "DerivationVisitor/Topological_GraphVisitor.h"
int main() {
    auto *graph = new ADJList;
    graph->read();
    //首先创建初始的visitor对象
    auto *visitor = new Topological_GraphVisitor(graph->getVerCnt());
    //因为visitor是后序处理，因此作为第二个参数传递给函数Travel
    //因为是按照从小到大的顺序遍历的，所以第三个参数为NULL
    graph->Travel(nullptr, visitor);
    visitor->outputCCIds();
}

 */
