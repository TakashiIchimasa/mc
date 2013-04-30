/*----------------------------------------------------------------------------
 * File:  sys_user_co.c
 *
 * Description:
 * Function definitions for user supplied (non-translated) call out entry
 * points in the generated application.
 *
 * (C) Copyright 1998-2009 Mentor Graphics Corporation.  All rights reserved.
 *--------------------------------------------------------------------------*/

#include "sys_sys_types.h"
#include "sys_user_co.h"

#ifdef SYS_USER_CO_PRINTF_ON
#include <stdio.h>
#define SYS_USER_CO_PRINTF( s ) printf( s );
#else
#define SYS_USER_CO_PRINTF( s )
#endif

/*
 * UserInitializationCallout
 *
 * This function is invoked at the immediate beginning of application
 * initialization. It is the very first function to be executed at system
 * startup.
 * User supplied implementation of this function should be restricted to
 * things like memory initialization, early hardware duties, etc.
 */
char DTD[256];
void
UserInitializationCalloutf( c_t * argv0 )
{
  /* Starting with the argv[0], add the path to the DocBook DTD.
     Also use only forward slashes.  */
  char * continuation;
  i_t i = 0;
  Escher_strcpy( DTD, argv0 );
  continuation = strstr( DTD, "docgen" );
  Escher_strcpy( continuation, "docgen/docbook/docbook-xml-4.5/docbookx.dtd" );
  for ( i = 0; i < 256, 0 != DTD[ i ]; i++ ) {
    DTD[ i ] = ( DTD[ i ] == '\\' ) ? '/' : DTD[ i ];
  }
  /* Activate this invocation to initialize the example simple TIM.  */
  #if ESCHER_SYS_MAX_XTUML_TIMERS > 0
  TIM_init();
  #endif
  /* Insert implementation specific code here.  */
  SYS_USER_CO_PRINTF( "UserInitializationCallout\n" )
}

/*
 * UserPreOoaInitializationCallout
 *
 * This function is invoked immediately prior to executing any xtUML
 * initialization functions.
 */
void
UserPreOoaInitializationCalloutf( void )
{
  /* Insert implementation specific code here.  */
  static char * a[2] = { "UserPostOoaInitializationCalloutf", "a.xtuml" };
  Escher_xtUML_load( 2, a );
  SYS_USER_CO_PRINTF( "UserPreOoaInitializationCallout\n" )
}

/*
 * UserPostOoaInitializationCallout
 *
 * This function is invoked immediately after executing any xtUML
 * initialization functions.
 * When this callout function returns, the system dispatcher will allow the
 * xtUML application analysis state models to start consuming events.
 */
void
UserPostOoaInitializationCalloutf( void )
{
  /* Insert implementation specific code here.  */
  SYS_USER_CO_PRINTF( "UserPostOoaInitializationCallout\n" )
}

/*
 * UserBackgroundProcessingCallout
 *
 * This function is invoked once during each loop execution of the system
 * dispather.
 * It is invoked at the 'top' of the system dispatcher loop, immediately
 * prior to dispatching any xtUML application analysis events.
 */
void
UserBackgroundProcessingCalloutf( void )
{
/* Activate this invocation to periodically tick the example simple TIM.  */
  #if ESCHER_SYS_MAX_XTUML_TIMERS > 0
  TIM_tick();
  #endif
  /* Insert implementation specific code here.  */
}

/*
 * UserPreShutdownCallout
 *
 * This function is invoked at termination of the system dispatcher, but
 * prior to performing any xtUML application analysis shutdown sequencing.
 */
void
UserPreShutdownCalloutf( void )
{
  /* Insert implementation specific code here.  */
  SYS_USER_CO_PRINTF( "UserPreShutdownCallout\n" )
}

/*
 * UserPostShutdownCallout
 *
 * This function is invoked immediately before application exit.
 */
void
UserPostShutdownCalloutf( void )
{
  /* Insert implementation specific code here.  */
  SYS_USER_CO_PRINTF( "UserPostShutdownCallout\n" )
}

