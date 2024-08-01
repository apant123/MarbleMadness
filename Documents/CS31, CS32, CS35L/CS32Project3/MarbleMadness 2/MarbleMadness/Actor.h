#ifndef ACTOR_H_
#define ACTOR_H_


#include "StudentWorld.h"
#include "GraphObject.h"
#include <cstdlib> // Required for rand() and srand()
#include <random>
#include <ctime>

class generic : public GraphObject {
    
public:
    generic(int ImageID, double startX, double startY, int dir, double hitpoints, StudentWorld* world)
     : GraphObject(ImageID, startX, startY, dir)
    {
        m_hitpoints = hitpoints;
        m_world = world;
        setVisible(true);
    }
    virtual void doSomething() = 0;
//    virtual void isAttacked() = 0; // this doesnt do anything, its never called. Pea Damage is the one thats gonna get called, use that and clean Pea Damage UP
    virtual bool isAlive() {return getHitpoints() > 0;};
    virtual int getHitpoints() {return m_hitpoints;}
    virtual void setHitpoints(int num) {m_hitpoints = num;}
    virtual bool isMarbleAt(double x, double y);
    StudentWorld* getWorld() {return m_world;}
    virtual bool isaMarble()  {return false;}
    virtual void PeaDamage() = 0;
    virtual bool isDamageable() {return false;}
    virtual bool canMoveOver() {return false;}
    virtual bool isAPit() {return false;}
    virtual bool RobotShootThrough() {return true;}
    virtual bool isRobotObstruction() {return false;}
    virtual bool isAGoodie() {return false;}
    virtual bool isAThiefBot() {return false;}
    virtual bool isAmmoGoodie() {return false;}
    virtual bool isHealthGoodie() {return false;}
    virtual bool isExtraLifeGoodie() {return false;}
    
    
private:
    StudentWorld* m_world;
    int m_hitpoints;
};


class Agent: public generic {
public:
    Agent(int ImageID, double startX, double startY, int dir, double hitpoints, StudentWorld* world):generic(ImageID, startX, startY, dir, hitpoints, world) {}
    bool isEmpty(int x, int y);
    virtual void PeaDamage() = 0;
//    virtual void isAttacked() = 0;
    virtual void doSomething() = 0;
    virtual bool isDamageable() {return true;}
    virtual bool isRobotObstruction() {return true;}
};

class Robot: public Agent {
public:
    Robot(int ImageID, double startX, double startY, int dir, double hitpoints, StudentWorld* world):Agent(ImageID, startX, startY, dir, hitpoints, world) {}
    virtual void PeaDamage() = 0;
//    virtual void isAttacked() = 0;
    virtual void doSomething() = 0;
    virtual void firePea();
    virtual bool sameDirection();
    virtual void RobotMove();
    
    
    virtual bool RobotShootThrough() {return false;}
    virtual bool sightClear();
    virtual bool pathClear();
    virtual bool moveonTick();
    virtual bool isObjectAt(int x, int y);
    virtual bool moveObjectAt(int x, int y);
    
    
    
    
    
};

class ThiefBot: public Robot {
public:
    ThiefBot(int ImageID, double startX, double startY, int dir, double hitpoints, StudentWorld* world):Robot(ImageID, startX, startY, dir, hitpoints, world){

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 6);

          // Generate a random number between 1 and 50
        m_distanceTurn = dis(gen);
        numItemsPickedUp = 0;
        typeGoodie = - 1;
        counter = 0;
        
    }
                                                                                                              
    
//    virtual void isAttacked() = 0;
    virtual void doSomething() = 0;
    virtual void PeaDamage() = 0;
    virtual bool onSomeGoodie();
    virtual bool isAThiefBot() {return true;}
    virtual bool pickedGoodie();
    virtual void RobotMove();
    
    
    
    virtual int getTypeGoodie() {return typeGoodie;}
    virtual int getCounter() {return counter;}
    virtual void setCounter(int set) {counter = set;}
    virtual int getDistanceTurn() {return m_distanceTurn;}
    virtual void setDistanceTurn(int set) {m_distanceTurn = set;}
    virtual int getnumItemsPickedUp() {return numItemsPickedUp;}
    virtual void setnumItemsPickedUp(int set) {numItemsPickedUp = set;}
    
