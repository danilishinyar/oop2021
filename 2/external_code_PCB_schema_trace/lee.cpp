bool lee(int ax, int ay, int bx, int by, char** schema, int max_x, int max_y){
    int len;
    int px[max_x * max_y], py[max_x * max_y]; // поиск пути из ячейки (ax, ay) в ячейку (bx, by){
    int dx[4] = {1, 0, -1, 0};   // смещения, соответствующие соседям ячейки
    int dy[4] = {0, 1, 0, -1};   // справа, снизу, слева и сверху
    int d, x, y, k;
    bool stop;
    // распространение волны
    schema[ax][ay] = 0 + 48;
    d = 0;
    do {
        stop = true;               // предполагаем, что все свободные клетки уже помечены
        for(y = 0; y < max_y; ++y)
            for(x = 0; x < max_y; ++x)
                if(schema[y][x] == d + 48){                         // ячейка (x, y) помечена числом d
                    for (k = 0; k < 4; ++k){                  // проходим по всем непомеченным соседям
                        int iy = y + dy[k];
                        int ix = x + dx[k];
                        if(iy >= 0 && iy < max_y && ix >= 0 && ix < max_x && schema[iy][ix] == '.'){
                            stop = false;              // найдены непомеченные клетки
                            schema[iy][ix] = d + 1 + 48;      // распространяем волну
                        }
                    }
                }
        d++;
    }while(!stop);
    // восстановление пути
    len = schema[by][bx] - 48;// длина кратчайшего пути из (ax, ay) в (bx, by)
    x = bx;
    y = by;
    d = len;
    while ( d > 0 ) {
        px[d] = x;
        py[d] = y;                   // записываем ячейку (x, y) в путь
        d--;
        for (k = 0; k < 4; ++k) {
            int iy=y + dy[k], ix = x + dx[k];
            if ( iy >= 0 && iy < max_y && ix >= 0 && ix < max_x && schema[iy][ix] == d + 48) {
                x = x + dx[k];
                y = y + dy[k];           // переходим в ячейку, которая на 1 ближе к старту
                break;
            }
        }
    }
    px[0] = ax;
    py[0] = ay;                    // теперь px[0..len] и py[0..len] - координаты ячеек пути
    return true;
}