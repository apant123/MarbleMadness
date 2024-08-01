#include "Actor.h"
#include "StudentWorld.h"
#include <random>
#include <ctime>

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
  void Avatar::doSomething() {
     if(getWorld()->getLives() <= 0 ) {
         return;
     } else {
         int ch;
         if(getWorld()->getKey(ch)) {
             
             switch(ch) {
                 case KEY_PRESS_ESCAPE:
                     setHitpoints(0);
                     getWorld()->playSound(SOUND_PLAYER_DIE);
                     break;
                 case KEY_PRESS_SPACE: {
                     if(getAmmo() > 0) {
                         if(getDirection() == right) getWorld()->getGenericVector().push_back(new Pea(getX() + 1, getY(), getDirection(), getWorld()));
                         if(getDirection() == left) getWorld()->getGenericVector().push_back(new Pea(getX() - 1, getY(), getDirection(), getWorld()));
                         if(getDirection() == up) getWorld()->getGenericVector().push_back(new Pea(getX() , getY() + 1, getDirection(), getWorld()));
                         if(getDirection() == down) getWorld()->getGenericVector().push_back(new Pea(getX() , getY() - 1, getDirection(), getWorld()));
                         
                         //getWorld()->getGenericVector().push_back(new Pea(getX(), getY(), getDirection(), getWorld()));
                         getWorld()->playSound(SOUND_PLAYER_FIRE);
                         setAmmo(getAmmo() - 1);
                     }
                 }
                     break;
                 case KEY_PRESS_LEFT:
                     setDirection(left);
                     getWorld()->MarbleMoveTo(getDirection(),getX() -1 ,getY());
                     if(isEmpty(getX() - 1, getY()) == true) {
                         moveTo(getX()-1,getY());
                     }
                     break;
                 case KEY_PRESS_RIGHT:
                     setDirection(right);
                     getWorld()->MarbleMoveTo(getDirection(),getX() + 1 ,getY());
                     if(isEmpty(getX() + 1, getY()) == true) {
                         moveTo(getX()+1, getY());
                     }
                     break;
                 case KEY_PRESS_UP:
                     setDirection(up);
                     getWorld()->MarbleMoveTo(getDirection(),getX() ,getY() + 1);
                        if(isEmpty(getX(), getY() + 1) == true) {
                         moveTo(getX(), getY()+1);
                     }
                     break;
                 case KEY_PRESS_DOWN:
                     setDirection(down);
                     getWorld()->MarbleMoveTo(getDirection(),getX() ,getY() - 1);
                        if(isEmpty(getX(), getY() -1) == true) {
                         moveTo(getX(), getY()-1);
                     }
                     break;
             }
         }
     }
    
    
    
}

// void Avatar::isAttacked() {
//    
//    setHitpoints(getHitpoints() - 2); // m_hitpoints -= 2;
//    if(getHitpoints() > 0){
//        generic::getWorld()->playSound(SOUND_PLAYER_IMPACT);
//    } else{
//        // set avatar state to dead RIGHT HERE
//        generic::getWorld()->playSound(SOUND_PLAYER_DIE);
//        
//    }
//    
//}


//void Marble::isAttacked() {
//    setHitpoints(getHitpoints() - 2);
//}


bool Agent::isEmpty(int x, int y) {
    
    for(int i = 0; i < getWorld()->getGenericVector().size(); i++) {
        if(getWorld()->getGenericVector()[i]->getX() == x && getWorld()->getGenericVector()[i]->getY() == y && getWorld()->getGenericVector()[i]->canMoveOver() == false) {
            return false;
        }
    }
    return true;
    //return getWorld()->isEmpty(x, y);
}

bool generic::isMarbleAt(double x, double y) {
    if (getX() == x && getY() == y) return true; //THIS LINE RIGHT HERE HAS NO EFFECT ON THE CODE
    return false;
}

