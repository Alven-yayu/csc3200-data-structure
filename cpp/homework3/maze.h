#include <algorithm>
#include <stack>
#include <vector>
#include <ostream>

enum class maze_cell { free, wall, start, end };

struct maze_pos {
    int x;
    int y;
    maze_pos(int x, int y) : x(x), y(y) {}
    bool operator==(const maze_pos& o) const { return x == o.x && y == o.y; }
    bool operator<(const maze_pos& o) const { return x < o.x || (x == o.x && y < o.y); }
};

inline std::ostream& operator<<(std::ostream& os, maze_pos p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

using maze_t = std::vector<std::vector<maze_cell>>;
using visited_t = std::vector<std::vector<bool>>;

template <typename Matrix>
bool valid_matrix(Matrix const& m) {
    using row_t = typename Matrix::value_type;
    return m.size() > 0 && m[0].size() > 0 &&
        std::all_of(m.begin(), m.end(), [&](row_t const& r) { return r.size() == m[0].size(); });
}

void print(maze_t const& maze, std::stack<maze_pos> s, visited_t const& visited);
bool validate_dfs(maze_t const& maze, std::stack<maze_pos> stack, visited_t const& visited,
                  bool finished = true);

void search_maze(maze_t const& maze, maze_pos start, maze_pos end,
                 std::stack<maze_pos>& stack, visited_t& visited);