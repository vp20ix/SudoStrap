#include "ui/mainwindow.h"
#include "ui/toggleswitch.h"
#include "ui_mainwindow.h"
#include "ui/customffdialog.h"
#include "ui/updatedialog.h"
#include "ui/launchdialog.h"

#include <QMessageBox>
#include <QJsonParseError>
#include <QDateTime>
#include <QFileDialog>
#include <QFileInfo>
#include <QStyle>
#include <QSaveFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QDebug>
#include <QSignalBlocker>
#include <QWidget>
#include <QAbstractItemView>
#include <QPixmap>
#include <QPainter>
#include <QSvgRenderer>
#include <QUrl>
#include <QDesktopServices>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QEvent>
#include <QGraphicsDropShadowEffect>
#include <QColor>
#include <QTimer>
#include <QProcess>
#include <QStandardPaths>
#include <QDir>
#include <QStringList>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    m_autoUpdateEnabled = false;
    m_activePreset = -1;

    // ============ Fix ComboBox popup ============
    auto styleComboPopup = [](QComboBox *combo) {
        if (!combo || !combo->view()) return;
        if (auto *container = combo->view()->parentWidget()) {
            container->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
            container->setStyleSheet(
                "QWidget { background-color: #1a1a26; "
                "border: 1px solid #2a2a3e; border-radius: 8px; }"
            );
        }
    };

    styleComboPopup(ui->renderDistCombo);
    styleComboPopup(ui->texQualityCombo);
    styleComboPopup(ui->lightingCombo);
    styleComboPopup(ui->setLangCombo);
    styleComboPopup(ui->gfxApiCombo);




    m_dirty = false;
    
    ui->saveButton->setEnabled(false);

    installGlow(ui->launchButton, QColor(0, 120, 212), 32);
    installGlow(ui->saveButton,   QColor(34, 211, 238), 24);
    installGlow(ui->closeButton,  QColor(255, 90, 90), 24);
    installGlow(ui->resetButton,  QColor(240, 160, 80), 24);
    installGlow(ui->ffCustomButton, QColor(34, 211, 238), 28);
    installGlow(ui->btnGithub, QColor(34, 211, 238), 24);
    installGlow(ui->btnDocs,   QColor(34, 211, 238), 24);
    installGlow(ui->btnIssue,  QColor(124, 92, 255), 24);

    // ============ Bidirectional sync ============
    // FPS Limit
    connect(ui->targetFpsSpin2, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int v) {
        if (ui->targetFpsSpin->value() != v) {
            QSignalBlocker bl(ui->targetFpsSpin);
            ui->targetFpsSpin->setValue(v);
        }
        // Any FPS value → enable unlock toggle
        if (auto *ts = qobject_cast<ToggleSwitch*>(ui->unlockFpsCheck)) {
            if (!ts->isChecked()) ts->setCheckedVisual(true);
        }
    });
    connect(ui->targetFpsSpin, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int v) {
        if (ui->targetFpsSpin2->value() != v) {
            QSignalBlocker bl(ui->targetFpsSpin2);
            ui->targetFpsSpin2->setValue(v);
        }
        if (auto *ts = qobject_cast<ToggleSwitch*>(ui->unlockFpsCheck)) {
            if (!ts->isChecked()) ts->setCheckedVisual(true);
        }
    });

    // Shadows <-> CSG
    connect(ui->shadowsCheck, &QAbstractButton::toggled, this, [this](bool on) {
        QSignalBlocker bl(ui->csgLodSpin);
        ui->csgLodSpin->setValue(on ? 0 : 500);
    });
    connect(ui->csgLodSpin, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int v) {
        QSignalBlocker bl(ui->shadowsCheck);
        ui->shadowsCheck->setChecked(v == 0);
    });

    // PostFx <-> FRM
    connect(ui->postFxCheck, &QAbstractButton::toggled, this, [this](bool on) {
        QSignalBlocker bl(ui->frmQualitySpin);
        ui->frmQualitySpin->setValue(on ? 1 : 10);
    });
    connect(ui->frmQualitySpin, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int v) {
        QSignalBlocker bl(ui->postFxCheck);
        ui->postFxCheck->setChecked(v == 1);
    });


    // About page links
    connect(ui->btnGithub, &QPushButton::clicked, this, []() {
        QDesktopServices::openUrl(QUrl("https://github.com/vp20ix/SudoStrap"));
    });
    connect(ui->btnDocs, &QPushButton::clicked, this, []() {
        QDesktopServices::openUrl(QUrl("https://github.com/vp20ix/SudoStrap/wiki"));
    });
    connect(ui->btnIssue, &QPushButton::clicked, this, []() {
        QDesktopServices::openUrl(QUrl("https://github.com/vp20ix/SudoStrap/issues"));
    });

    auto connectDirty = [this](QObject *obj) {
        if (auto *cb = qobject_cast<QAbstractButton*>(obj))
            connect(cb, &QAbstractButton::toggled, this, &MainWindow::markDirty);
        else if (auto *sp = qobject_cast<QSpinBox*>(obj))
            connect(sp, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::markDirty);
        else if (auto *cbx = qobject_cast<QComboBox*>(obj))
            connect(cbx, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::markDirty);
        else if (auto *le = qobject_cast<QLineEdit*>(obj))
            connect(le, &QLineEdit::textChanged, this, &MainWindow::markDirty);
    };

    for (auto *w : {static_cast<QObject*>(ui->unlockFpsCheck), static_cast<QObject*>(ui->shadowsCheck),
                    static_cast<QObject*>(ui->postFxCheck), static_cast<QObject*>(ui->grassCheck),
                    static_cast<QObject*>(ui->aaCheck), static_cast<QObject*>(ui->bloomCheck),
                    static_cast<QObject*>(ui->skyGrayCheck), static_cast<QObject*>(ui->renderDistCombo),
                    static_cast<QObject*>(ui->texQualityCombo), static_cast<QObject*>(ui->lightingCombo),
                    static_cast<QObject*>(ui->targetFpsSpin), static_cast<QObject*>(ui->targetFpsSpin2),
                    static_cast<QObject*>(ui->csgLodSpin), static_cast<QObject*>(ui->frmQualitySpin)}) {
        connectDirty(w);
    }

    

    // Styling properties (dynamic)
    ui->navSectionLabel->setProperty("role", "navSection");
    ui->statusChip->setProperty("role", "statusChip");
    ui->perfEyebrow->setProperty("role", "eyebrow");
    ui->perfTitle->setProperty("role", "pageTitle");
    ui->perfSubtitle->setProperty("role", "pageSubtitle");
    ui->row1->setProperty("role", "row");
    ui->icon1->setProperty("role", "icon");
    ui->t1->setProperty("role", "rowTitle");
    ui->d1->setProperty("role", "rowDesc");
    ui->unlockFpsCheck->setProperty("role", "toggle");
    ui->row2->setProperty("role", "row");
    ui->icon2->setProperty("role", "icon");
    ui->t2->setProperty("role", "rowTitle");
    ui->d2->setProperty("role", "rowDesc");
    ui->row3->setProperty("role", "row");
    ui->icon3->setProperty("role", "icon");
    ui->t3->setProperty("role", "rowTitle");
    ui->d3->setProperty("role", "rowDesc");
    ui->shadowsCheck->setProperty("role", "toggle");
    ui->row4->setProperty("role", "row");
    ui->icon4->setProperty("role", "icon");
    ui->t4->setProperty("role", "rowTitle");
    ui->d4->setProperty("role", "rowDesc");
    ui->postFxCheck->setProperty("role", "toggle");
    ui->row5->setProperty("role", "row");
    ui->icon5->setProperty("role", "icon");
    ui->t5->setProperty("role", "rowTitle");
    ui->d5->setProperty("role", "rowDesc");
    ui->gfxEyebrow->setProperty("role", "eyebrow");
    ui->gfxTitle->setProperty("role", "pageTitle");
    ui->gfxSubtitle->setProperty("role", "pageSubtitle");
    ui->grow1->setProperty("role", "row");
    ui->gicon1->setProperty("role", "icon");
    ui->gt1->setProperty("role", "rowTitle");
    ui->gd1->setProperty("role", "rowDesc");
    ui->grassCheck->setProperty("role", "toggle");
    ui->grow2->setProperty("role", "row");
    ui->gicon2->setProperty("role", "icon");
    ui->gt2->setProperty("role", "rowTitle");
    ui->gd2->setProperty("role", "rowDesc");
    ui->grow3->setProperty("role", "row");
    ui->gicon3->setProperty("role", "icon");
    ui->gt3->setProperty("role", "rowTitle");
    ui->gd3->setProperty("role", "rowDesc");
    ui->grow4->setProperty("role", "row");
    ui->gicon4->setProperty("role", "icon");
    ui->gt4->setProperty("role", "rowTitle");
    ui->gd4->setProperty("role", "rowDesc");
    ui->aaCheck->setProperty("role", "toggle");
    ui->grow5->setProperty("role", "row");
    ui->gicon5->setProperty("role", "icon");
    ui->gt5->setProperty("role", "rowTitle");
    ui->gd5->setProperty("role", "rowDesc");
    ui->bloomCheck->setProperty("role", "toggle");
    ui->grow6->setProperty("role", "row");
    ui->gicon6->setProperty("role", "icon");
    ui->gt6->setProperty("role", "rowTitle");
    ui->gd6->setProperty("role", "rowDesc");
    ui->skyGrayCheck->setProperty("role", "toggle");
    ui->ffEyebrow->setProperty("role", "eyebrow");
    ui->ffTitle->setProperty("role", "pageTitle");
    ui->ffSubtitle->setProperty("role", "pageSubtitle");
    ui->ffrow1->setProperty("role", "row");
    ui->fficon1->setProperty("role", "icon");
    ui->fft1->setProperty("role", "rowTitle");
    ui->ffd1->setProperty("role", "rowDesc");
    ui->ffrow2->setProperty("role", "row");
    ui->fficon2->setProperty("role", "icon");
    ui->fft2->setProperty("role", "rowTitle");
    ui->ffd2->setProperty("role", "rowDesc");
    ui->ffrow3->setProperty("role", "row");
    ui->fficon3->setProperty("role", "icon");
    ui->fft3->setProperty("role", "rowTitle");
    ui->ffd3->setProperty("role", "rowDesc");
    ui->ffCtaFrame->setProperty("role", "cta");
    ui->ffCtaTitle->setProperty("role", "rowTitle");
    ui->ffCtaDesc->setProperty("role", "rowDesc");
    ui->ffCustomButton->setProperty("role", "primaryBtn");
    ui->setEyebrow->setProperty("role", "eyebrow");
    ui->setTitle->setProperty("role", "pageTitle");
    ui->setSubtitle->setProperty("role", "pageSubtitle");
    ui->abtEyebrow->setProperty("role", "eyebrow");
    ui->abtTitle->setProperty("role", "pageTitle");
    ui->abtSubtitle->setProperty("role", "pageSubtitle");
    ui->versionLabel->setProperty("role", "version");
    ui->resetButton->setProperty("role", "footerReset");
    ui->saveButton->setProperty("role", "footerSave");
    ui->closeButton->setProperty("role", "footerClose");


    // ربط الأزرار
    connect(ui->btnPerformance, &QPushButton::clicked, this, &MainWindow::showPerformancePage);
    connect(ui->btnGraphics, &QPushButton::clicked, this, &MainWindow::showGraphicsPage);
    connect(ui->btnFastFlags, &QPushButton::clicked, this, &MainWindow::showFastFlagsPage);
    connect(ui->btnSettings, &QPushButton::clicked, this, &MainWindow::showSettingsPage);
    connect(ui->btnAbout, &QPushButton::clicked, this, &MainWindow::showAboutPage);
    connect(ui->ffCustomButton, &QPushButton::clicked, this, &MainWindow::openCustomFFDialog);
    connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::onSaveClicked);

    // Preset connections
    connect(ui->presetsToggle, &QAbstractButton::toggled, this, &MainWindow::onPresetsToggle);
    connect(ui->presetPerfApply, &QPushButton::clicked, this, [this]() { applyPreset(0); });
    connect(ui->presetBalApply, &QPushButton::clicked, this, [this]() { applyPreset(1); });
    connect(ui->presetQualApply, &QPushButton::clicked, this, [this]() { applyPreset(2); });
    connect(ui->presetPerfDetails, &QPushButton::clicked, this, [this]() { showPresetDetails(0); });
    connect(ui->presetBalDetails, &QPushButton::clicked, this, [this]() { showPresetDetails(1); });
    connect(ui->presetQualDetails, &QPushButton::clicked, this, [this]() { showPresetDetails(2); });
    connect(ui->resetButton, &QPushButton::clicked, this, &MainWindow::onResetClicked);
    connect(ui->closeButton, &QPushButton::clicked, this, &MainWindow::onCloseClicked);

    // Settings connections
    connect(ui->setToggleUpdate, &QAbstractButton::toggled, this, [this](bool on) {
        m_autoUpdateEnabled = on;
        markDirty();
    });
    connect(ui->setToggleStartup, &QAbstractButton::toggled, this, [this](bool) {
        markDirty();
    });
    connect(ui->setLangCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onLanguageChanged);
    connect(ui->launchButton, &QPushButton::clicked, this, &MainWindow::onLaunchClicked);

    // Load saved config on startup
    syncConfigToUI_Load();

}

