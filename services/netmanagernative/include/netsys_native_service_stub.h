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
#ifndef NETSYS_NATIVE_SERVICE_STUB_H__
#define NETSYS_NATIVE_SERVICE_STUB_H__

#include <map>

#include "i_netsys_service.h"
#include "iremote_stub.h"

namespace OHOS {
namespace NetsysNative {
class NetsysNativeServiceStub : public IRemoteStub<INetsysService> {
public:
    NetsysNativeServiceStub();
    ~NetsysNativeServiceStub() = default;
    int32_t OnRemoteRequest(uint32_t code, MessageParcel &data, MessageParcel &reply, MessageOption &option) override;
    int32_t NetsysFreeAddrinfo(struct addrinfo *aihead) ;

private:
    using ServiceInterface = int32_t (NetsysNativeServiceStub::*)(MessageParcel &data, MessageParcel &reply);
    std::map<uint32_t, ServiceInterface> opToInterfaceMap_;

    int32_t CmdEchoServer(MessageParcel &data, MessageParcel &reply);
    int32_t CmdSetResolverConfigParcel(MessageParcel &data, MessageParcel &reply);
    int32_t CmdSetResolverConfig(MessageParcel &data, MessageParcel &reply);
    int32_t CmdGetResolverConfig(MessageParcel &data, MessageParcel &reply);
    int32_t CmdCreateNetworkCache(MessageParcel &data, MessageParcel &reply);
    int32_t CmdFlushNetworkCache(MessageParcel &data, MessageParcel &reply);
    int32_t CmdDestroyNetworkCache(MessageParcel &data, MessageParcel &reply);
    int32_t CmdGetaddrinfo(MessageParcel &data, MessageParcel &reply);
    int32_t CmdInterfaceSetMtu(MessageParcel &data, MessageParcel &reply);
    int32_t CmdInterfaceGetMtu(MessageParcel &data, MessageParcel &reply);

    int32_t CmdRegisterNotifyCallback(MessageParcel &data, MessageParcel &reply);

    int32_t CmdNetworkAddRoute(MessageParcel &data, MessageParcel &reply);
    int32_t CmdNetworkRemoveRoute(MessageParcel &data, MessageParcel &reply);
    int32_t CmdNetworkAddRouteParcel(MessageParcel &data, MessageParcel &reply);
    int32_t CmdNetworkRemoveRouteParcel(MessageParcel &data, MessageParcel &reply);
    int32_t CmdNetworkSetDefault(MessageParcel &data, MessageParcel &reply);
    int32_t CmdNetworkGetDefault(MessageParcel &data, MessageParcel &reply);
    int32_t CmdNetworkClearDefault(MessageParcel &data, MessageParcel &reply);
    int32_t CmdGetProcSysNet(MessageParcel &data, MessageParcel &reply);
    int32_t CmdSetProcSysNet(MessageParcel &data, MessageParcel &reply);
    int32_t CmdNetworkCreatePhysical(MessageParcel &data, MessageParcel &reply);
    int32_t CmdInterfaceAddAddress(MessageParcel &data, MessageParcel &reply);
    int32_t CmdInterfaceDelAddress(MessageParcel &data, MessageParcel &reply);
    int32_t CmdNetworkAddInterface(MessageParcel &data, MessageParcel &reply);
    int32_t CmdNetworkRemoveInterface(MessageParcel &data, MessageParcel &reply);
    int32_t CmdNetworkDestroy(MessageParcel &data, MessageParcel &reply);
    int32_t CmdGetFwmarkForNetwork(MessageParcel &data, MessageParcel &reply);
    int32_t CmdInterfaceSetConfig(MessageParcel &data, MessageParcel &reply);
    int32_t CmdInterfaceGetConfig(MessageParcel &data, MessageParcel &reply);
    int32_t CmdStartDhcpClient(MessageParcel &data, MessageParcel &reply);
    int32_t CmdStopDhcpClient(MessageParcel &data, MessageParcel &reply);
    int32_t CmdStartDhcpService(MessageParcel &data, MessageParcel &reply);
    int32_t CmdStopDhcpService(MessageParcel &data, MessageParcel &reply);
};
} // namespace NetsysNative
} // namespace OHOS
#endif // NETSYS_NATIVE_SERVICE_STUB_H__