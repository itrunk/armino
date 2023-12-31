Event Mechanism
======================================================

:link_to_translation:`zh_CN:[中文]`

The event mechanism is used to notify users of asynchronous events generated by the SDK, such as WiFi disconnection。

Implementation Overview
*****************************************************

The event mechanism in the SDK is mainly implemented through a special event task. The event 
task manages the callback functions registered by 'bk_event_register_cb()' in a linked list. 
When 'bk_event_register_cb()' calls, the event task adds a node to the linked list. 
When 'bk_event_unregister_cb()' calls, the event task deletes the callback function node 
in the linked list and releases memory. When an event occurs, the event task calls all 
callback functions under the event in turn.


To save memory, the stack size of the Event Task is 2048 bytes by default, which can be configured in the SDK
CFG_EVENT_TASK_STACK_SIZE is defined in the file to modify the default size.


Precautions for callback function implementation
***************************************************************

The following principles should be observed when implementing callback functions：

 - There should be no blocking operation in the callback function. If the callback function is blocked, 
   it may affect other event processing
 - The call depth of the callback function should not be too deep, or the event task stack may overflow
 - The data pointer passed in the callback function will be released after the callback function returns.
   Therefore, if the application needs to access the data after the callback function returns, it needs 
   to copy the event data in the callback function


Call order of callback function
***************************************************************

When an event occurs, taking EVENT_WIFI_STA_CONNECTED as an example, 
the event task calls the callback function in the following order：

 - If a module pays attention to all the events under 'EVENT_WIFI_MOD', that is, 
   when the 'event_id' parameter is 'EVENT_ID_ALL' in 'bk_event_register_cb', it calls 
   all the callback functions registered as 'EVENT_ID_ALL' in turn, in the order of 
   registration first and calling first.
 - Call all the callback functions under the EVENT_WIFI_STA_CONNECTED event in turn, 
   and the calling sequence is registration first and call first.

.. important::

   In general, the application should not make any assumptions about the calling 
   sequence of different callback functions under the same event.


API Examples
**************************************************************************

Suppose the application wants to focus on 'EVENT_WIFI_STA_CONNECTED', 
Where user_cb() is the user-defined callback function and s_user_cb_arg is 
the user parameter of the callback function, the registration method is as follows::

    BK_LOG_ON_ERR(bk_event_register_cb(EVENT_MOD_WIFI, EVENT_WIFI_STA_CONNECTED,
	        user_cb, s_user_cb_arg));

When EVENT_WIFI_STA_CONNECTED is generated, the event task will call user_cb, 
and the first parameter is s_user_cb_arg.


If the application wants to focus on multiple or all events generated by the WiFi module, 
in addition to registering callback functions one by one as described above, it can also 
register a callback function to handle all WiFi events in the following way::

    BK_LOG_ON_ERR(bk_event_register_cb(EVENT_MOD_WIFI, EVENT_ID_ALL,
	        user_cb, s_user_cb_arg));

.. note::

   当When the application does not need to pay attention to an event, it is recommended to 
   call 'bk_event_unregister_cb()' to delete the callback function node; In particular, 
   when the callback function pointer or user parameter is no longer valid, be sure to call 
   'bk_event_unregister_cb()' to prevent illegal callback function calls or parameter accesses 
   from causing errors. 