MainWindow::~MainWindow() { delete ui; }


void MainWindow::setStatus(const QString &text) {
    ui->versionLabel->setText("v0.1.0  ·  " + text);
}

void MainWindow::showProgress(int value) {
    ui->progressBar->setVisible(true);
    ui->progressBar->setValue(value);
}

void MainWindow::hideProgress() {
    ui->progressBar->setVisible(false);
    ui->progressBar->setValue(0);
}

void MainWindow::showPerformancePage() { ui->pagesStack->setCurrentIndex(0); }
void MainWindow::showGraphicsPage()    { ui->pagesStack->setCurrentIndex(1); }
void MainWindow::showFastFlagsPage()   { ui->pagesStack->setCurrentIndex(2); }
void MainWindow::showSettingsPage()    { ui->pagesStack->setCurrentIndex(3); }
void MainWindow::showAboutPage()       { ui->pagesStack->setCurrentIndex(4); }

void MainWindow::openCustomFFDialog()
{
    CustomFFDialog dialog(this);
    dialog.setInitialFlags(m_config.flags());
    
    if (dialog.exec() == QDialog::Accepted) {
        QMap<QString, QString> oldFlags = m_config.flags();
        QMap<QString, QString> newFlags = dialog.currentFlags();
        
        // Apply to memory
        m_config.clearFlags();
        for (auto it = newFlags.begin(); it != newFlags.end(); ++it) {
            m_config.setFlag(it.key(), it.value());
        }
        
        
        markDirty();
        setStatus(QString::fromUtf8("Custom flags updated \u2713"));
        QTimer::singleShot(2000, this, [this]() { setStatus("Ready"); });
    }
}

