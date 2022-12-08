//
// Created by hp on 08/12/2022.
//

#include "ADJList.h"

int ADJList::lstLen(IntList *list) {
    int num = 0;
    IntList *head = list;
    while (head != nullptr) {
        num++;
        head = head->link;
    }
    return num;
}

ADJList::ADJList() {
    N = 0;
    this->adjLists = nullptr;
    this->weightOnV = nullptr;
}

ADJList::~ADJList() {
    delete this->adjLists;
    delete this->weightOnV;
}

IntList *ADJList::getLeavingEdges(int vIdx) {
    return this->adjLists[vIdx];
}

int ADJList::getVerCnt() const {
    return this->N;
}

int *ADJList::getWeightOnV() {
    return this->weightOnV;
}

void ADJList::read_WeightOnV() {
    delete this->adjLists;
    cin >> this->N;// 输入顶点个数
    this->weightOnV = new int[N];
    for (int i = 0; i < this->N; i++) {
        // 输入各顶点的权重
        cin >> this->weightOnV[i];
    }
    this->adjLists = new IntList *[N];
    for (int i = 0; i < this->N; i++) {
        int c;//该顶点的邻接顶点数目
        this->adjLists[i] = nullptr;
        cin >> c;
        IntList *tail = nullptr;
        for (int j = 0; j < c; j++) {
            auto *lstNode = new IntList();
            cin >> lstNode->tgtIdx;
            lstNode->link = nullptr;
            if (tail == nullptr) {
                this->adjLists[i] = lstNode;
            } else {
                tail->link = lstNode;
            }
            tail = lstNode;
        }
    }
}

void ADJList::read() {
    delete this->adjLists;
    cin >> this->N;
    this->adjLists = new IntList *[N];
    for (int i = 0; i < this->N; i++) {
        int c;
        this->adjLists[i] = nullptr;
        cin >> c;
        IntList *tail = nullptr;
        for (int j = 0; j < c; j++) {
            auto *lstNode = new IntList();
            cin >> lstNode->tgtIdx;
            lstNode->link = nullptr;
            if (tail == nullptr) {
                this->adjLists[i] = lstNode;
            } else {
                tail->link = lstNode;
            }
            tail = lstNode;
        }
    }
}

void ADJList::output() {
    cout << this->N << endl;// 输出顶点数
    for (int i = 0; i < this->N; i++) {
        int c = lstLen(this->adjLists[i]);
        cout << c << " ";
        for (IntList *cur = this->adjLists[i]; cur != nullptr; cur = cur->link) {
            cout << cur->tgtIdx << " ";
        }
        cout << endl;
    }
}

void ADJList::DFS(int v, int *color, GraphVisitor *preVisitor, GraphVisitor *postVisitor) {
    color[v] = GREY;
    if (preVisitor != nullptr) {
        preVisitor->visit(v, this);
    }
    IntList *edges = this->adjLists[v];
    for (IntList *cur = edges; cur != nullptr; cur = cur->link) {
        int tgtVertex = cur->tgtIdx;
        if (color[tgtVertex] == WHITE)
            DFS(tgtVertex, color, preVisitor, postVisitor);
    }
    if (postVisitor != nullptr) {
        postVisitor->visit(v, this);
    }
    color[v] = BLACK;
}

void ADJList::Travel(GraphVisitor *preVisitor, GraphVisitor *postVisitor, const int *sweepSequence) {
    int *color = new int[this->N];
    for (int i = 0; i < this->N; i++) {
        color[i] = WHITE;
    }
    int curVertex;
    for (int i = 0; i < this->N; i++) {
        curVertex = (sweepSequence == nullptr) ? i : sweepSequence[i];
        if (color[curVertex] == WHITE) {
            if (preVisitor != nullptr) preVisitor->reStart(curVertex);
            if (postVisitor != nullptr) postVisitor->reStart(curVertex);
            DFS(curVertex, color, preVisitor, postVisitor);
        }
    }
    delete[] color;
}