/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "ui/toggleswitch.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *rootLayout;
    QHBoxLayout *mainLayout;
    QWidget *sidebar;
    QVBoxLayout *sidebarLayout;
    QLabel *appTitle;
    QLabel *navSectionLabel;
    QPushButton *btnPerformance;
    QPushButton *btnGraphics;
    QPushButton *btnFastFlags;
    QPushButton *btnSettings;
    QPushButton *btnAbout;
    QSpacerItem *sidebarSpacer;
    QLabel *statusChip;
    QPushButton *launchButton;
    QStackedWidget *pagesStack;
    QWidget *pagePerformance;
    QVBoxLayout *perfOuter;
    QScrollArea *perfScroll;
    QWidget *perfContent;
    QVBoxLayout *perfLayout;
    QLabel *perfEyebrow;
    QLabel *perfTitle;
    QLabel *perfSubtitle;
    QSpacerItem *perfSp1;
    QFrame *row1;
    QHBoxLayout *row1L;
    QLabel *icon1;
    QVBoxLayout *text1;
    QLabel *t1;
    QLabel *d1;
    ToggleSwitch *unlockFpsCheck;
    QFrame *row2;
    QHBoxLayout *row2L;
    QLabel *icon2;
    QVBoxLayout *text2;
    QLabel *t2;
    QLabel *d2;
    QComboBox *renderDistCombo;
    QFrame *row3;
    QHBoxLayout *row3L;
    QLabel *icon3;
    QVBoxLayout *text3;
    QLabel *t3;
    QLabel *d3;
    ToggleSwitch *shadowsCheck;
    QFrame *row4;
    QHBoxLayout *row4L;
    QLabel *icon4;
    QVBoxLayout *text4;
    QLabel *t4;
    QLabel *d4;
    ToggleSwitch *postFxCheck;
    QFrame *row5;
    QHBoxLayout *row5L;
    QLabel *icon5;
    QVBoxLayout *text5;
    QLabel *t5;
    QLabel *d5;
    QSpinBox *targetFpsSpin2;
    QFrame *row6;
    QHBoxLayout *row6L;
    QLabel *icon6;
    QVBoxLayout *text6;
    QLabel *t6;
    QLabel *d6;
    ToggleSwitch *pingBoostCheck;
    QSpacerItem *perfSp2;
    QWidget *pageGraphics;
    QVBoxLayout *gfxOuter;
    QScrollArea *gfxScroll;
    QWidget *gfxContent;
    QVBoxLayout *gfxLayout;
    QLabel *gfxEyebrow;
    QLabel *gfxTitle;
    QLabel *gfxSubtitle;
    QSpacerItem *gfxSp1;
    QFrame *grow1;
    QHBoxLayout *grow1L;
    QLabel *gicon1;
    QVBoxLayout *gtext1;
    QLabel *gt1;
    QLabel *gd1;
    ToggleSwitch *grassCheck;
    QFrame *grow2;
    QHBoxLayout *grow2L;
    QLabel *gicon2;
    QVBoxLayout *gtext2;
    QLabel *gt2;
    QLabel *gd2;
    QComboBox *texQualityCombo;
    QFrame *grow3;
    QHBoxLayout *grow3L;
    QLabel *gicon3;
    QVBoxLayout *gtext3;
    QLabel *gt3;
    QLabel *gd3;
    QComboBox *lightingCombo;
    QFrame *grow4;
    QHBoxLayout *grow4L;
    QLabel *gicon4;
    QVBoxLayout *gtext4;
    QLabel *gt4;
    QLabel *gd4;
    ToggleSwitch *aaCheck;
    QFrame *grow5;
    QHBoxLayout *grow5L;
    QLabel *gicon5;
    QVBoxLayout *gtext5;
    QLabel *gt5;
    QLabel *gd5;
    ToggleSwitch *bloomCheck;
    QFrame *grow6;
    QHBoxLayout *grow6L;
    QLabel *gicon6;
    QVBoxLayout *gtext6;
    QLabel *gt6;
    QLabel *gd6;
    ToggleSwitch *skyGrayCheck;
    QSpacerItem *gfxSp2;
    QWidget *pageFastFlags;
    QVBoxLayout *ffOuter;
    QScrollArea *ffScroll;
    QWidget *ffContent;
    QVBoxLayout *ffLayout;
    QLabel *ffEyebrow;
    QLabel *ffTitle;
    QLabel *ffSubtitle;
    QSpacerItem *ffSp1;
    QFrame *ffrow1;
    QHBoxLayout *ffrow1L;
    QLabel *fficon1;
    QVBoxLayout *fftext1;
    QLabel *fft1;
    QLabel *ffd1;
    QSpinBox *csgLodSpin;
    QFrame *ffrow2;
    QHBoxLayout *ffrow2L;
    QLabel *fficon2;
    QVBoxLayout *fftext2;
    QLabel *fft2;
    QLabel *ffd2;
    QSpinBox *frmQualitySpin;
    QFrame *ffrow3;
    QHBoxLayout *ffrow3L;
    QLabel *fficon3;
    QVBoxLayout *fftext3;
    QLabel *fft3;
    QLabel *ffd3;
    QSpinBox *targetFpsSpin;
    QSpacerItem *ffSp2;
    QFrame *ffCtaFrame;
    QHBoxLayout *ffCtaLayout;
    QVBoxLayout *ffCtaText;
    QLabel *ffCtaTitle;
    QLabel *ffCtaDesc;
    QPushButton *ffCustomButton;
    QFrame *presetsDivider;
    QLabel *ffSectionPresets;
    QFrame *presetsToggleRow;
    QHBoxLayout *presetsToggleLayout;
    QLabel *presetsToggleIcon;
    QVBoxLayout *presetsToggleText;
    QLabel *presetsToggleTitle;
    QLabel *presetsToggleDesc;
    ToggleSwitch *presetsToggle;
    QWidget *presetsContainer;
    QVBoxLayout *presetsContainerLayout;
    QFrame *presetCardPerf;
    QHBoxLayout *presetCardPerfLayout;
    QLabel *presetPerfIcon;
    QVBoxLayout *presetPerfText;
    QLabel *presetPerfTitle;
    QLabel *presetPerfDesc;
    QPushButton *presetPerfDetails;
    QPushButton *presetPerfApply;
    QFrame *presetCardBal;
    QHBoxLayout *presetCardBalLayout;
    QLabel *presetBalIcon;
    QVBoxLayout *presetBalText;
    QLabel *presetBalTitle;
    QLabel *presetBalDesc;
    QPushButton *presetBalDetails;
    QPushButton *presetBalApply;
    QFrame *presetCardQual;
    QHBoxLayout *presetCardQualLayout;
    QLabel *presetQualIcon;
    QVBoxLayout *presetQualText;
    QLabel *presetQualTitle;
    QLabel *presetQualDesc;
    QPushButton *presetQualDetails;
    QPushButton *presetQualApply;
    QSpacerItem *ffSp3;
    QWidget *pageSettings;
    QVBoxLayout *setOuter;
    QScrollArea *setScroll;
    QWidget *setContent;
    QVBoxLayout *setLayout;
    QLabel *setEyebrow;
    QLabel *setTitle;
    QLabel *setSubtitle;
    QSpacerItem *setSp1;
    QLabel *setSectionGeneral;
    QFrame *setRowUpdate;
    QHBoxLayout *setRowUpdateLayout;
    QLabel *setIconUpdate;
    QVBoxLayout *setTextUpdate;
    QLabel *setTitleUpdate;
    QLabel *setDescUpdate;
    ToggleSwitch *setToggleUpdate;
    QFrame *setRowStartup;
    QHBoxLayout *setRowStartupLayout;
    QLabel *setIconStartup;
    QVBoxLayout *setTextStartup;
    QLabel *setTitleStartup;
    QLabel *setDescStartup;
    ToggleSwitch *setToggleStartup;
    QLabel *setSectionLang;
    QFrame *setRowLang;
    QHBoxLayout *setRowLangLayout;
    QLabel *setIconLang;
    QVBoxLayout *setTextLang;
    QLabel *setTitleLang;
    QLabel *setDescLang;
    QComboBox *setLangCombo;
    QSpacerItem *setSp2;
    QWidget *pageAbout;
    QVBoxLayout *abtOuter;
    QScrollArea *abtScroll;
    QWidget *abtContent;
    QVBoxLayout *abtLayout;
    QLabel *abtEyebrow;
    QLabel *abtTitle;
    QLabel *abtSubtitle;
    QSpacerItem *abtSp1;
    QFrame *abtHero;
    QHBoxLayout *abtHeroLayout;
    QLabel *abtLogo;
    QVBoxLayout *abtHeroText;
    QLabel *abtHeroTitle;
    QLabel *abtHeroVersion;
    QLabel *abtHeroDesc;
    QFrame *abtLinks;
    QVBoxLayout *abtLinksLayout;
    QLabel *abtLinksTitle;
    QHBoxLayout *abtLinksRow;
    QPushButton *btnGithub;
    QPushButton *btnDocs;
    QPushButton *btnIssue;
    QFrame *abtCredits;
    QVBoxLayout *abtCreditsLayout;
    QLabel *abtCreditsTitle;
    QLabel *abtCreditsText;
    QSpacerItem *abtSp2;
    QFrame *footer;
    QHBoxLayout *footerLayout;
    QLabel *versionLabel;
    QLabel *updateLabel;
    QPushButton *updateButton;
    QProgressBar *progressBar;
    QSpacerItem *footerSpacer;
    QPushButton *resetButton;
    QPushButton *saveButton;
    QPushButton *closeButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1180, 760);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        rootLayout = new QVBoxLayout(centralWidget);
        rootLayout->setSpacing(0);
        rootLayout->setObjectName("rootLayout");
        rootLayout->setContentsMargins(0, 0, 0, 0);
        mainLayout = new QHBoxLayout();
        mainLayout->setSpacing(0);
        mainLayout->setObjectName("mainLayout");
        mainLayout->setContentsMargins(0, 0, 0, 0);
        sidebar = new QWidget(centralWidget);
        sidebar->setObjectName("sidebar");
        sidebar->setMinimumSize(QSize(230, 0));
        sidebar->setMaximumSize(QSize(230, 16777215));
        sidebarLayout = new QVBoxLayout(sidebar);
        sidebarLayout->setSpacing(4);
        sidebarLayout->setObjectName("sidebarLayout");
        sidebarLayout->setContentsMargins(0, 0, 0, 14);
        appTitle = new QLabel(sidebar);
        appTitle->setObjectName("appTitle");

        sidebarLayout->addWidget(appTitle);

        navSectionLabel = new QLabel(sidebar);
        navSectionLabel->setObjectName("navSectionLabel");

        sidebarLayout->addWidget(navSectionLabel);

        btnPerformance = new QPushButton(sidebar);
        btnPerformance->setObjectName("btnPerformance");
        btnPerformance->setCheckable(true);
        btnPerformance->setChecked(true);
        btnPerformance->setAutoExclusive(true);

        sidebarLayout->addWidget(btnPerformance);

        btnGraphics = new QPushButton(sidebar);
        btnGraphics->setObjectName("btnGraphics");
        btnGraphics->setCheckable(true);
        btnGraphics->setAutoExclusive(true);

        sidebarLayout->addWidget(btnGraphics);

        btnFastFlags = new QPushButton(sidebar);
        btnFastFlags->setObjectName("btnFastFlags");
        btnFastFlags->setCheckable(true);
        btnFastFlags->setAutoExclusive(true);

        sidebarLayout->addWidget(btnFastFlags);

        btnSettings = new QPushButton(sidebar);
        btnSettings->setObjectName("btnSettings");
        btnSettings->setCheckable(true);
        btnSettings->setAutoExclusive(true);

        sidebarLayout->addWidget(btnSettings);

        btnAbout = new QPushButton(sidebar);
        btnAbout->setObjectName("btnAbout");
        btnAbout->setCheckable(true);
        btnAbout->setAutoExclusive(true);

        sidebarLayout->addWidget(btnAbout);

        sidebarSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        sidebarLayout->addItem(sidebarSpacer);

        statusChip = new QLabel(sidebar);
        statusChip->setObjectName("statusChip");

        sidebarLayout->addWidget(statusChip);

        launchButton = new QPushButton(sidebar);
        launchButton->setObjectName("launchButton");

        sidebarLayout->addWidget(launchButton);


        mainLayout->addWidget(sidebar);

        pagesStack = new QStackedWidget(centralWidget);
        pagesStack->setObjectName("pagesStack");
        pagePerformance = new QWidget();
        pagePerformance->setObjectName("pagePerformance");
        perfOuter = new QVBoxLayout(pagePerformance);
        perfOuter->setSpacing(0);
        perfOuter->setObjectName("perfOuter");
        perfOuter->setContentsMargins(0, 0, 0, 0);
        perfScroll = new QScrollArea(pagePerformance);
        perfScroll->setObjectName("perfScroll");
        perfScroll->setWidgetResizable(true);
        perfScroll->setFrameShape(QFrame::NoFrame);
        perfContent = new QWidget();
        perfContent->setObjectName("perfContent");
        perfLayout = new QVBoxLayout(perfContent);
        perfLayout->setSpacing(10);
        perfLayout->setObjectName("perfLayout");
        perfLayout->setContentsMargins(40, 36, 40, 36);
        perfEyebrow = new QLabel(perfContent);
        perfEyebrow->setObjectName("perfEyebrow");

        perfLayout->addWidget(perfEyebrow);

        perfTitle = new QLabel(perfContent);
        perfTitle->setObjectName("perfTitle");

        perfLayout->addWidget(perfTitle);

        perfSubtitle = new QLabel(perfContent);
        perfSubtitle->setObjectName("perfSubtitle");

        perfLayout->addWidget(perfSubtitle);

        perfSp1 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        perfLayout->addItem(perfSp1);

        row1 = new QFrame(perfContent);
        row1->setObjectName("row1");
        row1L = new QHBoxLayout(row1);
        row1L->setSpacing(20);
        row1L->setObjectName("row1L");
        row1L->setContentsMargins(24, 20, 24, 20);
        icon1 = new QLabel(row1);
        icon1->setObjectName("icon1");

        row1L->addWidget(icon1);

        text1 = new QVBoxLayout();
        text1->setSpacing(3);
        text1->setObjectName("text1");
        t1 = new QLabel(row1);
        t1->setObjectName("t1");

        text1->addWidget(t1);

        d1 = new QLabel(row1);
        d1->setObjectName("d1");

        text1->addWidget(d1);


        row1L->addLayout(text1);

        unlockFpsCheck = new ToggleSwitch(row1);
        unlockFpsCheck->setObjectName("unlockFpsCheck");

        row1L->addWidget(unlockFpsCheck);


        perfLayout->addWidget(row1);

        row2 = new QFrame(perfContent);
        row2->setObjectName("row2");
        row2L = new QHBoxLayout(row2);
        row2L->setSpacing(20);
        row2L->setObjectName("row2L");
        row2L->setContentsMargins(24, 20, 24, 20);
        icon2 = new QLabel(row2);
        icon2->setObjectName("icon2");

        row2L->addWidget(icon2);

        text2 = new QVBoxLayout();
        text2->setSpacing(3);
        text2->setObjectName("text2");
        t2 = new QLabel(row2);
        t2->setObjectName("t2");

        text2->addWidget(t2);

        d2 = new QLabel(row2);
        d2->setObjectName("d2");

        text2->addWidget(d2);


        row2L->addLayout(text2);

        renderDistCombo = new QComboBox(row2);
        renderDistCombo->addItem(QString());
        renderDistCombo->addItem(QString());
        renderDistCombo->addItem(QString());
        renderDistCombo->setObjectName("renderDistCombo");
        renderDistCombo->setMinimumSize(QSize(140, 0));

        row2L->addWidget(renderDistCombo);


        perfLayout->addWidget(row2);

        row3 = new QFrame(perfContent);
        row3->setObjectName("row3");
        row3L = new QHBoxLayout(row3);
        row3L->setSpacing(20);
        row3L->setObjectName("row3L");
        row3L->setContentsMargins(24, 20, 24, 20);
        icon3 = new QLabel(row3);
        icon3->setObjectName("icon3");

        row3L->addWidget(icon3);

        text3 = new QVBoxLayout();
        text3->setSpacing(3);
        text3->setObjectName("text3");
        t3 = new QLabel(row3);
        t3->setObjectName("t3");

        text3->addWidget(t3);

        d3 = new QLabel(row3);
        d3->setObjectName("d3");

        text3->addWidget(d3);


        row3L->addLayout(text3);

        shadowsCheck = new ToggleSwitch(row3);
        shadowsCheck->setObjectName("shadowsCheck");

        row3L->addWidget(shadowsCheck);


        perfLayout->addWidget(row3);

        row4 = new QFrame(perfContent);
        row4->setObjectName("row4");
        row4L = new QHBoxLayout(row4);
        row4L->setSpacing(20);
        row4L->setObjectName("row4L");
        row4L->setContentsMargins(24, 20, 24, 20);
        icon4 = new QLabel(row4);
        icon4->setObjectName("icon4");

        row4L->addWidget(icon4);

        text4 = new QVBoxLayout();
        text4->setSpacing(3);
        text4->setObjectName("text4");
        t4 = new QLabel(row4);
        t4->setObjectName("t4");

        text4->addWidget(t4);

        d4 = new QLabel(row4);
        d4->setObjectName("d4");

        text4->addWidget(d4);


        row4L->addLayout(text4);

        postFxCheck = new ToggleSwitch(row4);
        postFxCheck->setObjectName("postFxCheck");

        row4L->addWidget(postFxCheck);


        perfLayout->addWidget(row4);

        row5 = new QFrame(perfContent);
        row5->setObjectName("row5");
        row5L = new QHBoxLayout(row5);
        row5L->setSpacing(20);
        row5L->setObjectName("row5L");
        row5L->setContentsMargins(24, 20, 24, 20);
        icon5 = new QLabel(row5);
        icon5->setObjectName("icon5");

        row5L->addWidget(icon5);

        text5 = new QVBoxLayout();
        text5->setSpacing(3);
        text5->setObjectName("text5");
        t5 = new QLabel(row5);
        t5->setObjectName("t5");

        text5->addWidget(t5);

        d5 = new QLabel(row5);
        d5->setObjectName("d5");

        text5->addWidget(d5);


        row5L->addLayout(text5);

        targetFpsSpin2 = new QSpinBox(row5);
        targetFpsSpin2->setObjectName("targetFpsSpin2");
        targetFpsSpin2->setMinimum(0);
        targetFpsSpin2->setMaximum(9999);
        targetFpsSpin2->setValue(240);
        targetFpsSpin2->setMinimumSize(QSize(120, 0));

        row5L->addWidget(targetFpsSpin2);


        perfLayout->addWidget(row5);

        row6 = new QFrame(perfContent);
        row6->setObjectName("row6");
        row6L = new QHBoxLayout(row6);
        row6L->setSpacing(20);
        row6L->setObjectName("row6L");
        row6L->setContentsMargins(24, 20, 24, 20);
        icon6 = new QLabel(row6);
        icon6->setObjectName("icon6");

        row6L->addWidget(icon6);

        text6 = new QVBoxLayout();
        text6->setSpacing(3);
        text6->setObjectName("text6");
        t6 = new QLabel(row6);
        t6->setObjectName("t6");

        text6->addWidget(t6);

        d6 = new QLabel(row6);
        d6->setObjectName("d6");

        text6->addWidget(d6);


        row6L->addLayout(text6);

        pingBoostCheck = new ToggleSwitch(row6);
        pingBoostCheck->setObjectName("pingBoostCheck");

        row6L->addWidget(pingBoostCheck);


        perfLayout->addWidget(row6);

        perfSp2 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        perfLayout->addItem(perfSp2);

        perfScroll->setWidget(perfContent);

        perfOuter->addWidget(perfScroll);

        pagesStack->addWidget(pagePerformance);
        pageGraphics = new QWidget();
        pageGraphics->setObjectName("pageGraphics");
        gfxOuter = new QVBoxLayout(pageGraphics);
        gfxOuter->setSpacing(0);
        gfxOuter->setObjectName("gfxOuter");
        gfxOuter->setContentsMargins(0, 0, 0, 0);
        gfxScroll = new QScrollArea(pageGraphics);
        gfxScroll->setObjectName("gfxScroll");
        gfxScroll->setWidgetResizable(true);
        gfxScroll->setFrameShape(QFrame::NoFrame);
        gfxContent = new QWidget();
        gfxContent->setObjectName("gfxContent");
        gfxLayout = new QVBoxLayout(gfxContent);
        gfxLayout->setSpacing(10);
        gfxLayout->setObjectName("gfxLayout");
        gfxLayout->setContentsMargins(40, 36, 40, 36);
        gfxEyebrow = new QLabel(gfxContent);
        gfxEyebrow->setObjectName("gfxEyebrow");

        gfxLayout->addWidget(gfxEyebrow);

        gfxTitle = new QLabel(gfxContent);
        gfxTitle->setObjectName("gfxTitle");

        gfxLayout->addWidget(gfxTitle);

        gfxSubtitle = new QLabel(gfxContent);
        gfxSubtitle->setObjectName("gfxSubtitle");

        gfxLayout->addWidget(gfxSubtitle);

        gfxSp1 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        gfxLayout->addItem(gfxSp1);

        grow1 = new QFrame(gfxContent);
        grow1->setObjectName("grow1");
        grow1L = new QHBoxLayout(grow1);
        grow1L->setSpacing(20);
        grow1L->setObjectName("grow1L");
        grow1L->setContentsMargins(24, 20, 24, 20);
        gicon1 = new QLabel(grow1);
        gicon1->setObjectName("gicon1");

        grow1L->addWidget(gicon1);

        gtext1 = new QVBoxLayout();
        gtext1->setSpacing(3);
        gtext1->setObjectName("gtext1");
        gt1 = new QLabel(grow1);
        gt1->setObjectName("gt1");

        gtext1->addWidget(gt1);

        gd1 = new QLabel(grow1);
        gd1->setObjectName("gd1");

        gtext1->addWidget(gd1);


        grow1L->addLayout(gtext1);

        grassCheck = new ToggleSwitch(grow1);
        grassCheck->setObjectName("grassCheck");

        grow1L->addWidget(grassCheck);


        gfxLayout->addWidget(grow1);

        grow2 = new QFrame(gfxContent);
        grow2->setObjectName("grow2");
        grow2L = new QHBoxLayout(grow2);
        grow2L->setSpacing(20);
        grow2L->setObjectName("grow2L");
        grow2L->setContentsMargins(24, 20, 24, 20);
        gicon2 = new QLabel(grow2);
        gicon2->setObjectName("gicon2");

        grow2L->addWidget(gicon2);

        gtext2 = new QVBoxLayout();
        gtext2->setSpacing(3);
        gtext2->setObjectName("gtext2");
        gt2 = new QLabel(grow2);
        gt2->setObjectName("gt2");

        gtext2->addWidget(gt2);

        gd2 = new QLabel(grow2);
        gd2->setObjectName("gd2");

        gtext2->addWidget(gd2);


        grow2L->addLayout(gtext2);

        texQualityCombo = new QComboBox(grow2);
        texQualityCombo->addItem(QString());
        texQualityCombo->addItem(QString());
        texQualityCombo->addItem(QString());
        texQualityCombo->addItem(QString());
        texQualityCombo->setObjectName("texQualityCombo");
        texQualityCombo->setMinimumSize(QSize(140, 0));

        grow2L->addWidget(texQualityCombo);


        gfxLayout->addWidget(grow2);

        grow3 = new QFrame(gfxContent);
        grow3->setObjectName("grow3");
        grow3L = new QHBoxLayout(grow3);
        grow3L->setSpacing(20);
        grow3L->setObjectName("grow3L");
        grow3L->setContentsMargins(24, 20, 24, 20);
        gicon3 = new QLabel(grow3);
        gicon3->setObjectName("gicon3");

        grow3L->addWidget(gicon3);

        gtext3 = new QVBoxLayout();
        gtext3->setSpacing(3);
        gtext3->setObjectName("gtext3");
        gt3 = new QLabel(grow3);
        gt3->setObjectName("gt3");

        gtext3->addWidget(gt3);

        gd3 = new QLabel(grow3);
        gd3->setObjectName("gd3");

        gtext3->addWidget(gd3);


        grow3L->addLayout(gtext3);

        lightingCombo = new QComboBox(grow3);
        lightingCombo->addItem(QString());
        lightingCombo->addItem(QString());
        lightingCombo->addItem(QString());
        lightingCombo->setObjectName("lightingCombo");
        lightingCombo->setMinimumSize(QSize(180, 0));

        grow3L->addWidget(lightingCombo);


        gfxLayout->addWidget(grow3);

        grow4 = new QFrame(gfxContent);
        grow4->setObjectName("grow4");
        grow4L = new QHBoxLayout(grow4);
        grow4L->setSpacing(20);
        grow4L->setObjectName("grow4L");
        grow4L->setContentsMargins(24, 20, 24, 20);
        gicon4 = new QLabel(grow4);
        gicon4->setObjectName("gicon4");

        grow4L->addWidget(gicon4);

        gtext4 = new QVBoxLayout();
        gtext4->setSpacing(3);
        gtext4->setObjectName("gtext4");
        gt4 = new QLabel(grow4);
        gt4->setObjectName("gt4");

        gtext4->addWidget(gt4);

        gd4 = new QLabel(grow4);
        gd4->setObjectName("gd4");

        gtext4->addWidget(gd4);


        grow4L->addLayout(gtext4);

        aaCheck = new ToggleSwitch(grow4);
        aaCheck->setObjectName("aaCheck");

        grow4L->addWidget(aaCheck);


        gfxLayout->addWidget(grow4);

        grow5 = new QFrame(gfxContent);
        grow5->setObjectName("grow5");
        grow5L = new QHBoxLayout(grow5);
        grow5L->setSpacing(20);
        grow5L->setObjectName("grow5L");
        grow5L->setContentsMargins(24, 20, 24, 20);
        gicon5 = new QLabel(grow5);
        gicon5->setObjectName("gicon5");

        grow5L->addWidget(gicon5);

        gtext5 = new QVBoxLayout();
        gtext5->setSpacing(3);
        gtext5->setObjectName("gtext5");
        gt5 = new QLabel(grow5);
        gt5->setObjectName("gt5");

        gtext5->addWidget(gt5);

        gd5 = new QLabel(grow5);
        gd5->setObjectName("gd5");

        gtext5->addWidget(gd5);


        grow5L->addLayout(gtext5);

        bloomCheck = new ToggleSwitch(grow5);
        bloomCheck->setObjectName("bloomCheck");

        grow5L->addWidget(bloomCheck);


        gfxLayout->addWidget(grow5);

        grow6 = new QFrame(gfxContent);
        grow6->setObjectName("grow6");
        grow6L = new QHBoxLayout(grow6);
        grow6L->setSpacing(20);
        grow6L->setObjectName("grow6L");
        grow6L->setContentsMargins(24, 20, 24, 20);
        gicon6 = new QLabel(grow6);
        gicon6->setObjectName("gicon6");

        grow6L->addWidget(gicon6);

        gtext6 = new QVBoxLayout();
        gtext6->setSpacing(3);
        gtext6->setObjectName("gtext6");
        gt6 = new QLabel(grow6);
        gt6->setObjectName("gt6");

        gtext6->addWidget(gt6);

        gd6 = new QLabel(grow6);
        gd6->setObjectName("gd6");

        gtext6->addWidget(gd6);


        grow6L->addLayout(gtext6);

        skyGrayCheck = new ToggleSwitch(grow6);
        skyGrayCheck->setObjectName("skyGrayCheck");

        grow6L->addWidget(skyGrayCheck);


        gfxLayout->addWidget(grow6);

        gfxSp2 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gfxLayout->addItem(gfxSp2);

        gfxScroll->setWidget(gfxContent);

        gfxOuter->addWidget(gfxScroll);

        pagesStack->addWidget(pageGraphics);
        pageFastFlags = new QWidget();
        pageFastFlags->setObjectName("pageFastFlags");
        ffOuter = new QVBoxLayout(pageFastFlags);
        ffOuter->setSpacing(0);
        ffOuter->setObjectName("ffOuter");
        ffOuter->setContentsMargins(0, 0, 0, 0);
        ffScroll = new QScrollArea(pageFastFlags);
        ffScroll->setObjectName("ffScroll");
        ffScroll->setWidgetResizable(true);
        ffScroll->setFrameShape(QFrame::NoFrame);
        ffContent = new QWidget();
        ffContent->setObjectName("ffContent");
        ffLayout = new QVBoxLayout(ffContent);
        ffLayout->setSpacing(10);
        ffLayout->setObjectName("ffLayout");
        ffLayout->setContentsMargins(40, 36, 40, 36);
        ffEyebrow = new QLabel(ffContent);
        ffEyebrow->setObjectName("ffEyebrow");

        ffLayout->addWidget(ffEyebrow);

        ffTitle = new QLabel(ffContent);
        ffTitle->setObjectName("ffTitle");

        ffLayout->addWidget(ffTitle);

        ffSubtitle = new QLabel(ffContent);
        ffSubtitle->setObjectName("ffSubtitle");

        ffLayout->addWidget(ffSubtitle);

        ffSp1 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        ffLayout->addItem(ffSp1);

        ffrow1 = new QFrame(ffContent);
        ffrow1->setObjectName("ffrow1");
        ffrow1L = new QHBoxLayout(ffrow1);
        ffrow1L->setSpacing(20);
        ffrow1L->setObjectName("ffrow1L");
        ffrow1L->setContentsMargins(24, 20, 24, 20);
        fficon1 = new QLabel(ffrow1);
        fficon1->setObjectName("fficon1");

        ffrow1L->addWidget(fficon1);

        fftext1 = new QVBoxLayout();
        fftext1->setSpacing(3);
        fftext1->setObjectName("fftext1");
        fft1 = new QLabel(ffrow1);
        fft1->setObjectName("fft1");

        fftext1->addWidget(fft1);

        ffd1 = new QLabel(ffrow1);
        ffd1->setObjectName("ffd1");

        fftext1->addWidget(ffd1);


        ffrow1L->addLayout(fftext1);

        csgLodSpin = new QSpinBox(ffrow1);
        csgLodSpin->setObjectName("csgLodSpin");
        csgLodSpin->setMinimum(0);
        csgLodSpin->setMaximum(1000);
        csgLodSpin->setValue(500);
        csgLodSpin->setMinimumSize(QSize(120, 0));

        ffrow1L->addWidget(csgLodSpin);


        ffLayout->addWidget(ffrow1);

        ffrow2 = new QFrame(ffContent);
        ffrow2->setObjectName("ffrow2");
        ffrow2L = new QHBoxLayout(ffrow2);
        ffrow2L->setSpacing(20);
        ffrow2L->setObjectName("ffrow2L");
        ffrow2L->setContentsMargins(24, 20, 24, 20);
        fficon2 = new QLabel(ffrow2);
        fficon2->setObjectName("fficon2");

        ffrow2L->addWidget(fficon2);

        fftext2 = new QVBoxLayout();
        fftext2->setSpacing(3);
        fftext2->setObjectName("fftext2");
        fft2 = new QLabel(ffrow2);
        fft2->setObjectName("fft2");

        fftext2->addWidget(fft2);

        ffd2 = new QLabel(ffrow2);
        ffd2->setObjectName("ffd2");

        fftext2->addWidget(ffd2);


        ffrow2L->addLayout(fftext2);

        frmQualitySpin = new QSpinBox(ffrow2);
        frmQualitySpin->setObjectName("frmQualitySpin");
        frmQualitySpin->setMinimum(1);
        frmQualitySpin->setMaximum(21);
        frmQualitySpin->setValue(10);
        frmQualitySpin->setMinimumSize(QSize(120, 0));

        ffrow2L->addWidget(frmQualitySpin);


        ffLayout->addWidget(ffrow2);

        ffrow3 = new QFrame(ffContent);
        ffrow3->setObjectName("ffrow3");
        ffrow3L = new QHBoxLayout(ffrow3);
        ffrow3L->setSpacing(20);
        ffrow3L->setObjectName("ffrow3L");
        ffrow3L->setContentsMargins(24, 20, 24, 20);
        fficon3 = new QLabel(ffrow3);
        fficon3->setObjectName("fficon3");

        ffrow3L->addWidget(fficon3);

        fftext3 = new QVBoxLayout();
        fftext3->setSpacing(3);
        fftext3->setObjectName("fftext3");
        fft3 = new QLabel(ffrow3);
        fft3->setObjectName("fft3");

        fftext3->addWidget(fft3);

        ffd3 = new QLabel(ffrow3);
        ffd3->setObjectName("ffd3");

        fftext3->addWidget(ffd3);


        ffrow3L->addLayout(fftext3);

        targetFpsSpin = new QSpinBox(ffrow3);
        targetFpsSpin->setObjectName("targetFpsSpin");
        targetFpsSpin->setMinimum(0);
        targetFpsSpin->setMaximum(9999);
        targetFpsSpin->setValue(240);
        targetFpsSpin->setMinimumSize(QSize(120, 0));

        ffrow3L->addWidget(targetFpsSpin);


        ffLayout->addWidget(ffrow3);

        ffSp2 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        ffLayout->addItem(ffSp2);

        ffCtaFrame = new QFrame(ffContent);
        ffCtaFrame->setObjectName("ffCtaFrame");
        ffCtaLayout = new QHBoxLayout(ffCtaFrame);
        ffCtaLayout->setSpacing(16);
        ffCtaLayout->setObjectName("ffCtaLayout");
        ffCtaLayout->setContentsMargins(24, 22, 24, 22);
        ffCtaText = new QVBoxLayout();
        ffCtaText->setSpacing(4);
        ffCtaText->setObjectName("ffCtaText");
        ffCtaTitle = new QLabel(ffCtaFrame);
        ffCtaTitle->setObjectName("ffCtaTitle");

        ffCtaText->addWidget(ffCtaTitle);

        ffCtaDesc = new QLabel(ffCtaFrame);
        ffCtaDesc->setObjectName("ffCtaDesc");

        ffCtaText->addWidget(ffCtaDesc);


        ffCtaLayout->addLayout(ffCtaText);

        ffCustomButton = new QPushButton(ffCtaFrame);
        ffCustomButton->setObjectName("ffCustomButton");

        ffCtaLayout->addWidget(ffCustomButton);


        ffLayout->addWidget(ffCtaFrame);

        presetsDivider = new QFrame(ffContent);
        presetsDivider->setObjectName("presetsDivider");
        presetsDivider->setMinimumSize(QSize(0, 1));
        presetsDivider->setMaximumSize(QSize(16777215, 1));

        ffLayout->addWidget(presetsDivider);

        ffSectionPresets = new QLabel(ffContent);
        ffSectionPresets->setObjectName("ffSectionPresets");

        ffLayout->addWidget(ffSectionPresets);

        presetsToggleRow = new QFrame(ffContent);
        presetsToggleRow->setObjectName("presetsToggleRow");
        presetsToggleLayout = new QHBoxLayout(presetsToggleRow);
        presetsToggleLayout->setSpacing(20);
        presetsToggleLayout->setObjectName("presetsToggleLayout");
        presetsToggleLayout->setContentsMargins(24, 20, 24, 20);
        presetsToggleIcon = new QLabel(presetsToggleRow);
        presetsToggleIcon->setObjectName("presetsToggleIcon");

        presetsToggleLayout->addWidget(presetsToggleIcon);

        presetsToggleText = new QVBoxLayout();
        presetsToggleText->setSpacing(3);
        presetsToggleText->setObjectName("presetsToggleText");
        presetsToggleTitle = new QLabel(presetsToggleRow);
        presetsToggleTitle->setObjectName("presetsToggleTitle");

        presetsToggleText->addWidget(presetsToggleTitle);

        presetsToggleDesc = new QLabel(presetsToggleRow);
        presetsToggleDesc->setObjectName("presetsToggleDesc");

        presetsToggleText->addWidget(presetsToggleDesc);


        presetsToggleLayout->addLayout(presetsToggleText);

        presetsToggle = new ToggleSwitch(presetsToggleRow);
        presetsToggle->setObjectName("presetsToggle");

        presetsToggleLayout->addWidget(presetsToggle);


        ffLayout->addWidget(presetsToggleRow);

        presetsContainer = new QWidget(ffContent);
        presetsContainer->setObjectName("presetsContainer");
        presetsContainer->setVisible(false);
        presetsContainerLayout = new QVBoxLayout(presetsContainer);
        presetsContainerLayout->setSpacing(10);
        presetsContainerLayout->setObjectName("presetsContainerLayout");
        presetsContainerLayout->setContentsMargins(0, 0, 0, 0);
        presetCardPerf = new QFrame(presetsContainer);
        presetCardPerf->setObjectName("presetCardPerf");
        presetCardPerfLayout = new QHBoxLayout(presetCardPerf);
        presetCardPerfLayout->setSpacing(16);
        presetCardPerfLayout->setObjectName("presetCardPerfLayout");
        presetCardPerfLayout->setContentsMargins(22, 18, 22, 18);
        presetPerfIcon = new QLabel(presetCardPerf);
        presetPerfIcon->setObjectName("presetPerfIcon");

        presetCardPerfLayout->addWidget(presetPerfIcon);

        presetPerfText = new QVBoxLayout();
        presetPerfText->setSpacing(4);
        presetPerfText->setObjectName("presetPerfText");
        presetPerfTitle = new QLabel(presetCardPerf);
        presetPerfTitle->setObjectName("presetPerfTitle");

        presetPerfText->addWidget(presetPerfTitle);

        presetPerfDesc = new QLabel(presetCardPerf);
        presetPerfDesc->setObjectName("presetPerfDesc");

        presetPerfText->addWidget(presetPerfDesc);


        presetCardPerfLayout->addLayout(presetPerfText);

        presetPerfDetails = new QPushButton(presetCardPerf);
        presetPerfDetails->setObjectName("presetPerfDetails");

        presetCardPerfLayout->addWidget(presetPerfDetails);

        presetPerfApply = new QPushButton(presetCardPerf);
        presetPerfApply->setObjectName("presetPerfApply");

        presetCardPerfLayout->addWidget(presetPerfApply);


        presetsContainerLayout->addWidget(presetCardPerf);

        presetCardBal = new QFrame(presetsContainer);
        presetCardBal->setObjectName("presetCardBal");
        presetCardBalLayout = new QHBoxLayout(presetCardBal);
        presetCardBalLayout->setSpacing(16);
        presetCardBalLayout->setObjectName("presetCardBalLayout");
        presetCardBalLayout->setContentsMargins(22, 18, 22, 18);
        presetBalIcon = new QLabel(presetCardBal);
        presetBalIcon->setObjectName("presetBalIcon");

        presetCardBalLayout->addWidget(presetBalIcon);

        presetBalText = new QVBoxLayout();
        presetBalText->setSpacing(4);
        presetBalText->setObjectName("presetBalText");
        presetBalTitle = new QLabel(presetCardBal);
        presetBalTitle->setObjectName("presetBalTitle");

        presetBalText->addWidget(presetBalTitle);

        presetBalDesc = new QLabel(presetCardBal);
        presetBalDesc->setObjectName("presetBalDesc");

        presetBalText->addWidget(presetBalDesc);


        presetCardBalLayout->addLayout(presetBalText);

        presetBalDetails = new QPushButton(presetCardBal);
        presetBalDetails->setObjectName("presetBalDetails");

        presetCardBalLayout->addWidget(presetBalDetails);

        presetBalApply = new QPushButton(presetCardBal);
        presetBalApply->setObjectName("presetBalApply");

        presetCardBalLayout->addWidget(presetBalApply);


        presetsContainerLayout->addWidget(presetCardBal);

        presetCardQual = new QFrame(presetsContainer);
        presetCardQual->setObjectName("presetCardQual");
        presetCardQualLayout = new QHBoxLayout(presetCardQual);
        presetCardQualLayout->setSpacing(16);
        presetCardQualLayout->setObjectName("presetCardQualLayout");
        presetCardQualLayout->setContentsMargins(22, 18, 22, 18);
        presetQualIcon = new QLabel(presetCardQual);
        presetQualIcon->setObjectName("presetQualIcon");

        presetCardQualLayout->addWidget(presetQualIcon);

        presetQualText = new QVBoxLayout();
        presetQualText->setSpacing(4);
        presetQualText->setObjectName("presetQualText");
        presetQualTitle = new QLabel(presetCardQual);
        presetQualTitle->setObjectName("presetQualTitle");

        presetQualText->addWidget(presetQualTitle);

        presetQualDesc = new QLabel(presetCardQual);
        presetQualDesc->setObjectName("presetQualDesc");

        presetQualText->addWidget(presetQualDesc);


        presetCardQualLayout->addLayout(presetQualText);

        presetQualDetails = new QPushButton(presetCardQual);
        presetQualDetails->setObjectName("presetQualDetails");

        presetCardQualLayout->addWidget(presetQualDetails);

        presetQualApply = new QPushButton(presetCardQual);
        presetQualApply->setObjectName("presetQualApply");

        presetCardQualLayout->addWidget(presetQualApply);


        presetsContainerLayout->addWidget(presetCardQual);


        ffLayout->addWidget(presetsContainer);

        ffSp3 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        ffLayout->addItem(ffSp3);

        ffScroll->setWidget(ffContent);

        ffOuter->addWidget(ffScroll);

        pagesStack->addWidget(pageFastFlags);
        pageSettings = new QWidget();
        pageSettings->setObjectName("pageSettings");
        setOuter = new QVBoxLayout(pageSettings);
        setOuter->setSpacing(0);
        setOuter->setObjectName("setOuter");
        setOuter->setContentsMargins(0, 0, 0, 0);
        setScroll = new QScrollArea(pageSettings);
        setScroll->setObjectName("setScroll");
        setScroll->setWidgetResizable(true);
        setScroll->setFrameShape(QFrame::NoFrame);
        setContent = new QWidget();
        setContent->setObjectName("setContent");
        setLayout = new QVBoxLayout(setContent);
        setLayout->setSpacing(10);
        setLayout->setObjectName("setLayout");
        setLayout->setContentsMargins(40, 36, 40, 36);
        setEyebrow = new QLabel(setContent);
        setEyebrow->setObjectName("setEyebrow");

        setLayout->addWidget(setEyebrow);

        setTitle = new QLabel(setContent);
        setTitle->setObjectName("setTitle");

        setLayout->addWidget(setTitle);

        setSubtitle = new QLabel(setContent);
        setSubtitle->setObjectName("setSubtitle");

        setLayout->addWidget(setSubtitle);

        setSp1 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        setLayout->addItem(setSp1);

        setSectionGeneral = new QLabel(setContent);
        setSectionGeneral->setObjectName("setSectionGeneral");

        setLayout->addWidget(setSectionGeneral);

        setRowUpdate = new QFrame(setContent);
        setRowUpdate->setObjectName("setRowUpdate");
        setRowUpdateLayout = new QHBoxLayout(setRowUpdate);
        setRowUpdateLayout->setSpacing(20);
        setRowUpdateLayout->setObjectName("setRowUpdateLayout");
        setRowUpdateLayout->setContentsMargins(24, 20, 24, 20);
        setIconUpdate = new QLabel(setRowUpdate);
        setIconUpdate->setObjectName("setIconUpdate");

        setRowUpdateLayout->addWidget(setIconUpdate);

        setTextUpdate = new QVBoxLayout();
        setTextUpdate->setSpacing(3);
        setTextUpdate->setObjectName("setTextUpdate");
        setTitleUpdate = new QLabel(setRowUpdate);
        setTitleUpdate->setObjectName("setTitleUpdate");

        setTextUpdate->addWidget(setTitleUpdate);

        setDescUpdate = new QLabel(setRowUpdate);
        setDescUpdate->setObjectName("setDescUpdate");

        setTextUpdate->addWidget(setDescUpdate);


        setRowUpdateLayout->addLayout(setTextUpdate);

        setToggleUpdate = new ToggleSwitch(setRowUpdate);
        setToggleUpdate->setObjectName("setToggleUpdate");

        setRowUpdateLayout->addWidget(setToggleUpdate);


        setLayout->addWidget(setRowUpdate);

        setRowStartup = new QFrame(setContent);
        setRowStartup->setObjectName("setRowStartup");
        setRowStartupLayout = new QHBoxLayout(setRowStartup);
        setRowStartupLayout->setSpacing(20);
        setRowStartupLayout->setObjectName("setRowStartupLayout");
        setRowStartupLayout->setContentsMargins(24, 20, 24, 20);
        setIconStartup = new QLabel(setRowStartup);
        setIconStartup->setObjectName("setIconStartup");

        setRowStartupLayout->addWidget(setIconStartup);

        setTextStartup = new QVBoxLayout();
        setTextStartup->setSpacing(3);
        setTextStartup->setObjectName("setTextStartup");
        setTitleStartup = new QLabel(setRowStartup);
        setTitleStartup->setObjectName("setTitleStartup");

        setTextStartup->addWidget(setTitleStartup);

        setDescStartup = new QLabel(setRowStartup);
        setDescStartup->setObjectName("setDescStartup");

        setTextStartup->addWidget(setDescStartup);


        setRowStartupLayout->addLayout(setTextStartup);

        setToggleStartup = new ToggleSwitch(setRowStartup);
        setToggleStartup->setObjectName("setToggleStartup");

        setRowStartupLayout->addWidget(setToggleStartup);


        setLayout->addWidget(setRowStartup);

        setSectionLang = new QLabel(setContent);
        setSectionLang->setObjectName("setSectionLang");

        setLayout->addWidget(setSectionLang);

        setRowLang = new QFrame(setContent);
        setRowLang->setObjectName("setRowLang");
        setRowLangLayout = new QHBoxLayout(setRowLang);
        setRowLangLayout->setSpacing(20);
        setRowLangLayout->setObjectName("setRowLangLayout");
        setRowLangLayout->setContentsMargins(24, 20, 24, 20);
        setIconLang = new QLabel(setRowLang);
        setIconLang->setObjectName("setIconLang");

        setRowLangLayout->addWidget(setIconLang);

        setTextLang = new QVBoxLayout();
        setTextLang->setSpacing(3);
        setTextLang->setObjectName("setTextLang");
        setTitleLang = new QLabel(setRowLang);
        setTitleLang->setObjectName("setTitleLang");

        setTextLang->addWidget(setTitleLang);

        setDescLang = new QLabel(setRowLang);
        setDescLang->setObjectName("setDescLang");

        setTextLang->addWidget(setDescLang);


        setRowLangLayout->addLayout(setTextLang);

        setLangCombo = new QComboBox(setRowLang);
        setLangCombo->addItem(QString());
        setLangCombo->addItem(QString());
        setLangCombo->setObjectName("setLangCombo");
        setLangCombo->setMinimumSize(QSize(160, 0));

        setRowLangLayout->addWidget(setLangCombo);


        setLayout->addWidget(setRowLang);

        setSp2 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        setLayout->addItem(setSp2);

        setScroll->setWidget(setContent);

        setOuter->addWidget(setScroll);

        pagesStack->addWidget(pageSettings);
        pageAbout = new QWidget();
        pageAbout->setObjectName("pageAbout");
        abtOuter = new QVBoxLayout(pageAbout);
        abtOuter->setSpacing(0);
        abtOuter->setObjectName("abtOuter");
        abtOuter->setContentsMargins(0, 0, 0, 0);
        abtScroll = new QScrollArea(pageAbout);
        abtScroll->setObjectName("abtScroll");
        abtScroll->setWidgetResizable(true);
        abtScroll->setFrameShape(QFrame::NoFrame);
        abtContent = new QWidget();
        abtContent->setObjectName("abtContent");
        abtLayout = new QVBoxLayout(abtContent);
        abtLayout->setSpacing(12);
        abtLayout->setObjectName("abtLayout");
        abtLayout->setContentsMargins(40, 36, 40, 36);
        abtEyebrow = new QLabel(abtContent);
        abtEyebrow->setObjectName("abtEyebrow");

        abtLayout->addWidget(abtEyebrow);

        abtTitle = new QLabel(abtContent);
        abtTitle->setObjectName("abtTitle");

        abtLayout->addWidget(abtTitle);

        abtSubtitle = new QLabel(abtContent);
        abtSubtitle->setObjectName("abtSubtitle");

        abtLayout->addWidget(abtSubtitle);

        abtSp1 = new QSpacerItem(20, 16, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        abtLayout->addItem(abtSp1);

        abtHero = new QFrame(abtContent);
        abtHero->setObjectName("abtHero");
        abtHeroLayout = new QHBoxLayout(abtHero);
        abtHeroLayout->setSpacing(24);
        abtHeroLayout->setObjectName("abtHeroLayout");
        abtHeroLayout->setContentsMargins(28, 28, 28, 28);
        abtLogo = new QLabel(abtHero);
        abtLogo->setObjectName("abtLogo");

        abtHeroLayout->addWidget(abtLogo);

        abtHeroText = new QVBoxLayout();
        abtHeroText->setSpacing(6);
        abtHeroText->setObjectName("abtHeroText");
        abtHeroTitle = new QLabel(abtHero);
        abtHeroTitle->setObjectName("abtHeroTitle");

        abtHeroText->addWidget(abtHeroTitle);

        abtHeroVersion = new QLabel(abtHero);
        abtHeroVersion->setObjectName("abtHeroVersion");

        abtHeroText->addWidget(abtHeroVersion);

        abtHeroDesc = new QLabel(abtHero);
        abtHeroDesc->setObjectName("abtHeroDesc");

        abtHeroText->addWidget(abtHeroDesc);


        abtHeroLayout->addLayout(abtHeroText);


        abtLayout->addWidget(abtHero);

        abtLinks = new QFrame(abtContent);
        abtLinks->setObjectName("abtLinks");
        abtLinksLayout = new QVBoxLayout(abtLinks);
        abtLinksLayout->setSpacing(12);
        abtLinksLayout->setObjectName("abtLinksLayout");
        abtLinksLayout->setContentsMargins(28, 24, 28, 24);
        abtLinksTitle = new QLabel(abtLinks);
        abtLinksTitle->setObjectName("abtLinksTitle");

        abtLinksLayout->addWidget(abtLinksTitle);

        abtLinksRow = new QHBoxLayout();
        abtLinksRow->setSpacing(10);
        abtLinksRow->setObjectName("abtLinksRow");
        btnGithub = new QPushButton(abtLinks);
        btnGithub->setObjectName("btnGithub");

        abtLinksRow->addWidget(btnGithub);

        btnDocs = new QPushButton(abtLinks);
        btnDocs->setObjectName("btnDocs");

        abtLinksRow->addWidget(btnDocs);

        btnIssue = new QPushButton(abtLinks);
        btnIssue->setObjectName("btnIssue");

        abtLinksRow->addWidget(btnIssue);


        abtLinksLayout->addLayout(abtLinksRow);


        abtLayout->addWidget(abtLinks);

        abtCredits = new QFrame(abtContent);
        abtCredits->setObjectName("abtCredits");
        abtCreditsLayout = new QVBoxLayout(abtCredits);
        abtCreditsLayout->setSpacing(8);
        abtCreditsLayout->setObjectName("abtCreditsLayout");
        abtCreditsLayout->setContentsMargins(28, 24, 28, 24);
        abtCreditsTitle = new QLabel(abtCredits);
        abtCreditsTitle->setObjectName("abtCreditsTitle");

        abtCreditsLayout->addWidget(abtCreditsTitle);

        abtCreditsText = new QLabel(abtCredits);
        abtCreditsText->setObjectName("abtCreditsText");
        abtCreditsText->setWordWrap(true);

        abtCreditsLayout->addWidget(abtCreditsText);


        abtLayout->addWidget(abtCredits);

        abtSp2 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        abtLayout->addItem(abtSp2);

        abtScroll->setWidget(abtContent);

        abtOuter->addWidget(abtScroll);

        pagesStack->addWidget(pageAbout);

        mainLayout->addWidget(pagesStack);


        rootLayout->addLayout(mainLayout);

        footer = new QFrame(centralWidget);
        footer->setObjectName("footer");
        footer->setMinimumSize(QSize(0, 46));
        footer->setMaximumSize(QSize(16777215, 46));
        footerLayout = new QHBoxLayout(footer);
        footerLayout->setSpacing(10);
        footerLayout->setObjectName("footerLayout");
        footerLayout->setContentsMargins(20, 0, 20, 0);
        versionLabel = new QLabel(footer);
        versionLabel->setObjectName("versionLabel");

        footerLayout->addWidget(versionLabel);

        updateLabel = new QLabel(footer);
        updateLabel->setObjectName("updateLabel");
        updateLabel->setVisible(false);

        footerLayout->addWidget(updateLabel);

        updateButton = new QPushButton(footer);
        updateButton->setObjectName("updateButton");
        updateButton->setVisible(false);

        footerLayout->addWidget(updateButton);

        progressBar = new QProgressBar(footer);
        progressBar->setObjectName("progressBar");
        progressBar->setMinimumSize(QSize(220, 6));
        progressBar->setMaximumSize(QSize(220, 6));
        progressBar->setValue(0);
        progressBar->setTextVisible(false);
        progressBar->setVisible(false);

        footerLayout->addWidget(progressBar);

        footerSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        footerLayout->addItem(footerSpacer);

        resetButton = new QPushButton(footer);
        resetButton->setObjectName("resetButton");

        footerLayout->addWidget(resetButton);

        saveButton = new QPushButton(footer);
        saveButton->setObjectName("saveButton");

        footerLayout->addWidget(saveButton);

        closeButton = new QPushButton(footer);
        closeButton->setObjectName("closeButton");

        footerLayout->addWidget(closeButton);


        rootLayout->addWidget(footer);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        pagesStack->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "SudoStrap", nullptr));
        appTitle->setText(QCoreApplication::translate("MainWindow", "\342\232\241  SudoStrap", nullptr));
        navSectionLabel->setText(QCoreApplication::translate("MainWindow", "WORKSPACE", nullptr));
        btnPerformance->setText(QCoreApplication::translate("MainWindow", "\342\232\241   Performance", nullptr));
        btnGraphics->setText(QCoreApplication::translate("MainWindow", "\360\237\216\250   Graphics", nullptr));
        btnFastFlags->setText(QCoreApplication::translate("MainWindow", "\360\237\224\247   FastFlags", nullptr));
        btnSettings->setText(QCoreApplication::translate("MainWindow", "\342\232\231\357\270\217   Settings", nullptr));
        btnAbout->setText(QCoreApplication::translate("MainWindow", "\342\204\271\357\270\217   About", nullptr));
        statusChip->setText(QCoreApplication::translate("MainWindow", "\342\227\217  Sober Ready", nullptr));
        launchButton->setText(QCoreApplication::translate("MainWindow", "\342\226\266   Launch Sober", nullptr));
        perfEyebrow->setText(QCoreApplication::translate("MainWindow", "PERFORMANCE", nullptr));
        perfTitle->setText(QCoreApplication::translate("MainWindow", "Tune Roblox Performance", nullptr));
        perfSubtitle->setText(QCoreApplication::translate("MainWindow", "Get more FPS without sacrificing stability", nullptr));
        icon1->setText(QCoreApplication::translate("MainWindow", "\342\232\241", nullptr));
        t1->setText(QCoreApplication::translate("MainWindow", "Unlock FPS", nullptr));
        d1->setText(QCoreApplication::translate("MainWindow", "Bypass Roblox's default 60 FPS cap", nullptr));
        icon2->setText(QCoreApplication::translate("MainWindow", "\360\237\216\257", nullptr));
        t2->setText(QCoreApplication::translate("MainWindow", "Render Distance", nullptr));
        d2->setText(QCoreApplication::translate("MainWindow", "Lower far-object detail for more FPS", nullptr));
        renderDistCombo->setItemText(0, QCoreApplication::translate("MainWindow", "Low", nullptr));
        renderDistCombo->setItemText(1, QCoreApplication::translate("MainWindow", "Medium", nullptr));
        renderDistCombo->setItemText(2, QCoreApplication::translate("MainWindow", "High", nullptr));

        icon3->setText(QCoreApplication::translate("MainWindow", "\360\237\214\221", nullptr));
        t3->setText(QCoreApplication::translate("MainWindow", "Disable Shadows", nullptr));
        d3->setText(QCoreApplication::translate("MainWindow", "Removes dynamic shadows for a large FPS boost", nullptr));
        icon4->setText(QCoreApplication::translate("MainWindow", "\342\234\250", nullptr));
        t4->setText(QCoreApplication::translate("MainWindow", "Disable Post-Processing", nullptr));
        d4->setText(QCoreApplication::translate("MainWindow", "Removes bloom, depth of field, and sun rays", nullptr));
        icon5->setText(QCoreApplication::translate("MainWindow", "\360\237\216\232\357\270\217", nullptr));
        t5->setText(QCoreApplication::translate("MainWindow", "FPS Limit", nullptr));
        d5->setText(QCoreApplication::translate("MainWindow", "Set maximum framerate (0 = unlimited)", nullptr));
        icon6->setText(QCoreApplication::translate("MainWindow", "\360\237\214\220", nullptr));
        t6->setText(QCoreApplication::translate("MainWindow", "Network & Ping Boost", nullptr));
        d6->setText(QCoreApplication::translate("MainWindow", "Increase network tick rate and reduce latency", nullptr));
        gfxEyebrow->setText(QCoreApplication::translate("MainWindow", "GRAPHICS", nullptr));
        gfxTitle->setText(QCoreApplication::translate("MainWindow", "Visual Quality", nullptr));
        gfxSubtitle->setText(QCoreApplication::translate("MainWindow", "Trade beauty for performance", nullptr));
        gicon1->setText(QCoreApplication::translate("MainWindow", "\360\237\214\277", nullptr));
        gt1->setText(QCoreApplication::translate("MainWindow", "Disable Grass Textures", nullptr));
        gd1->setText(QCoreApplication::translate("MainWindow", "Removes grass from terrain", nullptr));
        gicon2->setText(QCoreApplication::translate("MainWindow", "\360\237\226\274\357\270\217", nullptr));
        gt2->setText(QCoreApplication::translate("MainWindow", "Texture Quality", nullptr));
        gd2->setText(QCoreApplication::translate("MainWindow", "Lower quality reduces VRAM usage", nullptr));
        texQualityCombo->setItemText(0, QCoreApplication::translate("MainWindow", "Lowest", nullptr));
        texQualityCombo->setItemText(1, QCoreApplication::translate("MainWindow", "Low", nullptr));
        texQualityCombo->setItemText(2, QCoreApplication::translate("MainWindow", "Medium", nullptr));
        texQualityCombo->setItemText(3, QCoreApplication::translate("MainWindow", "High", nullptr));

        gicon3->setText(QCoreApplication::translate("MainWindow", "\360\237\222\241", nullptr));
        gt3->setText(QCoreApplication::translate("MainWindow", "Lighting Mode", nullptr));
        gd3->setText(QCoreApplication::translate("MainWindow", "Voxel is fastest", nullptr));
        lightingCombo->setItemText(0, QCoreApplication::translate("MainWindow", "Voxel (fastest)", nullptr));
        lightingCombo->setItemText(1, QCoreApplication::translate("MainWindow", "ShadowMap", nullptr));
        lightingCombo->setItemText(2, QCoreApplication::translate("MainWindow", "Future (best)", nullptr));

        gicon4->setText(QCoreApplication::translate("MainWindow", "\360\237\224\267", nullptr));
        gt4->setText(QCoreApplication::translate("MainWindow", "Disable Anti-Aliasing", nullptr));
        gd4->setText(QCoreApplication::translate("MainWindow", "Smooths edges", nullptr));
        gicon5->setText(QCoreApplication::translate("MainWindow", "\360\237\214\253\357\270\217", nullptr));
        gt5->setText(QCoreApplication::translate("MainWindow", "Disable Bloom", nullptr));
        gd5->setText(QCoreApplication::translate("MainWindow", "Removes glow around lights", nullptr));
        gicon6->setText(QCoreApplication::translate("MainWindow", "\342\230\201\357\270\217", nullptr));
        gt6->setText(QCoreApplication::translate("MainWindow", "Gray Sky", nullptr));
        gd6->setText(QCoreApplication::translate("MainWindow", "Replaces sky with gray", nullptr));
        ffEyebrow->setText(QCoreApplication::translate("MainWindow", "ADVANCED", nullptr));
        ffTitle->setText(QCoreApplication::translate("MainWindow", "FastFlags Editor", nullptr));
        ffSubtitle->setText(QCoreApplication::translate("MainWindow", "Fine-tune rendering flags", nullptr));
        fficon1->setText(QCoreApplication::translate("MainWindow", "\360\237\223\220", nullptr));
        fft1->setText(QCoreApplication::translate("MainWindow", "CSG Level of Detail", nullptr));
        ffd1->setText(QCoreApplication::translate("MainWindow", "DFIntCSGLevelOfDetailSwitchingDistance", nullptr));
        fficon2->setText(QCoreApplication::translate("MainWindow", "\360\237\216\232\357\270\217", nullptr));
        fft2->setText(QCoreApplication::translate("MainWindow", "FRM Quality Override", nullptr));
        ffd2->setText(QCoreApplication::translate("MainWindow", "DFIntDebugFRMQualityLevelOverride (1-21)", nullptr));
        fficon3->setText(QCoreApplication::translate("MainWindow", "\342\232\241", nullptr));
        fft3->setText(QCoreApplication::translate("MainWindow", "Target FPS", nullptr));
        ffd3->setText(QCoreApplication::translate("MainWindow", "DFIntTaskSchedulerTargetFps", nullptr));
        ffCtaTitle->setText(QCoreApplication::translate("MainWindow", "Need more control?", nullptr));
        ffCtaDesc->setText(QCoreApplication::translate("MainWindow", "Add custom flags, import from file, or paste JSON", nullptr));
        ffCustomButton->setText(QCoreApplication::translate("MainWindow", "\342\232\231\357\270\217  Custom FastFlags", nullptr));
        ffSectionPresets->setText(QCoreApplication::translate("MainWindow", "QUICK PRESETS", nullptr));
        presetsToggleIcon->setText(QCoreApplication::translate("MainWindow", "\342\232\241", nullptr));
        presetsToggleTitle->setText(QCoreApplication::translate("MainWindow", "Enable Preset Mode", nullptr));
        presetsToggleDesc->setText(QCoreApplication::translate("MainWindow", "Apply pre-made flag combinations with one click", nullptr));
        presetPerfIcon->setText(QCoreApplication::translate("MainWindow", "\360\237\232\200", nullptr));
        presetPerfTitle->setText(QCoreApplication::translate("MainWindow", "Performance", nullptr));
        presetPerfDesc->setText(QCoreApplication::translate("MainWindow", "Maximum FPS, minimum quality", nullptr));
        presetPerfDetails->setText(QCoreApplication::translate("MainWindow", "Details", nullptr));
        presetPerfApply->setText(QCoreApplication::translate("MainWindow", "Apply", nullptr));
        presetBalIcon->setText(QCoreApplication::translate("MainWindow", "\342\232\226\357\270\217", nullptr));
        presetBalTitle->setText(QCoreApplication::translate("MainWindow", "Balanced", nullptr));
        presetBalDesc->setText(QCoreApplication::translate("MainWindow", "Good FPS with decent visuals", nullptr));
        presetBalDetails->setText(QCoreApplication::translate("MainWindow", "Details", nullptr));
        presetBalApply->setText(QCoreApplication::translate("MainWindow", "Apply", nullptr));
        presetQualIcon->setText(QCoreApplication::translate("MainWindow", "\360\237\216\250", nullptr));
        presetQualTitle->setText(QCoreApplication::translate("MainWindow", "Quality", nullptr));
        presetQualDesc->setText(QCoreApplication::translate("MainWindow", "Best visuals, higher system load", nullptr));
        presetQualDetails->setText(QCoreApplication::translate("MainWindow", "Details", nullptr));
        presetQualApply->setText(QCoreApplication::translate("MainWindow", "Apply", nullptr));
        setEyebrow->setText(QCoreApplication::translate("MainWindow", "SETTINGS", nullptr));
        setTitle->setText(QCoreApplication::translate("MainWindow", "Configuration", nullptr));
        setSubtitle->setText(QCoreApplication::translate("MainWindow", "Configure SudoStrap to your preferences", nullptr));
        setSectionGeneral->setText(QCoreApplication::translate("MainWindow", "GENERAL", nullptr));
        setIconUpdate->setText(QCoreApplication::translate("MainWindow", "\342\232\231\357\270\217", nullptr));
        setTitleUpdate->setText(QCoreApplication::translate("MainWindow", "Auto-Update", nullptr));
        setDescUpdate->setText(QCoreApplication::translate("MainWindow", "Automatically check and install updates on startup", nullptr));
        setIconStartup->setText(QCoreApplication::translate("MainWindow", "\360\237\232\200", nullptr));
        setTitleStartup->setText(QCoreApplication::translate("MainWindow", "Launch on Startup", nullptr));
        setDescStartup->setText(QCoreApplication::translate("MainWindow", "Start SudoStrap automatically with your system", nullptr));
        setSectionLang->setText(QCoreApplication::translate("MainWindow", "LANGUAGE", nullptr));
        setIconLang->setText(QCoreApplication::translate("MainWindow", "\360\237\214\215", nullptr));
        setTitleLang->setText(QCoreApplication::translate("MainWindow", "Interface Language", nullptr));
        setDescLang->setText(QCoreApplication::translate("MainWindow", "Choose the language for SudoStrap interface", nullptr));
        setLangCombo->setItemText(0, QCoreApplication::translate("MainWindow", "English", nullptr));
        setLangCombo->setItemText(1, QCoreApplication::translate("MainWindow", "\330\247\331\204\330\271\330\261\330\250\331\212\330\251", nullptr));

        abtEyebrow->setText(QCoreApplication::translate("MainWindow", "ABOUT", nullptr));
        abtTitle->setText(QCoreApplication::translate("MainWindow", "SudoStrap", nullptr));
        abtSubtitle->setText(QCoreApplication::translate("MainWindow", "FastFlags Manager for Linux", nullptr));
        abtLogo->setText(QCoreApplication::translate("MainWindow", "\342\232\241", nullptr));
        abtHeroTitle->setText(QCoreApplication::translate("MainWindow", "SudoStrap", nullptr));
        abtHeroVersion->setText(QCoreApplication::translate("MainWindow", "Version 0.1.0", nullptr));
        abtHeroDesc->setText(QCoreApplication::translate("MainWindow", "A modern FastFlags manager for Roblox on Linux \342\200\224 built with Qt6 and C++.", nullptr));
        abtLinksTitle->setText(QCoreApplication::translate("MainWindow", "LINKS", nullptr));
        btnGithub->setText(QCoreApplication::translate("MainWindow", "\360\237\223\226  GitHub", nullptr));
        btnDocs->setText(QCoreApplication::translate("MainWindow", "\360\237\223\232  Documentation", nullptr));
        btnIssue->setText(QCoreApplication::translate("MainWindow", "\360\237\220\233  Report Issue", nullptr));
        abtCreditsTitle->setText(QCoreApplication::translate("MainWindow", "CREDITS", nullptr));
        abtCreditsText->setText(QCoreApplication::translate("MainWindow", "Built with love for the Linux gaming community. Special thanks to the Sober team and the Qt Project.", nullptr));
        versionLabel->setText(QCoreApplication::translate("MainWindow", "v0.1.0  \302\267  Ready", nullptr));
        updateLabel->setText(QCoreApplication::translate("MainWindow", "\302\267 Update available", nullptr));
        updateButton->setText(QCoreApplication::translate("MainWindow", "\342\254\207  Update", nullptr));
        resetButton->setText(QCoreApplication::translate("MainWindow", "\342\206\272  Reset", nullptr));
        saveButton->setText(QCoreApplication::translate("MainWindow", "\360\237\222\276  Save", nullptr));
        closeButton->setText(QCoreApplication::translate("MainWindow", "\342\234\225  Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
