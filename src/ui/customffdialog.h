#ifndef CUSTOMFFDIALOG_H
#define CUSTOMFFDIALOG_H

#include <QDialog>
#include <QList>
#include <QString>

class QLineEdit;
class QTableWidget;

class CustomFFDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CustomFFDialog(QWidget *parent = nullptr);

private slots:
    void onSearchChanged(const QString &text);
    void onAddFlagClicked();
    void onAddFromFileClicked();
    void onAddFromJsonClicked();
    void onRemoveClicked();
    void onExportClicked();

private:
    struct FlagItem { QString name; QString value; QString category; };

    void addFlagRow(const QString &name, const QString &value, const QString &category);
    void refreshTable(const QString &filter = QString());
    bool flagExists(const QString &name);
    void importJsonObject(const QByteArray &data, const QString &source);

    QLineEdit *searchBox;
    QTableWidget *table;
    QList<FlagItem> flags;
};

#endif
