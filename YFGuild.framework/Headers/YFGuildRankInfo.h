//
//  YFGuildRankInfo.h
//  YFGuild
//
//  Created by leonard.li on 11/7/24.
//  Copyright © 2024 yifants. All rights reserved.
//

#import <Foundation/Foundation.h>

@class GuildRankInfo;

NS_ASSUME_NONNULL_BEGIN

@interface YFGuildRankInfo : NSObject

@property (copy, nonatomic) NSString *guildId; // 公会ID
@property (copy, nonatomic) NSString *name; // 公会名称
@property (copy, nonatomic) NSString *badge; // 公会头像
@property (assign, nonatomic) uint64_t score; // 公会分数
@property (copy, nonatomic) NSString *extendInfo; // 扩展字段

+ (instancetype)guildRankWithInfo:(GuildRankInfo *)info;

@end

NS_ASSUME_NONNULL_END
