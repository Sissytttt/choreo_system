// generated from rosidl_typesupport_c/resource/idl__type_support.cpp.em
// with input from dance_interfaces:action/Dance.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "dance_interfaces/action/detail/dance__struct.h"
#include "dance_interfaces/action/detail/dance__type_support.h"
#include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/message_type_support_dispatch.h"
#include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_c/visibility_control.h"
#include "rosidl_typesupport_interface/macros.h"

namespace dance_interfaces
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _Dance_Goal_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _Dance_Goal_type_support_ids_t;

static const _Dance_Goal_type_support_ids_t _Dance_Goal_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _Dance_Goal_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _Dance_Goal_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _Dance_Goal_type_support_symbol_names_t _Dance_Goal_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, dance_interfaces, action, Dance_Goal)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, dance_interfaces, action, Dance_Goal)),
  }
};

typedef struct _Dance_Goal_type_support_data_t
{
  void * data[2];
} _Dance_Goal_type_support_data_t;

static _Dance_Goal_type_support_data_t _Dance_Goal_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _Dance_Goal_message_typesupport_map = {
  2,
  "dance_interfaces",
  &_Dance_Goal_message_typesupport_ids.typesupport_identifier[0],
  &_Dance_Goal_message_typesupport_symbol_names.symbol_name[0],
  &_Dance_Goal_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t Dance_Goal_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_Dance_Goal_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace dance_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, dance_interfaces, action, Dance_Goal)() {
  return &::dance_interfaces::action::rosidl_typesupport_c::Dance_Goal_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "dance_interfaces/action/detail/dance__struct.h"
// already included above
// #include "dance_interfaces/action/detail/dance__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace dance_interfaces
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _Dance_Result_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _Dance_Result_type_support_ids_t;

static const _Dance_Result_type_support_ids_t _Dance_Result_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _Dance_Result_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _Dance_Result_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _Dance_Result_type_support_symbol_names_t _Dance_Result_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, dance_interfaces, action, Dance_Result)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, dance_interfaces, action, Dance_Result)),
  }
};

typedef struct _Dance_Result_type_support_data_t
{
  void * data[2];
} _Dance_Result_type_support_data_t;

static _Dance_Result_type_support_data_t _Dance_Result_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _Dance_Result_message_typesupport_map = {
  2,
  "dance_interfaces",
  &_Dance_Result_message_typesupport_ids.typesupport_identifier[0],
  &_Dance_Result_message_typesupport_symbol_names.symbol_name[0],
  &_Dance_Result_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t Dance_Result_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_Dance_Result_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace dance_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, dance_interfaces, action, Dance_Result)() {
  return &::dance_interfaces::action::rosidl_typesupport_c::Dance_Result_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "dance_interfaces/action/detail/dance__struct.h"
// already included above
// #include "dance_interfaces/action/detail/dance__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace dance_interfaces
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _Dance_Feedback_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _Dance_Feedback_type_support_ids_t;

static const _Dance_Feedback_type_support_ids_t _Dance_Feedback_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _Dance_Feedback_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _Dance_Feedback_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _Dance_Feedback_type_support_symbol_names_t _Dance_Feedback_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, dance_interfaces, action, Dance_Feedback)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, dance_interfaces, action, Dance_Feedback)),
  }
};

typedef struct _Dance_Feedback_type_support_data_t
{
  void * data[2];
} _Dance_Feedback_type_support_data_t;

static _Dance_Feedback_type_support_data_t _Dance_Feedback_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _Dance_Feedback_message_typesupport_map = {
  2,
  "dance_interfaces",
  &_Dance_Feedback_message_typesupport_ids.typesupport_identifier[0],
  &_Dance_Feedback_message_typesupport_symbol_names.symbol_name[0],
  &_Dance_Feedback_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t Dance_Feedback_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_Dance_Feedback_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace dance_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, dance_interfaces, action, Dance_Feedback)() {
  return &::dance_interfaces::action::rosidl_typesupport_c::Dance_Feedback_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "dance_interfaces/action/detail/dance__struct.h"
// already included above
// #include "dance_interfaces/action/detail/dance__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace dance_interfaces
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _Dance_SendGoal_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _Dance_SendGoal_Request_type_support_ids_t;

static const _Dance_SendGoal_Request_type_support_ids_t _Dance_SendGoal_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _Dance_SendGoal_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _Dance_SendGoal_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _Dance_SendGoal_Request_type_support_symbol_names_t _Dance_SendGoal_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, dance_interfaces, action, Dance_SendGoal_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, dance_interfaces, action, Dance_SendGoal_Request)),
  }
};

typedef struct _Dance_SendGoal_Request_type_support_data_t
{
  void * data[2];
} _Dance_SendGoal_Request_type_support_data_t;

