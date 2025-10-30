#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QTextEdit>

class dialog : public QDialog
{
    Q_OBJECT

public:
    dialog(QWidget *parent = nullptr);
    ~dialog();
private:
    QTextEdit *displayTextEdit;
    QPushButton *colorPushBtn;
    QPushButton *errorPushBtn;
    QPushButton *filePushBtn;
    QPushButton *fontPushBtn;
    QPushButton *inputPushBtn;
    QPushButton *pagePushBtn;
    QPushButton *progressPushBtn;
    QPushButton *printPushBtn;
    QPushButton *textColorPushBtn;
private slots:
    void doPushBtn();
};
#endif // CBULITINDIALOG_H
