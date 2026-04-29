// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from dance_interfaces:action/Dance.idl
// generated code does not contain a copyright notice
#include "dance_interfaces/action/detail/dance__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `dance_move`
// Member `texture`
// Member `params`
#include "rosidl_runtime_c/string_functions.h"

bool
dance_interfaces__action__Dance_Goal__init(dance_interfaces__action__Dance_Goal * msg)
{
  if (!msg) {
    return false;
  }
  // dance_move
  if (!rosidl_runtime_c__String__init(&msg->dance_move)) {
    dance_interfaces__action__Dance_Goal__fini(msg);
    return false;
  }
  // energy
  msg->energy = 0.5f;
  // texture
  if (!rosidl_runtime_c__String__init(&msg->texture)) {
    dance_interfaces__action__Dance_Goal__fini(msg);
    return false;
  }
  {
    bool success = rosidl_runtime_c__String__assign(&msg->texture, "neutral");
    if (!success) {
      goto abort_init_0;
    }
  }
  // params
  if (!rosidl_runtime_c__String__init(&msg->params)) {
    dance_interfaces__action__Dance_Goal__fini(msg);
    return false;
  }
  return true;
abort_init_0:
  return false;
}

void
dance_interfaces__action__Dance_Goal__fini(dance_interfaces__action__Dance_Goal * msg)
{
  if (!msg) {
    return;
  }
  // dance_move
  rosidl_runtime_c__String__fini(&msg->dance_move);
  // energy
  // texture
  rosidl_runtime_c__String__fini(&msg->texture);
  // params
  rosidl_runtime_c__String__fini(&msg->params);
}

bool
dance_interfaces__action__Dance_Goal__are_equal(const dance_interfaces__action__Dance_Goal * lhs, const dance_interfaces__action__Dance_Goal * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // dance_move
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->dance_move), &(rhs->dance_move)))
  {
    return false;
  }
  // energy
  if (lhs->energy != rhs->energy) {
    return false;
  }
  // texture
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->texture), &(rhs->texture)))
  {
    return false;
  }
  // params
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->params), &(rhs->params)))
  {
    return false;
  }
  return true;
}

bool
dance_interfaces__action__Dance_Goal__copy(
  const dance_interfaces__action__Dance_Goal * input,
  dance_interfaces__action__Dance_Goal * output)
{
  if (!input || !output) {
    return false;
  }
  // dance_move
  if (!rosidl_runtime_c__String__copy(
      &(input->dance_move), &(output->dance_move)))
  {
    return false;
  }
  // energy
  output->energy = input->energy;
  // texture
  if (!rosidl_runtime_c__String__copy(
      &(input->texture), &(output->texture)))
  {
    return false;
  }
  // params
  if (!rosidl_runtime_c__String__copy(
      &(input->params), &(output->params)))
  {
    return false;
  }
  return true;
}

dance_interfaces__action__Dance_Goal *
dance_interfaces__action__Dance_Goal__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dance_interfaces__action__Dance_Goal * msg = (dance_interfaces__action__Dance_Goal *)allocator.allocate(sizeof(dance_interfaces__action__Dance_Goal), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(dance_interfaces__action__Dance_Goal));
  bool success = dance_interfaces__action__Dance_Goal__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
