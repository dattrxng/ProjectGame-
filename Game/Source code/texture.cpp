#include "texture.h"
#include "exception.h"

#include <SDL_image.h>
#include <SDL_ttf.h>

Texture::Texture(MainWindow& m)
    : mTexture{nullptr}, gRenderer{m.get_renderer()}, mWidth{0}, mHeight{0} {}

Texture::~Texture()
{

    free();
}

bool Texture::loadFromFile( const std::string& path )
{

    free();

    SDL_Texture* newTexture = nullptr;


    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == nullptr ) {
        throw SnakeException(std::string("Unable to load image ") + path + " : " + IMG_GetError());
    }

    SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0xFF, 0xFF, 0xFF ) );


    newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
    if( newTexture == nullptr ) {
        throw SnakeException(std::string("Unable to create texture from ") + path + " : " + SDL_GetError());
    }

    mWidth = loadedSurface->w;
    mHeight = loadedSurface->h;


    SDL_FreeSurface( loadedSurface );

    mTexture = newTexture;
    return mTexture != nullptr;
}

bool Texture::loadFromRenderedText( const std::string& textureText, Font& f, SDL_Color textColor )
{

    free();

    SDL_Surface* textSurface = TTF_RenderText_Solid( f.get_font(), textureText.c_str(), textColor );
    if( textSurface == nullptr ) {
        throw SnakeException(std::string("Unable to render text surface! SDL_ttf Error: ") + TTF_GetError());
    }


    mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
    if( mTexture == nullptr ) {
        throw SnakeException(std::string("Unable to create texture from text :") + SDL_GetError());
    }


    mWidth = textSurface->w;
    mHeight = textSurface->h;


    SDL_FreeSurface( textSurface );

    return mTexture != nullptr;
}

void Texture::free()
{

    if( mTexture != nullptr ) {
        SDL_DestroyTexture( mTexture );
        mTexture = nullptr;
        mWidth = 0;
        mHeight = 0;
    }
}

void Texture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{

    SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void Texture::setBlendMode( SDL_BlendMode blending )
{

    SDL_SetTextureBlendMode( mTexture, blending );
}

void Texture::setAlpha( Uint8 alpha )
{

    SDL_SetTextureAlphaMod( mTexture, alpha );
}

void Texture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{

    SDL_Rect renderQuad = { x, y, mWidth, mHeight };


    if( clip != nullptr )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}
