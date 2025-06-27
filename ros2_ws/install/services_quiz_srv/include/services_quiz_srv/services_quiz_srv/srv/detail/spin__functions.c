// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from services_quiz_srv:srv/Spin.idl
// generated code does not contain a copyright notice
#include "services_quiz_srv/srv/detail/spin__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

// Include directives for member types
// Member `direction`
#include "rosidl_runtime_c/string_functions.h"

bool
services_quiz_srv__srv__Spin_Request__init(services_quiz_srv__srv__Spin_Request * msg)
{
  if (!msg) {
    return false;
  }
  // direction
  if (!rosidl_runtime_c__String__init(&msg->direction)) {
    services_quiz_srv__srv__Spin_Request__fini(msg);
    return false;
  }
  // angular_velocity
  // time
  return true;
}

void
services_quiz_srv__srv__Spin_Request__fini(services_quiz_srv__srv__Spin_Request * msg)
{
  if (!msg) {
    return;
  }
  // direction
  rosidl_runtime_c__String__fini(&msg->direction);
  // angular_velocity
  // time
}

bool
services_quiz_srv__srv__Spin_Request__are_equal(const services_quiz_srv__srv__Spin_Request * lhs, const services_quiz_srv__srv__Spin_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // direction
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->direction), &(rhs->direction)))
  {
    return false;
  }
  // angular_velocity
  if (lhs->angular_velocity != rhs->angular_velocity) {
    return false;
  }
  // time
  if (lhs->time != rhs->time) {
    return false;
  }
  return true;
}

bool
services_quiz_srv__srv__Spin_Request__copy(
  const services_quiz_srv__srv__Spin_Request * input,
  services_quiz_srv__srv__Spin_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // direction
  if (!rosidl_runtime_c__String__copy(
      &(input->direction), &(output->direction)))
  {
    return false;
  }
  // angular_velocity
  output->angular_velocity = input->angular_velocity;
  // time
  output->time = input->time;
  return true;
}

