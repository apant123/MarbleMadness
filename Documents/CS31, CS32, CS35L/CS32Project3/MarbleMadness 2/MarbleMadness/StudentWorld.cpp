
#include "StudentWorld.h"
#include "GameConstants.h"
#include "Level.h"
#include "Actor.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
   
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
    p = nullptr;
    m_bonus = 1000;
    m_crystals = 0;
    m_numticks = 0;
   // m_levelnum = 0;
}

int StudentWorld::init()
{
    
    loadLevel();
    
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{

    // This code is here merely to allow the game to build, run, and terminate after you type q
    
   
    for(int i = 0; i < m_generic.size(); i++) {
        setGameStatText(setDisplayText());

        if(p != nullptr && m_generic[i] != nullptr && p->isAlive() && m_generic[i]->isAlive()) {
            p->doSomething();
            m_generic[i]->doSomething();
            //p->doSomething();
            
            if(p->isAlive() == false) {
                m_bonus = 1000;
                decLives();
                setCrystals(0);
                m_numticks = 0;
                return GWSTATUS_PLAYER_DIED;
            }
            
            if(getLevel() == 3 && getCrystals() == -1) return GWSTATUS_PLAYER_WON;
            if(getCrystals() == -1)  {
                //advanceToNextLevel();
               // m_levelnum++;
                setCrystals(0);
                m_numticks = 0;
                m_bonus = 1000;
                
                return GWSTATUS_FINISHED_LEVEL;
            }
        }
   
    }

    
    
    
    
    removeDeadGameObjects();
    m_bonus--;
    m_numticks++;
    
    if(getCrystals() == -1)  {
        //advanceToNextLevel();
        //m_levelnum++;
        setCrystals(0);
        m_numticks = 0;
        return GWSTATUS_FINISHED_LEVEL;
    }
    
    
    
    
    
    
	return GWSTATUS_CONTINUE_GAME;
}

StudentWorld::~StudentWorld() {
    cleanUp();
  
}


void StudentWorld::cleanUp()
{
    for(int i = 0; i < m_generic.size(); i++) {
        if(m_generic[i] != nullptr && m_generic[i]->getWorld() != NULL) {
            delete m_generic[i];
            m_generic[i] = nullptr;
        }
    }
    if(p != nullptr) {
        delete p;
        p = nullptr;
    }
    
    m_generic.clear();
   
}


int StudentWorld::getBonus() {
    if(m_bonus <= 0) m_bonus = 0;
    return m_bonus;
}


string StudentWorld::setDisplayText() {
    int score = getScore();
    int level = getLevel();
    unsigned int bonus = getBonus(); // getBonus();
    int livesLeft = getLives();
    double health = p->getHitpoints() / 20.0 * 100;
    int ammo = p->getAmmo();
    
    ostringstream oss;
    oss.fill('0');
    oss << "Score: " << setw(7) << score <<  "  ";
    oss << "Level: " << setw(2) << level <<  "  ";
    oss.fill(' ');
    oss << "Lives: " << setw(2) << livesLeft << "  ";
    oss << "Health: " << setw(3) << health << "%  ";
    oss << "Ammo: " << setw(3) << ammo << "  ";
    oss << "Bonus: " << setw(4) << bonus << "  ";
    
    string s = oss.str();
    
    return s;
}


void StudentWorld::loadLevel() {
    
    Level lev(assetPath());
    Level::LoadResult result = lev.loadLevel("level00.txt");
    
    if(getLevel() == 1)  result = lev.loadLevel("level01.txt");
    if(getLevel() == 2)  result = lev.loadLevel("level02.txt");
    if(getLevel() == 3)  result = lev.loadLevel("level03.txt");

        
        //result = lev.loadLevel("level04.txt");
    //if(getLevel() == 5) return GWSTATUS_PLAYER_WON;
    
    


    
    
    if (result == Level::load_fail_file_not_found)
    cerr << "Could not find level00.txt data file\n";
    else if (result == Level::load_fail_bad_format)
    cerr << "Your level was improperly formatted\n";
    
    else if (result == Level::load_success)
    {
    cerr << "Successfully loaded level\n";
    
        
        for(int i = 0; i < VIEW_WIDTH; i++) {
            for(int j = 0; j < VIEW_HEIGHT; j++) {
         
                Level::MazeEntry ge = lev.getContentsOf(i,j);
                switch (ge)
                {
                case Level::empty:
                       
                        break;
                case Level::exit:
                        m_generic.push_back(new Exit(i,j,this));
                        break;
                case Level::player:
                        p = new Avatar(i,j,this);
                        break;
                case Level::horiz_ragebot:
                        m_generic.push_back(new Ragebot(i,j,Agent::right,this));
                        break;
                case Level::vert_ragebot:
                        m_generic.push_back(new Ragebot(i,j,Agent::down,this));
                        break;
                case Level::thiefbot_factory:
                        m_generic.push_back(new ThiefBotFactory(i,j, 1, this));
                        break;
                case Level::mean_thiefbot_factory:
                        m_generic.push_back(new ThiefBotFactory(i,j, 0, this));
                        break;
                case Level::wall:
                        m_generic.push_back(new Wall(i,j,this));
                        break;
                    case Level::marble:
                        m_generic.push_back(new Marble(i,j,this));
                        break;
                    case Level::pit:
                        m_generic.push_back(new Pit(i,j,this));
                        break;
                    case Level::crystal:
                        m_generic.push_back(new Crystal(i,j, this));
                        m_crystals++;
                        break;
                    case Level::restore_health:
                        m_generic.push_back(new restoreHealthGoodie(i,j,this));
                        break;
                    case Level::extra_life:
                        m_generic.push_back(new extraLifeGoodie(i,j,this));
                        break;
                    case Level::ammo:
                        m_generic.push_back(new ammoGoodie(i,j,this));
                        break;
                }
                }
                
            }
        
        
        
        }

    }
    

bool StudentWorld::isEmpty(int x, int y) {
    for(int i = 0; i < m_generic.size(); i++) {
        if(m_generic[i]->getX() == x && m_generic[i]->getY() == y && m_generic[i]->isAPit() == false) {
            return false;
        }
    }
    return true;
}


void StudentWorld::MarbleMoveTo(int dir, double x, double y) {
    
    for(int i = 0; i < m_generic.size(); i++) {
        if(m_generic[i]->isaMarble() && m_generic[i]->getX() == x && m_generic[i]->getY() == y) {
            
            switch(dir) {
                case Agent::up:
                    if(isEmpty(x, y + 1)) {
                        m_generic[i]->moveTo(x, y + 1);
                    }
                    break;
                case Agent::down:
                    if(isEmpty(x, y - 1)) {
                        m_generic[i]->moveTo(x, y - 1);
                    }
                    break;
                case Agent::right:
                    if(isEmpty(x + 1, y)) {
                        m_generic[i]->moveTo(x + 1, y);
                    }
                    break;
                case Agent::left:
                    if(isEmpty(x - 1, y)){
                        m_generic[i]->moveTo(x - 1, y);
                        break;
                    }
            }
            
        }
    }
}

void StudentWorld::removeDeadGameObjects() {
    for(int i = 0; i < m_generic.size(); i++) {
        if(m_generic[i] != nullptr && m_generic[i]->isAlive() == false) {
            delete m_generic[i];
            m_generic[i] = nullptr;
            for(int j = i; j < m_generic.size() - 1; j++) {
                m_generic[j] = m_generic[j+1];
            }
            m_generic.resize(m_generic.size() - 1);
        }
    }
}

