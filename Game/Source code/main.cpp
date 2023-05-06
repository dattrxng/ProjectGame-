#include "mainwindow.h"
#include "font.h"
#include "texture.h"
#include "field.h"
#include "snake.h"
#include "music.h"

#include <SDL.h>

#include <iostream>
#include <chrono>
#include <string>

constexpr static int WIDTH  = 640;
constexpr static int HEIGHT = 480;

int main(int argc, char* args[])
{
    using namespace std::chrono;


    MainWindow win(WIDTH, HEIGHT, "Snaky");
    win.set_icon("apple.png");


    Font font ("lazy.ttf", 18);
    Texture title (win);
    title.loadFromRenderedText("An nhieu nhat co the.", font, SDL_Color{0xFF,0,0,0xFF});


    auto avail_height = win.get_height() - (title.get_height()*2);
    Field field(WIDTH, avail_height, win);

    Snake snake(&field, 0);


    field.add_random_fruit();
    field.add_random_fruit();


    Music music ("1.mp3");
    music.play();

    auto t1 = steady_clock::now();
    SDL_Event e;
    auto score1 = 0;
    bool quit = false;
    while (!quit) {

        while( SDL_PollEvent( &e ) != 0 ) {

            if( e.type == SDL_QUIT ) {
                quit = true;
            }

            snake.handle_event(e);
        }


        auto s2 = steady_clock::now();
        auto duration2 = duration_cast<seconds>( s2 - t1 ).count();
        if (duration2 > 10) {
            field.add_random_obstacle(snake.get_coordinate());
            t1 = s2;
        }


        auto score2 = snake.score();
        if (score2 > score1) {
            title.loadFromRenderedText("An nhieu nhat co the. Score: " + std::to_string(snake.score()), font, SDL_Color{0xFF,0,0,0xFF});
            score1 = score2;
        }



        if(!snake.make_move()) {
            Texture t (win);
            t.loadFromRenderedText("BAN DA THUA!!! Score: " + std::to_string(snake.score()), font, SDL_Color{0xFF,0,0,0xFF});
            win.clear();
            t.render(( win.get_width() - t.get_width() ) / 2, ( win.get_height() - t.get_height() ) / 2 );
            win.update();

            SDL_Delay(5000);
            break;
        }



        win.clear();

        title.render( ( win.get_width() - title.get_width() ) / 2, ( title.get_height() ) / 2 );
        field.render(0, title.get_height()*2, &snake);

        win.update();


        SDL_Delay(100);
    }

    return 0;
}
