/**
* create by zh_u 2015-10-25
* BmobObject 是所有自定义对象的基类，也是BmobSDK的基础
*/

#ifndef BMOBSDK_BMOBOBJECT_H_
#define BMOBSDK_BMOBOBJECT_H_

#include <iostream>
#include <string>
#include <vector>
#include "cocos2d.h"
#include "network/HttpRequest.h"

#include "../delegate/bmobdelegate.h"
#include "../jsoncpp/include/json.h"
#include "bmobSDKinit.h"
#include "../util/bmobjsonutil.h"

using namespace std;
USING_NS_CC;

class BmobObject:public cocos2d::Ref{
protected:
    /**
    * save,update,delete's sign
    * HTTP操作的类型，对应的是回调接口类型
    */
    enum class HTTP_OP_Type{
        _bHTTP_SAVE,
        _bHTTP_UPDATE,
        _bHTTP_DELETE,
        _bHTTP_RESET,
        _bHTTP_REQUEST_CODE,
        _bHTTP_RESET_BY_CODE,
        _bHTTP_EMAIL_VERIFY,
        _bHTTP_LOGIN
    };

public:
	/**
    * 使用对象名来构造函数，也就是后台对应的表名
    * @param tableName 对象表名
    */
	BmobObject(string tableName);
    /**
    * 虚构函数
    */
    virtual ~BmobObject();

	/**
	* 调用该方法将对象数据保存到SDK后台
    * @param delegate 保存对象回调接口
	*/
	virtual void save(BmobSaveDelegate* delegate);
    
    /**
    * 更新对象调用方法
    * @param column 更新的字段名或者列名
    * @param value 要更新的值，默认增加1
    * 该方法值针对整型数据进行操作
    */
    virtual void increment(string column,int value = 1);
    /**
    * 设置要更新的字段和值
    * @param key    设置的字段名或者列名
    * @param object 需要设置的值
    */
    void setValue(string key,cocos2d::Ref *object);
    /**
    * 对数组的操作
    * @param key    要设置的字段名或者列名
    * @param array  数组值
    */
    void setValue(string key,cocos2d::__Array* array);
    /**
    * 使用objectId更新BmobSDK后台数据
    * @param ObjectId   更新数据对应的objectId
    * @param delegate   更新数据回调接口
    */
    virtual void update(string objectId,BmobUpdateDelegate* delegate);
    /**
    * 更新BmobSDK后台数据
    * @param    delegate    更新数据回调接口
    */
    virtual void update(BmobUpdateDelegate* delegate);
    /**
    * 设置要移除后台数据对应的字段
    * @param name   字段名
    */
    virtual void remove(string name);
    /**
    * 设置要移除后台数据对应的字段
    * @param array  要移除的字段数组
    */
    virtual void removeAll(string name,__Array* array);
    /**
    *  删除BmobSDK后台数据
    * @param    delegate    删除数据回调接口
    */
    virtual void del(BmobDeleteDelegate* delegate);
    /**
    * 直接使用objectId来删除数据
    * @param objectId 要删除数据对应的ObjectID
    * @param delegate 删除数据的回调接口
    */
    virtual void del(string objectId,BmobDeleteDelegate* delegate);

    /**
    * 向BmobSDK中添加包含一个数据的数组
    * @param column  字段名
    * @param object  对应字段名的值
    */
    virtual void add(string column,Ref* object);
    /**
    * 向BmobSDK中添加包含多个数据的数组
    * @param column 要添加的字段名
    * @param array 要添加的数组值
    */
    virtual void add(string column,__Array* array);
    /**
    * 将对象需要保存的数据压到HTTP请求中
    * @param key 要在后台保存的字段
    * @param object  要在后台保存的字段对应的值
    */
    void enParamsToHttp(std::string key,cocos2d::Ref *object);

	/**
	* 设置HTTP请求的头部
    * @param v 自定义HTTP的头部 
	*/
	virtual void setHeader(vector<string> v);
    /**
    * 获取当前HTTP请求的头部
    */
    virtual vector<string> getHeader();

    /**
    * 获取key对应的数据
    * @param key 字段名
    */
    virtual Ref* getParams(string key);
    /**
    * 将发送给服务端数据转换成json数据
    * @param value 
    */
    virtual void enJson(Json::Value* value);
    /**
    * 将Json数据解压成map<string,Ref*>
    * @param value 要解析的Json数据
    */
    virtual void deJson(Json::Value* value);

    /**
    * 清楚请求中的数据
    */
    void clear(){
        this->m_mapData.clear();
    }

protected:
    /**
    * 
    */
    BmobObject();

public:
	/**
	* 发送请求给BmobSDK后台
	*/
    void send();
    /**
    * 使用HTTP类型发送请求
    * @param type http请求类型,GET、POST、PUT、DELETE etc.
    */
    void send(network::HttpRequest::Type type);


    /**
    * HTTP请求回调函数
    * @param pSender
    * @param data 回调返回数据
    */
    virtual void onHttpRequestCompleted(cocos2d::Node *pSender,void *data);

  
protected:
    HTTP_OP_Type _opType;                           //HTTP操作类型//

	CC_SYNTHESIZE(string, m_objectId, ObjectId);   //对象对应BmobSDK后台ObjectId//
    CC_SYNTHESIZE(string,m_createdAt,CreatedAt);    //后台对象创建的时间//
    CC_SYNTHESIZE(string,m_updatedAt,UpdatedAt);    //后台对象更新的时间///
    CC_SYNTHESIZE(string,m_ACL,ACL);            
    CC_SYNTHESIZE(string,m_url,Url);                //请求的URL//

    CC_SYNTHESIZE(string,m_tableName,TableName);    //对象对应的表名//
    CC_SYNTHESIZE(string,m_session,Session);        //用户对象对应的session//

    CC_SYNTHESIZE(BmobSaveDelegate*,m_pSaveDelegate,SaveDelegate);  //保存对象回调接口//
    CC_SYNTHESIZE(BmobUpdateDelegate*,m_pUpdateDelegate,UpdateDelegate);    //更新对象回调接口//
    CC_SYNTHESIZE(BmobDeleteDelegate*,m_pDeleteDelegate,DeleteDelegate);    //删除对象回调接口//
    CC_SYNTHESIZE(BmobResetPasswordDelegate*,m_pResetDelegate,ResetDelegate);   //重置密码回调接口//
    CC_SYNTHESIZE(BmobRequestSMSCodeDelegate*,m_pRequestSMSCodeDelegate,RequestSMSCodeDelegate);    //请求SMS码回调接口//  
    CC_SYNTHESIZE(BmobResetPasswordByCodeDelegate*,m_pResetByMSMCodeDelegate,ResetByMSMCodeDelegate);   //通过SMS码重置密码的回调接口//
    CC_SYNTHESIZE(BmobEmailVerifyDelegate*,m_pEmailVerifyDelegate,EmailVerifyDelegate); //通过邮箱验证的回调接口//
    CC_SYNTHESIZE(BmobLoginDelegate*,m_pLoginDelegate,LoginDelegate);   //登录的回调接口//

    std::map<string, cocos2d::Ref *> m_mapData;    //请求的数据//
    std::vector<string> m_header;   //请求头部//

};

#endif