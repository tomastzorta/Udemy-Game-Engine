//
// Created by Tomas Tzorta on 07/12/2023.
//

#ifndef GAMEAPPLICATION_H
#define GAMEAPPLICATION_H

#include "LabyrinthFramework/Application.h"
#include "LabyrinthFramework/Core.h"

namespace labyrinth_engine
{
    class PlayerSpaceship;

    class GameApplication : public Application
    {
    public:
        GameApplication();
        void Tick(float a_deltaTime) override;
    private:
        float m_counter;
        Wptr<PlayerSpaceship> testPlayerSpaceship;
    };
}



#endif //GAMEAPPLICATION_H
