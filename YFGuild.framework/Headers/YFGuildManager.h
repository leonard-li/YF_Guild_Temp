//
//  YFGuildManager.h
//  YFGuild
//
//  Created by leonard.li on 2023/12/20.
//  Copyright © 2023 yifants. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "YFGuildInfo.h"
#import "YFMessageInfo.h"
#import "YFGuildUserInfo.h"
#import "YFGuildUserInfo1.h"
#import "YFSeasonPlayerInfo.h"
#import "YFActivityGuildInfo.h"
#import "YFActivityPlayerInfo.h"
#import "YFPlayerRankInfo.h"
#import "YFGuildRankInfo.h"
#import "YFHistoryRankInfo.h"
#import <YFAuth/YFAuth.h>

NS_ASSUME_NONNULL_BEGIN

@protocol YFGuildManagerDelegate <NSObject>

@required

/// 收到聊天消息(包括请求帮助消息)
/// @param message 消息
- (void)onReceiveMessage:(YFMessageInfo *)message;

/// 发送聊天消息(包括请求帮助消息)
/// @param message 消息
- (void)onSendingMessage:(YFMessageInfo *)message;

/// 断开socket连接
/// @param error 错误原因
- (void)didDisconnectWithError:(NSError *)error;

@optional
/// 发送帮助信息(更新帮助内容)
/// @param message 帮助信息
- (void)onSendHelp:(YFMessageInfo *)message;

/// 收到帮助信息(更新帮助内容)
/// @param message 帮助信息
- (void)onReceiveHelp:(YFMessageInfo *)message;

@end

typedef void(^CompletionBlock)(NSError * _Nullable error);

@interface YFGuildManager : NSObject

/// 单例
@property (class, nonatomic, readonly) YFGuildManager *sharedManager;
/// 公会信息
@property (strong, nonatomic, readonly) YFGuildInfo *guildInfo;
/// 设置监听
@property (weak, nonatomic) id<YFGuildManagerDelegate> delegate;
/// 当前玩家是否有公会
@property (assign, nonatomic, getter=isInGuild) BOOL inGuild;
/// 用户ID
@property (nonatomic, strong) NSString *currentUserId;
/// 业务标识
@property (nonatomic, strong) NSString *bid;
/// 平台类型, 不设置则为2, 安卓为1
@property (assign, nonatomic) int platform;
/// 聊天地址
@property (nonatomic, strong) NSString *chatHost;
/// 聊天端口号
@property (nonatomic, assign) NSInteger chatPort;

/// 是否使用1.0版本的公会 默认否
@property (assign, nonatomic) BOOL useV1;

/// 是否使用国内版的2.0公会
@property (assign, nonatomic) BOOL mainLand;

///// 发起帮助消息的有效期(单位秒, 默认12小时)
//@property (assign, nonatomic) NSTimeInterval helpDismissTime;
///// 帮助他人后到可以再次帮助他人的间隔时间(单位秒, 默认4小时)
//@property (assign, nonatomic) NSTimeInterval helpCDTime;

- (void)initGuildSDK;

/// 获取公会聊天地址及端口号
/// @param guildId 公会ID, 未加入公会可不传
/// @param completion 结果回调
- (void)getChatInfo:(NSString *)guildId
         completion:(void (^)(NSError * error, NSString * chatHost, NSInteger chatPort))completion;

/// 创建公会
/// @param name 公会名称
/// @param badge 公会头像
/// @param type 公会类型 类型(1.公开且无需审核的公会, 2.非公开且需要审核的公会, 3.非公开且无需要审核的公会, 4.公开且需要审核的公会)
/// @param level 最低入会等级
/// @param description 公会描述
/// @param geo 公会地区信息
/// @param handler 创建结果回调
- (void)createGuildWithName:(NSString *)name
                      badge:(NSString *)badge
                       type:(YFGuildType)type
               minimalLevel:(uint32_t)level
                description:(NSString *)description
                       geo:(NSString *)geo
                 completion:(void (^)(NSError * _Nullable error, YFGuildInfo * _Nullable guild))handler __attribute__((deprecated("已过期")));