void MainWindow::syncConfigToUI()
{
    // ---- FPS ----
    if (ui->unlockFpsCheck->isChecked()) {
        m_config.setFlag("DFIntTaskSchedulerTargetFps",
                         QString::number(ui->targetFpsSpin2->value()));
    } else {
        m_config.removeFlag("DFIntTaskSchedulerTargetFps");
    }

    // ---- Shadows / CSG ----
    if (ui->shadowsCheck->isChecked()) {
        m_config.setFlag("DFIntCSGLevelOfDetailSwitchingDistance", "0");
    } else {
        m_config.setFlag("DFIntCSGLevelOfDetailSwitchingDistance",
                         QString::number(ui->csgLodSpin->value()));
    }

    // ---- Grass / Render Distance (only ONE writes to the flag) ----
    if (ui->grassCheck->isChecked()) {
        // Grass disable overrides render distance
        m_config.setFlag("FIntFRMMaxGrassDistance", "0");
    } else {
        int rdi = ui->renderDistCombo->currentIndex();
        int dist = (rdi == 0) ? 0 : (rdi == 1) ? 500 : 1000;
        m_config.setFlag("FIntFRMMaxGrassDistance", QString::number(dist));
    }

    // ---- Texture Quality ----
    m_config.setFlag("DFIntTextureQualityOverride",
                     QString::number(ui->texQualityCombo->currentIndex()));

    // ---- Post-FX / FRM ----
    if (ui->postFxCheck->isChecked()) {
        m_config.setFlag("DFIntDebugFRMQualityLevelOverride", "1");
    } else {
        m_config.setFlag("DFIntDebugFRMQualityLevelOverride",
                         QString::number(ui->frmQualitySpin->value()));
    }

    // ---- AA ----
    if (ui->aaCheck->isChecked()) {
        m_config.setFlag("FIntDebugForceMSAASamples", "1");
    } else {
        m_config.removeFlag("FIntDebugForceMSAASamples");
    }

    // ---- Gray Sky ----
    if (ui->skyGrayCheck->isChecked()) {
        m_config.setFlag("FFlagDebugSkyGray", "true");
    } else {
        m_config.removeFlag("FFlagDebugSkyGray");
    }

    // ---- Network / Ping Boost ----
    if (ui->pingBoostCheck->isChecked()) {
        m_config.setFlag("DFIntSendMovementRateHz", "60");
        m_config.setFlag("DFIntSendPhysicsRateHz", "60");
        m_config.setFlag("DFIntServerTickRate", "60");
        m_config.setFlag("DFIntDataSenderMaxLatency", "100");
        m_config.setFlag("DFIntMinimalNetworkPeerStallTimeoutMs", "2000");
        m_config.setFlag("FFlagDisablePacketCache", "true");
        m_config.setFlag("FFlagEnablePhysicsInterpolation", "true");
        m_config.setFlag("FFlagPhysicsInterpolationUseFastMath", "true");
        m_config.setFlag("DFIntNetworkBandwidthThrottlingRatio", "0");
        m_config.setFlag("DFIntMaxPendingBandwidthTotalBytes", "104857600");
        m_config.setFlag("DFIntClientNetworkMaximumTimeoutMs", "5000");
        m_config.setFlag("FFlagFixNetworkBandwidthLimit", "true");
    } else {
        m_config.removeFlag("DFIntSendMovementRateHz");
        m_config.removeFlag("DFIntSendPhysicsRateHz");
        m_config.removeFlag("DFIntServerTickRate");
        m_config.removeFlag("DFIntDataSenderMaxLatency");
        m_config.removeFlag("DFIntMinimalNetworkPeerStallTimeoutMs");
        m_config.removeFlag("FFlagDisablePacketCache");
        m_config.removeFlag("FFlagEnablePhysicsInterpolation");
        m_config.removeFlag("FFlagPhysicsInterpolationUseFastMath");
        m_config.removeFlag("DFIntNetworkBandwidthThrottlingRatio");
        m_config.removeFlag("DFIntMaxPendingBandwidthTotalBytes");
        m_config.removeFlag("DFIntClientNetworkMaximumTimeoutMs");
        m_config.removeFlag("FFlagFixNetworkBandwidthLimit");
    }
}


