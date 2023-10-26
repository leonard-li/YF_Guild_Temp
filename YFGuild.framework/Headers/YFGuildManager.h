//
//  YFGuildManager.h
//  YFGuild
//
//  Created by 张强 on 2020/4/29.
//  Copyright © 2020 yifants. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "YFGuildInfo.h"
#import "YFMessageInfo.h"
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
typedef void(^GetMessagesBlock)(NSError * _Nullable error, NSArray<YFMessageInfo *> * _Nullable messages);
typedef void(^GetGuildsBlock)(NSError * _Nullable error, NSArray<YFGuildInfo *> * _Nullable guilds);
typedef void(^GetUsersBlock)(NSError * _Nullable error, NSArray<YFAuthUserInfo *> * _Nullable users);
typedef void(^GetGuildBlock)(NSError * _Nullable error, YFGuildInfo * _Nullable guild);
typedef void(^GetUserBlock)(NSError * _Nullable error, YFAuthUserInfo * _Nullable user);

@interface YFGuildManager : NSObject

/// 单例
@property (class, nonatomic, readonly) YFGuildManager *sharedManager;
/// 公会信息
@property (strong, nonatomic, readonly) YFGuildInfo *guildInfo;
/// 设置监听
@property (weak, nonatomic) id<YFGuildManagerDelegate> delegate;
/// 当前玩家是否有公会
@property (assign, nonatomic, getter=isInGuild) BOOL inGuild;
/// 包名(默认不需要设置)
@property (copy, nonatomic) NSString *bundleId;

@property (nonatomic, strong) NSString *currentUserId;

/// 创建公会
/// @param name 公会名称
/// @param badge 公会徽章
/// @param type 公会类型
/// @param level 最低入会等级
/// @param description 公会描述
/// @param handler 创建结果回调
- (void)createGuildWithName:(NSString *)name badge:(NSString *)badge type:(YFGuildType)type minimalLevel:(uint32_t)level description:(NSString *)description completionHandler:(CompletionBlock)handler;

/// 邀请无工会玩家加入工会
/// @param userId 无工会玩家ID
/// @param handler 邀请结果
- (void)inviteUser:(NSString *)userId completionHandler:(CompletionBlock)handler;

/// 申请加入某个工会
/// @param guildId 申请加入的公会ID
/// @param handler 申请结果
- (void)applyJoinGuild:(NSString *)guildId completionHandler:(CompletionBlock)handler;

/// 直接加入公开公会
/// @param guildId 公开的公会ID
/// @param handler 加入结果
- (void)joinGuild:(NSString *)guildId completionHandler:(CompletionBlock)handler;

/// 查询公会收到的入会申请,只有管理员和会长有权限
/// @param handler 收到的申请
- (void)getIncommingApplications:(GetMessagesBlock)handler;

/// 查询自己收到的公会邀请
/// @param handler 收到的邀请
- (void)getIncommingInvitations:(GetMessagesBlock)handler;

/// 查询自己收到的帮助
/// @param handler 收到的帮助
- (void)getIncommingHelp:(GetMessagesBlock)handler;

/// 获取推荐公会
/// @param handler 推荐公会
- (void)getRecommondedGuilds:(GetGuildsBlock)handler;

/// 获取推荐玩家
/// @param handler 推荐玩家
- (void)getRecommondedUsers:(GetUsersBlock)handler;

/// 处理入会申请
/// @param messageId 入会申请
/// @param accept 同意或者拒绝
/// @param handler 处理结果
- (void)handleApplication:(NSString *)messageId accept:(BOOL)accept completion:(CompletionBlock)handler;

/// 处理公会邀请
/// @param messageId 公会邀请
/// @param accept 同意或者拒绝
/// @param handler 处理结果
- (void)handleInvitation:(NSString *)messageId accept:(BOOL)accept completion:(CompletionBlock)handler;

/// 领取帮助
/// @param messageId 帮助ID
/// @param handler 结果
- (void)collectHelp:(NSString *)messageId completion:(CompletionBlock)handler;