/// 创建公会
/// @param name 公会名称
/// @param badge 公会头像
/// @param type 公会类型 类型(1.公开且无需审核的公会, 2.非公开且需要审核的公会, 3.非公开且无需要审核的公会, 4.公开且需要审核的公会)
/// @param level 最低入会等级
/// @param description 公会描述
/// @param geo 公会地区信息
/// @param extendedInfo 扩展信息
/// @param handler 创建结果回调
- (void)createGuildWithName:(NSString *)name
                      badge:(NSString *)badge
                       type:(YFGuildType)type
               minimalLevel:(uint32_t)level
                description:(NSString *)description
                        geo:(NSString *)geo
               extendedInfo:(NSString *)extendedInfo
                 completion:(void (^)(NSError * _Nullable error, YFGuildInfo * _Nullable guild))handler;

/// 查看公会成员
/// @param guildId 公会ID
/// @param handler 结果回调
- (void)getGuildMembers:(NSString *)guildId
             completion:(void(^)(NSError * _Nullable error, NSArray<YFGuildUserInfo *> * _Nullable members))handler;

/// 查看公会信息
/// @param guildId 公会ID
/// @param handler 结果回调
- (void)getGuildInfo:(NSString *)guildId
          completion:(void(^)(NSError * _Nullable error, YFGuildInfo * _Nullable guild))handler __attribute__((deprecated("已过期")));

/// 查看公会信息
/// @param guildId 公会ID
/// @param scoreRankId 公会排行榜id, 非必传, 传了这个返回的score就是公会在该榜单分数
/// @param handler 结果回调
- (void)getGuildInfo:(NSString *)guildId
         scoreRankId:(NSString *)scoreRankId
          completion:(void(^)(NSError * _Nullable error, YFGuildInfo * _Nullable guild))handler;

/// 搜索公会
/// @param keyword 搜索关键字 按公会名称/ID搜索
/// @param index 分页查询 -- 第几页, 默认1开始
/// @param number 分页查询 -- 每页多少条数据, 默认50, 最大50
/// @param handler 搜索到的公会
- (void)searchGuild:(NSString *)keyword
              index:(uint32_t)index
             number:(uint32_t)number
         completion:(void(^)(NSError * _Nullable error, NSArray<YFGuildInfo *> * _Nullable guilds))handler;

/// 按照公会ID搜索公会
/// @param guildId 公会 ID
/// @param handler 搜索到的公会
- (void)searchGuildsWithId:(NSString *)guildId 
                     index:(uint32_t)index
                    number:(uint32_t)number
                completion:(void(^)(NSError * _Nullable error, NSArray<YFGuildInfo *> * _Nullable guilds))handler;

/// 加入公会
/// @param guildId 公开的公会ID
/// @param handler 加入结果
- (void)joinGuild:(NSString *)guildId
       completion:(void(^)(NSError * _Nullable error))handler;

/// 修改用户在公会中的信息
/// @param guildId 要修改的公会ID
/// @param userId 要修改的用户ID
/// @param role 要修改的用户角色 1.无公会玩家，2.会长，3.管理员，4.普通成员
/// @param level 要修改的用户等级
/// @param score 分数
/// @param handler 设置结果
- (void)modifyGuild:(NSString *)guildId
           withUser:(NSString *)userId
           withRole:(YFRoleType)role
          withLevel:(NSInteger)level
          withScore:(NSInteger)score
         completion:(void(^)(NSError * _Nullable error))handler __attribute__((deprecated("已过期")));

