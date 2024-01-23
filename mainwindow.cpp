#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);    // 禁止最大化按钮
    setFixedSize(this->width(),this->height());// 禁止拖动窗口大小
    setWindowTitle("信科教务重度依赖");
    setWindowIcon(QIcon("../PKUGAME/icon.png"));
    setAttribute(Qt::WA_DeleteOnClose, true);
    show();
    showFullScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
}

