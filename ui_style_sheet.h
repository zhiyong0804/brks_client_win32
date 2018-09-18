#ifndef UI_STYLE_SHEET_H
#define UI_STYLE_SHEET_H

const QString sheet_home_user_center_icon = " \
        QPushButton{ border:none; border-image: url(:/home/home_user_center_icon);} \
        QPushButton:hover{ border-image: url(:/home/home_user_center_icon);} \
        QPushButton:pressed{ border-image: url(:/home/home_user_center_icon);}";
const QString sheet_home_messages_icon = " \
        QPushButton{ border:none; border-image: url(:/home/home_messages_icon);} \
        QPushButton:hover{ border-image: url(:/home/home_messages_icon);} \
        QPushButton:pressed{ border-image: url(:/home/home_messages_icon);}";
const QString sheet_home_bike_scan_b = " \
        QPushButton{ border:none; border-image: url(:/home/home_bike_scan_b);} \
        QPushButton:hover{ border-image: url(:/home/home_bike_scan_b);} \
        QPushButton:pressed{ border-image: url(:/home/home_bike_scan_b);}";
const QString sheet_locationButton = " \
        QPushButton{ border:none; border-image: url(:/home/bt_home_location);} \
        QPushButton:hover{ border-image: url(:/home/bt_home_location);} \
        QPushButton:pressed{ border-image: url(:/home/bt_home_location_pressed);}";

const QString sheet_user_userButton = " \
        QPushButton{ border:none; border-image: url(:/user/avatar_default_login);} \
        QPushButton:hover{ border-image: url(:/user/avatar_default_login);} \
        QPushButton:pressed{ border-image: url(:/user/avatar_default_login);}";
const QString sheet_user_mobiButton = " \
        QPushButton{ border:none; border-image: url(:/user/ic_mobile_coin);} \
        QPushButton:hover{ border-image: url(:/user/ic_mobile_coin);} \
        QPushButton:pressed{ border-image: url(:/user/ic_mobile_coin);}";
const QString sheet_user_remainderButton = " \
        QPushButton{ border:none; border-image: url(:/user/ic_drawer_money);} \
        QPushButton:hover{ border-image: url(:/user/ic_drawer_money);} \
        QPushButton:pressed{ border-image: url(:/user/ic_drawer_money);}";
const QString sheet_user_tripButton = " \
        QPushButton{ border:none; border-image: url(:/user/ic_drawer_trip);} \
        QPushButton:hover{ border-image: url(:/user/ic_drawer_trip);} \
        QPushButton:pressed{ border-image: url(:/user/ic_drawer_trip);}";

const QString sheet_user_memberButton = " \
        QPushButton{font:bold 14px;color: rgb(250,250,250); border:none;background-color: rgb(239,92, 72);} \
        QPushButton:hover{font:bold 14px; background-color: rgb(229,92, 72);} \
        QPushButton:pressed{font:bold 14px;color: rgb(240,240,240); background-color: rgb(239,92, 72);}";
const QString sheet_user_honorButton = " \
        QPushButton{font:bold 14px;color: rgb(250,250,250); border:none;background-color:rgb(86,92,101);} \
        QPushButton:hover{font:bold 14px; background-color:rgb(86,80,101);} \
        QPushButton:pressed{font:bold 14px;color: rgb(240,240,240); background-color:rgb(86,92,101);}";

const QString sheet_login_wechatButton = " \
        QPushButton{ border:none; border-image: url(:/login/login_wechat);} \
        QPushButton:hover{ border-image: url(:/login/login_wechat);} \
        QPushButton:pressed{ border-image: url(:/login/login_wechat);}";
const QString sheet_login_weiboButton = " \
        QPushButton{ border:none; border-image: url(:/login/login_weibo);} \
        QPushButton:hover{ border-image: url(:/login/login_weibo);} \
        QPushButton:pressed{ border-image: url(:/login/login_weibo);}";
const QString sheet_cost_monthCardButton = " \
        QPushButton{ border:none; border-image: url(:/cost/wallet_card_0);} \
        QPushButton:hover{ border-image: url(:/cost/wallet_card_0);} \
        QPushButton:pressed{ border-image: url(:/cost/wallet_card_0);}";
const QString sheet_remainderButton = " \
        QPushButton{font:bold 16px;color: rgb(0,0,0); border:none;background-color: rgb(200,200, 200);} \
        QPushButton:hover{font:bold 16px; background-color: rgb(220,220, 220);} \
        QPushButton:pressed{font:bold 16px;color: rgb(0,0,0); background-color: rgb(200,200, 200);}";
const QString sheet_recharge_remainderButton = " \
        QPushButton{ border:none; border-image: url(:/cost/balance_pay_icon);} \
        QPushButton:hover{ border-image: url(:/cost/balance_pay_icon);} \
        QPushButton:pressed{ border-image: url(:/cost/balance_pay_icon);}";
const QString sheet_recharge_weixinButton = " \
        QPushButton{ border:none; border-image: url(:/cost/weixin_ic);} \
        QPushButton:hover{ border-image: url(:/cost/weixin_ic);} \
        QPushButton:pressed{ border-image: url(:/cost/weixin_ic);}";
const QString sheet_recharge_aliplayButton = " \
        QPushButton{ border:none; border-image: url(:/cost/ic_alipay);} \
        QPushButton:hover{ border-image: url(:/cost/ic_alipay);} \
        QPushButton:pressed{ border-image: url(:/cost/ic_alipay);}";
        // 选中时
const QString sheet_recharge_cost_select = " \
        QPushButton{font:bold 16px;color: rgb(250,250,250); border:none;background-color: rgb(241,92, 70);} \
        QPushButton:hover{font:bold 16px; background-color: rgb(241,92, 70);} \
        QPushButton:pressed{font:bold 16px;color: rgb(250,250,250); background-color: rgb(241,92, 70);}";
const QString sheet_recharge_cost_unselect = " \
        QPushButton{font:bold 16px;color: rgb(10,10,10); border:none;background-color: rgb(242,242,242);} \
        QPushButton:hover{font:bold 16px; background-color: rgb(242,242,242);} \
        QPushButton:pressed{font:bold 16px;color: rgb(10,10,10); background-color: rgb(242,242,242);}";

const QString sheet_recharge_confirmButton = " \
        QPushButton{font:bold 18px;color: rgb(250,250,250); border:none;background-color: rgb(25,171, 24);} \
        QPushButton:hover{font:bold 18px; background-color: rgb(25,191,24);} \
        QPushButton:pressed{font:bold 18px;color: rgb(250,250,250); background-color: rgb(25,231,24);}";
#endif // UI_STYLE_SHEET_H
