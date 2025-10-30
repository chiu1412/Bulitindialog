#include "dialog.h"
#include <QColorDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QFontDialog>
#include <QInputDialog>
#include <QProgressDialog>
#include <QGridLayout>
#include <QErrorMessage>
#include <QCoreApplication> // For processEvents()

#include <QtPrintSupport/qprinter.h>
#include <QtPrintSupport/qpagesetupdialog.h>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrintPreviewDialog>

dialog::dialog(QWidget *parent)
    : QDialog(parent)
{
    QGridLayout *gridlayout =new QGridLayout;
    displayTextEdit = new QTextEdit(QStringLiteral("Qt標準通用對話盒"));
    colorPushBtn= new QPushButton(QStringLiteral("顏色對話盒"));
    errorPushBtn=  new QPushButton(QStringLiteral("錯誤訊息盒"));
    filePushBtn=new QPushButton(QStringLiteral("檔案對話盒"));
    fontPushBtn=new QPushButton(QStringLiteral("字體對話盒"));
    inputPushBtn=new QPushButton(QStringLiteral("輸入對話盒"));
    pagePushBtn =new QPushButton(QStringLiteral("頁面設定對話盒"));
    progressPushBtn= new QPushButton(QStringLiteral("進度對話盒"));
    printPushBtn = new QPushButton(QStringLiteral("列印對話盒"));
    textColorPushBtn = new QPushButton(QStringLiteral("更改文字顏色"));
    gridlayout->addWidget(colorPushBtn,0,0,1,1);
    gridlayout->addWidget(errorPushBtn,0,1,1,1);
    gridlayout->addWidget(filePushBtn,0,2,1,1);
    gridlayout->addWidget(fontPushBtn,1,0,1,1);
    gridlayout->addWidget(inputPushBtn,1,1,1,1);
    gridlayout->addWidget(pagePushBtn,1,2,1,1);
    gridlayout->addWidget(progressPushBtn,2,0,1,1);
    gridlayout->addWidget(printPushBtn,2,1,1,1);
    gridlayout->addWidget(displayTextEdit,3,0,3,3);
    gridlayout->addWidget(textColorPushBtn, 2, 2, 1, 1);

    setLayout(gridlayout);
    setWindowTitle(QStringLiteral("內建對話盒展示"));
    resize(400,300);

    connect(colorPushBtn, SIGNAL(clicked()), this, SLOT(doPushBtn()));
    connect(errorPushBtn, SIGNAL(clicked()), this, SLOT(doPushBtn()));
    connect(filePushBtn, SIGNAL(clicked()), this, SLOT(doPushBtn()));
    connect(fontPushBtn, SIGNAL(clicked()), this, SLOT(doPushBtn()));
    connect(inputPushBtn, SIGNAL(clicked()), this, SLOT(doPushBtn()));
    connect(pagePushBtn, SIGNAL(clicked()), this, SLOT(doPushBtn()));
    connect(progressPushBtn, SIGNAL(clicked()), this, SLOT(doPushBtn()));
    connect(printPushBtn, SIGNAL(clicked()), this, SLOT(doPushBtn()));
    connect(textColorPushBtn, SIGNAL(clicked()), this, SLOT(doPushBtn()));
}
void dialog::doPushBtn()
{
    QPushButton* btn =qobject_cast<QPushButton*>(sender());
    if (btn==colorPushBtn){
        QPalette palette=displayTextEdit->palette();
        const QColor &color =
            QColorDialog::getColor(palette.color(QPalette::Base),
                                   this,QStringLiteral("設定背景顏色"));
        if (color.isValid())
        {
            // 設置 QTextEdit 的背景顏色
            palette.setColor(QPalette::Base, color);
            displayTextEdit->setPalette(palette);
        }
    }
    if (btn==errorPushBtn)
    {
        QErrorMessage box(this);
        box.setWindowTitle(QStringLiteral("錯誤信息盒"));
        box.showMessage(QStringLiteral("錯誤信息盒實例xx:"));
        box.showMessage(QStringLiteral("錯誤信息盒實例yy:"));
        box.showMessage(QStringLiteral("錯誤信息盒實例zz:"));
        box.exec();
    }
    if(btn==filePushBtn)
    {
        QString fileName =QFileDialog::getOpenFileName(this,
                                                        QStringLiteral("打開檔案"),".",QStringLiteral("任何檔案(*.*)"));
        displayTextEdit->setText(fileName);
    }
    if (btn == fontPushBtn){
        bool ok;
        const QFont& font = QFontDialog::getFont(&ok,
                                                 displayTextEdit->font(),
                                                 this,
                                                 QStringLiteral("字體對話盒"));
        if (ok)
        {
            displayTextEdit->setFont(font);}
    }
    if (btn == inputPushBtn)
    {
        bool ok;
        QString text = QInputDialog::getText(this,
                                             QStringLiteral("輸入對話盒"),
                                             QStringLiteral("輸入文字"),
                                             QLineEdit::Normal,
                                             QDir::home().dirName(),
                                             &ok
                                             );
        if (ok && !text.isEmpty())
        {
            displayTextEdit->setText(text);
        }
    }
    if (btn == pagePushBtn)
    {
        QPrinter printer(QPrinter::HighResolution);
        QPageSetupDialog* dlg = new QPageSetupDialog(&printer, this);
        dlg->setWindowTitle(QStringLiteral("頁面設定對話方塊"));
        if (dlg->exec() == QDialog::Accepted)
        {

        }
    }
    if (btn == progressPushBtn)
    {
        QProgressDialog progress(QStringLiteral("正在複製檔案..."),
                                 QStringLiteral("取消"), 0, 10000, this);
        progress.setWindowTitle(QStringLiteral("進度對話方塊"));
        progress.show();

        for (int i=0; i<10000; i++)
        {
            progress.setValue(i);
            qApp->processEvents(); // 處理 UI 事件，保持視窗響應
            if (progress.wasCanceled())
                break;
            qDebug() << i; // 輸出當前進度到除錯視窗
        }
        progress.setValue(10000); // 確保進度條達到 100%
    }
    if (btn == printPushBtn)
    {
        QPrinter printer(QPrinter::HighResolution);
        QPrintDialog dialog(&printer, this);

        // 如果對話框執行結果不是 QDialog::Accepted (即使用者點擊了取消)
        if (dialog.exec() != QDialog::Accepted)
            return;

        // 如果執行到這裡，表示使用者已點擊「列印」
        // 實際的列印邏輯（例如 printer.begin() 和繪製內容）將放在這裡
    }
    if (btn == textColorPushBtn)
    {
        // 彈出顏色對話框，預設顏色使用當前文字顏色
        QColor color = QColorDialog::getColor(displayTextEdit->textColor(),
                                              this,
                                              QStringLiteral("選擇文字顏色"));

        if (color.isValid())
        {
            // 1. 創建一個文字格式物件
            QTextCharFormat format;

            // 2. 設定前景顏色 (即文字顏色)
            format.setForeground(QBrush(color));

            // 3. 獲取 QTextEdit 的文件游標
            QTextCursor cursor = displayTextEdit->textCursor();

            // 4. 選取 QTextEdit 中的所有文字
            cursor.select(QTextCursor::Document);

            // 5. 將新的文字格式應用到選取的所有文字上
            cursor.mergeCharFormat(format);

            // 6. 恢復游標到文件末尾（可選，讓後續輸入在新位置）
            displayTextEdit->setTextCursor(cursor);
        }
    }
}
dialog::~dialog() {}
