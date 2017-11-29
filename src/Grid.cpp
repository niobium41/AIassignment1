//
//  Grid.cpp
//  SearchStragies
//
//  Created by David Stritzl on 08/11/15.
//
//

#define _USE_MATH_DEFINES

#include "Grid.hpp"

#include <cassert>
#define _USE_MATH_DEFINES 
#include <cmath>

#include "Direction.hpp"

Grid::Grid() {
	toggleResults = false; // Don't show the result numbers by default
	real = false;
	// Assign names to search results and initial values
	for(int search = 0; search < N_SEARCHES; search++) {
		searchResults[search].name		   = names[search];
		searchResults[search].visitedNodes = NULL;
		searchResults[search].shortestPath = NULL;
		searchResults[search].goalReached = false;
	}

    // Set positions and neighbours of all elements
    for(int y = 0; y < GRID_SIZE; y++) {
        for(int x = 0; x < GRID_SIZE; x++) {
            grid[x][y].x = x;
            grid[x][y].y = y;
            
            if (x > 0)				grid[x][y].neighbours[DirectionWest]  = &grid[x - 1][y];
            if (x < GRID_SIZE - 1)	grid[x][y].neighbours[DirectionEast]  = &grid[x + 1][y];
            if (y > 0)				grid[x][y].neighbours[DirectionNorth] = &grid[x][y - 1];
            if (y < GRID_SIZE - 1)	grid[x][y].neighbours[DirectionSouth] = &grid[x][y + 1];
        }
    }
}

void Grid::reset() {
    // Reset all elements
    for(int y = 0; y < GRID_SIZE; y++) {
        for(int x = 0; x < GRID_SIZE; x++) {
            grid[x][y].reset();
        }
    }

	// Reset scores
	for (int search = 0; search < N_SEARCHES; search++) {
		searchResults[search].visitedNodes = NULL;
		searchResults[search].shortestPath = NULL;
		searchResults[search].goalReached = false;
	}

}

void Grid::resetVisited() {
	// Reset all elements' visited state
	for (int y = 0; y < GRID_SIZE; y++) {
		for (int x = 0; x < GRID_SIZE; x++) {
			grid[x][y].visited = false;
			grid[x][y].isPath = false;
		}
	}
}


void Grid::draw() {
    // Draw all elements
    for(int y = 0; y < GRID_SIZE; y++) {
        for(int x = 0; x < GRID_SIZE; x++) {
            grid[x][y].draw();
        }
    }
	
	// Show results if desired
	if (toggleResults) showResults();
}

void Grid::clearRect(int first_x, int first_y, int width, int height) {
    int last_x = first_x + width - 1;
    int last_y = first_y + height - 1;
    
    for(int y = first_y; y <= last_y; y++) {
        for(int x = first_x; x <= last_x; x++) {
            if(x != first_x) {
                grid[x][y].walls[DirectionWest] = false;
            }
            if(x != last_x) {
                grid[x][y].walls[DirectionEast] = false;
            }
            if(y != first_y) {
                grid[x][y].walls[DirectionNorth] = false;
            }
            if(y != last_y) {
                grid[x][y].walls[DirectionSouth] = false;
            }
        }
    }
}

void Grid::drawArc(int x_center, int y_center, double radius, double first_alpha, double last_alpha) {
    assert(first_alpha >= 0.0 && first_alpha <= 2 * M_PI);
    assert(last_alpha >= 0.0 && last_alpha <= 2 * M_PI);
    
    for(int y_relative = -radius; y_relative <= radius; y_relative++) {
        int y = y_center + y_relative;
        
        // stop if outside of grid
        if(y < 0 || y >= GRID_SIZE) {
            continue;
        }
        
        for(int x_relative = -radius; x_relative <= radius; x_relative++) {
            int x = x_center + x_relative;
            
            // stop if outside of grid
            if(x < 0 || x >= GRID_SIZE) {
                continue;
            }
            
            double alpha = std::atan2(y_relative, x_relative);
            if(alpha < 0) {
                alpha += 2 * M_PI;
            }
            
            // stop if outside of arc angle range
            if(last_alpha >= first_alpha) {
                if(alpha < first_alpha || alpha > last_alpha) {
                    continue;
                }
            } else {
                if(alpha < first_alpha && alpha > last_alpha) {
                    continue;
                }
            }
            
            // stop if outside of arc radius
            double distance = std::sqrt(std::pow(x_relative, 2) + std::pow(y_relative, 2));
            if(distance >= radius) {
                continue;
            }
            
            for(int direction = 0; direction < N_DIRECTIONS; direction++) {
                GridElement *neighbour = grid[x][y].neighbours[direction];
                if(neighbour == NULL) {
                    continue;
                }
                
                int x_neighbour_relative = neighbour->x - x_center;
                int y_neighbour_relative = neighbour->y - y_center;
                double neighbour_distance = std::sqrt(std::pow(x_neighbour_relative, 2) + std::pow(y_neighbour_relative, 2));
                
                // mark wall if neighbour is outside of arc radius
                if(neighbour_distance >= radius) {
                    grid[x][y].setWall((Direction)direction, true);
                }
            }
        }
    }


}

void Grid::setGoal() {
	// Set a random goal for the search algorithms
	goal = &grid[rand() % GRID_SIZE][rand() % GRID_SIZE];

	// Make sure the goal is marked on the grid
	goal->marked = true; 
} 

void Grid::showResults() {
	// Display the search results of all the search algorithms
	for (int search = 0; search < N_SEARCHES; search++) {
		results result = searchResults[search];
		
		ofSetColor(0, 100);
		ofDrawRectangle(ofGetWidth() - 180, 10+search*90, 170, 80);
		
		ofSetColor(result.goalReached ? ofColor(0,255,0):ofColor(255,0,0));
		ofDrawBitmapString(result.name,			ofGetWidth() - 170,	30 + search * 90);

		ofDrawBitmapString("Visited nodes: ",	ofGetWidth() - 170, 50 + search * 90);
		ofDrawBitmapString(result.visitedNodes, ofGetWidth() - 50,	50 + search * 90);

		ofDrawBitmapString("Shortest path: ",	ofGetWidth() - 170, 70 + search * 90);
		ofDrawBitmapString(result.shortestPath, ofGetWidth() - 50,	70 + search * 90);
	}
}