//
//  YFMessageInfo.h
//  YFGuild
//
//  Created by 张强 on 2020/4/29.
//  Copyright © 2020 yifants. All rights reserved.
//

#import <Foundation/Foundation.h>
@class MessageInfo;

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(uint32_t, YFMessageType) {
    YFMessageTypeText = 1,
    YFMessageTypeRequestHelp = 2,
    YFMessageTypeNewMember = 101,
    YFMessageTypeKickoff = 102,
    YFMessageTypeQuit = 103,
    YFMessageTypeTransfer = 105,
    YFMessageTypeModifyGuild = 106,
    YFMessageTypeSetManager = 107,
    YFMessageTypeApplication = 108,
    YFMessageTypeInvitation = 109,
    YFMessageTypeHelpOther = 110,   //socket发送的帮助
    YFMessageTypeSendHelp = 111    //HTTP发送的帮助
};

typedef NS_ENUM(uint32_t, YFMessageSendStatus) {
    YFMessageSendStatusSending = 1,
    YFMessageSendStatusFailed = 2,
    YFMessageSendStatusSuccess = 3
};

typedef NS_ENUM(uint32_t, YFMessageHandle) {
    YFMessageHandleRead = 1,
    YFMessageHandleAccept = 2,
    YFMessageHandleRefuse = 3,
    YFMessageHandleDelete = 4
};

typedef NS_ENUM(uint32_t, YFMessageStatus) {
    YFMessageStatusUnread = 0,
    YFMessageStatusRead = 1,
    YFMessageStatusAccept = 2,
    YFMessageStatusRefuse = 3,
    YFMessageStatusDelete = 4
};

@interface YFMessageInfo : NSObject

@property (copy, nonatomic) NSString *uid; // 消息唯一ID
@property (copy, nonatomic) NSString *from; // 谁发的消息
@property (copy, nonatomic) NSString *to; //发给谁的消息
@property (copy, nonatomic) NSString *content; // 内容
@property (assign, nonatomic) uint64_t timestamp; // 时间戳
@property (assign, nonatomic) YFMessageType type; // 消息类型
@property (assign, nonatomic) YFMessageStatus staus; // 消息状态
@property (copy, nonatomic) NSString *fromName; // 消息发送人的名称
@property (assign, nonatomic) uint32_t target; // 请求帮助需要的物品总数
@property (assign, nonatomic) uint32_t received; // 请求帮助目前收到的物品数目
@property (assign, nonatomic) uint32_t helpType; // 帮助物品的类型
@property (assign, nonatomic) uint32_t helpCount; // 帮助个数
@property (assign, nonatomic) YFMessageSendStatus sendStatus;  //消息发送状态

@property (assign, nonatomic, getter=helpIsFull) BOOL helpFull; // 帮助是否收集齐了

+ (instancetype)messageWithInfo:(MessageInfo *)info;

@end

NS_ASSUME_NONNULL_END
