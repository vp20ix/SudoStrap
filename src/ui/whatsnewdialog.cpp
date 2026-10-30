#include "ui/whatsnewdialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
WhatsNewDialog::WhatsNewDialog(const QStringList &changes,
                               const QString &versionLabel,
                               QWidget *parent) : QDialog(parent) {
    setWindowTitle("What's New in SudoStrap");
    setMinimumSize(520, 380);
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(24, 24, 24, 24);
    layout->setSpacing(12);
    auto *title = new QLabel("🎉  " + versionLabel);
    title->setStyleSheet("font-size: 18px; font-weight: bold;");
    layout->addWidget(title);
    auto *sub = new QLabel("Here's what changed since you last used SudoStrap:");
    sub->setStyleSheet("color: #888;");
    layout->addWidget(sub);
    auto *view = new QTextEdit;
    view->setReadOnly(true);
    QString html;
    for (const QString &line : changes) {
        html += "<p style='margin:6px 0;'>• " + line.toHtmlEscaped() + "</p>";
    }
    if (changes.isEmpty()) html = "<p style='color:#888;'>No detailed changes.</p>";
    view->setHtml(html);
    layout->addWidget(view, 1);
    auto *btn = new QPushButton("Got it");
    btn->setProperty("primary", true);
    connect(btn, &QPushButton::clicked, this, &QDialog::accept);
    layout->addWidget(btn, 0, Qt::AlignRight);
}
