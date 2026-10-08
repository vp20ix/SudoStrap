#include "ui/customffdialog.h"
#include <QDateTime>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>
#include <QInputDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QFile>
#include <algorithm>

CustomFFDialog::CustomFFDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Custom FastFlags");
    resize(760, 560);
    setStyleSheet(R"(
        QDialog { background-color: #1e1e1e; }
        QLabel { color: #e0e0e0; background: transparent; border: none; }
        QLineEdit { background-color: #2d2d30; border: 1px solid #3e3e42; border-radius: 6px; padding: 10px 14px; color: #e0e0e0; font-size: 13px; }
        QLineEdit:focus { border: 1px solid #0078d4; }
        QTableWidget { background-color: #2d2d30; alternate-background-color: #282828; border: 1px solid #3e3e42; border-radius: 8px; color: #e0e0e0; gridline-color: transparent; font-size: 13px; }
        QTableWidget::item { padding: 8px 12px; border-bottom: 1px solid #3e3e42; }
        QTableWidget::item:selected { background-color: #0078d4; }
        QHeaderView::section { background-color: #252526; color: #999999; padding: 10px 12px; border: none; border-bottom: 1px solid #3e3e42; font-weight: bold; font-size: 12px; }
        QPushButton { background-color: #3e3e42; color: #e0e0e0; border: 1px solid #555555; padding: 9px 16px; border-radius: 6px; font-size: 13px; }
        QPushButton:hover { background-color: #4e4e52; }
        QPushButton[primary="true"] { background-color: #0078d4; color: #ffffff; border: none; font-weight: bold; }
        QPushButton[primary="true"]:hover { background-color: #1084d8; }
        QPushButton[danger="true"] { background-color: #3e3e42; color: #ff6b6b; border: 1px solid #555555; }
        QPushButton[danger="true"]:hover { background-color: #4e2020; color: #ffffff; border-color: #ff6b6b; }
    )");

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(12);

    auto *title = new QLabel("Custom FastFlags");
    title->setStyleSheet("font-size: 20px; font-weight: bold; color: #ffffff;");
    auto *subtitle = new QLabel("Add flags manually, import from a file, or paste JSON");
    subtitle->setStyleSheet("font-size: 12px; color: #999999;");
    mainLayout->addWidget(title);
    mainLayout->addWidget(subtitle);

    searchBox = new QLineEdit;
    searchBox->setPlaceholderText("Search flags by name...");
    searchBox->setClearButtonEnabled(true);
    mainLayout->addWidget(searchBox);

    auto *actionLayout = new QHBoxLayout;
    actionLayout->setSpacing(8);
    auto *addBtn = new QPushButton("+  Add Flag");
    addBtn->setProperty("primary", true);
    auto *fileBtn = new QPushButton("Import File");
    auto *jsonBtn = new QPushButton("Paste JSON");
    auto *exportBtn = new QPushButton("Export All");
    auto *removeBtn = new QPushButton("Remove Selected");
    removeBtn->setProperty("danger", true);
    actionLayout->addWidget(addBtn);
    actionLayout->addWidget(fileBtn);
    actionLayout->addWidget(jsonBtn);
    actionLayout->addWidget(exportBtn);
    actionLayout->addStretch();
    actionLayout->addWidget(removeBtn);
    mainLayout->addLayout(actionLayout);

    table = new QTableWidget;
    table->setColumnCount(3);
    table->setHorizontalHeaderLabels({"Flag Name", "Value", "Source"});
    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setAlternatingRowColors(true);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->verticalHeader()->setVisible(false);
    mainLayout->addWidget(table);

    auto *bottomLayout = new QHBoxLayout;
    bottomLayout->addStretch();
    auto *closeBtn = new QPushButton("Close");
    closeBtn->setProperty("primary", true);
    bottomLayout->addWidget(closeBtn);
    mainLayout->addLayout(bottomLayout);

    connect(searchBox, &QLineEdit::textChanged, this, &CustomFFDialog::onSearchChanged);
    connect(addBtn, &QPushButton::clicked, this, &CustomFFDialog::onAddFlagClicked);
    connect(fileBtn, &QPushButton::clicked, this, &CustomFFDialog::onAddFromFileClicked);
    connect(jsonBtn, &QPushButton::clicked, this, &CustomFFDialog::onAddFromJsonClicked);
    connect(removeBtn, &QPushButton::clicked, this, &CustomFFDialog::onRemoveClicked);
    connect(exportBtn, &QPushButton::clicked, this, &CustomFFDialog::onExportClicked);
    connect(closeBtn, &QPushButton::clicked, this, &QDialog::accept);

    addFlagRow("DFIntTaskSchedulerTargetFps", "240", "Example");
    addFlagRow("DFIntCSGLevelOfDetailSwitchingDistance", "0", "Example");
    addFlagRow("FIntFRMMaxGrassDistance", "0", "Example");
}

void CustomFFDialog::onSearchChanged(const QString &t) { refreshTable(t); }

void CustomFFDialog::onAddFlagClicked()
{
    bool ok = false;
    QString name = QInputDialog::getText(this, "Add Flag", "Flag name:", QLineEdit::Normal, QString(), &ok);
    if (!ok || name.isEmpty()) return;
    if (flagExists(name)) { QMessageBox::warning(this, "Duplicate", "Already in the list."); return; }
    QString value = QInputDialog::getText(this, "Add Flag", "Value:", QLineEdit::Normal, QString(), &ok);
    if (!ok) return;
    addFlagRow(name, value, "Manual");
}

void CustomFFDialog::onAddFromFileClicked()
{
    QString path = QFileDialog::getOpenFileName(this, "Open JSON File", QString(), "JSON Files (*.json);;All Files (*)");
    if (path.isEmpty()) return;
    QFile f(path);
    if (!f.open(QFile::ReadOnly)) { QMessageBox::warning(this, "Error", "Could not open file."); return; }
    importJsonObject(f.readAll(), "File");
}

void CustomFFDialog::onAddFromJsonClicked()
{
    bool ok = false;
    QString json = QInputDialog::getMultiLineText(this, "Paste JSON", "Paste a JSON object:", QString(), &ok);
    if (!ok || json.isEmpty()) return;
    importJsonObject(json.toUtf8(), "Pasted");
}

void CustomFFDialog::onRemoveClicked()
{
    auto rows = table->selectionModel()->selectedRows();
    if (rows.isEmpty()) return;
    QList<int> indices;
    for (const auto &idx : rows) indices.append(idx.row());
    std::sort(indices.begin(), indices.end(), std::greater<int>());
    for (int row : indices) {
        QString name = table->item(row, 0) ? table->item(row, 0)->text() : QString();
        for (int i = 0; i < flags.size(); ++i) if (flags[i].name == name) { flags.removeAt(i); break; }
        table->removeRow(row);
    }
}

void CustomFFDialog::importJsonObject(const QByteArray &data, const QString &source)
{
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(data, &err);
    if (err.error != QJsonParseError::NoError || !doc.isObject()) {
        QMessageBox::warning(this, "Invalid JSON", "Could not parse JSON:\n" + err.errorString());
        return;
    }
    QJsonObject obj = doc.object();
    int added = 0;
    for (auto it = obj.begin(); it != obj.end(); ++it) {
        if (flagExists(it.key())) continue;
        QString val;
        if (it.value().isString()) val = it.value().toString();
        else if (it.value().isBool()) val = it.value().toBool() ? "true" : "false";
        else if (it.value().isDouble()) val = QString::number(it.value().toDouble());
        else val = "?";
        addFlagRow(it.key(), val, source);
        added++;
    }
    if (added == 0) QMessageBox::information(this, "Nothing Added", "No new flags were added.");
}

void CustomFFDialog::addFlagRow(const QString &name, const QString &value, const QString &category)
{
    flags.append({name, value, category});
    int row = table->rowCount();
    table->insertRow(row);
    table->setItem(row, 0, new QTableWidgetItem(name));
    table->setItem(row, 1, new QTableWidgetItem(value));
    table->setItem(row, 2, new QTableWidgetItem(category));
}

void CustomFFDialog::refreshTable(const QString &filter)
{
    table->setRowCount(0);
    for (const auto &f : flags) {
        if (filter.isEmpty() || f.name.contains(filter, Qt::CaseInsensitive)) {
            int row = table->rowCount();
            table->insertRow(row);
            table->setItem(row, 0, new QTableWidgetItem(f.name));
            table->setItem(row, 1, new QTableWidgetItem(f.value));
            table->setItem(row, 2, new QTableWidgetItem(f.category));
        }
    }
}

bool CustomFFDialog::flagExists(const QString &name)
{
    for (const auto &f : flags) if (f.name == name) return true;
    return false;
}

void CustomFFDialog::onExportClicked()
{
    if (flags.isEmpty()) {
        QMessageBox::information(this, "Nothing to Export",
            "The flag list is empty. Add some flags first.");
        return;
    }

    QString defaultName = "sudostrap_flags_" +
        QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss") + ".json";

    QString path = QFileDialog::getSaveFileName(
        this,
        "Export Flags",
        QDir::homePath() + "/" + defaultName,
        "JSON Files (*.json)"
    );

    if (path.isEmpty()) return;
    if (!path.endsWith(".json")) path += ".json";

    // Build JSON preserving types
    QJsonObject fflags;
    for (const auto &f : flags) {
        const QString &v = f.value;
        if (v == "true" || v == "false") {
            fflags[f.name] = (v == "true");
        } else {
            bool ok = false;
            double num = v.toDouble(&ok);
            if (ok && !v.contains('.') && !v.contains('e')) {
                fflags[f.name] = static_cast<int>(num);
            } else if (ok) {
                fflags[f.name] = num;
            } else {
                fflags[f.name] = v;
            }
        }
    }

    QJsonObject root;
    root["_exported_by"] = "SudoStrap";
    root["_date"] = QDateTime::currentDateTime().toString(Qt::ISODate);
    root["fflags"] = fflags;

    QFile f(path);
    if (!f.open(QFile::WriteOnly)) {
        QMessageBox::warning(this, "Export Failed",
            "Could not write file:\n" + path);
        return;
    }
    f.write(QJsonDocument(root).toJson(QJsonDocument::Indented));
    f.close();

    QMessageBox::information(this, "Export Complete",
        "Exported " + QString::number(flags.size()) + " flag(s) to:\n" + path);
}

void CustomFFDialog::setInitialFlags(const QMap<QString, QString> &initFlags)
{
    flags.clear();
    table->setRowCount(0);
    
    for (auto it = initFlags.begin(); it != initFlags.end(); ++it) {
        addFlagRow(it.key(), it.value(), "Config");
    }
}

QMap<QString, QString> CustomFFDialog::currentFlags() const
{
    QMap<QString, QString> result;
    for (const auto &f : flags) {
        result[f.name] = f.value;
    }
    return result;
}
