#include <iostream>
#include <SDL.h>


#include<string.h>
#include<SDL_image.h>

using namespace std;
SDL_Surface* Loadimage(string file_path)
{

    SDL_Surface* Loadimage = NULL;
    SDL_Surface*optimize_image = NULL;
    Loadimage = IMG_Load(file_path.c_str());
    if(Loadimage!=NULL){
        optimize_image = SDL_Displayformat(Loadimage);
        SDL_FreeSureface(Loadimage);
    }
    return optimize_image;
}
int main(int arc , char*argv[])
{
    SDL_Surface* screen = NULL;
    SDL_Surface* image = NULL;
    if(SDL_Init(SDL_INIT_EVERYTHING)==-1){
        return 1;
    }
    screen = SDL_SetVideoMode(1200 , 600 , 32 , SDL_SWSURFACE);
    image = Loadimage("bkground.png");
    SDL_SlitSurface(image,NULL,screen,NULL);
    SDL_Flip(screen);
    SDL_Delay(5000);
    SDL_FreeSurface(image);
    SDL_Quit();



    return 0;

}
