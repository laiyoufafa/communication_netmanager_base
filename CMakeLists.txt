cmake_minimum_required(VERSION 3.20)
project(netmanager_base)

set(CMAKE_CXX_STANDARD 23)

include_directories(frameworks/js/napi/common)
include_directories(frameworks/js/napi/netconn/include)
include_directories(frameworks/js/napi/netpolicy/include)
include_directories(frameworks/js/napi/netstats/include)
include_directories(frameworks/native/netmanagernative)
include_directories(interfaces)
include_directories(interfaces/innerkits)
include_directories(interfaces/innerkits/dnsresolverclient)
include_directories(interfaces/innerkits/dnsresolverclient/include)
include_directories(interfaces/innerkits/dnsresolverclient/include/proxy)
include_directories(interfaces/innerkits/include)
include_directories(interfaces/innerkits/netconnclient)
include_directories(interfaces/innerkits/netconnclient/include)
include_directories(interfaces/innerkits/netconnclient/include/proxy)
include_directories(interfaces/innerkits/netmanagernative)
include_directories(interfaces/innerkits/netmanagernative/include)
include_directories(interfaces/innerkits/netpolicyclient)
include_directories(interfaces/innerkits/netpolicyclient/include)
include_directories(interfaces/innerkits/netpolicyclient/include/proxy)
include_directories(interfaces/innerkits/netstatsclient)
include_directories(interfaces/innerkits/netstatsclient/include)
include_directories(interfaces/innerkits/netstatsclient/include/proxy)
include_directories(services/common/include)
include_directories(services/dnsresolvermanager/include)
include_directories(services/dnsresolvermanager/include/stub)
include_directories(services/netconnmanager/include)
include_directories(services/netconnmanager/include/stub)
include_directories(services/netsyscontroller/include)
include_directories(services/netmanagernative/include)
include_directories(services/netpolicymanager/include)
include_directories(services/netpolicymanager/include/stub)
include_directories(services/netstatsmanager/include)
include_directories(services/netstatsmanager/include/stub)
include_directories(test/netconnmanager/unittest/net_conn_manager_test)
include_directories(test/netpolicymanager/unittest/net_policy_manager_test)
include_directories(test/netstatsmanager/unittest/net_stats_manager_test)
include_directories(utils/base_async_work)
include_directories(utils/base_async_work/include)
include_directories(utils/base_context/include)
include_directories(utils/common_utils/include)
include_directories(utils/event_manager/include)
include_directories(utils/log/include)
include_directories(utils/module_template/include)
include_directories(utils/napi_utils/include)
include_directories(services/netmanagernative/include/netsys)

