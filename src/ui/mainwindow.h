#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColor>
#include "core/configmanager.h"

class QPushButton;
class QPropertyAnimation;
class QGraphicsDropShadowEffect;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void showPerformancePage();
    void showGraphicsPage();
    void showFastFlagsPage();
    void showSettingsPage();
    void showAboutPage();
    void openCustomFFDialog();
    void onSaveClicked();
    void onCloseClicked();
    void onLaunchClicked();
    void onResetClicked();
    void markDirty();
    void onPresetsToggle(bool on);
    void applyPreset(int presetId);
    void showPresetDetails(int presetId);
    void onLanguageChanged(int index);
    void checkForUpdates();
    void onUpdateClicked();

private:
    void setStatus(const QString &text);
    void showProgress(int value);
    void hideProgress();
    void resetDirty();
    void installGlow(QPushButton *btn, const QColor &color, int maxBlur = 28);
    void applyLanguage(const QString &lang);
    void syncUIToConfig();
    void syncConfigToUI();
    void syncConfigToUI_Load();
    void refreshFlagsTable();
    void applySingleFlagToUI(const QString &key, const QString &value);
    void setActivePreset(int presetId);

    Ui::MainWindow *ui;
    bool m_dirty;
    bool m_autoUpdateEnabled;
    int m_activePreset;
    ConfigManager m_config;
    QString m_currentLang;
};

#endif
