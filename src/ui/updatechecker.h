#ifndef UPDATECHECKER_H
#define UPDATECHECKER_H

#include <QDialog>
#include <QProcess>

class QLabel;
class QProgressBar;
class QTextEdit;
class QPushButton;
class QWidget;

class UpdateChecker : public QDialog
{
    Q_OBJECT
public:
    explicit UpdateChecker(QWidget *parent = nullptr);
    bool updateApplied() const { return m_updateApplied; }

private:
    enum class Stage { Check = 0, Download = 1, Build = 2, Done = 3 };
    enum class State { Idle, Fetching, Pulling, Building, Done, Failed };

    QLabel *m_oldVer = nullptr;
    QLabel *m_newVer = nullptr;
    QLabel *m_status = nullptr;
    QProgressBar *m_progress = nullptr;
    QWidget *m_logContainer = nullptr;
    QTextEdit *m_log = nullptr;
    QPushButton *m_detailsBtn = nullptr;
    QPushButton *m_cancelBtn = nullptr;

    QLabel *m_stepCircle[4] = {};
    QLabel *m_stepLabel[4] = {};

    QProcess *m_proc = nullptr;
    State m_state = State::Idle;
    Stage m_stage = Stage::Check;
    bool m_updateApplied = false;
    bool m_logOpen = false;
    QString m_workDir;
    QString m_currentVersion;
    QString m_targetVersion;

    void setupUi();
    void setStage(Stage s);
    void setStageFailed(Stage s);
    void setStatus(const QString &msg, int progress = -1);
    void appendLog(const QString &t);
    void toggleLog();
    void runFetch();
    void afterFetch(int code);
    void runPull();
    void runBuild();
    void onProcFinished(int code);
    void fail(const QString &msg);

protected:
    void closeEvent(QCloseEvent *e) override;
};

#endif