void MainWindow::onCloseClicked() { close(); }

void MainWindow::onLaunchClicked() {
    // ← استرجع إعداداتك من profile.json قبل تشغيل Sober
    if (m_config.loadProfile()) {
        m_config.save();  // اكتبها في config.json
        setStatus("Settings restored");
    }
    
    LaunchDialog dlg(this);
    dlg.startLaunch();
    dlg.exec();
    
    // بعد ما ينتهي الـ Dialog، أغلق البرنامج الرئيسي
    close();
}


void MainWindow::onResetClicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Confirm Reset",
        "Reset all settings to defaults?\n\n"
        "This will:\n"
        "• Set FPS Limit back to 240\n"
        "• Reset all toggles to OFF\n"
        "• Clear active preset\n\n"
        "This cannot be undone.",
        QMessageBox::Yes | QMessageBox::No,
        QMessageBox::No
    );

    if (reply != QMessageBox::Yes) {
        return;
    }

    // Reset UI to defaults
    if (auto *ts = qobject_cast<ToggleSwitch*>(ui->unlockFpsCheck)) ts->setCheckedVisual(false);
    ui->targetFpsSpin2->setValue(240);
    ui->targetFpsSpin->setValue(240);

    if (auto *ts = qobject_cast<ToggleSwitch*>(ui->shadowsCheck)) ts->setCheckedVisual(false);
    if (auto *ts = qobject_cast<ToggleSwitch*>(ui->postFxCheck)) ts->setCheckedVisual(false);
    if (auto *ts = qobject_cast<ToggleSwitch*>(ui->grassCheck)) ts->setCheckedVisual(false);
    if (auto *ts = qobject_cast<ToggleSwitch*>(ui->aaCheck)) ts->setCheckedVisual(false);
    if (auto *ts = qobject_cast<ToggleSwitch*>(ui->skyGrayCheck)) ts->setCheckedVisual(false);
    if (auto *ts = qobject_cast<ToggleSwitch*>(ui->pingBoostCheck)) ts->setCheckedVisual(false);

    ui->renderDistCombo->setCurrentIndex(1);
    ui->texQualityCombo->setCurrentIndex(2);
    ui->lightingCombo->setCurrentIndex(0);
    ui->csgLodSpin->setValue(500);
    ui->frmQualitySpin->setValue(10);

    setActivePreset(-1);

    // Clear ALL flags in memory
    m_config.clearFlags();

    // Delete config file
    QString configPath = QDir::homePath() +
        "/.var/app/org.vinegarhq.Sober/config/sober/config.json";

    if (QFile::exists(configPath)) {
        QFile::remove(configPath);
    }

    // Write only defaults (no flags)
    m_config.save();
    setStatus("Reset to defaults");
    QTimer::singleShot(2000, this, [this]() { setStatus("Ready"); });
}


void MainWindow::onSaveClicked()
{
    // Check if Sober is running
    QProcess check;
    check.start("flatpak", {"ps"});
    check.waitForFinished(1500);
    QString output = QString::fromUtf8(check.readAllStandardOutput());
    bool soberRunning = output.contains("org.vinegarhq.Sober");

    if (soberRunning) {
        QMessageBox::warning(this, "Sober is Running",
            "Sober is currently running. Saving settings now may "
            "cause Roblox to crash or close.\n\n"
            "Please close Sober first, then save again.");
        return;
    }

    setStatus("Saving...");
    showProgress(0);
    QTimer::singleShot(200, this, [this]() { showProgress(50); });

    QTimer::singleShot(500, this, [this]() {
        syncConfigToUI();

        if (m_config.save()) {
            m_config.saveProfile();  // ← احفظ نسخة خاصة
            showProgress(100);
            setStatus("Saved OK");
            resetDirty();
            QTimer::singleShot(700, this, [this]() { hideProgress(); });
            QTimer::singleShot(2400, this, [this]() { setStatus("Ready"); });
        } else {
            hideProgress();
            setStatus("Save failed");
            QMessageBox::warning(this, "Save Failed", m_config.lastError());
            QTimer::singleShot(3000, this, [this]() { setStatus("Ready"); });
        }
    });
}

void MainWindow::markDirty()
{
    if (!m_dirty) {
        m_dirty = true;
        ui->saveButton->setEnabled(true);
    }
}

void MainWindow::resetDirty()
{
    m_dirty = false;
    ui->saveButton->setEnabled(false);
}

void MainWindow::installGlow(QPushButton *btn, const QColor &color, int maxBlur)
{
    auto *eff = new QGraphicsDropShadowEffect(btn);
    eff->setBlurRadius(0);
    eff->setColor(color);
    eff->setOffset(0, 0);
    btn->setGraphicsEffect(eff);
    btn->setProperty("glowColor", color);
    btn->setProperty("glowMax", maxBlur);
    btn->installEventFilter(this);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    auto *btn = qobject_cast<QPushButton*>(obj);
    if (!btn || !btn->property("glowColor").isValid())
        return QMainWindow::eventFilter(obj, event);

    auto *eff = qobject_cast<QGraphicsDropShadowEffect*>(btn->graphicsEffect());
    if (!eff)
        return QMainWindow::eventFilter(obj, event);

    const int maxBlur = btn->property("glowMax").toInt();

    // إضافة الأنيميشن على خاصية blurRadius
    auto animateTo = [eff](int target, int duration) {
        if (eff->property("animating").toBool() &&
            eff->property("target").toInt() == target)
            return;
        auto *anim = new QPropertyAnimation(eff, "blurRadius", eff);
        anim->setDuration(duration);
        anim->setStartValue(eff->blurRadius());
        anim->setEndValue(target);
        anim->setEasingCurve(QEasingCurve::OutCubic);
        eff->setProperty("animating", true);
        eff->setProperty("target", target);
        QObject::connect(anim, &QPropertyAnimation::finished, eff, [eff]() {
            eff->setProperty("animating", false);
        });
        anim->start(QAbstractAnimation::DeleteWhenStopped);
    };

    if (event->type() == QEvent::Enter && btn->isEnabled()) {
        animateTo(maxBlur, 240);
    } else if (event->type() == QEvent::Leave || event->type() == QEvent::FocusOut) {
        animateTo(0, 300);
    } else if (event->type() == QEvent::EnabledChange) {
        if (!btn->isEnabled()) animateTo(0, 200);
    }

    return QMainWindow::eventFilter(obj, event);
}




