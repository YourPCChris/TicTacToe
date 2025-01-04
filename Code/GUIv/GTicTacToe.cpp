/*
 * Tic Tac Toe in C++ 
 * with a GUI using raylib
 *
 * Christopher Bennett
 *
 * 04/01/2025
 *
 * */

#include <iostream>
#include "raylib.h"
#include <vector>
#include <algorithm>
#include <chrono>


using namespace std;

void delay(int seconds) {
    auto start = std::chrono::steady_clock::now();
    while (std::chrono::steady_clock::now() - start < std::chrono::seconds(seconds)) {
        // Looping without doing anything, just waiting
    }
}

bool checkWin(const vector<pair<int, int>>& clicked, const vector<pair<int,int>>& grid) {
    // Winning lines
    vector<vector<int>> winningLines = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Rows
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Columns
        {0, 4, 8}, {2, 4, 6}             // Diagonals
    };

    for (const auto& line : winningLines) {
        if (find(clicked.begin(), clicked.end(), grid[line[0]]) != clicked.end() &&
            find(clicked.begin(), clicked.end(), grid[line[1]]) != clicked.end() &&
            find(clicked.begin(), clicked.end(), grid[line[2]]) != clicked.end()) {
            return true;
        }
    }
    return false;
}

void DrawWindow(int screenWidth, int screenHeight)
{
	ClearBackground(BLUE);
	//Drawing Title centered horizontally
	const char* title = "TicTacToe";
	int textWidth = MeasureText(title, 50);
	DrawText(title, (screenWidth - textWidth) / 2, 20, 50, BLACK);
}

void DrawGrid(const vector<pair<int, int>>& grid, int recWidth, int recHeight, vector<pair<int, int>>& clickedRec, vector<pair<int,int>>& circles)
{
	for (const auto& coord : grid)
	{
		if (find_if(clickedRec.begin(), clickedRec.end(),
						[&coord](const pair<int,int>& clickedCo){return (coord == clickedCo);}) != clickedRec.end())
			{
				DrawCircleLines(coord.first, coord.second, recWidth/2, WHITE);
			}
		else if (find_if(circles.begin(), circles.end(),
						[&coord](const pair<int,int>& clickedCo){return (coord == clickedCo);}) != circles.end())
			{
				DrawLine(coord.first - recWidth/2, coord.second - recHeight/2, coord.first + recWidth/2, coord.second + recWidth/2, WHITE);
				DrawLine(coord.first + recWidth/2, coord.second - recHeight/2, coord.first - recWidth/2, coord.second + recWidth/2, WHITE);
			}
		else
		{
			DrawRectangle(coord.first, coord.second, recWidth, recHeight, WHITE);
		}
	}
}

pair<int, int> checkClick(const vector<pair<int, int>>& grid, int rectWidth, int recHeight)
{
	//Get Mouse position and check it against grid of co-ordinates
	Vector2 MousePos = GetMousePosition();

	for (int i=0; i < grid.size() ;i++)
	{
		Rectangle rect = {(float)grid[i].first, (float)grid[i].second, (float)rectWidth, (float)recHeight};
		if (CheckCollisionPointRec(MousePos, rect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
			cout << "Rectangle Clicked" << endl;
			return grid[i];
		}
	}
	return make_pair(-1,-1);
}


int main()
{

	cout << "We Ball" << endl;


	
	//Define constant window size
	const int screenWidth = 1000;
	const int screenHeight = 800;
	const int recWidth = 50;
	const int recHeight = 50;
	vector<pair<int,int>> clickedRec;
	vector<pair<int,int>> circles;
	pair<int,int> clicked;
	bool turnCount = true;
	const char* playerOneWins = "Player One Wins!";
	const char* playerTwoWins = "Player Two Wins!";
	int winCount = 0;

	InitWindow(screenWidth, screenHeight, "TicTacToe");
	SetWindowState(FLAG_VSYNC_HINT);
	SetTargetFPS(60);

	//Define Grid Array
	vector<pair<int, int>> grid = 
	{
        {screenWidth / 3 - recWidth / 2, screenHeight / 3 - recHeight / 2}, // Top-left
        {screenWidth / 2 - recWidth / 2, screenHeight / 3 - recHeight / 2}, // Top-center
        {2 * screenWidth / 3 - recWidth / 2, screenHeight / 3 - recHeight / 2}, // Top-right
        {screenWidth / 3 - recWidth / 2, screenHeight / 2 - recHeight / 2}, // Middle-left
        {screenWidth / 2 - recWidth / 2, screenHeight / 2 - recHeight / 2}, // Middle-center
        {2 * screenWidth / 3 - recWidth / 2, screenHeight / 2 - recHeight / 2}, // Middle-right 
	{screenWidth / 3 - recWidth / 2, 2 * screenHeight / 3 - recHeight / 2}, // Bottom-left
        {screenWidth / 2 - recWidth / 2, 2 * screenHeight / 3 - recHeight / 2}, // Bottom-center
        {2 * screenWidth / 3 - recWidth / 2, 2 * screenHeight / 3 - recHeight / 2}  // Bottom-right
    	};


	//Main Loop
	while (!WindowShouldClose())
	{
		BeginDrawing();
			DrawWindow(screenWidth, screenHeight);
			//Check if grid is clicked
			if ((clicked = checkClick(grid, recWidth, recHeight)) != make_pair(-1,-1)){
				(turnCount ? clickedRec:circles).push_back(clicked);
				turnCount = !turnCount;
			}

			//Draw Grid
			DrawGrid(grid, recWidth, recHeight, clickedRec, circles);
			//Winner

			bool didPTwoWin = checkWin(circles, grid);
			bool didPOneWin = checkWin(clickedRec, grid);

			if (didPOneWin){
				++winCount;
				if (winCount >=  2)
				{
					DrawText(playerOneWins, (screenWidth - MeasureText(playerOneWins, 50))/2, 90, 50, YELLOW);
					cout << "Player One Win" << endl;
				}
                	}
                	if (didPTwoWin){
				++winCount;
				if (winCount >= 2){
					DrawText(playerTwoWins, (screenWidth - MeasureText(playerTwoWins, 50))/2, 90, 50, YELLOW);
					cout << "Player 2 Wins" << endl;
				}
                	}
		EndDrawing();

		if (winCount > 1){delay(2);break;}
	}
	CloseWindow();

	return 0;
}
