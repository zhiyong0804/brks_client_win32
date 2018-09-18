#include <QDebug>
#include "userinfo.h"
Settings *UserInfo::defaultUserData_ = nullptr;
UserInfo *UserInfo::sCurUserInfo  = nullptr;
UserInfo::UserInfo(QString &account):
    account_(account)
{
    userData_ = new Settings(account_);

    // 只有将数据写入才会生成.ini文件
    userData_->set(kAccount, account_);
    qDebug() << __FUNCTION__ << " account: " << account_;
    mobi_ = userData_->getInt(kMobi, 0);
    remainder_ = userData_->getDouble(kRemainder, 0.0);
    trip_ = userData_->getDouble(kTrip, 0.0);

    userData_->flush();
}

QString UserInfo::getDefaultAccount()
{
    QString account;
    if(!defaultUserData_)
    {
        // 初始化
        defaultUserData_ = new Settings(kDefaultUserData);
    }
    if(defaultUserData_->contains("kDefaultAccount"))
    {
        account = defaultUserData_->getString("kDefaultAccount","");
    }
    return account;
}

int UserInfo::setDefaultAccount(QString account)
{
    if(!defaultUserData_)
    {
        // 初始化
        defaultUserData_ = new Settings("kDefaultUserData");
    }
    defaultUserData_->set("kDefaultAccount", account);
    defaultUserData_->flush();
    return 0;
}

int UserInfo::removeDefaultAccount()
{
    if(!defaultUserData_)
    {
        // 初始化
        defaultUserData_ = new Settings("kDefaultUserData");
    }
    defaultUserData_->remove("kDefaultAccount");
    defaultUserData_->flush();
    return 0;
}

int UserInfo::requestLogin(QString account, QString verifyCode)
{
    if(sCurUserInfo)                // 如果已经有账号在登录则先退出
    {
        sCurUserInfo->flushAll();
        delete sCurUserInfo;
        sCurUserInfo = nullptr;
    }
    sCurUserInfo = new UserInfo(account);
    setDefaultAccount(account);
    return 0;
}

int UserInfo::defaultLogin()
{
    QString account = getDefaultAccount();
    if(!account.isEmpty())
    {
        if(sCurUserInfo)                // 如果已经有账号在登录则先退出
        {
            sCurUserInfo->flushAll();
            delete sCurUserInfo;
            sCurUserInfo = nullptr;
        }
        sCurUserInfo = new UserInfo(account);
        return 0;
    }
    else
    {
        return -1;
    }
}

int UserInfo::requestLogOff(QString account)
{
    if(sCurUserInfo)                // 如果已经有账号在登录则先退出
    {
        sCurUserInfo->flushAll();
        delete sCurUserInfo;
        sCurUserInfo = nullptr;
    }
    removeDefaultAccount();          // 删除默认账号
    return 0;
}

UserInfo *UserInfo::getCurUserInfo()
{
    return sCurUserInfo;
}

QString UserInfo::account() const
{
    return account_;
}

void UserInfo::setAccount(const QString &account)
{
    account_ = account;
}

int UserInfo::mobi() const
{
    return mobi_;
}

void UserInfo::setMobi(int mobi)
{
    mobi_ = mobi;
    userData_->set(kMobi, mobi_);
}

float UserInfo::remainder() const
{
    return remainder_;
}

void UserInfo::setRemainder(float remainder)
{
    remainder_ = remainder;
    userData_->set(kRemainder, remainder_);
}

float UserInfo::trip()
{
    trip_ = userData_->getDouble(kTrip, 0.0);
    return trip_;
}

void UserInfo::setTrip(float trip)
{
    trip_ = trip;
    userData_->set(kTrip, trip_);
}

void UserInfo::setRidingState(const ERidingState &ridingState)
{
    ridingState_ = ridingState;
}

void UserInfo::sync()
{
    userData_->flush();
}

void UserInfo::flushAll()
{

}
