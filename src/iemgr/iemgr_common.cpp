//
// Created by Michal Režňák on 8/7/17.
//

#include <cstring>
#include <limits>
#include <utility>
#include <libfds/iemgr.h>
#include "fds_iemgr_todo_name.h"

bool
split_name(const string& str, pair<string, string>& res)
{
    const size_t pos = str.find(':');
    if (str.substr(pos+1).find(':') != str.npos) {
        return false;
    }

    if (pos == str.npos) {
        res.first = "iana";
        res.second = str.substr(pos+1);
    }
    else {
        res.first = str.substr(0, pos);
        res.second = str.substr(pos+1);
    }

    return true;
}

bool
parsed_id_save(fds_iemgr_t* mgr, const fds_iemgr_scope_inter* scope, const uint16_t id)
{
    if (mgr->parsed_ids.find(id) != mgr->parsed_ids.end()) {
        mgr->err_msg = "Element with ID '" +to_string(id)+ "' is defined multiple times in the scope with PEN '" +to_string(scope->head.pen)+ "'";
        return false;
    }

    mgr->parsed_ids.insert(id);
    return true;
}

/**
 * \brief Copy string with postfix '@reverse'
 * \param[in] str String
 * \return Copied string on success, otherwise nullptr
 */
char *
copy_reverse(const char *str)
{
    if (str == nullptr) {
        return nullptr;
    }

    const char *rev = reverse_name;

    auto len = static_cast<const int>(strlen(str) + strlen(rev) + 1);
    auto res = new char[len];
    strcpy(res, (string(str)+rev).c_str());

    return res;
}

char *
copy_str(const char *str)
{
    if (str == nullptr) {
        return nullptr;
    }

    auto res = new char[strlen(str)+1];
    strcpy(res, str);
    return res;
}

fds_iemgr_element_unit
get_data_unit(const char *unit)
{
    if (!strcasecmp(unit,           "none"))
        return FDS_EU_NONE;
    else if (!strcasecmp(unit,      "bits"))
        return FDS_EU_BITS;
    else if (!strcasecmp(unit,      "octets"))
        return FDS_EU_OCTETS;
    else if (!strcasecmp(unit,      "packets"))
        return FDS_EU_PACKETS;
    else if (!strcasecmp(unit,      "flows"))
        return FDS_EU_FLOWS;
    else if (!strcasecmp(unit,      "seconds"))
        return FDS_EU_SECONDS;
    else if (!strcasecmp(unit,      "milliseconds"))
        return FDS_EU_MILLISECONDS;
    else if (!strcasecmp(unit,      "microseconds"))
        return FDS_EU_MICROSECONDS;
    else if (!strcasecmp(unit,      "nanoseconds"))
        return FDS_EU_NANOSECONDS;
    else if (!strcasecmp(unit,      "4-octet words"))
        return FDS_EU_4_OCTET_WORDS;
    else if (!strcasecmp(unit,      "messages"))
        return FDS_EU_MESSAGES;
    else if (!strcasecmp(unit,      "hops"))
        return FDS_EU_HOPS;
    else if (!strcasecmp(unit,      "entries"))
        return FDS_EU_ENTRIES;
    else if (!strcasecmp(unit,      "frames"))
        return FDS_EU_FRAMES;
    else
        return FDS_EU_UNASSIGNED;
}

/**
 * \brief Get semantics of an element
 * \param[in] semantic Semantic of an element in string
 * \return In what semantic is the element
 */
fds_iemgr_element_semantic
get_data_semantic(const char *semantic)
{
    // TODO snmpCounter not defined?
    if (!strcasecmp(semantic,          "default"))
        return FDS_ES_DEFAULT;
    else if (!strcasecmp(semantic,     "quantity"))
        return FDS_ES_QUANTITY;
    else if (!strcasecmp(semantic,     "totalCounter"))
        return FDS_ES_TOTAL_COUNTER;
    else if (!strcasecmp(semantic,     "deltaCounter"))
        return FDS_ES_DELTA_COUNTER;
    else if (!strcasecmp(semantic,     "identifier"))
        return FDS_ES_IDENTIFIER;
    else if (!strcasecmp(semantic,     "flags"))
        return FDS_ES_FLAGS;
    else if (!strcasecmp(semantic,     "list"))
        return FDS_ES_LIST;
    else
        return FDS_ES_UNASSIGNED;
}

/**
 * \brief Get data type of an element
 * \param[in] type Data type in string
 * \return Data type of the element
 */
