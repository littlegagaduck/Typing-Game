#include "game.h"
#include "ui_game.h"
#include "mainwindow.h"
#include "word.h"
#include "QMessageBox"

game::game(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::game)
{
    ui->setupUi(this);
    //固定大小0
    setFixedSize(800,600);
    //设置图标
    setWindowIcon(QIcon(":/res/typing.ico"));
    setWindowTitle("Typing Game");

    //菜单退出
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });
    connect(ui->actionRestart,&QAction::triggered,[=](){
        MainWindow *now =new MainWindow();
        this->hide();
        now->show();
    });

//    Word *word =new Word(this);
//    word -> setStyleSheet("color:black;font-size:24pt;font-family:黑体;");
//    word->move(150,150);
//    word->setText("gagaga");
//    word->setVisible(false);
//    word->Work();

    //初始化grid
    int cnt=0;
    for(int i=0;i<8;i++) {
        for(int j=0;j<4;j++) {
            grids[cnt].x=50+j*175;
            grids[cnt].y=50+i*50;\
            grids[cnt++].inUse=false;
        }
    }
}

void game::importStr(QString &s) {
    int length=s.length();
    int start=0,now=0;
    while(now<length) {
        while(now<length&&!((s[now]>='a'&&s[now]<='z')||(s[now]>='A'&&s[now]<='Z'))){
            now++;
        }
        start=now;
        int len=0;
        while(now<length&&((s[now]>='a'&&s[now]<='z')||(s[now]>='A'&&s[now]<='Z'))){
            len++;
            now++;
        }
        ans[cnt++]=s.mid(start,len);
        now++;
    }
    if(ans[cnt-1] == "") cnt--;
    for(int i=0;i<cnt;i++){
        ans[i]=ans[i].toLower();
    }

    for(int i=0;i<cnt;i++) {
        words[i]=new Word(this);
        words[i] -> setStyleSheet("color:black;font-size:16pt;font-family:Arial;");
//        words[i]->move(150,150);
        words[i]->setText(ans[i]);
        words[i]->setVisible(false);
//        words[i]->Work();
    }
}

game::~game()
{
    delete ui;
}

void game::on_pushButton_clicked()
{
    //开始游戏
//    for(int i=0;i<32;i++) {
//        words[i]->move(grids[i].x,grids[i].y);
//        words[i]->Work();
//    }
//    rand()%28     随机选择grids中的一个

    //启动定时器
    myTimer.start(2000);

    //监听定时器的信号 每隔10毫秒会抛出一个信号
    connect(&myTimer, &QTimer::timeout,[=](){
        if(cntWords < cnt) {
            int now=rand() % 28;
            while(grids[now].inUse) {
                now=rand() % 28;
            }
            grids[now].inUse=true;
            words[cntWords]->move(grids[now].x , grids[now].y);
            words[cntWords]->Work();
            words[cntWords]->gridNow=now;
            words[cntWords]->onShow=true;
            connect(words[cntWords],SIGNAL(gridsCondition(int)),this,SLOT(gridsCondition(int)));
            cntWords++;
        }
        else {
            if(cntQuit >= 2) {
                myTimer.stop();
                if(!resulted) {
                    resulted = true;
                    result();
                }
            }
            else cntQuit++;
        }
    });
}

//接受某个words时间已经到了  只能时间到了之后格子才能再次使用
void game::gridsCondition(int x)
{
    grids[x].inUse=false;
}


void game::on_lineEdit_returnPressed()
{
    QString nowInput=ui->lineEdit->text();
    ui->lineEdit->clear();

    bool flag = false;  //标识是否输入正确
    bool quit = false;  //判断是否结束运行
    for(int i = 0 ; i < cnt ; i++) {
        if(!words[i]->onShow) continue;
        if(words[i]->text() == nowInput){
            words[i]->onShow = false;
            words[i]->setVisible(false);
            words[i]->right = true;
            flag = true;
            if(i == cnt - 1) quit = true;
        }
    }
    if(!flag)
        wrong++;
    if(quit && !resulted) {
        qDebug() << "yya";
        resulted = true;
        result();
    }
}

void game::result() {
    int right = 0;
    int missed = 0;
    for(int i = 0 ; i < cnt ; i++) {
        if(words[i]->right) right++;
        else missed++;
    }

    QString dlgTitle="result";
    QString strInfo = "right : ";
    strInfo += QString ::number(right);
    strInfo += "\nwrong : ";
    strInfo += QString ::number(wrong);
    strInfo += "\nmissed : ";
    strInfo += QString ::number(missed);
    strInfo += "\nComing back to the main page";

    int chos = QMessageBox::information(this, dlgTitle, strInfo, QMessageBox::Ok, QMessageBox::NoButton);

    if(chos == QMessageBox::Ok) {
        MainWindow *now =new MainWindow();
        this->hide();
        now->show();
    }
    else {
        MainWindow *now =new MainWindow();
        this->hide();
        now->show();
    }
}

