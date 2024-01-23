#ifndef GAMESERVER_H
#define GAMESERVER_H
#include <QString>
#include <QList>
#include <QFile>
#include <QPair>
#include <QTextStream>
#define ll long long
#define g0(a) memset(a,0,sizeof(a))
#define vecs QVector<QString>
inline int read();
int Rand(int x,int y);
class game_player;
struct Infor{
    int Math,Cs,Physics,Eng,Pol,Gym,ex=0;
    //专项能力 [0,100] [0,100] [0,100] [0,100] [0,100] [0,100]
    //ex 表示额外能力
    int Friend=0;
    int npy;
};//属性类
struct Time
{
    int week_,day_,id_;
    //周，天， 段;
    Time(int x,int y,int z):week_(x),day_(y),id_(z){;}
    QString dw[10]={"一","二","三","四","五","六","日"};
    QString a[200]={"上午","下午","晚上"};
    public:
    QString ask_week();
        QString ask_day();
    QString ask_id_();
        QString Get_time_day_id_();
    QString Get_time();
    //把时间转换为字符型
    void operator ++();
    void operator = (Time B);
    bool operator == (Time B);
};
#define vect QVector<Time>
vecs Cin(QString File);
//将读入的文件转换为字符型 含有个数
class course_{
    public:
    int credit_,add_Mark=0,go_times=0,type_,Mark_=0,av;
    //学分,加分分数,上课次数，课程类型(=1表示数学课 ＝2表示物理 =3表示cs =4通选 =5英语 ＝6政治 =7体育 ) 得分,需要的精力
    int vitality_=0;
    //精力 就是你总共分配的精力 用于计算结果 用时间来量化 总时间21*6=144
    public:
    QString Name;
    //课名
    vect sche_;//最多三个时间段
    course_(int A,int B,int C,QString D,vect tmp):credit_(A),type_(B),av(C),Name(D),sche_(tmp){
    }//通过课名关联介绍，保证没有重复的课名
    void go_(int t);
    void Answer_();
    void Study(int t);
    int _credit_();
    QString Name_();
    vect Time_();
    private:
    bool pass_();
    public:
    double Gpa();
    void Bingo_(game_player& p);
    //结束某门课程，计算得分
};
//21*6*3 学分=学时
QString S(char c);
vecs SS(QString c);
class event_{
    public:
    int add_ex,add_friend,add_v,tp;
    int Npy;
    vecs introduce_;
    //tp=0活动 tp=1课程 tp=2课外学习课程
    Time c;//活动时间
    int _id;//课程编号
    event_(int a,int b,int C,int d,int e,int f,Time g,vecs u):add_ex(a),add_friend(b),add_v(C),_id(d),tp(e),Npy(f),c(g),introduce_(u){}
    void operator=(event_ B);
    vecs ask_introduce(){return introduce_;}

};//需要玩家对于每一个小的板块输入的数的总和<=6(限制！！！)
vecs ask_role_information(int id);
class game_player{
    public:
    QVector<event_> vec;
    QVector<course_> My_course_available[5];//后台所有课程
    QVector<event_> My_event_available[5];//后台所有活动 包含已选课程！！
    bool vis_course[5][100];//是否选择第i周期的某门课
    //每个周期的事儿=课程+活动 活动是临时跳出来的
    int energe_ [5][8][4];//已经消耗的精力
    Time clock_;
    Infor v;
    int pass_credit=0,fail_credit=0,vitality_=0;

    game_player(int id);
    //生成一个编号为id的角色
    std::tuple<int,int,int> ask_time();//查询时间
    QString Label_time();
    QPair<bool,vecs> choose_course(int w,int id);
    QVector<vecs> Now_event();
    double Get_gpa();
    double Get_gpa(int w);
    QString Complete(int x);
    void add_clock();
    QVector<vecs> ask_course_available(int week_);
    //只能查询 不能修改 通过.Mark 计算得分
    vecs ask_rule();
    vecs Game_over();
    QPair<bool,vecs> participate_(int id);//参加某门活动，影响
    QVector<vecs> now_course();
};//游戏玩家类
extern game_player* PLAYER;
#endif // GAMESERVER_H
