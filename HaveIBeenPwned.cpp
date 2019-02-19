#include "HaveIBeenPwned.h"

#include <QNetworkReply>
#include <QCryptographicHash>

HaveIBeenPwned::HaveIBeenPwned(QObject *parent) :
    QObject(parent),
    man(new QNetworkAccessManager(this))
{
    QObject::connect(man, &QNetworkAccessManager::finished, this, &HaveIBeenPwned::processReply);
}

/**
 * @brief HaveIBeenPwned::isPasswordPwned
 * @param pwd Given password to check
 * Calculating the SHA1 hash of the password
 * and sending the first five char to HIBP v2 API.
 */
void HaveIBeenPwned::isPasswordPwned(const QString &pwd)
{
    QCryptographicHash sha1Hasher(QCryptographicHash::Sha1);
    sha1Hasher.addData(pwd.toUtf8());
    hash = sha1Hasher.result().toHex().toUpper();
    req.setUrl(QUrl(HIBP_API + hash.left(HIBP_REQUEST_SHA_LENGTH)));
    hash = hash.mid(HIBP_REQUEST_SHA_LENGTH);
    man->get(req);
}

/**
 * @brief HaveIBeenPwned::processReply
 * @param reply HIBP password check request reply
 * Processing the answer of the password HIBP request.
 */
void HaveIBeenPwned::processReply(QNetworkReply *reply)
{
    if (reply->error()) {
        qDebug() << reply->errorString();
        return;
    }

    QString answer = reply->readAll();

    if (answer.contains(hash))
    {
        QString fromPwned = answer.mid(answer.indexOf(hash));
        QString pwned = fromPwned.left(fromPwned.indexOf(HASH_SEPARATOR));
        QString pwnedNum = pwned.mid(pwned.indexOf(':') + 1);
        emit sendPwnedNumber(pwnedNum.toInt());
    }
    else
    {
        emit sendSafePwd();
    }
}
