#include "Unit.h"

// inline Unit::Unit()
// {
// }

// inline Unit::Unit(int x, int y, int conor, int alpha, int gabX, int gabY, LTexture* texture)
// {
//     this->x = x;
//     this->y = y;
//     this->conor = conor;
//     this->alpha = alpha;
//     this->gabX = gabX;
//     this->gabY = gabY;
//     this->texture = texture;
// }

// inline void Unit::draw(SDL_Renderer *gRenderer)
// {
//     this->texture->render(
//         this->x,
//         this->y,
//         this->conor,
//         this->alpha,
//         this->animX,
//         this->animY,
//         this->animStepX,
//         this->animStepY,
//         this->gabX,
//         this->gabY,
//         gRenderer
//     );
// }

Unit::Unit()
{
}

Unit::Unit(int x, int y, int conor, int alpha, int gabX, int gabY, LTexture *texture)
{
    this->x = x;
    this->y = y;
    this->conor = conor;
    this->alpha = alpha;
    this->gabX = gabX;
    this->gabY = gabY;
    this->texture = texture;
}

void Unit::draw(SDL_Renderer *gRenderer)
{
    this->texture->render(
        this->x,
        this->y,
        this->conor,
        this->alpha,
        this->animX,
        this->animY,
        this->animStepX,
        this->animStepY,
        this->gabX,
        this->gabY,
        gRenderer);
}
