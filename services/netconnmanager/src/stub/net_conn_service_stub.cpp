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
#include "net_conn_service_stub.h"

#include "net_conn_constants.h"
#include "net_conn_types.h"
#include "net_mgr_log_wrapper.h"

namespace OHOS {
namespace NetManagerStandard {
NetConnServiceStub::NetConnServiceStub()
{
    memberFuncMap_[CMD_NM_SYSTEM_READY]                 = &NetConnServiceStub::OnSystemReady;
    memberFuncMap_[CMD_NM_REGISTER_NET_CONN_CALLBACK]   = &NetConnServiceStub::OnRegisterNetConnCallback;
    memberFuncMap_[CMD_NM_REGISTER_NET_CONN_CALLBACK_BY_SPECIFIER] =
        &NetConnServiceStub::OnRegisterNetConnCallbackBySpecifier;
    memberFuncMap_[CMD_NM_UNREGISTER_NET_CONN_CALLBACK] = &NetConnServiceStub::OnUnregisterNetConnCallback;
    memberFuncMap_[CMD_NM_UPDATE_NET_STATE_FOR_TEST]    = &NetConnServiceStub::OnUpdateNetStateForTest;
    memberFuncMap_[CMD_NM_REG_NET_SUPPLIER]             = &NetConnServiceStub::OnRegisterNetSupplier;
    memberFuncMap_[CMD_NM_UNREG_NETWORK]                = &NetConnServiceStub::OnUnregisterNetSupplier;
    memberFuncMap_[CMD_NM_SET_NET_SUPPLIER_INFO]        = &NetConnServiceStub::OnUpdateNetSupplierInfo;
    memberFuncMap_[CMD_NM_SET_NET_LINK_INFO]            = &NetConnServiceStub::OnUpdateNetLinkInfo;
    memberFuncMap_[CMD_NM_REGISTER_NET_DETECTION_RET_CALLBACK] =
        &NetConnServiceStub::OnRegisterNetDetectionCallback;
    memberFuncMap_[CMD_NM_UNREGISTER_NET_DETECTION_RET_CALLBACK] =
        &NetConnServiceStub::OnUnRegisterNetDetectionCallback;
    memberFuncMap_[CMD_NM_NET_DETECTION]                = &NetConnServiceStub::OnNetDetection;
    memberFuncMap_[CMD_NM_GET_IFACENAME_BY_TYPE]        = &NetConnServiceStub::OnGetIfaceNameByType;
    memberFuncMap_[CMD_NM_GETDEFAULTNETWORK]            = &NetConnServiceStub::OnGetDefaultNet;
    memberFuncMap_[CMD_NM_HASDEFAULTNET] =                &NetConnServiceStub::OnHasDefaultNet;
    memberFuncMap_[CMD_NM_GET_SPECIFIC_NET]             = &NetConnServiceStub::OnGetSpecificNet;
    memberFuncMap_[CMD_NM_GET_ALL_NETS]                 = &NetConnServiceStub::OnGetAllNets;
    memberFuncMap_[CMD_NM_GET_SPECIFIC_UID_NET]         = &NetConnServiceStub::OnGetSpecificUidNet;
    memberFuncMap_[CMD_NM_GET_CONNECTION_PROPERTIES]    = &NetConnServiceStub::OnGetConnectionProperties;
    memberFuncMap_[CMD_NM_GET_NET_CAPABILITIES]         = &NetConnServiceStub::OnGetNetCapabilities;
    memberFuncMap_[CMD_NM_GET_ADDRESSES_BY_NAME]        = &NetConnServiceStub::OnGetAddressesByName;
    memberFuncMap_[CMD_NM_GET_ADDRESS_BY_NAME]          = &NetConnServiceStub::OnGetAddressByName;
    memberFuncMap_[CMD_NM_BIND_SOCKET]                  = &NetConnServiceStub::OnBindSocket;
    memberFuncMap_[CMD_NM_REGISTER_NET_SUPPLIER_CALLBACK] = &NetConnServiceStub::OnRegisterNetSupplierCallback;
    memberFuncMap_[CMD_NM_SET_AIRPLANE_MODE] = &NetConnServiceStub::OnSetAirplaneMode;
    memberFuncMap_[CMD_NM_RESTORE_FACTORY_DATA] = &NetConnServiceStub::OnRestoreFactoryData;
}

NetConnServiceStub::~NetConnServiceStub() {}

std::string ToUtf8(std::u16string str16)
{
    return std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> {}.to_bytes(str16);
}

int32_t NetConnServiceStub::OnRemoteRequest(
    uint32_t code, MessageParcel &data, MessageParcel &reply, MessageOption &option)
{
    NETMGR_LOG_D("stub call start, code = [%{public}d]", code);

    std::u16string myDescripter = NetConnServiceStub::GetDescriptor();
    std::u16string remoteDescripter = data.ReadInterfaceToken();
    NETMGR_LOG_D("myDescripter[%{public}s], remoteDescripter[%{public}s]", ToUtf8(myDescripter).c_str(),
                 ToUtf8(remoteDescripter).c_str());
    if (myDescripter != remoteDescripter) {
        NETMGR_LOG_E("descriptor checked fail");
        return ERR_FLATTEN_OBJECT;
    }

    auto itFunc = memberFuncMap_.find(code);
    if (itFunc != memberFuncMap_.end()) {
        auto requestFunc = itFunc->second;
        if (requestFunc != nullptr) {
            return (this->*requestFunc)(data, reply);
        }
    }

    NETMGR_LOG_D("stub default case, need check");
    return IPCObjectStub::OnRemoteRequest(code, data, reply, option);
}

int32_t NetConnServiceStub::OnSystemReady(MessageParcel &data, MessageParcel &reply)
{
    SystemReady();
    return ERR_NONE;
}

int32_t NetConnServiceStub::OnRegisterNetSupplier(MessageParcel &data, MessageParcel &reply)
{
    NETMGR_LOG_D("stub processing");
    NetBearType bearerType;
    std::string ident;
    std::set<NetCap> netCaps;

    uint32_t type = 0;
    if (!data.ReadUint32(type)) {
        return ERR_FLATTEN_OBJECT;
    }
    bearerType = static_cast<NetBearType>(type);

    if (!data.ReadString(ident)) {
        return ERR_FLATTEN_OBJECT;
    }
    uint32_t size = 0;
    uint32_t value = 0;
    if (!data.ReadUint32(size)) {
        return ERR_FLATTEN_OBJECT;
    }
    for (uint32_t i = 0; i < size; ++i) {
        if (!data.ReadUint32(value)) {
            return ERR_FLATTEN_OBJECT;
        }
        netCaps.insert(static_cast<NetCap>(value));
    }

    uint32_t supplierId = 0;
    int32_t ret = RegisterNetSupplier(bearerType, ident, netCaps, supplierId);
    if (!reply.WriteInt32(ret)) {
        return ERR_FLATTEN_OBJECT;
    }
    if (ret == ERR_NONE) {
        NETMGR_LOG_E("supplierId[%{public}d].", supplierId);
        if (!reply.WriteUint32(supplierId)) {
            return ERR_FLATTEN_OBJECT;
        }
    }
    return ERR_NONE;
}

int32_t NetConnServiceStub::OnUnregisterNetSupplier(MessageParcel &data, MessageParcel &reply)
{
    uint32_t supplierId;
    if (!data.ReadUint32(supplierId)) {
        return ERR_FLATTEN_OBJECT;
    }

    int32_t ret = UnregisterNetSupplier(supplierId);
    if (!reply.WriteInt32(ret)) {
        return ERR_FLATTEN_OBJECT;
    }

    return ERR_NONE;
}

int32_t NetConnServiceStub::OnRegisterNetSupplierCallback(MessageParcel &data, MessageParcel &reply)
{
    int32_t result = NET_CONN_SUCCESS;
    uint32_t supplierId;
    data.ReadUint32(supplierId);
    sptr<IRemoteObject> remote = data.ReadRemoteObject();
    if (remote == nullptr) {
        NETMGR_LOG_E("Callback ptr is nullptr.");
        result = NET_CONN_ERR_GET_REMOTE_OBJECT_FAILED;
        reply.WriteInt32(result);
        return result;
    }

    sptr<INetSupplierCallback> callback = iface_cast<INetSupplierCallback>(remote);
    if (callback == nullptr) {
        result = NET_CONN_ERR_INPUT_NULL_PTR;
        reply.WriteInt32(result);
        return result;
    }

    result = ConvertCode(RegisterNetSupplierCallback(supplierId, callback));
    reply.WriteInt32(result);
    return result;
}

int32_t NetConnServiceStub::OnRegisterNetConnCallback(MessageParcel &data, MessageParcel &reply)
{
    int32_t result = NET_CONN_SUCCESS;
    sptr<IRemoteObject> remote = data.ReadRemoteObject();
    if (remote == nullptr) {
        NETMGR_LOG_E("Callback ptr is nullptr.");
        result = NET_CONN_ERR_GET_REMOTE_OBJECT_FAILED;
        reply.WriteInt32(result);
        return result;
    }

    sptr<INetConnCallback> callback = iface_cast<INetConnCallback>(remote);
    if (callback == nullptr) {
        result = NET_CONN_ERR_INPUT_NULL_PTR;
        reply.WriteInt32(result);
        return result;
    }

    result = ConvertCode(RegisterNetConnCallback(callback));
    reply.WriteInt32(result);
    return result;
}

int32_t NetConnServiceStub::OnRegisterNetConnCallbackBySpecifier(MessageParcel &data, MessageParcel &reply)
{
    sptr<NetSpecifier> netSpecifier = NetSpecifier::Unmarshalling(data);
    uint32_t timeoutMS = data.ReadUint32();
    int32_t result = ERR_FLATTEN_OBJECT;
    sptr<IRemoteObject> remote = data.ReadRemoteObject();
    if (remote == nullptr) {
        NETMGR_LOG_E("callback ptr is nullptr.");
        reply.WriteInt32(result);
        return result;
    }

    sptr<INetConnCallback> callback = iface_cast<INetConnCallback>(remote);
    if (callback == nullptr) {
        result = NET_CONN_ERR_INPUT_NULL_PTR;
        reply.WriteInt32(result);
        return result;
    }

    result = ConvertCode(RegisterNetConnCallback(netSpecifier, callback, timeoutMS));
    reply.WriteInt32(result);
    return result;
}

int32_t NetConnServiceStub::OnUnregisterNetConnCallback(MessageParcel &data, MessageParcel &reply)
{
    int32_t result = ERR_FLATTEN_OBJECT;
    sptr<IRemoteObject> remote = data.ReadRemoteObject();
    if (remote == nullptr) {
        NETMGR_LOG_E("callback ptr is nullptr.");
        reply.WriteInt32(result);
        return result;
    }

    sptr<INetConnCallback> callback = iface_cast<INetConnCallback>(remote);
    if (callback == nullptr) {
        result = NET_CONN_ERR_INPUT_NULL_PTR;
        reply.WriteInt32(result);
        return result;
    }

    result = ConvertCode(UnregisterNetConnCallback(callback));
    reply.WriteInt32(result);
    return result;
}

int32_t NetConnServiceStub::OnUpdateNetStateForTest(MessageParcel &data, MessageParcel &reply)
{
    NETMGR_LOG_I("Test NetConnServiceStub::OnUpdateNetStateForTest(), begin");
    sptr<NetSpecifier> netSpecifier = NetSpecifier::Unmarshalling(data);

    int32_t netState;
    if (!data.ReadInt32(netState)) {
        return ERR_FLATTEN_OBJECT;
    }

    NETMGR_LOG_I("Test NetConnServiceStub::OnUpdateNetStateForTest(), netState[%{public}d]", netState);
    int32_t result = ConvertCode(UpdateNetStateForTest(netSpecifier, netState));
    NETMGR_LOG_I("Test NetConnServiceStub::OnUpdateNetStateForTest(), result[%{public}d]", result);
    reply.WriteInt32(result);
    return result;
}

int32_t NetConnServiceStub::OnUpdateNetSupplierInfo(MessageParcel &data, MessageParcel &reply)
{
    NETMGR_LOG_D("OnUpdateNetSupplierInfo in.");
    uint32_t supplierId;
    if (!data.ReadUint32(supplierId)) {
        NETMGR_LOG_D("fail to get supplier id.");
        return ERR_FLATTEN_OBJECT;
    }

    NETMGR_LOG_D("OnUpdateNetSupplierInfo supplierId=[%{public}d].", supplierId);
    sptr<NetSupplierInfo> netSupplierInfo = NetSupplierInfo::Unmarshalling(data);
    int32_t ret = UpdateNetSupplierInfo(supplierId, netSupplierInfo);
    if (!reply.WriteInt32(ret)) {
        NETMGR_LOG_D("fail to update net supplier info.");
        return ERR_FLATTEN_OBJECT;
    }
    NETMGR_LOG_D("OnUpdateNetSupplierInfo out.");

    return ERR_NONE;
}

int32_t NetConnServiceStub::OnUpdateNetLinkInfo(MessageParcel &data, MessageParcel &reply)
{
    uint32_t supplierId;

    if (!data.ReadUint32(supplierId)) {
        return ERR_FLATTEN_OBJECT;
    }

    sptr<NetLinkInfo> netLinkInfo = NetLinkInfo::Unmarshalling(data);

    int32_t ret = UpdateNetLinkInfo(supplierId, netLinkInfo);
    if (!reply.WriteInt32(ret)) {
        return ERR_FLATTEN_OBJECT;
    }

    return ERR_NONE;
}

int32_t  NetConnServiceStub::OnRegisterNetDetectionCallback(MessageParcel &data, MessageParcel &reply)
{
    if (!data.ContainFileDescriptors()) {
        NETMGR_LOG_E("Execute ContainFileDescriptors failed");
    }
    int32_t netId = 0;
    if (!data.ReadInt32(netId)) {
        return NET_CONN_ERR_INVALID_PARAMETER;
    }

    int32_t result = NET_CONN_SUCCESS;
    sptr<IRemoteObject> remote = data.ReadRemoteObject();
    if (remote == nullptr) {
        NETMGR_LOG_E("Callback ptr is nullptr.");
        result = NET_CONN_ERR_GET_REMOTE_OBJECT_FAILED;
        reply.WriteInt32(result);
        return result;
    }

    sptr<INetDetectionCallback> callback = iface_cast<INetDetectionCallback>(remote);
    if (callback == nullptr) {
        result = NET_CONN_ERR_INPUT_NULL_PTR;
        reply.WriteInt32(result);
        return result;
    }

    result = ConvertCode(RegisterNetDetectionCallback(netId, callback));
    reply.WriteInt32(result);
    return result;
}

int32_t NetConnServiceStub::OnUnRegisterNetDetectionCallback(MessageParcel &data, MessageParcel &reply)
{
    if (!data.ContainFileDescriptors()) {
        NETMGR_LOG_E("Execute ContainFileDescriptors failed");
    }
    int32_t netId = 0;
    if (!data.ReadInt32(netId)) {
        return NET_CONN_ERR_INVALID_PARAMETER;
    }

    int32_t result = NET_CONN_SUCCESS;
    sptr<IRemoteObject> remote = data.ReadRemoteObject();
    if (remote == nullptr) {
        NETMGR_LOG_E("Callback ptr is nullptr.");
        result = NET_CONN_ERR_GET_REMOTE_OBJECT_FAILED;
        reply.WriteInt32(result);
        return result;
    }

    sptr<INetDetectionCallback> callback = iface_cast<INetDetectionCallback>(remote);
    if (callback == nullptr) {
        result = NET_CONN_ERR_INPUT_NULL_PTR;
        reply.WriteInt32(result);
        return result;
    }

    result = ConvertCode(UnRegisterNetDetectionCallback(netId, callback));
    reply.WriteInt32(result);
    return result;
}

int32_t NetConnServiceStub::OnNetDetection(MessageParcel &data, MessageParcel &reply)
{
    int32_t netId = 0;
    if (!data.ReadInt32(netId)) {
        return NET_CONN_ERR_INVALID_PARAMETER;
    }
    int32_t ret = ConvertCode(NetDetection(netId));
    if (!reply.WriteInt32(ret)) {
        return NET_CONN_ERR_INVALID_PARAMETER;
    }
    return ERR_NONE;
}

int32_t NetConnServiceStub::OnGetIfaceNameByType(MessageParcel &data, MessageParcel &reply)
{
    uint32_t netType = 0;
    if (!data.ReadUint32(netType)) {
        return ERR_FLATTEN_OBJECT;
    }
    NetBearType bearerType = static_cast<NetBearType>(netType);

    std::string ident;
    if (!data.ReadString(ident)) {
        return ERR_FLATTEN_OBJECT;
    }

    std::string ifaceName;
    int32_t ret = GetIfaceNameByType(bearerType, ident, ifaceName);
    if (!reply.WriteInt32(ret)) {
        return ERR_FLATTEN_OBJECT;
    }
    if (ret == ERR_NONE) {
        if (!reply.WriteString(ifaceName)) {
            return ERR_FLATTEN_OBJECT;
        }
    }
    return ret;
}

int32_t NetConnServiceStub::ConvertCode(int32_t internalCode)
{
    switch (internalCode) {
        case static_cast<int32_t>(ERR_NONE):
            return static_cast<int32_t>(NET_CONN_SUCCESS);
        case static_cast<int32_t>(ERR_INVALID_PARAMS):
            return static_cast<int32_t>(NET_CONN_ERR_INVALID_PARAMETER);
        case static_cast<int32_t>(ERR_SERVICE_NULL_PTR):
            return static_cast<int32_t>(NET_CONN_ERR_INPUT_NULL_PTR);
        case static_cast<int32_t>(ERR_NET_TYPE_NOT_FOUND):
            return static_cast<int32_t>(NET_CONN_ERR_NET_TYPE_NOT_FOUND);
        case static_cast<int32_t>(ERR_NO_ANY_NET_TYPE):
            return static_cast<int32_t>(NET_CONN_ERR_NO_ANY_NET_TYPE);
        case static_cast<int32_t>(ERR_NO_REGISTERED):
            return static_cast<int32_t>(NET_CONN_ERR_NO_REGISTERED);
        case static_cast<int32_t>(ERR_NET_NOT_FIND_NETID):
            return static_cast<int32_t>(NET_CONN_ERR_NETID_NOT_FOUND);
        case static_cast<int32_t>(ERR_PERMISSION_CHECK_FAIL):
            return static_cast<int32_t>(NET_CONN_ERR_PERMISSION_CHECK_FAILED);
        case static_cast<int32_t>(ERR_REGISTER_THE_SAME_CALLBACK):
            return static_cast<int32_t>(NET_CONN_ERR_SAME_CALLBACK);
        case static_cast<int32_t>(ERR_UNREGISTER_CALLBACK_NOT_FOUND):
            return static_cast<int32_t>(NET_CONN_ERR_CALLBACK_NOT_FOUND);
        case static_cast<int32_t>(ERR_NET_NOT_FIND_REQUEST_ID):
            return static_cast<int32_t>(NET_CONN_ERR_REQ_ID_NOT_FOUND);
        case static_cast<int32_t>(ERR_NET_DEFAULTNET_NOT_EXIST):
            return static_cast<int32_t>(NET_CONN_ERR_NO_DEFAULT_NET);
        default:
            break;
    }

    return static_cast<int32_t>(NET_CONN_ERR_INTERNAL_ERROR);
}

int32_t NetConnServiceStub::OnGetDefaultNet(MessageParcel& data, MessageParcel& reply)
{
    NETMGR_LOG_D("OnGetDefaultNet Begin...");
    int32_t netId;
    int32_t result = ConvertCode(GetDefaultNet(netId));
    NETMGR_LOG_D("GetDefaultNet result is: [%{public}d]", result);
    if (!reply.WriteInt32(result)) {
        return ERR_FLATTEN_OBJECT;
    }
    if (result == ERR_NONE) {
        if (!reply.WriteUint32(netId)) {
            return ERR_FLATTEN_OBJECT;
        }
    }
    return  ERR_NONE;
}

int32_t NetConnServiceStub::OnHasDefaultNet(MessageParcel& data, MessageParcel& reply)
{
    NETMGR_LOG_D("OnHasDefaultNet Begin...");
    bool flag = false;
    int32_t result = ConvertCode(HasDefaultNet(flag));
    NETMGR_LOG_D("HasDefaultNet result is: [%{public}d]", result);
    if (!reply.WriteInt32(result)) {
        return ERR_FLATTEN_OBJECT;
    }
    if (result == ERR_NONE) {
        if (!reply.WriteBool(flag)) {
            return ERR_FLATTEN_OBJECT;
        }
    }
    return  ERR_NONE;
}

int32_t NetConnServiceStub::OnGetSpecificNet(MessageParcel &data, MessageParcel &reply)
{
    uint32_t type;
    if (!data.ReadUint32(type)) {
        return ERR_FLATTEN_OBJECT;
    }
    NetBearType bearerType = static_cast<NetBearType>(type);

    NETMGR_LOG_D("stub execute GetSpecificNet");
    std::list<int32_t> netIdList;
    int32_t ret = GetSpecificNet(bearerType, netIdList);
    if (!reply.WriteInt32(ret)) {
        return ERR_FLATTEN_OBJECT;
    }
    if (ret == ERR_NONE) {
        int32_t size = static_cast<int32_t>(netIdList.size());
        if (!reply.WriteInt32(size)) {
            return ERR_FLATTEN_OBJECT;
        }

        for (auto p = netIdList.begin(); p != netIdList.end(); ++p) {
            if (!reply.WriteInt32(*p)) {
                return ERR_FLATTEN_OBJECT;
            }
        }
    }
    return ret;
}

int32_t NetConnServiceStub::OnGetAllNets(MessageParcel &data, MessageParcel &reply)
{
    NETMGR_LOG_D("stub execute GetAllNets");
    std::list<int32_t> netIdList;
    int32_t ret = GetAllNets(netIdList);
    if (!reply.WriteInt32(ret)) {
        return ERR_FLATTEN_OBJECT;
    }
    if (ret == ERR_NONE) {
        int32_t size = static_cast<int32_t>(netIdList.size());
        if (!reply.WriteInt32(size)) {
            return ERR_FLATTEN_OBJECT;
        }

        for (auto p = netIdList.begin(); p != netIdList.end(); ++p) {
            if (!reply.WriteInt32(*p)) {
                return ERR_FLATTEN_OBJECT;
            }
        }
    }
    return ret;
}

int32_t NetConnServiceStub::OnGetSpecificUidNet(MessageParcel &data, MessageParcel &reply)
{
    int32_t uid = 0;
    if (!data.ReadInt32(uid)) {
        return ERR_FLATTEN_OBJECT;
    }
    NETMGR_LOG_D("stub execute GetSpecificUidNet");

    int32_t netId = 0;
    int32_t ret = GetSpecificUidNet(uid, netId);
    if (!reply.WriteInt32(ret)) {
        return ERR_FLATTEN_OBJECT;
    }
    if (ret == ERR_NONE) {
        if (!reply.WriteInt32(netId)) {
            return ERR_FLATTEN_OBJECT;
        }
    }
    return ret;
}

int32_t NetConnServiceStub::OnGetConnectionProperties(MessageParcel &data, MessageParcel &reply)
{
    int32_t netId = 0;
    if (!data.ReadInt32(netId)) {
        return ERR_FLATTEN_OBJECT;
    }

    NETMGR_LOG_D("stub execute GetConnectionProperties");
    NetLinkInfo info;
    int32_t ret = GetConnectionProperties(netId, info);
    if (!reply.WriteInt32(ret)) {
        return ERR_FLATTEN_OBJECT;
    }
    if (ret == ERR_NONE) {
        sptr<NetLinkInfo> netLinkInfo_ptr = (std::make_unique<NetLinkInfo>(info)).release();
        if (!NetLinkInfo::Marshalling(reply, netLinkInfo_ptr)) {
            NETMGR_LOG_E("proxy Marshalling failed");
            return ERR_FLATTEN_OBJECT;
        }
    }
    return ret;
}

int32_t NetConnServiceStub::OnGetNetCapabilities(MessageParcel &data, MessageParcel &reply)
{
    int32_t netId = 0;
    if (!data.ReadInt32(netId)) {
        return ERR_FLATTEN_OBJECT;
    }

    NETMGR_LOG_D("stub execute GetNetCapabilities");

    NetAllCapabilities netAllCap;
    int32_t ret = GetNetCapabilities(netId, netAllCap);
    if (!reply.WriteInt32(ret)) {
        return ERR_FLATTEN_OBJECT;
    }
    if (ret == ERR_NONE) {
        if (!reply.WriteUint32(netAllCap.linkUpBandwidthKbps_) ||
            !reply.WriteUint32(netAllCap.linkDownBandwidthKbps_)) {
            return IPC_PROXY_ERR;
        }
        uint32_t size = netAllCap.netCaps_.size();
        if (!reply.WriteUint32(size)) {
            return ERR_FLATTEN_OBJECT;
        }
        for (auto netCap : netAllCap.netCaps_) {
            if (!reply.WriteUint32(static_cast<uint32_t>(netCap))) {
                return ERR_FLATTEN_OBJECT;
            }
        }

        size = netAllCap.bearerTypes_.size();
        if (!reply.WriteUint32(size)) {
            return ERR_FLATTEN_OBJECT;
        }
        for (auto bearerType : netAllCap.bearerTypes_) {
            if (!reply.WriteUint32(static_cast<uint32_t>(bearerType))) {
                return ERR_FLATTEN_OBJECT;
            }
        }
    }
    return ret;
}

int32_t NetConnServiceStub::OnGetAddressesByName(MessageParcel &data, MessageParcel &reply)
{
    std::string host;
    if (!data.ReadString(host)) {
        return ERR_FLATTEN_OBJECT;
    }
    int32_t netId;
    if (!data.ReadInt32(netId)) {
        return ERR_FLATTEN_OBJECT;
    }
    NETMGR_LOG_D("stub execute GetAddressesByName");
    std::vector<INetAddr> addrList;
    int32_t ret = GetAddressesByName(host, netId, addrList);
    if (!reply.WriteInt32(ret)) {
        return ERR_FLATTEN_OBJECT;
    }
    if (ret == ERR_NONE) {
        int32_t size = static_cast<int32_t>(addrList.size());
        if (!reply.WriteInt32(size)) {
            return ERR_FLATTEN_OBJECT;
        }
        for (auto p = addrList.begin(); p != addrList.end(); ++p) {
            sptr<INetAddr> netaddr_ptr = (std::make_unique<INetAddr>(*p)).release();
            if (!INetAddr::Marshalling(reply, netaddr_ptr)) {
                NETMGR_LOG_E("proxy Marshalling failed");
                return ERR_FLATTEN_OBJECT;
            }
        }
    }
    return ret;
}

int32_t NetConnServiceStub::OnGetAddressByName(MessageParcel &data, MessageParcel &reply)
{
    std::string host;
    if (!data.ReadString(host)) {
        return ERR_FLATTEN_OBJECT;
    }
    int32_t netId;
    if (!data.ReadInt32(netId)) {
        return ERR_FLATTEN_OBJECT;
    }
    NETMGR_LOG_D("stub execute GetAddressByName");
    INetAddr addr;
    int32_t ret = GetAddressByName(host, netId, addr);
    if (!reply.WriteInt32(ret)) {
        return ERR_FLATTEN_OBJECT;
    }
    if (ret == ERR_NONE) {
        sptr<INetAddr> netaddr_ptr = (std::make_unique<INetAddr>(addr)).release();
        if (!INetAddr::Marshalling(reply, netaddr_ptr)) {
            NETMGR_LOG_E("proxy Marshalling failed");
            return ERR_FLATTEN_OBJECT;
        }
    }
    return ret;
}

int32_t NetConnServiceStub::OnBindSocket(MessageParcel &data, MessageParcel &reply)
{
    int32_t socket_fd;
    if (!data.ReadInt32(socket_fd)) {
        return ERR_FLATTEN_OBJECT;
    }
    int32_t netId;
    if (!data.ReadInt32(netId)) {
        return ERR_FLATTEN_OBJECT;
    }
    NETMGR_LOG_D("stub execute BindSocket");

    int32_t ret = BindSocket(socket_fd, netId);
    if (!reply.WriteInt32(ret)) {
        return ERR_FLATTEN_OBJECT;
    }
    return ret;
}

int32_t NetConnServiceStub::OnSetAirplaneMode(MessageParcel &data, MessageParcel &reply)
{
    bool state = false;
    if (!data.ReadBool(state)) {
        return ERR_FLATTEN_OBJECT;
    }
    int32_t ret = SetAirplaneMode(state);
    if (!reply.WriteInt32(ret)) {
        return ERR_FLATTEN_OBJECT;
    }
    return ret;
}

int32_t NetConnServiceStub::OnRestoreFactoryData(MessageParcel &data, MessageParcel &reply)
{
    NETMGR_LOG_D("stub execute RestoreFactoryData");
    int32_t ret = RestoreFactoryData();
    if (!reply.WriteInt32(ret)) {
        return ERR_FLATTEN_OBJECT;
    }
    return ret;
}
} // namespace NetManagerStandard
} // namespace OHOS
