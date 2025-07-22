//
//  YFPlayerRankInfo.h
//  YFGuild
//
//  Created by leonard.li on 5/28/25.
//  Copyright © 2025 yifants. All rights reserved.
//

#import <Foundation/Foundation.h>
@class PlayerRankInfo;

NS_ASSUME_NONNULL_BEGIN

@interface YFPlayerRankInfo : NSObject

@property (copy, nonatomic) NSString *userId; // 玩家id
@property (assign, nonatomic) uint64_t score; // 玩家分数

+ (instancetype)playerRankInfoWithInfo:(PlayerRankInfo *)info;

@end

NS_ASSUME_NONNULL_END
