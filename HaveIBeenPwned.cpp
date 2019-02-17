#include "HaveIBeenPwned.h"

#include <QNetworkReply>
#include <QCryptographicHash>

HaveIBeenPwned::HaveIBeenPwned(QObject *parent) :
    QObject(parent),
    man(new QNetworkAccessManager(this))
{
    QObject::connect(man, &QNetworkAccessManager::finished, this, &HaveIBeenPwned::processReply);
}

void HaveIBeenPwned::isPasswordPwned(const QString &pwd)
{
    QCryptographicHash sha1Hasher(QCryptographicHash::Sha1);
    sha1Hasher.addData(pwd.toStdString().c_str());
    hash = sha1Hasher.result().toHex().toUpper();
    req.setUrl(QUrl(HIBP_API + hash.left(HIBP_REQUEST_SHA_LENGTH)));
    man->get(req);
}

void HaveIBeenPwned::processReply(QNetworkReply *reply)
{
    if (reply->error()) {
        qDebug() << reply->errorString();
        return;
    }

    QString answer = reply->readAll();

    if (answer.contains(hash.mid(HIBP_REQUEST_SHA_LENGTH)))
    {
        QString fromPwned = answer.mid(answer.indexOf(hash.mid(HIBP_REQUEST_SHA_LENGTH)));
        QString pwned = fromPwned.left(fromPwned.indexOf("\r\n"));
        QString pwnedNum = pwned.mid(pwned.indexOf(':') + 1);
        emit sendPwnedNumber(pwnedNum.toInt());
    }
    else
    {
        emit sendSafePwd();
    }
}
