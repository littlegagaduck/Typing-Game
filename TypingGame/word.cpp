#include "word.h"
#include <QGraphicsOpacityEffect>
#include <QTimer>
#include <QLabel>
#include <QEventLoop>

Word::Word(QWidget *parent)
    : QLabel(parent)
{
    pare=parent;

}

void Word::Work() {
    effect = new QGraphicsOpacityEffect(pare);
    effect->setOpacity(opa_level);
    this -> setGraphicsEffect(effect);
    this->setVisible(true);
    opacity_timer = new QTimer(this);
    connect(opacity_timer,SIGNAL(timeout()),this,SLOT(opacitySlot()));
    opacity_timer -> start(30);

    connect(this,SIGNAL(opacity_timer_stop()),this, SLOT(opacity_timer_shutdown()));
}

void Word::opacitySlot()
{
    if(light)  //淡入
    {
        opa_level += 0.01;
        effect->setOpacity(opa_level);
        this -> setGraphicsEffect(effect);
        if(opa_level > 1){
//            QEventLoop eventloop;
//            QTimer::singleShot(3000, &eventloop, SLOT(quit()));	//持续3秒
//            eventloop.exec();
            light = false;
        }
    }
    else  //淡出
    {
        opa_level -= 0.02;
        effect->setOpacity(opa_level);
        this -> setGraphicsEffect(effect);
        if(opa_level < 0){
            this -> hide();
            this->onShow = false;
            if(!this->right) missed = true;
            emit gridsCondition(gridNow);
            emit opacity_timer_stop();
        }
    }
}

void Word::opacity_timer_shutdown()
{
    opacity_timer -> stop();
}
