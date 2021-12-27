#include "Menu.h"


namespace Menu{
	const int ReservedOptions = 20;

	const char *msgs[] = {"1 - Input contact", "2 - Print current PCB", "3 - Check contact is connected correctly",
						  "4 - Connect 2 contacts", "5 - Print all contacts of chosen type", "6 - Print distance between two contacts",
						  "7 - Print contact with given index", "8 - Inverse all contact's type",
						  "9 - Delete last contact", "10 - Create another PCB and work with it", "11 - Print schema", "0 - Quit"};

	void menu(Prog3_D::PCB &p) {
		void (*fptr[])(Prog3_D::PCB&) = {nullptr, inputCon, printPCB, checkCon, connectCon, printConSingleType, distCon,
										   printContact, invertPCB, deleteLast, anotherMenu, PrintSchema};
		int rc = dialog();
		while(rc){
			fptr[rc](p);
			rc = dialog();
		}
	}

	int dialog() {
		const int Nmsgs = sizeof(msgs) / sizeof(msgs[0]);
		const char *errmsg = "";
		int rc;
		do {
			std::cout << errmsg;
			errmsg = "Error, repeat:\n";
			for (auto & msg : msgs)
				std::cout << msg << std::endl;
			std::cout << "Make your choice: ";
			if(getNum(rc, std::cin) < 0) throw(std::exception());
		} while (rc < 0 || rc >= Nmsgs);
		return rc;
	}

	void inputCon(Prog3_D::PCB &p){
		try{
			std::cout << "Input contact in format: x coord, y coord, type(0 for output, 1 for input)" << std::endl;
			std::cin >> p;
		}catch (std::runtime_error &err){
			std::cout << err.what() << std::endl;
		}
	}

	void printPCB(Prog3_D::PCB &p){
		std::cout << p;
	}

	void checkCon(Prog3_D::PCB &p){
		int n;
		std::cout << "Contact's index:";
		if(getNum(n, std::cin) < 0) throw(std::exception());

		bool ch;
		try{
			ch = p.check(n);
		}catch (std::runtime_error &err){
			std::cout << err.what() << std::endl;
			return;
		}

		if(ch)
			std::cout << "Connection is correct" << std::endl;
		else
			std::cout << "Connection is incorrect" << std::endl;
	}

	void connectCon(Prog3_D::PCB &p){
		int n1, n2;
		std::cout << "First contact's index:";
		if(getNum(n1, std::cin) < 0) throw(std::exception());
		std::cout << "Second contact's index:";
		if(getNum(n2, std::cin) < 0) throw(std::exception());

		try{
			p.makeConnection(n1, n2);
		}catch(std::runtime_error &err){
			std::cout << err.what() << std::endl;
		}
	}

	void printConSingleType(Prog3_D::PCB &p){
		int choise;
		bool fl = true, type;
		const char *msg = "Input 0 if selected type is output, 1 - input:";
		do{
			std::cout << msg;
			msg = "Error, repeat:";
			if(getNum(choise, std::cin) < 0) throw std::exception();
			switch (choise) {
				case 1:
					type = true;
					fl = false;
					break;
				case 0:
					type = false;
					fl = false;
					break;
				default:
					break;
			}
		}while(fl);

		Prog3_D::PCB temp = p.selType(type);
		std::cout << temp;
	}

	void distCon(Prog3_D::PCB &p){
		int n1, n2;
		std::cout << "Enter first contact's index:";
		if(getNum(n1, std::cin) < 0) throw(std::exception());
		std::cout << "Enter second contact's index:";
		if(getNum(n2, std::cin) < 0) throw(std::exception());

		try{
			double dist = p.dist(n1, n2);
			std::cout << "Distance = " << dist << std::endl;
		}catch(std::runtime_error &err){
			std::cout << err.what() << std::endl;
		}
	}

	void printContact(Prog3_D::PCB &p){
		int n;
		std::cout << "Enter contact's index:";
		if(getNum(n, std::cin) < 0) throw(std::exception());

		try{
			std::cout << p[n];
		}catch(std::runtime_error &err){
			std::cout << err.what() << std::endl;
		}
	}

	void invertPCB(Prog3_D::PCB &p){
		-p;
		std::cout << "New PCB:" << std::endl << p;
	}

	void deleteLast(Prog3_D::PCB &p){
//		std::cout << p-- << std::endl;//проверка для постфиксного оператора
		--p;
	}

