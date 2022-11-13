#include "sai.h"
#include "stub_sai.h"
#include "assert.h"


static const sai_attribute_entry_t lag_attribs[] = {
    { SAI_LAG_ATTR_PORT_LIST, false, false, false, true,
      "List of ports in LAG", SAI_ATTR_VAL_TYPE_OBJLIST },
    { END_FUNCTIONALITY_ATTRIBS_ID, false, false, false, false,
      "", SAI_ATTR_VAL_TYPE_UNDETERMINED }
};

static const sai_attribute_entry_t lag_member_attribs[] = {
    { SAI_LAG_MEMBER_ATTR_LAG_ID, true, true, false, true,
      "LAG ID", SAI_ATTR_VAL_TYPE_OID },
    { SAI_LAG_MEMBER_ATTR_PORT_ID, true, true, false, true,
      "PORT ID", SAI_ATTR_VAL_TYPE_OID },
    { END_FUNCTIONALITY_ATTRIBS_ID, false, false, false, false,
      "", SAI_ATTR_VAL_TYPE_UNDETERMINED }
};


sai_status_t stub_create_lag(
    _Out_ sai_object_id_t* lag_id,
    _In_ uint32_t attr_count,
    _In_ sai_attribute_t *attr_list)
{
    static int32_t next_lag_id = 1;
    sai_status_t status;
    status = stub_create_object(SAI_OBJECT_TYPE_LAG, next_lag_id++, lag_id);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Cannot create a LAG OID\n");
        return status;
    }
    char list_str[MAX_LIST_VALUE_STR_LEN];
    sai_attr_list_to_str(attr_count, attr_list, lag_attribs, MAX_LIST_VALUE_STR_LEN, list_str);
    printf("CREATE LAG: 0x%lX (%s)\n", *lag_id, list_str);
    return SAI_STATUS_SUCCESS; 
}

sai_status_t stub_remove_lag(
    _In_ sai_object_id_t  lag_id)
{
    printf("Remove LAG OID 0x%lX\n", lag_id);
    return SAI_STATUS_SUCCESS;
}

sai_status_t stub_set_lag_attribute(
    _In_ sai_object_id_t  lag_id,
    _In_ const sai_attribute_t *attr)
{
    printf("Call set_lag_attribute function.\n");
    printf("LAG OID: 0x%lX\n", lag_id);
    return SAI_STATUS_SUCCESS;
}

sai_status_t stub_get_lag_attribute(
    _In_ sai_object_id_t lag_id,
    _In_ uint32_t attr_count,
    _Inout_ sai_attribute_t *attr_list)
{
    printf("Call get_lag_attribute function.\n");
    printf("LAG OID: 0x%lX\n", lag_id);
    return SAI_STATUS_SUCCESS;
}

sai_status_t stub_create_lag_member(
    _Out_ sai_object_id_t* lag_member_id,
    _In_ uint32_t attr_count,
    _In_ sai_attribute_t *attr_list)
{
    static int32_t next_lag_member_id = 1;
    sai_status_t status;
    status = stub_create_object(SAI_OBJECT_TYPE_LAG_MEMBER, next_lag_member_id++, lag_member_id);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Cannot create a LAG member OID\n");
        return status;
    }
    char list_str[MAX_LIST_VALUE_STR_LEN];
    sai_attr_list_to_str(attr_count, attr_list, lag_member_attribs, MAX_LIST_VALUE_STR_LEN, list_str);
    printf("CREATE LAG MEMBER: 0x%lX (%s)\n", *lag_member_id, list_str);
    return SAI_STATUS_SUCCESS;
}

sai_status_t stub_remove_lag_member(
    _In_ sai_object_id_t  lag_member_id)
{
    printf("Remove LAG member OID 0x%lX\n", lag_member_id);
    return SAI_STATUS_SUCCESS;
}

sai_status_t stub_set_lag_member_attribute(
    _In_ sai_object_id_t  lag_member_id,
    _In_ const sai_attribute_t *attr)
{
    printf("Call set_lag_member_attribute function.\n");
    printf("LAG MEMBER OID: 0x%lX\n", lag_member_id);
    return SAI_STATUS_SUCCESS;
}

sai_status_t stub_get_lag_member_attribute(
    _In_ sai_object_id_t lag_member_id,
    _In_ uint32_t attr_count,
    _Inout_ sai_attribute_t *attr_list)
{
    printf("Call get_lag_member_attribute function.\n");
    printf("LAG MEMBER OID: 0x%lX\n", lag_member_id);
    return SAI_STATUS_SUCCESS;
}

const sai_lag_api_t lag_api = {
    stub_create_lag,
    stub_remove_lag,
    stub_set_lag_attribute,
    stub_get_lag_attribute,
    stub_create_lag_member,
    stub_remove_lag_member,
    stub_set_lag_member_attribute,
    stub_get_lag_member_attribute
};