static _Dance_SendGoal_Request_type_support_data_t _Dance_SendGoal_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _Dance_SendGoal_Request_message_typesupport_map = {
  2,
  "dance_interfaces",
  &_Dance_SendGoal_Request_message_typesupport_ids.typesupport_identifier[0],
  &_Dance_SendGoal_Request_message_typesupport_symbol_names.symbol_name[0],
  &_Dance_SendGoal_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t Dance_SendGoal_Request_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_Dance_SendGoal_Request_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace dance_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, dance_interfaces, action, Dance_SendGoal_Request)() {
  return &::dance_interfaces::action::rosidl_typesupport_c::Dance_SendGoal_Request_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "dance_interfaces/action/detail/dance__struct.h"
// already included above
// #include "dance_interfaces/action/detail/dance__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace dance_interfaces
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _Dance_SendGoal_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _Dance_SendGoal_Response_type_support_ids_t;

static const _Dance_SendGoal_Response_type_support_ids_t _Dance_SendGoal_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _Dance_SendGoal_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _Dance_SendGoal_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _Dance_SendGoal_Response_type_support_symbol_names_t _Dance_SendGoal_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, dance_interfaces, action, Dance_SendGoal_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, dance_interfaces, action, Dance_SendGoal_Response)),
  }
};

typedef struct _Dance_SendGoal_Response_type_support_data_t
{
  void * data[2];
} _Dance_SendGoal_Response_type_support_data_t;

static _Dance_SendGoal_Response_type_support_data_t _Dance_SendGoal_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _Dance_SendGoal_Response_message_typesupport_map = {
  2,
  "dance_interfaces",
  &_Dance_SendGoal_Response_message_typesupport_ids.typesupport_identifier[0],
  &_Dance_SendGoal_Response_message_typesupport_symbol_names.symbol_name[0],
  &_Dance_SendGoal_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t Dance_SendGoal_Response_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_Dance_SendGoal_Response_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace dance_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, dance_interfaces, action, Dance_SendGoal_Response)() {
  return &::dance_interfaces::action::rosidl_typesupport_c::Dance_SendGoal_Response_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "dance_interfaces/action/detail/dance__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/service_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace dance_interfaces
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _Dance_SendGoal_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _Dance_SendGoal_type_support_ids_t;

static const _Dance_SendGoal_type_support_ids_t _Dance_SendGoal_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _Dance_SendGoal_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _Dance_SendGoal_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _Dance_SendGoal_type_support_symbol_names_t _Dance_SendGoal_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, dance_interfaces, action, Dance_SendGoal)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, dance_interfaces, action, Dance_SendGoal)),
  }
};

typedef struct _Dance_SendGoal_type_support_data_t
{
  void * data[2];
} _Dance_SendGoal_type_support_data_t;

static _Dance_SendGoal_type_support_data_t _Dance_SendGoal_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _Dance_SendGoal_service_typesupport_map = {
  2,
  "dance_interfaces",
  &_Dance_SendGoal_service_typesupport_ids.typesupport_identifier[0],
  &_Dance_SendGoal_service_typesupport_symbol_names.symbol_name[0],
  &_Dance_SendGoal_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t Dance_SendGoal_service_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_Dance_SendGoal_service_typesupport_map),
  rosidl_typesupport_c__get_service_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace dance_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_c, dance_interfaces, action, Dance_SendGoal)() {
  return &::dance_interfaces::action::rosidl_typesupport_c::Dance_SendGoal_service_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "dance_interfaces/action/detail/dance__struct.h"
// already included above
// #include "dance_interfaces/action/detail/dance__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace dance_interfaces
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _Dance_GetResult_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _Dance_GetResult_Request_type_support_ids_t;

static const _Dance_GetResult_Request_type_support_ids_t _Dance_GetResult_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _Dance_GetResult_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _Dance_GetResult_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _Dance_GetResult_Request_type_support_symbol_names_t _Dance_GetResult_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, dance_interfaces, action, Dance_GetResult_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, dance_interfaces, action, Dance_GetResult_Request)),
  }
};

typedef struct _Dance_GetResult_Request_type_support_data_t
{
  void * data[2];
} _Dance_GetResult_Request_type_support_data_t;

static _Dance_GetResult_Request_type_support_data_t _Dance_GetResult_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _Dance_GetResult_Request_message_typesupport_map = {
  2,
  "dance_interfaces",
  &_Dance_GetResult_Request_message_typesupport_ids.typesupport_identifier[0],
  &_Dance_GetResult_Request_message_typesupport_symbol_names.symbol_name[0],
  &_Dance_GetResult_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t Dance_GetResult_Request_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_Dance_GetResult_Request_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace dance_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, dance_interfaces, action, Dance_GetResult_Request)() {
  return &::dance_interfaces::action::rosidl_typesupport_c::Dance_GetResult_Request_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "dance_interfaces/action/detail/dance__struct.h"
// already included above
// #include "dance_interfaces/action/detail/dance__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace dance_interfaces
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _Dance_GetResult_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _Dance_GetResult_Response_type_support_ids_t;

static const _Dance_GetResult_Response_type_support_ids_t _Dance_GetResult_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _Dance_GetResult_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _Dance_GetResult_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _Dance_GetResult_Response_type_support_symbol_names_t _Dance_GetResult_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, dance_interfaces, action, Dance_GetResult_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, dance_interfaces, action, Dance_GetResult_Response)),
  }
};

