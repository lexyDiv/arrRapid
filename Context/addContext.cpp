#include "Context.cpp"

Context ctx(800, 600);
SDL_Renderer *Image::gRenderer = ctx.getRenderer();
Image *image = new Image("src/zombi.png");
Image *test = new Image("src/h.png");

rapid<rapid<Cell *> *> *arr = new rapid<rapid<Cell *> *>;

void getField()
{
    arr->backForce(300);
    for (int i = 0; i < 300; i++)
    {
        arr->push(new rapid<Cell *>);
        arr->getItem(i)->backForce(200);
        for (int k = 0; k < 200; k++)
        {
            Cell *cell = new Cell(k + 600, i, 2);
            arr->getItem(i)->push(cell);
        }
        arr->getItem(i)->norm();
    }
    arr->norm();
}
