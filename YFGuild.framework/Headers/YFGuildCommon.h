//
//  YFGuildCommon.h
//  YFGuild
//
//  Created by 张强 on 2020/4/30.
//  Copyright © 2020 yifants. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <YFCore/YFcore.h>
#import <YFAuth/YFAuth.h>
#import <YFUtils/YFUtils.h>

#define YFGuildLogError(frmt, ...)   LOG_MAYBE(NO,                LOG_LEVEL_DEF, YFSKLogFlagError,   0, @"公会", __PRETTY_FUNCTION__, frmt, ##__VA_ARGS__)
#define YFGuildLogWarn(frmt, ...)    LOG_MAYBE(LOG_ASYNC_ENABLED, LOG_LEVEL_DEF, YFSKLogFlagWarning, 0, @"公会", __PRETTY_FUNCTION__, frmt, ##__VA_ARGS__)
#define YFGuildLogInfo(frmt, ...)    LOG_MAYBE(LOG_ASYNC_ENABLED, LOG_LEVEL_DEF, YFSKLogFlagInfo,    0, @"公会", __PRETTY_FUNCTION__, frmt, ##__VA_ARGS__)
#define YFGuildLogDebug(frmt, ...)   LOG_MAYBE(LOG_ASYNC_ENABLED, LOG_LEVEL_DEF, YFSKLogFlagDebug,   0, @"公会", __PRETTY_FUNCTION__, frmt, ##__VA_ARGS__)
#define YFGuildLogVerbose(frmt, ...) LOG_MAYBE(LOG_ASYNC_ENABLED, LOG_LEVEL_DEF, YFSKLogFlagVerbose, 0, @"公会", __PRETTY_FUNCTION__, frmt, ##__VA_ARGS__)

typedef NS_ENUM(NSInteger, YFGuildErrorCode) {
    // Create guild
    YFGuildErrorCodeInGuild = 1001,  //已经在公会内,无法创建
    YFGuildErrorCodeMissName = 1002, //缺少公会名称,无法创建
    YFGuildErrorCodeMissAvatar = 1003, // 缺少公会头像,无法创建
    YFGuildErrorCodeMissDesc = 1004, // 缺少公会描述, 无法创建
    
    // Modify guild
    YFGuildErrorCodeNotAuthorized = 1011, // 角色权限不够(只有会长和管理员才能修改)
};

typedef NS_ENUM(uint32_t, YFGuildType) {
    YFGuildTypePublic = 1,      //公开且无需审核的公会
    YFGuildTypeNeedApply = 2,   //非公开且需要审核的公会
    YFGuildTypePrivate = 3,     //非公开且无需要审核的公会
    YFGuildTypeSemiPublic = 4   //公开且需要审核的公会
};

// 消息类型(文本、互助、申请,邀请...等) 10000以内为公会系统自用 开发者可自定义范围(10000-90000)
typedef NS_ENUM(uint32_t, YFMessageType) {
    YFMessageTypeText = 1,
    YFMessageTypeRequestHelp = 2,
    YFMessageTypeSystem = 100,      //系统消息 
    YFMessageTypeNewMember = 101,
    YFMessageTypeKickoff = 102,
    YFMessageTypeQuit = 103,
    YFMessageTypeDismiss = 104,
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

// 1.已读 2.同意入会 3.拒绝入会 4.删除消息 10000以内数值系统自用 可自定义范围(10000-90000)
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

@interface YFMessageBase

@property (copy, nonatomic) NSString *uid; // 消息唯一ID
@property (assign, nonatomic) YFMessageType type; // 消息类型  1.已读 2.同意入会 3.拒绝入会 4.删除消息 10000以内数值系统自用 可自定义范围(10000-90000)

@end
