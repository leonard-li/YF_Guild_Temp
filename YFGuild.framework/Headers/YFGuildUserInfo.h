//
//  YFGuildUserInfo.h
//  YFGuild
//
//  Created by leonard.li on 2023/6/6.
//  Copyright © 2023 yifants. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <YFAuth/YFAuth.h>

@class Player;

NS_ASSUME_NONNULL_BEGIN

@interface YFGuildUserInfo : NSObject

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
@property (assign, nonatomic) uint64_t score; // 玩家分数

//兼容1.0版本的属性
@property (assign, nonatomic) uint64_t joinTime;// 入会时间

+ (instancetype)guildUserWithInfo:(Player *)info;

+ (instancetype)guildUserWithYFUserInfo:(YFAuthUserInfo *)info;

@end

NS_ASSUME_NONNULL_END