add_executable(netmanager_base
        frameworks/js/napi/common/base_context.h
        frameworks/js/napi/common/event_context.h
        frameworks/js/napi/common/napi_common.cpp
        frameworks/js/napi/common/napi_common.h
        frameworks/js/napi/netconn/include/event_listener_context.h
        frameworks/js/napi/netconn/include/napi_net_conn.h
        frameworks/js/napi/netconn/include/napi_net_conn_observer.h
        frameworks/js/napi/netconn/include/napi_net_connection.h
        frameworks/js/napi/netconn/src/event_listener_context.cpp
        frameworks/js/napi/netconn/src/napi_net_conn.cpp
        frameworks/js/napi/netconn/src/napi_net_conn_observer.cpp
        frameworks/js/napi/netconn/src/napi_net_connection.cpp
        frameworks/js/napi/netpolicy/include/napi_net_policy.h
        frameworks/js/napi/netpolicy/include/napi_net_policy_observer.h
        frameworks/js/napi/netpolicy/include/net_policy_event_listener_context.h
        frameworks/js/napi/netpolicy/src/napi_net_policy.cpp
        frameworks/js/napi/netpolicy/src/napi_net_policy_observer.cpp
        frameworks/js/napi/netpolicy/src/net_policy_event_listener_context.cpp
        frameworks/js/napi/netstats/include/napi_net_stats.h
        frameworks/js/napi/netstats/include/net_stats_callback.h
        frameworks/js/napi/netstats/include/net_stats_event_listener_manager.h
        frameworks/js/napi/netstats/src/napi_net_stats.cpp
        frameworks/js/napi/netstats/src/net_stats_callback.cpp
        frameworks/js/napi/netstats/src/net_stats_event_listener_manager.cpp
        frameworks/native/dnsresolverclient/src/proxy/dns_resolver_service_proxy.cpp
        frameworks/native/dnsresolverclient/src/dns_addr_info.cpp
        frameworks/native/dnsresolverclient/src/dns_resolver_client.cpp
        frameworks/native/netconnclient/src/proxy/net_conn_callback_stub.cpp
        frameworks/native/netconnclient/src/proxy/net_conn_service_proxy.cpp
        frameworks/native/netconnclient/src/proxy/net_detection_callback_stub.cpp
        frameworks/native/netconnclient/src/proxy/net_supplier_callback_stub.cpp
        frameworks/native/netconnclient/src/inet_addr.cpp
        frameworks/native/netconnclient/src/net_all_capabilities.cpp
        frameworks/native/netconnclient/src/net_conn_client.cpp
        frameworks/native/netconnclient/src/net_handle.cpp
        frameworks/native/netconnclient/src/net_link_info.cpp
        frameworks/native/netconnclient/src/net_specifier.cpp
        frameworks/native/netconnclient/src/net_supplier_callback_base.cpp
        frameworks/native/netconnclient/src/net_supplier_info.cpp
        frameworks/native/netconnclient/src/route.cpp
        frameworks/native/netmanagernative/dhcp_result_parcel.cpp
        frameworks/native/netmanagernative/dnsresolver_params_parcel.cpp
        frameworks/native/netmanagernative/netsys_addr_info_parcel.cpp
        frameworks/native/netmanagernative/netsys_native_service_proxy.cpp
        frameworks/native/netmanagernative/netsys_native_service_proxy.h
        frameworks/native/netmanagernative/notify_callback_proxy.cpp
        frameworks/native/netmanagernative/notify_callback_proxy.h
        frameworks/native/netpolicyclient/src/proxy/net_policy_callback_stub.cpp
        frameworks/native/netpolicyclient/src/proxy/net_policy_service_proxy.cpp
        frameworks/native/netpolicyclient/src/net_policy_cellular_policy.cpp
        frameworks/native/netpolicyclient/src/net_policy_client.cpp
        frameworks/native/netpolicyclient/src/net_policy_quota_policy.cpp
        frameworks/native/netstatsclient/src/proxy/net_stats_callback_stub.cpp
        frameworks/native/netstatsclient/src/proxy/net_stats_service_proxy.cpp
        frameworks/native/netstatsclient/src/data_flow_statistics.cpp
        frameworks/native/netstatsclient/src/net_stats_client.cpp
        frameworks/native/netstatsclient/src/net_stats_info.cpp
        interfaces/innerkits/dnsresolverclient/include/proxy/dns_resolver_service_proxy.h
        interfaces/innerkits/dnsresolverclient/include/proxy/i_dns_resolver_service.h
        interfaces/innerkits/dnsresolverclient/include/dns_addr_info.h
        interfaces/innerkits/dnsresolverclient/include/dns_resolver_client.h
        interfaces/innerkits/dnsresolverclient/include/dns_resolver_constants.h
        interfaces/innerkits/include/inet_addr.h
        interfaces/innerkits/include/net_manager_constants.h
        interfaces/innerkits/netconnclient/include/proxy/i_net_conn_callback.h
        interfaces/innerkits/netconnclient/include/proxy/i_net_conn_service.h
        interfaces/innerkits/netconnclient/include/proxy/i_net_detection_callback.h
        interfaces/innerkits/netconnclient/include/proxy/i_net_supplier_callback.h
        interfaces/innerkits/netconnclient/include/proxy/net_conn_callback_stub.h
        interfaces/innerkits/netconnclient/include/proxy/net_conn_service_proxy.h
        interfaces/innerkits/netconnclient/include/proxy/net_detection_callback_stub.h
        interfaces/innerkits/netconnclient/include/proxy/net_supplier_callback_stub.h
        interfaces/innerkits/netconnclient/include/net_all_capabilities.h
        interfaces/innerkits/netconnclient/include/net_conn_client.h
        interfaces/innerkits/netconnclient/include/net_conn_constants.h
        interfaces/innerkits/netconnclient/include/net_handle.h
        interfaces/innerkits/netconnclient/include/net_link_info.h
        interfaces/innerkits/netconnclient/include/net_specifier.h
        interfaces/innerkits/netconnclient/include/net_supplier_callback_base.h
        interfaces/innerkits/netconnclient/include/net_supplier_info.h
        interfaces/innerkits/netconnclient/include/route.h
        interfaces/innerkits/netmanagernative/include/dhcp_result_parcel.h
        interfaces/innerkits/netmanagernative/include/dnsresolver_params_parcel.h
        interfaces/innerkits/netmanagernative/include/i_netsys_service.h
        interfaces/innerkits/netmanagernative/include/i_notify_callback.h
        interfaces/innerkits/netmanagernative/include/netsys_addr_info_parcel.h
        interfaces/innerkits/netmanagernative/include/netnative_log_wrapper.h
        interfaces/innerkits/netmanagernative/include/notify_callback_stub.h
        interfaces/innerkits/netpolicyclient/include/proxy/i_net_policy_callback.h
        interfaces/innerkits/netpolicyclient/include/proxy/i_net_policy_service.h
        interfaces/innerkits/netpolicyclient/include/proxy/net_policy_callback_stub.h
        interfaces/innerkits/netpolicyclient/include/proxy/net_policy_service_proxy.h
        interfaces/innerkits/netpolicyclient/include/net_policy_cellular_policy.h
        interfaces/innerkits/netpolicyclient/include/net_policy_client.h
        interfaces/innerkits/netpolicyclient/include/net_policy_constants.h
        interfaces/innerkits/netpolicyclient/include/net_policy_quota_policy.h
        interfaces/innerkits/netstatsclient/include/proxy/i_net_stats_callback.h
        interfaces/innerkits/netstatsclient/include/proxy/i_net_stats_service.h
        interfaces/innerkits/netstatsclient/include/proxy/net_stats_callback_stub.h
        interfaces/innerkits/netstatsclient/include/proxy/net_stats_service_proxy.h
        interfaces/innerkits/netstatsclient/include/data_flow_statistics.h
        interfaces/innerkits/netstatsclient/include/net_stats_client.h
        interfaces/innerkits/netstatsclient/include/net_stats_constants.h
        interfaces/innerkits/netstatsclient/include/net_stats_info.h
        services/common/include/broadcast_manager.h
        services/common/include/dns_base_service.h
        services/common/include/net_conn_base_service.h
        services/common/include/net_ethernet_base_service.h
        services/common/include/net_manager_center.h
        services/common/include/net_policy_base_service.h
        services/common/include/net_stats_base_service.h
        services/common/include/route_utils.h
        services/common/include/timer.h
        services/common/src/broadcast_manager.cpp
        services/common/src/net_manager_center.cpp
        services/common/src/route_utils.cpp
        services/dnsresolvermanager/include/stub/dns_resolver_service_stub.h
        services/dnsresolvermanager/include/dns_resolver_service.h
        services/dnsresolvermanager/include/dns_service_iface.h
        services/dnsresolvermanager/src/stub/dns_resolver_service_stub.cpp
        services/dnsresolvermanager/src/dns_resolver_service.cpp
        services/dnsresolvermanager/src/dns_service_iface.cpp
        services/netconnmanager/include/stub/net_conn_callback_proxy.h
        services/netconnmanager/include/stub/net_conn_service_stub.h
        services/netconnmanager/include/stub/net_detection_callback_proxy.h
        services/netconnmanager/include/stub/net_supplier_callback_proxy.h
        services/netconnmanager/include/http_request.h
        services/netconnmanager/include/net_activate.h
        services/netconnmanager/include/net_conn_service.h
        services/netconnmanager/include/net_conn_service_iface.h
        services/netconnmanager/include/net_conn_types.h
        services/netconnmanager/include/net_monitor.h
        services/netconnmanager/include/net_score.h
        services/netconnmanager/include/net_supplier.h
        services/netconnmanager/include/network.h
        services/netconnmanager/src/stub/net_conn_callback_proxy.cpp
        services/netconnmanager/src/stub/net_conn_service_stub.cpp
        services/netconnmanager/src/stub/net_detection_callback_proxy.cpp
        services/netconnmanager/src/stub/net_supplier_callback_proxy.cpp
        services/netconnmanager/src/http_request.cpp
        services/netconnmanager/src/net_activate.cpp
        services/netconnmanager/src/net_conn_service.cpp
        services/netconnmanager/src/net_conn_service_iface.cpp
        services/netconnmanager/src/net_monitor.cpp
        services/netconnmanager/src/net_score.cpp
        services/netconnmanager/src/net_supplier.cpp
        services/netconnmanager/src/network.cpp
        services/netsyscontroller/include/i_netsys_controller_service.h
        services/netsyscontroller/include/mock_netsys_native_client.h
        services/netsyscontroller/include/netsys_controller.h
        services/netsyscontroller/include/netsys_controller_callback.h
        services/netsyscontroller/include/netsys_controller_define.h
        services/netsyscontroller/include/netsys_controller_service_impl.h
        services/netsyscontroller/include/netsys_native_client.h
        services/netsyscontroller/src/mock_netsys_native_client.cpp
        services/netsyscontroller/src/netsys_controller.cpp
        services/netsyscontroller/src/netsys_controller_service_impl.cpp
        services/netsyscontroller/src/netsys_native_client.cpp
        services/netmanagernative/include/netsys_native_service.h
        services/netmanagernative/include/netsys_native_service_stub.h
        services/netmanagernative/src/dhcp_controller.cpp
        services/netmanagernative/src/netsys_native_service.cpp
        services/netmanagernative/src/netsys_native_service_stub.cpp
        services/netmanagernative/src/notify_callback_stub.cpp
        services/netpolicymanager/include/stub/net_policy_callback_proxy.h
        services/netpolicymanager/include/stub/net_policy_service_stub.h
        services/netpolicymanager/include/net_policy_callback.h
        services/netpolicymanager/include/net_policy_define.h
        services/netpolicymanager/include/net_policy_file.h
        services/netpolicymanager/include/net_policy_firewall.h
        services/netpolicymanager/include/net_policy_service.h
        services/netpolicymanager/include/net_policy_service_common.h
        services/netpolicymanager/include/net_policy_traffic.h
        services/netpolicymanager/src/stub/net_policy_callback_proxy.cpp
        services/netpolicymanager/src/stub/net_policy_service_stub.cpp
        services/netpolicymanager/src/net_policy_callback.cpp
        services/netpolicymanager/src/net_policy_file.cpp
        services/netpolicymanager/src/net_policy_firewall.cpp
        services/netpolicymanager/src/net_policy_service.cpp
        services/netpolicymanager/src/net_policy_service_common.cpp
        services/netpolicymanager/src/net_policy_traffic.cpp
        services/netstatsmanager/include/stub/net_stats_callback_proxy.h
        services/netstatsmanager/include/stub/net_stats_service_stub.h
        services/netstatsmanager/include/net_stats_callback.h
        services/netstatsmanager/include/net_stats_csv.h
        services/netstatsmanager/include/net_stats_listener.h
        services/netstatsmanager/include/net_stats_service.h
        services/netstatsmanager/include/net_stats_service_iface.h
        services/netstatsmanager/src/stub/net_stats_callback_proxy.cpp
        services/netstatsmanager/src/stub/net_stats_service_stub.cpp
        services/netstatsmanager/src/net_stats_callback.cpp
        services/netstatsmanager/src/net_stats_csv.cpp
        services/netstatsmanager/src/net_stats_listener.cpp
        services/netstatsmanager/src/net_stats_service.cpp
        services/netstatsmanager/src/net_stats_service_iface.cpp
        test/dnsresolvermanager/unittest/dns_resolver_manager_test/dns_resolver_manager_test.cpp
        test/netconnmanager/unittest/net_conn_manager_test/net_conn_callback_test.cpp
        test/netconnmanager/unittest/net_conn_manager_test/net_conn_callback_test.h
        test/netconnmanager/unittest/net_conn_manager_test/net_conn_manager_test.cpp
        test/netconnmanager/unittest/net_conn_manager_test/net_detection_callback_test.cpp
        test/netconnmanager/unittest/net_conn_manager_test/net_detection_callback_test.h
        test/netconnmanager/unittest/net_conn_manager_test/net_handle_test.cpp
        test/netconnmanager/unittest/net_conn_manager_test/net_score_test.cpp
        test/netconnmanager/unittest/net_conn_manager_test/route_utils_test.cpp
        test/netmanagernative/unittest/network_route_test.cpp
        test/netmanagernative/unittest/resolver_config_test.cpp
        test/netpolicymanager/unittest/net_policy_manager_test/net_policy_callback_test.cpp
        test/netpolicymanager/unittest/net_policy_manager_test/net_policy_callback_test.h
        test/netpolicymanager/unittest/net_policy_manager_test/net_policy_manager_test.cpp
        test/netstatsmanager/unittest/net_stats_manager_test/net_stats_callback_test.cpp
        test/netstatsmanager/unittest/net_stats_manager_test/net_stats_callback_test.h
        test/netstatsmanager/unittest/net_stats_manager_test/net_stats_manager_test.cpp
        utils/base_async_work/include/netmanager_base_base_async_work.h
        utils/base_context/include/netmanager_base_base_context.h
        utils/base_context/src/netmanager_base_base_context.cpp
        utils/common_utils/include/netmanager_base_common_utils.h
        utils/common_utils/src/netmanager_base_common_utils.cpp
        utils/event_manager/include/netmanager_base_event_listener.h
        utils/event_manager/include/netmanager_base_event_manager.h
        utils/event_manager/src/netmanager_base_event_listener.cpp
        utils/event_manager/src/netmanager_base_event_manager.cpp
        utils/log/include/net_mgr_log_wrapper.h
        utils/log/include/netmanager_base_log.h
        utils/log/src/net_mgr_log_wrapper.cpp
        services/netmanagernative/src/netsys/network_controller.cpp
        utils/module_template/include/netmanager_base_module_template.h
        utils/module_template/src/netmanager_base_module_template.cpp
        utils/napi_utils/include/netmanager_base_napi_utils.h
        utils/napi_utils/src/netmanager_base_napi_utils.cpp)

