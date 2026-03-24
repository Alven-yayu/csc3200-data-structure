#include <algorithm>
#include <stack>
#include <vector>
#include <iostream>  
#include "maze.h"

// 方向数组
const int dx[] = {0, 0, -1, 1};
const int dy[] = {-1, 1, 0, 0};

void search_maze(maze_t const& maze, maze_pos start, maze_pos end,
                 std::stack<maze_pos>& stack, visited_t& visited) {
    // 检查迷宫是否为空
    if (maze.empty() || maze[0].empty()) {
        return;
    }

    // 清空 visited 矩阵
    for (auto& row : visited) {
        std::fill(row.begin(), row.end(), false);
    }

    // 初始化：将起点压入栈，并标记为已访问
    stack.push(start);
    visited[start.y][start.x] = true;

    // DFS 搜索
    while (!stack.empty()) {
        maze_pos current = stack.top();

        // 如果到达终点，搜索结束
        if (current == end) {
            return;
        }

        // 尝试四个方向
        bool found_next = false;
        for (int i = 0; i < 4; ++i) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];

            // 检查是否在迷宫范围内
            if (nx >= 0 && nx < maze[0].size() && ny >= 0 && ny < maze.size()) {
                // 检查是否是墙或已访问
                if (maze[ny][nx] == maze_cell::wall || visited[ny][nx]) {
                    continue;
                }

                // 如果是 free 或 end，且未被访问，压入栈并标记
                if (maze[ny][nx] == maze_cell::free || maze[ny][nx] == maze_cell::end) {
                    maze_pos next(nx, ny);
                    stack.push(next);
                    visited[ny][nx] = true;
                    found_next = true;
                    break; // 找到下一个位置后，立即开始下一轮搜索
                }
            }
        }

        // 如果没有找到下一个位置，回溯（弹出当前节点）
        if (!found_next) {
            stack.pop();
        }
    }

    // 如果栈为空，说明没有找到路径
    std::cout << "没有找到从起点到终点的路径！" << std::endl;
}