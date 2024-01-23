#include <QString>
#include <QList>
#include <QFile>
#include <QPair>
#include <QtCore>
#include <QTextStream>
#include <iostream>
#include "gameserver.h"
#define ll long long
#define o 1000005
#define g0(a) memset(a,0,sizeof(a))
#define vecs QVector<QString>
int Rand(int x, int y) {
    return x + 1ll * rand() * rand() * rand() % (y - x + 1);
}
class game_player;

QString Time::ask_week() {
    return "第" + dw[week_ - 1] + "学期";
}
QString Time::ask_day() {
    return "周" + dw[day_ - 1];
}
QString Time::ask_id_() {
    return a[id_ - 1];
}
QString Time::Get_time_day_id_() {
    QString s = ask_day() + ask_id_();
    return s;
}
QString Time::Get_time() {
    QString s = ask_week() + "  " + ask_day() + " " + ask_id_();
    return s;
}
//把时间转换为字符型
void Time::operator ++() {
    id_++;

    if (id_ == 4)
        id_ = 1, day_++;

    if (day_ == 8)
        day_ = 1, week_++;
}
bool Time::operator == (Time B) {
    return week_ == B.week_ && day_ == B.day_ && id_ == B.id_;
}
void Time::operator =(Time B) {
    week_ = B.week_, day_ = B.day_, id_ = B.id_;
}
#define vect QVector<Time>
vecs Cin(QString File) {
    QVector<QString> s;
    QFile inputFile(File);

    if (inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&inputFile);

        while (!in.atEnd()) {
            QString ss = in.readLine();
            s.push_back(ss);
        }

        inputFile.close();
    }

    return s;
}
//}//将读入的文件转换为Time型 含有个数
void course_::go_(int t) {
    go_times++;
    vitality_ += t;
}
void course_::Answer_() {
    if (type_ <= 5)
        add_Mark += std::max(type_ - 2, 0);

    if (type_ == 6)
        add_Mark += 2;
}//回答了一个问题
void course_::Study(int t) {
    vitality_ += t;
}
int course_::_credit_() {
    return credit_;
}
QString course_::Name_() {
    return Name;
}
vect course_::Time_() {
    return sche_;
}
bool course_::pass_() {
    return Mark_ >= 60;   //是否
}
double course_::Gpa() {
    return 4 - (100 - Mark_) * (100 - Mark_) * 3.0 / 1600;
}
//结束某门课程，计算得分
//21*6*3 学分=学时
QString S(char c) {
    QString s;
    s += c;
    return s;
}
vecs SS(QString c) {
    vecs tmp;
    tmp.push_back(c);
    return tmp;
}
void event_::operator = (event_ B) {
    add_ex = B.add_ex;
    add_friend = B.add_friend;
    add_v = B.add_v;
    tp = B.tp;
    Npy = B.Npy;
    introduce_ = B.introduce_;
    c = B.c;
    _id = B._id;
}
QPair<bool, vecs> participate_(game_player &p); //参加某门活动，影响
vecs ask_role_information(int id) {
    return Cin(":/src/text_content/character/" + S(id + '0') + ".txt");
}//获取第i角色的信息 vecs第一个参数是名字 后面的依次是介绍 id=0,1,2,3
game_player::game_player(int id) : clock_(1, 1, 1) {
    memset(energe_, 0, sizeof(energe_));
    memset(vis_course, 0, sizeof(vis_course));

    QFile file(":/src/text_content/character/" + QString::number(id) + "v.txt");

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        in >> v.Math >> v.Cs >> v.Physics >> v.Eng >> v.Pol >> v.Gym;
        in >> v.npy;
        file.close();
    }

    QFile courseFile(":/src/text_content/course/allclass.txt");

    if (courseFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream cin(&courseFile);

        int x, y, z, tp;

        while (!cin.atEnd()) {
            cin >> x >> y >> z;
            QString p;
            cin >> p;
            cin >> tp;
            int n;
            cin >> n;
            int ww = Rand(1, 3);
            vect tmp;

            for (int i = 0; i < n; i++) {
                if (!tp) {
                    tmp.push_back(Time(ww, Rand(1, 7), Rand(1, 3)));
                } else {
                    int B, C;
                    cin >> B >> C;
                    tmp.push_back(Time(tp, B, C));
                }
            }

            if (tp) {
                ww = tp;
            }

            My_course_available[ww].push_back(course_(x, y, z, p, tmp));
        }

        courseFile.close();
    }

    QFile activityFile(":/src/text_content/activity/allactivity" + QString::number(id) + ".txt");

    if (activityFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream II(&activityFile);

        for (int i = 1; i <= 3; i++) {
            int n;
            II >> n;

            while (n--) {
                int x, y, z, a, tot, MM, MMM;
                II >> x >> y >> z >> a >> MM >> MMM >> tot;

                vecs p;
                QString p_;

                while (tot--) {
                    II >> p_;
                    p.push_back(p_);
                }

                My_event_available[i].push_back(event_(x, y, z, -1, 0, a, Time(i, MM, MMM), p));
            }
        }

        activityFile.close();
    }
}
//生成一个编号为id的角色
std::tuple<int,int,int> game_player::ask_time() {
    return {clock_.id_,clock_.day_,clock_.week_};   //查询时间
}
QString game_player::Label_time() {
    return clock_.Get_time();
}
QPair<bool, vecs> game_player::choose_course(int w,
        int id) { //试图选择后台w周期的第id门课 id从0开始编号
    course_ now_ = My_course_available[w][id];
    vecs Warn_;
    bool tag = 0;
    int cre = now_.credit_;
    int s = My_course_available[w].size();
    for (int i = 0; i < s; i++)
        if(vis_course[w][i])
            {
                bool fl=0;
                for(auto t1:now_.sche_)
                    for(auto t2:My_course_available[w][i].sche_)
                    if(t1==t2&&!fl) fl=1,Warn_.push_back("你所选择的" + now_.Name_() + "与" + My_course_available[w][i].Name_() + "冲突!");
            }
    if (Warn_.empty())
        tag = 1, Warn_.push_back("你已成功选上该课!");

    if (tag) {
        vis_course[w][id] = 1;

        for (auto p : now_.sche_)
            My_event_available[w].push_back(event_(0, Rand(0, 4) == 4 ? 1 : 0, cre, id, 1, Rand(0, 1), p,
                                                   SS("去上" + now_.Name_())));

        bool vis_[4][8] = {0};
        int tmp_ = 5;

        while (tmp_--) {
            int t = Rand(1, 7), tt = Rand(1, 3);

            if (vis_[t][tt]) {
                ++cre;
                continue;
            }

            vis_[t][tt] = 1;
            int val = Rand(1, cre);
            QString tmp = "花费";
            tmp += QString::number(val) + "的时间去额外学习" + now_.Name_();
            My_event_available[w].push_back(event_(0, 0, val, id, 2, 0, Time(w, t, tt), SS(tmp)));
        }
    }

    return QPair<bool, vecs>(tag, Warn_);
}//tag=1，成功 tag=0,失败
QVector<vecs> game_player::Now_event() {
    vec.clear();
    for(auto p:My_event_available[clock_.week_])
        if(p.c==clock_)vec.push_back(p);
    QVector<vecs> Back;
    for(auto p:vec)
        Back.push_back(p.ask_introduce());
    return Back;
}
QVector<vecs> game_player::now_course(){
    int week_=clock_.week_;
    QVector<course_> tmp=My_course_available[week_];
    int m=tmp.size();
    QVector<vecs> ans;
    for(int i=0;i<m;i++)
    {
        if(!vis_course[week_][i])continue;
        QVector<QString> ss;
        ss.append(tmp[i].Name);
        QString owo="学分："+QString::number(tmp[i].credit_)+"\n"+"上课时间:";
        for (auto p : tmp[i].sche_)
            owo += p.Get_time(), owo += " ";
        ss.append(owo);
        ans.append(ss);
    }
    return ans;
}
double game_player::Get_gpa() {
    double A = 0;
    int B = 0;

    for (int w = 1; w <= clock_.week_; w++)
        for (int i = 0; i < My_course_available[w].size(); i++)
            if (vis_course[w][i] && My_course_available[w][i].Gpa() >= 1.00) {
                A += My_course_available[w][i].Gpa() * My_course_available[w][i]._credit_();
                B += My_course_available[w][i]._credit_();
            }

    if (B == 0)
        return -1;

    return A / B;
}
double game_player::Get_gpa(int w) {
    double A = 0;
    int B = 0;

    for (int i = 0; i < My_course_available[w].size(); i++)
        if (vis_course[w][i] && My_course_available[w][i].Gpa() >= 1.00) {
            A += My_course_available[w][i].Gpa() * My_course_available[w][i]._credit_();
            B += My_course_available[w][i]._credit_();
        }

    if (B == 0)
        return -1;

    return A / B;
}//计算第w周期的绩点
QString game_player::Complete(int x) {
    for (auto p : My_course_available[x]) {
        p.Bingo_(*this);
    }

    QString s1 = "亲爱的玩家，第";
    s1 += char(x + '0');
    s1 += "周期已经结束~";
    return s1;
}//结束x周期 注意先结束再结算绩点 需要前端调用
void game_player::add_clock() {
    ++clock_;
}
QVector<vecs> game_player::ask_course_available(int week_) {
    QVector<course_> tmp = My_course_available[week_];
    int m = tmp.size();
    QVector<vecs> ans;
    for (int i = 0; i < m; i++) {
        QVector<QString> ss;
        ss.append(tmp[i].Name);
        QString owo="学分："+QString::number(tmp[i].credit_)+"\n"+"上课时间:";
        for (auto p : tmp[i].sche_)
            owo += p.Get_time(), owo += " ";
        ss.append(owo);
        ans.append(ss);
    }
    return ans;
}
//只能查询 不能修改 通过.Mark 计算得分
vecs ask_rule() {
    return Cin(":/src/text_content/Rule.txt");
}//查询游戏规则
vecs Game_over() {
    return Cin(":/src/text_content/Rule.txt");
}//游戏结束
void course_::Bingo_(game_player &p) {
    add_Mark -= (sche_.size() - go_times) * (type_ - 1) / 2;
    int x;

    if (type_ == 1)
        x = sqrt(p.v.Math) * 10;

    if (type_ == 2)
        x = sqrt(p.v.Cs) * 10;

    if (type_ == 3)
        x = sqrt(p.v.Physics) * 10;

    if (type_ == 4)
        x = Rand(70, 90);

    if (type_ == 5)
        x = sqrt(p.v.Eng) * 10;

    if (type_ == 6)
        x = sqrt(p.v.Pol) * 10;

    if (type_ == 7)
        x = sqrt(p.v.Gym) * 10;

    x += add_Mark + Rand(-8, 8);

    if (x < 100)
        x += 1.0 * vitality_ / av * (100 - x);

    Mark_ = std::min(Mark_, 100);
    double gpa = Gpa();
    int m = 0;

    if (gpa >= 3.999)
        m = 5;
    else if (gpa >= 3.8)
        m = 4;
    else if (gpa >= 3.6)
        m = 3;
    else if (gpa >= 3.0)
        m = 2;
    else if (gpa >= 2.0)
        m = 1;

    if (type_ == 1)
        p.v.Friend += Rand(0, 2), p.v.Math += m;

    if (type_ == 2)
        p.v.Friend += Rand(0, 2), p.v.Cs += m;

    if (type_ == 3)
        p.v.Friend += Rand(0, 2) + 2, p.v.Physics += m;

    if (type_ == 4)
        p.v.Friend += Rand(0, 3), p.v.ex += m;

    if (type_ == 5)
        p.v.Friend += Rand(0, 2) + 2, p.v.Eng += m;

    if (type_ == 6)
        p.v.Friend += Rand(0, 2) + 2, p.v.Pol += m;

    if (type_ == 7)
        p.v.Friend += Rand(1, 5), p.v.Gym += m;

    if (gpa >= 1.00)
        p.pass_credit += credit_;
    else
        p.fail_credit += credit_;
}
QPair<bool,vecs> game_player::participate_(int id){
    bool tag=0;
    event_ tmp=vec[id];
    if(energe_[tmp.c.week_][tmp.c.day_][tmp.c.id_]+tmp.add_v>6)return QPair<bool,vecs>(0,SS("你已经做了够多事儿了！"));
    energe_[tmp.c.week_][tmp.c.day_][tmp.c.id_]+=tmp.add_v;
    v.ex+=tmp.add_ex,v.Friend+=tmp.add_friend,vitality_+=tmp.add_v;
    if(!v.npy&&Rand(1,100)<=tmp.Npy)v.npy=1;
    if(tmp._id>0){
        int w=tmp.c.week_;
        if(tmp.tp==1)My_course_available[w][tmp._id].go_(tmp.add_v);
        if(tmp.tp==2)My_course_available[w][tmp._id].vitality_+=tmp.add_v;
    }
    return  QPair<bool,vecs>(1,SS("成功！"));
}