include_directories(
        ../../arkui/napi/interfaces/kits
        ../../arkui/napi/interfaces/inner_api
        ../../arkui/napi/native_engine/impl/quickjs
        ../../arkui/napi/
        ../../../third_party/node/src
)

include_directories(utils/napi_utils/include)
include_directories(utils/common_utils/include)
include_directories(utils/event_manager/include)
include_directories(utils/base_context/include)
include_directories(utils/base_async_work/include)
include_directories(utils/module_template/include)
include_directories(utils/log/include)

include_directories(../../../utils/native/base/include/)
include_directories(../../../base/hiviewdfx/hilog/interfaces/native/innerkits/include)
include_directories(../../../third_party/quickjs)
include_directories(../../../third_party/googletest/googletest/include)
include_directories(../../../third_party/libuv/include)

include_directories(../../../for_linux)
include_directories(../../../foundation/distributedschedule/samgr/interfaces/innerkits/samgr_proxy/include)
include_directories(../../../foundation/distributedschedule/samgr/interfaces/innerkits/common/include)
include_directories(../../../foundation/distributedschedule/samgr/interfaces/innerkits/lsamgr/include)
include_directories(../../../foundation/communication/ipc/interfaces/innerkits/ipc_core/include)
include_directories(../../../foundation/distributedschedule/safwk/services/safwk/include/)
include_directories(../../../base/notification/common_event_service/interfaces/innerkits/native/include)
include_directories(../../../third_party/curl/include/)
include_directories(../wifi/dhcp/services/mgr_service/include)
include_directories(../wifi/dhcp/services/mgr_service/interfaces)
include_directories(../../aafwk/standard/interfaces/innerkits/want/include/ohos/aafwk/content)

link_directories(../../../utils/native/base/cmake-build-debug/src/securec)
link_directories(../../../foundation/arkui/napi/cmake-build-debug)
link_directories(../../../third_party/quickjs)
link_directories(../../../third_party/googletest/cmake-build-debug/googlemock/gtest)
link_directories(../../../third_party/googletest/cmake-build-debug/googlemock)
link_directories(../../../third_party/libuv/cmake-build-debug)

link_directories(cmake-build-debug/utils)

add_compile_definitions(NETMGR_DEBUG)

add_subdirectory(utils)
add_subdirectory(frameworks/js/napi/connection)
add_subdirectory(frameworks/js/napi/network)