void Pea::doSomething() {
    if(isAlive() == false) {
        return;
    } else {
 
        if(broken != 0) {
            for(int i = 0; i < getWorld()->getGenericVector().size(); i++) {
                if(getWorld()->getGenericVector()[i]->getX() == getX() && getWorld()->getGenericVector()[i]->getY() == getY() && getWorld()->getGenericVector()[i]->isDamageable() == true) {
                    getWorld()->getGenericVector()[i]->PeaDamage();
                    setHitpoints(0);
                    
                }
            }
            
            if(getWorld()->returnP()->getX() == getX() && getWorld()->returnP()->getY() == getY()) {
                getWorld()->returnP()->PeaDamage();
                setHitpoints(0);
            }
 
        //moveTo(getX(), getY());moveTo(getX() + 1, getY());
        
        
       // if(getDirection() == right)  moveTo(getX() + 1, getY());

        
            int dir = getDirection();
            switch(dir) {
                case up:
                    moveTo(getX(), getY() + 1);
                    break;
                case down:
                    moveTo(getX(), getY() - 1);
                    break;
                case right:
                    moveTo(getX() + 1 , getY());
                    break;
                case left:
                    moveTo(getX() - 1, getY());
                    break;
            }
        
        
        //broken++;
        
        
        
            for(int i = 0; i < getWorld()->getGenericVector().size(); i++) {
                if(getWorld()->getGenericVector()[i]->getX() == getX() && getWorld()->getGenericVector()[i]->getY() == getY() && getWorld()->getGenericVector()[i]->isDamageable() == true) {
                    if(isAlive() == true){
                        getWorld()->getGenericVector()[i]->PeaDamage();
                        setHitpoints(0);
                    }
                }
            }
            
            if(getWorld()->returnP()->getX() == getX() && getWorld()->returnP()->getY() == getY()) {
                if(isAlive() == true) {
                    getWorld()->returnP()->PeaDamage();
                    setHitpoints(0);
                }
            }
            
        }

        
        broken++;
        
    }

}



void Avatar::PeaDamage() {
    setHitpoints(getHitpoints() - 2);
    if(isAlive() == true) {
        getWorld()->playSound(SOUND_PLAYER_IMPACT);
    } else {
        getWorld()->playSound(SOUND_PLAYER_DIE);
    }
}



void Crystal::doSomething() {
    if(isAlive() == false) {
        return;
    } else {
        if(getX() == getWorld()->returnP()->getX() && getY() == getWorld()->returnP()->getY()) {
            getWorld()->increaseScore(50);
            getWorld()->playSound(SOUND_GOT_GOODIE);
            setHitpoints(0);
            getWorld()->setCrystals(getWorld()->getCrystals() - 1);
            if(getWorld()->getCrystals() == 0) {
                getWorld()->playSound(SOUND_REVEAL_EXIT);
            }
            
        }
    
}
}
                             

void Pit::doSomething () {
    if(isAlive() == false) {
        return;
    } else {
        for(int i = 0; i < getWorld()->getGenericVector().size();i++) {
            if(getWorld()->getGenericVector()[i]->getX() == getX() && getWorld()->getGenericVector()[i]->getY() == getY() && getWorld()->getGenericVector()[i]->isaMarble() == true) {
                setHitpoints(0);
                getWorld()->getGenericVector()[i]->setHitpoints(0);
            }
        }
    }
}


void Exit::doSomething() {
    if(getWorld()->getCrystals() == 0) {
        //getWorld()->playSound(SOUND_REVEAL_EXIT);
        setVisible(true);
    }
    

    
    if(getX() == getWorld()->returnP()->getX() && getY() == getWorld()->returnP()->getY() && getWorld()->getCrystals() == 0) {
        getWorld()->playSound(SOUND_FINISHED_LEVEL);
        getWorld()->increaseScore(2000);
        getWorld()->setCrystals(-1);
        getWorld()->increaseScore(getWorld()->getBonus());
        
    }

}


void extraLifeGoodie::doSomething() {
    if(isAlive() == false){
        return;
    } else {
        
        if(getWorld()->returnP()->getX() == getX() && getWorld()->returnP()->getY() == getY()){
            getWorld()->increaseScore(1000);
            setHitpoints(0);
            getWorld()->playSound(SOUND_GOT_GOODIE);
            getWorld()->incLives();
            
        }
    }
            
}


void ammoGoodie::doSomething() {
    if(isAlive() == false) {
        return;
    } else {
        if(getWorld()->returnP()->getX() == getX() && getWorld()->returnP()->getY() == getY()){
            getWorld()->increaseScore(100);
            setHitpoints(0);
            getWorld()->playSound(SOUND_GOT_GOODIE);
            getWorld()->returnP()->setAmmo(getWorld()->returnP()->getAmmo() + 20);
            
        }
    }
}