typedef struct _Dance_GetResult_Response_type_support_data_t
{
  void * data[2];
} _Dance_GetResult_Response_type_support_data_t;

static _Dance_GetResult_Response_type_support_data_t _Dance_GetResult_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _Dance_GetResult_Response_message_typesupport_map = {
  2,
  "dance_interfaces",
  &_Dance_GetResult_Response_message_typesupport_ids.typesupport_identifier[0],
  &_Dance_GetResult_Response_message_typesupport_symbol_names.symbol_name[0],
  &_Dance_GetResult_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t Dance_GetResult_Response_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_Dance_GetResult_Response_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace dance_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, dance_interfaces, action, Dance_GetResult_Response)() {
  return &::dance_interfaces::action::rosidl_typesupport_c::Dance_GetResult_Response_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "dance_interfaces/action/detail/dance__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/service_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace dance_interfaces
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _Dance_GetResult_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _Dance_GetResult_type_support_ids_t;

static const _Dance_GetResult_type_support_ids_t _Dance_GetResult_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _Dance_GetResult_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _Dance_GetResult_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _Dance_GetResult_type_support_symbol_names_t _Dance_GetResult_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, dance_interfaces, action, Dance_GetResult)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, dance_interfaces, action, Dance_GetResult)),
  }
};

typedef struct _Dance_GetResult_type_support_data_t
{
  void * data[2];
} _Dance_GetResult_type_support_data_t;

static _Dance_GetResult_type_support_data_t _Dance_GetResult_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _Dance_GetResult_service_typesupport_map = {
  2,
  "dance_interfaces",
  &_Dance_GetResult_service_typesupport_ids.typesupport_identifier[0],
  &_Dance_GetResult_service_typesupport_symbol_names.symbol_name[0],
  &_Dance_GetResult_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t Dance_GetResult_service_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_Dance_GetResult_service_typesupport_map),
  rosidl_typesupport_c__get_service_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace dance_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_c, dance_interfaces, action, Dance_GetResult)() {
  return &::dance_interfaces::action::rosidl_typesupport_c::Dance_GetResult_service_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "dance_interfaces/action/detail/dance__struct.h"
// already included above
// #include "dance_interfaces/action/detail/dance__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace dance_interfaces
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _Dance_FeedbackMessage_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _Dance_FeedbackMessage_type_support_ids_t;

static const _Dance_FeedbackMessage_type_support_ids_t _Dance_FeedbackMessage_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _Dance_FeedbackMessage_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _Dance_FeedbackMessage_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _Dance_FeedbackMessage_type_support_symbol_names_t _Dance_FeedbackMessage_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, dance_interfaces, action, Dance_FeedbackMessage)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, dance_interfaces, action, Dance_FeedbackMessage)),
  }
};

typedef struct _Dance_FeedbackMessage_type_support_data_t
{
  void * data[2];
} _Dance_FeedbackMessage_type_support_data_t;

static _Dance_FeedbackMessage_type_support_data_t _Dance_FeedbackMessage_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _Dance_FeedbackMessage_message_typesupport_map = {
  2,
  "dance_interfaces",
  &_Dance_FeedbackMessage_message_typesupport_ids.typesupport_identifier[0],
  &_Dance_FeedbackMessage_message_typesupport_symbol_names.symbol_name[0],
  &_Dance_FeedbackMessage_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t Dance_FeedbackMessage_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_Dance_FeedbackMessage_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace dance_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, dance_interfaces, action, Dance_FeedbackMessage)() {
  return &::dance_interfaces::action::rosidl_typesupport_c::Dance_FeedbackMessage_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

#include "action_msgs/msg/goal_status_array.h"
#include "action_msgs/srv/cancel_goal.h"
#include "dance_interfaces/action/dance.h"
// already included above
// #include "dance_interfaces/action/detail/dance__type_support.h"

static rosidl_action_type_support_t _dance_interfaces__action__Dance__typesupport_c;

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_action_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__ACTION_SYMBOL_NAME(
  rosidl_typesupport_c, dance_interfaces, action, Dance)()
{
  // Thread-safe by always writing the same values to the static struct
  _dance_interfaces__action__Dance__typesupport_c.goal_service_type_support =
    ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(
    rosidl_typesupport_c, dance_interfaces, action, Dance_SendGoal)();
  _dance_interfaces__action__Dance__typesupport_c.result_service_type_support =
    ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(
    rosidl_typesupport_c, dance_interfaces, action, Dance_GetResult)();
  _dance_interfaces__action__Dance__typesupport_c.cancel_service_type_support =
    ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(
    rosidl_typesupport_c, action_msgs, srv, CancelGoal)();
  _dance_interfaces__action__Dance__typesupport_c.feedback_message_type_support =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c, dance_interfaces, action, Dance_FeedbackMessage)();
  _dance_interfaces__action__Dance__typesupport_c.status_message_type_support =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c, action_msgs, msg, GoalStatusArray)();

  return &_dance_interfaces__action__Dance__typesupport_c;
}

#ifdef __cplusplus
}
#endif
