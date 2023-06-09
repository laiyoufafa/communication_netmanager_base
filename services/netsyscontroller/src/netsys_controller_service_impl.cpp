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
#include "netsys_controller_service_impl.h"
#include "net_mgr_log_wrapper.h"

namespace OHOS {
namespace NetManagerStandard {
NetsysControllerServiceImpl::NetsysControllerServiceImpl()
{}

NetsysControllerServiceImpl::~NetsysControllerServiceImpl() {}

void NetsysControllerServiceImpl::Init()
{
    mockNetsysClient_.RegisterMockApi();
    return;
}

int32_t NetsysControllerServiceImpl::NetworkCreatePhysical(int32_t netId, int32_t permission)
{
    NETMGR_LOG_I("Create Physical network: netId[%{public}d], permission[%{public}d]", netId, permission);
    if (mockNetsysClient_.CheckMockApi(MOCK_NETWORKCREATEPHYSICAL_API)) {
        return mockNetsysClient_.NetworkCreatePhysical(netId, permission);
    }
    return netsysClient_.NetworkCreatePhysical(netId, permission);
}

int32_t NetsysControllerServiceImpl::NetworkDestroy(int32_t netId)
{
    NETMGR_LOG_I("Destroy network: netId[%{public}d]", netId);
    if (mockNetsysClient_.CheckMockApi(MOCK_NETWORKDESTROY_API)) {
        return mockNetsysClient_.NetworkDestroy(netId);
    }
    return netsysClient_.NetworkDestroy(netId);
}

int32_t NetsysControllerServiceImpl::NetworkAddInterface(int32_t netId, const std::string &iface)
{
    NETMGR_LOG_I("Add network interface: netId[%{public}d], iface[%{public}s]", netId, iface.c_str());
    if (mockNetsysClient_.CheckMockApi(MOCK_NETWORKADDINTERFACE_API)) {
        return mockNetsysClient_.NetworkAddInterface(netId, iface);
    }
    return netsysClient_.NetworkAddInterface(netId, iface);
}

int32_t NetsysControllerServiceImpl::NetworkRemoveInterface(int32_t netId, const std::string &iface)
{
    NETMGR_LOG_I("Remove network interface: netId[%{public}d], iface[%{public}s]", netId, iface.c_str());
    if (mockNetsysClient_.CheckMockApi(MOCK_NETWORKREMOVEINTERFACE_API)) {
        return mockNetsysClient_.NetworkRemoveInterface(netId, iface);
    }
    return netsysClient_.NetworkRemoveInterface(netId, iface);
}

int32_t NetsysControllerServiceImpl::NetworkAddRoute(int32_t netId, const std::string &ifName,
    const std::string &destination, const std::string &nextHop)
{
    NETMGR_LOG_I("Add Route: netId[%{public}d], ifName[%{public}s], destination[%{public}s], nextHop[%{public}s]",
        netId, ifName.c_str(), destination.c_str(), nextHop.c_str());
    if (mockNetsysClient_.CheckMockApi(MOCK_NETWORKADDROUTE_API)) {
        return mockNetsysClient_.NetworkAddRoute(netId, ifName, destination, nextHop);
    }
    return netsysClient_.NetworkAddRoute(netId, ifName, destination, nextHop);
}

int32_t NetsysControllerServiceImpl::NetworkRemoveRoute(int32_t netId, const std::string &ifName,
    const std::string &destination, const std::string &nextHop)
{
    NETMGR_LOG_I("Remove Route: netId[%{public}d], ifName[%{public}s], destination[%{public}s], nextHop[%{public}s]",
        netId, ifName.c_str(), destination.c_str(), nextHop.c_str());
    if (mockNetsysClient_.CheckMockApi(MOCK_NETWORKREMOVEROUTE_API)) {
        return mockNetsysClient_.NetworkRemoveRoute(netId, ifName, destination, nextHop);
    }
    return netsysClient_.NetworkRemoveRoute(netId, ifName, destination, nextHop);
}

int32_t NetsysControllerServiceImpl::SetInterfaceDown(const std::string &iface)
{
    NETMGR_LOG_I("Set interface down: iface[%{public}s]", iface.c_str());
    if (mockNetsysClient_.CheckMockApi(MOCK_SETINTERFACEDOWN_API)) {
        return mockNetsysClient_.SetInterfaceDown(iface);
    }
    return netsysClient_.SetInterfaceDown(iface);
}

int32_t NetsysControllerServiceImpl::SetInterfaceUp(const std::string &iface)
{
    NETMGR_LOG_I("Set interface up: iface[%{public}s]", iface.c_str());
    if (mockNetsysClient_.CheckMockApi(MOCK_SETINTERFACEUP_API)) {
        return mockNetsysClient_.SetInterfaceUp(iface);
    }
    return netsysClient_.SetInterfaceUp(iface);
}

void NetsysControllerServiceImpl::InterfaceClearAddrs(const std::string &ifName)
{
    NETMGR_LOG_I("Clear addrs: ifName[%{public}s]", ifName.c_str());
    if (mockNetsysClient_.CheckMockApi(MOCK_INTERFACECLEARADDRS_API)) {
        return mockNetsysClient_.InterfaceClearAddrs(ifName);
    }
    return netsysClient_.InterfaceClearAddrs(ifName);
}

int32_t NetsysControllerServiceImpl::InterfaceGetMtu(const std::string &ifName)
{
    NETMGR_LOG_I("Get mtu: ifName[%{public}s]", ifName.c_str());
    if (mockNetsysClient_.CheckMockApi(MOCK_INTERFACEGETMTU_API)) {
        return mockNetsysClient_.InterfaceGetMtu(ifName);
    }
    return netsysClient_.InterfaceGetMtu(ifName);
}

int32_t NetsysControllerServiceImpl::InterfaceSetMtu(const std::string &ifName, int32_t mtu)
{
    NETMGR_LOG_I("Set mtu: ifName[%{public}s], mtu[%{public}d]", ifName.c_str(), mtu);
    if (mockNetsysClient_.CheckMockApi(MOCK_INTERFACESETMTU_API)) {
        return mockNetsysClient_.InterfaceSetMtu(ifName, mtu);
    }
    return netsysClient_.InterfaceSetMtu(ifName, mtu);
}

int32_t NetsysControllerServiceImpl::InterfaceAddAddress(const std::string &ifName,
    const std::string &ipAddr, int32_t prefixLength)
{
    NETMGR_LOG_I("Add address: ifName[%{public}s], ipAddr[%{public}s], prefixLength[%{public}d]",
        ifName.c_str(), ipAddr.c_str(), prefixLength);
    if (mockNetsysClient_.CheckMockApi(MOCK_INTERFACEADDADDRESS_API)) {
        return mockNetsysClient_.InterfaceAddAddress(ifName, ipAddr, prefixLength);
    }
    return netsysClient_.InterfaceAddAddress(ifName, ipAddr, prefixLength);
}

int32_t NetsysControllerServiceImpl::InterfaceDelAddress(const std::string &ifName,
    const std::string &ipAddr, int32_t prefixLength)
{
    NETMGR_LOG_I("Delete address: ifName[%{public}s], ipAddr[%{public}s], prefixLength[%{public}d]",
        ifName.c_str(), ipAddr.c_str(), prefixLength);
    if (mockNetsysClient_.CheckMockApi(MOCK_INTERFACEDELADDRESS_API)) {
        return mockNetsysClient_.InterfaceDelAddress(ifName, ipAddr, prefixLength);
    }
    return netsysClient_.InterfaceDelAddress(ifName, ipAddr, prefixLength);
}

int32_t NetsysControllerServiceImpl::SetResolverConfig(uint16_t netId, uint16_t baseTimeoutMsec, uint8_t retryCount,
    const std::vector<std::string> &servers, const std::vector<std::string> &domains)
{
    NETMGR_LOG_I("Set resolver config: netId[%{public}d]", netId);
    if (mockNetsysClient_.CheckMockApi(MOCK_SETRESOLVERCONFIG_API)) {
        return mockNetsysClient_.SetResolverConfig(netId, baseTimeoutMsec, retryCount, servers, domains);
    }
    return netsysClient_.SetResolverConfig(netId, baseTimeoutMsec, retryCount, servers, domains);
}

int32_t NetsysControllerServiceImpl::GetResolverInfo(uint16_t netId, std::vector<std::string> &servers,
    std::vector<std::string> &domains, uint16_t &baseTimeoutMsec, uint8_t &retryCount)
{
    NETMGR_LOG_I("Get resolver config: netId[%{public}d]", netId);
    if (mockNetsysClient_.CheckMockApi(MOCK_GETRESOLVERINFO_API)) {
        return mockNetsysClient_.GetResolverInfo(netId, servers, domains, baseTimeoutMsec, retryCount);
    }
    return netsysClient_.GetResolverInfo(netId, servers, domains, baseTimeoutMsec, retryCount);
}

int32_t NetsysControllerServiceImpl::CreateNetworkCache(uint16_t netId)
{
    NETMGR_LOG_I("create dns cache: netId[%{public}d]", netId);
    if (mockNetsysClient_.CheckMockApi(MOCK_CREATENETWORKCACHE_API)) {
        return mockNetsysClient_.CreateNetworkCache(netId);
    }
    return netsysClient_.CreateNetworkCache(netId);
}

int32_t NetsysControllerServiceImpl::DestroyNetworkCache(uint16_t netId)
{
    NETMGR_LOG_I("Destroy dns cache: netId[%{public}d]", netId);
    if (mockNetsysClient_.CheckMockApi(MOCK_DESTROYNETWORKCACHE_API)) {
        return mockNetsysClient_.DestroyNetworkCache(netId);
    }
    return netsysClient_.DestroyNetworkCache(netId);
}

int32_t NetsysControllerServiceImpl::FlushNetworkCache(uint16_t netId)
{
    NETMGR_LOG_I("Destroy Flush dns cache: netId[%{public}d]", netId);
    if (mockNetsysClient_.CheckMockApi(MOCK_FLUSHNETWORKCACHE_API)) {
        return mockNetsysClient_.FlushNetworkCache(netId);
    }
    return netsysClient_.FlushNetworkCache(netId);
}

int32_t NetsysControllerServiceImpl::GetAddrInfo(const std::string &hostName, const std::string &serverName,
    const struct addrinfo &hints, std::unique_ptr<addrinfo> &res, uint16_t netId)
{
    NETMGR_LOG_I("NetsysControllerServiceImpl GetAddrInfo");
    if (mockNetsysClient_.CheckMockApi(MOCK_GETADDRINFO_API)) {
        return mockNetsysClient_.GetAddrInfo(hostName, serverName, hints, res, netId);
    }
    return netsysClient_.GetAddrInfo(hostName, serverName, hints, res, netId);
}

int64_t NetsysControllerServiceImpl::GetCellularRxBytes()
{
    NETMGR_LOG_I("NetsysControllerServiceImpl GetCellularRxBytes");
    if (mockNetsysClient_.CheckMockApi(MOCK_GETCELLULARRXBYTES_API)) {
        return mockNetsysClient_.GetCellularRxBytes();
    }
    return netsysClient_.GetCellularRxBytes();
}

int64_t NetsysControllerServiceImpl::GetCellularTxBytes()
{
    NETMGR_LOG_I("NetsysControllerServiceImpl GetCellularTxBytes");
    if (mockNetsysClient_.CheckMockApi(MOCK_GETCELLULARTXBYTES_API)) {
        return mockNetsysClient_.GetCellularTxBytes();
    }
    return netsysClient_.GetCellularTxBytes();
}

int64_t NetsysControllerServiceImpl::GetAllRxBytes()
{
    NETMGR_LOG_I("NetsysControllerServiceImpl GetAllRxBytes");
    if (mockNetsysClient_.CheckMockApi(MOCK_GETALLRXBYTES_API)) {
        return mockNetsysClient_.GetAllRxBytes();
    }
    return netsysClient_.GetAllRxBytes();
}

int64_t NetsysControllerServiceImpl::GetAllTxBytes()
{
    NETMGR_LOG_I("NetsysControllerServiceImpl GetAllTxBytes");
    if (mockNetsysClient_.CheckMockApi(MOCK_GETALLTXBYTES_API)) {
        return mockNetsysClient_.GetAllTxBytes();
    }
    return netsysClient_.GetAllTxBytes();
}

int64_t NetsysControllerServiceImpl::GetUidRxBytes(uint32_t uid)
{
    NETMGR_LOG_I("NetsysControllerServiceImpl GetUidRxBytes");
    if (mockNetsysClient_.CheckMockApi(MOCK_GETUIDRXBYTES_API)) {
        return mockNetsysClient_.GetUidRxBytes(uid);
    }
    return netsysClient_.GetUidRxBytes(uid);
}

int64_t NetsysControllerServiceImpl::GetUidTxBytes(uint32_t uid)
{
    NETMGR_LOG_I("NetsysControllerServiceImpl GetUidTxBytes");
    if (mockNetsysClient_.CheckMockApi(MOCK_GETUIDTXBYTES_API)) {
        return mockNetsysClient_.GetUidTxBytes(uid);
    }
    return netsysClient_.GetUidTxBytes(uid);
}

int64_t NetsysControllerServiceImpl::GetUidOnIfaceRxBytes(uint32_t uid, const std::string &interfaceName)
{
    NETMGR_LOG_I("NetsysControllerServiceImpl GetUidOnIfaceRxBytes");
    if (mockNetsysClient_.CheckMockApi(MOCK_GETUIDRXBYTES_API)) {
        return mockNetsysClient_.GetUidOnIfaceRxBytes(uid, interfaceName);
    }
    return netsysClient_.GetUidOnIfaceRxBytes(uid, interfaceName);
}

int64_t NetsysControllerServiceImpl::GetUidOnIfaceTxBytes(uint32_t uid, const std::string &interfaceName)
{
    NETMGR_LOG_I("NetsysControllerServiceImpl GetUidOnIfaceTxBytes");
    if (mockNetsysClient_.CheckMockApi(MOCK_GETUIDTXBYTES_API)) {
        return mockNetsysClient_.GetUidOnIfaceTxBytes(uid, interfaceName);
    }
    return netsysClient_.GetUidOnIfaceTxBytes(uid, interfaceName);
}

int64_t NetsysControllerServiceImpl::GetIfaceRxBytes(const std::string &interfaceName)
{
    NETMGR_LOG_I("NetsysControllerServiceImpl GetIfaceRxBytes");
    if (mockNetsysClient_.CheckMockApi(MOCK_GETIFACERXBYTES_API)) {
        return mockNetsysClient_.GetIfaceRxBytes(interfaceName);
    }
    return netsysClient_.GetIfaceRxBytes(interfaceName);
}

int64_t NetsysControllerServiceImpl::GetIfaceTxBytes(const std::string &interfaceName)
{
    NETMGR_LOG_I("NetsysControllerServiceImpl GetIfaceTxBytes");
    if (mockNetsysClient_.CheckMockApi(MOCK_GETIFACETXBYTES_API)) {
        return mockNetsysClient_.GetIfaceTxBytes(interfaceName);
    }
    return netsysClient_.GetIfaceTxBytes(interfaceName);
}

std::vector<std::string> NetsysControllerServiceImpl::InterfaceGetList()
{
    NETMGR_LOG_I("NetsysControllerServiceImpl InterfaceGetList");
    if (mockNetsysClient_.CheckMockApi(MOCK_INTERFACEGETLIST_API)) {
        return mockNetsysClient_.InterfaceGetList();
    }
    return netsysClient_.InterfaceGetList();
}

std::vector<std::string> NetsysControllerServiceImpl::UidGetList()
{
    NETMGR_LOG_I("NetsysControllerServiceImpl UidGetList");
    if (mockNetsysClient_.CheckMockApi(MOCK_UIDGETLIST_API)) {
        return mockNetsysClient_.UidGetList();
    }
    return netsysClient_.UidGetList();
}

int64_t NetsysControllerServiceImpl::GetIfaceRxPackets(const std::string &interfaceName)
{
    NETMGR_LOG_D("NetsysControllerServiceImpl GetIfaceRxPackets");
    if (mockNetsysClient_.CheckMockApi(MOCK_GETIFACERXPACKETS_API)) {
        return mockNetsysClient_.GetIfaceRxPackets(interfaceName);
    }
    return netsysClient_.GetIfaceRxPackets(interfaceName);
}

int64_t NetsysControllerServiceImpl::GetIfaceTxPackets(const std::string &interfaceName)
{
    NETMGR_LOG_D("NetsysControllerServiceImpl GetIfaceTxPackets");
    if (mockNetsysClient_.CheckMockApi(MOCK_GETIFACETXPACKETS_API)) {
        return mockNetsysClient_.GetIfaceTxPackets(interfaceName);
    }
    return netsysClient_.GetIfaceTxPackets(interfaceName);
}

int32_t NetsysControllerServiceImpl::SetDefaultNetWork(int32_t netId)
{
    NETMGR_LOG_D("NetsysControllerServiceImpl SetDefaultNetWork");
    if (mockNetsysClient_.CheckMockApi(MOCK_SETDEFAULTNETWORK_API)) {
        return mockNetsysClient_.SetDefaultNetWork(netId);
    }
    return netsysClient_.SetDefaultNetWork(netId);
}

int32_t NetsysControllerServiceImpl::ClearDefaultNetWorkNetId()
{
    NETMGR_LOG_D("NetsysControllerServiceImpl ClearDefaultNetWorkNetId");
    if (mockNetsysClient_.CheckMockApi(MOCK_CLEARDEFAULTNETWORK_API)) {
        return mockNetsysClient_.ClearDefaultNetWorkNetId();
    }
    return netsysClient_.ClearDefaultNetWorkNetId();
}

int32_t NetsysControllerServiceImpl::BindSocket(int32_t socket_fd, uint32_t netId)
{
    NETMGR_LOG_D("NetsysControllerServiceImpl BindSocket");
    if (mockNetsysClient_.CheckMockApi(MOCK_BINDSOCKET_API)) {
        return mockNetsysClient_.BindSocket(socket_fd, netId);
    }
    return netsysClient_.BindSocket(socket_fd, netId);
}

int32_t NetsysControllerServiceImpl::IpEnableForwarding(const std::string& requester)
{
    NETMGR_LOG_D("NetsysControllerServiceImpl IpEnableForwarding");
    if (mockNetsysClient_.CheckMockApi(MOCK_IPENABLEFORWARDING_API)) {
        return mockNetsysClient_.IpEnableForwarding(requester);
    }
    return netsysClient_.IpEnableForwarding(requester);
}

int32_t NetsysControllerServiceImpl::IpDisableForwarding(const std::string& requester)
{
    NETMGR_LOG_D("NetsysControllerServiceImpl IpDisableForwarding");
    if (mockNetsysClient_.CheckMockApi(MOCK_IPDISABLEFORWARDING_API)) {
        return mockNetsysClient_.IpDisableForwarding(requester);
    }
    return netsysClient_.IpDisableForwarding(requester);
}

int32_t NetsysControllerServiceImpl::TetherAddForward(const std::string& downstreamIface,
    const std::string& upstreamIface)
{
    NETMGR_LOG_D("NetsysControllerServiceImpl TetherAddForward");
    if (mockNetsysClient_.CheckMockApi(MOCK_TETHERADDFORWARD_API)) {
        return mockNetsysClient_.TetherAddForward(downstreamIface, upstreamIface);
    }
    return netsysClient_.TetherAddForward(downstreamIface, upstreamIface);
}

int32_t NetsysControllerServiceImpl::TetherRemoveForward(const std::string& downstreamIface,
    const std::string& upstreamIface)
{
    NETMGR_LOG_D("NetsysControllerServiceImpl TetherRemoveForward");
    if (mockNetsysClient_.CheckMockApi(MOCK_TETHERREMOVEFORWARD_API)) {
        return mockNetsysClient_.TetherRemoveForward(downstreamIface, upstreamIface);
    }
    return netsysClient_.TetherRemoveForward(downstreamIface, upstreamIface);
}

int32_t NetsysControllerServiceImpl::IpfwdAddInterfaceForward(const std::string& fromIface, const std::string& toIface)
{
    NETMGR_LOG_D("NetsysControllerServiceImpl IpfwdAddInterfaceForward");
    if (mockNetsysClient_.CheckMockApi(MOCK_IPFWDADDIFACEFORWARD_API)) {
        return mockNetsysClient_.IpfwdAddInterfaceForward(fromIface, toIface);
    }
    return netsysClient_.IpfwdAddInterfaceForward(fromIface, toIface);
}

int32_t NetsysControllerServiceImpl::IpfwdRemoveInterfaceForward(const std::string& fromIface, const std::string& toIface)
{
    NETMGR_LOG_D("NetsysControllerServiceImpl IpfwdRemoveInterfaceForward");
    if (mockNetsysClient_.CheckMockApi(MOCK_IPFWDREMOVEIFACEFORWARD_API)) {
        return mockNetsysClient_.IpfwdRemoveInterfaceForward(fromIface, toIface);
    }
    return netsysClient_.IpfwdRemoveInterfaceForward(fromIface, toIface);
}

int32_t NetsysControllerServiceImpl::TetherDnsSet(uint32_t netId, const std::vector<std::string>& dnsAddrs)
{
    NETMGR_LOG_D("NetsysControllerServiceImpl IpfwdRemoveInterfaceForward");
    if (mockNetsysClient_.CheckMockApi(MOCK_TETHERDNSSET_API)) {
        return mockNetsysClient_.TetherDnsSet(netId, dnsAddrs);
    }
    return netsysClient_.TetherDnsSet(netId, dnsAddrs);
}

int32_t NetsysControllerServiceImpl::RegisterNetsysNotifyCallback(const NetsysNotifyCallback &callback)
{
    NETMGR_LOG_D("NetsysControllerServiceImpl IpfwdRemoveInterfaceForward");
    if (mockNetsysClient_.CheckMockApi(MOCK_REGISTERNETSYSNOTIFYCALLBACK_API)) {
        return mockNetsysClient_.RegisterNetsysNotifyCallback(callback);
    }
    return netsysClient_.RegisterNetsysNotifyCallback(callback);
}


int32_t NetsysControllerServiceImpl::BindNetworkServiceVpn(int32_t socketFd)
{
    NETMGR_LOG_D("NetsysNativeClient::BindNetworkServiceVpn");
    if (mockNetsysClient_.CheckMockApi(MOCK_BINDNETWORKSERVICEVPN_API)) {
        return mockNetsysClient_.BindNetworkServiceVpn(socketFd);
    }
    return netsysClient_.BindNetworkServiceVpn(socketFd);
}

int32_t NetsysControllerServiceImpl::EnableVirtualNetIfaceCard(int32_t socketFd, struct ifreq &ifRequest,
    int32_t &ifaceFd)
{
    NETMGR_LOG_D("NetsysControllerServiceImpl::EnableVirtualNetIfaceCard");
    if (mockNetsysClient_.CheckMockApi(MOCK_ENABLEVIRTUALNETIFACECARD_API)) {
        return mockNetsysClient_.EnableVirtualNetIfaceCard(socketFd, ifRequest, ifaceFd);
    }
    return netsysClient_.EnableVirtualNetIfaceCard(socketFd, ifRequest, ifaceFd);
}

int32_t NetsysControllerServiceImpl::SetIpAddress(int32_t socketFd, const std::string &ipAddress, int32_t prefixLen,
    struct ifreq &ifRequest)
{
    NETMGR_LOG_D("NetsysControllerServiceImpl::SetIpAddress");
    if (mockNetsysClient_.CheckMockApi(MOCK_SETIPADDRESS_API)) {
        return mockNetsysClient_.SetIpAddress(socketFd, ipAddress, prefixLen, ifRequest);
    }
    return netsysClient_.SetIpAddress(socketFd, ipAddress, prefixLen, ifRequest);
}

int32_t NetsysControllerServiceImpl::SetBlocking(int32_t ifaceFd, bool isBlock)
{
    NETMGR_LOG_D("NetsysControllerServiceImpl::SetBlocking");
    if (mockNetsysClient_.CheckMockApi(MOCK_SETBLOCKING_API)) {
        return mockNetsysClient_.SetBlocking(ifaceFd, isBlock);
    }
    return netsysClient_.SetBlocking(ifaceFd, isBlock);
}

int32_t NetsysControllerServiceImpl::StartDhcpClient(const std::string &iface, bool bIpv6)
{
    NETMGR_LOG_D("NetsysControllerServiceImpl::StartDhcpClient");
    if (mockNetsysClient_.CheckMockApi(MOCK_STARTDHCPCLIENT_API)) {
        return mockNetsysClient_.StartDhcpClient(iface, bIpv6);
    }
    return netsysClient_.StartDhcpClient(iface, bIpv6);
}

int32_t NetsysControllerServiceImpl::StopDhcpClient(const std::string &iface, bool bIpv6)
{
    NETMGR_LOG_D("NetsysControllerServiceImpl::StopDhcpClient");
    if (mockNetsysClient_.CheckMockApi(MOCK_STOPDHCPCLIENT_API)) {
        return mockNetsysClient_.StopDhcpClient(iface, bIpv6);
    }
    return netsysClient_.StopDhcpClient(iface, bIpv6);
}

int32_t NetsysControllerServiceImpl::RegisterCallback(sptr<NetsysControllerCallback> callback)
{
    NETMGR_LOG_D("NetsysControllerServiceImpl::RegisterCallback");
    if (mockNetsysClient_.CheckMockApi(MOCK_REGISTERNOTIFYCALLBACK_API)) {
        return mockNetsysClient_.RegisterCallback(callback);
    }
    return netsysClient_.RegisterCallback(callback);
}

int32_t NetsysControllerServiceImpl::StartDhcpService(const std::string &iface, const std::string &ipv4addr)
{
    NETMGR_LOG_D("NetsysControllerServiceImpl::SetBlocking");
    if (mockNetsysClient_.CheckMockApi(MOCK_STARTDHCPSERVICE_API)) {
        return mockNetsysClient_.StartDhcpService(iface, ipv4addr);
    }
    return netsysClient_.StartDhcpService(iface, ipv4addr);
}

int32_t NetsysControllerServiceImpl::StopDhcpService(const std::string &iface)
{
    NETMGR_LOG_D("NetsysControllerServiceImpl::StopDhcpService");
    if (mockNetsysClient_.CheckMockApi(MOCK_STOPDHCPSERVICE_API)) {
        return mockNetsysClient_.StopDhcpService(iface);
    }
    return netsysClient_.StopDhcpService(iface);
}
} // namespace NetManagerStandard
} // namespace OHOS