void restoreHealthGoodie::doSomething() {
    if(isAlive() == false){
        return;
    } else {
        if(getWorld()->returnP()->getX() == getX() && getWorld()->returnP()->getY() == getY()){
            getWorld()->increaseScore(500);
            setHitpoints(0);
            getWorld()->playSound(SOUND_GOT_GOODIE);
            getWorld()->returnP()->setHitpoints(20);
            
        }
    }

}

bool Robot::moveonTick() {
    int ticks = (28 - getWorld()->getLevel()) / 4; // levelNumber is the current
     // level number (0, 1, 2, etc.)
    if (ticks < 3)
     ticks = 3; // no RageBot moves more frequently than this
    if(getWorld()->getTicks() % ticks == 0) return true;

    return false;
}

void Ragebot::doSomething() {
    if(isAlive() == false){
        return;
    }else {
        if(moveonTick() == true && sightClear() == true) {
            firePea();
        } else if(moveonTick() == true) {
            RobotMove();
        }
        
        
//        if(moveonTick() == true ) {
//            getWorld()->playSound(SOUND_GOT_GOODIE);
//        }
    }
}

void Robot::RobotMove() {
    if(getDirection() == right) {
        if(moveObjectAt(getX() + 1, getY()) == true) setDirection(left);
        else moveTo(getX() + 1, getY());
    }else if(getDirection() == left) {
        if(moveObjectAt(getX() - 1, getY()) == true) setDirection(right);
        else moveTo(getX() - 1, getY());
    } else if(getDirection() == up) {
        if(moveObjectAt(getX() , getY() + 1) == true) setDirection(down);
        else moveTo(getX() , getY() + 1);
    } else if(getDirection() == down) {
        if(moveObjectAt(getX() , getY() - 1) == true) setDirection(up);
        else moveTo(getX() , getY() - 1);
    }
}





bool Robot::sightClear() {
    if(  (getWorld()->returnP()->getX() == getX() || getWorld()->returnP()->getY() == getY()) &&  (sameDirection() == true && pathClear() == true )   ) {
        return true;
    }
    return false;
}

bool Robot::moveObjectAt(int x, int y) {
    for(int i = 0; i < getWorld()->getGenericVector().size(); i++) {
        if((getWorld()->getGenericVector()[i]->getX() == x && getWorld()->getGenericVector()[i]->getY() == y && getWorld()->getGenericVector()[i]->isRobotObstruction() == true) || (getWorld()->returnP()->getX() == x && getWorld()->returnP()->getY() == y))  {
            return true;
        }
    }
    return false;
}





bool Robot::sameDirection() {
    if(getX() == getWorld()->returnP()->getX()) {
        if(getDirection() == down && getY() > getWorld()->returnP()->getY()) return true;
        if(getDirection() == up && getY() < getWorld()->returnP()->getY()) return true;
    }
    
    if(getY() == getWorld()->returnP()->getY()) {
        if(getDirection() == right && getX() < getWorld()->returnP()->getX()) return true;
        if(getDirection() == left && getX() > getWorld()->returnP()->getX()) return true;
    }
    return false;
}

bool Robot::pathClear() {
    if(getX() == getWorld()->returnP()->getX()) {
        if(getDirection() == up) {
            int distance = getWorld()->returnP()->getY() - getY();
            for(int i = 1; i < distance; i++) {
                if(isObjectAt(getX(), getY() + i) == true) return false;
            }
        }
        if(getDirection() == down) {
            int distance = getY() - getWorld()->returnP()->getY();
            for(int i = 1; i < distance; i++) {
                if(isObjectAt(getX(), getY() - i) == true) return false;
            }
        }

    }
    if(getY() == getWorld()->returnP()->getY()) {
        
        if(getDirection() == right) {
            int distance = getWorld()->returnP()->getX() - getX();
            for(int i = 1; i < distance; i++) {
                if(isObjectAt(getX() + i, getY() ) == true) return false;
            }
        }

        if(getDirection() == left) {
            int distance = getX() - getWorld()->returnP()->getX();
            for(int i = 1; i < distance; i++) {
                if(isObjectAt(getX() - i, getY() ) == true) return false;
            }
            
        }
    }
   
    return true;
}

