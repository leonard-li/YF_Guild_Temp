//
//  YFGuildUserInfo1.h
//  YFGuild
//
//  Created by leonard.li on 12/26/24.
//  Copyright © 2024 yifants. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <YFAuth/YFAuth.h>

@class GPlayer;

NS_ASSUME_NONNULL_BEGIN

@interface YFGuildUserInfo1 : NSObject

@property (copy, nonatomic) NSString *userId; // 成员ID
@property (copy, nonatomic) NSString *userName; // 成员昵称
@property (copy, nonatomic) NSString *userIcon; // 成员头像
@property (copy, nonatomic) NSString *countryCode; // 成员国家
@property (assign, nonatomic) YFRoleType role; // 成员角色 1.无公会玩家，2.会长，3.管理员，4.普通成员
@property (copy, nonatomic) NSString *guildId; // 公会ID
@property (assign, nonatomic) uint64_t guildTime; // 入会时间
@property (assign, nonatomic) uint32_t level; // 成员等级
@property (assign, nonatomic) uint32_t helpCount; // 互赠次数
@property (assign, nonatomic) uint64_t loginTime; // 成员最近登录时间
@property (copy, nonatomic) NSString *extendedInfo; // 扩展字段
@property (assign, nonatomic) uint64_t score; // 玩家分数
@property (assign, nonatomic) uint32_t helpsMade; // 玩家累计帮助次数
@property (assign, nonatomic) uint32_t helpsReceived; // 玩家累计接收帮助次数
@property (assign, nonatomic) uint64_t dataId; // 数据自增id
@property (copy, nonatomic) NSString *guildName; // 公会名称
@property (copy, nonatomic) NSString *guildBadge; // 公会会徽
@property (assign, nonatomic) uint32_t activeIndex; // 活跃指数
@property (assign, nonatomic) uint32_t likes; // 用户点赞数

+ (instancetype)guildUserWithInfo:(GPlayer *)info;


@end

NS_ASSUME_NONNULL_END
