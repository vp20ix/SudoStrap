#include "ui/toggleswitch.h"
#include <QPainter>
#include <QPainterPath>
#include <QLinearGradient>

ToggleSwitch::ToggleSwitch(QWidget *parent)
    : QAbstractButton(parent), m_knobPos(0.0)
{
    setCheckable(true);
    setFixedSize(50, 30);
    setCursor(Qt::PointingHandCursor);

    m_anim = new QPropertyAnimation(this, "knobPos", this);
    m_anim->setDuration(200);
    m_anim->setEasingCurve(QEasingCurve::OutCubic);

    connect(this, &QAbstractButton::toggled, this, [this](bool on) {
        m_anim->stop();
        m_anim->setStartValue(m_knobPos);
        m_anim->setEndValue(on ? 1.0 : 0.0);
        m_anim->start();
    });
}

QSize ToggleSwitch::sizeHint() const { return QSize(50, 30); }

void ToggleSwitch::setKnobPos(qreal p) { m_knobPos = p; update(); }

void ToggleSwitch::setCheckedVisual(bool checked)
{
    m_anim->stop();
    QAbstractButton::setChecked(checked);
    m_knobPos = checked ? 1.0 : 0.0;
    update();
}

void ToggleSwitch::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    const int w = width();
    const int h = height();
    const qreal r = h / 2.0;

    QPainterPath track;
    track.addRoundedRect(QRectF(0.5, 0.5, w - 1.0, h - 1.0), r, r);

    if (isChecked()) {
        QLinearGradient grad(0, 0, w, h);
        grad.setColorAt(0.0, QColor(34, 211, 238));
        grad.setColorAt(1.0, QColor(0, 120, 212));
        p.fillPath(track, grad);
    } else {
        p.fillPath(track, QColor(30, 30, 46));
        p.setPen(QPen(QColor(58, 58, 78), 1.5));
        p.drawPath(track);
    }

    const qreal knobD = h - 8.0;
    const qreal knobMin = 4.0;
    const qreal knobMax = w - knobD - 4.0;
    const qreal knobX = knobMin + m_knobPos * (knobMax - knobMin);
    const qreal knobY = (h - knobD) / 2.0;

    if (isChecked()) {
        p.setPen(Qt::NoPen);
        p.setBrush(QColor(0, 0, 0, 40));
        p.drawEllipse(QRectF(knobX + 1, knobY + 2, knobD, knobD));
    }

    p.setPen(Qt::NoPen);
    p.setBrush(isChecked() ? QColor(255, 255, 255) : QColor(138, 138, 158));
    p.drawEllipse(QRectF(knobX, knobY, knobD, knobD));
}