bool Robot::isObjectAt(int x, int y) {
    for(int i = 0; i < getWorld()->getGenericVector().size(); i++) {
        if(getWorld()->getGenericVector()[i]->getX() == x && getWorld()->getGenericVector()[i]->getY() == y && getWorld()->getGenericVector()[i]->RobotShootThrough() == false)  {
            return true;
        }
    }
    return false;
}

void Robot::firePea() {

    if(getDirection() == up) getWorld()->getGenericVector().push_back(new Pea(getX(), getY() + 1, getDirection(), getWorld()));
    if(getDirection() == down) getWorld()->getGenericVector().push_back(new Pea(getX(), getY() - 1, getDirection(), getWorld()));
    if(getDirection() == right) getWorld()->getGenericVector().push_back(new Pea(getX() + 1 , getY() , getDirection(), getWorld()));
    if(getDirection() == left) getWorld()->getGenericVector().push_back(new Pea(getX() - 1 , getY() , getDirection(), getWorld()));
    
    
    getWorld()->playSound(SOUND_ENEMY_FIRE);
    
}

//if(getDirection() == up) getWorld()->getGenericVector().push_back(new Pea(getX(), getY() + 1, getDirection(), getWorld()));
//if(getDirection() == down) getWorld()->getGenericVector().push_back(new Pea(getX(), getY() - 1, getDirection(), getWorld()));
//if(getDirection() == right) getWorld()->getGenericVector().push_back(new Pea(getX() + 1 , getY() , getDirection(), getWorld()));
//if(getDirection() == left) getWorld()->getGenericVector().push_back(new Pea(getX() - 1 , getY() , getDirection(), getWorld()));


void Ragebot::PeaDamage() {
    setHitpoints(getHitpoints() - 2);
    if(isAlive() == true) {
        getWorld()->playSound(SOUND_ROBOT_IMPACT);
    } else {
        setHitpoints(0); // redundent call but makes code clear.
        getWorld()->playSound(SOUND_ROBOT_DIE);
        getWorld()->increaseScore(100);
    }
}



bool ThiefBot::pickedGoodie() {
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10);

      // Generate a random number between 1 and 50
      int rand = dis(gen);
    
    for(int i = 0; i < getWorld()->getGenericVector().size(); i++) {
        if(getX() == getWorld()->getGenericVector()[i]->getX() && getY() == getWorld()->getGenericVector()[i]->getY() && getWorld()->getGenericVector()[i]->isAGoodie() == true) {
            if(rand == 1 && getnumItemsPickedUp() == 0) {
                if(getWorld()->getGenericVector()[i]->isAmmoGoodie() == true) {
                    typeGoodie = 0;
                    getWorld()->getGenericVector()[i]->setHitpoints(0);
                    getWorld()->playSound(SOUND_ROBOT_MUNCH);
                    setnumItemsPickedUp(1);
                    return true;
                }
                if(getWorld()->getGenericVector()[i]->isHealthGoodie() == true) {
                    typeGoodie = 1;
                    getWorld()->getGenericVector()[i]->setHitpoints(0);
                    getWorld()->playSound(SOUND_ROBOT_MUNCH);
                    setnumItemsPickedUp(1);
                    return true;
                }
                if(getWorld()->getGenericVector()[i]->isExtraLifeGoodie() == true) {
                    typeGoodie = 2;
                    getWorld()->getGenericVector()[i]->setHitpoints(0);
                    getWorld()->playSound(SOUND_ROBOT_MUNCH);
                    setnumItemsPickedUp(1);
                    return true;
                }
         
            }
            
          
            
        }
    }
    return false;
    
    //extraLife = 2;
    // Health = 1;
    // Ammo = 0;
}