/// 修改用户在公会中的信息
/// @param guildId 要修改的公会ID
/// @param userId 要修改的用户ID
/// @param role 要修改的用户角色 1.无公会玩家，2.会长，3.管理员，4.普通成员
/// @param level 要修改的用户等级
/// @param extendedInfo 玩家扩展信息
/// @param score 分数
/// @param name 玩家名称
/// @param icon 玩家头像
/// @param activeIndex 玩家活跃指数, 应用于转让会长优先级( 或各类优先级处理)
/// @param handler 设置结果
- (void)modifyGuild:(NSString *)guildId
           withUser:(NSString *)userId
           withRole:(YFRoleType)role
          withLevel:(NSInteger)level
   withExtendedInfo:(NSString *)extendedInfo
          withScore:(NSInteger)score
           withName:(NSString *)name
           withIcon:(NSString *)icon
    withActiveIndex:(NSInteger)activeIndex
         completion:(void(^)(NSError * _Nullable error))handler;

/// 更新玩家等级/进度
/// @param level 玩家等级/进度
/// @param handler 更新结果
- (void)updateLevel:(uint32_t)level completion:(CompletionBlock)handler;

- (void)setManager:(NSString *)userId
          completion:(void(^)(NSError * _Nullable error))handler;

- (void)unsetManager:(NSString *)userId
            completion:(void(^)(NSError * _Nullable error))handler;

/// 退出公会
/// @param guildId 公会ID
/// @param userId 用户ID
/// @param handler 退出公会结果
- (void)quitGuild:(NSString *)guildId
         withUser:(NSString *)userId
       completion:(void(^)(NSError * _Nullable error))handler;

/// 将玩家踢出公会
/// @param userId 被踢的玩家
/// @param handler 处理结果
- (void)kickoffUser:(NSString *)userId completion:(void(^)(NSError * _Nullable error))handler;

/// 解散公会
/// @param handler 解散结果
- (void)dismissGuild:(NSString *)guildId
          completion:(void(^)(NSError * _Nullable error))handler;

/// 修改公会信息
/// @param info 公会信息
/// @param handler 修改结果
- (void)modifyGuildInfo:(YFGuildInfo *)info
             completion:(void(^)(NSError * _Nullable error))handler;

/// 无需权限可修改公会信息
/// @param guildId 公会信息
/// @param extendedInfo 公会扩展字段
/// @param recommendIndex 公会推荐指数(越高越靠前 用于推荐公会排序)
/// @param handler 修改结果
- (void)modifyGuild:(NSString *)guildId
   withExtendedInfo:(NSString *)extendedInfo
 withRecommendIndex:(uint32_t)recommendIndex
         completion:(void(^)(NSError * _Nullable error))handler;

/// 修改公会最大成员数
/// @param guildId 公会ID
/// @param number 公会最大成员数
/// @param handler 修改结果
- (void)modifyGuild:(NSString *)guildId
         withNumber:(uint32_t)number
         completion:(void(^)(NSError * _Nullable error))handler;

/// 转让公会给某个成员
/// @param guildId 公会ID
/// @param from 旧会长的用户ID
/// @param to 新会长的用户ID
/// @param handler 转让结果
- (void)transferGuild:(NSString *)guildId
                 from:(NSString *)from
                   to:(NSString *)to
           completion:(void(^)(NSError * _Nullable error))handler;

/// 获取推荐公会
/// @param level 最低入会等级
/// @param index 分页查询 -- 第几页, 默认1开始
/// @param number 分页查询 -- 每页多少条数据, 默认50, 最大50
/// @param handler 推荐公会
- (void)getRecommondedGuilds:(NSInteger)level
                       index:(uint32_t)index
                      number:(uint32_t)number
                  completion:(void(^)(NSError * _Nullable error, NSArray<YFGuildInfo *> * _Nullable guilds))handler;

/// 获取玩家信息
/// @param userId 玩家ID
/// @param handler 玩家信息
- (void)getUserInfo:(NSString *)userId
         completion:(void(^)(NSError * _Nullable error, YFAuthUserInfo * _Nullable user))handler;

