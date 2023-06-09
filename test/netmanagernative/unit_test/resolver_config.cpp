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
#include <iostream>
#include <memory>
#include <securec.h>

#include "i_netsys_service.h"
#include "iservice_registry.h"
#include "netsys_native_service_proxy.h"
#include "netnative_log_wrapper.h"
#include "system_ability_definition.h"
#include "dnsresolv.h"
#include "test.h"
#include "test_notify_callback.h"
using namespace OHOS::nmd;
using namespace OHOS;
using namespace OHOS::NetsysNative;

namespace {
OHOS::sptr<OHOS::NetsysNative::INotifyCallback> callback_ =
    (std::make_unique<OHOS::NetsysNative::TestNotifyCallback>()).release();
sptr<INetsysService> GetProxyK()
{
    NETNATIVE_LOGE("Get samgr >>>>>>>>>>>>>>>>>>>>>>>>>>");
    auto samgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    NETNATIVE_LOGE("Get samgr %{public}p", samgr.GetRefPtr());
    std::cout << "Get samgr  "<< samgr.GetRefPtr() << std::endl;

    auto remote = samgr->GetSystemAbility(COMM_NETSYS_NATIVE_SYS_ABILITY_ID);
    NETNATIVE_LOGE("Get remote %{public}p", remote.GetRefPtr());
    std::cout << "Get remote "<< remote.GetRefPtr() << std::endl;

    auto proxy = iface_cast<NetsysNative::INetsysService>(remote);
    if (proxy != nullptr) {
        NETNATIVE_LOGE("Get proxy %{public}p", proxy.GetRefPtr());
        std::cout << "Get proxy " << proxy.GetRefPtr() << std::endl;
    } else {
        std::cout << "Get proxy nullptr" << std::endl;
    }
    
    return proxy;
}

auto netsysServiceK_ = GetProxyK();
}

namespace {
void freeNetsysAddrInfo(struct addrinfo *aihead)
{
    struct addrinfo *ai, *ainext ;
    for (ai = aihead ; ai != nullptr ; ai = ainext) {
        if (ai->ai_addr != nullptr)
            free(ai->ai_addr);

        if (ai->ai_canonname != nullptr)
            free(ai->ai_canonname) ;
        ainext = ai->ai_next ;
        free(ai);
    }
}
}

void TestSetResolverConfig()
{
    nmd::DnsresolverParams param0 = {
        0, 0, 1, {"8.8.8.8", "114.114.114.114"}, {"baidu.com", "sohu.com"}};
    nmd::DnsresolverParams param1 = {
        1, 0, 1, {"8.8.8.8", "114.114.114.114"}, {"yahoo.com", "163.com"}};
    int  ret = -1;
    ret = netsysServiceK_->CreateNetworkCache(0);
    NETNATIVE_LOGE("NETSYS: CreateNetworkCache0   ret=%{public}d", ret);
    ret = netsysServiceK_->CreateNetworkCache(1);
    NETNATIVE_LOGE("NETSYS: CreateNetworkCache1   ret=%{public}d", ret);
    ret = netsysServiceK_->SetResolverConfig(param0);
    NETNATIVE_LOGE("NETSYS: SetResolverConfig0   ret=%{public}d", ret);
    ret = netsysServiceK_->SetResolverConfig(param1);
    NETNATIVE_LOGE("NETSYS: SetResolverConfig1   ret=%{public}d", ret);
}

void TestGetResolverConfig()
{
    int  ret = -1;
    std::vector<std::string> servers;
    std::vector<std::string> domains;
    DnsResParams  dnsParam;
    int  num = 3;
    for (int i = 0; i < num; i++) {
        ret = netsysServiceK_->GetResolverConfig(i, servers, domains, dnsParam);
        NETNATIVE_LOGE("NETSYS: getResolverConfig   ret=%{public}d, iii=%{public}d", ret, i);
        NETNATIVE_LOGE("NETSYS:  server size %{public}d, domains  size %{public}d",
            static_cast<int32_t>(servers.size()), static_cast<int32_t>(domains.size()));
        NETNATIVE_LOGE("NETSYS:  TimeOut %{public}d, retryCount  %{public}d", dnsParam.baseTimeoutMsec,
            dnsParam.retryCount);
        for (auto item:servers) {
            std::cout<<"Server:" <<item.c_str()<<std::endl;
        }
        for (auto iter:domains) {
            std::cout<<"Domains:" <<iter.c_str()<<std::endl;
        }
    }
}

void  TestInterfaceGetCfg()
{
    std::cout<<"hello"<<std::endl;
}

void TestCreateNetworkCache()
{
    int  ret = -1;
    ret = netsysServiceK_->CreateNetworkCache(0);
    NETNATIVE_LOGE("NETSYS: CreateNetworkCache0   ret=%{public}d", ret);
    ret = netsysServiceK_->CreateNetworkCache(1);
    NETNATIVE_LOGE("NETSYS: CreateNetworkCache1   ret=%{public}d", ret);
}

