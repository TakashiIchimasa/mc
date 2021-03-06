T_b("/*---------------------------------------------------------------------");
T_b("\n");
T_b(" ");
T_b("* File:  ");
T_b(te_file->thread);
T_b(".");
T_b(te_file->src_file_ext);
T_b("\n");
T_b(" ");
T_b("*");
T_b("\n");
T_b(" ");
T_b("* Description:");
T_b("\n");
T_b(" ");
T_b("* This file provides implementation of multi-tasking/threading");
T_b("\n");
T_b(" ");
T_b("* capabilities allowing classes/subsystems to run in different");
T_b("\n");
T_b(" ");
T_b("* threads on a multi-tasking/threading OS/RTOS.");
T_b("\n");
T_b(" ");
T_b("*");
T_b("\n");
T_b(" ");
T_b("* ");
T_b(te_copyright->body);
T_b("\n");
T_b(" ");
T_b("*-------------------------------------------------------------------*/");
T_b("\n");
T_b("#include <windows.h>   /* MS Windows declarations */");
T_b("\n");
T_b("#include <process.h>");
T_b("\n");
T_b("#include <stdio.h>");
T_b("\n");
T_b("#include \"");
T_b(te_file->types);
T_b(".");
T_b(te_file->hdr_file_ext);
T_b("\"");
T_b("\n");
T_b("static HANDLE mutices[ SEMAPHORE_FLAVOR_MAX ];");
T_b("\n");
T_b("static HANDLE nonbusy_wait_cond[ NUM_OF_TOTAL_THREADS ];");
T_b("\n");
T_b("static u1_t threadnumber[ NUM_OF_TOTAL_THREADS ];");
T_b("\n");
T_b("/*");
T_b("\n");
T_b(" ");
T_b("* Initialize those structures that need to be set up once at system");
T_b("\n");
T_b(" ");
T_b("* bring-up time.");
T_b("\n");
T_b(" ");
T_b("*/");
T_b("\n");
T_b("void ");
T_b(te_prefix->result);
T_b("InitializeThreading( void )");
T_b("\n");
T_b("{");
T_b("\n");
T_b("  ");
T_b("u1_t i;");
T_b("\n");
T_b("  ");
T_b("for ( i = 0; i < NUM_OF_TOTAL_THREADS; i++ ) {");
T_b("\n");
T_b("    ");
T_b("threadnumber[ i ] = i;");
T_b("\n");
T_b("    ");
T_b("nonbusy_wait_cond[ i ] = CreateSemaphore( NULL, 0, 1, NULL );");
T_b("\n");
T_b("  ");
T_b("}");
T_b("\n");
T_b("  ");
T_b("for ( i = 0; i < SEMAPHORE_FLAVOR_MAX; i++ ) {");
T_b("\n");
T_b("    ");
T_b("mutices[i] = CreateSemaphore( NULL, 0, 1, NULL );");
T_b("\n");
T_b("  ");
T_b("}");
T_b("\n");
T_b("}");
T_b("\n");
T_b("/*");
T_b("\n");
T_b(" ");
T_b("* Obtain a resource lock so that this thread has mutually exclusive");
T_b("\n");
T_b(" ");
T_b("* access.");
T_b("\n");
T_b(" ");
T_b("*/");
T_b("\n");
T_b("void ");
T_b(te_thread->mutex_lock);
T_b("( const u1_t flavor )");
T_b("\n");
T_b("{");
T_b("\n");
T_b("  ");
T_b("ReleaseSemaphore(mutices[ flavor ], 1, NULL);");
T_b("\n");
T_b("}");
T_b("\n");
T_b("/*");
T_b("\n");
T_b(" ");
T_b("* Release a resource lock that was obtained with the lock method.");
T_b("\n");
T_b(" ");
T_b("*/");
T_b("\n");
T_b("void ");
T_b(te_thread->mutex_unlock);
T_b("( const u1_t flavor )");
T_b("\n");
T_b("{");
T_b("\n");
T_b("  ");
T_b("ReleaseSemaphore(mutices[ flavor ], 1, NULL);");
T_b("\n");
T_b("}");
T_b("\n");
T_b("/*");
T_b("\n");
T_b(" ");
T_b("* Go into a non-busy wait state waiting on someone to wake us");
T_b("\n");
T_b(" ");
T_b("* up with the nonbusy_wake method.");
T_b("\n");
T_b(" ");
T_b("*/");
T_b("\n");
T_b("void ");
T_b(te_thread->nonbusy_wait);
T_b("( const u1_t thread )");
T_b("\n");
T_b("{");
T_b("\n");
T_b("  ");
T_b("HANDLE dwc;");
T_b("\n");
T_b("  ");
T_b(te_thread->mutex_lock);
T_b("( SEMAPHORE_FLAVOR_NONBUSY );");
T_b("\n");
T_b("  ");
T_b("dwc = nonbusy_wait_cond[thread];");
T_b("\n");
T_b("  ");
T_b(te_thread->mutex_unlock);
T_b("( SEMAPHORE_FLAVOR_NONBUSY );");
T_b("\n");
T_b("  ");
T_b("if ( thread == 0 ) {");
T_b("\n");
T_b("    ");
T_b("/*");
T_b("\n");
T_b("     ");
T_b("* At least one thread has to wake up and service any");
T_b("\n");
T_b("     ");
T_b("* pending delayed events.  We let thread 0 do this.");
T_b("\n");
T_b("     ");
T_b("* So, thread 0 will only block a maximum of 10ms. Other ");
T_b("\n");
T_b("     ");
T_b("* threads will block forever waiting for the send event ");
T_b("\n");
T_b("     ");
T_b("* to wake them.");
T_b("\n");
T_b("     ");
T_b("*/");
T_b("\n");
T_b("    ");
T_b("WaitForSingleObject( dwc, 10 );");
T_b("\n");
T_b("  ");
T_b("} else {");
T_b("\n");
T_b("    ");
T_b("WaitForSingleObject( dwc, INFINITE );");
T_b("\n");
T_b("  ");
T_b("}");
T_b("\n");
T_b("}");
T_b("\n");
T_b("/*");
T_b("\n");
T_b(" ");
T_b("* Wake up a thread that went to sleep waiting for something to happen.");
T_b("\n");
T_b(" ");
T_b("*/");
T_b("\n");
T_b("void ");
T_b(te_thread->nonbusy_wake);
T_b("( const u1_t thread )");
T_b("\n");
T_b("{");
T_b("\n");
T_b("  ");
T_b(te_thread->mutex_lock);
T_b("( SEMAPHORE_FLAVOR_NONBUSY );");
T_b("\n");
T_b("  ");
T_b("ReleaseSemaphore( nonbusy_wait_cond[ thread ], 1, NULL );");
T_b("\n");
T_b("  ");
T_b(te_thread->mutex_unlock);
T_b("( SEMAPHORE_FLAVOR_NONBUSY );");
T_b("\n");
T_b("}");
T_b("\n");
T_b("/*");
T_b("\n");
T_b(" ");
T_b("* Create and spin off a task/thread to run the input routine.");
T_b("\n");
T_b(" ");
T_b("*/");
T_b("\n");
T_b("void ");
T_b(te_thread->create);
T_b("( void *(routine)(void *), const u1_t i )");
T_b("\n");
T_b("{");
T_b("\n");
T_b("  ");
T_b("_beginthread( (void *) routine, 0, (void*)&(threadnumber[i]) );");
T_b("\n");
T_b("}");
T_b("\n");
T_b("/*");
T_b("\n");
T_b(" ");
T_b("* Cleanup the structures initialized in ");
T_b(te_prefix->result);
T_b("InitializeThreading.");
T_b("\n");
T_b(" ");
T_b("*/");
T_b("\n");
T_b("void ");
T_b(te_thread->shutdown);
T_b("( void )");
T_b("\n");
T_b("{");
T_b("\n");
T_b("  ");
T_b("u1_t i;");
T_b("\n");
T_b("  ");
T_b("for ( i = 0; i < NUM_OF_TOTAL_THREADS; i++ ) {");
T_b("\n");
T_b("    ");
T_b("CloseHandle( nonbusy_wait_cond[ i ] );");
T_b("\n");
T_b("    ");
T_b("nonbusy_wait_cond[ i ] = 0;");
T_b("\n");
T_b("  ");
T_b("}");
T_b("\n");
T_b("  ");
T_b("for ( i = 0; i < SEMAPHORE_FLAVOR_MAX; i++ ) {");
T_b("\n");
T_b("    ");
T_b("CloseHandle( mutices[ i ] );");
T_b("\n");
T_b("    ");
T_b("mutices[ i ] = 0;");
T_b("\n");
T_b("  ");
T_b("}");
T_b("\n");
T_b("}");
T_b("\n");
