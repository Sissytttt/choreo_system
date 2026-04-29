
#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};


#[link(name = "dance_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__dance_interfaces__action__Dance_Goal() -> *const std::ffi::c_void;
}

#[link(name = "dance_interfaces__rosidl_generator_c")]
extern "C" {
    fn dance_interfaces__action__Dance_Goal__init(msg: *mut Dance_Goal) -> bool;
    fn dance_interfaces__action__Dance_Goal__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<Dance_Goal>, size: usize) -> bool;
    fn dance_interfaces__action__Dance_Goal__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<Dance_Goal>);
    fn dance_interfaces__action__Dance_Goal__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<Dance_Goal>, out_seq: *mut rosidl_runtime_rs::Sequence<Dance_Goal>) -> bool;
}

// Corresponds to dance_interfaces__action__Dance_Goal
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Dance_Goal {

    // This member is not documented.
    #[allow(missing_docs)]
    pub dance_move: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub energy: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub texture: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub params: rosidl_runtime_rs::String,

}



impl Default for Dance_Goal {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !dance_interfaces__action__Dance_Goal__init(&mut msg as *mut _) {
        panic!("Call to dance_interfaces__action__Dance_Goal__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for Dance_Goal {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { dance_interfaces__action__Dance_Goal__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { dance_interfaces__action__Dance_Goal__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { dance_interfaces__action__Dance_Goal__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for Dance_Goal {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for Dance_Goal where Self: Sized {
  const TYPE_NAME: &'static str = "dance_interfaces/action/Dance_Goal";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__dance_interfaces__action__Dance_Goal() }
  }
}


#[link(name = "dance_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__dance_interfaces__action__Dance_Result() -> *const std::ffi::c_void;
}

#[link(name = "dance_interfaces__rosidl_generator_c")]
extern "C" {
    fn dance_interfaces__action__Dance_Result__init(msg: *mut Dance_Result) -> bool;
    fn dance_interfaces__action__Dance_Result__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<Dance_Result>, size: usize) -> bool;
    fn dance_interfaces__action__Dance_Result__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<Dance_Result>);
    fn dance_interfaces__action__Dance_Result__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<Dance_Result>, out_seq: *mut rosidl_runtime_rs::Sequence<Dance_Result>) -> bool;
}

// Corresponds to dance_interfaces__action__Dance_Result
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Dance_Result {

    // This member is not documented.
    #[allow(missing_docs)]
    pub result_code: i32,

}



impl Default for Dance_Result {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !dance_interfaces__action__Dance_Result__init(&mut msg as *mut _) {
        panic!("Call to dance_interfaces__action__Dance_Result__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for Dance_Result {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { dance_interfaces__action__Dance_Result__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { dance_interfaces__action__Dance_Result__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { dance_interfaces__action__Dance_Result__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for Dance_Result {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for Dance_Result where Self: Sized {
  const TYPE_NAME: &'static str = "dance_interfaces/action/Dance_Result";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__dance_interfaces__action__Dance_Result() }
  }
}


#[link(name = "dance_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__dance_interfaces__action__Dance_Feedback() -> *const std::ffi::c_void;
}

#[link(name = "dance_interfaces__rosidl_generator_c")]
extern "C" {
    fn dance_interfaces__action__Dance_Feedback__init(msg: *mut Dance_Feedback) -> bool;
    fn dance_interfaces__action__Dance_Feedback__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<Dance_Feedback>, size: usize) -> bool;
    fn dance_interfaces__action__Dance_Feedback__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<Dance_Feedback>);
    fn dance_interfaces__action__Dance_Feedback__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<Dance_Feedback>, out_seq: *mut rosidl_runtime_rs::Sequence<Dance_Feedback>) -> bool;
}

// Corresponds to dance_interfaces__action__Dance_Feedback
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Dance_Feedback {

    // This member is not documented.
    #[allow(missing_docs)]
    pub progress: i32,

}



impl Default for Dance_Feedback {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !dance_interfaces__action__Dance_Feedback__init(&mut msg as *mut _) {
        panic!("Call to dance_interfaces__action__Dance_Feedback__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for Dance_Feedback {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { dance_interfaces__action__Dance_Feedback__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { dance_interfaces__action__Dance_Feedback__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { dance_interfaces__action__Dance_Feedback__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for Dance_Feedback {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for Dance_Feedback where Self: Sized {
  const TYPE_NAME: &'static str = "dance_interfaces/action/Dance_Feedback";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__dance_interfaces__action__Dance_Feedback() }
  }
}


#[link(name = "dance_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__dance_interfaces__action__Dance_FeedbackMessage() -> *const std::ffi::c_void;
}

