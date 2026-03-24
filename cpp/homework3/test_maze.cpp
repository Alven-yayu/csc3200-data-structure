#include <array>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <random>
#include <stack>
#include <vector>

#include "maze.h"

template <typename Generator>
std::tuple<maze_t, maze_pos, maze_pos> make_maze(std::size_t width, std::size_t height, Generator& gen) {
    using maze_row_t = maze_t::value_type;
    maze_t out(2 * width + 1, maze_row_t(2 * height + 1, maze_cell::wall));
    for(int x = 1 ; x < 2 * width + 1 ; x += 2)
        for(int y = 1 ; y < 2 * height + 1 ; y += 2)
            out[x][y] = maze_cell::free;

    std::uniform_int_distribution<int> width_dist(0, width - 1);
    std::uniform_int_distribution<int> height_dist(0, height - 1);
    const maze_pos start { width_dist(gen) * 2 + 1, height_dist(gen) * 2 + 1 };
    std::map<maze_pos, bool> visited;
    visited[start] = true;
    std::stack<maze_pos> stack;
    stack.push(start);
    out[start.x][start.y] = maze_cell::start;
    const maze_pos end = [&](){
            while (true) {
                const maze_pos end ( width_dist(gen) * 2 + 1, height_dist(gen) * 2 + 1 );
                if(end == start) continue;
                out[end.x][end.y] = maze_cell::end;
                return end;
            }
        }();
    auto unvisited_neighbours = [&](maze_pos p) {
        std::vector<maze_pos> out;
        for (auto n : std::array<maze_pos, 4>{{{p.x - 2, p.y}, {p.x + 2, p.y}, {p.x, p.y - 2}, {p.x, p.y + 2}}})
            if(n.x > 0 && n.x < 2 * width + 1 && n.y > 0 && n.y < 2 * height + 1 && !visited[n])
                out.push_back(n);
        return out;
    };
    while ( ! stack.empty() ) {
        const maze_pos current = stack.top();
        visited[current] = true;
        stack.pop();
        auto un = unvisited_neighbours(current);
        if ( !un.empty() ) {
            stack.push(current);
            std::uniform_int_distribution<std::size_t> neighbour_dist(0, un.size() - 1);
            const auto neighbour = un[neighbour_dist(gen)];
            const maze_pos between { (current.x + neighbour.x) / 2, (current.y + neighbour.y) / 2 };
            out[between.x][between.y] = maze_cell::free;
            stack.push(neighbour);
        }
    }
    return std::make_tuple(out, start, end);
}

void print(maze_t const& maze, std::stack<maze_pos> s, visited_t const& visited) {
    assert(valid_matrix(maze) && valid_matrix(visited));
    assert(maze.size() == visited.size() && maze[0].size() == visited[0].size());

    auto wall_char = [&](int x, int y) {
        if((x == 0 || x == maze.size() - 1) && (y == 0 || y == maze[0].size() - 1))
            return '+';
        else if(x == 0 || x == maze.size() - 1)
            return '|';
        else if(y == 0 || y == maze[0].size() - 1)
            return '-';
        else if(maze[x][y + 1] == maze_cell::wall && maze[x][y - 1] == maze_cell::wall
            && maze[x - 1][y] != maze_cell::wall && maze[x + 1][y] != maze_cell::wall)
            return '|';
        else if(maze[x][y + 1] != maze_cell::wall && maze[x][y - 1] != maze_cell::wall
            && maze[x - 1][y] == maze_cell::wall && maze[x + 1][y] == maze_cell::wall)
            return '-';
        else return '+';
    };
    char c_unvisited[4] = { ' ', '+', 's', 'e' };
#ifndef MONOCHROME
    std::array<const char*, 4> c_visited = { "\x1b[90m.\x1b[0m", "\x1b[31m?\x1b[0m", "S", "E" };
    std::array<const char*, 4> c_stack = { "\x1b[32m*\x1b[0m", "\x1b[31m?\x1b[0m", "\x1b[32mS\x1b[0m", "\x1b[32mE\x1b[0m" };
#else
    std::array<const char*, 4> c_visited = { ".", "?", "S", "E" };
    std::array<const char*, 4> c_stack = { "*", "?", "S", "E" };
#endif
    std::map<maze_pos, bool> on_stack;
    std::cout << "Stack: ";
    while(s.size() > 1) {
        on_stack[s.top()] = true;
        std::cout << s.top() << ", ";
        s.pop();
    }
    on_stack[s.top()] = true;
    std::cout << s.top() << "\n-------------------------------------------------------------\n";
    std::cout << ' ';
    if (maze.size() > 10) {
        std::cout << ' '; 
        for(std::size_t x = 0; x <= maze.size() / 10; ++x)
            std::cout << static_cast<char>('0' + x) << "...      ";
        std::cout << "\n  ";
    }
    for(std::size_t x = 0; x < maze.size(); ++x)
        std::cout << static_cast<char>('0' + x % 10);
    std::cout << '\n';
    for(std::size_t y = 0; y < maze[0].size(); ++y) {
        if (maze[0].size() > 10)
            std::cout << static_cast<char>('0' + y / 10);
        std::cout << static_cast<char>('0' + y % 10);
        for(std::size_t x = 0; x < maze.size(); ++x) {
            if(on_stack[maze_pos(x, y)]) std::cout << c_stack[static_cast<int>(maze[x][y])];
            else if(visited[x][y]) std::cout << c_visited[static_cast<int>(maze[x][y])];
            else std::cout << (maze[x][y] == maze_cell::wall ? wall_char(x, y) : c_unvisited[static_cast<int>(maze[x][y])] );
        }
        std::cout << "\n";
    }
    std::cout << "-------------------------------------------------------------\n";
    std::cout << "Legend:\n";
    std::array<const char*, 4> names { "free", "wall", "start", "end" };
    for(int i = 0; i < 4; ++i) {
        std::cout << names[i] << ":\ton stack: " << c_stack[i] << "\tvisited: " 
                  << c_visited[i] << "\tunvisited: " << c_unvisited[i] << "\n";
    }
    std::cout << '\n';
}

