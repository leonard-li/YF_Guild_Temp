//
//  YFHistoryRankInfo.h
//  YFGuild
//
//  Created by leonard.li on 11/7/24.
//  Copyright © 2024 yifants. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "YFGuildRankInfo.h"

@class HistoryRankInfo;

NS_ASSUME_NONNULL_BEGIN

@interface YFHistoryRankInfo : NSObject

@property (assign, nonatomic) uint64_t endTime; // 榜单结算时间
@property (copy, nonatomic) NSMutableArray<YFGuildRankInfo *> *list; // 玩家信息列表

+ (instancetype)historyRankWithInfo:(HistoryRankInfo *)info;

@end

NS_ASSUME_NONNULL_END