private:
    int typeGoodie;
    int m_distanceTurn;
    int counter;
    int numItemsPickedUp;
};


class MeanThiefBot: public ThiefBot {
public:
    MeanThiefBot(double startX, double startY, StudentWorld* world): ThiefBot(IID_MEAN_THIEFBOT, startX, startY, right, 8, world){}
//    virtual void isAttacked() {};
    virtual void doSomething() ;
    virtual void PeaDamage();
    
};






class RegularThiefBot: public ThiefBot {
public:
    RegularThiefBot(double startX, double startY, StudentWorld* world): ThiefBot(IID_THIEFBOT, startX, startY, right, 5, world) {}
    
    virtual void PeaDamage();
//    virtual void isAttacked() {}
    virtual void doSomething();
    virtual bool isDamageable() {return true;}
    
};




class Ragebot: public Robot {
public:
    Ragebot(double startX, double startY, int direction, StudentWorld* world): Robot(IID_RAGEBOT, startX, startY, direction, 10, world ) {}
    
    
    virtual void PeaDamage();
//    virtual void isAttacked() {}
    virtual void doSomething();
    
   
    
};

class ThiefBotFactory:public generic {
public:
    ThiefBotFactory(double startX, double startY, int factorytype, StudentWorld* world): generic(IID_ROBOT_FACTORY, startX, startY, none, 1, world) {
        
        m_factorytype = factorytype;
    }
    // 1 is regular thief bot
    // 0 is mean thief bot
    
    virtual void PeaDamage() {}
//    virtual void isAttacked() {}
    virtual void doSomething();
    virtual bool RobotShootThrough() {return false;}
    virtual bool isDamageable() {return true;}
    virtual bool isRobotObstruction() {return true;}
    
protected:
    virtual int countTheifBots();
    bool TheifOnMe();
    
    
private:
    int m_factorytype;
    
};













class Avatar: public Agent {
public:
    Avatar(double startX, double startY, StudentWorld* world): Agent(IID_PLAYER, startX, startY, right, 20, world) {
        m_ammo = 20;
        //m_hitpoints = 20;
    
        //setVisible(true);
        
    }
    
    virtual void doSomething();
//    virtual void isAttacked() {};
    int getAmmo() {return m_ammo;}
    int setAmmo(int set) {return m_ammo = set;}
//    int getHitpoints() {return m_hitpoints;}
    virtual void PeaDamage();
    virtual bool isRobotObstruction() {return true;}
   
private:
    int m_ammo;
    //int m_hitpoints;
 
};


class Wall: public generic {
public:
    Wall(double startX, double startY, StudentWorld* world): generic(IID_WALL, startX, startY, none, 1, world) {
        //setVisible(true);
    }
    virtual void doSomething() {};
//    virtual void isAttacked() {};
    virtual void PeaDamage() {}
    virtual bool isDamageable() {return true;}
    virtual bool RobotShootThrough() {return false;}
    virtual bool isRobotObstruction() {return true;}
    
};


class Marble: public generic {
public:
    Marble(double startX, double startY, StudentWorld* world): generic(IID_MARBLE, startX, startY, none, 10 , world) {
        //m_hitpoints = 10;
   
    }
    virtual void doSomething() {};
//    virtual void isAttacked() {};
    virtual bool isaMarble() {return true;}
    virtual void PeaDamage() {setHitpoints(getHitpoints() - 2);}
    virtual bool isDamageable() {return true;}
    virtual bool RobotShootThrough() {return false;}
    virtual bool isRobotObstruction() {return true;}
};


class Pea: public generic {
public:
    Pea(double startX, double startY, int direction, StudentWorld* world): generic(IID_PEA, startX, startY, direction, 1, world) {
        broken = 0;
    }
    
    
    virtual void doSomething();
//    virtual void isAttacked() {};
    virtual void PeaDamage() {}
    
private:
    int broken = 0;
};

