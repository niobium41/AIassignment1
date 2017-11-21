//
//  GridDepthFirstSearch.cpp
//  SearchStragies
//
//  Created by David Stritzl on 08/11/2016.
//	Adapted by Laura Beunk on 15/11/2017.
//

#include <cstdlib>
#include <iostream>
#include <stack>

#include "ofApp.h"
#include "Grid.hpp"
#include "search.h"

void Grid::depthFirstSearchInit() {
	dfs.search = 0; // Index in the array of searches (to display results)

	 // Create a stack
	dfs.currentNode = ROOT; // Make the first node the root

	dfs.hue = 0;
	dfs.colorIncrement = (float)255.0 / ((float)GRID_SIZE*(float)GRID_SIZE); // Map the amount of nodes to hue

	dfs.visitedNodes = 0; // Keep track of the amount of visited nodes

	resetVisited(); // Reset the visited nodes at the start of every search
}

void Grid::depthFirstSearch() {
	do{
	// Put the current node on the stack
	dfs.stack.push(dfs.currentNode);

	// Check if the current node is visited, if not change its status and color
	if (!dfs.currentNode->visited) {

		dfs.currentNode->visitedColor.setHsb(dfs.hue, 255, 200);

		// If the hue is past 255 start at 0 again, else increment the hue;
		dfs.hue = (dfs.hue > 255) ? 0 : dfs.hue + dfs.colorIncrement;

		dfs.currentNode->visited = true;
		dfs.visitedNodes++; // Another node visited
	}

	// Check if the goal has been reached
	if (dfs.currentNode == goal) {

		// Save the amount of nodes visited and stack size (path length)
		searchResults[dfs.search].visitedNodes = dfs.visitedNodes;
		searchResults[dfs.search].shortestPath = dfs.stack.size();
		searchResults[dfs.search].goalReached = true;
		real = false;
		return; // We're done since we've found the goal

	}
	else {

		// If the goal has not been reached, the next node will be a random unvisited neighbour, or NULL
		GridElement* next = dfs.currentNode->randomUnvisitedNeighbour();

		if (next != NULL) {
			// If we found an unvisted neighbour, make it the current node
			dfs.currentNode = next;
		}
		else {
			// Go back in the stack if no unvisited neighbours by removing the current node from the stack
			dfs.stack.pop();

			// Make the top node the current node and pop it since push at the start of loop
			dfs.currentNode = dfs.stack.top();
			dfs.stack.pop();
		}
	}
	if (dfs.stack.empty()) {
		searchResults[dfs.search].visitedNodes = dfs.visitedNodes;
		real = false;

	}
	if (real) {
		return;
	}
	}while (!dfs.stack.empty());
	real = false;
}
//void Grid::depthFirstSearch() {
//	
//	int search = 0; // Index in the array of searches (to display results)
//
//	std::stack<GridElement *> stack; // Create a stack
//	GridElement* currentNode = ROOT; // Make the first node the root
//
//	float hue = 0;
//	float colorIncrement = (float)255.0 / ((float)GRID_SIZE*(float)GRID_SIZE); // Map the amount of nodes to hue
//
//	int visitedNodes = 0; // Keep track of the amount of visited nodes
//
//	resetVisited(); // Reset the visited nodes at the start of every search
//
//	// Loop when the stack is not empty
//	do  {
//
//		// Put the current node on the stack
//		stack.push(currentNode);
//		
//		// Check if the current node is visited, if not change its status and color
//		if (!currentNode->visited) { 
//
//			currentNode->visitedColor.setHsb(hue, 255, 200); 
//
//			// If the hue is past 255 start at 0 again, else increment the hue;
//			hue = (hue > 255) ? 0 : hue + colorIncrement;
//
//			currentNode->visited = true;
//			visitedNodes++; // Another node visited
//		}
//		
//		// Check if the goal has been reached
//		if (currentNode == goal) {
//
//			// Save the amount of nodes visited and stack size (path length)
//			searchResults[search].visitedNodes = visitedNodes;
//			searchResults[search].shortestPath = stack.size();
//			searchResults[search].goalReached = true;
//
//			return; // We're done since we've found the goal
//
//		} else {
//
//			// If the goal has not been reached, the next node will be a random unvisited neighbour, or NULL
//			GridElement* next = currentNode->randomUnvisitedNeighbour();
//
//			if (next != NULL) { 
//				// If we found an unvisted neighbour, make it the current node
//				currentNode = next;
//			} else {
//				// Go back in the stack if no unvisited neighbours by removing the current node from the stack
//				stack.pop();
//
//				// Make the top node the current node and pop it since push at the start of loop
//				currentNode = stack.top();
//				stack.pop(); 
//			}
//		}
//		
//	} while (!stack.empty());
//	
//	// Save the amount of nodes visited and stack size (path length)
//	searchResults[search].visitedNodes = visitedNodes;
//	searchResults[search].goalReached = false;
//
    //
    // USAGE
    //
    // - add element (of type GridElement *) to the top of the stack:
    // stack.push(element)
    //
    // - remove element from the top of the stack: (note: this will crash the program if the stack is empty)
    // stack.pop()
    //
    // - get element from the top of the stack: (note: this will crash the program if the stack is empty)
    // stack.top()
    //   example:
    // GridElement *element = stack.top();
    //
    // - check if the stack is empty:
    // stack.empty()
    //   example:
    // bool is_empty = stack.empty();
    //
    // for more information refer to the documentation:
    // http://en.cppreference.com/w/cpp/container/stack
    //
}

