#include <iostream>
#include <queue>
#include <bitset>
#define ROW 3
#define COL 3

using namespace std;

enum class direction
{
	up,
	down,
	left,
	right
};

typedef struct board
{
	int puzzle[ROW][COL];
	int pos_x = 0;
	int pos_y = 0;
	int weight = 0;
	int fx = 0;
}board;

struct cmp_board
{
	bool operator()(board x, board y) {
		return x.fx > y.fx;
	}
};

bitset<1000000000> closed;

int board_state(board current);
bool check_goal(board puzzle, board goal);
int compute_heuristic(board x, board goal);
board move_board(board current, direction d);
void print_board(board x);

int main(void)
{
	board current;
	board goal;

	priority_queue<board, vector<board>, cmp_board> open;

	// init goal
	for (int i = 0; i < ROW; ++i) {
		for (int j = 0; j < COL; ++j) {
			goal.puzzle[i][j] = i + (j + (ROW - 1) * i) + 1;

			if (i == ROW - 1 && j == COL - 1) {
				goal.puzzle[i][j] = 0;
			}
		}
	}

	// init puzzle
	for (int i = 0; i < ROW; ++i) {
		for (int j = 0; j < COL; ++j) {
			current.puzzle[i][j] = i + (j + (ROW - 1) * i);

			if (current.puzzle[i][j] == 0)
			{
				current.pos_x = i;
				current.pos_y = j;
			}
		}
	}

	open.push(current);

	while (!open.empty())
	{
		auto x = open.top();
		open.pop();

		print_board(x);

		if (check_goal(x, goal))
		{
			cout << "성공입니당" << endl;
			return 0;
		}

		auto x_board_state = board_state(x);

		closed[x_board_state] = true;

		// 다음 방향
		for (const auto d : { direction::up, direction::down, direction::left, direction::right })
		{
			auto new_board = move_board(x, d);

			if (new_board.pos_x == -1)
				continue;

			auto new_board_state = board_state(new_board);

			if (!closed[new_board_state])
			{
				// f(x) 구하는 방법
				new_board.fx = compute_heuristic(new_board, goal);

				open.push(new_board);
			}
		}
	}

	// condition: fail
	cout << "실패했습니당" << endl;
	return 1;
}

// 보드 상태를 숫자로
int board_state(board current)
{
	int answer = 0;
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			answer *= 10;
			answer += current.puzzle[i][j];
		}
	}
	return answer;
}

// 보드 움직이기
board move_board(board current, direction d)
{
	bool is_action = false;

	switch (d)
	{
	case direction::up:
		if (current.pos_x - 1 > -1)
		{
			swap(current.puzzle[current.pos_x][current.pos_y], current.puzzle[current.pos_x - 1][current.pos_y]);
			current.pos_x -= 1;
			is_action = true;
		}
		break;
	case direction::down:
		if (current.pos_x + 1 < ROW)
		{
			swap(current.puzzle[current.pos_x][current.pos_y], current.puzzle[current.pos_x + 1][current.pos_y]);
			current.pos_x += 1;
			is_action = true;
		}
		break;
	case direction::left:
		if (current.pos_y - 1 > -1)
		{
			swap(current.puzzle[current.pos_x][current.pos_y], current.puzzle[current.pos_x][current.pos_y - 1]);
			current.pos_y -= 1;
			is_action = true;
		}
		break;
	case direction::right:
		if (current.pos_y + 1 < COL)
		{
			swap(current.puzzle[current.pos_x][current.pos_y], current.puzzle[current.pos_x][current.pos_y + 1]);
			current.pos_y += 1;
			is_action = true;
		}
		break;
	default:
		break;
	}

	if (!is_action)
	{
		board null_board;
		null_board.pos_x = -1;
		return null_board;
	}

	return current;
}

// 결과 체크
bool check_goal(board current_puzzle, board goal)
{
	for (auto i = 0; i < ROW; ++i)
	{
		for (auto j = 0; j < COL; ++j)
		{
			if (current_puzzle.puzzle[i][j] != goal.puzzle[i][j])
				return false;
		}
	}

	return true;
}

// h(x) 계산 함수
int compute_heuristic(board x, board goal)
{
	int count = 0;

	for (auto i = 0; i < ROW; ++i)
	{
		for (auto j = 0; j < COL; ++j)
		{
			// 퍼즐이 같지 않으면 count 상승
			// 0은 빈칸이므로 결과에서 제거
			if (x.puzzle[i][j] != 0 && (x.puzzle[i][j] != goal.puzzle[i][j]))
			{
				count += 1;
			}
		}
	}

	return count;
}

void print_board(board x)
{
	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COL; ++j)
		{
			cout << x.puzzle[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}