	void anotherMenu(Prog3_D::PCB &p) {
		Prog3_D::PCB p2;

		void (*fptr[])(Prog3_D::PCB&) = {nullptr, inputCon, printPCB, checkCon, connectCon, printConSingleType, distCon,
										   printContact, invertPCB, deleteLast, anotherMenu};
		void (*fptr2[])(Prog3_D::PCB&, Prog3_D::PCB&) = {mergePCB, comparePCB, sumPCB};
		int rc = anotherDialog();
		while(rc){
			if(rc >= ReservedOptions){
				fptr2[rc - ReservedOptions](p2, p);
			}
			else fptr[rc](p2);
			rc = anotherDialog();
		}
	}

	int anotherDialog() {
		std::cout << "Working with additional PCB:" << std::endl;
		const char *msgs2[] = {"20 - Add all second PCB's contacts to primary PCB",
							   "21 - Compare numbers of contacts in primary and secondary PCB",
							   "22 - Print classes' union"};
		const int Nmsgs = sizeof(msgs) / sizeof(msgs[0]);
		const int Nmsgs2 = sizeof(msgs2) / sizeof(msgs2[0]);
		const char *errmsg = "";
		int rc;
		do {
			std::cout << errmsg;
			errmsg = "Error, repeat:\n";
			for (auto & msg : msgs)
				std::cout << msg << std::endl;
			for (auto & msg : msgs2)
				std::cout << msg << std::endl;
			std::cout << "Make your choice: ";
			if(getNum(rc, std::cin) < 0) throw(std::exception());
		} while (rc < 0 || rc >= Nmsgs && rc < ReservedOptions || rc > Nmsgs2 + ReservedOptions);
		return rc;
	}

	void mergePCB(Prog3_D::PCB &p2, Prog3_D::PCB &p){
		p += p2;
	}

	void comparePCB(Prog3_D::PCB &p2, Prog3_D::PCB &p){
		int res = p >= p2;
		if(res > 0)
			std::cout << "Primary PCB has more contacts than second PCB";
		else if(res == 0)
			std::cout << "Numbers of contacts are equal";
		else std::cout << "Primary PCB has less contacts than second PCB";
		std::cout << std::endl;
	}

	void sumPCB(Prog3_D::PCB &p2, Prog3_D::PCB &p){
		Prog3_D::PCB p3(p + p2);
		std::cout << p3 << std::endl;
	}


