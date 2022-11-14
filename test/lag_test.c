#include <stdio.h>
#include <stdlib.h>
#include "sai.h"

#define LAG_MEMBER_ATTR_COUNT 2

const char* test_profile_get_value(
    _In_ sai_switch_profile_id_t profile_id,
    _In_ const char* variable)
{
    return 0;
}

int test_profile_get_next_value(
    _In_ sai_switch_profile_id_t profile_id,
    _Out_ const char** variable,
    _Out_ const char** value)
{
    return -1;
}

const service_method_table_t test_services = {
    test_profile_get_value,
    test_profile_get_next_value
};

int main()
{
    sai_status_t        status;

    // LAG
    sai_lag_api_t      *lag_api;
    sai_object_id_t     lag_oid[2];
    sai_object_id_t     lag_member_oid[4];

    // Switch (is needed to get port OIDs)
    sai_switch_api_t         *switch_api;
    sai_attribute_t           attrs[2];
    sai_switch_notification_t notifications;
    sai_object_id_t           port_list[64];

    status = sai_api_initialize(0, &test_services);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Failed to initialize SAI, status = %d\n", status);
        exit(1);
    }

    // Switch and port OIDs
    status = sai_api_query(SAI_API_SWITCH, (void**)&switch_api);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Error: sai_api_query returns error.\n");
        exit(1);
    }
    status = switch_api->initialize_switch(0, "HW_ID", 0, &notifications);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Error: switch initialization is not successul\n");
        exit(1);
    }
    attrs[0].id = SAI_SWITCH_ATTR_PORT_LIST;
    attrs[0].value.objlist.list = port_list;
    attrs[0].value.objlist.count = 64;
    status = switch_api->get_switch_attribute(1, attrs);

    // LAG and LAG members
    status = sai_api_query(SAI_API_LAG, (void**)&lag_api);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Failed to query LAG API, status=%d\n", status);
        return 1;
    }

    status = lag_api->create_lag(lag_oid + 0, 0, NULL);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Failed to create a LAG, status=%d\n", status);
        return 1;
    }
    status = lag_api->create_lag(lag_oid + 1, 0, NULL);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Failed to create a LAG, status=%d\n", status);
        return 1;
    }
    for (int i = 0; i <= 3; i++) {
        sai_attribute_t lag_member_attrs[LAG_MEMBER_ATTR_COUNT] = {
            [0] = {.id = SAI_LAG_MEMBER_ATTR_LAG_ID, .value.oid = (i <= 1) ? lag_oid[0] : lag_oid[1]},
            [1] = {.id = SAI_LAG_MEMBER_ATTR_PORT_ID, .value.oid = port_list[i]}
        };
        status = lag_api->create_lag_member(lag_member_oid + i, LAG_MEMBER_ATTR_COUNT, lag_member_attrs);
    }

    sai_attribute_t attr_to_get_from_lag_member0 = {.id = SAI_LAG_MEMBER_ATTR_LAG_ID};
    printf("Get LAG member 0 attributes\n");
    status = lag_api->get_lag_member_attribute(lag_member_oid[0], 1, &attr_to_get_from_lag_member0);
    if (status != SAI_STATUS_SUCCESS) { 
        printf("Failed to get_lag_member_attribute, status=%d\n", status);
        return 1;
    }
    printf("Ok!\n");

    sai_attribute_t attr_to_get_from_lag_member2 = {.id = SAI_LAG_MEMBER_ATTR_PORT_ID};
    printf("Get LAG member 2 attributes\n");
    status = lag_api->get_lag_member_attribute(lag_member_oid[2], 1, &attr_to_get_from_lag_member2);
    if (status != SAI_STATUS_SUCCESS) { 
        printf("Failed to get_lag_member_attribute, status=%d\n", status);
        return 1;
    }
    printf("Ok!\n");

    sai_object_id_t lag0_port_list[2];
    sai_attribute_t attr_to_get_from_lag0 = {
        .id = SAI_LAG_ATTR_PORT_LIST,
        .value.objlist.list = lag0_port_list,
        .value.objlist.count = 2
    };
    printf("Get LAG 0 attribute PORT LIST\n");
    status = lag_api->get_lag_attribute(lag_oid[0], 1, &attr_to_get_from_lag0);
    if (status != SAI_STATUS_SUCCESS) { 
        printf("Failed to get_lag_attribute, status=%d\n", status);
        return 1;
    }
    printf("Ok!\n");

    sai_object_id_t lag1_port_list[2];
    sai_attribute_t attr_to_get_from_lag1 = {
        .id = SAI_LAG_ATTR_PORT_LIST,
        .value.objlist.list = lag1_port_list,
        .value.objlist.count = 2
    };
    printf("Get LAG 1 attribute PORT LIST\n");
    status = lag_api->get_lag_attribute(lag_oid[1], 1, &attr_to_get_from_lag1);
    if (status != SAI_STATUS_SUCCESS) { 
        printf("Failed to get_lag_attribute, status=%d\n", status);
        return 1;
    }
    printf("Ok!\n");

    status = lag_api->remove_lag_member(lag_member_oid[1]);
    if (status != SAI_STATUS_SUCCESS) { 
        printf("Failed to remove LAG member, status=%d\n", status);
        return 1;
    }
    sai_object_id_t lag0_port_list_2[1];
    sai_attribute_t attr_to_get_from_lag0_2 = {
        .id = SAI_LAG_ATTR_PORT_LIST,
        .value.objlist.list = lag0_port_list_2,
        .value.objlist.count = 1
    };
    printf("Get LAG 0 attribute PORT LIST\n");
    status = lag_api->get_lag_attribute(lag_oid[0], 1, &attr_to_get_from_lag0_2);
    if (status != SAI_STATUS_SUCCESS) { 
        printf("Failed to get_lag_attribute, status=%d\n", status);
        return 1;
    }
    printf("Ok!\n");

    status = lag_api->remove_lag_member(lag_member_oid[2]);
    if (status != SAI_STATUS_SUCCESS) { 
        printf("Failed to remove LAG member, status=%d\n", status);
        return 1;
    }

    printf("Remove LAG with a LAG member. MUST RETURN ERROR.\n");
    status = lag_api->remove_lag(lag_oid[1]);
    if (status == SAI_STATUS_SUCCESS) { 
        printf("Test failed: function returned success!");
        return 1;
    }

    status = lag_api->remove_lag_member(lag_member_oid[0]);
    if (status != SAI_STATUS_SUCCESS) { 
        printf("Failed to remove LAG member, status=%d\n", status);
        return 1;
    }
    status = lag_api->remove_lag_member(lag_member_oid[3]);
    if (status != SAI_STATUS_SUCCESS) { 
        printf("Failed to remove LAG member, status=%d\n", status);
        return 1;
    }

    status = lag_api->remove_lag(lag_oid[1]);
    if (status != SAI_STATUS_SUCCESS) { 
        printf("Failed to remove LAG, status=%d\n", status);
        return 1;
    }
    status = lag_api->remove_lag(lag_oid[0]);
    if (status != SAI_STATUS_SUCCESS) { 
        printf("Failed to remove LAG, status=%d\n", status);
        return 1;
    }

    status = sai_api_uninitialize();

    return 0;
}

