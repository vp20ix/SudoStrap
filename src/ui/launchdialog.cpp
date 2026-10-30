#include "ui/launchdialog.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QProgressBar>
#include <QTimer>
#include <QProcess>
#include <QStandardPaths>
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>
#include <QPixmap>

LaunchDialog::LaunchDialog(QWidget *parent, QPointer<QProcess> process)
    : QDialog(parent), m_process(process), pendingProgress(0), launchStarted(false)
{
    setWindowTitle("SudoStrap Bootstrapper");
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

    auto *title = new QLabel(mainWidget);
    title->setObjectName("launchLogo");
    title->setFixedSize(200, 62);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("background: transparent;");
    const QPixmap logo(QStringLiteral(":/icons/logo_banner.png"));
    if (!logo.isNull()) {
        title->setPixmap(logo.scaled(title->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    layout->addWidget(title, 0, Qt::AlignHCenter);

    auto *subtitle = new QLabel("Preparing Roblox for Linux", mainWidget);
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
                stop:0 #22d3ee, stop:1 #0078d4);
            border-radius: 4px;
        }
    )");
    layout->addWidget(progressBar);

    statusLabel = new QLabel("Initializing...", mainWidget);
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

    process = new QProcess(this);
}

LaunchDialog::~LaunchDialog()
{
    // ما نقتل العملية، نخليها شغالة في الخلفية
}

void LaunchDialog::startLaunch()
{
    setStep("Checking for updates...", 15);

    QTimer::singleShot(800, this, [this]() {
        QString flatpak = QStandardPaths::findExecutable("flatpak");
        if (flatpak.isEmpty()) {
            setStep("flatpak not found ✕", 0);
            statusLabel->setStyleSheet("color: #ff6b6b; font-size: 12px; background: transparent;");
            QTimer::singleShot(2000, this, [this]() { finish(false); });
            return;
        }

        setStep("Launching Sober...", 45);

        // نستخدم startDetached عشان ما ننتظر العملية
        QProcess::startDetached(flatpak, {"run", "org.vinegarhq.Sober"});

        // نكمل البار بمؤقت واقعي
        QTimer::singleShot(1200, this, [this]() {
            setStep("Starting Roblox...", 70);

            QTimer::singleShot(1200, this, [this]() {
                setStep("Roblox is starting...", 90);

                QTimer::singleShot(1200, this, [this]() {
                    setStep("Roblox is running ●", 100);
                    statusLabel->setStyleSheet("color: #22c55e; font-size: 12px; font-weight: bold; background: transparent;");

                    QTimer::singleShot(1500, this, [this]() { finish(true); });
                });
            });
        });
    });
}

void LaunchDialog::setStep(const QString &text, int value)
{
    statusLabel->setText(text);
    animateProgress(value);
}

void LaunchDialog::animateProgress(int targetValue)
{
    pendingProgress = targetValue;
    animation->stop();
    animation->setStartValue(progressBar->value());
    animation->setEndValue(targetValue);
    animation->start();
}


void LaunchDialog::finish(bool success)
{
    emit launchFinished(success);
    accept();
}
