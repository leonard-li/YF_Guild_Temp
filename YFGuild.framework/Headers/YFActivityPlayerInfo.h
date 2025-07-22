//
//  YFActivityPlayerInfo.h
//  YFGuild
//
//  Created by leonard.li on 8/23/24.
//  Copyright © 2024 yifants. All rights reserved.
//

#import <Foundation/Foundation.h>

@class PlayerActivity;

NS_ASSUME_NONNULL_BEGIN

@interface YFActivityPlayerInfo : NSObject

@property (copy, nonatomic) NSString *uid; // 玩家id
@property (copy, nonatomic) NSString *name; // 玩家名称
@property (copy, nonatomic) NSString *icon; // 玩家头像
@property (assign, nonatomic) uint64_t score; // 玩家分数
@property (copy, nonatomic) NSString *extents; // 玩家扩展信息
@property (assign, nonatomic) uint64_t level; // 等级

+ (instancetype)activityPlayerWithInfo:(PlayerActivity *)info;

@end

NS_ASSUME_NONNULL_END
