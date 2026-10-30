#ifndef WHATSNEWDIALOG_H
#define WHATSNEWDIALOG_H
#include <QDialog>
#include <QStringList>
class WhatsNewDialog : public QDialog {
    Q_OBJECT
public:
    explicit WhatsNewDialog(const QStringList &changes,
                            const QString &versionLabel,
                            QWidget *parent = nullptr);
};
#endif
