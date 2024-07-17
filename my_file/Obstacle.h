//障碍物类
class Obstacle {
public:
    Obstacle(int x, int y, int r,int speed,int dir,int hp){
        x_ = x;
        y_ = y;
        r_ = r;
        speed_ = speed;
        dir_ = dir;
        hp_ = copy_hp = hp;
        flag = false;
    }

    void draw() const {
        if (flag == true) {
            setfillcolor(RGB(0,255,0));
            solidcircle(x_, y_, 7);//显示绿色装备
            return;
        }
        if (hp_) {
            //绘制障碍物
            setfillcolor(BLUE);
            solidcircle(x_, y_, r_);
            //绘制障碍物生命值
            settextcolor(WHITE);
            settextstyle(r_, 0, "Arial Rounded MT");
            char s[5] = { 0 };
            sprintf_s(s, sizeof(s), "%d", hp_);
            outtextxy(x_-r_/2+3, y_-r_/2+2, s);
        }
    }

    void hit() {
        hp_--;
    }
    void move() {
        x_ += dx[dir_]*speed_;
        y_ += dy[dir_]*speed_;
    }

    bool isOutOfScreen() const {
        return y_ < 0 || y_>H || x_<0 || x_>W;
    }
    
    int x_;
    int y_;
    int r_;
    int speed_;
    int dir_;
    int hp_;//生命值
    int copy_hp;//生命值的备份，用于计算得分
    bool flag;//障碍物的状态
};
