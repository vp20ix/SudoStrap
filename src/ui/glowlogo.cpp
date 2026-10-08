#include "ui/glowlogo.h"
#include <QPainter>
#include <QLinearGradient>
#include <QPainterPath>

GlowLogo::GlowLogo(QWidget *parent)
    : QLabel(parent), m_glowOpacity(1.0)
{
    setAttribute(Qt::WA_TransparentForMouseEvents);
}

void GlowLogo::setLogo(const QPixmap &pixmap)
{
    m_logo = pixmap;
    update();
}

void GlowLogo::setGlowOpacity(qreal v)
{
    m_glowOpacity = v;
    update();
}

void GlowLogo::paintEvent(QPaintEvent *)
{
    if (m_logo.isNull()) return;

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.setRenderHint(QPainter::SmoothPixmapTransform);

    const int w = width();
    const int h = height();
    const qreal radius = 10.0;

    // ============ 1. توهج خفيف جداً (فقط 8px حول الشعار) ============
    const qreal glowPad = 6.0;
    QRectF glowRect(glowPad, glowPad, w - 2 * glowPad, h - 2 * glowPad);

    for (int i = 4; i >= 1; --i) {
        const qreal spread = i * 1.5;
        const qreal alpha = 0.08 * (5 - i);

        QLinearGradient grad(glowRect.topLeft(), glowRect.bottomLeft());
        grad.setColorAt(0.0, QColor(34, 211, 238, static_cast<int>(alpha * 255)));
        grad.setColorAt(1.0, QColor(139, 92, 246, static_cast<int>(alpha * 255)));

        p.setPen(QPen(QBrush(grad), spread * 2.0,
                      Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        p.setBrush(Qt::NoBrush);
        p.drawRoundedRect(glowRect, radius, radius);
    }

    // ============ 2. الإطار الملاصق للشعار ============
    // الشعار يملأ معظم المساحة، والإطار يحيط به مباشرة
    const qreal framePad = 4.0;
    QRectF frame(framePad, framePad, w - 2 * framePad, h - 2 * framePad);

    QLinearGradient borderGrad(frame.topLeft(), frame.bottomLeft());
    borderGrad.setColorAt(0.0, QColor(34, 211, 238));
    borderGrad.setColorAt(1.0, QColor(139, 92, 246));

    p.setPen(QPen(QBrush(borderGrad), 1.5));
    p.setBrush(Qt::NoBrush);
    p.drawRoundedRect(frame, radius, radius);

    // ============ 3. الشعار يملأ الإطار ============
    QPixmap scaled = m_logo.scaled(frame.size().toSize(),
                                    Qt::KeepAspectRatioByExpanding,
                                    Qt::SmoothTransformation);

    // اقتصاص مركزي عشان يملأ الإطار
    const int sx = (scaled.width() - frame.width()) / 2;
    const int sy = (scaled.height() - frame.height()) / 2;
    QPixmap cropped = scaled.copy(sx, sy, frame.width(), frame.height());

    // ارسم داخل الإطار
    QPainterPath clip;
    clip.addRoundedRect(frame, radius, radius);
    p.setClipPath(clip);
    p.drawPixmap(frame.topLeft().toPoint(), cropped);
    p.setClipping(false);
}
