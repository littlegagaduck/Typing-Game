#include "importword.h"
#include "ui_importword.h"
#include "mainwindow.h"
#include "game.h"

ImportWord::ImportWord(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ImportWord)
{
    ui->setupUi(this);
    //固定大小0
    setFixedSize(800,600);
    //设置图标
    setWindowIcon(QIcon(":/res/typing.ico"));
    setWindowTitle("Typing Game");

    //菜单退出
    connect(ui->actionQuit,&QAction::triggered,[=](){
        this->close();
    });
    connect(ui->actionRestart,&QAction::triggered,[=](){
        MainWindow *now =new MainWindow();
        this->hide();
        now->show();
    });

    ui->textEdit->setFontFamily("Arial");
    ui->textEdit->setFontPointSize(14);
}

ImportWord::~ImportWord()
{
    delete ui;
}

void ImportWord::on_pushButton_clicked()
{
    QString s = ui->textEdit->toPlainText();
    game *next=new game();
    connect(this,SIGNAL(importStr(QString &)),next,SLOT(importStr(QString &)));
    emit importStr(s);
    this->hide();
    next->show();
}

