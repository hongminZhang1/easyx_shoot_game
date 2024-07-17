#include "head.h"
#include "Score.h"
#include "Obstacle.h"
#include "Bullet.h"
#include "Player.h"
bool Verynear(const Player& player, int x, int y) {
    return pow((player.x_ - x), 2) + pow((player.y_ - y), 2) <= pow(1.5 * player.r_, 2);
}
vector<Obstacle> obstacles;//障碍物序列
Score score;//得分
int speed[5] = { 0,2,1,1,1 };//速度
int d = 2;//障碍物数
time_t start2, end2,start3, end3;
int main() {

    //初始化随机数种子
    srand(time(nullptr));

    // 初始化图形窗口
    HWND hwnd = initgraph(W, H);
    SetWindowPos(hwnd, HWND_TOPMOST, 200, 100, 0, 0, SWP_NOSIZE);
    init_score_check();

    // 开启双缓冲
    BeginBatchDraw();

    Player player(400, 300, 20);
    int playerflag = 1;//玩家状态
    bool flag = true;//游戏状态
    bool stopflag = false;//是否冰冻
    bool sizeflag = false;//子弹是否变大
    while (flag) {
        if (stopflag&&difftime(end2, start2) >= 7)stopflag = false;
        if (sizeflag&&difftime(end3, start3) >= 20)sizeflag = false;
        // 清屏
        cleardevice(); 

        //显示分数
        score.show();

        //显示技能数
        player.show_skill();

        //模式调整
        if (obstacles.size() < 8) {
            int t = score.get_total();
            if (t < 200) {
                d = 3; speed[1] = speed[2] = speed[3] = 1; speed[4] = 2;
            }
            else if (t< 400) {
                d = 4; speed[1] = speed[2] = 1; speed[3] = speed[4] = 2;
            }
            else if (t < 600) {
                d = 4; speed[1] = 1; speed[2] = speed[3] = speed[4] = 2;
            }
            else  {
                d = 5; for (int i = 1; i <= 4; i++) speed[i] = 2;
            }
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < d; j++) {
                    int r = rand() % 10 + 10;
                    int hp = rand() % 5 + 1;
                    int dir = rand() % 8 + 1;
                    int positions[4][2] = { {0, rand() % H}, {rand() % W, 0}, {W, rand() % H}, {rand() % W, H} };
                    obstacles.emplace_back(positions[i][0], positions[i][1], r, speed[i + 1], dir, hp);
                }
            }
        }

        // 绘制玩家
        player.draw(playerflag);

        // 更新子弹
        player.updateBullets(obstacles,score);

        //绘制子弹
        player.drawBullets();

        // 绘制障碍物
        for (auto it = obstacles.begin();it != obstacles.end();) {
            if(!stopflag)it->move();
            if (it->isOutOfScreen()) {
                it = obstacles.erase(it);continue;
            }
            else {  
                it->draw();
                if (!player.is_alive(it)) {
                    if (it->flag == false) {//如果碰到的不是装备
                        flag = false;break;
                    }
                    else {
                        it = obstacles.erase(it);
                        player.pick_reward();continue;
                    }
                }
                it++;
            }
        }
        Sleep(2);
        end2 = end3 = time(nullptr);
        // 检查键盘输入
        if (_kbhit()) {
            char ch = _getch();
            switch (ch) {
            case'w':case'W':player.move(0, -20);playerflag = 1;break;
            case's':case'S':player.move(0, 20);playerflag = 2;break;
            case'a':case'A':player.move(-20, 0);playerflag = 3;break;
            case'd':case'D':player.move(20, 0);playerflag = 4;break;
            case'r':case'R':
                if (score.getscore() >= 100) {
                    player.skill(sizeflag);score.addscore(-100);
                }break;
            case'1':player.first_skill(obstacles);break;
            case'2':
                if (player.second_skill()) {
                    start2 = time(nullptr);stopflag = true;
                }break;
            case'3':
                if (player.third_skill()) {
                    start3 = time(nullptr);sizeflag = true;
                }break;
            case' ': player.shoot(playerflag,sizeflag);break;
            }
        }
        // 刷新缓冲区
        FlushBatchDraw();
    }

    // 关闭双缓冲
    EndBatchDraw();
    MessageBoxW(hwnd, L"玩家死亡！", L"result", MB_OK);
    // 关闭图形窗口
    closegraph();
    return 0;
}
