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

#include "net_link_info.h"
#include "net_mgr_log_wrapper.h"

namespace OHOS {
namespace NetManagerStandard {
bool NetLinkInfo::Marshalling(Parcel &parcel) const
{
    if (!parcel.WriteString(ifaceName_)) {
        return false;
    }
    if (!parcel.WriteString(domain_)) {
        return false;
    }
    if (!parcel.WriteUint32(netAddrList_.size())) {
        return false;
    }
    for (auto it = netAddrList_.begin(); it != netAddrList_.end(); it++) {
        if (!it->Marshalling(parcel)) {
            NETMGR_LOG_E("write net address to parcel failed");
            return false;
        }
    }
    if (!parcel.WriteUint32(dnsList_.size())) {
        return false;
    }
    for (auto it = dnsList_.begin(); it != dnsList_.end(); it++) {
        if (!it->Marshalling(parcel)) {
            NETMGR_LOG_E("write dns to parcel failed");
            return false;
        }
    }
    if (!parcel.WriteUint32(routeList_.size())) {
        return false;
    }
    for (auto it = routeList_.begin(); it != routeList_.end(); it++) {
        if (!it->Marshalling(parcel)) {
            NETMGR_LOG_E("write route to parcel failed");
            return false;
        }
    }
    if (!parcel.WriteUint16(mtu_)) {
        return false;
    }
    if (!parcel.WriteString(tcpBufferSizes_)) {
        return false;
    }
    return true;
}

sptr<NetLinkInfo> NetLinkInfo::Unmarshalling(Parcel &parcel)
{
    sptr<NetLinkInfo> ptr = (std::make_unique<NetLinkInfo>()).release();
    if (ptr == nullptr) {
        return nullptr;
    }
    uint32_t size = 0;
    if (!parcel.ReadString(ptr->ifaceName_) || !parcel.ReadString(ptr->domain_) || !parcel.ReadUint32(size)) {
        return nullptr;
    }
    sptr<INetAddr> netAddr;
    for (uint32_t i = 0; i < size; i++) {
        netAddr = INetAddr::Unmarshalling(parcel);
        if (netAddr == nullptr) {
            NETMGR_LOG_E("INetAddr::Unmarshalling(parcel) is null");
            return nullptr;
        }
        ptr->netAddrList_.push_back(*netAddr);
    }
    if (!parcel.ReadUint32(size)) {
        return nullptr;
    }
    for (uint32_t i = 0; i < size; i++) {
        netAddr = INetAddr::Unmarshalling(parcel);
        if (netAddr == nullptr) {
            NETMGR_LOG_E("INetAddr::Unmarshalling(parcel) is null");
            return nullptr;
        }
        ptr->dnsList_.push_back(*netAddr);
    }
    if (!parcel.ReadUint32(size)) {
        return nullptr;
    }
    sptr<Route> route;
    for (uint32_t i = 0; i < size; i++) {
        route = Route::Unmarshalling(parcel);
        if (route == nullptr) {
            NETMGR_LOG_E("Route::Unmarshalling(parcel) is null");
            return nullptr;
        }
        ptr->routeList_.push_back(*route);
    }
    if (!parcel.ReadUint16(ptr->mtu_) || !parcel.ReadString(ptr->tcpBufferSizes_)) {
        return nullptr;
    }
    return ptr;
}

bool NetLinkInfo::Marshalling(Parcel &parcel, const sptr<NetLinkInfo> &object)
{
    if (object == nullptr) {
        NETMGR_LOG_E("NetLinkInfo object ptr is nullptr");
        return false;
    }
    if (!parcel.WriteString(object->ifaceName_)) {
        return false;
    }
    if (!parcel.WriteString(object->domain_)) {
        return false;
    }
    if (!parcel.WriteUint32(object->netAddrList_.size())) {
        return false;
    }
    for (auto it = object->netAddrList_.begin(); it != object->netAddrList_.end(); it++) {
        if (!it->Marshalling(parcel)) {
            NETMGR_LOG_E("write objects net address to parcel failed");
            return false;
        }
    }
    if (!parcel.WriteUint32(object->dnsList_.size())) {
        return false;
    }
    for (auto it = object->dnsList_.begin(); it != object->dnsList_.end(); it++) {
        if (!it->Marshalling(parcel)) {
            NETMGR_LOG_E("write objects dns to parcel failed");
            return false;
        }
    }
    if (!parcel.WriteUint32(object->routeList_.size())) {
        return false;
    }
    for (auto it = object->routeList_.begin(); it != object->routeList_.end(); it++) {
        if (!it->Marshalling(parcel)) {
            NETMGR_LOG_E("write objects route to parcel failed");
            return false;
        }
    }
    if (!parcel.WriteUint16(object->mtu_)) {
        return false;
    }
    if (!parcel.WriteString(object->tcpBufferSizes_)) {
        return false;
    }
    return true;
}

void NetLinkInfo::Initialize()
{
    ifaceName_ = "";
    domain_ = "";
    std::list<INetAddr>().swap(netAddrList_);
    std::list<INetAddr>().swap(dnsList_);
    std::list<Route>().swap(routeList_);
    mtu_ = 0;
    tcpBufferSizes_ = "";
}

std::string NetLinkInfo::ToString(const std::string &tab) const
{
    std::string str;
    str.append("\n");
    str.append(tab);
    str.append("[NetLinkInfo]");

    str.append("\n");
    str.append(tab);
    str.append("ifaceName_ = ");
    str.append(ifaceName_);

    str.append("\n");
    str.append(tab);
    str.append("domain_ = ");
    str.append(domain_);

    str.append("\n");
    str.append(tab);
    str.append("netAddrList_ = ");
    for (auto it = netAddrList_.begin(); it != netAddrList_.end(); it++) {
        str.append(it->ToString(tab + "    "));
    }

    str.append("\n");
    str.append(tab);
    str.append("dnsList_ = ");
    for (auto it = dnsList_.begin(); it != dnsList_.end(); it++) {
        str.append(it->ToString(tab + "    "));
    }

    str.append("\n");
    str.append(tab);
    str.append("routeList_ = ");
    for (auto it = routeList_.begin(); it != routeList_.end(); it++) {
        str.append(it->ToString(tab + "    "));
    }

    str.append("\n");
    str.append(tab);
    str.append("mtu_ = ");
    str.append(std::to_string(mtu_));

    str.append("\n");
    str.append(tab);
    str.append("tcpBufferSizes_ = ");
    str.append(tcpBufferSizes_);
    return str;
}

std::string NetLinkInfo::ToStringBase(const std::string &tab) const
{
    std::string str;
    str.append("\n");
    str.append(tab);
    str.append("[NetLinkInfo]");

    str.append("\n");
    str.append(tab);
    str.append("ifaceName_ = ");
    str.append(ifaceName_);

    str.append("\n");
    str.append(tab);
    str.append("domain_ = ");
    str.append(domain_);

    str.append("\n");
    str.append(tab);
    str.append("mtu_ = ");
    str.append(std::to_string(mtu_));

    str.append("\n");
    str.append(tab);
    str.append("tcpBufferSizes_ = ");
    str.append(tcpBufferSizes_);

    str.append("\n");
    str.append(tab);
    str.append("End");
    return str;
}

std::string NetLinkInfo::ToStringAddr(const std::string &tab) const
{
    std::string str;
    str.append("\n");
    str.append(tab);
    str.append("netAddrList_ = ");
    for (auto it = netAddrList_.begin(); it != netAddrList_.end(); it++) {
        str.append(it->ToString(tab + "    "));
    }
    str.append("\n");
    str.append(tab);
    str.append("End");
    return str;
}

std::string NetLinkInfo::ToStringDns(const std::string &tab) const
{
    std::string str;
    str.append("\n");
    str.append(tab);
    str.append("dnsList_ = ");
    for (auto it = dnsList_.begin(); it != dnsList_.end(); it++) {
        str.append(it->ToString(tab + "    "));
    }
    str.append("\n");
    str.append(tab);
    str.append("End");
    return str;
}

std::string NetLinkInfo::ToStringRoute(const std::string &tab) const
{
    std::string str;
    str.append("\n");
    str.append(tab);
    str.append("routeList_ = ");
    for (auto it = routeList_.begin(); it != routeList_.end(); it++) {
        str.append(it->ToString(tab + "    "));
    }
    str.append("\n");
    str.append(tab);
    str.append("End");
    return str;
}
} // namespace NetManagerStandard
} // namespace OHOS