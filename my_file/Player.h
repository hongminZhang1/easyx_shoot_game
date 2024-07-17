//玩家类
class Player {
public:
    Player(int x, int y, int r) : x_(x), y_(y), r_(r) {
        first_ = second_ = third_ = 0;
    }

    void move(int dx, int dy) {//白球移动
        if (!(x_ + dx >= r_ / 2 && x_ + dx <= W - r_ / 2 && y_ + dy >= r_ / 2 && y_ + dy <= H - r_ / 2))return;
        x_ += dx;
        y_ += dy;
    }

    void draw(int flag) const {
        setfillcolor(RGB(115, 251, 253));
        solidcircle(x_, y_, r_);
        setfillcolor(RGB(255,242,0));
        solidcircle(x_ + dx[flag] * r_/2, y_ + dy[flag] * r_/2, r_/2-2);
    }

    void shoot(int dir,bool sizeflag) {
        int r = 5, speed = 6;
        if (sizeflag) {
            r = 10;
            speed = 12;
        }
        if(dir<=4)bullets_.emplace_back(x_ + dx[dir] * r_, y_ + dy[dir] * r_, r, speed, dir);
        else bullets_.emplace_back(x_ + dx[dir] * r_, y_ + dy[dir] * r_, r, speed, dir);
    }

    void updateBullets(vector<Obstacle>& obstacles,Score &score) {
        for (auto it = bullets_.begin(); it != bullets_.end();) {
            it->move();
            if (it->isOutOfScreen()) {//超出屏幕
                it = bullets_.erase(it);
            }
            else {
                for (auto it1 = obstacles.begin();it1 != obstacles.end();it1++) {
                    if (it->collidesWith(*it1)) {
                        it1->hit();
                        if (!(it1->hp_)) {//障碍物被打爆
                            score.addscore(check[it1->r_][it1->copy_hp]);//增加分数
                            if (!(rand() % K)){//爆出装备
                                it1->flag = true;
                            }
                            else obstacles.erase(it1);
                        }
                        it = bullets_.erase(it);
                        break;
                    }
                }
                if (it != bullets_.end()) it++;
            }
        }
    }
    
    void drawBullets() const {
        for (const auto& bullet : bullets_) {
            bullet.draw();
        }
    }
    friend bool Verynear(const Player& player,int x, int y);

    bool is_alive(vector<Obstacle>::iterator it) {
        return pow(x_ - it->x_, 2) + pow(y_ - it->y_, 2) >= pow(r_ + it->r_, 2);
    }
    void skill(bool sizeflag) {//消耗分数释放大招
        for(int t=0;t<5;t++){
            for (int i = 1;i <= 24;i++) {
                shoot(i, sizeflag);
            }
            Sleep(2);
        }
    }
    void show_skill() {
        settextcolor(WHITE);
        settextstyle(20, 0, "Arial Rounded MT");
        char s[30] = { 0 };
        sprintf_s(s, sizeof(s), "技能:%d %d %d", first_, second_, third_);
        outtextxy(W - 100, 40, s);
    }
    /*void first_skill() {
        if (first_) {
            while (true) {
                int t = rand() % 4 + 1;
                int tx = x_ + dx[t] * 150, ty = y_ + dy[t] * 150;
                if (tx >= r_ / 2 && tx <= W - r_ / 2 && ty >= r_ / 2 && ty <= H - r_ / 2) {
                    x_ = tx;y_ = ty;first_--;break;
                }
            }
        }
    }*/
    void first_skill(vector<Obstacle>& obstacles) {
       if (first_) {//同意执行第一技能
           //在150范围画一个圈
           circle(x_, y_, 150);
           for (auto it = obstacles.begin();it != obstacles.end();) {
               if (pow(it->x_ - x_, 2) + pow(it->y_ - y_, 2) <= pow(150, 2)) {
                   it = obstacles.erase(it);
                   continue;
               }
               it++;
           }
           first_--;
       }
   }
    bool second_skill() {
        if (second_) {
            second_--;
            return true;//同意执行第二技能
        }
        return false;
    }
    bool third_skill() {
        if (third_) {
            third_--;
            return true;//同意执行第三技能
        }
        return false;
    }
    void pick_reward() {//拾取道具
        while (true) {
            if (first_ == 9 && second_ == 9 && third_ == 9)break;//技能达到最大容量
            int t = rand() % 3;
            if (t == 0 && first_ != 9) {
                first_++;break;
            }
            else if (t == 1 && second_ != 9) {
                second_++;break;
            }
            else if (t == 2 && third_ != 9) {
                third_++;break;
            }
        }
    }
private:
    int x_;
    int y_;
    int r_;
    vector<Bullet> bullets_;//子弹序列
    //一、二、三技能
    int first_;//[领域展开]清除150单位内的障碍物
    int second_;//冰冻7s
    int third_;//20s子弹增强
};

