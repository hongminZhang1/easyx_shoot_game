//子弹类
class Bullet {
public:
    Bullet(int x, int y,int r, int speed,int dir) : x_(x), y_(y), speed_(speed),r_(r) ,dir_(dir){}

    void move() {
        x_ += dx[dir_]*speed_;
        y_ += dy[dir_] * speed_;
    }
    void draw() const {
        //撞击墙壁效果
        if (y_ >= 0 && y_ <= r_)setfillcolor(RGB(117, 250, 141));
        else if (y_ >= H - r_ && y_ <= H)setfillcolor(RGB(117, 250, 141));
        else if (x_ >= 0 && x_ <=  r_)setfillcolor(RGB(117, 250, 141));
        else if (x_ >= W -  r_ && x_ <= W)setfillcolor(RGB(117, 250, 141));
        else setfillcolor(RED);
        solidcircle(x_, y_, r_);
    }

    bool isOutOfScreen() const {
        return y_ < 0 || y_>H || x_<0 || x_>W;
    }

    bool collidesWith( Obstacle &obstacle) {
        return pow(x_ - obstacle.x_, 2) + pow(y_ - obstacle.y_, 2) <= pow(r_ + obstacle.r_, 2);
    }
private:
    int x_;
    int y_;
    int r_;
    int dir_;
    int speed_;
};

