#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include "word.h"
#include "QTimer"

namespace Ui {
class game;
}

class game : public QMainWindow
{
    Q_OBJECT

public:
    explicit game(QWidget *parent = nullptr);
    ~game();
    Word *words[10000];
    int cnt;        //word的数量
    struct grid {
        int x,y;
        bool inUse;
    }grids[100];
    QTimer myTimer;
    int cntWords=0;  //计数，到第几个了

    int wrong=0;

    int cntQuit = 0;

    //显示结果
    void result();
    bool resulted = false;  //是否已经显示结果

private slots:
    void importStr(QString &);
    void on_pushButton_clicked();
    void gridsCondition(int x);  //控制当前grid的状态

    void on_lineEdit_returnPressed();

private:
    Ui::game *ui;
    QString ans[10000];
};

#endif // GAME_H
