/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *video;
    QLabel *video1;
    QDialogButtonBox *buttonBox;
    QFrame *frame;
    QLabel *loseLabel;
    QSlider *loseSlider;
    QLabel *loseNum;
    QPushButton *losePushButton;
    QLabel *decodeLabel;
    QLabel *decodeRate;
    QLabel *relayLabel;
    QLabel *relayNum;
    QLabel *afLabel;
    QLabel *afNum;
    QLabel *dfLabel;
    QLabel *deNum;
    QFrame *frame_2;
    QLabel *loseLabel1;
    QSlider *loseSlider1;
    QLabel *loseNum1;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(479, 392);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        video = new QLabel(centralWidget);
        video->setObjectName(QStringLiteral("video"));
        video->setGeometry(QRect(0, 0, 480, 272));
        sizePolicy.setHeightForWidth(video->sizePolicy().hasHeightForWidth());
        video->setSizePolicy(sizePolicy);
        video->setFrameShape(QFrame::Box);
        video->setFrameShadow(QFrame::Raised);
        video1 = new QLabel(centralWidget);
        video1->setObjectName(QStringLiteral("video1"));
        video1->setGeometry(QRect(490, 0, 480, 272));
        video1->setFrameShape(QFrame::Box);
        video1->setFrameShadow(QFrame::Raised);
        buttonBox = new QDialogButtonBox(centralWidget);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(800, 490, 156, 23));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        frame = new QFrame(centralWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(0, 280, 481, 191));
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Raised);
        loseLabel = new QLabel(frame);
        loseLabel->setObjectName(QStringLiteral("loseLabel"));
        loseLabel->setGeometry(QRect(40, 100, 70, 20));
        loseSlider = new QSlider(frame);
        loseSlider->setObjectName(QStringLiteral("loseSlider"));
        loseSlider->setGeometry(QRect(160, 100, 160, 20));
        loseSlider->setOrientation(Qt::Horizontal);
        loseNum = new QLabel(frame);
        loseNum->setObjectName(QStringLiteral("loseNum"));
        loseNum->setGeometry(QRect(120, 100, 35, 20));
        losePushButton = new QPushButton(frame);
        losePushButton->setObjectName(QStringLiteral("losePushButton"));
        losePushButton->setGeometry(QRect(350, 100, 50, 20));
        decodeLabel = new QLabel(frame);
        decodeLabel->setObjectName(QStringLiteral("decodeLabel"));
        decodeLabel->setGeometry(QRect(40, 120, 110, 20));
        decodeRate = new QLabel(frame);
        decodeRate->setObjectName(QStringLiteral("decodeRate"));
        decodeRate->setGeometry(QRect(160, 120, 35, 20));
        relayLabel = new QLabel(frame);
        relayLabel->setObjectName(QStringLiteral("relayLabel"));
        relayLabel->setGeometry(QRect(30, 20, 91, 16));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        relayLabel->setFont(font);
        relayNum = new QLabel(frame);
        relayNum->setObjectName(QStringLiteral("relayNum"));
        relayNum->setGeometry(QRect(130, 20, 31, 16));
        relayNum->setFont(font);
        afLabel = new QLabel(frame);
        afLabel->setObjectName(QStringLiteral("afLabel"));
        afLabel->setGeometry(QRect(30, 40, 91, 16));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setItalic(false);
        font1.setWeight(75);
        afLabel->setFont(font1);
        afNum = new QLabel(frame);
        afNum->setObjectName(QStringLiteral("afNum"));
        afNum->setGeometry(QRect(130, 40, 111, 16));
        afNum->setFont(font);
        dfLabel = new QLabel(frame);
        dfLabel->setObjectName(QStringLiteral("dfLabel"));
        dfLabel->setGeometry(QRect(250, 40, 91, 16));
        dfLabel->setFont(font);
        deNum = new QLabel(frame);
        deNum->setObjectName(QStringLiteral("deNum"));
        deNum->setGeometry(QRect(350, 40, 121, 16));
        deNum->setFont(font);
        frame_2 = new QFrame(centralWidget);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setGeometry(QRect(490, 280, 480, 191));
        frame_2->setFrameShape(QFrame::Box);
        frame_2->setFrameShadow(QFrame::Raised);
        loseLabel1 = new QLabel(frame_2);
        loseLabel1->setObjectName(QStringLiteral("loseLabel1"));
        loseLabel1->setGeometry(QRect(40, 20, 70, 20));
        loseSlider1 = new QSlider(frame_2);
        loseSlider1->setObjectName(QStringLiteral("loseSlider1"));
        loseSlider1->setGeometry(QRect(175, 20, 160, 20));
        loseSlider1->setOrientation(Qt::Horizontal);
        loseNum1 = new QLabel(frame_2);
        loseNum1->setObjectName(QStringLiteral("loseNum1"));
        loseNum1->setGeometry(QRect(125, 20, 35, 20));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 479, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "demoVideo", 0));
        video->setText(QApplication::translate("MainWindow", "video", 0));
        video1->setText(QApplication::translate("MainWindow", "video1", 0));
        loseLabel->setText(QApplication::translate("MainWindow", "\346\250\241\346\213\237\344\270\242\345\214\205\347\216\207\357\274\232", 0));
        loseNum->setText(QApplication::translate("MainWindow", "0%", 0));
        losePushButton->setText(QApplication::translate("MainWindow", "\347\241\256\350\256\244", 0));
        decodeLabel->setText(QApplication::translate("MainWindow", "Raptor\350\247\243\347\240\201\346\210\220\345\212\237\347\216\207\357\274\232", 0));
        decodeRate->setText(QApplication::translate("MainWindow", "100%", 0));
        relayLabel->setText(QApplication::translate("MainWindow", "\344\270\255\347\273\247\350\212\202\347\202\271\346\200\273\346\225\260\357\274\232", 0));
        relayNum->setText(QApplication::translate("MainWindow", "6", 0));
        afLabel->setText(QApplication::translate("MainWindow", "\346\224\276\345\244\247\344\270\255\347\273\247\347\274\226\345\217\267\357\274\232", 0));
        afNum->setText(QApplication::translate("MainWindow", "1,3,6", 0));
        dfLabel->setText(QApplication::translate("MainWindow", "\350\257\221\347\240\201\344\270\255\347\273\247\347\274\226\345\217\267\357\274\232", 0));
        deNum->setText(QApplication::translate("MainWindow", "2,4,5", 0));
        loseLabel1->setText(QApplication::translate("MainWindow", "\346\250\241\346\213\237\344\270\242\345\214\205\347\216\207\357\274\232", 0));
        loseNum1->setText(QApplication::translate("MainWindow", "0%", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