#[link(name = "dance_interfaces__rosidl_generator_c")]
extern "C" {
    fn dance_interfaces__action__Dance_FeedbackMessage__init(msg: *mut Dance_FeedbackMessage) -> bool;
    fn dance_interfaces__action__Dance_FeedbackMessage__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<Dance_FeedbackMessage>, size: usize) -> bool;
    fn dance_interfaces__action__Dance_FeedbackMessage__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<Dance_FeedbackMessage>);
    fn dance_interfaces__action__Dance_FeedbackMessage__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<Dance_FeedbackMessage>, out_seq: *mut rosidl_runtime_rs::Sequence<Dance_FeedbackMessage>) -> bool;
}

// Corresponds to dance_interfaces__action__Dance_FeedbackMessage
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Dance_FeedbackMessage {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub feedback: super::super::action::rmw::Dance_Feedback,

}



impl Default for Dance_FeedbackMessage {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !dance_interfaces__action__Dance_FeedbackMessage__init(&mut msg as *mut _) {
        panic!("Call to dance_interfaces__action__Dance_FeedbackMessage__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for Dance_FeedbackMessage {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { dance_interfaces__action__Dance_FeedbackMessage__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { dance_interfaces__action__Dance_FeedbackMessage__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { dance_interfaces__action__Dance_FeedbackMessage__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for Dance_FeedbackMessage {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for Dance_FeedbackMessage where Self: Sized {
  const TYPE_NAME: &'static str = "dance_interfaces/action/Dance_FeedbackMessage";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__dance_interfaces__action__Dance_FeedbackMessage() }
  }
}




#[link(name = "dance_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__dance_interfaces__action__Dance_SendGoal_Request() -> *const std::ffi::c_void;
}

#[link(name = "dance_interfaces__rosidl_generator_c")]
extern "C" {
    fn dance_interfaces__action__Dance_SendGoal_Request__init(msg: *mut Dance_SendGoal_Request) -> bool;
    fn dance_interfaces__action__Dance_SendGoal_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<Dance_SendGoal_Request>, size: usize) -> bool;
    fn dance_interfaces__action__Dance_SendGoal_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<Dance_SendGoal_Request>);
    fn dance_interfaces__action__Dance_SendGoal_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<Dance_SendGoal_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<Dance_SendGoal_Request>) -> bool;
}

// Corresponds to dance_interfaces__action__Dance_SendGoal_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Dance_SendGoal_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub goal: super::super::action::rmw::Dance_Goal,

}



impl Default for Dance_SendGoal_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !dance_interfaces__action__Dance_SendGoal_Request__init(&mut msg as *mut _) {
        panic!("Call to dance_interfaces__action__Dance_SendGoal_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for Dance_SendGoal_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { dance_interfaces__action__Dance_SendGoal_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { dance_interfaces__action__Dance_SendGoal_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { dance_interfaces__action__Dance_SendGoal_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for Dance_SendGoal_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for Dance_SendGoal_Request where Self: Sized {
  const TYPE_NAME: &'static str = "dance_interfaces/action/Dance_SendGoal_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__dance_interfaces__action__Dance_SendGoal_Request() }
  }
}


#[link(name = "dance_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__dance_interfaces__action__Dance_SendGoal_Response() -> *const std::ffi::c_void;
}

#[link(name = "dance_interfaces__rosidl_generator_c")]
extern "C" {
    fn dance_interfaces__action__Dance_SendGoal_Response__init(msg: *mut Dance_SendGoal_Response) -> bool;
    fn dance_interfaces__action__Dance_SendGoal_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<Dance_SendGoal_Response>, size: usize) -> bool;
    fn dance_interfaces__action__Dance_SendGoal_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<Dance_SendGoal_Response>);
    fn dance_interfaces__action__Dance_SendGoal_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<Dance_SendGoal_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<Dance_SendGoal_Response>) -> bool;
}

// Corresponds to dance_interfaces__action__Dance_SendGoal_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Dance_SendGoal_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub accepted: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub stamp: builtin_interfaces::msg::rmw::Time,

}



