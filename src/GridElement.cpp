//
//  GridElement.cpp
//  SearchStragies
//
//  Created by David Stritzl on 08/11/15.
//
//

#include "GridElement.hpp"

#include <cstdio>

#include "ofMain.h"
#include "constants.h"

GridElement::GridElement() {
    // Reset all neighbours
    for(int direction = 0; direction < N_DIRECTIONS; direction++) {
        neighbours[direction] = NULL;
    }
    
	visitedColor.setHsb(0, 0, 0);
    reset();
	
}

void GridElement::reset() {
    // reset all walls
    for(int direction = 0; direction < N_DIRECTIONS; direction++) {
        walls[direction] = true;
    }
	isPath = false;
    visited = false;
	marked = false;
    parent = NULL;
    length_of_path = -1;
    score = 0;
}

void GridElement::draw() {
    // draw background if visited
    if(visited) {
        ofSetColor(visitedColor);
        ofDrawRectangle(x * GRID_ELEMENT_WIDTH, y * GRID_ELEMENT_HEIGHT, GRID_ELEMENT_WIDTH, GRID_ELEMENT_HEIGHT);
    }
    
    // draw circle if marked
    if(marked) {
        ofSetColor(255, 255, 255);
        ofDrawEllipse((x + 0.5) * GRID_ELEMENT_WIDTH, (y + 0.5) * GRID_ELEMENT_HEIGHT, GRID_ELEMENT_WIDTH * 0.5, GRID_ELEMENT_HEIGHT * 0.5);
    }
	if (isPath) {
		ofSetColor(255, 255, 255,70);
		ofDrawRectangle((x) * GRID_ELEMENT_WIDTH, (y) * GRID_ELEMENT_HEIGHT, GRID_ELEMENT_WIDTH , GRID_ELEMENT_HEIGHT );
	}
    // draw all walls
    for(int direction = 0; direction < N_DIRECTIONS; direction++) {
        if(walls[direction]) {
            drawWall((Direction)direction);
        }
    }
}

void GridElement::drawWall(Direction direction) {
    ofSetColor(255);
    
    switch(direction) {
        case DirectionNorth:
            ofDrawLine(x * GRID_ELEMENT_WIDTH, y * GRID_ELEMENT_HEIGHT, (x + 1) * GRID_ELEMENT_WIDTH, y * GRID_ELEMENT_HEIGHT);
            break;
        case DirectionEast:
            ofDrawLine((x + 1) * GRID_ELEMENT_WIDTH, y * GRID_ELEMENT_HEIGHT, (x + 1) * GRID_ELEMENT_WIDTH, (y + 1) * GRID_ELEMENT_HEIGHT);
            break;
        case DirectionSouth:
            ofDrawLine(x * GRID_ELEMENT_WIDTH, (y + 1) * GRID_ELEMENT_HEIGHT, (x + 1) * GRID_ELEMENT_WIDTH, (y + 1) * GRID_ELEMENT_HEIGHT);
            break;
        case DirectionWest:
            ofDrawLine(x * GRID_ELEMENT_WIDTH, y * GRID_ELEMENT_HEIGHT, x * GRID_ELEMENT_WIDTH, (y + 1) * GRID_ELEMENT_HEIGHT);
            break;
    }
}

void GridElement::setWall(Direction direction, bool is_solid) {
    walls[direction] = is_solid;
    
    // set opposite wall if it exists
    if(neighbours[direction] != NULL) {
        neighbours[direction]->walls[oppositeDirection(direction)] = is_solid;
    }
}

GridElement* GridElement::randomUnvisitedNeighbour() {
	// Returns a pointer to a random unvisited neighbour or NULL if all are visited

	int found[4] = { 0,0,0,0 }; // To keep track of checked neighbours

	// Loop until each neighbour has been checked, or an unvisited neighbour has been found 
	while (found[0]+found[1]+found[2]+found[3] < 4) {
		int direction = rand() % 4; // Choose a random direction to check
		
		found[direction] = 1; // Set this direction to checked

		// If this neighbour is accessible and unvisited, return it
		if (neighbours[direction]!=NULL && !walls[direction] && !neighbours[direction]->visited) {
			return neighbours[direction];
		}
	}

	return NULL; // Return NULL if no univisted neighbour has been found
}