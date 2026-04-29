// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from dance_interfaces:action/Dance.idl
// generated code does not contain a copyright notice

#ifndef DANCE_INTERFACES__ACTION__DETAIL__DANCE__STRUCT_H_
#define DANCE_INTERFACES__ACTION__DETAIL__DANCE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'dance_move'
// Member 'texture'
// Member 'params'
#include "rosidl_runtime_c/string.h"

/// Struct defined in action/Dance in the package dance_interfaces.
typedef struct dance_interfaces__action__Dance_Goal
{
  rosidl_runtime_c__String dance_move;
  float energy;
  rosidl_runtime_c__String texture;
  rosidl_runtime_c__String params;
} dance_interfaces__action__Dance_Goal;

// Struct for a sequence of dance_interfaces__action__Dance_Goal.
typedef struct dance_interfaces__action__Dance_Goal__Sequence
{
  dance_interfaces__action__Dance_Goal * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} dance_interfaces__action__Dance_Goal__Sequence;


// Constants defined in the message

/// Struct defined in action/Dance in the package dance_interfaces.
typedef struct dance_interfaces__action__Dance_Result
{
  int32_t result_code;
} dance_interfaces__action__Dance_Result;

// Struct for a sequence of dance_interfaces__action__Dance_Result.
typedef struct dance_interfaces__action__Dance_Result__Sequence
{
  dance_interfaces__action__Dance_Result * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} dance_interfaces__action__Dance_Result__Sequence;


// Constants defined in the message

/// Struct defined in action/Dance in the package dance_interfaces.
typedef struct dance_interfaces__action__Dance_Feedback
{
  int32_t progress;
} dance_interfaces__action__Dance_Feedback;

// Struct for a sequence of dance_interfaces__action__Dance_Feedback.
typedef struct dance_interfaces__action__Dance_Feedback__Sequence
{
  dance_interfaces__action__Dance_Feedback * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} dance_interfaces__action__Dance_Feedback__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'goal'
#include "dance_interfaces/action/detail/dance__struct.h"

/// Struct defined in action/Dance in the package dance_interfaces.
typedef struct dance_interfaces__action__Dance_SendGoal_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
  dance_interfaces__action__Dance_Goal goal;
} dance_interfaces__action__Dance_SendGoal_Request;

// Struct for a sequence of dance_interfaces__action__Dance_SendGoal_Request.
typedef struct dance_interfaces__action__Dance_SendGoal_Request__Sequence
{
  dance_interfaces__action__Dance_SendGoal_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} dance_interfaces__action__Dance_SendGoal_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in action/Dance in the package dance_interfaces.
typedef struct dance_interfaces__action__Dance_SendGoal_Response
{
  bool accepted;
  builtin_interfaces__msg__Time stamp;
} dance_interfaces__action__Dance_SendGoal_Response;

// Struct for a sequence of dance_interfaces__action__Dance_SendGoal_Response.
typedef struct dance_interfaces__action__Dance_SendGoal_Response__Sequence
{
  dance_interfaces__action__Dance_SendGoal_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} dance_interfaces__action__Dance_SendGoal_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"

/// Struct defined in action/Dance in the package dance_interfaces.
typedef struct dance_interfaces__action__Dance_GetResult_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
} dance_interfaces__action__Dance_GetResult_Request;

// Struct for a sequence of dance_interfaces__action__Dance_GetResult_Request.
typedef struct dance_interfaces__action__Dance_GetResult_Request__Sequence
{
  dance_interfaces__action__Dance_GetResult_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} dance_interfaces__action__Dance_GetResult_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'result'
// already included above
// #include "dance_interfaces/action/detail/dance__struct.h"

/// Struct defined in action/Dance in the package dance_interfaces.
typedef struct dance_interfaces__action__Dance_GetResult_Response
{
  int8_t status;
  dance_interfaces__action__Dance_Result result;
} dance_interfaces__action__Dance_GetResult_Response;

// Struct for a sequence of dance_interfaces__action__Dance_GetResult_Response.
typedef struct dance_interfaces__action__Dance_GetResult_Response__Sequence
{
  dance_interfaces__action__Dance_GetResult_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} dance_interfaces__action__Dance_GetResult_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'feedback'
// already included above
// #include "dance_interfaces/action/detail/dance__struct.h"

/// Struct defined in action/Dance in the package dance_interfaces.
typedef struct dance_interfaces__action__Dance_FeedbackMessage
{
  unique_identifier_msgs__msg__UUID goal_id;
  dance_interfaces__action__Dance_Feedback feedback;
} dance_interfaces__action__Dance_FeedbackMessage;

// Struct for a sequence of dance_interfaces__action__Dance_FeedbackMessage.
typedef struct dance_interfaces__action__Dance_FeedbackMessage__Sequence
{
  dance_interfaces__action__Dance_FeedbackMessage * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} dance_interfaces__action__Dance_FeedbackMessage__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // DANCE_INTERFACES__ACTION__DETAIL__DANCE__STRUCT_H_
