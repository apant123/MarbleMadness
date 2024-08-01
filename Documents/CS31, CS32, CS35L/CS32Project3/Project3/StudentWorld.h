


#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"

#include <string>
#include <vector>
using namespace std;

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class generic;
class Avatar;
class StudentWorld : public GameWorld
{
public:
  StudentWorld(std::string assetPath);
  virtual ~StudentWorld();
  virtual int init(); // construct a data structure to store all actors. Use pointer of vectors
  virtual int move();
  virtual void cleanUp();
  string setDisplayText();
  int getBonus();
  void loadLevel();
  Avatar* returnP() {return p;}
  bool isEmpty(int x, int y);
  void MarbleMoveTo(int dir, double x, double y);
  vector<generic*>& getGenericVector() {return m_generic;}
  void removeDeadGameObjects();
  int getCrystals() {return m_crystals;}
  void setCrystals(int set) {m_crystals = set;}
  int getTicks() {return m_numticks;}
  void setTicks(int num) {m_numticks = num;}
    
    
    
private:
    vector<generic*> m_generic;
    Avatar* p;
    int m_bonus;
    int m_crystals;
    int m_numticks;
   // int m_levelnum;
};





#endif // STUDENTWORLD_H_



