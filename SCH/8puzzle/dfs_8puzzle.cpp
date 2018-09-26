#include <iostream>
#include <vector>
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
}board;

bitset<1000000000> closed;

int board_state(board current);
bool check_goal(board puzzle, board goal);
board move_board(board current, direction d);
void print_board(board x);

int main(void)
{
	board current;
	board goal;

	vector<board> open;

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

	open.push_back(current);

	while (!open.empty())
	{
		auto x = open.back();
		open.pop_back();

		// x가 goal과 같을 때
		if (check_goal(x, goal))
		{
			// condition: success
			cout << "성공입니당" << endl;
			return 0;
		}
		else
		{
			// 다음 방향
			for (const auto d : { direction::up, direction::down, direction::left, direction::right })
			{
				auto new_board = move_board(x, d);
				if (new_board.pos_x == -1)
					continue;
				auto new_board_state = board_state(new_board);

				if (!closed[new_board_state])
				{
					closed[new_board_state] = true;
					open.push_back(new_board);
				}
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