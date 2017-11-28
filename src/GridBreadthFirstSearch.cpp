//
//  GridBreadthFirstSearch.cpp
//  SearchStragies
//
//  Created by David Stritzl on 08/11/2016.
//
//

#include "Grid.hpp"
#include "ofApp.h"

#include <iostream>
#include <queue>

void Grid::breadthFirstSearchInit() {
	bfs.search = 1; // Index in the array of searches (to display results)

	bfs.currentNode = ROOT; // Make the first node the root

	bfs.hue = 0;
	bfs.colorIncrement = (float)255.0 / ((float)GRID_SIZE*(float)GRID_SIZE); // Map the amount of nodes to hue

	bfs.visitedNodes = 0; // Keep track of the amount of visited nodes

	resetVisited(); // Reset the visited nodes at the start of every search
	
	

	bfs.queue.push(bfs.currentNode);
}
void Grid::breadthFirstSearch() {
	do {
		bfs.currentNode = bfs.queue.front();
		bfs.queue.pop();

		

			
		

		if (bfs.currentNode == goal) {

			// Save the amount of nodes visited and stack size (path length)
			searchResults[bfs.search].visitedNodes = bfs.visitedNodes;
			//searchResults[bfs.search].shortestPath = bfs.stack.size();
			searchResults[bfs.search].goalReached = true;
			real = false;
			queue<GridElement*> empty;
			swap(bfs.queue, empty);
			return; // We're done since we've found the goal

		}
		else {
			for (int direction = 0; direction < N_DIRECTIONS; direction++) {
				if (bfs.currentNode->neighbours[direction] != NULL && !bfs.currentNode->walls[direction] && !bfs.currentNode->neighbours[direction]->visited) {
					bfs.queue.push(bfs.currentNode->neighbours[direction]);
					
					bfs.queue.back()->visitedColor.setHsb(bfs.hue, 255, 200);

					// If the hue is past 255 start at 0 again, else increment the hue;
					bfs.hue = (dfs.hue > 255) ? 0 : bfs.hue + bfs.colorIncrement;

					bfs.queue.back()->visited = true;
					bfs.visitedNodes++; // Another node visited
				}
			}
		}
		if (real) {
			return;
		}
	} while (!bfs.queue.empty()&&bfs.visitedNodes<GRID_SIZE*GRID_SIZE);
	queue<GridElement*> empty;
	swap(bfs.queue, empty);
	real = false;
    //
    // USAGE
    //
    // - add element (of type GridElement *) to the end of the queue:
    // queue.push(element)
    //
    // - remove element from the front of the queue: (note: this will crash the program if the queue is empty)
    // queue.pop()
    //
    // - get element from the front of the queue: (note: this will crash the program if the queue is empty)
    // queue.front()
    //   example:
    // GridElement *element = queue.front();
    //
    // - check if the queue is empty:
    // queue.empty()
    //   example:
    // bool is_empty = queue.empty();
    //
    // for more information refer to the documentation:
    // http://en.cppreference.com/w/cpp/container/queue
    //
}
