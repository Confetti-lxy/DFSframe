# DFS框架和Visitor模式

+ 通常我们可以基于DFS框架实现各种图算法。单独的某一种算法的代码通常会设置全局变量、然后根据需要修改DFS框架，在适当的地方插入适当的代码。
+ 但这样的代码的复用性很差，难以在大多数地方通用，此时可以通过DFS框架和Visitor模式构造对应的类来进行处理，使得算法具有较好的复用性。

## visitor的虚基类

代码如下：

```
class ADJList;
class GraphVisitor
{
public:
	void virtual reStart(int vIdx) {};
	void virtual visit(int vIdx, ADJList * graph) = 0;
};
```

其中：

1. visit(int vIdx, ADJList * graph)是指访问编号为vIdx的顶点时的处理过程；
2. reStart(int vIdx)是指在从vIdx开始访问时的处理过程。这个函数实际上只有在需要记住DFS的起始顶点信息时才需要设置，否则直接定义为空函数即可。
3. 注意这两个都是虚函数

这样处理之后，图的遍历的相关函数可以写成下面的形式：
这两个函数都有两个参数：preVisitor, postVisitor。分别在前序、后序位置调用该visitor的visit成员函数。
另外，Travel的第三个参数是sweep各个顶点时的顺序，如果为NULL，那么它就按照顶点序号从小到大进行处理。

```
void DFS(int v, int* color, GraphVisitor *preVisitor, GraphVisitor *postVisitor)
	{
		color[v] = GREY;
		if (preVisitor != NULL) preVisitor->visit(v, this);

		IntList * edges = this->adjLists[v];
		for (IntList *cur = edges; cur != NULL; cur = cur->link)
		{
			int tgtVertex = cur->Data;
			if (color[tgtVertex] == WHITE)
				DFS(tgtVertex, color, preVisitor, postVisitor);
		}

		if (postVisitor != NULL) postVisitor->visit(v, this);
		color[v] = BLACK;
	}

	void Travel(GraphVisitor *preVisitor, GraphVisitor *postVisitor, int* sweepSequence = NULL)
	{
		int *color = new int[this->N];
		for (int i = 0; i < this->N; i++)
			color[i] = WHITE;
		int curVertex;
		for (int i = 0; i < this->N; i++)
		{
			curVertex = (sweepSequence == NULL) ? i : sweepSequence[i];
			if (color[curVertex] == WHITE)
			{
				if (preVisitor != NULL) preVisitor->reStart(curVertex);
				if (postVisitor != NULL) postVisitor->reStart(curVertex);

				DFS(curVertex, color, preVisitor, postVisitor);
			}
		}

		delete[] color;
	}
```

## Visitor模式

在使用Visitor模式时，一般只需要进行下面的处理：

1. 首先、把需要的全局变量设置成Visitor对象的成员变量；
2. 然后、在适当的地方调用Visitor的成员函数visit，而这个visit函数将根据需要对成员变量进行处理。
3. 最后，当遍历完毕后，调用Visitor中的成员函数获取成员变量的值。

## 代码文件清单

+ 主函数 main.cpp
+ 编译文件 CMakeLists.txt
+ git配置文件 .gitignore
+ 目录清单 catalogue.md
+ Debug文件夹 cmake-build-debug
+ BasicsVisitor文件夹,包含:

1. IntList.h 链表类的创建
2. ADJList.cpp,ADJList.h visitor的基虚类和邻接表的定义

+ DerivationVisitor文件夹,包含:

1. CC_GraphVisitor.h 求无向图的连通子图
2. Topological_GraphVisitor 拓扑排序