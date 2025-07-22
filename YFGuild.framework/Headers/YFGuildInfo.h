//
//  YFGuildInfo.h
//  YFGuild
//
//  Created by 张强 on 2020/4/29.
//  Copyright © 2020 yifants. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "YFGuildCommon.h"

@class GuildInfo;

NS_ASSUME_NONNULL_BEGIN

@interface YFGuildInfo : NSObject
@property (copy, nonatomic) NSString *guildId; // 公会ID
@property (copy, nonatomic) NSString *name; // 公会名称
@property (copy, nonatomic) NSString *badge; // 公会头像
@property (copy, nonatomic) NSString *ownerId; // 公会会长ID
@property (copy, nonatomic) NSString *guildDesc; // 公会描述
@property (assign, nonatomic) uint64_t cTime; // 创建时间
@property (assign, nonatomic) YFGuildType type; // 公会类型 1.公开且无需审核的公会, 2.非公开且需要审核的公会, 3.非公开且无需要审核的公会, 4.公开且需要审核的公会
@property (assign, nonatomic) uint32_t count; // 公会当前总人数
@property (assign, nonatomic) uint32_t minimalLevel; // 加入门槛
@property (assign, nonatomic) uint32_t helpCount; // 公会成员总互助次数
@property (assign, nonatomic) uint64_t activityTime; // 公会最近活跃时间
@property (assign, nonatomic) uint32_t guildLevel; // 公会等级（成员等级之和?）
@property (copy, nonatomic) NSString *geo; // 公会地区
@property (assign, nonatomic) uint32_t maxCount; // 公会人数上限
@property (assign, nonatomic) uint32_t apply; // 0 未申请 1 申请中
@property (assign, nonatomic) uint64_t score; // 公会排行榜分数
@property (copy, nonatomic) NSString *extendedInfo; // 公会扩展字段
@property (assign, nonatomic) uint32_t recommendIndex; // 公会推荐指数(越高越靠前 用于推荐公会排序)
@property (assign, nonatomic) uint32_t activityType; // 公会活跃度(1-高 2-中 3-低)

+ (instancetype)guildWithInfo:(GuildInfo *)info;

@end

NS_ASSUME_NONNULL_END
