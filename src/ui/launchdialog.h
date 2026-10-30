#ifndef LAUNCHDIALOG_H
#define LAUNCHDIALOG_H

#include <QDialog>
#include <QProcess>
#include <QPointer>
#include <QProcess>

class QProgressBar;
class QLabel;
class QPropertyAnimation;

class LaunchDialog : public QDialog
{
    Q_OBJECT
public:
    explicit LaunchDialog(QWidget *parent = nullptr, QPointer<QProcess> process = nullptr);
    ~LaunchDialog();

    void startLaunch();

signals:
    void launchFinished(bool success);

private slots:

private:
    QPointer<QProcess> m_process;
    void setStep(const QString &text, int value);
    void animateProgress(int targetValue);
    void finish(bool success);

    QProgressBar *progressBar;
    QLabel *statusLabel;
    QProcess *process;
    QPropertyAnimation *animation;
    int pendingProgress;
    bool launchStarted;
};

#endif
