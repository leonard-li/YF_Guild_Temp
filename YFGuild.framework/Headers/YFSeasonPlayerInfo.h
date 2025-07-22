//
//  YFSeasonPlayerInfo.h
//  YFGuild
//
//  Created by leonard.li on 8/9/24.
//  Copyright © 2024 yifants. All rights reserved.
//

#import <Foundation/Foundation.h>

@class SeasonPlayerInfo;

NS_ASSUME_NONNULL_BEGIN

@interface YFSeasonPlayerInfo : NSObject

@property (copy, nonatomic) NSString *uid; // 玩家id
@property (assign, nonatomic) uint64_t contribute; // 玩家贡献度
@property (copy, nonatomic) NSString *user_extents; // 玩家扩展信息

+ (instancetype)seasonPlayerWithInfo:(SeasonPlayerInfo *)info;

@end

NS_ASSUME_NONNULL_END