/// 同步玩家信息
/// @param userId 玩家ID
/// @param level 玩家等级
/// @param userName 玩家名称
/// @param userIcon 玩家头像
/// @param userGeo 玩家地区
/// @param handler 同步结果
- (void)syncUser:(NSString *)userId
           level:(NSInteger)level
        userName:(NSString *)userName
        userIcon:(NSString *)userIcon
         userGeo:(NSString *)userGeo
      completion:(void(^)(NSError * _Nullable error))handler __attribute__((deprecated("已过期")));

/// 同步玩家信息
/// @param userId 玩家ID
/// @param level 玩家等级
/// @param userName 玩家名称
/// @param userIcon 玩家头像
/// @param userGeo 玩家地区
/// @param handler 同步结果
- (void)syncUser:(NSString *)userId
           level:(NSInteger)level
        userName:(NSString *)userName
        userIcon:(NSString *)userIcon
         userGeo:(NSString *)userGeo
    extendedInfo:(NSString *)extendedInfo
     activeIndex:(NSInteger)activeIndex
      completion:(void(^)(NSError * _Nullable error))handler;

/// 搜索玩家
/// @param keyword 关键字
/// @param guildId 公会ID
/// @param index 分页查询 -- 第几页, 默认1开始
/// @param number 分页查询 -- 每页多少条数据, 默认50, 最大50
/// @param handler 搜索到的玩家
- (void)searchUsers:(NSString *)keyword
            guildId:(NSString *)guildId
              index:(uint32_t)index
             number:(uint32_t)number
         completion:(void(^)(NSError * _Nullable error, NSArray<YFGuildUserInfo *> * _Nullable users))handler;

/// 根据用户id集合搜索玩家
/// @param userIds 用户ID集合
/// @param ids 用户(对应的数据库主键ID) 集合 【一般情况下不需要传这个参数】
/// @param handler 搜索到的玩家
- (void)searchWithUserIds:(NSArray *)userIds
                  withIds:(NSArray *)ids
               completion:(void(^)(NSError * _Nullable error, NSArray<YFGuildUserInfo1 *> * _Nullable users))handler;

/// 给用户点赞
/// @param from 发起者用户ID
/// @param to 目标用户ID
/// @param handler 结果
- (void)addLikesFrom:(NSString *)from
                  to:(NSString *)to
          completion:(void(^)(NSError * _Nullable error))handler;

/// 获取推荐玩家
/// @param guildId 公会ID
/// @param level 最低入会等级
/// @param index 分页查询 -- 第几页, 默认1开始
/// @param number 分页查询 -- 每页多少条数据, 默认50, 最大50
/// @param handler 获取推荐玩家结果
- (void)getRecommondedUsers:(NSString *)guildId
                      level:(NSInteger)level
                      index:(uint32_t)index
                     number:(uint32_t)number
                 completion:(void(^)(NSError * _Nullable error, NSArray<YFGuildUserInfo *> * _Nullable users))handler;

/// 更改公会用户Id
/// @param oldUserId 老用户Id
/// @param newUserId 新用户Id
/// @param handler 更改用户Id结果
- (void)transferUser:(NSString *)oldUserId to:(NSString *)newUserId completion:(void(^)(NSError * _Nullable error))handler;

/// 获取公会排行榜
/// @param rankingId 榜单id
/// @param start 开始位置
/// @param end 结束位置
/// @param geo 要获取的榜单地区
/// @param handler 公会排行
- (void)getGuildRanking:(NSString *)rankingId
                  start:(uint32_t)start
                    end:(uint32_t)end
                    geo:(NSString *)geo
             completion:(void(^)(NSError * _Nullable error, NSArray<YFGuildInfo *> * _Nullable guilds))handler;

/// 玩家直接迁移到其他公会(玩家已在公会中, 直接加入其他公会)
/// @param guildId 要迁移到的公会Id
/// @param handler 迁移结果
- (void)tansferTo:(NSString *)guildId
       completion:(void(^)(NSError * _Nullable error))handler;