class pickableItem: public generic {
public:
pickableItem(int ImageID, double startX, double startY, int dir, double hitpoints, StudentWorld* world):generic(ImageID, startX, startY, dir, hitpoints, world) {}
    
    virtual void doSomething() = 0;
    virtual void PeaDamage() {}
//    virtual void isAttacked() {}
    virtual bool canMoveOver() {return true;}
    
};

class goodie: public pickableItem {
public:
    goodie (int ImageID, double startX, double startY, int dir, double hitpoints, StudentWorld* world):pickableItem(ImageID, startX, startY, dir, hitpoints, world) {}
    virtual void doSomething() = 0;
    virtual bool isAGoodie() {return true;}
    
};

class extraLifeGoodie: public goodie {
public:
    
    extraLifeGoodie(double startX, double startY, StudentWorld* world):goodie(IID_EXTRA_LIFE, startX, startY, none, 1, world) {}
    virtual void doSomething();
    virtual bool isExtraLifeGoodie() {return true;}
   
};

class ammoGoodie:public goodie {
public:
    ammoGoodie(double startX, double startY, StudentWorld* world): goodie(IID_AMMO, startX, startY, none, 1, world) {}
    virtual void doSomething();
    virtual bool isAmmoGoodie() {return true;}
};

class restoreHealthGoodie: public goodie {
public:
    restoreHealthGoodie(double startX, double startY, StudentWorld* world): goodie(IID_RESTORE_HEALTH, startX, startY, none, 1, world){}
    virtual void doSomething();
    virtual bool isHealthGoodie() {return true;}
};



class Crystal: public pickableItem {
public:
    Crystal(double startX, double startY, StudentWorld* world): pickableItem(IID_CRYSTAL, startX, startY, none, 1, world) {
    }
    
    virtual void doSomething();
//    virtual void isAttacked() {};
    virtual void PeaDamage() {}
    virtual bool canMoveOver() {return true;}
    // void setCrystals(int set) {m_crystals = set;}
     //int getCrystals() {return m_crystals;}
    
//private:
//   int m_crystals;
};

class Pit: public generic {
public:
    Pit(double startX, double startY, StudentWorld* world): generic(IID_PIT, startX, startY, none, 1, world) {}
    
    virtual void doSomething();
//    virtual void isAttacked() {};
    virtual void PeaDamage() {}
    virtual bool isAPit() {return true;}
    virtual bool isRobotObstruction() {return true;}
    
};

class Exit: public generic{
public:
    Exit(double startX, double startY, StudentWorld* world): generic(IID_EXIT, startX, startY, none, 1, world) {
        setVisible(false);
    }
    
    virtual void doSomething();
//    virtual void isAttacked() {};
    virtual void PeaDamage() {}
    bool canMoveOver() {return true;}
    
};




#endif // ACTOR_H_







// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp



/*
 
 GraphObject(int imageID, double startX, double startY, int dir = 0, double size = 1.0)
  : m_imageID(imageID), m_visible(true), m_x(startX), m_y(startY),
    m_destX(startX), m_destY(startY), m_brightness(1.0),
    m_animationNumber(0), m_direction(dir), m_size(size)
 {
     if (m_size <= 0)
         m_size = 1;

     getGraphObjects().insert(this);
     setVisible(true);
 }
 */


/*

 GraphObject(int imageID, double startX, double startY, int dir = 0, double size = 1.0)
  : GraphObject(imageID), GraphObject(true), GraphObject(startX), GraphObject(startY),
 GraphObject(startX), GraphObject(startY), GraphObject(1.0),
 GraphObject(0), GraphObject(dir), GraphObject(size)
 {
     if (m_size <= 0)
         m_size = 1;

     getGraphObjects().insert(this);
     setVisible(true);
 }
 
 

*/

//GraphObject(int imageID, double startX, double startY, int dir = 0, double size = 1.0)




