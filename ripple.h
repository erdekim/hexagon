
#ifndef RIPPLE_H_
#define RIPPLE_H_

#include "mapping.h"

enum RippleStrategy {
  RNG = 0,
  Clockwise = 1,
  CounterClockwise = 2,
};

enum Color {
  RED = 0,
  GREEN = 1,
  BLUE = 2,
};

class Ripple {

  private:

    int currentNode;
    int targetNode;

    // Distance 
    int distance;
    
    byte color[3];
    
    RippleStrategy rippleStrategy;
    
//    float speed; // Pixels / s
//    float drag;

    long lifespan; // Number of pixels 

    bool dead = true;

    int calculateNewNode() {
      int newNode;

      switch (rippleStrategy) {
        case RNG:
          
          break;
        case Clockwise:
          for(int i = 0; i < 6; i++) {
            if(nodeConnections[targetNode][i] == currentNode) {
 
                // i is the node we came from;
  
              for(int j = 1; j < 6; j++) {
                int tmpIndex = j + i;
                int tmpValue = nodeConnections[targetNode][(tmpIndex) % 6];
                if(tmpValue != -1) {
                  return tmpValue;
                }
              }
            }
          }
          break;
        case CounterClockwise:
          for(int i = 0; i < 6; i++) {
            if(nodeConnections[targetNode][i] == currentNode) {
 
                // i is the node we came from;
  
              for(int j = 1; j < 6; j++) {
                int tmpIndex = i - j;
                int tmpValue = nodeConnections[targetNode][(tmpIndex + 6) % 6];
                if(tmpValue != -1) {
                  return tmpValue;
                }
              }
            }
          }
          
          break;
      }

      
      return newNode;
    }
  public:

    Ripple() {
      
    }
  
    void start(int startingNode, int target, RippleStrategy strategy, Color c) {
      currentNode = startingNode;
      targetNode = target;
      rippleStrategy = strategy;

      dead = false;

      lifespan = 8 * 16;
      
      color[c] = 255;
    }
  
    boolean update(long deltaTime) {
      if(dead) {
        return true;
      }
      
      if(distance > 15) {
        int newNode = calculateNewNode();

        currentNode = targetNode;
        targetNode = newNode;

        distance = 0;
      }
      
      distance++;
      lifespan--;

      if(lifespan <= 0) {
        dead = true;
        return true;
      }

      return false;
    }

    int render(byte (*bytes)[15 * 30][3]) {
      if(dead) {
        return -1;
      }
      if(distance >= 15) {
        return -1;
      }
      
      int index = getLed(currentNode, targetNode, distance);
      if(index != -1) {
        for(int i = 0; i < 3; i++) {
          (*bytes)[index][i] = byte(max((*bytes)[index][i], color[i]));
        } 
      }
    }
};

#endif