// -------------------------------------

/// 邀请无公会玩家加入公会
/// @param userId 无公会玩家ID
/// @param handler 邀请结果
- (void)inviteUser:(NSString *)userId completion:(void(^)(NSError * _Nullable error))handler;

/// 申请加入某个公会
/// @param guildId 申请加入的公会ID
/// @param handler 申请结果
- (void)applyJoinGuild:(NSString *)guildId completion:(void(^)(NSError * _Nullable error))handler;

/// 查询公会收到的入会申请,只有管理员和会长有权限
/// @param handler 收到的申请
- (void)getIncommingApplications:(void(^)(NSError * _Nullable error, NSArray<YFMessageInfo *> * _Nullable messages))handler;

/// 查询自己收到的公会邀请
/// @param handler 收到的邀请
- (void)getIncommingInvitations:(void(^)(NSError * _Nullable error, NSArray<YFMessageInfo *> * _Nullable messages))handler;

/// 查询自己收到的帮助
/// @param handler 收到的帮助
- (void)getIncommingHelp:(void(^)(NSError * _Nullable error, NSArray<YFMessageInfo *> * _Nullable messages))handler;

/// 处理入会申请
/// @param messageId 入会申请
/// @param accept 同意或者拒绝
/// @param handler 处理结果
- (void)handleApplication:(NSString *)messageId accept:(BOOL)accept completion:(void(^)(NSError * _Nullable error))handler;

/// 处理公会邀请
/// @param messageId 公会邀请
/// @param accept 同意或者拒绝
/// @param handler 处理结果
- (void)handleInvitation:(NSString *)messageId accept:(BOOL)accept completion:(void(^)(NSError * _Nullable error))handler;

/// 领取帮助
/// @param messageId 帮助ID
/// @param handler 结果
- (void)collectHelp:(NSString *)messageId completion:(void(^)(NSError * _Nullable error))handler;

/// 批量处理多个离线消息
/// @param messages 消息集合
/// @param handler 结果
- (void)handleMultipleMessages:(NSArray<YFMessageBase *> *)messages completion:(void(^)(NSError * _Nullable error))handler;

/// 获取聊天列表的消息
/// @param handler 获取消息结果
- (void)getMessagesCompletion:(void(^)(NSError * _Nullable error, NSArray<YFMessageInfo *> * _Nullable messages))handler;

/// 获取有效离线消息
/// @param guildId 公会ID
/// @param types 消息类型集合 (文本、互助、申请,邀请...等) 10000以内为公会系统自用 开发者可自定义范围(10000-90000)
/// @param count 消息数量
/// @param handler 结果
- (void)getValidMessagesByGuild:(NSString *)guildId
                  byMessageType:(NSArray<NSNumber *> *)types
                        byCount:(uint32_t)count
                     completion:(void(^)(NSError * _Nullable error, NSArray<YFMessageInfo *> * _Nullable messages))handler;

/// 获取公会有子消息的消息列表
/// @param guildId 公会ID
/// @param mainType 主消息类型
/// @param subTypes 子消息类型集合
/// @param msgIds 主消息id限制
/// @param handler 结果
- (void)getMessagesByGuild:(NSString *)guildId
             byMessageType:(NSNumber *)mainType
         bySubMessageTypes:(NSArray<NSNumber *> *)subTypes
              byMessageIds:(NSArray<NSString *> *)msgIds
                completion:(void(^)(NSError * _Nullable error, NSArray<YFMessageInfo *> * _Nullable messages))handler;

/// 刷新玩家信息和公会信息
/// @param handler 刷新结果
- (void)refreshCompletion:(void(^)(NSError * _Nullable error))handler;

/// 登录聊天室
/// @param handler 登录结果
- (void)loginChatCompletion:(void(^)(NSError * _Nullable error))handler;

