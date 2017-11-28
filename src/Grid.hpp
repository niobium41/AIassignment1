//
//  Grid.hpp
//  SearchStragies
//
//  Created by David Stritzl on 08/11/15.
//
//

#ifndef Grid_hpp
#define Grid_hpp

#include "GridElement.hpp"
#include "constants.h"

#define N_WALLS_TO_BE_REMOVED 20

// simple macro to compute the manhattan distance to the end
// USAGE for a GridElement el: MANHATTAN_DISTANCE_TO_END(el)
#define MANHATTAN_DISTANCE_TO_END(el) ((GRID_SIZE - 1) - el->x) + ((GRID_SIZE - 1) - el->y)

class Grid {
public:
    Grid();
	bool real;
    void reset();
	void resetVisited();
    
    void draw();
    
    void clearRect(int, int, int, int);
    void drawArc(int, int, double, double, double);
    
    void generateMaze();
    void generateRooms();
    void generateObstacles();
    void generateJail();
    
    void depthFirstSearch();
	void depthFirstSearchInit();
	
	struct stackSearch {
		int search;
		std::stack<GridElement *> stack;
		GridElement* currentNode;
		float hue;
		float colorIncrement;
		int visitedNodes;
	};
	stackSearch dfs;

	struct queueSearch {
		int search;
		std::queue<GridElement *> queue;
		GridElement* currentNode;
		float hue;
		float colorIncrement;
		int visitedNodes;
	};
	queueSearch bfs;

    void breadthFirstSearch();
	void breadthFirstSearchInit();
    void greedySearch();
    void aStarSearch();
    
    GridElement grid[GRID_SIZE][GRID_SIZE];

	GridElement* goal;
	void setGoal();
	
	// Struct to store results
	struct results {
		string name;
		int visitedNodes;
		int shortestPath;
		bool goalReached;
	};

	// Array of structs for each search algorithm
	results searchResults[N_SEARCHES];

	// Names of search algorithms to display with results
	string names[N_SEARCHES]= { "Depth first", "Breadth first", "Greedy", "A*" };
	
	void showResults();

	bool toggleResults;
};

#endif /* Grid_hpp */
