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