void TestFlushNetworkCache()
{
    int ret = -1 ;
    ret = netsysServiceK_->FlushNetworkCache(0);
    NETNATIVE_LOGE("NETSYS: FlushNetworkCache0   ret=%{public}d", ret);
    ret = netsysServiceK_->FlushNetworkCache(1);
    NETNATIVE_LOGE("NETSYS: FlushNetworkCache1   ret=%{public}d", ret);
}

void TestDestroyNetworkCache()
{
    int ret = -1;
    ret = netsysServiceK_->DestroyNetworkCache(1);
    NETNATIVE_LOGE("NETSYS: DestroyNetworkCache1   ret=%{public}d", ret);
}

void TestGetaddrinfo()
{
    char  hostName[OHOS::nmd::MAX_NAME_LEN];
    struct addrinfo hints;
    struct addrinfo *res1;
    struct addrinfo *resP1;
    int ret;
    bzero(&hints, sizeof(addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_protocol = 0;
    int copyRet = strncpy_s(hostName, OHOS::nmd::MAX_NAME_LEN, "www.ifeng.com", strlen("www.ifeng.com") + 1);
    NETNATIVE_LOGI("copyRet = %{public}d", copyRet);
    ret = netsysServiceK_->Getaddrinfo(hostName, NULL, &hints, &res1, 0);
    NETNATIVE_LOGE("NETSYS: Getaddrinfo   ret=%{public}d,HostName  %{public}s", ret, hostName);
    if (res1 == nullptr) {
        NETNATIVE_LOGE("res1 res1  is nullptr");
    }

    int  k = 0;
    for (resP1 = res1; resP1 != nullptr; resP1 = resP1->ai_next) {
        char host[1024] = {0};
        NETNATIVE_LOGE("LOOP kkkk  start k=%{public}d \n", k);
        NETNATIVE_LOGE("LOOP ai_addrlen %{public}d\n", resP1->ai_addrlen);
        k++ ;
        ret = getnameinfo(resP1->ai_addr, resP1->ai_addrlen, host, sizeof(host), NULL, 0, NI_NUMERICHOST);
        if (ret != 0) {
            NETNATIVE_LOGE("getnameinfo: %{public}s\n", gai_strerror(ret));
        } else {
            NETNATIVE_LOGE("IPIP1:  %{public}s,HOSTNAME %{public}s", host, hostName);
        }
    }

    printf("overover\n");
    if (res1 != nullptr) {
        NETNATIVE_LOGI("TestGetaddrinfo:: end freeNetsysAddrInfo");
        freeNetsysAddrInfo(res1);
    }
}

void TestInterfaceSetMtu()
{
    int ret = -1;
    std::string  ifName = "eth0";
    int mtu = 1200;
    std::cout<<"begin to GetMtu"<<std::endl;
    ret = netsysServiceK_->InterfaceGetMtu(ifName);
    NETNATIVE_LOGE("NETSYS: GetMtu   ago  ret=%{public}d", ret);
    std::cout<<"begin to SetMtu"<<std::endl;
    ret = netsysServiceK_->InterfaceSetMtu(ifName, mtu);
    NETNATIVE_LOGE("NETSYS: SetMtu   ret=%{public}d", ret);
    std::cout<<"begin22 to GetMtu"<<std::endl;
    ret =  netsysServiceK_->InterfaceGetMtu(ifName);
    NETNATIVE_LOGE("NETSYS: GetMtu   ret=%{public}d", ret);
}

void TestInterfaceGetMtu()
{
    int ret = -1;
    std::string  ifName = "eth0";
    int  mtu = 1200;
    std::cout<<"begin to GetMtu"<<std::endl;
    ret = netsysServiceK_->InterfaceGetMtu(ifName);
    NETNATIVE_LOGE("NETSYS: GetMtu   ago  ret=%{public}d", ret);
    std::cout<<"begin to SetMtu"<<std::endl;
    ret = netsysServiceK_->InterfaceSetMtu(ifName, mtu);
    NETNATIVE_LOGE("NETSYS: SetMtu   ret=%{public}d", ret);
    std::cout<<"begin22 to GetMtu"<<std::endl;
    ret = netsysServiceK_->InterfaceGetMtu(ifName);
    NETNATIVE_LOGE("NETSYS: GetMtu   ret=%{public}d", ret);
}

void TestRegisterNotifyCallback()
{
    if (netsysServiceK_ == nullptr || callback_ == nullptr) {
        std::cout << "TestRegisterNotifyCallback netsysServiceK_ or callback is nullptr" << std::endl;
        return;
    }
    std::cout << "enter TestRegisterNotifyCallback " << std::endl;
    int32_t ret = netsysServiceK_->RegisterNotifyCallback(callback_);
    std::cout << "TestRegisterNotifyCallback ret:" << ret << std::endl;

    return;
}

