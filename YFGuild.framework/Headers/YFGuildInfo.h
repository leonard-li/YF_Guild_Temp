//
//  YFGuildInfo.h
//  YFGuild
//
//  Created by 张强 on 2020/4/29.
//  Copyright © 2020 yifants. All rights reserved.
//

#import <Foundation/Foundation.h>

@class GuildInfo;

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(uint32_t, YFGuildType) {
    YFGuildTypePublic = 1,
    YFGuildTypeNeedApply = 2,
    YFGuildTypePrivate = 3
};

@interface YFGuildInfo : NSObject

@property (copy, nonatomic) NSString *guildId; // 公会ID
@property (copy, nonatomic) NSString *name; // 公会名称
@property (copy, nonatomic) NSString *badge; // 公会徽章
@property (copy, nonatomic) NSString *ownerId; // 会长ID
@property (copy, nonatomic) NSString *guildDesc; // 公会描述
@property (assign, nonatomic) YFGuildType type; // 公会类型
@property (assign, nonatomic) uint32_t count; // 公会当前总人数
@property (assign, nonatomic) uint64_t ctime; // 公会创建时间
@property (assign, nonatomic) uint32_t helpCount; // 公会援助次数
@property (assign, nonatomic) uint32_t minimalLevel; // 公会最低加入等级

+ (instancetype)guildWithInfo:(GuildInfo *)info;

@end

typedef NSString * YFGuildInfoUpdateKey;

FOUNDATION_EXPORT YFGuildInfoUpdateKey const nameKey;
FOUNDATION_EXPORT YFGuildInfoUpdateKey const badgeKey;
FOUNDATION_EXPORT YFGuildInfoUpdateKey const guildDescKey;
FOUNDATION_EXPORT YFGuildInfoUpdateKey const typeKey;

NS_ASSUME_NONNULL_END
