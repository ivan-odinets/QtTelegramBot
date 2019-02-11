#ifndef NETWORKING_H
#define NETWORKING_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>

#define API_HOST "api.telegram.org"

#define ENDPOINT_GET_ME                     "/getMe"
#define ENDPOINT_GET_CHAT                   "/getChat"
#define ENDPOINT_GET_CHAT_MEMBER            "/getChatMember"
#define ENDPOINT_SEND_MESSAGE               "/sendMessage"
#define ENDPOINT_DELETE_MESSAGE             "/deleteMessage"
#define ENDPOINT_FORWARD_MESSAGE            "/forwardMessage"
#define ENDPOINT_SEND_PHOTO                 "/sendPhoto"
#define ENDPOINT_SEND_AUDIO                 "/sendAudio"
#define ENDPOINT_SEND_DOCUMENT              "/sendDocument"
#define ENDPOINT_SEND_STICKER               "/sendSticker"
#define ENDPOINT_SEND_VIDEO                 "/sendVideo"
#define ENDPOINT_SEND_VOICE                 "/sendVoice"
#define ENDPOINT_SEND_LOCATION              "/sendLocation"
#define ENDPOINT_SEND_CHAT_ACTION           "/sendChatAction"
#define ENDPOINT_KICK_CHAT_MEMBER           "/kickChatMember"
#define ENDPOINT_UNBAN_CHAT_MEMBER          "/unbanChatMember"
#define ENDPOINT_RESTRICT_CHAT_MEMBER       "/restrictChatMember"
#define ENDPOINT_ANSWER_CALLBACK_QUERY      "/answerCallbackQuery"
#define ENDPOINT_GET_USER_PROFILE_PHOTOS    "/getUserProfilePhotos"
#define ENDPOINT_GET_UPDATES                "/getUpdates"
#define ENDPOINT_SET_WEBHOOK                "/setWebhook"
#define ENDPOINT_GET_FILE                   "/getFile"

namespace Telegram {

class HttpParameter {
public:
    HttpParameter() {}
    HttpParameter(const QVariant& value, bool isFile = false, const QString& mimeType = "text/plain", const QString& filename = QString()) :
        value(value.toByteArray()), isFile(isFile), mimeType(mimeType), filename(filename) {}

    QByteArray value;
    bool isFile;
    QString mimeType;
    QString filename;
};

typedef QMap<QString, HttpParameter> ParameterList;

class Networking : public QObject
{
    Q_OBJECT
public:
    Networking(QString token, QObject *parent = 0);
    ~Networking();

    enum Method { GET, POST, UPLOAD };

    QByteArray request(const QString& endpoint, const ParameterList& params, Method method);

private:
    QNetworkAccessManager *m_nam;
    QString m_token;

    QUrl buildUrl(const QString& endpoint);
    QByteArray parameterListToString(const ParameterList& list);

    QByteArray generateMultipartBoundary(ParameterList list);
    QByteArray generateMultipartFormData(ParameterList list, QByteArray boundary);
    QString generateRandomString(int length);
};

}

#endif // NETWORKING_H
