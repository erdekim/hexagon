#ifndef MAPPING_H_
#define MAPPING_H_

#define EDGES 30
#define NODES 19


struct Node;
struct Edge;
struct Graph;

int* createLedIndex(int number, bool ascending);




// This array contains an entry for each node in the hexagon, there are 19 total.
// They are ordered top down, and left to right.

// The smaller arrays contain the node connected to any of the 6 directions. 
// The first index is straight up, and then it moves clockwise.
// If the value is -1, no node is connected in that direction
int nodeConnections[19][6] = {
  {-1, -1, 2, -1, 1, -1},
  {-1, 0, 4, 6, 3, -1},
  {-1, -1, 5, 7, 4, 0},
  {-1, 1, -1, 8, -1, -1},
  {-1, 2, -1, 9, -1, 1},
  {-1, -1, -1, 10, -1, 2},
  {1, -1, 9, -1, 8, -1},
  {2, -1, 10, -1, 9, -1},
  {3, 6, 11, 13, -1, -1},
  {4, 7, 12, 14, 11, 6},
  {5, -1, -1, 15, 12, 7},
  {-1, 9, -1, 16, -1, 8},
  {-1, 10, -1, 17, -1, 9},
  {8, -1, 16, -1, -1, -1},
  {9, -1, 17, -1, 16, -1},
  {10, -1, -1, -1, 17, -1},
  {11, 14, 18, -1, -1, 13},
  {12, 15, -1, -1, 18, 14},
  {-1, 17, -1, -1, -1, 16}, 
};

int edges[30][2] = {
  {0, 1},
  {0, 2},
  {1, 3},
  {1, 4},
  {1, 6},
  {2, 4},
  {2, 5},
  {2, 7},
  {3, 8},
  {4, 9},
  {5, 10},
  {6, 8},
  {6, 9}, // nice
  {7, 9},
  {7, 10},
  {8, 11},
  {8, 13},
  {9, 11},
  {9, 12},
  {9, 14},
  {10, 12},
  {10, 15},
  {11, 16},
  {12, 17},
  {13, 16},
  {14, 16},
  {14, 17},
  {15, 17},
  {16, 18},
  {17, 18},
};


// Maps the led indices to the edges
// First: top most index
// Second: Bottom most index
int ledIndices[30][2] = {
  {239, 225}, // [0, 1] - 15
  {240, 254}, // [0, 2] - 16
  {149, 135}, // [1, 3] - 9
  {224, 210}, // [1, 4] - 14
  {150, 164}, // [1, 6] - 10
  {255, 269}, // [2, 4] - 17
  {270, 284}, // [2, 5] - 18
  {329, 315}, // [2, 7] - 21
  {134, 120}, // [3, 8] - 8
  {209, 195}, // [4, 9] - 13
  {285, 299}, // [5, 10] - 19
  {165, 179}, // [6, 8] - 11
  {180, 194}, // [6, 9] - 12
  {330, 344}, // [7, 9] - 22
  {314, 300}, // [7, 10] - 20
  {105, 119}, // [8, 11] - 7
  {104, 90},  // [8, 13] - 6
  {45, 59},   // [9, 11] - 3
  {345, 359}, // [9, 12] - 23
  {44, 30},   // [9, 14] - 2
  {374, 360}, // [10, 12] - 24
  {375, 389}, // [10, 15] - 25
  {60, 74},   // [11, 16] - 4
  {419, 405}, // [12, 17] - 27
  {89, 75},   // [13, 16] - 5
  {29, 15},   // [14, 16] - 1
  {434, 420}, // [14, 17] - 28
  {390, 404}, // [15, 17] - 26
  {14, 0},    // [16, 18] - 0
  {435, 449}, // [17, 18] - 29
};

int getLed(int fromNode, int toNode, int distance) {
  int retVal; 
  
  int minNode = min(fromNode, toNode);
  int maxNode = max(fromNode, toNode);

  bool descending = fromNode < toNode;
 
  int edgeIndex = -1;

  for(int i = 0; i < 30; i++) {
    if(edges[i][0] == minNode && edges[i][1] == maxNode) {

      edgeIndex = i;
      break;
    }
  }


  bool edgeDescending= ledIndices[edgeIndex][0] < ledIndices[edgeIndex][1]; 

  int topIndex = ledIndices[edgeIndex][0];
  int bottomIndex = ledIndices[edgeIndex][1];

  if(descending && edgeDescending) {
    retVal = topIndex + distance;  
  } else if (!descending && edgeDescending) {
    retVal = bottomIndex - distance;
  } else if (descending && !edgeDescending) {
    retVal = topIndex - distance;
  } else if (!descending && !edgeDescending) {
    retVal = bottomIndex + distance;
  }

  return retVal;
}



int centerIndex = 9;

int numberOfCubeNodes = 6;
int cubesNodes[] = {4, 7, 12, 14, 11, 6};

int numberOfEdgeNodes = 12;
int edgeNodes[] = {0, 2, 5, 10, 15, 17, 18, 16, 13, 8, 3, 1};

#endif

