//
//  GridDepthFirstSearch.cpp
//  SearchStragies
//
//  Created by David Stritzl on 08/11/2016.
//
//

#include <cstdlib>
#include <iostream>
#include <stack>

#include "Grid.hpp"


void Grid::depthFirstSearch() {
	int search = 0; //index in the array of searches (to display results)

	std::stack<GridElement *> stack;
	GridElement* currentNode = ROOT;

	float hue = 0;
	float colorIncrement = (float)255.0 / ((float)GRID_SIZE*(float)GRID_SIZE); //map the amount of nodes to hue
	int visitedNodes = 0;
	
	resetVisited(); //reset the visited nodes at the start of every search

	do  {

		stack.push(currentNode);
		
		if (!currentNode->visited) { 

			currentNode->visitedColor.setHsb(hue, 255, 200); 

			// if the hue is past 255 start at 0 again, else increment the hue;
			hue = (hue > 255) ? 0 : hue + colorIncrement;

			currentNode->visited = true;
			visitedNodes++;
		}
		
		if (currentNode == goal) {
			searchResults[search].visitedNodes = visitedNodes;
			searchResults[search].shortestPath = stack.size();
			break; //we're done since we've found the goal

		} else {

			//the next node will be a random unvisited neighbour, or NULL
			GridElement* next = currentNode->randomUnvisitedNeighbour();

			if (next != NULL) {
				currentNode = next;
			} else {
				//Go back in the stack if no unvisited neighbours
				stack.pop();
				currentNode = stack.top();
				stack.pop(); //pop current node, since push at the start of loop
			}
		}

	} while (!stack.empty());
	
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