/// 发送即时聊天消息
/// @param content 聊天内容
- (void)sendMessageWithContent:(NSString *)content;

/// 查询能否发送帮助
- (BOOL)canSendHelpRequest;

/// 发送帮助
/// @param type 类型
/// @param count 个数
- (void)sendHelpRequestWithType:(uint8_t)type targetCount:(uint32_t)count;

/// 帮助某个玩家
/// @param messageId 针对某条帮助请求
/// @param userId 帮助的对象(发出请求的玩家ID)
/// @param type 帮助类型(生命, 金币...)
/// @param count 帮助个数
/// @param block 帮助发送结果回调
- (void)helpWithMessage:(NSString *)messageId to:(NSString *)userId type:(uint8_t)type count:(uint32_t)count completion:(void(^)(NSError * _Nullable error))block;

/// 登出聊天室
- (void)logoutChat;

#pragma mark - 赛季活动

/// 查询玩家在某赛季领取奖励信息
/// @param activityId 活动Id
/// @param userId 玩家Id
/// @param seasonFlag 赛季活动标识
/// @param completion 回调(在某赛季下领取的奖励id列表)
- (void)getClaimInfoWithActivityId:(NSString *)activityId
                            userId:(NSString *)userId
                        seasonFlag:(int)seasonFlag
                        completion:(void (^)(NSError * _Nullable error, NSArray<NSString *> * _Nullable rewardIdList))completion;

/// 记录赛季活动领取奖励
/// @param activityId 活动Id
/// @param userId 玩家Id
/// @param seasonFlag 赛季活动标识
/// @param rewardIdList 赛季活动下唯一奖励id列表
/// @param completion 回调
- (void)recordClaimWithActivityId:(NSString *)activityId
                           userId:(NSString *)userId
                       seasonFlag:(int)seasonFlag
                         rewardId:(NSString *)rewardId
                     rewardIdList:(NSArray<NSString *> *)rewardIdList
                       completion:(void (^)(NSError * _Nullable error))completion;

/// 查询赛季活动公会玩家信息
/// @param activityId 活动Id
/// @param flag 赛季活动标识
/// @param gId 公会id
/// @param completion 回调
- (void)getSeasonPlayerInfoWithActivityId:(NSString *)activityId
                                     flag:(int)flag
                                      gId:(NSString *)gId
                               completion:(void (^)(NSError * _Nullable error, NSArray<YFSeasonPlayerInfo *> * _Nullable list))completion;

/// 查询赛季活动公会信息
/// @param activityId 活动Id
/// @param flag 赛季活动标识
/// @param gId 公会id
/// @param completion 回调
- (void)getSeasonGuildInfoWithActivityId:(NSString *)activityId
                                    flag:(int)flag
                                     gId:(NSString *)gId
                              completion:(void (^)(NSError * _Nullable error, double contribute, NSString * guildExtents))completion;

/// 提交赛季活动贡献度
/// @param activityId 活动Id
/// @param flag 赛季活动标识
/// @param contribute 贡献度
/// @param userId 玩家id
/// @param guildId 公会id
/// @param userExtents 玩家扩展信息
/// @param guildExtents 公会扩展信息
/// @param completion 回调
- (void)commitContributeWithActivityId:(NSString *)activityId
                                  flag:(int)flag
                            contribute:(double)contribute
                                userId:(NSString *)userId
                               guildId:(NSString *)guildId
                           userExtents:(NSString *)userExtents
                          guildExtents:(NSString *)guildExtents
                            completion:(void (^)(NSError * _Nullable error))completion;

/// 获取赛季活动标识
/// @param activityId 活动Id
/// @param userId 用户id
/// @param completion 回调
- (void)getSeasonFlagInfoWithActivityId:(NSString *)activityId
                                  userId:(NSString *)userId
                              completion:(void (^)(NSError * _Nullable error, int flag, double start_time, double end_time))completion;

