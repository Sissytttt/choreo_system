// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from dance_interfaces:action/Dance.idl
// generated code does not contain a copyright notice

#ifndef DANCE_INTERFACES__ACTION__DETAIL__DANCE__BUILDER_HPP_
#define DANCE_INTERFACES__ACTION__DETAIL__DANCE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "dance_interfaces/action/detail/dance__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace dance_interfaces
{

namespace action
{

namespace builder
{

class Init_Dance_Goal_params
{
public:
  explicit Init_Dance_Goal_params(::dance_interfaces::action::Dance_Goal & msg)
  : msg_(msg)
  {}
  ::dance_interfaces::action::Dance_Goal params(::dance_interfaces::action::Dance_Goal::_params_type arg)
  {
    msg_.params = std::move(arg);
    return std::move(msg_);
  }

private:
  ::dance_interfaces::action::Dance_Goal msg_;
};

class Init_Dance_Goal_texture
{
public:
  explicit Init_Dance_Goal_texture(::dance_interfaces::action::Dance_Goal & msg)
  : msg_(msg)
  {}
  Init_Dance_Goal_params texture(::dance_interfaces::action::Dance_Goal::_texture_type arg)
  {
    msg_.texture = std::move(arg);
    return Init_Dance_Goal_params(msg_);
  }

private:
  ::dance_interfaces::action::Dance_Goal msg_;
};

class Init_Dance_Goal_energy
{
public:
  explicit Init_Dance_Goal_energy(::dance_interfaces::action::Dance_Goal & msg)
  : msg_(msg)
  {}
  Init_Dance_Goal_texture energy(::dance_interfaces::action::Dance_Goal::_energy_type arg)
  {
    msg_.energy = std::move(arg);
    return Init_Dance_Goal_texture(msg_);
  }

private:
  ::dance_interfaces::action::Dance_Goal msg_;
};

class Init_Dance_Goal_dance_move
{
public:
  Init_Dance_Goal_dance_move()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Dance_Goal_energy dance_move(::dance_interfaces::action::Dance_Goal::_dance_move_type arg)
  {
    msg_.dance_move = std::move(arg);
    return Init_Dance_Goal_energy(msg_);
  }

private:
  ::dance_interfaces::action::Dance_Goal msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::dance_interfaces::action::Dance_Goal>()
{
  return dance_interfaces::action::builder::Init_Dance_Goal_dance_move();
}

}  // namespace dance_interfaces


namespace dance_interfaces
{

namespace action
{

namespace builder
{

class Init_Dance_Result_result_code
{
public:
  Init_Dance_Result_result_code()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::dance_interfaces::action::Dance_Result result_code(::dance_interfaces::action::Dance_Result::_result_code_type arg)
  {
    msg_.result_code = std::move(arg);
    return std::move(msg_);
  }

private:
  ::dance_interfaces::action::Dance_Result msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::dance_interfaces::action::Dance_Result>()
{
  return dance_interfaces::action::builder::Init_Dance_Result_result_code();
}

}  // namespace dance_interfaces


namespace dance_interfaces
{

namespace action
{

namespace builder
{

class Init_Dance_Feedback_progress
{
public:
  Init_Dance_Feedback_progress()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::dance_interfaces::action::Dance_Feedback progress(::dance_interfaces::action::Dance_Feedback::_progress_type arg)
  {
    msg_.progress = std::move(arg);
    return std::move(msg_);
  }

private:
  ::dance_interfaces::action::Dance_Feedback msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::dance_interfaces::action::Dance_Feedback>()
{
  return dance_interfaces::action::builder::Init_Dance_Feedback_progress();
}

}  // namespace dance_interfaces


namespace dance_interfaces
{

namespace action
{

namespace builder
{

class Init_Dance_SendGoal_Request_goal
{
public:
  explicit Init_Dance_SendGoal_Request_goal(::dance_interfaces::action::Dance_SendGoal_Request & msg)
  : msg_(msg)
  {}
  ::dance_interfaces::action::Dance_SendGoal_Request goal(::dance_interfaces::action::Dance_SendGoal_Request::_goal_type arg)
  {
    msg_.goal = std::move(arg);
    return std::move(msg_);
  }

private:
  ::dance_interfaces::action::Dance_SendGoal_Request msg_;
};

class Init_Dance_SendGoal_Request_goal_id
{
public:
  Init_Dance_SendGoal_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Dance_SendGoal_Request_goal goal_id(::dance_interfaces::action::Dance_SendGoal_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_Dance_SendGoal_Request_goal(msg_);
  }

private:
  ::dance_interfaces::action::Dance_SendGoal_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::dance_interfaces::action::Dance_SendGoal_Request>()
{
  return dance_interfaces::action::builder::Init_Dance_SendGoal_Request_goal_id();
}

}  // namespace dance_interfaces


namespace dance_interfaces
{

namespace action
{

namespace builder
{

class Init_Dance_SendGoal_Response_stamp
{
public:
  explicit Init_Dance_SendGoal_Response_stamp(::dance_interfaces::action::Dance_SendGoal_Response & msg)
  : msg_(msg)
  {}
  ::dance_interfaces::action::Dance_SendGoal_Response stamp(::dance_interfaces::action::Dance_SendGoal_Response::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::dance_interfaces::action::Dance_SendGoal_Response msg_;
};

class Init_Dance_SendGoal_Response_accepted
{
public:
  Init_Dance_SendGoal_Response_accepted()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Dance_SendGoal_Response_stamp accepted(::dance_interfaces::action::Dance_SendGoal_Response::_accepted_type arg)
  {
    msg_.accepted = std::move(arg);
    return Init_Dance_SendGoal_Response_stamp(msg_);
  }

private:
  ::dance_interfaces::action::Dance_SendGoal_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::dance_interfaces::action::Dance_SendGoal_Response>()
{
  return dance_interfaces::action::builder::Init_Dance_SendGoal_Response_accepted();
}

}  // namespace dance_interfaces


namespace dance_interfaces
{

namespace action
{

namespace builder
{

class Init_Dance_GetResult_Request_goal_id
{
public:
  Init_Dance_GetResult_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::dance_interfaces::action::Dance_GetResult_Request goal_id(::dance_interfaces::action::Dance_GetResult_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::dance_interfaces::action::Dance_GetResult_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::dance_interfaces::action::Dance_GetResult_Request>()
{
  return dance_interfaces::action::builder::Init_Dance_GetResult_Request_goal_id();
}

}  // namespace dance_interfaces


namespace dance_interfaces
{

namespace action
{

namespace builder
{

class Init_Dance_GetResult_Response_result
{
public:
  explicit Init_Dance_GetResult_Response_result(::dance_interfaces::action::Dance_GetResult_Response & msg)
  : msg_(msg)
  {}
  ::dance_interfaces::action::Dance_GetResult_Response result(::dance_interfaces::action::Dance_GetResult_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::dance_interfaces::action::Dance_GetResult_Response msg_;
};

class Init_Dance_GetResult_Response_status
{
public:
  Init_Dance_GetResult_Response_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Dance_GetResult_Response_result status(::dance_interfaces::action::Dance_GetResult_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_Dance_GetResult_Response_result(msg_);
  }

private:
  ::dance_interfaces::action::Dance_GetResult_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::dance_interfaces::action::Dance_GetResult_Response>()
{
  return dance_interfaces::action::builder::Init_Dance_GetResult_Response_status();
}

}  // namespace dance_interfaces


namespace dance_interfaces
{

namespace action
{

namespace builder
{

class Init_Dance_FeedbackMessage_feedback
{
public:
  explicit Init_Dance_FeedbackMessage_feedback(::dance_interfaces::action::Dance_FeedbackMessage & msg)
  : msg_(msg)
  {}
  ::dance_interfaces::action::Dance_FeedbackMessage feedback(::dance_interfaces::action::Dance_FeedbackMessage::_feedback_type arg)
  {
    msg_.feedback = std::move(arg);
    return std::move(msg_);
  }

private:
  ::dance_interfaces::action::Dance_FeedbackMessage msg_;
};

class Init_Dance_FeedbackMessage_goal_id
{
public:
  Init_Dance_FeedbackMessage_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Dance_FeedbackMessage_feedback goal_id(::dance_interfaces::action::Dance_FeedbackMessage::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_Dance_FeedbackMessage_feedback(msg_);
  }

private:
  ::dance_interfaces::action::Dance_FeedbackMessage msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::dance_interfaces::action::Dance_FeedbackMessage>()
{
  return dance_interfaces::action::builder::Init_Dance_FeedbackMessage_goal_id();
}

}  // namespace dance_interfaces

#endif  // DANCE_INTERFACES__ACTION__DETAIL__DANCE__BUILDER_HPP_
