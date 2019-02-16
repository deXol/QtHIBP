#ifndef HAVEIBEENPWNED_H
#define HAVEIBEENPWNED_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>

class HaveIBeenPwned : public QObject
{
    Q_OBJECT
public:
    explicit HaveIBeenPwned(QObject *parent = nullptr);

    void isPasswordPwned(const QString &pwd);

signals:
    void sendPwnedResult(QString pwned);

public slots:
    void processReply(QNetworkReply *reply);

private:
    QNetworkAccessManager *man = nullptr;
    QNetworkRequest req;

    QString hash;

    const QString HIBP_API = "https://api.pwnedpasswords.com/range/";
};

#endif // HAVEIBEENPWNED_H