void MainWindow::onLanguageChanged(int index)
{
    applyLanguage(index == 1 ? "ar" : "en");
    markDirty();
}

void MainWindow::applyLanguage(const QString &lang)
{
    m_currentLang = lang;
    const bool ar = (lang == "ar");

    // ============ Sidebar ============
    ui->navSectionLabel->setText(ar ? QString::fromUtf8("مساحة العمل") : "WORKSPACE");
    ui->btnPerformance->setText(ar ? QString::fromUtf8("⚡   الأداء") : "⚡   Performance");
    ui->btnGraphics->setText(ar ? QString::fromUtf8("🎨   الرسومات") : "🎨   Graphics");
    ui->btnFastFlags->setText(ar ? QString::fromUtf8("🔧   الفاست فلاق") : "🔧   FastFlags");
    ui->btnSettings->setText(ar ? QString::fromUtf8("⚙️   الإعدادات") : "⚙️   Settings");
    ui->btnAbout->setText(ar ? QString::fromUtf8("ℹ️   حول") : "ℹ️   About");
    ui->statusChip->setText(ar ? QString::fromUtf8("●  Sober جاهز") : "●  Sober Ready");
    ui->launchButton->setText(ar ? QString::fromUtf8("▶   تشغيل Sober") : "▶   Launch Sober");

    // ============ Footer buttons ============
    ui->resetButton->setText(ar ? QString::fromUtf8("↺  إعادة تعيين") : "↺  Reset");
    ui->saveButton->setText(ar ? QString::fromUtf8("💾  حفظ") : "💾  Save");
    ui->closeButton->setText(ar ? QString::fromUtf8("✕  إغلاق") : "✕  Close");

    // ============ Performance ============
    ui->perfEyebrow->setText(ar ? QString::fromUtf8("الأداء") : "PERFORMANCE");
    ui->perfTitle->setText(ar ? QString::fromUtf8("ضبط أداء Roblox") : "Tune Roblox Performance");
    ui->perfSubtitle->setText(ar ? QString::fromUtf8("احصل على FPS أكثر دون التضحية بالاستقرار") : "Get more FPS without sacrificing stability");

    ui->t1->setText(ar ? QString::fromUtf8("فتح FPS") : "Unlock FPS");
    ui->d1->setText(ar ? QString::fromUtf8("تجاوز حد 60 FPS الافتراضي") : "Bypass Roblox default 60 FPS cap");
    ui->t2->setText(ar ? QString::fromUtf8("مسافة العرض") : "Render Distance");
    ui->d2->setText(ar ? QString::fromUtf8("تقليل تفاصيل الأجسام البعيدة") : "Lower far-object detail for more FPS");
    ui->t3->setText(ar ? QString::fromUtf8("تعطيل الظلال") : "Disable Shadows");
    ui->d3->setText(ar ? QString::fromUtf8("يزيل الظلال الديناميكية لزيادة FPS") : "Removes dynamic shadows for a large FPS boost");
    ui->t4->setText(ar ? QString::fromUtf8("تعطيل المعالجة اللاحقة") : "Disable Post-Processing");
    ui->d4->setText(ar ? QString::fromUtf8("يزيل التوهج، عمق الميدان، وأشعة الشمس") : "Removes bloom, depth of field, and sun rays");
    ui->t5->setText(ar ? QString::fromUtf8("حد FPS") : "FPS Limit");
    ui->d5->setText(ar ? QString::fromUtf8("ضبط الحد الأقصى للإطارات (0 = بلا حدود)") : "Set maximum framerate (0 = unlimited)");

    // ============ Graphics ============
    ui->gfxEyebrow->setText(ar ? QString::fromUtf8("الرسومات") : "GRAPHICS");
    ui->gfxTitle->setText(ar ? QString::fromUtf8("الجودة البصرية") : "Visual Quality");
    ui->gfxSubtitle->setText(ar ? QString::fromUtf8("بادل الجمال بالأداء") : "Trade beauty for performance");

    ui->gt1->setText(ar ? QString::fromUtf8("تعطيل ملمس العشب") : "Disable Grass Textures");
    ui->gd1->setText(ar ? QString::fromUtf8("يزيل العشب من التضاريس") : "Removes grass from terrain");
    ui->gt2->setText(ar ? QString::fromUtf8("جودة الملمس") : "Texture Quality");
    ui->gd2->setText(ar ? QString::fromUtf8("الجودة الأقل تقلل استهلاك VRAM") : "Lower quality reduces VRAM usage");
    ui->gt3->setText(ar ? QString::fromUtf8("وضع الإضاءة") : "Lighting Mode");
    ui->gd3->setText(ar ? QString::fromUtf8("Voxel هو الأسرع") : "Voxel is fastest");
    ui->gt4->setText(ar ? QString::fromUtf8("تعطيل تنعيم الحواف") : "Disable Anti-Aliasing");
    ui->gd4->setText(ar ? QString::fromUtf8("ينعم الحواف") : "Smooths edges");
    ui->gt5->setText(ar ? QString::fromUtf8("تعطيل التوهج") : "Disable Bloom");
    ui->gd5->setText(ar ? QString::fromUtf8("يزيل التوهج حول الأضواء") : "Removes glow around lights");
    ui->gt6->setText(ar ? QString::fromUtf8("سماء رمادية") : "Gray Sky");
    ui->gd6->setText(ar ? QString::fromUtf8("يستبدل السماء بالرمادي") : "Replaces sky with gray");

    // ============ FastFlags ============
    ui->ffEyebrow->setText(ar ? QString::fromUtf8("متقدم") : "ADVANCED");
    ui->ffTitle->setText(ar ? QString::fromUtf8("محرر الفاست فلاق") : "FastFlags Editor");
    ui->ffSubtitle->setText(ar ? QString::fromUtf8("ضبط دقيق لأعلام العرض") : "Fine-tune rendering flags");

    ui->fft1->setText(ar ? QString::fromUtf8("CSG مستوى التفاصيل") : "CSG Level of Detail");
    ui->fft2->setText(ar ? QString::fromUtf8("تجاوز جودة FRM") : "FRM Quality Override");
    ui->fft3->setText(ar ? QString::fromUtf8("FPS المستهدف") : "Target FPS");

    ui->ffCtaTitle->setText(ar ? QString::fromUtf8("تحتاج تحكم أكثر؟") : "Need more control?");
    ui->ffCtaDesc->setText(ar ? QString::fromUtf8("أضف أعلام مخصصة، استورد من ملف، أو الصق JSON") : "Add custom flags, import from file, or paste JSON");
    ui->ffCustomButton->setText(ar ? QString::fromUtf8("⚙️  فاست فلاق مخصص") : "⚙️  Custom FastFlags");

    // ============ Settings ============
    ui->setEyebrow->setText(ar ? QString::fromUtf8("الإعدادات") : "SETTINGS");
    ui->setTitle->setText(ar ? QString::fromUtf8("الإعدادات") : "Configuration");
    ui->setSubtitle->setText(ar ? QString::fromUtf8("اضبط SudoStrap حسب تفضيلاتك") : "Configure SudoStrap to your preferences");
    ui->setSectionGeneral->setText(ar ? QString::fromUtf8("عام") : "GENERAL");
    ui->setTitleUpdate->setText(ar ? QString::fromUtf8("التحديث التلقائي") : "Auto-Update");
    ui->setDescUpdate->setText(ar ? QString::fromUtf8("فحص وتثبيت التحديثات تلقائياً عند البدء") : "Automatically check and install updates on startup");
    ui->setTitleStartup->setText(ar ? QString::fromUtf8("التشغيل مع النظام") : "Launch on Startup");
    ui->setDescStartup->setText(ar ? QString::fromUtf8("تشغيل SudoStrap تلقائياً مع النظام") : "Start SudoStrap automatically with your system");
    ui->setSectionLang->setText(ar ? QString::fromUtf8("اللغة") : "LANGUAGE");
    ui->setTitleLang->setText(ar ? QString::fromUtf8("لغة الواجهة") : "Interface Language");
    ui->setDescLang->setText(ar ? QString::fromUtf8("اختر لغة واجهة SudoStrap") : "Choose the language for SudoStrap interface");

    // ============ About ============
    ui->abtEyebrow->setText(ar ? QString::fromUtf8("حول") : "ABOUT");
    ui->abtSubtitle->setText(ar ? QString::fromUtf8("مدير الفاست فلاق للينكس") : "FastFlags Manager for Linux");
    ui->abtHeroVersion->setText(ar ? QString::fromUtf8("الإصدار 0.1.0") : "Version 0.1.0");
    ui->abtHeroDesc->setText(ar ? QString::fromUtf8("مدير FastFlags عصري لـ Roblox على لينكس — مبني بـ Qt6 و C++.") : "A modern FastFlags manager for Roblox on Linux — built with Qt6 and C++.");
    ui->abtLinksTitle->setText(ar ? QString::fromUtf8("روابط") : "LINKS");
    ui->btnGithub->setText(ar ? QString::fromUtf8("📖  GitHub") : "📖  GitHub");
    ui->btnDocs->setText(ar ? QString::fromUtf8("📚  التوثيق") : "📚  Documentation");
    ui->btnIssue->setText(ar ? QString::fromUtf8("🐛  الإبلاغ عن مشكلة") : "🐛  Report Issue");
    ui->abtCreditsTitle->setText(ar ? QString::fromUtf8("الشكر") : "CREDITS");
    ui->abtCreditsText->setText(ar ? QString::fromUtf8("صُنع بـ ❤️ لمجتمع لينكس. شكر خاص لفريق Sober ومشروع Qt.") : "Built with love for the Linux gaming community. Special thanks to the Sober team and the Qt Project.");


}

