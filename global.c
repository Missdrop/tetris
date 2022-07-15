/* 全局变量定义文件 */

char tetrisField[22][12] = {
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}
};

const struct blockShape{
    char blockshape[4][4][2];
}
blockT = {
    {{{0, -1}, {0, 0}, {0, 1}, {-1, 0}},
    {{-1, 0}, {0, 0}, {1, 0}, {0, 1}},
    {{0, -1}, {0, 0}, {0, 1}, {1, 0}},
    {{0, -1}, {0, 0}, {-1, 0}, {1, 0}}}
},
blockS = {
    {{{0, -1}, {0, 0}, {-1, 0}, {-1, 1}},
    {{-1, 0}, {0, 0}, {0, 1}, {1, 1}},
    {{1, -1}, {1, 0}, {0, 0}, {0, 1}},
    {{-1, -1}, {0, -1}, {0, 0}, {1, 0}}}
},
blockZ = {
    {{{-1, -1}, {-1, 0}, {0, 0}, {0, 1}},
    {{-1, 1}, {0, 1}, {0, 0}, {1, 0}},
    {{0, -1}, {0, 0}, {1, 0}, {1, 1}},
    {{1, -1}, {0, -1}, {0, 0}, {-1, 0}}}
},
blockL = {
    {{{0, -1}, {0, 0}, {0, 1}, {-1, 1}},
    {{-1, 0}, {0, 0}, {1, 0}, {1, 1}},
    {{1, -1}, {0, -1}, {0, 0}, {0, 1}},
    {{-1, -1}, {-1, 0}, {0, 0}, {1, 0}}}
},
blockJ = {
    {{{-1, -1}, {0, -1}, {0, 0}, {0, 1}},
    {{1, 0}, {0, 0}, {-1, 0}, {-1, 1}},
    {{0, -1}, {0, 0}, {0, 1}, {1, 1}},
    {{-1, 0}, {0, 0}, {1, 0}, {1, -1}}}
},
blockO = {
    {{{0, 0}, {-1, 0}, {-1, 1}, {0, 1}},
    {{0, 0}, {-1, 0}, {-1, 1}, {0, 1}},
    {{0, 0}, {-1, 0}, {-1, 1}, {0, 1}},
    {{0, 0}, {-1, 0}, {-1, 1}, {0, 1}}}
},
blockI ={
    {{{0, -1}, {0, 0}, {0, 1}, {0, 2}},
    {{-1, 1}, {0, 1}, {1, 1}, {2, 1}},
    {{1, -1}, {1, 0}, {1, 1}, {1, 2}},
    {{-1, 0}, {0, 0}, {1, 0}, {2, 0}}}
};

const char blockMovement[3][2] = {
    {0, -1},                                //向左
    {0, 1},                                 //向右
    {1, 0}                                  //向下
};

const char wallKickData[4][2][4][2] =
{
    {                                           //0
        {{-1,0},{-1,-1},{0,2},{-1,2}},      //R
        {{1,0},{1,-1},{0,2},{1,2}}          //L
    },
    {                                           //R
        {{1,0},{1,1},{0,-2},{1,-2}},        //2
        {{1,0},{1,1},{0,-2},{1,-2}}         //0
    },
    {                                           //2
        {{1,0},{1,-1},{0,2},{1,2}},         //L
        {{-1,0},{-1,-1},{0,2},{-1,2}}       //R
    },
    {                                           //L
        {{-1,0},{-1,1},{0,-2},{-1,-2}},     //0
        {{-1,0},{-1,1},{0,-2},{-1,-2}}      //2
    }
};

const char wallKickDataI[4][2][4][2] =
{
    {                                           //0
        {{-2,0},{1,0},{-2,1},{1,-2}},       //R
        {{-1,0},{2,0},{-1,-2},{2,1}}        //L
    },
    {                                           //R
        {{-1,0},{2,0},{-1,-2},{2,1}},       //2
        {{2,0},{-1,0},{2,-1},{-1,2}}        //0
    },
    {                                           //2
        {{2,0},{-1,0},{2,-1},{-1,2}},       //L
        {{1,0},{-2,0},{1,2},{-2,-1}}        //R
    },
    {                                           //L
        {{1,0},{-2,0},{1,2},{-2,-1}},       //0
        {{-2,0},{1,0},{-2,1},{1,-2}}        //2
    }
};

struct tetroMinoState {
    char type;
    char location[2];
    char direction;
} previewBlock;

int score = 0;

char facing[4] = {'0', 'R', '2', 'L'};