impl Default for Dance_SendGoal_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !dance_interfaces__action__Dance_SendGoal_Response__init(&mut msg as *mut _) {
        panic!("Call to dance_interfaces__action__Dance_SendGoal_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for Dance_SendGoal_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { dance_interfaces__action__Dance_SendGoal_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { dance_interfaces__action__Dance_SendGoal_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { dance_interfaces__action__Dance_SendGoal_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for Dance_SendGoal_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for Dance_SendGoal_Response where Self: Sized {
  const TYPE_NAME: &'static str = "dance_interfaces/action/Dance_SendGoal_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__dance_interfaces__action__Dance_SendGoal_Response() }
  }
}


#[link(name = "dance_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__dance_interfaces__action__Dance_GetResult_Request() -> *const std::ffi::c_void;
}

#[link(name = "dance_interfaces__rosidl_generator_c")]
extern "C" {
    fn dance_interfaces__action__Dance_GetResult_Request__init(msg: *mut Dance_GetResult_Request) -> bool;
    fn dance_interfaces__action__Dance_GetResult_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<Dance_GetResult_Request>, size: usize) -> bool;
    fn dance_interfaces__action__Dance_GetResult_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<Dance_GetResult_Request>);
    fn dance_interfaces__action__Dance_GetResult_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<Dance_GetResult_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<Dance_GetResult_Request>) -> bool;
}

// Corresponds to dance_interfaces__action__Dance_GetResult_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Dance_GetResult_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,

}



impl Default for Dance_GetResult_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !dance_interfaces__action__Dance_GetResult_Request__init(&mut msg as *mut _) {
        panic!("Call to dance_interfaces__action__Dance_GetResult_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for Dance_GetResult_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { dance_interfaces__action__Dance_GetResult_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { dance_interfaces__action__Dance_GetResult_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { dance_interfaces__action__Dance_GetResult_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for Dance_GetResult_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for Dance_GetResult_Request where Self: Sized {
  const TYPE_NAME: &'static str = "dance_interfaces/action/Dance_GetResult_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__dance_interfaces__action__Dance_GetResult_Request() }
  }
}


#[link(name = "dance_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__dance_interfaces__action__Dance_GetResult_Response() -> *const std::ffi::c_void;
}

#[link(name = "dance_interfaces__rosidl_generator_c")]
extern "C" {
    fn dance_interfaces__action__Dance_GetResult_Response__init(msg: *mut Dance_GetResult_Response) -> bool;
    fn dance_interfaces__action__Dance_GetResult_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<Dance_GetResult_Response>, size: usize) -> bool;
    fn dance_interfaces__action__Dance_GetResult_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<Dance_GetResult_Response>);
    fn dance_interfaces__action__Dance_GetResult_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<Dance_GetResult_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<Dance_GetResult_Response>) -> bool;
}

// Corresponds to dance_interfaces__action__Dance_GetResult_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Dance_GetResult_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub status: i8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub result: super::super::action::rmw::Dance_Result,

}



impl Default for Dance_GetResult_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !dance_interfaces__action__Dance_GetResult_Response__init(&mut msg as *mut _) {
        panic!("Call to dance_interfaces__action__Dance_GetResult_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for Dance_GetResult_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { dance_interfaces__action__Dance_GetResult_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { dance_interfaces__action__Dance_GetResult_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { dance_interfaces__action__Dance_GetResult_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for Dance_GetResult_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for Dance_GetResult_Response where Self: Sized {
  const TYPE_NAME: &'static str = "dance_interfaces/action/Dance_GetResult_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__dance_interfaces__action__Dance_GetResult_Response() }
  }
}






#[link(name = "dance_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__dance_interfaces__action__Dance_SendGoal() -> *const std::ffi::c_void;
}

// Corresponds to dance_interfaces__action__Dance_SendGoal
#[allow(missing_docs, non_camel_case_types)]
pub struct Dance_SendGoal;

impl rosidl_runtime_rs::Service for Dance_SendGoal {
    type Request = Dance_SendGoal_Request;
    type Response = Dance_SendGoal_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__dance_interfaces__action__Dance_SendGoal() }
    }
}




#[link(name = "dance_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__dance_interfaces__action__Dance_GetResult() -> *const std::ffi::c_void;
}

// Corresponds to dance_interfaces__action__Dance_GetResult
#[allow(missing_docs, non_camel_case_types)]
pub struct Dance_GetResult;

impl rosidl_runtime_rs::Service for Dance_GetResult {
    type Request = Dance_GetResult_Request;
    type Response = Dance_GetResult_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__dance_interfaces__action__Dance_GetResult() }
    }
}


