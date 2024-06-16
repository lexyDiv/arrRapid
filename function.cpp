#include "Cell/Cell.cpp"

std::string testMap[] = {

    "00000000000000s0000000000000000000000000000tttttttttttttttttttttt",
    "00000000S00000s00000000000000000000000000000ttttttttttttttttttttt",
    "00000000000000s000000000000000000000000000ttttttttttttttttttttttt",
    "00110000000000s0000000000000000000000000000tttttttttttttttttttttt",
    "00110000000000s0000000000000000000000000000tttttttttttttttttttttt",
    "0000000000000000000000000000t000000000000000ttttttttttttttttttttt",
    "0000000000000000000000000000tt0000000000000tttttttttttttttttttttt",
    "0000000000000000000000000000tt00000000000000ttttttttttttttttttttt",
    "00000000000000000000000000000t000000000000000tttttttttttttttttttt",
    "00000000000000s0000000000000000000000000000tttttttttttttttttttttt",
    "00000000000000s0000000000000000000000000000tttttttttttttttttttttt",
    "00000000000000s00000g00000000000000000000000ttttttttttttttttttttt",
    "00000000000000000000000000000000000000000000ttttttttttttttttttttt",
    "000e00000000000000g00g0000000000000000000000ttttttttttttttttttttt",
    "00000000000000000000000000000e000000000000000tttttttttttttttttttt",
    "00000000000000000g0g0g0g0g0g0g0g0000000000000tttttttttttttttttttt",
    "00s00000000000s00000000000000000000000000000000tt0ttttttttttttttt",
    "sss000000000sss00000g0000000000g0000000000000000000000ttttttt0000",
    "000000000000000000000000000000000010000000000000000000000tt000000",
    "00000000000000000000000000000000g0010000000000000000000000t000000",
    "00000000000000000000000000100000001000000000000000000tt00t0000000",
    "00000000000000000000000000000000000000000000tt000000t00t000000000",
    "00000000000000000000000000000000000000000000000000000000000000000",
    "0000000000000000000000000100000e000000000000000000000000000100000",
    "000000000000000000000000010000000000000000000000g0000100100000000",
    "0000000000000000e000000000000000000000000000000000000011111000000",
    "00000000000000000000000000000000000000000000000000000011110000000",
    "00000000www000000000000000000000000000wwwww0000000000000000000000",
    "0000000wwwww00000000000wwwww000000000wwwwwww000000000000000000000",
    "w00000wwwwwwww0000wwwwwwwwwwww0wwwwwwwwwwwwwwww0000w0ww0000000000",
    "wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww0000",
    "wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww000",
    "wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww000",
    "wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww000",
    "wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww0000",
    "wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww9wwwwwwwwwww00000",
    "wwwwwwwwwwwww9wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww00000",
    "wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww0000",
    "wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww0000",
    "wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww000",
    "wwwwwwwwwwwwwwwwwwwwwwww0wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww000",
    "wwwwwwwwwwwwwwwwwwwwwww000wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww0000",
    "w000000www0000wwwww000000000wwwww00000wwwwww0000000000wwwwww00000",
    "000000000000000www0000000000000000000000www000000000000wwwww00000",
    "00000000000000000000000000000000000000000000000000000000wwww00000",
    "000000000000000000000000000000000000000000000000000000000w0000000",
    "00000000000000000000000000000000000000000000000000000000000000000",
    "00000000000000000000000000000000000000000000000000000000000000000",
    "00000000000000000000000000000000000000000000000000000000000000000",
    "00000000000000000000000000000000000000000000000000000000000000000",
    "0000000000000000000000000000000000000000000000000t0t0000t00000000",
    "000000000000000000000000000000000g0000000000000ttt0ttt0tttt0t0t00",
    "0000000000000000000000000000000g00000000000t001111111101111111111",
    "e00000e000000e00000000e0000000000000000000t0011111111111111111111",
    "00000000000000000000000000000000g00000000000111111111111111111111",
    "000000000000000000000000000000000000000000t1111111111111111111111",
    "00000000000000000000000000000000000000000001111111111111111111111",
    "000S00000000000000000000000000000000000t0tt1111111111111111111111",
    "00000000000000000000000000000000000000000tt1111111111111111111111",
    "000000000000000000000000000000000000000000t1111111111111111111111",
    "000000000000000000000000e00000000000000000t1111111111111111111111",
    "00000000000000000000000000000000000000000001111111111111111111111",
    "0000000000g0000000000000000000000000000000t1111111111111111111111",
    "00000000000000000000000000000000000000000001111111111111111111111",
    "000000000000000000000000000000000000000000t1111111111111111111111"};

rapid<rapid<Cell *> *> *arr = new rapid<rapid<Cell *> *>;
Image* image = new Image("src/zombi.png");
Image* miniMap = new Image(64, 64);

void getField()
{

    //      std::string strL = std::to_string(testMap->size()) + " ";

    //  printf(strL.c_str());

    arr->backForce(65);
    for (int i = 0; i < 65; i++)
    {
        arr->push(new rapid<Cell *>);
        arr->getItem(i)->backForce(65);
        for (int k = 0; k < 65; k++)
        {
            char lit = testMap[i][k];
            Color color{0, 0, 0};
            if (lit == '0')
            {
                color = ctx.ColorsMap("green");
            }
            else if (lit == 'g')
            {
                color = ctx.ColorsMap("violet");
            }
            else if (lit == 't' || lit == '1')
            {
                color = ctx.ColorsMap("dgreen");
            }
            else if (lit == 'w')
            {
                color = ctx.ColorsMap("blue");
            }
            else if (lit == 'S')
            {
                color = ctx.ColorsMap("yellow");
            }

            Cell *cell = new Cell(k + 600, i, 2, color);
            arr->getItem(i)->push(cell);
        }
        arr->getItem(i)->norm();
    }
    arr->norm();

    // std::string log = " length = " + std::to_string(arr->getItem(0)->getLength());
    // Color color = arr->getItem(0)->getItem(0)->color;
    // std::string log2 = " color = " + std::to_string(color.G);
    // printf(log.c_str());
    // printf(log2.c_str());
}