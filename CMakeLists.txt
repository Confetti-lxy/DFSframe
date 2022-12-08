cmake_minimum_required(VERSION 3.23)
project(DFSframe)

set(CMAKE_CXX_STANDARD 14)

add_executable(DFSframe main.cpp BasicsVisitor/ADJList.cpp BasicsVisitor/ADJList.h BasicsVisitor/IntList.h DerivationVisitor/CC_GraphVisitor.h DerivationVisitor/Topological_GraphVisitor.h)