dance_interfaces__action__Dance_Goal__destroy(dance_interfaces__action__Dance_Goal * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    dance_interfaces__action__Dance_Goal__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
dance_interfaces__action__Dance_Goal__Sequence__init(dance_interfaces__action__Dance_Goal__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dance_interfaces__action__Dance_Goal * data = NULL;

  if (size) {
    data = (dance_interfaces__action__Dance_Goal *)allocator.zero_allocate(size, sizeof(dance_interfaces__action__Dance_Goal), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = dance_interfaces__action__Dance_Goal__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        dance_interfaces__action__Dance_Goal__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
dance_interfaces__action__Dance_Goal__Sequence__fini(dance_interfaces__action__Dance_Goal__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      dance_interfaces__action__Dance_Goal__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

dance_interfaces__action__Dance_Goal__Sequence *
dance_interfaces__action__Dance_Goal__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dance_interfaces__action__Dance_Goal__Sequence * array = (dance_interfaces__action__Dance_Goal__Sequence *)allocator.allocate(sizeof(dance_interfaces__action__Dance_Goal__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = dance_interfaces__action__Dance_Goal__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
dance_interfaces__action__Dance_Goal__Sequence__destroy(dance_interfaces__action__Dance_Goal__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    dance_interfaces__action__Dance_Goal__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
dance_interfaces__action__Dance_Goal__Sequence__are_equal(const dance_interfaces__action__Dance_Goal__Sequence * lhs, const dance_interfaces__action__Dance_Goal__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!dance_interfaces__action__Dance_Goal__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
dance_interfaces__action__Dance_Goal__Sequence__copy(
  const dance_interfaces__action__Dance_Goal__Sequence * input,
  dance_interfaces__action__Dance_Goal__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(dance_interfaces__action__Dance_Goal);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    dance_interfaces__action__Dance_Goal * data =
      (dance_interfaces__action__Dance_Goal *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!dance_interfaces__action__Dance_Goal__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          dance_interfaces__action__Dance_Goal__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!dance_interfaces__action__Dance_Goal__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


bool
dance_interfaces__action__Dance_Result__init(dance_interfaces__action__Dance_Result * msg)
{
  if (!msg) {
    return false;
  }
  // result_code
  return true;
}

void
dance_interfaces__action__Dance_Result__fini(dance_interfaces__action__Dance_Result * msg)
{
  if (!msg) {
    return;
  }
  // result_code
}

bool
dance_interfaces__action__Dance_Result__are_equal(const dance_interfaces__action__Dance_Result * lhs, const dance_interfaces__action__Dance_Result * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // result_code
  if (lhs->result_code != rhs->result_code) {
    return false;
  }
  return true;
}

bool
dance_interfaces__action__Dance_Result__copy(
  const dance_interfaces__action__Dance_Result * input,
  dance_interfaces__action__Dance_Result * output)
{
  if (!input || !output) {
    return false;
  }
  // result_code
  output->result_code = input->result_code;
  return true;
}

dance_interfaces__action__Dance_Result *
dance_interfaces__action__Dance_Result__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dance_interfaces__action__Dance_Result * msg = (dance_interfaces__action__Dance_Result *)allocator.allocate(sizeof(dance_interfaces__action__Dance_Result), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(dance_interfaces__action__Dance_Result));
  bool success = dance_interfaces__action__Dance_Result__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
dance_interfaces__action__Dance_Result__destroy(dance_interfaces__action__Dance_Result * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    dance_interfaces__action__Dance_Result__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
dance_interfaces__action__Dance_Result__Sequence__init(dance_interfaces__action__Dance_Result__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dance_interfaces__action__Dance_Result * data = NULL;

  if (size) {
    data = (dance_interfaces__action__Dance_Result *)allocator.zero_allocate(size, sizeof(dance_interfaces__action__Dance_Result), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = dance_interfaces__action__Dance_Result__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        dance_interfaces__action__Dance_Result__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
dance_interfaces__action__Dance_Result__Sequence__fini(dance_interfaces__action__Dance_Result__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      dance_interfaces__action__Dance_Result__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

dance_interfaces__action__Dance_Result__Sequence *
dance_interfaces__action__Dance_Result__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dance_interfaces__action__Dance_Result__Sequence * array = (dance_interfaces__action__Dance_Result__Sequence *)allocator.allocate(sizeof(dance_interfaces__action__Dance_Result__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = dance_interfaces__action__Dance_Result__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
dance_interfaces__action__Dance_Result__Sequence__destroy(dance_interfaces__action__Dance_Result__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    dance_interfaces__action__Dance_Result__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
dance_interfaces__action__Dance_Result__Sequence__are_equal(const dance_interfaces__action__Dance_Result__Sequence * lhs, const dance_interfaces__action__Dance_Result__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!dance_interfaces__action__Dance_Result__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
dance_interfaces__action__Dance_Result__Sequence__copy(
  const dance_interfaces__action__Dance_Result__Sequence * input,
  dance_interfaces__action__Dance_Result__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(dance_interfaces__action__Dance_Result);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    dance_interfaces__action__Dance_Result * data =
      (dance_interfaces__action__Dance_Result *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!dance_interfaces__action__Dance_Result__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          dance_interfaces__action__Dance_Result__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!dance_interfaces__action__Dance_Result__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


bool
dance_interfaces__action__Dance_Feedback__init(dance_interfaces__action__Dance_Feedback * msg)
{
  if (!msg) {
    return false;
  }
  // progress
  return true;
}

void
dance_interfaces__action__Dance_Feedback__fini(dance_interfaces__action__Dance_Feedback * msg)
{
  if (!msg) {
    return;
  }
  // progress
}

bool
dance_interfaces__action__Dance_Feedback__are_equal(const dance_interfaces__action__Dance_Feedback * lhs, const dance_interfaces__action__Dance_Feedback * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // progress
  if (lhs->progress != rhs->progress) {
    return false;
  }
  return true;
}

bool
dance_interfaces__action__Dance_Feedback__copy(
  const dance_interfaces__action__Dance_Feedback * input,
  dance_interfaces__action__Dance_Feedback * output)
{
  if (!input || !output) {
    return false;
  }
  // progress
  output->progress = input->progress;
  return true;
}

dance_interfaces__action__Dance_Feedback *
dance_interfaces__action__Dance_Feedback__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dance_interfaces__action__Dance_Feedback * msg = (dance_interfaces__action__Dance_Feedback *)allocator.allocate(sizeof(dance_interfaces__action__Dance_Feedback), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(dance_interfaces__action__Dance_Feedback));
  bool success = dance_interfaces__action__Dance_Feedback__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
dance_interfaces__action__Dance_Feedback__destroy(dance_interfaces__action__Dance_Feedback * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    dance_interfaces__action__Dance_Feedback__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
dance_interfaces__action__Dance_Feedback__Sequence__init(dance_interfaces__action__Dance_Feedback__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dance_interfaces__action__Dance_Feedback * data = NULL;

  if (size) {
    data = (dance_interfaces__action__Dance_Feedback *)allocator.zero_allocate(size, sizeof(dance_interfaces__action__Dance_Feedback), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = dance_interfaces__action__Dance_Feedback__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        dance_interfaces__action__Dance_Feedback__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
dance_interfaces__action__Dance_Feedback__Sequence__fini(dance_interfaces__action__Dance_Feedback__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      dance_interfaces__action__Dance_Feedback__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

dance_interfaces__action__Dance_Feedback__Sequence *
dance_interfaces__action__Dance_Feedback__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dance_interfaces__action__Dance_Feedback__Sequence * array = (dance_interfaces__action__Dance_Feedback__Sequence *)allocator.allocate(sizeof(dance_interfaces__action__Dance_Feedback__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = dance_interfaces__action__Dance_Feedback__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
dance_interfaces__action__Dance_Feedback__Sequence__destroy(dance_interfaces__action__Dance_Feedback__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    dance_interfaces__action__Dance_Feedback__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
dance_interfaces__action__Dance_Feedback__Sequence__are_equal(const dance_interfaces__action__Dance_Feedback__Sequence * lhs, const dance_interfaces__action__Dance_Feedback__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!dance_interfaces__action__Dance_Feedback__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
dance_interfaces__action__Dance_Feedback__Sequence__copy(
  const dance_interfaces__action__Dance_Feedback__Sequence * input,
  dance_interfaces__action__Dance_Feedback__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(dance_interfaces__action__Dance_Feedback);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    dance_interfaces__action__Dance_Feedback * data =
      (dance_interfaces__action__Dance_Feedback *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!dance_interfaces__action__Dance_Feedback__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          dance_interfaces__action__Dance_Feedback__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!dance_interfaces__action__Dance_Feedback__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `goal_id`
#include "unique_identifier_msgs/msg/detail/uuid__functions.h"
// Member `goal`
// already included above
// #include "dance_interfaces/action/detail/dance__functions.h"

bool
dance_interfaces__action__Dance_SendGoal_Request__init(dance_interfaces__action__Dance_SendGoal_Request * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    dance_interfaces__action__Dance_SendGoal_Request__fini(msg);
    return false;
  }
  // goal
  if (!dance_interfaces__action__Dance_Goal__init(&msg->goal)) {
    dance_interfaces__action__Dance_SendGoal_Request__fini(msg);
    return false;
  }
  return true;
}

void
dance_interfaces__action__Dance_SendGoal_Request__fini(dance_interfaces__action__Dance_SendGoal_Request * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
  // goal
  dance_interfaces__action__Dance_Goal__fini(&msg->goal);
}

bool
dance_interfaces__action__Dance_SendGoal_Request__are_equal(const dance_interfaces__action__Dance_SendGoal_Request * lhs, const dance_interfaces__action__Dance_SendGoal_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__are_equal(
      &(lhs->goal_id), &(rhs->goal_id)))
  {
    return false;
  }
  // goal
  if (!dance_interfaces__action__Dance_Goal__are_equal(
      &(lhs->goal), &(rhs->goal)))
  {
    return false;
  }
  return true;
}

bool
dance_interfaces__action__Dance_SendGoal_Request__copy(
  const dance_interfaces__action__Dance_SendGoal_Request * input,
  dance_interfaces__action__Dance_SendGoal_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__copy(
      &(input->goal_id), &(output->goal_id)))
  {
    return false;
  }
  // goal
  if (!dance_interfaces__action__Dance_Goal__copy(
      &(input->goal), &(output->goal)))
  {
    return false;
  }
  return true;
}

dance_interfaces__action__Dance_SendGoal_Request *
dance_interfaces__action__Dance_SendGoal_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dance_interfaces__action__Dance_SendGoal_Request * msg = (dance_interfaces__action__Dance_SendGoal_Request *)allocator.allocate(sizeof(dance_interfaces__action__Dance_SendGoal_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(dance_interfaces__action__Dance_SendGoal_Request));
  bool success = dance_interfaces__action__Dance_SendGoal_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
dance_interfaces__action__Dance_SendGoal_Request__destroy(dance_interfaces__action__Dance_SendGoal_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    dance_interfaces__action__Dance_SendGoal_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
dance_interfaces__action__Dance_SendGoal_Request__Sequence__init(dance_interfaces__action__Dance_SendGoal_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dance_interfaces__action__Dance_SendGoal_Request * data = NULL;

  if (size) {
    data = (dance_interfaces__action__Dance_SendGoal_Request *)allocator.zero_allocate(size, sizeof(dance_interfaces__action__Dance_SendGoal_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = dance_interfaces__action__Dance_SendGoal_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        dance_interfaces__action__Dance_SendGoal_Request__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
dance_interfaces__action__Dance_SendGoal_Request__Sequence__fini(dance_interfaces__action__Dance_SendGoal_Request__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      dance_interfaces__action__Dance_SendGoal_Request__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

dance_interfaces__action__Dance_SendGoal_Request__Sequence *
dance_interfaces__action__Dance_SendGoal_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dance_interfaces__action__Dance_SendGoal_Request__Sequence * array = (dance_interfaces__action__Dance_SendGoal_Request__Sequence *)allocator.allocate(sizeof(dance_interfaces__action__Dance_SendGoal_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = dance_interfaces__action__Dance_SendGoal_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
dance_interfaces__action__Dance_SendGoal_Request__Sequence__destroy(dance_interfaces__action__Dance_SendGoal_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    dance_interfaces__action__Dance_SendGoal_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
dance_interfaces__action__Dance_SendGoal_Request__Sequence__are_equal(const dance_interfaces__action__Dance_SendGoal_Request__Sequence * lhs, const dance_interfaces__action__Dance_SendGoal_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!dance_interfaces__action__Dance_SendGoal_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
dance_interfaces__action__Dance_SendGoal_Request__Sequence__copy(
  const dance_interfaces__action__Dance_SendGoal_Request__Sequence * input,
  dance_interfaces__action__Dance_SendGoal_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(dance_interfaces__action__Dance_SendGoal_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    dance_interfaces__action__Dance_SendGoal_Request * data =
      (dance_interfaces__action__Dance_SendGoal_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!dance_interfaces__action__Dance_SendGoal_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          dance_interfaces__action__Dance_SendGoal_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!dance_interfaces__action__Dance_SendGoal_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__functions.h"

bool
dance_interfaces__action__Dance_SendGoal_Response__init(dance_interfaces__action__Dance_SendGoal_Response * msg)
{
  if (!msg) {
    return false;
  }
  // accepted
  // stamp
  if (!builtin_interfaces__msg__Time__init(&msg->stamp)) {
    dance_interfaces__action__Dance_SendGoal_Response__fini(msg);
    return false;
  }
  return true;
}

void
dance_interfaces__action__Dance_SendGoal_Response__fini(dance_interfaces__action__Dance_SendGoal_Response * msg)
{
  if (!msg) {
    return;
  }
  // accepted
  // stamp
  builtin_interfaces__msg__Time__fini(&msg->stamp);
}

bool
dance_interfaces__action__Dance_SendGoal_Response__are_equal(const dance_interfaces__action__Dance_SendGoal_Response * lhs, const dance_interfaces__action__Dance_SendGoal_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // accepted
  if (lhs->accepted != rhs->accepted) {
    return false;
  }
  // stamp
  if (!builtin_interfaces__msg__Time__are_equal(
      &(lhs->stamp), &(rhs->stamp)))
  {
    return false;
  }
  return true;
}

bool
dance_interfaces__action__Dance_SendGoal_Response__copy(
  const dance_interfaces__action__Dance_SendGoal_Response * input,
  dance_interfaces__action__Dance_SendGoal_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // accepted
  output->accepted = input->accepted;
  // stamp
  if (!builtin_interfaces__msg__Time__copy(
      &(input->stamp), &(output->stamp)))
  {
    return false;
  }
  return true;
}

dance_interfaces__action__Dance_SendGoal_Response *
dance_interfaces__action__Dance_SendGoal_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dance_interfaces__action__Dance_SendGoal_Response * msg = (dance_interfaces__action__Dance_SendGoal_Response *)allocator.allocate(sizeof(dance_interfaces__action__Dance_SendGoal_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(dance_interfaces__action__Dance_SendGoal_Response));
  bool success = dance_interfaces__action__Dance_SendGoal_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
dance_interfaces__action__Dance_SendGoal_Response__destroy(dance_interfaces__action__Dance_SendGoal_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    dance_interfaces__action__Dance_SendGoal_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
dance_interfaces__action__Dance_SendGoal_Response__Sequence__init(dance_interfaces__action__Dance_SendGoal_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dance_interfaces__action__Dance_SendGoal_Response * data = NULL;

  if (size) {
    data = (dance_interfaces__action__Dance_SendGoal_Response *)allocator.zero_allocate(size, sizeof(dance_interfaces__action__Dance_SendGoal_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = dance_interfaces__action__Dance_SendGoal_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        dance_interfaces__action__Dance_SendGoal_Response__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
dance_interfaces__action__Dance_SendGoal_Response__Sequence__fini(dance_interfaces__action__Dance_SendGoal_Response__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      dance_interfaces__action__Dance_SendGoal_Response__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

dance_interfaces__action__Dance_SendGoal_Response__Sequence *
dance_interfaces__action__Dance_SendGoal_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dance_interfaces__action__Dance_SendGoal_Response__Sequence * array = (dance_interfaces__action__Dance_SendGoal_Response__Sequence *)allocator.allocate(sizeof(dance_interfaces__action__Dance_SendGoal_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = dance_interfaces__action__Dance_SendGoal_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
dance_interfaces__action__Dance_SendGoal_Response__Sequence__destroy(dance_interfaces__action__Dance_SendGoal_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    dance_interfaces__action__Dance_SendGoal_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
dance_interfaces__action__Dance_SendGoal_Response__Sequence__are_equal(const dance_interfaces__action__Dance_SendGoal_Response__Sequence * lhs, const dance_interfaces__action__Dance_SendGoal_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!dance_interfaces__action__Dance_SendGoal_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
dance_interfaces__action__Dance_SendGoal_Response__Sequence__copy(
  const dance_interfaces__action__Dance_SendGoal_Response__Sequence * input,
  dance_interfaces__action__Dance_SendGoal_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(dance_interfaces__action__Dance_SendGoal_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    dance_interfaces__action__Dance_SendGoal_Response * data =
      (dance_interfaces__action__Dance_SendGoal_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!dance_interfaces__action__Dance_SendGoal_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          dance_interfaces__action__Dance_SendGoal_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!dance_interfaces__action__Dance_SendGoal_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__functions.h"

bool
dance_interfaces__action__Dance_GetResult_Request__init(dance_interfaces__action__Dance_GetResult_Request * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    dance_interfaces__action__Dance_GetResult_Request__fini(msg);
    return false;
  }
  return true;
}

void
dance_interfaces__action__Dance_GetResult_Request__fini(dance_interfaces__action__Dance_GetResult_Request * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
}

bool
dance_interfaces__action__Dance_GetResult_Request__are_equal(const dance_interfaces__action__Dance_GetResult_Request * lhs, const dance_interfaces__action__Dance_GetResult_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__are_equal(
      &(lhs->goal_id), &(rhs->goal_id)))
  {
    return false;
  }
  return true;
}

bool
dance_interfaces__action__Dance_GetResult_Request__copy(
  const dance_interfaces__action__Dance_GetResult_Request * input,
  dance_interfaces__action__Dance_GetResult_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__copy(
      &(input->goal_id), &(output->goal_id)))
  {
    return false;
  }
  return true;
}

dance_interfaces__action__Dance_GetResult_Request *
dance_interfaces__action__Dance_GetResult_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dance_interfaces__action__Dance_GetResult_Request * msg = (dance_interfaces__action__Dance_GetResult_Request *)allocator.allocate(sizeof(dance_interfaces__action__Dance_GetResult_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(dance_interfaces__action__Dance_GetResult_Request));
  bool success = dance_interfaces__action__Dance_GetResult_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
dance_interfaces__action__Dance_GetResult_Request__destroy(dance_interfaces__action__Dance_GetResult_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    dance_interfaces__action__Dance_GetResult_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
dance_interfaces__action__Dance_GetResult_Request__Sequence__init(dance_interfaces__action__Dance_GetResult_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dance_interfaces__action__Dance_GetResult_Request * data = NULL;

  if (size) {
    data = (dance_interfaces__action__Dance_GetResult_Request *)allocator.zero_allocate(size, sizeof(dance_interfaces__action__Dance_GetResult_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = dance_interfaces__action__Dance_GetResult_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        dance_interfaces__action__Dance_GetResult_Request__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
dance_interfaces__action__Dance_GetResult_Request__Sequence__fini(dance_interfaces__action__Dance_GetResult_Request__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      dance_interfaces__action__Dance_GetResult_Request__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

dance_interfaces__action__Dance_GetResult_Request__Sequence *
dance_interfaces__action__Dance_GetResult_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dance_interfaces__action__Dance_GetResult_Request__Sequence * array = (dance_interfaces__action__Dance_GetResult_Request__Sequence *)allocator.allocate(sizeof(dance_interfaces__action__Dance_GetResult_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = dance_interfaces__action__Dance_GetResult_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
dance_interfaces__action__Dance_GetResult_Request__Sequence__destroy(dance_interfaces__action__Dance_GetResult_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    dance_interfaces__action__Dance_GetResult_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
dance_interfaces__action__Dance_GetResult_Request__Sequence__are_equal(const dance_interfaces__action__Dance_GetResult_Request__Sequence * lhs, const dance_interfaces__action__Dance_GetResult_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!dance_interfaces__action__Dance_GetResult_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
dance_interfaces__action__Dance_GetResult_Request__Sequence__copy(
  const dance_interfaces__action__Dance_GetResult_Request__Sequence * input,
  dance_interfaces__action__Dance_GetResult_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(dance_interfaces__action__Dance_GetResult_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    dance_interfaces__action__Dance_GetResult_Request * data =
      (dance_interfaces__action__Dance_GetResult_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!dance_interfaces__action__Dance_GetResult_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          dance_interfaces__action__Dance_GetResult_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!dance_interfaces__action__Dance_GetResult_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `result`
// already included above
// #include "dance_interfaces/action/detail/dance__functions.h"

bool
dance_interfaces__action__Dance_GetResult_Response__init(dance_interfaces__action__Dance_GetResult_Response * msg)
{
  if (!msg) {
    return false;
  }
  // status
  // result
  if (!dance_interfaces__action__Dance_Result__init(&msg->result)) {
    dance_interfaces__action__Dance_GetResult_Response__fini(msg);
    return false;
  }
  return true;
}

void
dance_interfaces__action__Dance_GetResult_Response__fini(dance_interfaces__action__Dance_GetResult_Response * msg)
{
  if (!msg) {
    return;
  }
  // status
  // result
  dance_interfaces__action__Dance_Result__fini(&msg->result);
}

bool
dance_interfaces__action__Dance_GetResult_Response__are_equal(const dance_interfaces__action__Dance_GetResult_Response * lhs, const dance_interfaces__action__Dance_GetResult_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // status
  if (lhs->status != rhs->status) {
    return false;
  }
  // result
  if (!dance_interfaces__action__Dance_Result__are_equal(
      &(lhs->result), &(rhs->result)))
  {
    return false;
  }
  return true;
}

bool
dance_interfaces__action__Dance_GetResult_Response__copy(
  const dance_interfaces__action__Dance_GetResult_Response * input,
  dance_interfaces__action__Dance_GetResult_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // status
  output->status = input->status;
  // result
  if (!dance_interfaces__action__Dance_Result__copy(
      &(input->result), &(output->result)))
  {
    return false;
  }
  return true;
}

dance_interfaces__action__Dance_GetResult_Response *
dance_interfaces__action__Dance_GetResult_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dance_interfaces__action__Dance_GetResult_Response * msg = (dance_interfaces__action__Dance_GetResult_Response *)allocator.allocate(sizeof(dance_interfaces__action__Dance_GetResult_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(dance_interfaces__action__Dance_GetResult_Response));
  bool success = dance_interfaces__action__Dance_GetResult_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
dance_interfaces__action__Dance_GetResult_Response__destroy(dance_interfaces__action__Dance_GetResult_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    dance_interfaces__action__Dance_GetResult_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
dance_interfaces__action__Dance_GetResult_Response__Sequence__init(dance_interfaces__action__Dance_GetResult_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dance_interfaces__action__Dance_GetResult_Response * data = NULL;

  if (size) {
    data = (dance_interfaces__action__Dance_GetResult_Response *)allocator.zero_allocate(size, sizeof(dance_interfaces__action__Dance_GetResult_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = dance_interfaces__action__Dance_GetResult_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        dance_interfaces__action__Dance_GetResult_Response__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
dance_interfaces__action__Dance_GetResult_Response__Sequence__fini(dance_interfaces__action__Dance_GetResult_Response__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      dance_interfaces__action__Dance_GetResult_Response__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

dance_interfaces__action__Dance_GetResult_Response__Sequence *
dance_interfaces__action__Dance_GetResult_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dance_interfaces__action__Dance_GetResult_Response__Sequence * array = (dance_interfaces__action__Dance_GetResult_Response__Sequence *)allocator.allocate(sizeof(dance_interfaces__action__Dance_GetResult_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = dance_interfaces__action__Dance_GetResult_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
dance_interfaces__action__Dance_GetResult_Response__Sequence__destroy(dance_interfaces__action__Dance_GetResult_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    dance_interfaces__action__Dance_GetResult_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
dance_interfaces__action__Dance_GetResult_Response__Sequence__are_equal(const dance_interfaces__action__Dance_GetResult_Response__Sequence * lhs, const dance_interfaces__action__Dance_GetResult_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!dance_interfaces__action__Dance_GetResult_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
dance_interfaces__action__Dance_GetResult_Response__Sequence__copy(
  const dance_interfaces__action__Dance_GetResult_Response__Sequence * input,
  dance_interfaces__action__Dance_GetResult_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(dance_interfaces__action__Dance_GetResult_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    dance_interfaces__action__Dance_GetResult_Response * data =
      (dance_interfaces__action__Dance_GetResult_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!dance_interfaces__action__Dance_GetResult_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          dance_interfaces__action__Dance_GetResult_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!dance_interfaces__action__Dance_GetResult_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__functions.h"
// Member `feedback`
// already included above
// #include "dance_interfaces/action/detail/dance__functions.h"

bool
dance_interfaces__action__Dance_FeedbackMessage__init(dance_interfaces__action__Dance_FeedbackMessage * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    dance_interfaces__action__Dance_FeedbackMessage__fini(msg);
    return false;
  }
  // feedback
  if (!dance_interfaces__action__Dance_Feedback__init(&msg->feedback)) {
    dance_interfaces__action__Dance_FeedbackMessage__fini(msg);
    return false;
  }
  return true;
}

void
dance_interfaces__action__Dance_FeedbackMessage__fini(dance_interfaces__action__Dance_FeedbackMessage * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
  // feedback
  dance_interfaces__action__Dance_Feedback__fini(&msg->feedback);
}

bool
dance_interfaces__action__Dance_FeedbackMessage__are_equal(const dance_interfaces__action__Dance_FeedbackMessage * lhs, const dance_interfaces__action__Dance_FeedbackMessage * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__are_equal(
      &(lhs->goal_id), &(rhs->goal_id)))
  {
    return false;
  }
  // feedback
  if (!dance_interfaces__action__Dance_Feedback__are_equal(
      &(lhs->feedback), &(rhs->feedback)))
  {
    return false;
  }
  return true;
}

bool
dance_interfaces__action__Dance_FeedbackMessage__copy(
  const dance_interfaces__action__Dance_FeedbackMessage * input,
  dance_interfaces__action__Dance_FeedbackMessage * output)
{
  if (!input || !output) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__copy(
      &(input->goal_id), &(output->goal_id)))
  {
    return false;
  }
  // feedback
  if (!dance_interfaces__action__Dance_Feedback__copy(
      &(input->feedback), &(output->feedback)))
  {
    return false;
  }
  return true;
}

dance_interfaces__action__Dance_FeedbackMessage *
dance_interfaces__action__Dance_FeedbackMessage__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dance_interfaces__action__Dance_FeedbackMessage * msg = (dance_interfaces__action__Dance_FeedbackMessage *)allocator.allocate(sizeof(dance_interfaces__action__Dance_FeedbackMessage), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(dance_interfaces__action__Dance_FeedbackMessage));
  bool success = dance_interfaces__action__Dance_FeedbackMessage__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
dance_interfaces__action__Dance_FeedbackMessage__destroy(dance_interfaces__action__Dance_FeedbackMessage * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    dance_interfaces__action__Dance_FeedbackMessage__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
dance_interfaces__action__Dance_FeedbackMessage__Sequence__init(dance_interfaces__action__Dance_FeedbackMessage__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dance_interfaces__action__Dance_FeedbackMessage * data = NULL;

  if (size) {
    data = (dance_interfaces__action__Dance_FeedbackMessage *)allocator.zero_allocate(size, sizeof(dance_interfaces__action__Dance_FeedbackMessage), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = dance_interfaces__action__Dance_FeedbackMessage__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        dance_interfaces__action__Dance_FeedbackMessage__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
dance_interfaces__action__Dance_FeedbackMessage__Sequence__fini(dance_interfaces__action__Dance_FeedbackMessage__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      dance_interfaces__action__Dance_FeedbackMessage__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

dance_interfaces__action__Dance_FeedbackMessage__Sequence *
dance_interfaces__action__Dance_FeedbackMessage__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dance_interfaces__action__Dance_FeedbackMessage__Sequence * array = (dance_interfaces__action__Dance_FeedbackMessage__Sequence *)allocator.allocate(sizeof(dance_interfaces__action__Dance_FeedbackMessage__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = dance_interfaces__action__Dance_FeedbackMessage__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
dance_interfaces__action__Dance_FeedbackMessage__Sequence__destroy(dance_interfaces__action__Dance_FeedbackMessage__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    dance_interfaces__action__Dance_FeedbackMessage__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
dance_interfaces__action__Dance_FeedbackMessage__Sequence__are_equal(const dance_interfaces__action__Dance_FeedbackMessage__Sequence * lhs, const dance_interfaces__action__Dance_FeedbackMessage__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!dance_interfaces__action__Dance_FeedbackMessage__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
dance_interfaces__action__Dance_FeedbackMessage__Sequence__copy(
  const dance_interfaces__action__Dance_FeedbackMessage__Sequence * input,
  dance_interfaces__action__Dance_FeedbackMessage__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(dance_interfaces__action__Dance_FeedbackMessage);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    dance_interfaces__action__Dance_FeedbackMessage * data =
      (dance_interfaces__action__Dance_FeedbackMessage *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!dance_interfaces__action__Dance_FeedbackMessage__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          dance_interfaces__action__Dance_FeedbackMessage__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!dance_interfaces__action__Dance_FeedbackMessage__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
