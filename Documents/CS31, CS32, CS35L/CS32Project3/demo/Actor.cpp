#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"

Valentine::Valentine(StudentWorld* sw, int x, int y)
 : GraphObject(IID_EXTRA_LIFE, x, y), m_world(sw)
{
}

void Valentine::doSomething()
{
    int key;
    if (m_world->getKey(key))
    {
        if (key == KEY_PRESS_SPACE)
        	m_world->playSound(SOUND_GOT_GOODIE);
    }
}
