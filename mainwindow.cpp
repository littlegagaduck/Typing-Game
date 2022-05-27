#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "game.h"
#include "importword.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //固定大小0
    setFixedSize(800,500);
    //设置图标
    setWindowIcon(QIcon(":/res/typing.ico"));
    setWindowTitle("Typing Game");

    //菜单退出
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    ImportWord *now=new ImportWord;
    this->hide();
    now->show();
}