bool validate_dfs(maze_t const& maze, std::stack<maze_pos> stack, visited_t const& visited,
                  bool finished) {
    assert(valid_matrix(maze) && valid_matrix(visited));
    assert(maze.size() == visited.size() && maze[0].size() == visited[0].size());

    bool valid = true;
    std::map<maze_pos, bool> on_stack;
    while( !stack.empty() ) {
        on_stack[stack.top()] = true;
        stack.pop();
    }
    for (int x = 0; x < maze.size(); ++x)
        for (int y = 0; y < maze[0].size(); ++y) {
            const auto cell = maze[x][y];
            std::array<maze_pos, 4> neighbours {{{x - 1, y}, {x + 1, y}, {x, y - 1}, {x, y + 1}}};
            auto in_range = [&maze](maze_pos n)
                { return n.x >= 0 && n.x < maze.size() && n.y >= 0 && n.y < maze[0].size(); };
            const int visited_neighbours = std::count_if(neighbours.begin(), neighbours.end(),
                    [&](maze_pos n) { return in_range(n) && visited[n.x][n.y]; });
            const int wall_neighbours = std::count_if(neighbours.begin(), neighbours.end(),
                    [&](maze_pos n) { return in_range(n) && maze[n.x][n.y] == maze_cell::wall; });
            switch(cell) {
                case maze_cell::free:
                    if (visited[x][y])
                        valid = valid && (visited_neighbours >= 2 || on_stack[maze_pos(x, y)] || wall_neighbours == 3);
                    break;
                case maze_cell::wall:
                    valid = valid && !visited[x][y];
                    break;
                case maze_cell::start:
                    valid = valid && (visited_neighbours >= 1 || !finished);
                    break;
                case maze_cell::end:
                    valid = valid && (visited_neighbours == 1 || !finished);
                    break;
            }
            if ( !valid ) {
                std::cout << "failed at " << x << ", " << y << '\n';
                return false;
            }
        }
    return true;
}

int main() {
    std::mt19937 g(0);
    double score = 0.;
    const int mazes_per_dim = 5;
    for (int dim : {3, 5, 8, 10, 12, 15, 20}) {
        int padded_dim = dim * 2 + 1;
        std::cout << "Testing " << mazes_per_dim << " " << padded_dim << " * " << padded_dim << " mazes.\n";
        bool all_valid = true;
        for (int i = 0; i < mazes_per_dim; ++i) {
            auto [maze, start, end] = make_maze(dim, dim, g);
            std::stack<maze_pos> stack;
            visited_t visited(maze.size(), std::vector<bool>(maze[0].size(), false));
            search_maze(maze, start, end, stack, visited);
            auto valid = validate_dfs(maze, stack, visited, true);
            if ( !valid ) {
                std::cout << "Failure.\n";
                print(maze, stack, visited);
                all_valid = false;
            }
        }
        if (all_valid) {
            score += 0.5;
            std::cout << "Success.\n";
        }
    }
    std::cout << "Problem 1 subtotal: " << score << " / 3.5\n";
    return 0;
}