#pragma mark - 组队活动

/// 根据队伍id获取的玩家
/// @param activityId 活动Id
/// @param teamId 队伍Id
/// @param completion 回调
- (void)getPlayersWithActivityId:(NSString *)activityId
                          teamId:(NSString *)teamId
                      completion:(void (^)(NSError * _Nullable error, NSString * _Nullable roomId, NSArray<YFActivityPlayerInfo *> * _Nullable list))completion;

/// 根据公会id获取不在活动中的玩家
/// @param activityId 活动Id
/// @param guildId 公会id
/// @param endTime 活动结束时间
/// @param completion 回调
- (void)getPlayersNotInActivityId:(NSString *)activityId
                          guildId:(NSString *)guildId
                          endTime:(double)endTime
                       completion:(void (^)(NSError * _Nullable error, NSArray<YFActivityPlayerInfo *> * _Nullable list))completion;

/// 创建队伍接口
/// @param activityId 活动Id
/// @param endTime 活动结束时间
/// @param userId 用户Id
/// @param completion 回调
- (void)createTeam:(NSString *)activityId
           endTime:(double)endTime
            userId:(NSString *)userId
        completion:(void (^)(NSError * _Nullable error, NSString * _Nullable roomId, NSString * _Nullable teamId))completion;

/// 加入组队活动
/// @param teamId 队伍id
/// @param activityId 活动Id
/// @param endTime 活动结束时间
/// @param userId 用户Id
/// @param completion 回调
- (void)joinTeam:(NSString *)teamId
      activityId:(NSString *)activityId
         endTime:(double)endTime
          userId:(NSString *)userId
      completion:(void (^)(NSError * _Nullable error))completion;

/// 提交组队活动的分数
/// @param activityId 活动Id
/// @param teamId 队伍id
/// @param userId 用户Id
/// @param score 分数
/// @param completion 回调
- (void)commitTeamActivity:(NSString *)activityId
                    teamId:(NSString *)teamId
                    userId:(NSString *)userId
                     score:(double)score
                completion:(void (^)(NSError * _Nullable error))completion;

/// 获取组队活动信息
/// @param activityId 活动Id
/// @param roomId 活动房间id
/// @param completion 回调
- (void)getTeamInfo:(NSString *)activityId
             roomId:(NSString *)roomId
         completion:(void (^)(NSError * _Nullable error, NSArray<NSArray<YFActivityPlayerInfo *> *> * _Nullable list))completion;

#pragma mark - 公会活动

/// 获取当前活动的奖励等级
/// @param activityId 活动Id
/// @param endTime 当前活动结束时间
/// @param gid 公会id
/// @param completion 回调
- (void)getTreasure:(NSString *)activityId
            endTime:(double)endTime
                gid:(NSString *)gid
         completion:(void (^)(NSError * _Nullable error, int treasure))completion;

/// 获取成员活动信息列表
/// @param activityId 活动Id
/// @param roomId 活动房间id
/// @param gid 公会id
/// @param completion 回调
- (void)getPlayerActivity:(NSString *)activityId
                   roomId:(NSString *)roomId
                      gid:(NSString *)gid
               completion:(void (^)(NSError * _Nullable error, NSArray<YFActivityPlayerInfo *> * _Nullable list))completion;

/// 获取公会活动信息列表
/// @param roomId 活动房间id
/// @param completion 回调
- (void)getGuildActivity:(NSString *)roomId
              completion:(void (^)(NSError * _Nullable error, NSArray<YFActivityGuildInfo *> * _Nullable list))completion;

/// 检查公会是否参与活动
/// @param activityId 活动id
/// @param endTime 活动结束时间
/// @param userId  用户id
/// @param completion 回调
- (void)checkGuildInActivity:(NSString *)activityId
                     endTime:(double)endTime
                      userId:(NSString *)userId
                  completion:(void (^)(NSError * _Nullable error, NSString * _Nullable roomId))completion;

