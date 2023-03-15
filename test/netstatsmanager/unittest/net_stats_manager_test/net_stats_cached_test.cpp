/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <gtest/gtest.h>

#ifdef GTEST_API_
#define private public
#define protected public
#endif

#include "net_manager_constants.h"
#include "net_stats_cached.h"
#include "net_stats_history.h"

namespace OHOS {
namespace NetManagerStandard {
namespace {
using namespace testing::ext;
} // namespace

class NetStatsCachedTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp();
    void TearDown();
    static inline auto instance_ = std::make_shared<NetStatsCached>();
};

void NetStatsCachedTest::SetUpTestCase() {}

void NetStatsCachedTest::TearDownTestCase() {}

void NetStatsCachedTest::SetUp() {}

void NetStatsCachedTest::TearDown() {}

HWTEST_F(NetStatsCachedTest, CacheUidStatsTest001, TestSize.Level1)
{
    instance_->CacheUidStats();
    auto ret = instance_->CheckUidStor();
    EXPECT_FALSE(ret);
    ret = instance_->CheckIfaceStor();
    EXPECT_FALSE(ret);
    NetStatsInfo info;
    instance_->stats_.PushUidStats(info);
    instance_->stats_.PushIfaceStats(info);
    EXPECT_TRUE(instance_->stats_.GetUidStatsInfo().empty());
    EXPECT_TRUE(instance_->stats_.GetIfaceStatsInfo().empty());
    EXPECT_EQ(instance_->stats_.GetCurrentUidStats(), static_cast<uint64_t>(0));
    EXPECT_EQ(instance_->stats_.GetCurrentIfaceStats(), static_cast<uint64_t>(0));
    instance_->stats_.ResetUidStats();
    instance_->stats_.ResetIfaceStats();
    EXPECT_TRUE(instance_->stats_.GetUidStatsInfo().empty());
    EXPECT_TRUE(instance_->stats_.GetIfaceStatsInfo().empty());
    EXPECT_EQ(instance_->stats_.GetCurrentUidStats(), static_cast<uint64_t>(0));
    EXPECT_EQ(instance_->stats_.GetCurrentIfaceStats(), static_cast<uint64_t>(0));
    instance_->CacheStats();
}

HWTEST_F(NetStatsCachedTest, StartCachedTest001, TestSize.Level1)
{
    instance_->StartCached();
    std::vector<NetStatsInfo> allInfo;
    int32_t uid = 4800;
    int32_t start = 1;
    int32_t end = 10;
    auto history = std::make_unique<NetStatsHistory>();
    int32_t ret = history->GetHistory(allInfo, uid, start, end);
    EXPECT_EQ(ret, NETMANAGER_SUCCESS);
    instance_->GetUidStatsCached(allInfo);
    instance_->GetIfaceStatsCached(allInfo);
    instance_->CacheIfaceStats();
    uint32_t threshold = 100;
    instance_->SetCycleThreshold(threshold);
    instance_->ForceUpdateStats();
    instance_->Reset();
}
} // namespace NetManagerStandard
} // namespace OHOS