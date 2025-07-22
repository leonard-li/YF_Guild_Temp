//
//  YFActivityGuildInfo.h
//  YFGuild
//
//  Created by leonard.li on 8/26/24.
//  Copyright © 2024 yifants. All rights reserved.
//

#import <Foundation/Foundation.h>
@class GuildActivity;

NS_ASSUME_NONNULL_BEGIN

@interface YFActivityGuildInfo : NSObject

@property (copy, nonatomic) NSString *gid; // 公会id
@property (copy, nonatomic) NSString *name; // 公会名称
@property (copy, nonatomic) NSString *icon; // 公会头像
@property (assign, nonatomic) uint64_t score; // 公会分数

+ (instancetype)activityGuildWithInfo:(GuildActivity *)info;

@end

NS_ASSUME_NONNULL_END
