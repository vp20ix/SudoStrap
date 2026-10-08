#ifndef UPDATEDIALOG_H
#define UPDATEDIALOG_H

#include <QDialog>

class QProgressBar;
class QLabel;
class QPropertyAnimation;
class QTimer;

class UpdateDialog : public QDialog
{
    Q_OBJECT
public:
    explicit UpdateDialog(const QString &newVersion, QWidget *parent = nullptr);
    void startUpdate();

signals:
    void updateFinished(bool success);

private:
    void setStep(const QString &text, int value);
    void animateProgress(int targetValue);
    void finish(bool success);

    QProgressBar *progressBar;
    QLabel *statusLabel;
    QLabel *iconLabel;
    QPropertyAnimation *animation;
    QTimer *timer;
    QString m_newVersion;
    int m_currentProgress;
    int m_targetProgress;
    int m_step;
};

#endif
