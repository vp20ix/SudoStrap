#include "ui/updatechecker.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QProgressBar>
#include <QTextEdit>
#include <QPushButton>
#include <QProcess>
#include <QDir>
#include <QTimer>
#include <QCloseEvent>
#include <QCoreApplication>
#include <QFileInfo>
#include <QPixmap>
#include <QFrame>

UpdateChecker::UpdateChecker(QWidget *parent) : QDialog(parent)
{
    QFileInfo fi(QCoreApplication::applicationFilePath());
    QString real = fi.canonicalFilePath();
    if (real.isEmpty()) real = fi.absoluteFilePath();
    m_workDir = QFileInfo(real).absolutePath() + "/..";
    m_currentVersion = "v" + QCoreApplication::applicationVersion();
    setupUi();
    QTimer::singleShot(300, this, &UpdateChecker::runFetch);
}

void UpdateChecker::setupUi()
{
    setWindowTitle("SudoStrap Updater");
    setModal(true);
    setMinimumSize(560, 420);
    setStyleSheet(R"(
        QDialog { background-color: #1e1e1e; color: #e0e0e0; }
        QLabel { color: #e0e0e0; background: transparent; border: none; }
        QProgressBar {
            background-color: #2d2d30;
            border: 1px solid #3e3e42;
            border-radius: 6px;
            height: 22px;
            text-align: center;
            color: #ffffff;
            font-weight: bold;
        }
        QProgressBar::chunk {
            background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                stop:0 #0078d4, stop:1 #00b8d4);
            border-radius: 5px;
        }
        QTextEdit {
            background-color: #141414;
            border: 1px solid #2a2a2e;
            border-radius: 6px;
            color: #b0b0b0;
            font-family: monospace;
            font-size: 11px;
            padding: 8px;
        }
        QPushButton {
            background-color: #3e3e42;
            color: #e0e0e0;
            border: 1px solid #555;
            padding: 8px 16px;
            border-radius: 6px;
        }
        QPushButton:hover { background-color: #4e4e52; }
        QPushButton[primary="true"] {
            background-color: #0078d4; color: white; border: none; font-weight: bold;
        }
        QPushButton[primary="true"]:hover { background-color: #1084d8; }
    )");

    auto *root = new QVBoxLayout(this);
    root->setContentsMargins(24, 24, 24, 20);
    root->setSpacing(16);

    // ===== Header =====
    auto *header = new QHBoxLayout;
    header->setSpacing(16);

    auto *logo = new QLabel;
    QPixmap pm(":/icons/logo.png");
    if (!pm.isNull()) {
        logo->setPixmap(pm.scaled(48, 48, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        logo->setText("SS");
        logo->setStyleSheet("font-size: 24px; font-weight: bold; color: #0078d4;");
    }
    logo->setFixedSize(48, 48);
    logo->setAlignment(Qt::AlignCenter);
    header->addWidget(logo);

    auto *titleBox = new QVBoxLayout;
    titleBox->setSpacing(2);
    auto *title = new QLabel("Updating SudoStrap");
    title->setStyleSheet("font-size: 18px; font-weight: bold; color: #ffffff;");
    titleBox->addWidget(title);

    auto *verRow = new QHBoxLayout;
    verRow->setSpacing(8);
    m_oldVer = new QLabel(m_currentVersion);
    m_oldVer->setStyleSheet("color: #888; font-size: 13px;");
    auto *arrow = new QLabel("→");
    arrow->setStyleSheet("color: #555; font-size: 13px;");
    m_newVer = new QLabel("checking…");
    m_newVer->setStyleSheet("color: #0078d4; font-size: 13px; font-weight: bold;");
    verRow->addWidget(m_oldVer);
    verRow->addWidget(arrow);
    verRow->addWidget(m_newVer);
    verRow->addStretch();
    titleBox->addLayout(verRow);
    header->addLayout(titleBox, 1);
    root->addLayout(header);

    // ===== Stepper =====
    auto *stepper = new QHBoxLayout;
    stepper->setSpacing(6);
    const char *stepNames[4] = {"Check", "Download", "Build", "Done"};
    for (int i = 0; i < 4; i++) {
        auto *col = new QVBoxLayout;
        col->setSpacing(4);
        m_stepCircle[i] = new QLabel("○");
        m_stepCircle[i]->setAlignment(Qt::AlignCenter);
        m_stepCircle[i]->setStyleSheet("color: #555; font-size: 18px;");
        m_stepLabel[i] = new QLabel(stepNames[i]);
        m_stepLabel[i]->setAlignment(Qt::AlignCenter);
        m_stepLabel[i]->setStyleSheet("color: #888; font-size: 11px;");
        col->addWidget(m_stepCircle[i]);
        col->addWidget(m_stepLabel[i]);
        stepper->addLayout(col, 1);
        if (i < 3) {
            auto *line = new QLabel("───");
            line->setStyleSheet("color: #333; font-size: 14px;");
            stepper->addWidget(line, 0, Qt::AlignTop);
        }
    }
    root->addLayout(stepper);

    // ===== Status + Progress =====
    m_status = new QLabel("Preparing…");
    m_status->setStyleSheet("color: #ccc; font-size: 12px;");
    root->addWidget(m_status);

    m_progress = new QProgressBar;
    m_progress->setRange(0, 100);
    m_progress->setValue(0);
    m_progress->setFormat("%p%");
    root->addWidget(m_progress);

    // ===== Details toggle =====
    m_detailsBtn = new QPushButton("▼  Show details");
    m_detailsBtn->setStyleSheet("text-align: left; padding: 6px 10px;");
    m_detailsBtn->setFlat(true);
    connect(m_detailsBtn, &QPushButton::clicked, this, &UpdateChecker::toggleLog);
    root->addWidget(m_detailsBtn);

    m_logContainer = new QWidget;
    m_logContainer->setVisible(false);
    auto *logLay = new QVBoxLayout(m_logContainer);
    logLay->setContentsMargins(0, 0, 0, 0);
    m_log = new QTextEdit;
    m_log->setReadOnly(true);
    m_log->setMinimumHeight(100);
    m_log->setMaximumHeight(150);
    logLay->addWidget(m_log);
    root->addWidget(m_logContainer);

    root->addStretch();

    // ===== Footer =====
    auto *footer = new QHBoxLayout;
    footer->addStretch();
    m_cancelBtn = new QPushButton("Cancel");
    connect(m_cancelBtn, &QPushButton::clicked, this, [this]() {
        if (m_proc) { m_proc->kill(); m_proc->waitForFinished(500); }
        reject();
    });
    footer->addWidget(m_cancelBtn);
    root->addLayout(footer);

    setStage(Stage::Check);
}

void UpdateChecker::setStage(Stage s)
{
    m_stage = s;
    for (int i = 0; i < 4; i++) {
        QLabel *c = m_stepCircle[i];
        QLabel *l = m_stepLabel[i];
        if (i < static_cast<int>(s)) {
            c->setText("✓");
            c->setStyleSheet("color: #4ade80; font-size: 18px; font-weight: bold;");
            l->setStyleSheet("color: #4ade80; font-size: 11px;");
        } else if (i == static_cast<int>(s)) {
            c->setText("●");
            c->setStyleSheet("color: #0078d4; font-size: 18px; font-weight: bold;");
            l->setStyleSheet("color: #ffffff; font-size: 11px; font-weight: bold;");
        } else {
            c->setText("○");
            c->setStyleSheet("color: #555; font-size: 18px;");
            l->setStyleSheet("color: #888; font-size: 11px;");
        }
    }
}

void UpdateChecker::setStageFailed(Stage s)
{
    QLabel *c = m_stepCircle[static_cast<int>(s)];
    QLabel *l = m_stepLabel[static_cast<int>(s)];
    c->setText("✕");
    c->setStyleSheet("color: #ff5555; font-size: 18px; font-weight: bold;");
    l->setStyleSheet("color: #ff5555; font-size: 11px; font-weight: bold;");
}

void UpdateChecker::setStatus(const QString &msg, int progress)
{
    m_status->setText(msg);
    if (progress >= 0) m_progress->setValue(progress);
}

void UpdateChecker::appendLog(const QString &t)
{
    if (t.trimmed().isEmpty()) return;
    m_log->append(t.trimmed());
}

void UpdateChecker::toggleLog()
{
    m_logOpen = !m_logOpen;
    m_logContainer->setVisible(m_logOpen);
    m_detailsBtn->setText(m_logOpen ? "▲  Hide details" : "▼  Show details");
    adjustSize();
}

void UpdateChecker::runFetch()
{
    setStage(Stage::Check);
    setStatus("Checking GitHub…", 5);
    appendLog("$ git fetch origin");
    m_state = State::Fetching;
    m_proc = new QProcess(this);
    m_proc->setWorkingDirectory(m_workDir);
    m_proc->setProcessChannelMode(QProcess::MergedChannels);
    connect(m_proc, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, &UpdateChecker::onProcFinished);
    connect(m_proc, &QProcess::readyRead, this, [this]() {
        appendLog(QString::fromUtf8(m_proc->readAll()));
    });
    m_proc->start("git", {"fetch", "origin"});
}

void UpdateChecker::afterFetch(int code)
{
    if (code != 0) { fail("git fetch failed — check your internet connection."); return; }

    // read target tag
    QProcess tagP;
    tagP.setWorkingDirectory(m_workDir);
    tagP.start("git", {"describe", "--tags", "--abbrev=0", "origin/main"});
    tagP.waitForFinished(3000);
    QString tag = QString::fromUtf8(tagP.readAllStandardOutput()).trimmed();
    if (tag.isEmpty()) {
        QProcess hP;
        hP.setWorkingDirectory(m_workDir);
        hP.start("git", {"rev-parse", "--short", "origin/main"});
        hP.waitForFinished(2000);
        tag = QString::fromUtf8(hP.readAllStandardOutput()).trimmed();
    }
    m_targetVersion = tag;

    QProcess lh; lh.setWorkingDirectory(m_workDir);
    lh.start("git", {"rev-parse", "HEAD"}); lh.waitForFinished(3000);
    QString local = QString::fromUtf8(lh.readAllStandardOutput()).trimmed();
    QProcess rh; rh.setWorkingDirectory(m_workDir);
    rh.start("git", {"rev-parse", "origin/main"}); rh.waitForFinished(3000);
    QString remote = QString::fromUtf8(rh.readAllStandardOutput()).trimmed();

    if (local == remote || remote.isEmpty()) {
        m_newVer->setText("up to date ✓");
        m_newVer->setStyleSheet("color: #4ade80; font-size: 13px; font-weight: bold;");
        setStage(Stage::Done);
        setStatus("You're already on the latest version.", 100);
        m_cancelBtn->setText("Close");
        QTimer::singleShot(1400, this, &QDialog::reject);
        return;
    }

    m_newVer->setText(m_targetVersion);
    appendLog("Update available: " + local.left(7) + " → " + remote.left(7));
    runPull();
}

void UpdateChecker::runPull()
{
    setStage(Stage::Download);
    setStatus("Downloading update…", 25);
    appendLog("$ git pull --ff-only origin main");
    m_state = State::Pulling;
    m_proc = new QProcess(this);
    m_proc->setWorkingDirectory(m_workDir);
    m_proc->setProcessChannelMode(QProcess::MergedChannels);
    connect(m_proc, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, &UpdateChecker::onProcFinished);
    connect(m_proc, &QProcess::readyRead, this, [this]() {
        appendLog(QString::fromUtf8(m_proc->readAll()));
    });
    m_proc->start("git", {"pull", "--ff-only", "origin", "main"});
}

void UpdateChecker::runBuild()
{
    setStage(Stage::Build);
    setStatus("Building SudoStrap…", 45);
    appendLog("$ bash build.sh");
    m_state = State::Building;
    m_proc = new QProcess(this);
    m_proc->setWorkingDirectory(m_workDir);
    m_proc->setProcessChannelMode(QProcess::MergedChannels);
    connect(m_proc, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, &UpdateChecker::onProcFinished);
    connect(m_proc, &QProcess::readyRead, this, [this]() {
        QString chunk = QString::fromUtf8(m_proc->readAll());
        appendLog(chunk);
        if (chunk.contains("Building")) setStatus("Compiling sources…", 60);
        if (chunk.contains("Linking"))  setStatus("Linking binary…", 85);
    });
    m_proc->start("bash", {"build.sh"});
}

void UpdateChecker::onProcFinished(int code)
{
    if (!m_proc) return;
    m_proc->deleteLater();
    m_proc = nullptr;

    switch (m_state) {
    case State::Fetching:
        afterFetch(code);
        break;
    case State::Pulling:
        if (code != 0) { fail("git pull failed — you may have local changes."); return; }
        runBuild();
        break;
    case State::Building:
        if (code != 0) { fail("Build failed — see details for errors."); return; }
        setStage(Stage::Done);
        setStatus("Update installed ✓  Restarting…", 100);
        m_updateApplied = true;
        m_cancelBtn->setVisible(false);
        QTimer::singleShot(1400, this, &QDialog::accept);
        break;
    default:
        break;
    }
}

void UpdateChecker::fail(const QString &msg)
{
    m_state = State::Failed;
    setStageFailed(m_stage);
    setStatus("⚠  " + msg, 100);
    m_progress->setStyleSheet(
        "QProgressBar { background-color:#2d2d30; border:1px solid #3e3e42;"
        "border-radius:6px; height:22px; text-align:center; color:#fff; font-weight:bold;}"
        "QProgressBar::chunk { background-color:#c0392b; border-radius:5px; }");
    m_cancelBtn->setText("Close");
    if (!m_logOpen) toggleLog();
}

void UpdateChecker::closeEvent(QCloseEvent *e)
{
    if (m_proc) { m_proc->kill(); m_proc->waitForFinished(800); }
    e->accept();
}
