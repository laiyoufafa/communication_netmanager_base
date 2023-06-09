/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "iservice_registry.h"
#include "system_ability_definition.h"

#include "net_conn_callback_test.h"
#include "net_conn_client.h"
#include "net_conn_constants.h"
#include "net_detection_callback_test.h"
#include "net_mgr_log_wrapper.h"

namespace OHOS {
namespace NetManagerStandard {
constexpr int WAIT_TIME_SECOND_LONG = 5;
constexpr int WAIT_TIME_SECOND_NET_DETECTION = 2;
using namespace testing::ext;
class NetConnManagerTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp();
    void TearDown();
    sptr<NetLinkInfo> GetUpdateLinkInfoSample() const;

    sptr<NetConnCallbackTest> GetINetConnCallbackSample() const;

    sptr<NetDetectionCallbackTest> GetINetDetectionCallbackSample() const;

    void LogCapabilities(const std::list<sptr<NetHandle>> &netList) const;
    static sptr<INetConnService> GetProxy();
};

void NetConnManagerTest::SetUpTestCase() {}

void NetConnManagerTest::TearDownTestCase() {}

void NetConnManagerTest::SetUp() {}

void NetConnManagerTest::TearDown() {}

sptr<NetLinkInfo> NetConnManagerTest::GetUpdateLinkInfoSample() const
{
    sptr<NetLinkInfo> netLinkInfo = (std::make_unique<NetLinkInfo>()).release();
    netLinkInfo->ifaceName_ = "test";
    netLinkInfo->domain_ = "test";

    sptr<INetAddr> netAddr = (std::make_unique<INetAddr>()).release();
    netAddr->type_ = INetAddr::IPV4;
    netAddr->family_ = 0x10;
    netAddr->prefixlen_ = 0x17;
    netAddr->address_ = "192.168.2.0";
    netAddr->netMask_ = "192.255.255.255";
    netAddr->hostName_ = "netAddr";
    netLinkInfo->netAddrList_.push_back(*netAddr);

    sptr<INetAddr> dns = (std::make_unique<INetAddr>()).release();
    dns->type_ = INetAddr::IPV4;
    dns->family_ = 0x10;
    dns->prefixlen_ = 0x17;
    dns->address_ = "192.168.2.0";
    dns->netMask_ = "192.255.255.255";
    dns->hostName_ = "netAddr";
    netLinkInfo->dnsList_.push_back(*dns);

    sptr<Route> route = (std::make_unique<Route>()).release();
    route->iface_ = "iface0";
    route->destination_.type_ = INetAddr::IPV4;
    route->destination_.family_ = 0x10;
    route->destination_.prefixlen_ = 0x17;
    route->destination_.address_ = "192.168.2.0";
    route->destination_.netMask_ = "192.255.255.255";
    route->destination_.hostName_ = "netAddr";
    route->gateway_.type_ = INetAddr::IPV4;
    route->gateway_.family_ = 0x10;
    route->gateway_.prefixlen_ = 0x17;
    route->gateway_.address_ = "192.168.2.0";
    route->gateway_.netMask_ = "192.255.255.255";
    route->gateway_.hostName_ = "netAddr";
    netLinkInfo->routeList_.push_back(*route);

    netLinkInfo->mtu_ = 0x5DC;

    return netLinkInfo;
}

sptr<NetConnCallbackTest> NetConnManagerTest::GetINetConnCallbackSample() const
{
    sptr<NetConnCallbackTest> callback = (std::make_unique<NetConnCallbackTest>()).release();
    return callback;
}

sptr<NetDetectionCallbackTest> NetConnManagerTest::GetINetDetectionCallbackSample() const
{
    sptr<NetDetectionCallbackTest> detectionCallback = (std::make_unique<NetDetectionCallbackTest>()).release();
    return detectionCallback;
}

void NetConnManagerTest::LogCapabilities(const std::list<sptr<NetHandle>> &netList) const
{
    for (auto it : netList) {
        std::cout << "netid = " << it->GetNetId() << std::endl;
        NetAllCapabilities netAllCap;
        DelayedSingleton<NetConnClient>::GetInstance()->GetNetCapabilities(*it, netAllCap);
        std::cout << netAllCap.ToString("|") << std::endl;
    }
}

sptr<INetConnService> NetConnManagerTest::GetProxy()
{
    sptr<ISystemAbilityManager> systemAbilityMgr =
        SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    if (systemAbilityMgr == nullptr) {
        std::cout << "NetConnService Get ISystemAbilityManager failed ... " << std::endl;
        return nullptr;
    }

    sptr<IRemoteObject> remote = systemAbilityMgr->CheckSystemAbility(COMM_NET_CONN_MANAGER_SYS_ABILITY_ID);
    if (remote) {
        sptr<INetConnService> NetConnService = iface_cast<INetConnService>(remote);
        std::cout << "NetConnService Get COMM_NET_CONN_MANAGER_SYS_ABILITY_ID success ... " << std::endl;
        return NetConnService;
    } else {
        std::cout << "NetConnService Get COMM_NET_CONN_MANAGER_SYS_ABILITY_ID fail ... " << std::endl;
        return nullptr;
    }
}

/**
 * @tc.name: NetConnManager001
 * @tc.desc: Test NetConnManager SystemReady.
 * @tc.type: FUNC
 */
HWTEST_F(NetConnManagerTest, NetConnManager001, TestSize.Level1)
{
    int32_t result = DelayedSingleton<NetConnClient>::GetInstance()->SystemReady();
    ASSERT_TRUE(result == NetConnResultCode::NET_CONN_SUCCESS);
}

/**
 * @tc.name: NetConnManager002
 * @tc.desc: Test NetConnManager RegisterNetSupplier.
 * @tc.type: FUNC
 */
HWTEST_F(NetConnManagerTest, NetConnManager002, TestSize.Level1)
{
    NetBearType bearerType = BEARER_CELLULAR;
    std::set<NetCap> netCaps {NET_CAPABILITY_INTERNET, NET_CAPABILITY_MMS};
    std::string ident = "ident01";
    uint32_t supplierId = 0;
    int32_t result = DelayedSingleton<NetConnClient>::GetInstance()->RegisterNetSupplier(
        bearerType, ident, netCaps, supplierId);
    ASSERT_TRUE(result == NetConnResultCode::NET_CONN_SUCCESS);
}

/**
 * @tc.name: NetConnManager003
 * @tc.desc: Test NetConnManager UnregisterNetSupplier.
 * @tc.type: FUNC
 */
HWTEST_F(NetConnManagerTest, NetConnManager003, TestSize.Level1)
{
    NetBearType bearerType = BEARER_CELLULAR;
    std::set<NetCap> netCaps {NET_CAPABILITY_INTERNET, NET_CAPABILITY_MMS};
    std::string ident = "ident02";
    uint32_t supplierId = 0;
    int32_t result = DelayedSingleton<NetConnClient>::GetInstance()->RegisterNetSupplier(
        bearerType, ident, netCaps, supplierId);
    ASSERT_TRUE(result == NetConnResultCode::NET_CONN_SUCCESS);

    result = DelayedSingleton<NetConnClient>::GetInstance()->UnregisterNetSupplier(supplierId);
    ASSERT_TRUE(result == NetConnResultCode::NET_CONN_SUCCESS);
}

/**
 * @tc.name: NetConnManager004
 * @tc.desc: Test NetConnManager UpdateNetSupplierInfo.
 * @tc.type: FUNC
 */

HWTEST_F(NetConnManagerTest, NetConnManager004, TestSize.Level1)
{
    NetBearType bearerType = BEARER_CELLULAR;
    std::set<NetCap> netCaps {NET_CAPABILITY_INTERNET, NET_CAPABILITY_MMS};
    std::string ident = "ident03";
    uint32_t supplierId = 0;
    int32_t result = DelayedSingleton<NetConnClient>::GetInstance()->RegisterNetSupplier(
        bearerType, ident, netCaps, supplierId);
    ASSERT_TRUE(result == NetConnResultCode::NET_CONN_SUCCESS);

    sptr<NetSupplierInfo> netSupplierInfo = new NetSupplierInfo;
    netSupplierInfo->isAvailable_ = true;
    netSupplierInfo->isRoaming_ = true;
    netSupplierInfo->strength_ = 0x64;
    netSupplierInfo->frequency_ = 0x10;
    result = DelayedSingleton<NetConnClient>::GetInstance()->UpdateNetSupplierInfo(supplierId, netSupplierInfo);
    ASSERT_TRUE(result == NetConnResultCode::NET_CONN_SUCCESS);
}

/**
 * @tc.name: NetConnManager005
 * @tc.desc: Test NetConnManager UpdateNetLinkInfo.
 * @tc.type: FUNC
 */
HWTEST_F(NetConnManagerTest, NetConnManager005, TestSize.Level1)
{
    NetBearType bearerType = BEARER_CELLULAR;
    std::set<NetCap> netCaps {NET_CAPABILITY_INTERNET, NET_CAPABILITY_MMS};

    std::string ident = "ident04";
    uint32_t supplierId = 0;
    int32_t result = DelayedSingleton<NetConnClient>::GetInstance()->RegisterNetSupplier(
        bearerType, ident, netCaps, supplierId);
    ASSERT_TRUE(result == NetConnResultCode::NET_CONN_SUCCESS);

    sptr<NetLinkInfo> netLinkInfo = GetUpdateLinkInfoSample();
    result = DelayedSingleton<NetConnClient>::GetInstance()->UpdateNetLinkInfo(supplierId, netLinkInfo);
    ASSERT_TRUE(result == NetConnResultCode::NET_CONN_SUCCESS);
}

/**
 * @tc.name: NetConnManager006
 * @tc.desc: Test NetConnManager RegisterNetConnCallback.
 * @tc.type: FUNC
 */
HWTEST_F(NetConnManagerTest, NetConnManager006, TestSize.Level1)
{
    NetBearType bearerType = BEARER_CELLULAR;
    std::set<NetCap> netCaps {NET_CAPABILITY_INTERNET};

    std::string ident = "ident";
    uint32_t supplierId = 0;
    int32_t result = DelayedSingleton<NetConnClient>::GetInstance()->RegisterNetSupplier(
        bearerType, ident, netCaps, supplierId);
    ASSERT_TRUE(result == NetConnResultCode::NET_CONN_SUCCESS);

    sptr<NetSpecifier> netSpecifier = (std::make_unique<NetSpecifier>()).release();
    netSpecifier->ident_ = ident;
    netSpecifier->SetCapabilities(netCaps);
    sptr<NetConnCallbackTest> callback = GetINetConnCallbackSample();
    result = DelayedSingleton<NetConnClient>::GetInstance()->RegisterNetConnCallback(callback);
    if (result == NetConnResultCode::NET_CONN_SUCCESS) {
        sptr<INetConnService> proxy = NetConnManagerTest::GetProxy();
        if (proxy == nullptr) {
            return;
        }
        proxy->UpdateNetStateForTest(netSpecifier, 1);
        callback->WaitFor(WAIT_TIME_SECOND_LONG);
        int32_t netState = callback->GetNetState();
        std::cout << "NetConnManager006 RegisterNetConnCallback netState:" << netState << std::endl;
    } else {
        std::cout << "NetConnManager006 RegisterNetConnCallback return fail" << std::endl;
    }

    result = DelayedSingleton<NetConnClient>::GetInstance()->UnregisterNetConnCallback(callback);
    ASSERT_TRUE(result == NetConnResultCode::NET_CONN_SUCCESS);
}

/**
 * @tc.name: NetConnManager008
 * @tc.desc: Test NetConnManager RegisterNetDetectionCallback.
 * @tc.type: FUNC
 */
HWTEST_F(NetConnManagerTest, NetConnManager008, TestSize.Level1)
{
    auto client = DelayedSingleton<NetConnClient>::GetInstance();
    sptr<INetConnService> proxy = NetConnManagerTest::GetProxy();
    if (proxy == nullptr) {
        return;
    }

    std::list<sptr<NetHandle>> netList;
    client->GetAllNets(netList);
    sptr<NetDetectionCallbackTest> detectionCallback = GetINetDetectionCallbackSample();
    if (detectionCallback == nullptr) {
        return;
    }

    std::cout << "netIdList size:" << netList.size() << std::endl;
    int32_t result = 0;
    int32_t netId = 0;
    for (sptr<NetHandle> netHandle : netList) {
        NetAllCapabilities netAllCap;
        client->GetNetCapabilities(*netHandle, netAllCap);
        std::cout << netAllCap.ToString("|") << std::endl;
        if (netAllCap.bearerTypes_.find(BEARER_WIFI) == netAllCap.bearerTypes_.end()) {
            continue;
        }
        netId = netHandle->GetNetId();
        result = proxy->RegisterNetDetectionCallback(netId, detectionCallback);
        ASSERT_TRUE(result == NetConnResultCode::NET_CONN_SUCCESS);
        std::cout << "TestRegisterNetDetectionCallback netId:" << netId << " result:" << result << std::endl;
        result = client->NetDetection(*netHandle);
        ASSERT_TRUE(result == NetConnResultCode::NET_CONN_SUCCESS);
        std::cout << "TestNetDetection result:" << result << std::endl;
        detectionCallback->WaitFor(WAIT_TIME_SECOND_NET_DETECTION);
        int32_t netDetectionRet = detectionCallback->GetNetDetectionResult();
        std::cout << "RegisterNetDetectionCallback netDetectionRet:" << netDetectionRet << std::endl;
        std::string urlRedirect = detectionCallback->GetUrlRedirect();
        std::cout << "RegisterNetDetectionCallback urlRedirect:" << urlRedirect << std::endl;

        result = proxy->UnRegisterNetDetectionCallback(netId, detectionCallback);
        ASSERT_TRUE(result == NetConnResultCode::NET_CONN_SUCCESS);
        std::cout << "TestUnRegisterNetDetectionCallback result:" << result << std::endl;
        result = client->NetDetection(*netHandle);
        ASSERT_TRUE(result == NetConnResultCode::NET_CONN_SUCCESS);
        std::cout << "TestNetDetection result:" << result << std::endl;
        detectionCallback->WaitFor(WAIT_TIME_SECOND_NET_DETECTION);
        netDetectionRet = detectionCallback->GetNetDetectionResult();
        ASSERT_TRUE(netDetectionRet == static_cast<int32_t>(NetDetectionResultCode::NET_DETECTION_FAIL));
        std::cout << "RegisterNetDetectionCallback netDetectionRet:" << netDetectionRet << std::endl;
        urlRedirect = detectionCallback->GetUrlRedirect();
        ASSERT_TRUE(urlRedirect.empty());
        std::cout << "RegisterNetDetectionCallback urlRedirect:" << urlRedirect << std::endl;
    }
}

/**
 * @tc.name: NetConnManager009
 * @tc.desc: Test NetConnManager RegisterNetDetectionCallback.
 * @tc.type: FUNC
 */
HWTEST_F(NetConnManagerTest, NetConnManager009, TestSize.Level1)
{
    sptr<INetConnService> proxy = NetConnManagerTest::GetProxy();
    if (proxy == nullptr) {
        return;
    }

    sptr<NetDetectionCallbackTest> detectionCallback = GetINetDetectionCallbackSample();
    if (detectionCallback == nullptr) {
        return;
    }

    const int32_t netIdError = -1;
    int32_t result = 0;
    result = proxy->RegisterNetDetectionCallback(netIdError, detectionCallback);
    std::cout << "TestRegisterNetDetectionCallback netIdError:" << netIdError << " result:" << result << std::endl;
    ASSERT_TRUE(result != NetConnResultCode::NET_CONN_SUCCESS);
    result = proxy->UnRegisterNetDetectionCallback(netIdError, detectionCallback);
    std::cout << "TestUnRegisterNetDetectionCallback netIdError:" << netIdError << " result:" << result
        << std::endl;
    ASSERT_TRUE(result != NetConnResultCode::NET_CONN_SUCCESS);
    NetHandle netHError(netIdError);
    result = DelayedSingleton<NetConnClient>::GetInstance()->NetDetection(netHError);
    std::cout << "TestNetDetection netIdError:" << netIdError << " result:" << result << std::endl;
    ASSERT_TRUE(result != NetConnResultCode::NET_CONN_SUCCESS);

    result = proxy->RegisterNetDetectionCallback(netIdError, nullptr);
    std::cout << "TestRegisterNetDetectionCallback nullptr result:" << result << std::endl;
    ASSERT_TRUE(result != NetConnResultCode::NET_CONN_SUCCESS);
    result = proxy->UnRegisterNetDetectionCallback(netIdError, nullptr);
    std::cout << "TestUnRegisterNetDetectionCallback nullptr result:" << result << std::endl;
    ASSERT_TRUE(result != NetConnResultCode::NET_CONN_SUCCESS);
}

/**
 * @tc.name: NetConnManager011
 * @tc.desc: Test NetConnManager GetSpecificNet.
 * @tc.type: FUNC
 */
HWTEST_F(NetConnManagerTest, NetConnManager011, TestSize.Level1)
{
    NetBearType bearerType = BEARER_CELLULAR;
    std::set<NetCap> netCaps {NET_CAPABILITY_INTERNET, NET_CAPABILITY_MMS};

    std::string ident = "ident";
    uint32_t supplierId1 = 0;
    int32_t result = DelayedSingleton<NetConnClient>::GetInstance()->RegisterNetSupplier(bearerType,
        ident, netCaps, supplierId1);
    ASSERT_TRUE(result == NetConnResultCode::NET_CONN_SUCCESS);
    std::cout << "supplierId1 : " << supplierId1 << std::endl;

    ident = "ident2";
    uint32_t supplierId2 = 0;
    result = DelayedSingleton<NetConnClient>::GetInstance()->RegisterNetSupplier(bearerType,
        ident, netCaps, supplierId2);
    ASSERT_TRUE(result == NetConnResultCode::NET_CONN_SUCCESS);
    std::cout << "supplierId2 : " << supplierId2 << std::endl;

    ident = "ident3";
    uint32_t supplierId3 = 0;
    result = DelayedSingleton<NetConnClient>::GetInstance()->RegisterNetSupplier(bearerType,
        ident, netCaps, supplierId3);
    ASSERT_TRUE(result == NetConnResultCode::NET_CONN_SUCCESS);
    std::cout << "supplierId3 : " << supplierId3 << std::endl;

    sptr<INetConnService> proxy = NetConnManagerTest::GetProxy();
    if (proxy == nullptr) {
        return;
    }
    std::list<int32_t> netIdList;
    result = proxy->GetSpecificNet(bearerType, netIdList);
    ASSERT_TRUE(result == NetConnResultCode::NET_CONN_SUCCESS);
    for (auto it : netIdList) {
        std::cout << "netid = " << it << std::endl;
    }
}

/**
 * @tc.name: NetConnManager012
 * @tc.desc: Test NetConnManager GetAllNets.
 * @tc.type: FUNC
 */
HWTEST_F(NetConnManagerTest, NetConnManager012, TestSize.Level1)
{
    NetBearType bearerTypeCel = BEARER_CELLULAR;
    NetBearType bearerTypeEth = BEARER_ETHERNET;
    std::set<NetCap> netCaps {NET_CAPABILITY_INTERNET};

    std::string ident = "ident";
    uint32_t supplierId1 = 0;
    int32_t result = DelayedSingleton<NetConnClient>::GetInstance()->RegisterNetSupplier(bearerTypeCel,
        ident, netCaps, supplierId1);
    ASSERT_TRUE(result == NetConnResultCode::NET_CONN_SUCCESS);
    std::cout << "supplierId1 : " << supplierId1 << std::endl;

    ident = "ident2";
    uint32_t supplierId2 = 0;
    result = DelayedSingleton<NetConnClient>::GetInstance()->RegisterNetSupplier(bearerTypeEth,
        ident, netCaps, supplierId2);
    ASSERT_TRUE(result == NetConnResultCode::NET_CONN_SUCCESS);
    std::cout << "supplierId2 : " << supplierId2 << std::endl;

    ident = "ident3";
    uint32_t supplierId3 = 0;
    result = DelayedSingleton<NetConnClient>::GetInstance()->RegisterNetSupplier(bearerTypeCel,
        ident, netCaps, supplierId3);
    ASSERT_TRUE(result == NetConnResultCode::NET_CONN_SUCCESS);
    std::cout << "supplierId3 : " << supplierId3 << std::endl;

    std::list<sptr<NetHandle>> netList;
    result = DelayedSingleton<NetConnClient>::GetInstance()->GetAllNets(netList);
    ASSERT_TRUE(result == NetConnResultCode::NET_CONN_SUCCESS);
    for (auto it : netList) {
        std::cout << "netid = " << it->GetNetId() << std::endl;
    }
}

/**
 * @tc.name: NetConnManager013
 * @tc.desc: Test NetConnManager GetNetCapabilities.
 * @tc.type: FUNC
 */
HWTEST_F(NetConnManagerTest, NetConnManager013, TestSize.Level1)
{
    NetBearType bearerType = BEARER_CELLULAR;
    std::set<NetCap> netCaps {NET_CAPABILITY_INTERNET, NET_CAPABILITY_MMS};

    std::string ident = "ident";
    uint32_t supplierId = 0;
    int32_t result = DelayedSingleton<NetConnClient>::GetInstance()->RegisterNetSupplier(
        bearerType, ident, netCaps, supplierId);
    ASSERT_TRUE(result == NetConnResultCode::NET_CONN_SUCCESS);
    std::cout << "supplierId : " << supplierId << std::endl;

    std::list<sptr<NetHandle>> netList;
    result = DelayedSingleton<NetConnClient>::GetInstance()->GetAllNets(netList);
    ASSERT_TRUE(result == NetConnResultCode::NET_CONN_SUCCESS);
    LogCapabilities(netList);
}

/**
 * @tc.name: NetConnManager014
 * @tc.desc: Test NetConnManager GetConnectionProperties.
 * @tc.type: FUNC
 */
HWTEST_F(NetConnManagerTest, NetConnManager014, TestSize.Level1)
{
    NetBearType bearerType = BEARER_CELLULAR;
    std::set<NetCap> netCaps {NET_CAPABILITY_INTERNET, NET_CAPABILITY_MMS};

    std::string ident = "ident";
    uint32_t supplierId = 0;
    int32_t result = DelayedSingleton<NetConnClient>::GetInstance()->RegisterNetSupplier(bearerType,
        ident, netCaps, supplierId);
    ASSERT_TRUE(result == NetConnResultCode::NET_CONN_SUCCESS);
    std::cout << "supplierId : " << supplierId << std::endl;

    sptr<NetLinkInfo> netLinkInfo = GetUpdateLinkInfoSample();
    result = DelayedSingleton<NetConnClient>::GetInstance()->UpdateNetLinkInfo(supplierId, netLinkInfo);
    ASSERT_TRUE(result == NetConnResultCode::NET_CONN_SUCCESS);

    NetLinkInfo info;
    NetHandle netHandle(100);
    result = DelayedSingleton<NetConnClient>::GetInstance()->GetConnectionProperties(netHandle, info);
    std::cout << "result = " << result << std::endl;
    ASSERT_TRUE(result == NetConnResultCode::NET_CONN_SUCCESS);
    std::cout << info.ToString("\n") << std::endl;
}
} // namespace NetManagerStandard
} // namespace OHOS
