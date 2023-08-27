#ifndef SWITCHBUTTON_HPP
#define SWITCHBUTTON_HPP

#include <QPushButton>
#include <QMouseEvent>

class SwitchButton : public QPushButton
{
    Q_OBJECT
    Q_DISABLE_COPY(SwitchButton)

    Q_PROPERTY(bool value READ enabled WRITE setEnabled)
    Q_PROPERTY(bool value READ value WRITE setValue NOTIFY valueChanged)

public:
    explicit SwitchButton(QWidget* parent = nullptr): QPushButton(parent)
      , m_enabled(true)
      , m_value(false)
    {
        this->setFlat(true);

        /**
         * @note setDefault property is used to get enter key on button.
         */
        this->setDefault(true);

        changeIcon();
        resize(parent->width(), parent->height());
    }

    ~SwitchButton() override {}

    void setEnabled(bool value)
    {
        m_enabled = value;
    }

    bool enabled() const
    {
        return m_enabled;
    }

    void setValue(bool value)
    {
        if (m_value != value && m_enabled)
        {
            m_value = value;
            changeIcon(m_value);
            emit valueChanged(value);
        }
    }

    bool value() const
    {
        return m_value;
    }

    void resize(int w, int h)
    {
        if (m_width != w || m_height != h)
        {
            this->setIconSize(QSize(w, h));

            m_width = w;
            m_height = h;
        }
    }

private:
    bool m_enabled;
    bool m_value;
    int  m_width    = 0;
    int  m_height   = 0;

signals:
    void valueChanged(bool);
    void mousePress(QMouseEvent *e);
    void mouseRelease(QMouseEvent *e);
    void mouseMove(QMouseEvent *e);
    void mouseDblClick(QMouseEvent *e);
    void keyPress(QKeyEvent *e);

private slots:
    /**
     * @brief changeIcon
     * @param isOn
     */
    void changeIcon(bool isOn = false)
    {
        QPixmap pixmap(":/images/Switch_On.png");
        if (!isOn)
            pixmap.load(":/images/Switch_Off.png");

        QIcon icon(pixmap);
        this->setIcon(icon);
    }

protected:
    /**
     * @brief mousePressEvent
     * @param e
     */
    void mousePressEvent(QMouseEvent *e) override
    {
        if ((e->x() < this->width() / 2 && m_value) || (e->x() > this->width() / 2 && !m_value))
            setValue(!m_value);

        emit mousePress(e);
    }

    /**
     * @brief mouseReleaseEvent
     * @param e
     */
    void mouseReleaseEvent(QMouseEvent *e) override
    {
        emit mouseRelease(e);
    }

    /**
     * @brief mouseMoveEvent
     * @param e
     */
    void mouseMoveEvent(QMouseEvent *e) override
    {
        if ((e->x() < this->width() / 2 && m_value) || (e->x() > this->width() / 2 && !m_value))
            setValue(!m_value);

        emit mouseMove(e);
    }

    /**
     * @brief mouseDoubleClickEvent
     * @param e
     */
    void mouseDoubleClickEvent(QMouseEvent *e) override
    {
        emit mouseDblClick(e);
    }

    /**
     * @brief keyPressEvent
     * @param e
     */
    void keyPressEvent(QKeyEvent *e) override
    {
        if (e->key() == Qt::Key_Enter)
            setValue(!m_value);

        emit keyPress(e);
    }
};

#endif // SWITCHBUTTON_HPP
