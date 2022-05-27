#ifndef WORD_H
#define WORD_H
#include <QGraphicsOpacityEffect>
#include <QTimer>
#include <QLabel>
#include <QWidget>

class Word : public QLabel
{

    Q_OBJECT
    public:
    explicit Word(QWidget *parent = 0);

public:
    Word();
    void Work();
    void gaga();
    int gridNow;    //放到了哪个格子

    QTimer *opacity_timer = nullptr;
    QGraphicsOpacityEffect *effect = nullptr;

    bool onShow;    //是否正在显示
    float opa_level = 0;
    bool light = true;
    QWidget *pare;

    bool right = false;   //是否输入正确
    bool missed = false;  //是否被错过了

private slots:
    void opacitySlot();
    void opacity_timer_shutdown();

signals:
    void opacity_timer_stop();  //运行结束的信号
    void gridsCondition(int x);  //控制当前grid的状态
};

#endif // WORD_H