/*
 * UserEventCantHappenCallout
 *
 * This function is invoked any time that an event is received that
 * results in a "cant happen" transition.
 */
void
UserEventCantHappenCalloutf(
  const Escher_StateNumber_t current_state,
  const Escher_StateNumber_t next_state,
  const Escher_EventNumber_t event_number )
{
  /* Insert implementation specific code here.  */
  SYS_USER_CO_PRINTF( "UserEventCantHappenCallout\n" )
}

/*
 * UserEventNoInstanceCallout
 *
 * This function is invoked when we failed to validate the instance
 * to which an event was directed.  This can happen in normal operation
 * when the instance was deleted while the event was in flight (analysis
 * error).
 */
void
UserEventNoInstanceCalloutf(
  const Escher_EventNumber_t event_number )
{
  /* Insert implementation specific code here.  */
  SYS_USER_CO_PRINTF( "UserEventNoInstanceCallout\n" )
}

/*
 * UserEventFreeListEmptyCallout
 *
 * This function is invoked when an attempt is made to allocate an
 * event, but there are no more left.
 */
void
UserEventFreeListEmptyCalloutf( void )
{
  /* Insert implementation specific code here.  */
  SYS_USER_CO_PRINTF( "UserEventFreeListEmptyCallout\n" )
}

/*
 * UserEmptyHandleDetectedCallout
 *
 * This function is invoked when an attempt is made to use an instance
 * reference variable (handle) that is null (empty).
 */
void
UserEmptyHandleDetectedCalloutf( c_t * object_keyletters, c_t * s )
{
  /* Insert implementation specific code here.  */
  SYS_USER_CO_PRINTF( "UserEmptyHandleDetectedCallout\n" )
}

/*
 * UserObjectPoolEmptyCallout
 *
 * This function is invoked when an attempt is made to create an
 * instance of an object, but there are no instances available.
 */
void
UserObjectPoolEmptyCalloutf( c_t * domain, c_t * object_name )
{
  /* Insert implementation specific code here.  */
  SYS_USER_CO_PRINTF( "UserObjectPoolEmptyCallout\n" )
}

/*
 * UserNodeListEmptyCallout
 *
 * This function is invoked when an attempt is made to allocate a
 * node, but there are no more left.
 */
void
UserNodeListEmptyCalloutf( void )
{
  /* Insert implementation specific code here.  */
  SYS_USER_CO_PRINTF( "UserNodeListEmptyCallout\n" )
}

/*
 * UserInterleavedBridgeOverflowCallout
 *
 * This function is invoked when an attempt is made to post too many
 * interleaved bridges.  The depth of this list is defined by
 * SYS_MAX_INTERLEAVED_BRIDGES (unless changed in the archetype).
 */
void
UserInterleavedBridgeOverflowCalloutf( void )
{
  /* Insert implementation specific code here.  */
  SYS_USER_CO_PRINTF( "UserInterleavedBridgeOverflowCallout\n" )
}

/*
 * UserSelfEventQueueEmptyCallout
 *
 * This function is invoked when the events to self queue is
 * interrogated and found to be empty.
 */
void
UserSelfEventQueueEmptyCalloutf( void )
{
  /* Insert implementation specific code here.  */
}

/*
 * UserNonSelfEventQueueEmptyCallout
 *
 * This function is invoked when the events to instance queue is
 * interrogated and found to be empty.
 */
void
UserNonSelfEventQueueEmptyCalloutf( void )
{
  /* Insert implementation specific code here.  */
}

/*
 * UserPersistenceErrorCallout
 *
 * This function is invoked when the events to instance queue is
 * interrogated and found to be empty.
 */
void
UserPersistenceErrorCalloutf( i_t error_code )
{
  /* Insert implementation specific code here.  */
  SYS_USER_CO_PRINTF( "UserPersistenceErrorCallout\n" )
}