// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from dance_interfaces:action/Dance.idl
// generated code does not contain a copyright notice

#ifndef DANCE_INTERFACES__ACTION__DETAIL__DANCE__STRUCT_HPP_
#define DANCE_INTERFACES__ACTION__DETAIL__DANCE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__dance_interfaces__action__Dance_Goal __attribute__((deprecated))
#else
# define DEPRECATED__dance_interfaces__action__Dance_Goal __declspec(deprecated)
#endif

namespace dance_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct Dance_Goal_
{
  using Type = Dance_Goal_<ContainerAllocator>;

  explicit Dance_Goal_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::DEFAULTS_ONLY == _init)
    {
      this->energy = 0.5f;
      this->texture = "neutral";
    } else if (rosidl_runtime_cpp::MessageInitialization::ZERO == _init) {
      this->dance_move = "";
      this->energy = 0.0f;
      this->texture = "";
      this->params = "";
    }
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->dance_move = "";
      this->params = "";
    }
  }

  explicit Dance_Goal_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : dance_move(_alloc),
    texture(_alloc),
    params(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::DEFAULTS_ONLY == _init)
    {
      this->energy = 0.5f;
      this->texture = "neutral";
    } else if (rosidl_runtime_cpp::MessageInitialization::ZERO == _init) {
      this->dance_move = "";
      this->energy = 0.0f;
      this->texture = "";
      this->params = "";
    }
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->dance_move = "";
      this->params = "";
    }
  }

  // field types and members
  using _dance_move_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _dance_move_type dance_move;
  using _energy_type =
    float;
  _energy_type energy;
  using _texture_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _texture_type texture;
  using _params_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _params_type params;

  // setters for named parameter idiom
  Type & set__dance_move(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->dance_move = _arg;
    return *this;
  }
  Type & set__energy(
    const float & _arg)
  {
    this->energy = _arg;
    return *this;
  }
  Type & set__texture(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->texture = _arg;
    return *this;
  }
  Type & set__params(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->params = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    dance_interfaces::action::Dance_Goal_<ContainerAllocator> *;
  using ConstRawPtr =
    const dance_interfaces::action::Dance_Goal_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<dance_interfaces::action::Dance_Goal_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<dance_interfaces::action::Dance_Goal_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      dance_interfaces::action::Dance_Goal_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<dance_interfaces::action::Dance_Goal_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      dance_interfaces::action::Dance_Goal_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<dance_interfaces::action::Dance_Goal_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<dance_interfaces::action::Dance_Goal_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<dance_interfaces::action::Dance_Goal_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__dance_interfaces__action__Dance_Goal
    std::shared_ptr<dance_interfaces::action::Dance_Goal_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__dance_interfaces__action__Dance_Goal
    std::shared_ptr<dance_interfaces::action::Dance_Goal_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Dance_Goal_ & other) const
  {
    if (this->dance_move != other.dance_move) {
      return false;
    }
    if (this->energy != other.energy) {
      return false;
    }
    if (this->texture != other.texture) {
      return false;
    }
    if (this->params != other.params) {
      return false;
    }
    return true;
  }
  bool operator!=(const Dance_Goal_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Dance_Goal_

// alias to use template instance with default allocator
using Dance_Goal =
  dance_interfaces::action::Dance_Goal_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace dance_interfaces


#ifndef _WIN32
# define DEPRECATED__dance_interfaces__action__Dance_Result __attribute__((deprecated))
#else
# define DEPRECATED__dance_interfaces__action__Dance_Result __declspec(deprecated)
#endif

namespace dance_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct Dance_Result_
{
  using Type = Dance_Result_<ContainerAllocator>;

  explicit Dance_Result_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->result_code = 0l;
    }
  }

  explicit Dance_Result_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->result_code = 0l;
    }
  }

  // field types and members
  using _result_code_type =
    int32_t;
  _result_code_type result_code;

  // setters for named parameter idiom
  Type & set__result_code(
    const int32_t & _arg)
  {
    this->result_code = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    dance_interfaces::action::Dance_Result_<ContainerAllocator> *;
  using ConstRawPtr =
    const dance_interfaces::action::Dance_Result_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<dance_interfaces::action::Dance_Result_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<dance_interfaces::action::Dance_Result_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      dance_interfaces::action::Dance_Result_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<dance_interfaces::action::Dance_Result_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      dance_interfaces::action::Dance_Result_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<dance_interfaces::action::Dance_Result_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<dance_interfaces::action::Dance_Result_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<dance_interfaces::action::Dance_Result_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__dance_interfaces__action__Dance_Result
    std::shared_ptr<dance_interfaces::action::Dance_Result_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__dance_interfaces__action__Dance_Result
    std::shared_ptr<dance_interfaces::action::Dance_Result_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Dance_Result_ & other) const
  {
    if (this->result_code != other.result_code) {
      return false;
    }
    return true;
  }
  bool operator!=(const Dance_Result_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Dance_Result_

// alias to use template instance with default allocator
using Dance_Result =
  dance_interfaces::action::Dance_Result_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace dance_interfaces


#ifndef _WIN32
# define DEPRECATED__dance_interfaces__action__Dance_Feedback __attribute__((deprecated))
#else
# define DEPRECATED__dance_interfaces__action__Dance_Feedback __declspec(deprecated)
#endif

namespace dance_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct Dance_Feedback_
{
  using Type = Dance_Feedback_<ContainerAllocator>;

  explicit Dance_Feedback_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->progress = 0l;
    }
  }

  explicit Dance_Feedback_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->progress = 0l;
    }
  }

  // field types and members
  using _progress_type =
    int32_t;
  _progress_type progress;

  // setters for named parameter idiom
  Type & set__progress(
    const int32_t & _arg)
  {
    this->progress = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    dance_interfaces::action::Dance_Feedback_<ContainerAllocator> *;
  using ConstRawPtr =
    const dance_interfaces::action::Dance_Feedback_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<dance_interfaces::action::Dance_Feedback_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<dance_interfaces::action::Dance_Feedback_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      dance_interfaces::action::Dance_Feedback_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<dance_interfaces::action::Dance_Feedback_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      dance_interfaces::action::Dance_Feedback_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<dance_interfaces::action::Dance_Feedback_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<dance_interfaces::action::Dance_Feedback_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<dance_interfaces::action::Dance_Feedback_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__dance_interfaces__action__Dance_Feedback
    std::shared_ptr<dance_interfaces::action::Dance_Feedback_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__dance_interfaces__action__Dance_Feedback
    std::shared_ptr<dance_interfaces::action::Dance_Feedback_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Dance_Feedback_ & other) const
  {
    if (this->progress != other.progress) {
      return false;
    }
    return true;
  }
  bool operator!=(const Dance_Feedback_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Dance_Feedback_

// alias to use template instance with default allocator
using Dance_Feedback =
  dance_interfaces::action::Dance_Feedback_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace dance_interfaces


// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.hpp"
// Member 'goal'
#include "dance_interfaces/action/detail/dance__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__dance_interfaces__action__Dance_SendGoal_Request __attribute__((deprecated))
#else
# define DEPRECATED__dance_interfaces__action__Dance_SendGoal_Request __declspec(deprecated)
#endif

namespace dance_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct Dance_SendGoal_Request_
{
  using Type = Dance_SendGoal_Request_<ContainerAllocator>;

  explicit Dance_SendGoal_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_init),
    goal(_init)
  {
    (void)_init;
  }

  explicit Dance_SendGoal_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_alloc, _init),
    goal(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _goal_id_type =
    unique_identifier_msgs::msg::UUID_<ContainerAllocator>;
  _goal_id_type goal_id;
  using _goal_type =
    dance_interfaces::action::Dance_Goal_<ContainerAllocator>;
  _goal_type goal;

  // setters for named parameter idiom
  Type & set__goal_id(
    const unique_identifier_msgs::msg::UUID_<ContainerAllocator> & _arg)
  {
    this->goal_id = _arg;
    return *this;
  }
  Type & set__goal(
    const dance_interfaces::action::Dance_Goal_<ContainerAllocator> & _arg)
  {
    this->goal = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    dance_interfaces::action::Dance_SendGoal_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const dance_interfaces::action::Dance_SendGoal_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<dance_interfaces::action::Dance_SendGoal_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<dance_interfaces::action::Dance_SendGoal_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      dance_interfaces::action::Dance_SendGoal_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<dance_interfaces::action::Dance_SendGoal_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      dance_interfaces::action::Dance_SendGoal_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<dance_interfaces::action::Dance_SendGoal_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<dance_interfaces::action::Dance_SendGoal_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<dance_interfaces::action::Dance_SendGoal_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__dance_interfaces__action__Dance_SendGoal_Request
    std::shared_ptr<dance_interfaces::action::Dance_SendGoal_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__dance_interfaces__action__Dance_SendGoal_Request
    std::shared_ptr<dance_interfaces::action::Dance_SendGoal_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Dance_SendGoal_Request_ & other) const
  {
    if (this->goal_id != other.goal_id) {
      return false;
    }
    if (this->goal != other.goal) {
      return false;
    }
    return true;
  }
  bool operator!=(const Dance_SendGoal_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Dance_SendGoal_Request_

// alias to use template instance with default allocator
using Dance_SendGoal_Request =
  dance_interfaces::action::Dance_SendGoal_Request_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace dance_interfaces


// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__dance_interfaces__action__Dance_SendGoal_Response __attribute__((deprecated))
#else
# define DEPRECATED__dance_interfaces__action__Dance_SendGoal_Response __declspec(deprecated)
#endif

namespace dance_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct Dance_SendGoal_Response_
{
  using Type = Dance_SendGoal_Response_<ContainerAllocator>;

  explicit Dance_SendGoal_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->accepted = false;
    }
  }

  explicit Dance_SendGoal_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->accepted = false;
    }
  }

  // field types and members
  using _accepted_type =
    bool;
  _accepted_type accepted;
  using _stamp_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _stamp_type stamp;

  // setters for named parameter idiom
  Type & set__accepted(
    const bool & _arg)
  {
    this->accepted = _arg;
    return *this;
  }
  Type & set__stamp(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->stamp = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    dance_interfaces::action::Dance_SendGoal_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const dance_interfaces::action::Dance_SendGoal_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<dance_interfaces::action::Dance_SendGoal_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<dance_interfaces::action::Dance_SendGoal_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      dance_interfaces::action::Dance_SendGoal_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<dance_interfaces::action::Dance_SendGoal_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      dance_interfaces::action::Dance_SendGoal_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<dance_interfaces::action::Dance_SendGoal_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<dance_interfaces::action::Dance_SendGoal_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<dance_interfaces::action::Dance_SendGoal_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__dance_interfaces__action__Dance_SendGoal_Response
    std::shared_ptr<dance_interfaces::action::Dance_SendGoal_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__dance_interfaces__action__Dance_SendGoal_Response
    std::shared_ptr<dance_interfaces::action::Dance_SendGoal_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Dance_SendGoal_Response_ & other) const
  {
    if (this->accepted != other.accepted) {
      return false;
    }
    if (this->stamp != other.stamp) {
      return false;
    }
    return true;
  }
  bool operator!=(const Dance_SendGoal_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Dance_SendGoal_Response_

// alias to use template instance with default allocator
using Dance_SendGoal_Response =
  dance_interfaces::action::Dance_SendGoal_Response_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace dance_interfaces

namespace dance_interfaces
{

namespace action
{

struct Dance_SendGoal
{
  using Request = dance_interfaces::action::Dance_SendGoal_Request;
  using Response = dance_interfaces::action::Dance_SendGoal_Response;
};

}  // namespace action

}  // namespace dance_interfaces


// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__dance_interfaces__action__Dance_GetResult_Request __attribute__((deprecated))
#else
# define DEPRECATED__dance_interfaces__action__Dance_GetResult_Request __declspec(deprecated)
#endif

namespace dance_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct Dance_GetResult_Request_
{
  using Type = Dance_GetResult_Request_<ContainerAllocator>;

  explicit Dance_GetResult_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_init)
  {
    (void)_init;
  }

  explicit Dance_GetResult_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _goal_id_type =
    unique_identifier_msgs::msg::UUID_<ContainerAllocator>;
  _goal_id_type goal_id;

  // setters for named parameter idiom
  Type & set__goal_id(
    const unique_identifier_msgs::msg::UUID_<ContainerAllocator> & _arg)
  {
    this->goal_id = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    dance_interfaces::action::Dance_GetResult_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const dance_interfaces::action::Dance_GetResult_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<dance_interfaces::action::Dance_GetResult_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<dance_interfaces::action::Dance_GetResult_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      dance_interfaces::action::Dance_GetResult_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<dance_interfaces::action::Dance_GetResult_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      dance_interfaces::action::Dance_GetResult_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<dance_interfaces::action::Dance_GetResult_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<dance_interfaces::action::Dance_GetResult_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<dance_interfaces::action::Dance_GetResult_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__dance_interfaces__action__Dance_GetResult_Request
    std::shared_ptr<dance_interfaces::action::Dance_GetResult_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__dance_interfaces__action__Dance_GetResult_Request
    std::shared_ptr<dance_interfaces::action::Dance_GetResult_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Dance_GetResult_Request_ & other) const
  {
    if (this->goal_id != other.goal_id) {
      return false;
    }
    return true;
  }
  bool operator!=(const Dance_GetResult_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Dance_GetResult_Request_

// alias to use template instance with default allocator
using Dance_GetResult_Request =
  dance_interfaces::action::Dance_GetResult_Request_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace dance_interfaces


// Include directives for member types
// Member 'result'
// already included above
// #include "dance_interfaces/action/detail/dance__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__dance_interfaces__action__Dance_GetResult_Response __attribute__((deprecated))
#else
# define DEPRECATED__dance_interfaces__action__Dance_GetResult_Response __declspec(deprecated)
#endif

namespace dance_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct Dance_GetResult_Response_
{
  using Type = Dance_GetResult_Response_<ContainerAllocator>;

  explicit Dance_GetResult_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : result(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->status = 0;
    }
  }

  explicit Dance_GetResult_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : result(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->status = 0;
    }
  }

  // field types and members
  using _status_type =
    int8_t;
  _status_type status;
  using _result_type =
    dance_interfaces::action::Dance_Result_<ContainerAllocator>;
  _result_type result;

  // setters for named parameter idiom
  Type & set__status(
    const int8_t & _arg)
  {
    this->status = _arg;
    return *this;
  }
  Type & set__result(
    const dance_interfaces::action::Dance_Result_<ContainerAllocator> & _arg)
  {
    this->result = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    dance_interfaces::action::Dance_GetResult_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const dance_interfaces::action::Dance_GetResult_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<dance_interfaces::action::Dance_GetResult_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<dance_interfaces::action::Dance_GetResult_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      dance_interfaces::action::Dance_GetResult_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<dance_interfaces::action::Dance_GetResult_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      dance_interfaces::action::Dance_GetResult_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<dance_interfaces::action::Dance_GetResult_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<dance_interfaces::action::Dance_GetResult_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<dance_interfaces::action::Dance_GetResult_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__dance_interfaces__action__Dance_GetResult_Response
    std::shared_ptr<dance_interfaces::action::Dance_GetResult_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__dance_interfaces__action__Dance_GetResult_Response
    std::shared_ptr<dance_interfaces::action::Dance_GetResult_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Dance_GetResult_Response_ & other) const
  {
    if (this->status != other.status) {
      return false;
    }
    if (this->result != other.result) {
      return false;
    }
    return true;
  }
  bool operator!=(const Dance_GetResult_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Dance_GetResult_Response_

// alias to use template instance with default allocator
using Dance_GetResult_Response =
  dance_interfaces::action::Dance_GetResult_Response_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace dance_interfaces

namespace dance_interfaces
{

namespace action
{

struct Dance_GetResult
{
  using Request = dance_interfaces::action::Dance_GetResult_Request;
  using Response = dance_interfaces::action::Dance_GetResult_Response;
};

}  // namespace action

}  // namespace dance_interfaces


// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.hpp"
// Member 'feedback'
// already included above
// #include "dance_interfaces/action/detail/dance__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__dance_interfaces__action__Dance_FeedbackMessage __attribute__((deprecated))
#else
# define DEPRECATED__dance_interfaces__action__Dance_FeedbackMessage __declspec(deprecated)
#endif

namespace dance_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct Dance_FeedbackMessage_
{
  using Type = Dance_FeedbackMessage_<ContainerAllocator>;

  explicit Dance_FeedbackMessage_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_init),
    feedback(_init)
  {
    (void)_init;
  }

  explicit Dance_FeedbackMessage_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_alloc, _init),
    feedback(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _goal_id_type =
    unique_identifier_msgs::msg::UUID_<ContainerAllocator>;
  _goal_id_type goal_id;
  using _feedback_type =
    dance_interfaces::action::Dance_Feedback_<ContainerAllocator>;
  _feedback_type feedback;

  // setters for named parameter idiom
  Type & set__goal_id(
    const unique_identifier_msgs::msg::UUID_<ContainerAllocator> & _arg)
  {
    this->goal_id = _arg;
    return *this;
  }
  Type & set__feedback(
    const dance_interfaces::action::Dance_Feedback_<ContainerAllocator> & _arg)
  {
    this->feedback = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    dance_interfaces::action::Dance_FeedbackMessage_<ContainerAllocator> *;
  using ConstRawPtr =
    const dance_interfaces::action::Dance_FeedbackMessage_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<dance_interfaces::action::Dance_FeedbackMessage_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<dance_interfaces::action::Dance_FeedbackMessage_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      dance_interfaces::action::Dance_FeedbackMessage_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<dance_interfaces::action::Dance_FeedbackMessage_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      dance_interfaces::action::Dance_FeedbackMessage_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<dance_interfaces::action::Dance_FeedbackMessage_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<dance_interfaces::action::Dance_FeedbackMessage_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<dance_interfaces::action::Dance_FeedbackMessage_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__dance_interfaces__action__Dance_FeedbackMessage
    std::shared_ptr<dance_interfaces::action::Dance_FeedbackMessage_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__dance_interfaces__action__Dance_FeedbackMessage
    std::shared_ptr<dance_interfaces::action::Dance_FeedbackMessage_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Dance_FeedbackMessage_ & other) const
  {
    if (this->goal_id != other.goal_id) {
      return false;
    }
    if (this->feedback != other.feedback) {
      return false;
    }
    return true;
  }
  bool operator!=(const Dance_FeedbackMessage_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Dance_FeedbackMessage_

// alias to use template instance with default allocator
using Dance_FeedbackMessage =
  dance_interfaces::action::Dance_FeedbackMessage_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace dance_interfaces

#include "action_msgs/srv/cancel_goal.hpp"
#include "action_msgs/msg/goal_info.hpp"
#include "action_msgs/msg/goal_status_array.hpp"

namespace dance_interfaces
{

namespace action
{

struct Dance
{
  /// The goal message defined in the action definition.
  using Goal = dance_interfaces::action::Dance_Goal;
  /// The result message defined in the action definition.
  using Result = dance_interfaces::action::Dance_Result;
  /// The feedback message defined in the action definition.
  using Feedback = dance_interfaces::action::Dance_Feedback;

  struct Impl
  {
    /// The send_goal service using a wrapped version of the goal message as a request.
    using SendGoalService = dance_interfaces::action::Dance_SendGoal;
    /// The get_result service using a wrapped version of the result message as a response.
    using GetResultService = dance_interfaces::action::Dance_GetResult;
    /// The feedback message with generic fields which wraps the feedback message.
    using FeedbackMessage = dance_interfaces::action::Dance_FeedbackMessage;

    /// The generic service to cancel a goal.
    using CancelGoalService = action_msgs::srv::CancelGoal;
    /// The generic message for the status of a goal.
    using GoalStatusMessage = action_msgs::msg::GoalStatusArray;
  };
};

typedef struct Dance Dance;

}  // namespace action

}  // namespace dance_interfaces

#endif  // DANCE_INTERFACES__ACTION__DETAIL__DANCE__STRUCT_HPP_
