#ifndef LAUNCHDIALOG_H
#define LAUNCHDIALOG_H

#include <QDialog>
#include <QProcess>

class QProgressBar;
class QLabel;
class QPropertyAnimation;

class LaunchDialog : public QDialog
{
    Q_OBJECT
public:
    explicit LaunchDialog(QWidget *parent = nullptr);
    ~LaunchDialog();

    void startLaunch();

signals:
    void launchFinished(bool success);

private slots:

private:
    void setStep(const QString &text, int value);
    void animateProgress(int targetValue);
    void finish(bool success);

    QProgressBar *progressBar;
    QLabel *statusLabel;
    QLabel *iconLabel;
    QProcess *process;
    QPropertyAnimation *animation;
    int pendingProgress;
    bool launchStarted;
};

#endif
