//
//  main.cpp
//  Room
//
//  Created by Yue Huang on 2014-04-08.
//  Copyright (c) 2014 Yue Huang. All rights reserved.
//

#include <OpenGL/OpenGL.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GLUT/GLUT.h>
#include <stdio.h>
#include <string>
#include "mainRoom.h"
#include "timer.h"
#include "instance.h"
//Minimum Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main( int argc, char* args[] ){
    SDL_Window* gWindow = NULL;
    SDL_GLContext gContext;
    
    bool init_sucess = true;
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		init_sucess = false;
	}else{
		//Use OpenGL 2.1
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
        
		//Create window
		gWindow = SDL_CreateWindow( "Room", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
		if( gWindow == NULL ){
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			init_sucess = false;
		}else{
			//Create context
			gContext = SDL_GL_CreateContext( gWindow );
			if( gContext == NULL ){
				printf( "OpenGL context could not be created! SDL Error: %s\n", SDL_GetError() );
				init_sucess = false;
			}else{
				//Use Vsync
				if( SDL_GL_SetSwapInterval( 1 ) < 0 ) printf( "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError() );
				
                //Initialize OpenGl
                {
                    glEnable(GL_TEXTURE_2D);
                    glShadeModel(GL_SMOOTH);
                    
                    glMatrixMode(GL_PROJECTION);
                    glLoadIdentity();
                    glOrtho(0,SCREEN_WIDTH,SCREEN_HEIGHT,0,-1,1);
                    glMatrixMode(GL_MODELVIEW);
                    glLoadIdentity();
                }
			}
		}
	}
    
	//Start up SDL and create window
	if(!init_sucess) printf( "Failed to initialize!\n" );
	else{
		//Main loop flag
		bool quit = false;
//				SDL_StartTextInput();
        Instance::get().load_all();
        MainRoom * main_room = new MainRoom();
        //Handle events on queue
        SDL_Event event;
		//While application is running
		while( !quit ){
			
			while ( SDL_PollEvent( &event )!= 0){
				//Don't break until we get the event we want...
                
				if( event.type == SDL_QUIT ){
					quit = true;
                    break;
				}else if(event.type == SDL_MOUSEBUTTONDOWN){
                    main_room->update(event);
                    break;
                }
			}
            
            glClear(GL_COLOR_BUFFER_BIT);
            main_room->render();
            SDL_GL_SwapWindow( gWindow );
		}
        delete main_room;
        Instance::get().clean_all();
		//Disable text input SDL_StopTextInput();
	}
    
	//Close and free
//    SDL_GL_DeleteContext(gContext);
    SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
	return 0;
}