/// 提交公会活动的分数请求
/// @param activityId 活动id
/// @param userId  用户id
/// @param score 活动分数
/// @param roomId 活动房间id
/// @param completion 回调
- (void)commitGuildActivity:(NSString *)activityId
                     userId:(NSString *)userId
                      socre:(double)score
                     roomId:(NSString *)roomId
                 completion:(void (^)(NSError * _Nullable error))completion;

/// 加入公会活动请求
/// @param activityId 活动id
/// @param endTime 活动结束时间
/// @param userId  用户id
/// @param completion 回调
- (void)joinGuildActivity:(NSString *)activityId
                  endTime:(double)endTime
                   userId:(NSString *)userId
               completion:(void (^)(NSError * _Nullable error, NSString * _Nullable roomId))completion;

#pragma mark - 公会排行榜

/// 成员提交分数到公会榜单
/// @param score 分数
/// @param rankingId  榜单id
/// @param userId 玩家Id
/// @param geo 地区
/// @param extendInfo 提交扩展字段(不同玩家提交则会覆盖 最终在GuildRankingFetchReq接口中返回 以公会为一组)
/// @param completion 回调
- (void)commitScore:(double)score
          toRanking:(NSString *)rankingId
             userId:(NSString *)userId
                geo:(NSString *)geo
          extendInfo:(NSString *)extendInfo
         completion:(void (^)(NSError * _Nullable error))completion;

/// 获取公会排行榜(升级版)
/// @param rankingId 榜单id
/// @param start 起始位置(榜单100位 值为0-99)
/// @param end 结束位置(榜单100位 值为0-99)
/// @param geo 要获取的榜单地区
/// @param completion 回调
- (void)getGuildRanking2:(NSString *)rankingId
                   start:(uint32_t)start
                     end:(uint32_t)end
                     geo:(NSString *)geo
              completion:(void (^)(NSError * _Nullable error, NSArray<YFGuildRankInfo *> * _Nullable list))completion;

/// 获取榜单历史前3玩家信息
/// @param rankingId 榜单id
/// @param geo 要获取的榜单地区
/// @param completion 回调
- (void)getTop3GuildRanking:(NSString *)rankingId
                        geo:(NSString *)geo
                 completion:(void (^)(NSError * _Nullable error, NSArray<YFHistoryRankInfo *> * _Nullable list))completion;

/// 获取榜单历史前3玩家信息
/// @param rankingId 榜单id
/// @param geo 要获取的榜单地区
/// @param endTime 获取对应结算时间的记录 时间戳单位：秒
/// @param limit 返回每期数据条数限制
/// @param completion 回调
- (void)getTop3GuildRanking:(NSString *)rankingId
                        geo:(NSString *)geo
                    endTime:(int64_t)endTime
                      limit:(int64_t)limit
                 completion:(void (^)(NSError * _Nullable error, NSArray<YFHistoryRankInfo *> * _Nullable list))completion;

/// 获取某公会在榜单中的信息
/// @param rankingId 榜单id
/// @param guildId 公会id
/// @param geo 要获取的榜单地区
/// @param completion 回调
- (void)getGuildRankInfo:(NSString *)rankingId
                 guildId:(NSString *)guildId
                     geo:(NSString *)geo
              completion:(void (^)(NSError * _Nullable error, int64_t rank, YFGuildRankInfo * _Nullable info))completion;

/// 获取某公会在榜单中成员提交分数的信息
/// @param rankingId 榜单id
/// @param guildId 工会id
/// @param geo 要获取的榜单地区
/// @param completion 回调
- (void)getGuildRankMember:(NSString *)rankingId
                   guildId:(NSString *)guildId
                       geo:(NSString *)geo
                completion:(void (^)(NSError * _Nullable error, NSArray<YFPlayerRankInfo *> * _Nullable list))completion;

@end

NS_ASSUME_NONNULL_END
