#ifndef RECAPTCHABRIDGE_H
#define RECAPTCHABRIDGE_H

#include <QObject>

class RecaptchaBridge : public QObject
{
    Q_OBJECT
public:
    explicit RecaptchaBridge(QObject *parent = nullptr) : QObject(parent) {}

public slots:
    void callQt(QString token) {
        emit tokenReceived(token);
    }

signals:
    void tokenReceived(QString token);
};

#endif // RECAPTCHABRIDGE_H