/// 按照名称模糊搜索玩家
/// @param keyword 关键字
/// @param handler 搜索到的玩家
- (void)searchUsers:(NSString *)keyword completion:(GetUsersBlock)handler;

/// 按照名称模糊搜索公会
/// @param keyword 关键字
/// @param handler 搜索到的公会
- (void)searchGuilds:(NSString *)keyword completion:(GetGuildsBlock)handler;

/// 按照公会ID搜索公会
/// @param guildId 公会 ID
/// @param handler 搜索到的公会
- (void)searchGuildsWithId:(NSString *)guildId completion:(GetGuildsBlock)handler;

/// 踢玩家出公会
/// @param userId 被踢的玩家
/// @param handler 处理结果
- (void)kickoffUser:(NSString *)userId completion:(CompletionBlock)handler;

/// 设置管理员
/// @param userId 设置某个玩家为管理员
/// @param handler 设置结果
- (void)setManager:(NSString *)userId completion:(CompletionBlock)handler;

/// 取消管理员
/// @param userId 取消某个玩家管理员头衔
/// @param handler 设置结果
- (void)unsetManager:(NSString *)userId completion:(CompletionBlock)handler;

/// 解散公会
/// @param handler 解散结果
- (void)dismissGuildCompletion:(CompletionBlock)handler;

/// 转让公会给某个成员
/// @param user 被转让的成员
/// @param handler 转让结果
- (void)transferGuild:(YFAuthUserInfo *)user completion:(CompletionBlock)handler;

/// 获取公会信息
/// @param guildId 公会ID
/// @param handler 公会信息
- (void)getGuildInfo:(NSString *)guildId Completion:(GetGuildBlock)handler;

/// 获取玩家信息
/// @param userId 玩家ID
/// @param handler 玩家信息
- (void)getUserInfo:(NSString *)userId completion:(GetUserBlock)handler;

/// 修改公会信息
/// @param info 公会信息
/// @param handler 修改结果
- (void)modifyGuildInfo:(YFGuildInfo *)info completion:(CompletionBlock)handler;

/// 获取公会成员列表
/// @param handler 公会成员列表
- (void)getGuildMembers:(GetUsersBlock)handler;

/// 退出公会
/// @param handler 退出公会结果
- (void)quitGuild:(CompletionBlock)handler;

/// 更改公会用户Id
/// @param oldUserId 老用户Id
/// @param newUserId 新用户Id
/// @param handler 更改用户Id结果
- (void)transferUser:(NSString *)oldUserId to:(NSString *)newUserId completion:(CompletionBlock)handler;

/// 获取聊天列表的消息
/// @param handler 获取消息结果
- (void)getMessagesCompletion:(GetMessagesBlock)handler;

/// 更新玩家等级/进度
/// @param level 玩家等级/进度
/// @param handler 更新结果
- (void)updateLevel:(uint32_t)level completion:(CompletionBlock)handler;

/// 刷新玩家信息和公会信息
/// @param handler 刷新结果
- (void)refreshCompletion:(nullable CompletionBlock)handler;

/// 登录聊天室
/// @param handler 登录结果
- (void)loginChatCompletion:(nullable CompletionBlock)handler;

/// 发送即时聊天消息
/// @param content 聊天内容
- (void)sendMessageWithContent:(NSString *)content;

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
- (void)helpWithMessage:(NSString *)messageId to:(NSString *)userId type:(uint8_t)type count:(uint32_t)count completion:(CompletionBlock)block;

/// 同步玩家信息
/// @param level 玩家等级
/// @param userName 玩家名字
/// @param userIcon 玩家头像
/// @param userGeo 玩家地理信息
/// @param block 同步结果
- (void)syncUserInfoWithLevel:(uint32_t)level userName:(NSString *)userName userIcon:(NSString *)userIcon userGeo:(NSString *)userGeo completion:(CompletionBlock)block;

/// 登出聊天室
- (void)logoutChat;

@end

NS_ASSUME_NONNULL_END
