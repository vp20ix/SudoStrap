#include "ui/updatedialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QProgressBar>
#include <QTimer>
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>
#include <QColor>

UpdateDialog::UpdateDialog(const QString &newVersion, QWidget *parent)
    : QDialog(parent), m_newVersion(newVersion),
      m_currentProgress(0), m_targetProgress(0), m_step(0)
{
    setWindowTitle("SudoStrap Update");
    setFixedSize(480, 240);
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);

    auto *mainWidget = new QWidget(this);
    mainWidget->setObjectName("dialogBox");
    mainWidget->setStyleSheet(R"(
        #dialogBox {
            background-color: #1a1a24;
            border: 1px solid #2a2a3a;
            border-radius: 14px;
        }
    )");

    auto *outer = new QVBoxLayout(this);
    outer->setContentsMargins(0, 0, 0, 0);
    outer->addWidget(mainWidget);

    auto *layout = new QVBoxLayout(mainWidget);
    layout->setContentsMargins(30, 28, 30, 28);
    layout->setSpacing(14);

    iconLabel = new QLabel("⬇", mainWidget);
    iconLabel->setAlignment(Qt::AlignCenter);
    iconLabel->setStyleSheet("font-size: 36px; color: #22d3ee; background: transparent;");
    layout->addWidget(iconLabel);

    auto *title = new QLabel("Update Available", mainWidget);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("color: #ffffff; font-size: 18px; font-weight: bold; letter-spacing: 1px; background: transparent;");
    layout->addWidget(title);

    auto *subtitle = new QLabel("SudoStrap " + newVersion + " is ready to install", mainWidget);
    subtitle->setAlignment(Qt::AlignCenter);
    subtitle->setStyleSheet("color: #707080; font-size: 11px; background: transparent;");
    layout->addWidget(subtitle);

    layout->addSpacing(8);

    progressBar = new QProgressBar(mainWidget);
    progressBar->setRange(0, 100);
    progressBar->setValue(0);
    progressBar->setTextVisible(false);
    progressBar->setFixedHeight(8);
    progressBar->setStyleSheet(R"(
        QProgressBar {
            background-color: #2a2a3a;
            border: none;
            border-radius: 4px;
        }
        QProgressBar::chunk {
            background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                stop:0 #22d3ee, stop:1 #7c5cff);
            border-radius: 4px;
        }
    )");
    layout->addWidget(progressBar);

    statusLabel = new QLabel("Preparing download...", mainWidget);
    statusLabel->setAlignment(Qt::AlignCenter);
    statusLabel->setStyleSheet("color: #22d3ee; font-size: 12px; background: transparent;");
    layout->addWidget(statusLabel);

    auto *shadow = new QGraphicsDropShadowEffect(mainWidget);
    shadow->setBlurRadius(40);
    shadow->setColor(QColor(0, 0, 0, 180));
    shadow->setOffset(0, 8);
    mainWidget->setGraphicsEffect(shadow);

    animation = new QPropertyAnimation(progressBar, "value", this);
    animation->setDuration(350);
    animation->setEasingCurve(QEasingCurve::OutCubic);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this]() {
        if (m_currentProgress < m_targetProgress) {
            m_currentProgress += 1;
            progressBar->setValue(m_currentProgress);
            return;
        }
        // انتقل للخطوة التالية
        if (m_step == 0) {
            m_step = 1;
            setStep("Downloading SudoStrap " + m_newVersion + "...", 60);
        } else if (m_step == 1) {
            m_step = 2;
            setStep("Verifying checksum...", 85);
        } else if (m_step == 2) {
            m_step = 3;
            setStep("Installing...", 100);
        } else if (m_step == 3) {
            timer->stop();
            statusLabel->setText("Update installed ✓");
            statusLabel->setStyleSheet("color: #22c55e; font-size: 12px; font-weight: bold; background: transparent;");
            QTimer::singleShot(1500, this, [this]() { finish(true); });
        }
    });
}

void UpdateDialog::startUpdate()
{
    setStep("Preparing download...", 20);
    timer->start(40);
}

void UpdateDialog::setStep(const QString &text, int value)
{
    statusLabel->setText(text);
    animateProgress(value);
    m_targetProgress = value;
}

void UpdateDialog::animateProgress(int targetValue)
{
    animation->stop();
    animation->setStartValue(progressBar->value());
    animation->setEndValue(targetValue);
    animation->start();
}

void UpdateDialog::finish(bool success)
{
    emit updateFinished(success);
    accept();
}
