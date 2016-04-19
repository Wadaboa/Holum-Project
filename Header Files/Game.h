//
//
//  Project : Holum
//  File Name : Game.h
//  Date : 17/12/2015
//
//

#pragma once

class Game {
    private:
        void init();
    
    public:
        Game();
        MANAGER_STATUS gameEvents();
        vector<Drawable*> getObjectsVector();
};
