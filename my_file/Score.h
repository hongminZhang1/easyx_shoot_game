//计分类
class Score {
	int score;//分数
	int x_;
	int y_;
	int total_score;
public:
	Score(int x=W-100,int y=0):score(0),total_score(0),x_(x),y_(y){}
	void show() {//显示分数
		settextcolor(WHITE);//白色
		settextstyle(20, 0, "Arial Rounded MT");
		char s[20] = { 0 };
		sprintf_s(s, sizeof(s), "得分:%d", score);
		outtextxy(x_,y_,s);
		sprintf_s(s, sizeof(s), "总计:%d", total_score);
		outtextxy(x_, y_+20, s);
	}
	void addscore(int d) {//增加分数
		if (d > 0)total_score += d;
		score += d;
	}
	int get_total()const  {
		return total_score;
	}
	int getscore() {
		return score;
	}
};
