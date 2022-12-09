# 用于单项目的整合代码，只需要在需要的地方添加对应的类和代码即可

## 前置通用部分

```
#include <bits/stdc++.h>

using namespace std;

class IntList
{
public:
	int tgtIdx;
	IntList *link;
};

class ADJList;

class GraphVisitor
{
public:
	// 指访问编号为vIdx的顶点时的处理过程
	virtual void reStart(int vIdx){};

	// 指在从vIdx开始访问时的处理过程。
	// 这个函数实际上只有在需要记住DFS的起始顶点信息时才需要设置，否则直接定义为空函数即可。
	virtual void visit(int vIdx, ADJList *graph) = 0;
};

// 邻接表
class ADJList
{
private:
	int N;				// 顶点的个数
	IntList **adjLists; // 邻接表数组
	int *weightOnV;		// 顶点的权重数组

	static int lstLen(IntList *list); // 获取list链表的长度

public:
	static const int WHITE = 0;
	static const int GREY = 1;
	static const int BLACK = 2;

	ADJList();

	~ADJList();

	IntList *getLeavingEdges(int vIdx); // 获取顶点vIdx的邻接链表

	int getVerCnt() const; // 获取顶点的个数

	int *getWeightOnV(); // 返回权重数组

	void read_WeightOnV(); // 读取数据构造邻接表和权重数组

	void read(); // 读取数据构造邻接表(在顶点不存在权重的情况下使用)

	void output(); // 输出邻接表

	// 图的遍历的相关函数可以写成下面的形式：
	// 这两个函数都有两个参数：preVisitor, postVisitor。分别在前序、后序位置调用该visitor的visit成员函数。
	// 另外，Travel的第三个参数是sweep各个顶点时的顺序，如果为NULL，那么它就按照顶点序号从小到大进行处理。
	void DFS(int v, int *color, GraphVisitor *preVisitor, GraphVisitor *postVisitor); // 深度优先搜索

	// 遍历所有顶点(图可能不是连通图)
	void Travel(GraphVisitor *preVisitor, GraphVisitor *postVisitor, const int *sweepSequence = nullptr);
};
```

## 专门的算法处理class类和main函数

```
// 专门的算法处理class类
int main()
{
	auto *graph = new ADJList;
	graph->read();
	// 首先创建初始的visitor对象
	auto *visitor = new (对应的类)(graph->getVerCnt());
	// 第一个参数为前序处理,第二个参数为后续处理,第三个参数为节点处理顺序
	graph->Travel(nullptr, visitor, nullptr);
	// 专门的输出函数,部分情况可忽略
	visitor->outputCCIds();
}
```

## 后置通用部分

```
int ADJList::lstLen(IntList *list)
{
	int num = 0;
	IntList *head = list;
	while (head != nullptr)
	{
		num++;
		head = head->link;
	}
	return num;
}

ADJList::ADJList()
{
	N = 0;
	this->adjLists = nullptr;
	this->weightOnV = nullptr;
}

ADJList::~ADJList()
{
	delete this->adjLists;
	delete this->weightOnV;
}

IntList *ADJList::getLeavingEdges(int vIdx)
{
	return this->adjLists[vIdx];
}

int ADJList::getVerCnt() const
{
	return this->N;
}

int *ADJList::getWeightOnV()
{
	return this->weightOnV;
}

void ADJList::read_WeightOnV()
{
	delete this->adjLists;
	cin >> this->N; // 输入顶点个数
	this->weightOnV = new int[N];
	for (int i = 0; i < this->N; i++)
	{
		// 输入各顶点的权重
		cin >> this->weightOnV[i];
	}
	this->adjLists = new IntList *[N];
	for (int i = 0; i < this->N; i++)
	{
		int c; // 该顶点的邻接顶点数目
		this->adjLists[i] = nullptr;
		cin >> c;
		IntList *tail = nullptr;
		for (int j = 0; j < c; j++)
		{
			auto *lstNode = new IntList();
			cin >> lstNode->tgtIdx;
			lstNode->link = nullptr;
			if (tail == nullptr)
			{
				this->adjLists[i] = lstNode;
			}
			else
			{
				tail->link = lstNode;
			}
			tail = lstNode;
		}
	}
}

void ADJList::read()
{
	delete this->adjLists;
	cin >> this->N;
	this->adjLists = new IntList *[N];
	for (int i = 0; i < this->N; i++)
	{
		int c;
		this->adjLists[i] = nullptr;
		cin >> c;
		IntList *tail = nullptr;
		for (int j = 0; j < c; j++)
		{
			auto *lstNode = new IntList();
			cin >> lstNode->tgtIdx;
			lstNode->link = nullptr;
			if (tail == nullptr)
			{
				this->adjLists[i] = lstNode;
			}
			else
			{
				tail->link = lstNode;
			}
			tail = lstNode;
		}
	}
}

void ADJList::output()
{
	cout << this->N << endl; // 输出顶点数
	for (int i = 0; i < this->N; i++)
	{
		int c = lstLen(this->adjLists[i]);
		cout << c << " ";
		for (IntList *cur = this->adjLists[i]; cur != nullptr; cur = cur->link)
		{
			cout << cur->tgtIdx << " ";
		}
		cout << endl;
	}
}

void ADJList::DFS(int v, int *color, GraphVisitor *preVisitor, GraphVisitor *postVisitor)
{
	color[v] = GREY;
	if (preVisitor != nullptr)
	{
		preVisitor->visit(v, this);
	}
	IntList *edges = this->adjLists[v];
	for (IntList *cur = edges; cur != nullptr; cur = cur->link)
	{
		int tgtVertex = cur->tgtIdx;
		if (color[tgtVertex] == WHITE)
			DFS(tgtVertex, color, preVisitor, postVisitor);
	}
	if (postVisitor != nullptr)
	{
		postVisitor->visit(v, this);
	}
	color[v] = BLACK;
}

void ADJList::Travel(GraphVisitor *preVisitor, GraphVisitor *postVisitor, const int *sweepSequence)
{
	int *color = new int[this->N];
	for (int i = 0; i < this->N; i++)
	{
		color[i] = WHITE;
	}
	int curVertex;
	for (int i = 0; i < this->N; i++)
	{
		curVertex = (sweepSequence == nullptr) ? i : sweepSequence[i];
		if (color[curVertex] == WHITE)
		{
			if (preVisitor != nullptr)
				preVisitor->reStart(curVertex);
			if (postVisitor != nullptr)
				postVisitor->reStart(curVertex);
			DFS(curVertex, color, preVisitor, postVisitor);
		}
	}
	delete[] color;
}
```