void MainWindow::syncConfigToUI_Load()
{
    QFile dbg("/tmp/sudostrap_debug.txt");
    dbg.open(QFile::WriteOnly);
    dbg.write("=== syncConfigToUI_Load called ===\n");

    // حاول profile أولاً، إذا ما فيه احمل من config
    bool loaded = m_config.loadProfile();
    if (!loaded) {
        loaded = m_config.load();
    }
    dbg.write(("load() result: " + QString(loaded ? "TRUE" : "FALSE") + "\n").toUtf8());

    if (!loaded) {
        dbg.write(("error: " + m_config.lastError() + "\n").toUtf8());
        dbg.close();
        resetDirty();
        return;
    }

    QString fpsCheck = m_config.getFlag("DFIntTaskSchedulerTargetFps");
    dbg.write(("FPS flag value: [" + fpsCheck + "]\n").toUtf8());
    dbg.close();

    auto setToggle = [](QAbstractButton *tg, bool on) {
        tg->blockSignals(true);
        if (auto *ts = qobject_cast<ToggleSwitch*>(tg)) {
            ts->setCheckedVisual(on);
        } else {
            tg->setChecked(on);
        }
        tg->blockSignals(false);
        tg->update();
    };

    auto setSpin = [](QSpinBox *sp, const QString &val) {
        if (val.isEmpty()) return;
        bool ok = false;
        int v = val.toInt(&ok);
        if (ok) {
            sp->blockSignals(true);
            sp->setValue(v);
            sp->blockSignals(false);
        }
    };

    auto setCombo = [](QComboBox *cb, int idx) {
        if (idx < 0 || idx >= cb->count()) return;
        cb->blockSignals(true);
        cb->setCurrentIndex(idx);
        cb->blockSignals(false);
    };

    QString fps = m_config.getFlag("DFIntTaskSchedulerTargetFps");
    bool hasFps = false;
    if (!fps.isEmpty()) {
        bool ok = false;
        int v = fps.toInt(&ok);
        if (ok && v > 0) {
            hasFps = true;
            setSpin(ui->targetFpsSpin2, fps);
            setSpin(ui->targetFpsSpin, fps);
        }
    }
    setToggle(ui->unlockFpsCheck, hasFps);

    QString csg = m_config.getFlag("DFIntCSGLevelOfDetailSwitchingDistance");
    if (!csg.isEmpty()) {
        bool ok = false;
        int v = csg.toInt(&ok);
        if (ok) {
            setSpin(ui->csgLodSpin, csg);
            setToggle(ui->shadowsCheck, v == 0);
        }
    }

    QString frm = m_config.getFlag("DFIntDebugFRMQualityLevelOverride");
    if (!frm.isEmpty()) {
        bool ok = false;
        int v = frm.toInt(&ok);
        if (ok) {
            setSpin(ui->frmQualitySpin, frm);
            setToggle(ui->postFxCheck, v == 1);
        }
    }

    QString tex = m_config.getFlag("DFIntTextureQualityOverride");
    if (!tex.isEmpty()) {
        bool ok = false;
        int v = tex.toInt(&ok);
        if (ok && v >= 0 && v <= 3) {
            setCombo(ui->texQualityCombo, v);
        }
    }

    QString grass = m_config.getFlag("FIntFRMMaxGrassDistance");
    if (grass == "0") {
        setCombo(ui->renderDistCombo, 0);
        setToggle(ui->grassCheck, true);
    } else if (grass == "500") {
        setCombo(ui->renderDistCombo, 1);
        setToggle(ui->grassCheck, false);
    } else if (grass == "1000") {
        setCombo(ui->renderDistCombo, 2);
        setToggle(ui->grassCheck, false);
    }

    QString aa = m_config.getFlag("FIntDebugForceMSAASamples");
    setToggle(ui->aaCheck, aa == "1");

    QString sky = m_config.getFlag("FFlagDebugSkyGray");
    setToggle(ui->skyGrayCheck, sky == "true");

    // ---- Ping Boost ----
    QString pingFlag = m_config.getFlag("DFIntSendMovementRateHz");
    setToggle(ui->pingBoostCheck, !pingFlag.isEmpty());

    resetDirty();
}

