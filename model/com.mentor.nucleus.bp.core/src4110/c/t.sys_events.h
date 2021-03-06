T_b("/*");
T_b("\n");
T_b(" ");
T_b("* Data structures and methods associated with the event base class of this");
T_b("\n");
T_b(" ");
T_b("* model compiler.");
T_b("\n");
T_b(" ");
T_b("*/");
T_b("\n");
T_b("/* ");
T_b(te_typemap->event_flags_name);
T_b(" bit masks */");
T_b("\n");
T_b("#define ");
T_b(te_prefix->define_u);
T_b("IS_INSTANCE_EVENT     0x01");
T_b("\n");
T_b("#define ");
T_b(te_prefix->define_u);
T_b("IS_CREATION_EVENT     0x02");
T_b("\n");
T_b("#define ");
T_b(te_prefix->define_u);
T_b("IS_ASSIGNER_EVENT     0x04");
T_b("\n");
T_b("#define ");
T_b(te_prefix->define_u);
T_b("IS_DELAYED_EVENT      0x08");
T_b("\n");
T_b("#define ");
T_b(te_prefix->define_u);
T_b("NO_FSM_RELEASE_EVENT  0x10");
T_b("\n");
T_b("#define ");
T_b(te_prefix->define_u);
T_b("IS_POLYMORPHIC_EVENT  0x20");
T_b("\n");
T_b("#define ");
T_b(te_prefix->define_u);
T_b("IS_TRUE_EVENT         0x40");
T_b("\n");
T_b("#define ");
T_b(te_prefix->define_u);
T_b("IS_POLY_IN_FLIGHT     0x80");
T_b("\n");
T_b("#define ");
T_b(te_prefix->define_usw);
T_b("UNINITIALIZED_STATE 0");
T_b("\n");
T_b("#define ");
T_b(te_prefix->define_usw);
T_b("EVENT_CANT_HAPPEN ((");
T_b(te_typemap->state_number_name);
T_b(") -1)");
T_b("\n");
T_b("#define ");
T_b(te_prefix->define_usw);
T_b("EVENT_IS_IGNORED  ((");
T_b(te_typemap->state_number_name);
T_b(") -2)");
T_b("\n");
T_b("/* This represents the constant part of the event structure.  */");
T_b("\n");
T_b("typedef struct {");
T_b("\n");
T_b("  ");
T_b(te_typemap->domain_number_name);
T_b(" destination_domain_number;");
T_b("\n");
T_b("  ");
T_b(te_typemap->object_number_name);
T_b(" destination_object_number;");
T_b("\n");
T_b("  ");
T_b(te_typemap->event_number_name);
T_b(" event_number;");
T_b("\n");
T_b("  ");
T_b(te_typemap->event_flags_name);
T_b(" event_flags;");
T_b("\n");
if ( 0==strcmp("SystemC",te_thread->flavor) ) {
T_b("  ");
T_b("sc_event * sc_e;");
T_b("\n");
}
if ( 0==strcmp("C++",te_target->language) ) {
T_b("  ");
T_b("void * thismodule;");
T_b("\n");
}
if ( event_prioritization_needed->result ) {
T_b("  ");
T_b(te_typemap->event_priority_name);
T_b(" priority;");
T_b("\n");
}
T_b("} ");
T_b(te_eq->constant_type);
T_b(";");
T_b("\n");
T_b("/* Structure:  ");
T_b(te_eq->base_event_type);
T_b("\n");
T_b(" ");
T_b("* Base class of application analysis xtUML events.  */");
T_b("\n");
T_b("#define EVENT_BASE_ATTRIBUTE_LIST \");
T_b("  ");
T_b("struct ");
T_b(te_prefix->type);
T_b("xtUMLevent_s * next;\");
if ( event_prioritization_needed->result ) {
T_b("  ");
T_b("struct ");
T_b(te_prefix->type);
T_b("xtUMLevent_s * prev;\");
}
T_b("  ");
T_b(te_instance->handle);
T_b(" object_instance;\");
if ( event_prioritization_needed->result ) {
T_b("  ");
T_b(te_instance->handle);
T_b(" sending_instance;\");
}
T_b("  ");
T_b(te_typemap->domain_number_name);
T_b(" destination_domain_number;\");
T_b("  ");
T_b(te_typemap->object_number_name);
T_b(" destination_object_number;\");
T_b("  ");
T_b(te_typemap->event_number_name);
T_b(" event_number;\");
T_b("  ");
T_b(te_typemap->event_flags_name);
T_b(" event_flags;\");
if ( 0==strcmp("SystemC",te_thread->flavor) ) {
T_b("  ");
T_b("sc_event * sc_e;\");
}
if ( 0==strcmp("C++",te_target->language) ) {
T_b("  ");
T_b("void * thismodule;\");
}
if ( event_prioritization_needed->result ) {
T_b("  ");
T_b(te_typemap->event_priority_name);
T_b(" priority;");
T_b("\n");
}
T_b("struct ");
T_b(te_prefix->type);
T_b("xtUMLevent_s {");
T_b("\n");
T_b("  ");
T_b("EVENT_BASE_ATTRIBUTE_LIST");
T_b("\n");
T_b("};");
T_b("\n");
T_b("typedef struct ");
T_b(te_prefix->type);
T_b("xtUMLevent_s ");
T_b(te_eq->base_event_type);
T_b(";");
T_b("\n");
T_b("typedef unsigned long ETimer_time_t;");
T_b("\n");
if ( te_tim->keyed_timer_support ) {
T_b(te_file->arc_path);
T_b("typedef struct {");
T_b("\n");
T_b("  ");
T_b(te_tim->internal_type);
T_b(" * timer;");
T_b("\n");
T_b("  ");
T_b("u4_t key;");
T_b("\n");
T_b("} ");
T_b(te_prefix->type);
T_b("Timer_t;");
T_b("\n");
} else {
T_b("typedef void ");
T_b(te_prefix->type);
T_b("Timer_t;");
T_b("\n");
}
T_b("/*");
T_b("\n");
T_b(" ");
T_b("* Event Macros");
T_b("\n");
T_b(" ");
T_b("*/");
T_b("\n");
if ( event_prioritization_needed->result ) {
T_b("#define ");
T_b(te_prefix->define_csw);
T_b("GetOoaEventPriority(X) (((X))->priority)");
T_b("\n");
T_b("#define ");
T_b(te_prefix->define_csw);
T_b("SetOoaEventPriority(X, Y) (((X))->priority = Y)");
T_b("\n");
}
T_b("#define ");
T_b(te_prefix->define_csw);
T_b("GetOoaEventFlags(X) (((X))->event_flags)");
T_b("\n");
T_b("#define ");
T_b(te_prefix->define_csw);
T_b("SetOoaEventFlags(X, Y) (((X))->event_flags = Y)");
T_b("\n");
T_b("#define ");
T_b(te_prefix->define_csw);
T_b("GetIsInstanceEvent(X) (");
T_b(te_prefix->define_csw);
T_b("GetOoaEventFlags(X) & ");
T_b(te_prefix->define_u);
T_b("IS_INSTANCE_EVENT)");
T_b("\n");
T_b("#define ");
T_b(te_prefix->define_csw);
T_b("SetIsInstanceEvent(X) (");
T_b(te_prefix->define_csw);
T_b("GetOoaEventFlags(X) |= ");
T_b(te_prefix->define_u);
T_b("IS_INSTANCE_EVENT)");
T_b("\n");
T_b("#define ");
T_b(te_prefix->define_csw);
T_b("GetIsCreationEvent(X) (");
T_b(te_prefix->define_csw);
T_b("GetOoaEventFlags(X) & ");
T_b(te_prefix->define_u);
T_b("IS_CREATION_EVENT)");
T_b("\n");
T_b("#define ");
T_b(te_prefix->define_csw);
T_b("SetIsCreationEvent(X) (");
T_b(te_prefix->define_csw);
T_b("GetOoaEventFlags(X) |= ");
T_b(te_prefix->define_u);
T_b("IS_CREATION_EVENT)");
T_b("\n");
T_b("#define ");
T_b(te_prefix->define_csw);
T_b("GetIsAssignerEvent(X) (");
T_b(te_prefix->define_csw);
T_b("GetOoaEventFlags(X) & ");
T_b(te_prefix->define_u);
T_b("IS_ASSIGNER_EVENT)");
T_b("\n");
T_b("#define ");
T_b(te_prefix->define_csw);
T_b("SetIsAssignerEvent(X) (");
T_b(te_prefix->define_csw);
T_b("GetOoaEventFlags(X) |= ");
T_b(te_prefix->define_u);
T_b("IS_ASSIGNER_EVENT)");
T_b("\n");
T_b("#define ");
T_b(te_prefix->define_csw);
T_b("GetIsDelayedEvent(X)  (");
T_b(te_prefix->define_csw);
T_b("GetOoaEventFlags(X) & ");
T_b(te_prefix->define_u);
T_b("IS_DELAYED_EVENT)");
T_b("\n");
T_b("#define ");
T_b(te_prefix->define_csw);
T_b("SetIsDelayedEvent(X)  (");
T_b(te_prefix->define_csw);
T_b("GetOoaEventFlags(X) |= ");
T_b(te_prefix->define_u);
T_b("IS_DELAYED_EVENT)");
T_b("\n");
T_b("#define ");
T_b(te_prefix->define_csw);
T_b("GetIsPolymorphicEvent(X) (");
T_b(te_prefix->define_csw);
T_b("GetOoaEventFlags(X) & ");
T_b(te_prefix->define_u);
T_b("IS_POLYMORPHIC_EVENT)");
T_b("\n");
T_b("#define ");
T_b(te_prefix->define_csw);
T_b("SetIsPolymorphicEvent(X) (");
T_b(te_prefix->define_csw);
T_b("GetOoaEventFlags(X) |= ");
T_b(te_prefix->define_u);
T_b("IS_POLYMORPHIC_EVENT)");
T_b("\n");
T_b("#define ");
T_b(te_prefix->define_csw);
T_b("ClearIsPolymorphicEvent(X)  (");
T_b(te_prefix->define_csw);
T_b("GetOoaEventFlags(X) &= ~(");
T_b(te_typemap->event_flags_name);
T_b(")");
T_b(te_prefix->define_u);
T_b("IS_POLYMORPHIC_EVENT)");
T_b("\n");
T_b("#define ");
T_b(te_prefix->define_csw);
T_b("GetFsmReleasesEvent(X) (");
T_b(te_prefix->define_csw);
T_b("GetOoaEventFlags(X) & ");
T_b(te_prefix->define_u);
T_b("NO_FSM_RELEASE_EVENT)");
T_b("\n");
T_b("#define ");
T_b(te_prefix->define_csw);
T_b("SetFsmReleasesEvent(X) (");
T_b(te_prefix->define_csw);
T_b("GetOoaEventFlags(X) |= ");
T_b(te_prefix->define_u);
T_b("NO_FSM_RELEASE_EVENT)");
T_b("\n");
T_b("#define ");
T_b(te_prefix->define_csw);
T_b("GetOoaEventNumber(X) (((X))->event_number)");
T_b("\n");
T_b("#define ");
T_b(te_prefix->define_csw);
T_b("SetOoaEventNumber(X, Y) (((X))->event_number = (Y))");
T_b("\n");
T_b("#define ");
T_b(te_prefix->define_csw);
T_b("GetEventTargetInstance(X) (((X))->object_instance)");
T_b("\n");
T_b("#define ");
T_b(te_prefix->define_csw);
T_b("SetEventTargetInstance(X, Y) (((X))->object_instance = (");
T_b(te_instance->handle);
T_b(")(Y))");
T_b("\n");
T_b("#define ");
T_b(te_prefix->define_csw);
T_b("GetEventSendingInstance(X) (((X))->sending_instance)");
T_b("\n");
T_b("#define ");
T_b(te_prefix->define_csw);
T_b("SetEventSendingInstance(X, Y) (((X))->sending_instance = (");
T_b(te_instance->handle);
T_b(")(Y))");
T_b("\n");
T_b("#define ");
T_b(te_prefix->define_csw);
T_b("GetEventDestDomainNumber(X) (((X))->destination_domain_number)");
T_b("\n");
T_b("#define ");
T_b(te_prefix->define_csw);
T_b("SetEventDestDomainNumber(X, Y) (((X))->destination_domain_number = (Y))");
T_b("\n");
T_b("#define ");
T_b(te_prefix->define_csw);
T_b("GetEventDestObjectNumber(X) (((X))->destination_object_number)");
T_b("\n");
T_b("#define ");
T_b(te_prefix->define_csw);
T_b("SetEventDestObjectNumber(X, Y) (((X))->destination_object_number = (Y))");
T_b("\n");
T_b("/* Opaque type definition of a translated state action member function.  */");
T_b("\n");
T_b("typedef _reentrant void (*StateAction_t)( ");
T_b(te_instance->handle);
T_b(", const ");
T_b(te_eq->base_event_type);
T_b(" * const );");
T_b("\n");
T_b("/* Opaque type definition of class event dispatcher member function.  */");
T_b("\n");
T_b("typedef _reentrant void (*EventTaker_t)( ");
T_b(te_eq->base_event_type);
T_b(" * );");
T_b("\n");
T_b("/* Opaque type definition of domain level event dispatcher member function.  */");
T_b("\n");
T_b("typedef _reentrant void (*DomainDispatcher_t)( ");
T_b(te_eq->base_event_type);
T_b(" * );");
T_b("\n");
if ( 0!=strcmp("C",te_target->language) ) {
T_b("/* Structure:  ");
T_b(te_eq->system_events_union);
T_b("\n");
T_b(" ");
T_b("* Provides a default event structure for use while initializing");
T_b("\n");
T_b(" ");
T_b("* the event pool.  */");
T_b("\n");
T_b("typedef union {");
T_b("\n");
T_b("  ");
T_b(te_eq->base_event_type);
T_b(" ");
T_b(te_eq->base_variable);
T_b(";");
T_b("\n");
T_b("} ");
T_b(te_eq->system_events_union);
T_b("_t;");
T_b("\n");
T_b("/* anchor declaration for front and back of list of events */");
T_b("\n");
T_b("typedef struct {");
T_b("\n");
T_b("  ");
T_b(te_eq->base_event_type);
T_b(" * head, * tail;");
T_b("\n");
T_b("} xtUMLEventQueue_t;");
T_b("\n");
T_b("class sys_events {");
T_b("\n");
T_b("protected:");
T_b("\n");
T_b("  ");
T_b("sys_events() {");
T_b("\n");
T_b("      ");
T_b("// This constructor should only be called by the compiler during static");
T_b("\n");
T_b("      ");
T_b("// initialization and never by clients.  Here we don't allocate the");
T_b("\n");
T_b("      ");
T_b("// event pool space during static initialization.");
T_b("\n");
T_b("  ");
T_b("}");
T_b("\n");
T_b("  ");
T_b("sys_events(i_t max_event_size, i_t event_pool_size, i_t num_class_threads) {");
T_b("\n");
if ( non_self_event_queue_needed->result || self_event_queue_needed->result ) {
T_b("    ");
T_b(te_eq->system_event_pool);
T_b(" = (");
T_b(te_eq->system_events_union);
T_b("_t *) operator new (max_event_size * event_pool_size);");
T_b("\n");
if ( non_self_event_queue_needed->result ) {
T_b("    ");
T_b("non_self_event_queue = new xtUMLEventQueue_t[ num_class_threads ];");
T_b("\n");
}
if ( self_event_queue_needed->result ) {
T_b("    ");
T_b("self_event_queue = new xtUMLEventQueue_t[ num_class_threads ];");
T_b("\n");
}
T_b("    ");
T_b("InitializeOoaEventPool( max_event_size, event_pool_size );");
T_b("\n");
T_b("    ");
T_b(te_eq->run_flag);
T_b(" = true;");
T_b("\n");
}
T_b("  ");
T_b("}");
T_b("\n");
T_b("  ");
T_b("~sys_events() {");
T_b("\n");
T_b("    ");
T_b("delete [] ");
T_b(te_eq->system_event_pool);
T_b(";");
T_b("\n");
if ( non_self_event_queue_needed->result ) {
T_b("    ");
T_b("delete [] non_self_event_queue;");
T_b("\n");
}
if ( self_event_queue_needed->result ) {
T_b("    ");
T_b("delete [] self_event_queue;");
T_b("\n");
}
T_b("  ");
T_b("}");
T_b("\n");
T_b("public:");
T_b("\n");
T_b("  ");
T_b(te_eq->system_events_union);
T_b("_t * ");
T_b(te_eq->system_event_pool);
T_b(";");
T_b("\n");
T_b("  ");
T_b(te_eq->base_event_type);
T_b(" * free_event_list;  /* Pointer to head of list of available event nodes.  */");
T_b("\n");
T_b("  ");
T_b("bool ");
T_b(te_eq->run_flag);
T_b(";");
T_b("\n");
if ( non_self_event_queue_needed->result ) {
T_b("  ");
T_b("xtUMLEventQueue_t * non_self_event_queue;");
T_b("\n");
T_b("  ");
T_b(te_eq->base_event_type);
T_b(" * DequeueOoaNonSelfEvent( ");
T_b(dq_arg_type);
T_b(" );");
T_b("\n");
}
if ( self_event_queue_needed->result ) {
T_b("  ");
T_b("xtUMLEventQueue_t * self_event_queue;");
T_b("\n");
T_b("  ");
T_b(te_eq->base_event_type);
T_b(" * DequeueOoaSelfEvent( ");
T_b(dq_arg_type);
T_b(" );");
T_b("\n");
}
}
T_b(te_eq->base_event_type);
T_b(" * ");
T_b(te_eq->allocate);
T_b("( void );");
T_b("\n");
T_b(te_eq->base_event_type);
T_b(" * ");
T_b(te_eq->new);
T_b("( const void * const, const ");
T_b(te_eq->constant_type);
T_b(" * const );");
T_b("\n");
T_b(te_eq->base_event_type);
T_b(" * ");
T_b(te_eq->modify);
T_b("( ");
T_b(te_eq->base_event_type);
T_b(" *, const ");
T_b(te_eq->constant_type);
T_b(" * const );");
T_b("\n");
T_b("void ");
T_b(te_eq->delete);
T_b("( ");
T_b(te_eq->base_event_type);
T_b(" * );");
T_b("\n");
T_b("void ");
T_b(te_prefix->symbolsw);
T_b("InitializeOoaEventPool( ");
if ( 0==strcmp("C",te_target->language) ) {
T_b("void );");
T_b("\n");
} else {
T_b("i_t, i_t );");
T_b("\n");
}
T_b("void ");
T_b(te_prefix->result);
T_b("xtUML_run( void );");
T_b("\n");
T_b("void * ");
T_b(te_instance->global_self);
T_b("( void );");
T_b("\n");
T_b("void ");
T_b(te_eq->non_self);
T_b("( ");
T_b(te_eq->base_event_type);
T_b(" * );");
T_b("\n");
T_b("void ");
T_b(te_eq->self);
T_b("( ");
T_b(te_eq->base_event_type);
T_b(" * );");
T_b("\n");
if ( te_tim->timer_event_search_and_destroy ) {
T_b("bool ");
T_b(te_eq->search_and_destroy);
T_b("( ");
T_b(te_eq->base_event_type);
T_b(" * );");
T_b("\n");
}
if ( te_sys->AUTOSAR ) {
T_b("void * ooa_loop( void * );");
T_b("\n");
} else if ( 0==strcmp("C++",te_target->language) ) {
T_b("  ");
T_b("void ooa_loop( void * );");
T_b("\n");
T_b("  ");
T_b("virtual EventTaker_t * ");
T_b(te_instance->get_event_dispatcher);
T_b("( void ) { return 0; }");
T_b("\n");
if ( te_thread->enabled ) {
T_b("  ");
T_b("virtual ");
T_b(te_typemap->object_number_name);
T_b(" * ");
T_b(te_instance->get_thread_assignment);
T_b("( void ) { return 0; }");
T_b("\n");
}
}
if ( 0!=strcmp("C",te_target->language) ) {
T_b("};");
T_b("\n");
}
T_b(te_file->arc_path);
if ( not_empty tim_te_ee ) {
T_b("#include \"");
T_b(te_file->tim);
T_b(".");
T_b(te_file->hdr_file_ext);
T_b("\"");
T_b("\n");
}
