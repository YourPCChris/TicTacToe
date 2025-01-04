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


using namespace std;

void DrawWindow(int screenWidth, int screenHeight)
{
	ClearBackground(BLUE);
	//Drawing Title centered horizontally
	const char* title = "TicTacToe";
	int textWidth = MeasureText(title, 50);
	DrawText(title, (screenWidth - textWidth) / 2, 20, 50, BLACK);
}

void DrawGrid(const vector<pair<int, int>>& grid, int recWidth, int recHeight, vector<pair<int, int>>& clickedRec)
{
	for (const auto& coord : grid)
	{
		if (std::find_if(clickedRec.begin(), clickedRec.end(),
					[&coord](const pair<int,int>& clickedCo){return (coord == clickedCo);}) != clickedRec.end())
		{
			DrawCircleLines(coord.first, coord.second, recWidth/2, WHITE);
		}else{
			DrawRectangle(coord.first, coord.second, recWidth, recHeight, WHITE);
		}
	}
	/*
	for (const auto& coord : grid)
    	{
	       	// Check if coord is in clickedRec
       	 	if (std::find(clickedRec.begin(), clickedRec.end(), coord) != clickedRec.end()) {
            	// If the coordinate is in clickedRec, draw a hollow circle
            	DrawCircleLines(coord.first, coord.second, recWidth / 2, WHITE);
        	}
        	else {
            	// Otherwise, draw a filled rectangle
            	DrawRectangle(coord.first, coord.second, recWidth, recHeight, WHITE);
        	}
	}
	*/
}
bool comparePair(pair<int,int>& one, pair<int, int> two)
{
	return (one == two);
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
	pair<int,int> clicked;

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
			if ((clicked = checkClick(grid, recWidth, recHeight)) != make_pair(-1,-1)) clickedRec.push_back(clicked);
			DrawGrid(grid, recWidth, recHeight, clickedRec);
		EndDrawing();
	}
	CloseWindow();

	return 0;
}
