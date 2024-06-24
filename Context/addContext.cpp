




i = 33 !
i = 34 "
i = 35 #
i = 36 $
i = 37 %
i = 38 &
i = 39 '
i = 40 (
i = 41 )
i = 42 *
i = 43 +
i = 44 ,
i = 45 -
i = 46 .
i = 47 /
i = 48 0
i = 49 1
i = 50 2
i = 51 3
i = 52 4
i = 53 5
i = 54 6
i = 55 7
i = 56 8
i = 57 9
i = 58 :
i = 59 ;
i = 60 <
i = 61 =
i = 62 >
i = 63 ?
i = 64 @
i = 65 A
i = 66 B
i = 67 C
i = 68 D
i = 69 E
i = 70 F
i = 71 G
i = 72 H
i = 73 I
i = 74 J
i = 75 K
i = 76 L
i = 77 M
i = 78 N
i = 79 O
i = 80 P
i = 81 Q
i = 82 R
i = 83 S
i = 84 T
i = 85 U
i = 86 V
i = 87 W
i = 88 X
i = 89 Y
i = 90 Z
i = 91 [
i = 92 \
i = 93 ]
i = 94 ^
i = 95 _
i = 96 `
i = 97 a
i = 98 b
i = 99 c
i = 100 d
i = 101 e
i = 102 f
i = 103 g
i = 104 h
i = 105 i
i = 106 j
i = 107 k
i = 108 l
i = 109 m
i = 110 n
i = 111 o
i = 112 p
i = 113 q
i = 114 r
i = 115 s
i = 116 t
i = 117 u
i = 118 v
i = 119 w
i = 120 x
i = 121 y
i = 122 z
i = 123 {
i = 124 |
i = 125 }
i = 126 ~





                            case SDLK_9:
                            //If there is no music playing
                            if( Mix_PlayingMusic() == 0 )
                            {
                                //Play the music
                                Mix_PlayMusic( gMusic, -1 );
                            }
                            //If music is being played
                            else
                            {
                                //If the music is paused
                                if( Mix_PausedMusic() == 1 )
                                {
                                    //Resume the music
                                    Mix_ResumeMusic();
                                }
                                //If the music is playing
                                else
                                {
                                    //Pause the music
                                    Mix_PauseMusic();
                                }
                            }
                            break;
                            
                            case SDLK_0:
                            //Stop the music
                            Mix_HaltMusic();
                            break;
                        }
                    }








// #include "Context.cpp"

// Context ctx(800, 600);
// SDL_Renderer *Image::gRenderer = ctx.getRenderer();
// Image *image = new Image("src/zombi.png");
// Image *test = new Image("src/h.png");

// rapid<rapid<Cell *> *> *arr = new rapid<rapid<Cell *> *>;

// int S = 10;
// int s = 20;
// int t = 30;
// int g = 40;
// int w = 50;

// std::string testMap[] = {

//     "00000000000000s0000000000000000000000000000tttttttttttttttttttttt",
//     "00000000S00000s00000000000000000000000000000ttttttttttttttttttttt",
//     "00000000000000s000000000000000000000000000ttttttttttttttttttttttt",
//     "00110000000000s0000000000000000000000000000tttttttttttttttttttttt",
//     "00110000000000s0000000000000000000000000000tttttttttttttttttttttt",
//     "0000000000000000000000000000t000000000000000ttttttttttttttttttttt",
//     "0000000000000000000000000000tt0000000000000tttttttttttttttttttttt",
//     "0000000000000000000000000000tt00000000000000ttttttttttttttttttttt",
//     "00000000000000000000000000000t000000000000000tttttttttttttttttttt",
//     "00000000000000s0000000000000000000000000000tttttttttttttttttttttt",
//     "00000000000000s0000000000000000000000000000tttttttttttttttttttttt",
//     "00000000000000s00000g00000000000000000000000ttttttttttttttttttttt",
//     "00000000000000000000000000000000000000000000ttttttttttttttttttttt",
//     "000e00000000000000g00g0000000000000000000000ttttttttttttttttttttt",
//     "00000000000000000000000000000e000000000000000tttttttttttttttttttt",
//     "00000000000000000g0g0g0g0g0g0g0g0000000000000tttttttttttttttttttt",
//     "00s00000000000s00000000000000000000000000000000tt0ttttttttttttttt",
//     "sss000000000sss00000g0000000000g0000000000000000000000ttttttt0000",
//     "000000000000000000000000000000000010000000000000000000000tt000000",
//     "00000000000000000000000000000000g0010000000000000000000000t000000",
//     "00000000000000000000000000100000001000000000000000000tt00t0000000",
//     "00000000000000000000000000000000000000000000tt000000t00t000000000",
//     "00000000000000000000000000000000000000000000000000000000000000000",
//     "0000000000000000000000000100000e000000000000000000000000000100000",
//     "000000000000000000000000010000000000000000000000g0000100100000000",
//     "0000000000000000e000000000000000000000000000000000000011111000000",
//     "00000000000000000000000000000000000000000000000000000011110000000",
//     "00000000www000000000000000000000000000wwwww0000000000000000000000",
//     "0000000wwwww00000000000wwwww000000000wwwwwww000000000000000000000",
//     "w00000wwwwwwww0000wwwwwwwwwwww0wwwwwwwwwwwwwwww0000w0ww0000000000",
//     "wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww0000",
//     "wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww000",
//     "wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww000",
//     "wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww000",
//     "wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww0000",
//     "wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww9wwwwwwwwwww00000",
//     "wwwwwwwwwwwww9wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww00000",
//     "wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww0000",
//     "wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww0000",
//     "wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww000",
//     "wwwwwwwwwwwwwwwwwwwwwwww0wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww000",
//     "wwwwwwwwwwwwwwwwwwwwwww000wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww0000",
//     "w000000www0000wwwww000000000wwwww00000wwwwww0000000000wwwwww00000",
//     "000000000000000www0000000000000000000000www000000000000wwwww00000",
//     "00000000000000000000000000000000000000000000000000000000wwww00000",
//     "000000000000000000000000000000000000000000000000000000000w0000000",
//     "00000000000000000000000000000000000000000000000000000000000000000",
//     "00000000000000000000000000000000000000000000000000000000000000000",
//     "00000000000000000000000000000000000000000000000000000000000000000",
//     "00000000000000000000000000000000000000000000000000000000000000000",
//     "0000000000000000000000000000000000000000000000000t0t0000t00000000",
//     "000000000000000000000000000000000g0000000000000ttt0ttt0tttt0t0t00",
//     "0000000000000000000000000000000g00000000000t001111111101111111111",
//     "e00000e000000e00000000e0000000000000000000t0011111111111111111111",
//     "00000000000000000000000000000000g00000000000111111111111111111111",
//     "000000000000000000000000000000000000000000t1111111111111111111111",
//     "00000000000000000000000000000000000000000001111111111111111111111",
//     "000S00000000000000000000000000000000000t0tt1111111111111111111111",
//     "00000000000000000000000000000000000000000tt1111111111111111111111",
//     "000000000000000000000000000000000000000000t1111111111111111111111",
//     "000000000000000000000000e00000000000000000t1111111111111111111111",
//     "00000000000000000000000000000000000000000001111111111111111111111",
//     "0000000000g0000000000000000000000000000000t1111111111111111111111",
//     "00000000000000000000000000000000000000000001111111111111111111111",
//     "000000000000000000000000000000000000000000t1111111111111111111111"};

// void getField()
// {

//     //      std::string strL = std::to_string(testMap->size()) + " ";

//     //  printf(strL.c_str());

//     arr->backForce(65);
//     for (int i = 0; i < 65; i++)
//     {
//         arr->push(new rapid<Cell *>);
//         arr->getItem(i)->backForce(65);
//         for (int k = 0; k < 65; k++)
//         {
//             char lit = testMap[i][k];
//             Color color;
//             if (lit == '0')
//             {
//                 color = ctx.ColorsMap("green");
//             }

//             // Cell *cell = new Cell(k + 600, i, 2, "dd");
//             // arr->getItem(i)->push(cell);
//         }
//         arr->getItem(i)->norm();
//     }
//     arr->norm();
// }
