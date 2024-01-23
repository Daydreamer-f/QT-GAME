#include "warning_page.h"
#include "ui_warning_page.h"
#include <QString>
#include <QLabel>
#include <QLayout>
#include <QTimer>
//#include <QMediaPlayer>
WARNING_PAGE::WARNING_PAGE(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WARNING_PAGE)
{
    setWindowTitle("信科教务重度依赖");
    setWindowIcon(QIcon(":/src/text_content/icon.png"));
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose, true);
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint|Qt::WindowMinimizeButtonHint| Qt::WindowCloseButtonHint|Qt::FramelessWindowHint);
    setFixedSize(this->width(),this->height());
    setWindowModality(Qt::ApplicationModal);
    ui->button->setText("CONTINUE");

}

WARNING_PAGE::~WARNING_PAGE()
{
    close();
    delete ui;
}
void WARNING_PAGE::init(QVector<QString> s){//从文件中读入所有即将显示的字符串
    str=s;
    std::reverse(str.begin(),str.end());
    if(str.size()){
        display(*str.rbegin(),1),str.pop_back();
    }
    if(!str.size()) ui->button->setText("CLOSE");
    return ;
}
void WARNING_PAGE::display(QString s, int num)
{
    // 禁用按钮并设置为灰色
    ui->button->setEnabled(false);
    ui->button->setStyleSheet("background-color: gray;");

    QString Character = s.left(num);
    ui->label->setText(Character);
    ui->label->setWordWrap(true);
    ui->label->setAlignment(Qt::AlignCenter);
//    QMediaPlayer *player = new QMediaPlayer;
//    QSound *sound = new QSound(":/src/text_content/music/type.wav");
//    sound->play();
    if (Character != s) {
        QTimer::singleShot(rand()%20+40, [this, s, num]() {
            display(s, num + 1);
        });
    } else {
        // 恢复按钮并设置回默认状态
        ui->button->setEnabled(true);
        ui->button->setStyleSheet(""); // 清除样式表，恢复默认样式
    }
}
void WARNING_PAGE::on_button_clicked()
{
    if(str.size()){
        display(*str.rbegin(),1),str.pop_back();
        if(!str.size()) ui->button->setText("CLOSE");
    }
    else close();

}

