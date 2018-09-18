#ifndef USERINFO_H
#define USERINFO_H

#include "settings.h"

const QString kDefaultUserData = "defaultUser";
class UserInfo
{
public:
    const QString kDefaultAccount = "kDefaultAccount";
    const QString kAccount = "kAccount";
    const QString kMobi = "kMobi";
    const QString kRemainder = "kRemainder";
    const QString kTrip = "kTrip";
public:
    typedef enum ridingState
    {
        kRidingFinish,      // 骑行结束
        kRiding,            // 骑行中
    }ERidingState;
public:

    static QString getDefaultAccount();             // 获取缺省的用户账号，如果有缺省账号则用起进行登录
    static int setDefaultAccount(QString account);  // 设置账号为缺省账号
    static int removeDefaultAccount();              // 删除缺省账号
    static int requestLogin(QString account, QString verifyCode);       // 请求登录账号
    static int defaultLogin();
    static int requestLogOff(QString account);      // 请求退出账号
    static UserInfo *getCurUserInfo();
    QString account() const;
    void setAccount(const QString &account);

    int mobi() const;
    void setMobi(int mobi);

    float remainder() const;
    void setRemainder(float remainder);

    float trip();
    void setTrip(float trip);

    void setRidingState(const ERidingState &ridingState);
    void sync();
    void flushAll();
private:
    UserInfo(QString  &account);
    QString account_;       // 账号
    int mobi_;              // 摩币
    float remainder_;       // 余额
    float trip_;            // 骑行里程
    ERidingState ridingState_;  // 骑行状态
    Settings *userData_;         // 个人信息的设置
    static UserInfo *sCurUserInfo;  // 当前账号
public:
    static Settings *defaultUserData_;  //
};

#endif // USERINFO_H
