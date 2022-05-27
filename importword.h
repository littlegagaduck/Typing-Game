#ifndef IMPORTWORD_H
#define IMPORTWORD_H

#include <QMainWindow>

namespace Ui {
class ImportWord;
}

class ImportWord : public QMainWindow
{
    Q_OBJECT

public:
    explicit ImportWord(QWidget *parent = nullptr);
    ~ImportWord();

private slots:
    void on_pushButton_clicked();

signals:
    void importStr(QString &);

private:
    Ui::ImportWord *ui;
};

#endif // IMPORTWORD_H