void ThiefBot::RobotMove() {
//
//    static const int none = -1;
//      static const int right = 0;
//      static const int left = 180;
//      static const int up = 90;
//      static const int down = 270;

    static const int directions[] = {0, 90, 180, 270};
    static const int numDirections = sizeof(directions) / sizeof(directions[0]);

    // Seed the random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, numDirections - 1);

    // Generate a random index
    int directiontemp = directions[dis(gen)];
    
    int temp  = 0;
    bool tempbool = true;
   
    if(getCounter() < getDistanceTurn()) {
        if(getDirection() == right && moveObjectAt(getX() + 1, getY()) == false) {
            moveTo(getX() + 1, getY());
            tempbool = false;
        }
        else if(getDirection() == left && moveObjectAt(getX() - 1, getY()) == false) {
            moveTo(getX() - 1, getY());
            tempbool = false;
        }
        else if(getDirection() == up && moveObjectAt(getX(), getY() + 1) == false) {
            moveTo(getX(), getY() + 1 );
            tempbool = false;
        }
        else if(getDirection() == down && moveObjectAt(getX(), getY() - 1) == false) {
            moveTo(getX(), getY() - 1);
            tempbool = false;
        }
        else if(tempbool == true) temp = 5;
            
        
        tempbool = true;
       setCounter(getCounter() + 1);
        
        
        
    }
    
    if((temp == 5) || getCounter() >= getDistanceTurn() ) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 6);

        setDistanceTurn(dis(gen));
        temp = 0;
        
        bool tempright = true;
        bool templeft = true;
        bool tempup = true;
        bool tempdown = true;
        bool breakout = true;
        
        while(breakout == true) {
            if(directiontemp == right) {
                if(moveObjectAt(getX() + 1, getY()) == false) {
                    setDirection(right);
                    moveTo(getX() + 1, getY());
                    breakout = false;
                } else if(tempright == true) {
                    tempright = false;
                }
            }
            if(directiontemp == left) {
                if(moveObjectAt(getX() - 1, getY()) == false) {
                    setDirection(left);
                    moveTo(getX() - 1, getY());
                    breakout = false;
                } else if (templeft == true) {
                    templeft = false;
                }
            }
            if(directiontemp == up) {
                if(moveObjectAt(getX(), getY() + 1) == false) {
                    setDirection(up);
                    moveTo(getX(), getY() + 1);
                    breakout = false;
                } else if(tempup == true) {
                    tempup = false;
                }
            }
            if(directiontemp == down) {
                if(moveObjectAt(getX(), getY() - 1) == false) {
                    setDirection(down);
                    moveTo(getX(), getY() - 1);
                    breakout = false;
                } else if(tempdown == true) {
                    tempdown = false;
                }
            }
            if(tempup == false && tempdown == false && tempright == false && templeft == false) {
                breakout = false;
                if(directiontemp == right) setDirection(right);
                if(directiontemp == left) setDirection(left);
                if(directiontemp == up) setDirection(up);
                if(directiontemp == down) setDirection(down);
                //setDirection(directiontemp);
            }
            
            
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0, numDirections - 1);

            // Generate a random index
            directiontemp = directions[dis(gen)];
            
            setCounter(0);
        }
        
        
        
    }
    

//    if(getDirection() == right) {
//        if(moveObjectAt(getX() + 1, getY()) == true) setDirection(randomIndex);
//        else moveTo(getX() + 1, getY());
//    }else if(getDirection() == left) {
//        if(moveObjectAt(getX() - 1, getY()) == true) setDirection(randomIndex);
//        else moveTo(getX() - 1, getY());
//    } else if(getDirection() == up) {
//        if(moveObjectAt(getX() , getY() + 1) == true) setDirection(randomIndex);
//        else moveTo(getX() , getY() + 1);
//    } else if(getDirection() == down) {
//        if(moveObjectAt(getX() , getY() - 1) == true) setDirection(randomIndex);
//        else moveTo(getX() , getY() - 1);
//    }
//

}


void RegularThiefBot::doSomething() {
    
    if(isAlive() == false) {
        return;
    } else {
        if(moveonTick() == true) {
            if(pickedGoodie() == true) {}
            else {
                RobotMove();
            }
        }
    }
}


void RegularThiefBot::PeaDamage() {
    setHitpoints(getHitpoints() -2);
    
    if(isAlive() == true) {
        getWorld()->playSound(SOUND_ROBOT_IMPACT);
    }else {
        if(getTypeGoodie() == 0) getWorld()->getGenericVector().push_back(new ammoGoodie(getX(), getY(), getWorld()));
        if(getTypeGoodie() == 1) getWorld()->getGenericVector().push_back(new restoreHealthGoodie(getX(), getY(), getWorld()));
        if(getTypeGoodie() == 2) getWorld()->getGenericVector().push_back(new extraLifeGoodie(getX(), getY(), getWorld()));
        
        
        setHitpoints(0);
        getWorld()->playSound(SOUND_ROBOT_DIE);
        getWorld()->increaseScore(10);
    }
}