    void PrintSchema(Prog3_D::PCB &p){
        if(p.getSize() == 0){
            std::cout << "#" << std::endl;
            return;
        }
        int x;
        int y;
        find_borders(p, x, y);//ищем границы, чтобы выводить что-то типа координатной плоскости
        char** schema = new char*[y];
        for (int i = 0; i < y; ++i){//заполняем результирующую мартицу . (пустая клетка платы)
            schema[i] = new char[x];
            for (int j = 0; j < x; ++j)
                schema[i][j] = '.';
        }
        int noffset_x = 0;
        int noffset_y = 0;
        int poffset_x = 2147483647;
        int poffset_y = 2147483647;
        for(int i = 0; i < p.getSize(); ++i){//ищем величины, на которые нужно сместить контакт, чтобы сохранять условный масштаб
            if(p[i].x < 0)
                if(noffset_x > static_cast<int>(p[i].x))//так float к int
                    noffset_x = static_cast<int>(p[i].x);
            if(p[i].y < 0)
                if(noffset_y > static_cast<int>(p[i].y))
                    noffset_y = static_cast<int>(p[i].y);
            if(p[i].x < 2147483647 && p[i].x >= 0)
                if(poffset_x > static_cast<int>(p[i].x))
                   poffset_x = static_cast<int>(p[i].x);
            if(p[i].y < 2147483647 && p[i].y >= 0)
                if(poffset_y > static_cast<int>(p[i].y))
                    poffset_y = static_cast<int>(p[i].y);
        }
        for(int i = 0; i < p.getSize(); ++i){//наносим контакты на рисунок платы
            int x1, y1;
            if(!p[i].type) {
                if (noffset_y == 0 && noffset_x == 0) {
                    x1 = std::abs(static_cast<int>(p[i].x) - poffset_x);
                    y1 = std::abs(static_cast<int>(p[i].y) - poffset_y);
                } else {
                    x1 = std::abs(static_cast<int>(p[i].x) - noffset_x);
                    y1 = std::abs(static_cast<int>(p[i].y) - noffset_y);
                }
                schema[y1][x1] = '+';
            }
            else{
                if (noffset_y == 0 && noffset_x == 0) {
                    x1 = std::abs(static_cast<int>(p[i].x) - poffset_x);
                    y1 = std::abs(static_cast<int>(p[i].y) - poffset_y);
                } else {
                    x1 = std::abs(static_cast<int>(p[i].x) - noffset_x);
                    y1 = std::abs(static_cast<int>(p[i].y) - noffset_y);
                }
                schema[y1][x1] = '-';
            }
        }

        for(int i = 0; i < p.getSize(); ++i) {//наносим дорожки на плату
            int x1, y1;
            int x2 = -1, y2 = -1;
            if (!p[i].type) {
                if (noffset_y == 0 && noffset_x == 0) {
                    x1 = std::abs(static_cast<int>(p[i].x) - poffset_x);
                    y1 = std::abs(static_cast<int>(p[i].y) - poffset_y);
                    if (p[i].index != -1) {
                        x2 = std::abs(static_cast<int>(p[p[i].index].x) - poffset_x);
                        y2 = std::abs(static_cast<int>(p[p[i].index].y) - poffset_y);
                    }
                } else {
                    x1 = std::abs(static_cast<int>(p[i].x) - noffset_x);
                    y1 = std::abs(static_cast<int>(p[i].y) - noffset_y);
                    if (p[i].index != -1) {
                        x2 = std::abs(static_cast<int>(p[p[i].index].x) - noffset_x);
                        y2 = std::abs(static_cast<int>(p[p[i].index].y) - noffset_y);
                    }
                }
            }
            if (x2 * y2 != 1) {
                bool a = path(x1, y1, x2, y2, schema, x, y);
                if(!a){
                    std::cout << "Sorry, can't draw this pcb" << std::endl;
                    for (int k = 0; k < y; ++k)
                        delete[] schema[k];
                    delete[] schema;
                    return;
                }
            }
        }

        for (int i = 0; i < y; ++i) {//печатаем схему
            std::cout << std::endl;
            for (int j = 0; j < x; ++j){
                std::cout << schema[i][j] << " ";
            }
        }

        std::cout << std::endl;
        for (int i = 0; i < y; ++i)
            delete[] schema[i];
        delete[] schema;
    }

    void find_borders(Prog3_D::PCB &p, int &x, int &y){
        int min_x = 2147483647;
        int max_x = -2147483647;
        int min_y = 2147483647;
        int max_y = -2147483647;
        for(int i = 0; i < p.getSize(); i++){
            if(p[i].x <= min_x)
                min_x = static_cast<int>(p[i].x);
            if(p[i].x >= max_x)
                max_x =  static_cast<int>(p[i].x);
            if(p[i].y <= min_y)
                min_y =  static_cast<int>(p[i].y);
            if(p[i].y >= max_y)
                max_y =  static_cast<int>(p[i].y);
        }
        x = max_x - min_x + 1;
        y = max_y - min_y + 1;
    }


