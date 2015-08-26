#ifndef MOUSEFILTER_HPP
#define MOUSEFILTER_HPP

#include <QtGui>
#include <QDebug>

class MouseFilter : public QObject
{
    Q_OBJECT
public:
    explicit MouseFilter(QObject *parent = 0);

    bool eventFilter(QObject* object,QEvent* event)
    {
       if (event->type() == QEvent::KeyPress)
       {
           QKeyEvent *keyEvent = dynamic_cast<QKeyEvent *>(event);

       qDebug() << "You Pressed " << keyEvent->text() << "\n";
           return true;
       }
       else
       {
           // standard event processing
           return QObject::eventFilter(object, event);
       }
    };

signals:

public slots:
};

#endif // MOUSEFILTER_HPP