fds_iemgr_element_type
get_data_type(const char *type)
{
    if (!strcasecmp(type,                    "octetArray"))
        return FDS_ET_OCTET_ARRAY;
    else if (!strcasecmp(type,               "unsigned8"))
        return FDS_ET_UNSIGNED_8;
    else if (!strcasecmp(type,               "unsigned16"))
        return FDS_ET_UNSIGNED_16;
    else if (!strcasecmp(type,               "unsigned32"))
        return FDS_ET_UNSIGNED_32;
    else if(!strcasecmp(type,                "unsigned64"))
        return FDS_ET_UNSIGNED_64;
    else if (!strcasecmp(type,               "signed8"))
        return FDS_ET_SIGNED_8;
    else if (!strcasecmp(type,               "signed16"))
        return FDS_ET_SIGNED_16;
    else if (!strcasecmp(type,               "signed32"))
        return FDS_ET_SIGNED_32;
    else if (!strcasecmp(type,               "signed64"))
        return FDS_ET_SIGNED_64;
    else if (!strcasecmp(type,               "float32"))
        return FDS_ET_FLOAT_32;
    else if (!strcasecmp(type,               "float64"))
        return FDS_ET_FLOAT_64;
    else if (!strcasecmp(type,               "boolean"))
        return FDS_ET_BOOLEAN;
    else if (!strcasecmp(type,               "macAddress"))
        return FDS_ET_MAC_ADDRESS;
    else if (!strcasecmp(type,               "string"))
        return FDS_ET_STRING;
    else if (!strcasecmp(type,               "dateTimeSeconds"))
        return FDS_ET_DATE_TIME_SECONDS;
    else if (!strcasecmp(type,               "dateTimeMilliseconds"))
        return FDS_ET_DATE_TIME_MILLISECONDS;
    else if (!strcasecmp(type,               "dateTimeMicroseconds"))
        return FDS_ET_DATE_TIME_MICROSECONDS;
    else if (!strcasecmp(type,               "dateTimeNanoseconds"))
        return FDS_ET_DATE_TIME_NANOSECONDS;
    else if (!strcasecmp(type,               "ipv4Address"))
        return FDS_ET_IPV4_ADDRESS;
    else if (!strcasecmp(type,               "ipv6Address"))
        return FDS_ET_IPV6_ADDRESS;
    else if (!strcasecmp(type,               "basicList"))
        return FDS_ET_BASIC_LIST;
    else if (!strcasecmp(type,               "subTemplateList"))
        return FDS_ET_SUB_TEMPLATE_LIST;
    else if (!strcasecmp(type,               "subTemplateMultiList"))
        return FDS_ET_SUB_TEMPLATE_MULTILIST;
    else
        return FDS_ET_UNASSIGNED;
}

/**
 * \brief Get element status
 * \param[in] status Element status
 * \return Element status
 */
fds_iemgr_element_status
get_status(const char *status)
{
    if (!strcasecmp(status,      "current"))
        return FDS_ST_CURRENT;
    else if (!strcasecmp(status, "deprecated"))
        return FDS_ST_DEPRECATED;
    else
        return FDS_ST_INVALID;
}

/**
 * \brief Get biflow mode
 * \param[in]  mode Biflow mode in a string
 * \return Biflow mode
 */
fds_iemgr_element_biflow
get_biflow(const char *mode)
{
    if (!strcasecmp(mode,        "pen"))
        return FDS_BW_PEN;
    else if (!strcasecmp(mode,   "none"))
        return FDS_BW_NONE;
    else if (!strcasecmp(mode,   "split"))
        return FDS_BW_SPLIT;
    else if (!strcasecmp(mode,   "individual"))
        return FDS_BW_INDIVIDUAL;
    else
        return FDS_BW_INVALID;
}

/**
 * \brief Check biflow ID and return converted ID
 * \param[in,out] mgr   Manager
 * \param[in]     scope Scope
 * \param[in]     id    ID
 * \return Return ID on success, otherwise return -1
 */
int64_t
get_biflow_id(fds_iemgr_t* mgr, const fds_iemgr_scope_inter* scope, int64_t id)
{
    if (id > uint32_limit) {
        mgr->err_msg = "Number '" +to_string(id)+ "' defined as biflow ID of a scope with PEN '" +to_string(scope->head.pen)+ "' is bigger than limit " +to_string(uint32_limit);
        return -1;
    }
    if (id < 0) {
        mgr->err_msg = "Number '" +to_string(id)+ "' defined as biflow ID of the scope with PEN cannot be negative.";
        return false;
    }

    if (scope->head.biflow_mode == FDS_BW_SPLIT) {
        if (id > 14) { // TODO count from 0 or 1 ?
            mgr->err_msg = "Number '" +to_string(id)+ "' defined as ID of a scope with PEN '" +to_string(scope->head.pen)+ "' must define which bit will be used for biflow SPLIT mode, thus can't be bigger than 14";
            return -1;
        }
    }

    return static_cast<uint32_t>(id);
}

/**
 * \brief Get ID of the element from the value
 * \param[in,out] mgr     Manager
 * \param[out]    elem_id Element ID
 * \param[in]     val     Value
 * \return True on success, otherwise False
 */
bool
get_id(fds_iemgr_t *mgr, uint16_t& elem_id, int64_t val)
{
    if (val > uint15_limit) {
        mgr->err_msg = "Number '" +to_string(val)+ "' defined to the element as an ID is bigger than limit " +to_string(uint15_limit);
        return false;
    }
    if (val < 0) {
        mgr->err_msg = "Number '" +to_string(val)+ "' defined to the element as an ID cannot be negative.";
        return false;
    }

    elem_id = (uint16_t ) val;
    return true;
}

/**
 * \brief Get ID of reverse element
 * \param[in,out] mgr Manager
 * \param[in]     id  ID
 * \return
 */
int
get_biflow_elem_id(fds_iemgr_t* mgr, const int64_t id)
{
    if (id > uint15_limit) {
        mgr->err_msg = "ID '" +to_string(id)+"' defined to the element is bigger than limit " +to_string(uint15_limit)+ ".";
        return -1;
    }
    if (id < 0) {
        mgr->err_msg = "ID '" +to_string(id)+"' defined to the element cannot be negative.";
        return -1;
    }
    return static_cast<uint16_t>(id);
}

/**
 * \brief Get PEN of the scope from the value
 * \param[in,out] mgr       Manager
 * \param[out]    scope_pen Scope PEN
 * \param[in]     val       Value
 * \return True on success, otherwise False
 */
bool
get_pen(fds_iemgr_t *mgr, uint32_t& scope_pen, const int64_t val)
{
    if (val > uint32_limit) {
        mgr->err_msg = "Number '" +to_string(val)+ "' defined to the scope as PEN is bigger than limit " +to_string(uint32_limit);
        return false;
    }
    if (val < 0) {
        mgr->err_msg = "Number '" +to_string(val)+ "' defined to the scope as PEN cannot be negative.";
        return false;
    }

    scope_pen = (uint32_t) val;
    return true;
}
