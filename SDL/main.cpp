//
//  main.cpp
//  SDL
//
//  Created by shiyu wang on 10/12/15.
//  Copyright © 2015 shiyu wang. All rights reserved.
//

#include <SDL2/SDL.h>

int main(int argc, const char * argv[]){
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        puts("SDL_Init error");
        return -1;
    } else {
        puts("SDL_Init success!");
        return 0;
    }
    
}