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
    /**
     * @brief sendPwnedNumber
     * @param num
     * Sending signal how many times the given password
     * has been compromised
     */
    void sendPwnedNumber(int num);
    /**
     * @brief sendSafePwd
     * Sending signal if the given password is safe
     */
    void sendSafePwd();

public slots:
    void processReply(QNetworkReply *reply);

private:
    QNetworkAccessManager *man = nullptr;
    QNetworkRequest req;

    QString hash;

    const QString HIBP_API = "https://api.pwnedpasswords.com/range/";
    const QString HASH_SEPARATOR = "\r\n";
    const int HIBP_REQUEST_SHA_LENGTH = 5;
};

#endif // HAVEIBEENPWNED_H
