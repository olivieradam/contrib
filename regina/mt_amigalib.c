/* This is the file to support single-threading.
 * We initialize the global data structure and the global access variable.
 */

#if !defined(__AROS__) && !defined(_AMIGA)
# error mt_amiga.c only works on Amiga or AROS
#endif

#include "rexx.h"

#include <exec/memory.h>
#include <exec/semaphores.h>
#include <exec/lists.h>
#include <exec/nodes.h>

APTR __regina_semaphorepool;
struct MinList *__regina_tsdlist = NULL;

typedef struct _mt_tsd_t {
  APTR mempool;
} mt_tsd_t;

typedef struct _tsd_node_t {
  struct MinNode node;
  struct Task *task;
  tsd_t *TSD;
} tsd_node_t;


/* Lowest level memory allocation function for normal circumstances. */
static void *MTMalloc(const tsd_t *TSD,size_t size)
{
   mt_tsd_t *mt = (mt_tsd_t *)TSD->mt_tsd;
   void *mem;

   size += sizeof(size_t);
   mem = AllocPooled( mt->mempool, size);
   *((size_t*)mem)=size;

  return (void *)(((char *)mem)+sizeof(size_t));
}

/* Lowest level memory deallocation function for normal circumstances. */
static void MTFree(const tsd_t *TSD,void *chunk)
{
   mt_tsd_t *mt = (mt_tsd_t *)TSD->mt_tsd;
   APTR mem = (APTR)(((char *)chunk)-sizeof(size_t));
  
   FreePooled( mt->mempool, (APTR)mem, *(size_t *)mem );
}

/* Lowest level exit handler. Use this indirection to prevent errors. */
static void MTExit(int code)
{
   exit(code);
}

static void cleanup(void)
{
  struct Task *thistask = FindTask(NULL);
  tsd_node_t *node;
  mt_tsd_t *mt;

  node = (tsd_node_t *)GetHead(__regina_tsdlist);
  while (node!=NULL && node->task!=thistask)
    node = (tsd_node_t *)GetSucc(node);
  if (node==NULL)
  {
    fputs("!!!NODE==NULL!!!", stderr);
  }

  mt = (mt_tsd_t *)node->TSD->mt_tsd;
  DeletePool( mt->mempool );

  node->TSD = NULL; /* Node is not removed to avoid the need of Forbid/Permit during searching of the list */
}

tsd_t *ReginaInitializeThread(void)
{
   int OK;

   tsd_t *__regina_tsd = malloc(sizeof(tsd_t));
   mt_tsd_t *mt;
  
   /* Default all values to zero        */
   memset(__regina_tsd,0,sizeof(tsd_t));
   __regina_tsd->MTMalloc = MTMalloc;
   __regina_tsd->MTFree = MTFree;
   __regina_tsd->MTExit = MTExit;

   OK = ( __regina_tsd->mt_tsd = malloc(sizeof(mt_tsd_t))) != NULL;
   mt = (mt_tsd_t *)__regina_tsd->mt_tsd;
   OK |= ( mt->mempool = CreatePool(MEMF_PUBLIC, 8192, 1024) ) != NULL;

   OK |= init_memory(__regina_tsd);     /* Initialize the memory module FIRST*/

   /* Without the initial memory we don't have ANY chance! */
   if (!OK)
      return(NULL);

   OK |= init_vars(__regina_tsd);      /* Initialize the variable module    */
   OK |= init_stacks(__regina_tsd);    /* Initialize the stack module       */
   OK |= init_filetable(__regina_tsd); /* Initialize the files module       */
   OK |= init_math(__regina_tsd);      /* Initialize the math module        */
   OK |= init_spec_vars(__regina_tsd); /* Initialize the interprt module    */
   OK |= init_tracing(__regina_tsd);   /* Initialize the tracing module     */
   OK |= init_builtin(__regina_tsd);   /* Initialize the builtin module     */
   OK |= init_client(__regina_tsd);    /* Initialize the client module      */
   OK |= init_library(__regina_tsd);   /* Initialize the library module     */
   OK |= init_rexxsaa(__regina_tsd);   /* Initialize the rexxsaa module     */
   OK |= init_shell(__regina_tsd);     /* Initialize the shell module       */
   OK |= init_envir(__regina_tsd);     /* Initialize the envir module       */
   OK |= init_expr(__regina_tsd);      /* Initialize the expr module        */
#ifdef VMS
   OK |= init_vms(__regina_tsd);       /* Initialize the vmscmd module      */
   OK |= init_vmf(__regina_tsd);       /* Initialize the vmsfuncs module    */
#endif
   OK |= init_amigaf(__regina_tsd);    /* Initialize the amigafuncs module  */
   __regina_tsd->loopcnt = 1;            /* stupid r2perl-module              */
   __regina_tsd->traceparse = -1;
   __regina_tsd->thread_id = 1;

   /* Initiliaze thread specific data */
   if (!OK)
      exiterror( ERR_STORAGE_EXHAUSTED, 0 ) ;

   return(__regina_tsd);
}

void AmigaLockSemaphore(struct SignalSemaphore **semaphoreptr)
{
  if (*semaphoreptr == NULL)
  {
    Forbid();

    if (*semaphoreptr == NULL)
    {
      *semaphoreptr = AllocPooled (__regina_semaphorepool, sizeof(struct SignalSemaphore));
      InitSemaphore(*semaphoreptr);
    }

    Permit();
  }

  ObtainSemaphore(*semaphoreptr);
}

void AmigaUnlockSemaphore(struct SignalSemaphore *semaphore)
{
  assert(semaphore!=NULL);
  ReleaseSemaphore(semaphore);
}


tsd_t *__regina_get_tsd(void)
{
  struct Task *thistask = FindTask(NULL);
  tsd_node_t *node;

  /* Allocate list of TSDs if it is not yet present */
  if (__regina_tsdlist == NULL)
  {
    Forbid();
    
    if (__regina_tsdlist == NULL)
    {
      __regina_tsdlist = (struct MinList *)AllocPooled (__regina_semaphorepool, sizeof(struct MinList));
      NewList(__regina_tsdlist);
    }
    
    Permit();
  }

  node = (tsd_node_t *)GetHead(__regina_tsdlist);
  while (node!=NULL && node->task!=thistask)
    node = (tsd_node_t *)GetSucc(node);
  
  if (node==NULL)
  {
    /* taskdata not found */
    node = (tsd_node_t *)AllocPooled(__regina_semaphorepool, sizeof(tsd_node_t));
    node->task = thistask;
    node->TSD = ReginaInitializeThread();
    AddTail(__regina_tsdlist, node);
    atexit(cleanup);
  }
  else if (node->TSD==NULL) /* Was MTExit called on this task ? */
  {
    node->TSD = ReginaInitializeThread();
    atexit(cleanup);
  }

  return node->TSD;
}