services_quiz_srv__srv__Spin_Request *
services_quiz_srv__srv__Spin_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  services_quiz_srv__srv__Spin_Request * msg = (services_quiz_srv__srv__Spin_Request *)allocator.allocate(sizeof(services_quiz_srv__srv__Spin_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(services_quiz_srv__srv__Spin_Request));
  bool success = services_quiz_srv__srv__Spin_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
services_quiz_srv__srv__Spin_Request__destroy(services_quiz_srv__srv__Spin_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    services_quiz_srv__srv__Spin_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
services_quiz_srv__srv__Spin_Request__Sequence__init(services_quiz_srv__srv__Spin_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  services_quiz_srv__srv__Spin_Request * data = NULL;

  if (size) {
    data = (services_quiz_srv__srv__Spin_Request *)allocator.zero_allocate(size, sizeof(services_quiz_srv__srv__Spin_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = services_quiz_srv__srv__Spin_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        services_quiz_srv__srv__Spin_Request__fini(&data[i - 1]);
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
services_quiz_srv__srv__Spin_Request__Sequence__fini(services_quiz_srv__srv__Spin_Request__Sequence * array)
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
      services_quiz_srv__srv__Spin_Request__fini(&array->data[i]);
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

services_quiz_srv__srv__Spin_Request__Sequence *
services_quiz_srv__srv__Spin_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  services_quiz_srv__srv__Spin_Request__Sequence * array = (services_quiz_srv__srv__Spin_Request__Sequence *)allocator.allocate(sizeof(services_quiz_srv__srv__Spin_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = services_quiz_srv__srv__Spin_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
services_quiz_srv__srv__Spin_Request__Sequence__destroy(services_quiz_srv__srv__Spin_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    services_quiz_srv__srv__Spin_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
services_quiz_srv__srv__Spin_Request__Sequence__are_equal(const services_quiz_srv__srv__Spin_Request__Sequence * lhs, const services_quiz_srv__srv__Spin_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!services_quiz_srv__srv__Spin_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
services_quiz_srv__srv__Spin_Request__Sequence__copy(
  const services_quiz_srv__srv__Spin_Request__Sequence * input,
  services_quiz_srv__srv__Spin_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(services_quiz_srv__srv__Spin_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    services_quiz_srv__srv__Spin_Request * data =
      (services_quiz_srv__srv__Spin_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!services_quiz_srv__srv__Spin_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          services_quiz_srv__srv__Spin_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!services_quiz_srv__srv__Spin_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


bool
services_quiz_srv__srv__Spin_Response__init(services_quiz_srv__srv__Spin_Response * msg)
{
  if (!msg) {
    return false;
  }
  // success
  return true;
}

void
services_quiz_srv__srv__Spin_Response__fini(services_quiz_srv__srv__Spin_Response * msg)
{
  if (!msg) {
    return;
  }
  // success
}

bool
services_quiz_srv__srv__Spin_Response__are_equal(const services_quiz_srv__srv__Spin_Response * lhs, const services_quiz_srv__srv__Spin_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // success
  if (lhs->success != rhs->success) {
    return false;
  }
  return true;
}

bool
services_quiz_srv__srv__Spin_Response__copy(
  const services_quiz_srv__srv__Spin_Response * input,
  services_quiz_srv__srv__Spin_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // success
  output->success = input->success;
  return true;
}

services_quiz_srv__srv__Spin_Response *
services_quiz_srv__srv__Spin_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  services_quiz_srv__srv__Spin_Response * msg = (services_quiz_srv__srv__Spin_Response *)allocator.allocate(sizeof(services_quiz_srv__srv__Spin_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(services_quiz_srv__srv__Spin_Response));
  bool success = services_quiz_srv__srv__Spin_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
services_quiz_srv__srv__Spin_Response__destroy(services_quiz_srv__srv__Spin_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    services_quiz_srv__srv__Spin_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
services_quiz_srv__srv__Spin_Response__Sequence__init(services_quiz_srv__srv__Spin_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  services_quiz_srv__srv__Spin_Response * data = NULL;

  if (size) {
    data = (services_quiz_srv__srv__Spin_Response *)allocator.zero_allocate(size, sizeof(services_quiz_srv__srv__Spin_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = services_quiz_srv__srv__Spin_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        services_quiz_srv__srv__Spin_Response__fini(&data[i - 1]);
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
services_quiz_srv__srv__Spin_Response__Sequence__fini(services_quiz_srv__srv__Spin_Response__Sequence * array)
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
      services_quiz_srv__srv__Spin_Response__fini(&array->data[i]);
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

services_quiz_srv__srv__Spin_Response__Sequence *
services_quiz_srv__srv__Spin_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  services_quiz_srv__srv__Spin_Response__Sequence * array = (services_quiz_srv__srv__Spin_Response__Sequence *)allocator.allocate(sizeof(services_quiz_srv__srv__Spin_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = services_quiz_srv__srv__Spin_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
services_quiz_srv__srv__Spin_Response__Sequence__destroy(services_quiz_srv__srv__Spin_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    services_quiz_srv__srv__Spin_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
services_quiz_srv__srv__Spin_Response__Sequence__are_equal(const services_quiz_srv__srv__Spin_Response__Sequence * lhs, const services_quiz_srv__srv__Spin_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!services_quiz_srv__srv__Spin_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
services_quiz_srv__srv__Spin_Response__Sequence__copy(
  const services_quiz_srv__srv__Spin_Response__Sequence * input,
  services_quiz_srv__srv__Spin_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(services_quiz_srv__srv__Spin_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    services_quiz_srv__srv__Spin_Response * data =
      (services_quiz_srv__srv__Spin_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!services_quiz_srv__srv__Spin_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          services_quiz_srv__srv__Spin_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!services_quiz_srv__srv__Spin_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