void MainWindow::onPresetsToggle(bool on)
{
    ui->presetsContainer->setVisible(on);
    markDirty();
}

void MainWindow::applyPreset(int presetId)
{
    if (presetId == 0) {
        if (auto *ts = qobject_cast<ToggleSwitch*>(ui->unlockFpsCheck)) ts->setCheckedVisual(true);
        ui->targetFpsSpin2->setValue(9999);
        ui->targetFpsSpin->setValue(9999);
        if (auto *ts = qobject_cast<ToggleSwitch*>(ui->shadowsCheck)) ts->setCheckedVisual(true);
        if (auto *ts = qobject_cast<ToggleSwitch*>(ui->postFxCheck)) ts->setCheckedVisual(true);
        if (auto *ts = qobject_cast<ToggleSwitch*>(ui->grassCheck)) ts->setCheckedVisual(true);
        if (auto *ts = qobject_cast<ToggleSwitch*>(ui->aaCheck)) ts->setCheckedVisual(true);
        ui->texQualityCombo->setCurrentIndex(0);
        ui->renderDistCombo->setCurrentIndex(0);
        ui->csgLodSpin->setValue(0);
        ui->frmQualitySpin->setValue(1);
    } else if (presetId == 1) {
        if (auto *ts = qobject_cast<ToggleSwitch*>(ui->unlockFpsCheck)) ts->setCheckedVisual(true);
        ui->targetFpsSpin2->setValue(240);
        ui->targetFpsSpin->setValue(240);
        if (auto *ts = qobject_cast<ToggleSwitch*>(ui->shadowsCheck)) ts->setCheckedVisual(false);
        if (auto *ts = qobject_cast<ToggleSwitch*>(ui->postFxCheck)) ts->setCheckedVisual(false);
        if (auto *ts = qobject_cast<ToggleSwitch*>(ui->grassCheck)) ts->setCheckedVisual(false);
        if (auto *ts = qobject_cast<ToggleSwitch*>(ui->aaCheck)) ts->setCheckedVisual(false);
        ui->texQualityCombo->setCurrentIndex(2);
        ui->renderDistCombo->setCurrentIndex(1);
        ui->csgLodSpin->setValue(500);
        ui->frmQualitySpin->setValue(10);
    } else if (presetId == 2) {
        if (auto *ts = qobject_cast<ToggleSwitch*>(ui->unlockFpsCheck)) ts->setCheckedVisual(true);
        ui->targetFpsSpin2->setValue(9999);
        ui->targetFpsSpin->setValue(9999);
        if (auto *ts = qobject_cast<ToggleSwitch*>(ui->shadowsCheck)) ts->setCheckedVisual(false);
        if (auto *ts = qobject_cast<ToggleSwitch*>(ui->postFxCheck)) ts->setCheckedVisual(false);
        if (auto *ts = qobject_cast<ToggleSwitch*>(ui->grassCheck)) ts->setCheckedVisual(false);
        if (auto *ts = qobject_cast<ToggleSwitch*>(ui->aaCheck)) ts->setCheckedVisual(false);
        ui->texQualityCombo->setCurrentIndex(3);
        ui->renderDistCombo->setCurrentIndex(2);
        ui->csgLodSpin->setValue(0);
        ui->frmQualitySpin->setValue(21);
    }

    // Custom flags per preset
    if (presetId == 1) {
        m_config.setFlag("FFlagDebugGraphicsDisableDirect3D11", "False");
        m_config.setFlag("FFlagDebugGraphicsPreferD3D11", "True");
        m_config.setFlag("DFIntGraphicsQualityOverride", "5");
        m_config.setFlag("DFIntGraphicsQualityLevels", "10");
        m_config.setFlag("DFIntTextureQualityOverride", "2");
        m_config.setFlag("FIntDebugForceMipLevels", "0");
        m_config.setFlag("FIntRenderShadowMapDetailResolution", "1024");
        m_config.setFlag("FIntRenderShadowIntensity", "50");
        m_config.setFlag("DFIntCSGLevelOfDetailSwitchDistance", "500");
        m_config.setFlag("FIntRenderFarClip", "15000");
        m_config.setFlag("DFIntMSAASamples", "0");
        m_config.setFlag("FFlagRenderBloom3", "False");
        m_config.setFlag("FFlagRenderSunRays", "False");
        m_config.setFlag("FFlagRenderSSAO2", "False");
        m_config.setFlag("FFlagRenderTerrainHDTextures", "False");
        m_config.removeFlag("FFlagRenderFixVolumetricShadowCascade");
        m_config.removeFlag("DFIntMinimalVisionDistantLodValue");
        m_config.removeFlag("FFlagRenderGlobalShadows");
        m_config.removeFlag("FIntRenderSSAOQuality");
    }

    if (presetId == 2) {
        m_config.setFlag("FFlagDebugGraphicsDisableDirect3D11", "False");
        m_config.setFlag("FFlagDebugGraphicsPreferD3D11", "True");
        m_config.setFlag("DFIntGraphicsQualityOverride", "10");
        m_config.setFlag("DFIntGraphicsQualityLevels", "10");
        m_config.setFlag("DFIntTextureQualityOverride", "3");
        m_config.setFlag("FIntDebugForceMipLevels", "0");
        m_config.setFlag("FIntRenderShadowMapDetailResolution", "2048");
        m_config.setFlag("FIntRenderShadowIntensity", "100");
        m_config.setFlag("FFlagRenderFixVolumetricShadowCascade", "True");
        m_config.setFlag("DFIntCSGLevelOfDetailSwitchDistance", "0");
        m_config.setFlag("DFIntMinimalVisionDistantLodValue", "0");
        m_config.setFlag("FIntRenderFarClip", "25000");
        m_config.setFlag("FFlagRenderGlobalShadows", "True");
        m_config.setFlag("DFIntMSAASamples", "2");
        m_config.setFlag("FFlagRenderBloom3", "True");
        m_config.setFlag("FFlagRenderSunRays", "True");
        m_config.setFlag("FFlagRenderSSAO2", "True");
        m_config.setFlag("FIntRenderSSAOQuality", "1");
        m_config.setFlag("FFlagRenderTerrainHDTextures", "True");
    }

    setActivePreset(presetId);
    markDirty();
    setStatus("Preset applied");
    QTimer::singleShot(2000, this, [this]() { setStatus("Ready"); });
}