void MeanThiefBot::doSomething() {
    if(isAlive() == false) {
        return;
    }else {
        if(moveonTick() == true) {
            if(sightClear() == true) {
                firePea();
            }else if (pickedGoodie() == true){
                return;
            } else{
                RobotMove();
            }
        }
    }
}



void MeanThiefBot::PeaDamage() {
    setHitpoints(getHitpoints() -2);
    
    if(isAlive() == true) {
        getWorld()->playSound(SOUND_ROBOT_IMPACT);
    }else {
        if(getTypeGoodie() == 0) getWorld()->getGenericVector().push_back(new ammoGoodie(getX(), getY(), getWorld()));
        if(getTypeGoodie() == 1) getWorld()->getGenericVector().push_back(new restoreHealthGoodie(getX(), getY(), getWorld()));
        if(getTypeGoodie() == 2) getWorld()->getGenericVector().push_back(new extraLifeGoodie(getX(), getY(), getWorld()));
        
        
        setHitpoints(0);
        getWorld()->playSound(SOUND_ROBOT_DIE);
        getWorld()->increaseScore(20);
    }
}







bool ThiefBot::onSomeGoodie() {
    
    for(int i = 0; i < getWorld()->getGenericVector().size(); i++) {
        if(getWorld()->getGenericVector()[i]->getX() == getX() && getWorld()->getGenericVector()[i]->getY() == getY() && getWorld()->getGenericVector()[i]->isAGoodie() == true) {
            return true;
        }
    }
    return false;
    
}


int ThiefBotFactory::countTheifBots() {
    //const int VIEW_WIDTH    = 15;
    //const int VIEW_HEIGHT    = 15;
    int count = 0;
    
    for(int i = getX() - 3; i <= getX() + 3; i++) {
        for(int j = getY() - 3; j <= getY() + 3; j++) {
            for(int k = 0; k < getWorld()->getGenericVector().size(); k++) {
                if(i >= 0 && i < 15 && j >= 0 && j < 15) {
                    if(i == getWorld()->getGenericVector()[k]->getX() && j == getWorld()->getGenericVector()[k]->getY() && getWorld()->getGenericVector()[k]->isAThiefBot() == true) {
                        count++;
                    }
                }

            }
        }
    }
    return count;
}


bool ThiefBotFactory::TheifOnMe() {
    for(int i = 0; i < getWorld()->getGenericVector().size(); i++) {
        if(getWorld()->getGenericVector()[i]->getX() == getX() && getWorld()->getGenericVector()[i]->getY() == getY() && getWorld()->getGenericVector()[i]->isAThiefBot() == true) {
            return true;
        }
    }    
    return false;
}

//int bob = 0;
void ThiefBotFactory::doSomething() {
    if(m_factorytype == 1) {
//        std::srand(static_cast<unsigned int>(std::time(0)));
//
//        // Generate a random number between 1 and 50
//        int random_number = std::rand() % 50 + 1;
        
        std::random_device rd;
          std::mt19937 gen(rd());
          std::uniform_int_distribution<> dis(1, 50);

          // Generate a random number between 1 and 50
          int random_number = dis(gen);
    
        int x = countTheifBots();
        bool q  = TheifOnMe();
        if(x < 3 & q == false) { //x < 3 & q == false
            if(random_number == 5) { //random_number == 5
              
                    getWorld()->getGenericVector().push_back(new RegularThiefBot(getX(), getY(), getWorld()));
                    getWorld()->playSound(SOUND_ROBOT_BORN);

            }
        }
        
    }
    
    
    if(m_factorytype == 0) {
//        std::srand(static_cast<unsigned int>(std::time(0)));
//
//        // Generate a random number between 1 and 50
//        int random_number = std::rand() % 50 + 1;
        
        std::random_device rd;
          std::mt19937 gen(rd());
          std::uniform_int_distribution<> dis(1, 50);

          // Generate a random number between 1 and 50
          int random_number = dis(gen);
    
        int y = countTheifBots();
        bool w  = TheifOnMe();
        if(y < 3 & w == false) {
            if(random_number == 5) {
              
                    getWorld()->getGenericVector().push_back(new MeanThiefBot(getX(), getY(), getWorld()));
                    getWorld()->playSound(SOUND_ROBOT_BORN);

            }
        }
        
    }
    
}




