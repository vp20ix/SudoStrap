#ifndef TOGGLESWITCH_H
#define TOGGLESWITCH_H

#include <QAbstractButton>
#include <QPropertyAnimation>

class ToggleSwitch : public QAbstractButton
{
    Q_OBJECT
    Q_PROPERTY(qreal knobPos READ knobPos WRITE setKnobPos)

public:
    explicit ToggleSwitch(QWidget *parent = nullptr);
    QSize sizeHint() const override;

    qreal knobPos() const { return m_knobPos; }
    void setKnobPos(qreal p);

    // Public method to set checked AND update visual + knob position
    void setCheckedVisual(bool checked);

protected:
    void paintEvent(QPaintEvent *) override;

private:
    qreal m_knobPos;
    QPropertyAnimation *m_anim;
};

#endif