void MainWindow::setActivePreset(int presetId)
{
    m_activePreset = presetId;

    auto setActive = [](QWidget *card, QPushButton *btn, bool active) {
        if (card) {
            card->setProperty("active", active ? "true" : "false");
            card->style()->unpolish(card);
            card->style()->polish(card);
            card->update();
        }
        if (btn) {
            btn->setProperty("active", active ? "true" : "false");
            btn->setEnabled(!active);
            btn->style()->unpolish(btn);
            btn->style()->polish(btn);
            btn->update();
        }
    };

    setActive(ui->presetCardPerf, ui->presetPerfApply, presetId == 0);
    setActive(ui->presetCardBal,  ui->presetBalApply,  presetId == 1);
    setActive(ui->presetCardQual, ui->presetQualApply, presetId == 2);
}

void MainWindow::showPresetDetails(int presetId)
{
    QString name, details;

    if (presetId == 0) {
        name = "Performance Preset";
        details =
            "DFIntTaskSchedulerTargetFps = 9999\n"
            "DFIntCSGLevelOfDetailSwitchingDistance = 0\n"
            "DFIntDebugFRMQualityLevelOverride = 1\n"
            "DFIntTextureQualityOverride = 0\n"
            "FIntFRMMaxGrassDistance = 0\n"
            "FIntDebugForceMSAASamples = 1";
    } else if (presetId == 1) {
        name = "Balanced Preset";
        details =
            "FFlagDebugGraphicsPreferD3D11 = True\\n"
            "DFIntGraphicsQualityOverride = 5\\n"
            "DFIntTextureQualityOverride = 2\\n"
            "FIntRenderShadowMapDetailResolution = 1024\\n"
            "FIntRenderShadowIntensity = 50\\n"
            "DFIntCSGLevelOfDetailSwitchDistance = 500\\n"
            "FIntRenderFarClip = 15000\\n"
            "DFIntMSAASamples = 0\\n"
            "DFIntTaskSchedulerTargetFps = 240";
    } else {
        name = "Quality Preset";
        details =
            "FFlagDebugGraphicsDisableDirect3D11 = False\\n"
            "FFlagDebugGraphicsPreferD3D11 = True\\n"
            "DFIntGraphicsQualityOverride = 10\\n"
            "DFIntGraphicsQualityLevels = 10\\n"
            "DFIntTextureQualityOverride = 3\\n"
            "FIntDebugForceMipLevels = 0\\n"
            "FIntRenderShadowMapDetailResolution = 2048\\n"
            "FIntRenderShadowIntensity = 100\\n"
            "FFlagRenderFixVolumetricShadowCascade = True\\n"
            "DFIntCSGLevelOfDetailSwitchDistance = 0\\n"
            "DFIntMinimalVisionDistantLodValue = 0\\n"
            "FIntRenderFarClip = 25000\\n"
            "FFlagRenderGlobalShadows = True\\n"
            "DFIntMSAASamples = 2\\n"
            "FFlagRenderBloom3 = True\\n"
            "FFlagRenderSunRays = True\\n"
            "FFlagRenderSSAO2 = True\\n"
            "FIntRenderSSAOQuality = 1\\n"
            "FFlagRenderTerrainHDTextures = True";
    }

    QMessageBox box(this);
    box.setWindowTitle(name);
    box.setText("<b>" + name + "</b><br><br>FastFlags that will be applied:");
    box.setInformativeText("<pre style='font-family: monospace;'>" + details + "</pre>");
    box.setIcon(QMessageBox::Information);
    box.exec();
}



