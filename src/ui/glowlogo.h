#ifndef GLOWLOGO_H
#define GLOWLOGO_H

#include <QLabel>
#include <QTimer>

class GlowLogo : public QLabel
{
    Q_OBJECT
    Q_PROPERTY(qreal glowOpacity READ glowOpacity WRITE setGlowOpacity)

public:
    explicit GlowLogo(QWidget *parent = nullptr);
    void setLogo(const QPixmap &pixmap);

    qreal glowOpacity() const { return m_glowOpacity; }
    void setGlowOpacity(qreal v);

protected:
    void paintEvent(QPaintEvent *) override;

private:
    QPixmap m_logo;
    qreal m_glowOpacity;
};

#endif