    bool path(int ax, int ay, int bx, int by, char** schema, int max_x, int max_y){
        int len;
        int flag;
        int path_x[max_x * max_y], path_y[max_x * max_y];//координаты пути
        for(int i = 0; i < max_x * max_y; i++){
            path_x[i] = -1;
            path_y[i] = -1;
        }

        int dx[4] = {1, 0, -1, 0};
        int dy[4] = {0, 1, 0, -1};
        int ddy[4] = {1, -1, 1, -1};
        int ddx[4] = {1, 1, -1, -1};
        int d, x, y, k;
        bool stop;
        schema[ay][ax] = 0+48;
        schema[by][bx] = 'z';
        d = 0;
        do {//намчеаем возможные пути
            stop = true;
            for(y = 0; y < max_y; ++y)
                for(x = 0; x < max_y; ++x)
                    if(schema[y][x] == d+48){
                        for (k = 0; k < 4; ++k){
                            int iy = y + dy[k];
                            int ix = x + dx[k];
                            int iiy = y + ddy[k];
                            int iix = x + ddx[k];
                            if(iy >= 0 && iy < max_y && ix >= 0 && ix < max_x && (schema[iy][ix] == '.' || schema[iy][ix] == 'z')) {
                                stop = false;
                                schema[iy][ix] = d + 1 + 48;
                            }
                            if(iiy >= 0 && iiy < max_y && iix >= 0 && iix < max_x && (schema[iiy][iix] == '.' || schema[iiy][iix] == 'z')
                             && !((iiy >= 1 && iix >= 1 && schema[iiy - 1][iix] < 48 && schema[iiy][iix - 1] < 48) || (iiy >= 1 && iix < max_x - 1 && schema[iiy][iix + 1] < 48 && schema[iiy - 1][iix] < 48) || (iiy < max_y - 1 && iix >= 1 && schema[iiy + 1][iix] < 48 && schema[iiy][iix - 1] < 48) || (iiy < max_y - 1 && iix < max_x - 1 && schema[iiy + 1][iix] < 48 && schema[iiy][iix + 1] < 48)))
                                schema[iiy][iix] = d + 1 +48;

                        }
                    }
            d++;
        }while(!stop);

        flag = 1;//проверка дошла ли волна
        for (k = 0; k < 4; ++k) {
            int iy = by + dy[k];
            int ix = bx + dx[k];
            int iiy = by + ddy[k];
            int iix = bx + ddx[k];
            if(iy >= 0 && iy < max_y && ix >= 0 && ix < max_x) {
                if(schema[iy][ix] != '.')
                    flag = 0;
            }
            if(iiy >= 0 && iiy < max_y && iix >= 0 && iix < max_x) {
                if(schema[iiy][iix] != '.')
                    flag = 0;
            }
        }
        if(flag)
            return false;
        len = d;//длина пути
        x = bx;
        y = by;
        int offset = 0;
        int n = 2147483647;
        int min_x = 2147483647;
        int min_y = 2147483647;
        while (d > 0) {
            path_x[d] = x;
            path_y[d] = y;
            d--;
            for (k = 0; k < 4; ++k) {
                int iy = y + dy[k];
                int ix = x + dx[k];
                int iiy = y + ddy[k];
                int iix = x + ddx[k];

                if (iiy >= 0 && iiy < max_y && iix >= 0 && iix < max_x && !(schema[iiy][iix] == '-' || schema[iiy][iix] == '+' || schema[iiy][iix] == '*')
                && !((iiy >= 1 && iix >= 1 && schema[iiy - 1][iix] < 48 && schema[iiy][iix - 1] < 48) || (iiy >= 1 && iix < max_x - 1 && schema[iiy][iix + 1] < 48 && schema[iiy - 1][iix] < 48) || (iiy < max_y - 1 && iix >= 1 && schema[iiy + 1][iix] < 48 && schema[iiy][iix - 1] < 48) || (iiy < max_y - 1 && iix < max_x - 1 && schema[iiy + 1][iix] < 48 && schema[iiy][iix + 1] < 48))) {
                    if (schema[iiy][iix] <= n) {
                        n = schema[iiy][iix];
                        min_x = iix;
                        min_y = iiy;
                    }
                }
                if(iy >= 0 && iy < max_y && ix >= 0 && ix < max_x && !(schema[iy][ix] == '-' || schema[iy][ix] == '+' || schema[iy][ix] == '*')){
                    if (schema[iy][ix] < n) {
                        n = schema[iy][ix];
                        min_x = ix;
                        min_y = iy;
                    }
                }

            }
            x = min_x;
            y = min_y;
            if(n == 48){
                offset = d;
                break;
            }
        }
        flag = 0;
        for (k = 0; k < 4; ++k) {
            int iy = ay + dy[k];
            int ix = ax + dx[k];
            int iiy = ay + ddy[k];
            int iix = ax + ddx[k];
            if(iy >= 0 && iy < max_y && ix >= 0 && ix < max_x) {
                if(path_x[1+offset] == -1 && path_y[1+offset] == -1 && schema[path_y[1+offset]][path_x[1+offset]] == schema[iy][ix])
                    flag = 1;
            }
            if(iiy >= 0 && iiy < max_y && iix >= 0 && iix < max_x) {
                if(path_x[1+offset] == -1 && path_y[1+offset] == -1 && schema[path_y[1+offset]][path_x[1+offset]] == schema[iiy][iix])
                    flag = 1;
            }
        }
        if(flag)
            return false;
        path_x[0+offset] = ax;
        path_y[0+offset] = ay;
        for(int i = offset; i < len; i++){//помечаем путь
            schema[path_y[i]][path_x[i]] = '*';
        }
        schema[ay][ax] = '+';
        schema[by][bx] = '-';
        for(int i = 0; i < max_y; ++i){
            for(int j = 0; j < max_x; ++j){
                if(!(schema[i][j] == '-' || schema[i][j] == '+' || schema[i][j] == '*'))
                    schema[i][j] = '.';
            }
        }
        return true;
    }

}