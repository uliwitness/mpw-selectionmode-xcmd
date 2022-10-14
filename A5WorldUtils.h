#ifndef A5WORLDUTILS_H
#define A5WORLDUTILS_H

#include <Memory.h>

#define kAppParmsSize 32

typedef Handle A5RefType;

// MacRuntime.o routines:
extern long A5Size();
extern void A5Init(Ptr myA5);

/* MakeA5World allocates space for an A5 world based on the
    size of the global variables defined by the module and its
    units. If sufficient space is not available, MakeA5World
    returns NIL for A5Ref and further initialization is aborted. */
void MakeA5World(A5RefType *outA5Ref);

/* SetA5World locks down a previously-allocated handle containing
    an A5 world and sets the A5 register appropriately. The return
    value is the old value of A5 and the client should save it for
    use by RestoreA5World. */
long SetA5World(A5RefType inA5Ref);

/* RestoreA5World restores A5 to its original value (which the
    client should have saved) and unlocks the A5 world to avoid
    heap fragmentation in cases where the world is used again. */
void RestoreA5World(long oldA5, A5RefType inA5Ref);

/* DisposeA5World simply disposes of the A5 world handle. */
void DisposeA5World(A5RefType inA5Ref);

/* OpenA5World combines MakeA5World and SetA5World for the majority
    of cases in which these two routines are called consecutively. An
    exception is when a single A5 world is invoked many times. In this
    case, the world is only created once with MakeA5World and it is
    invoked each time by SetA5World. Most developers will find it easier
    just to call OpenA5World and CloseA5World at the end. If the memory
    allocation request fails, OpenA5World returns NIL for A5Ref and zero
    in the function result. */
long OpenA5World(A5RefType *outA5Ref);

/* CloseA5World is the dual of OpenA5World. It combines RestoreA5World
    and DisposeA5World. Again, in certain cases it may be necessary to
    call those two routines explicitly, but most of the time CloseA5World
    is all that is required. */
void CloseA5World(long oldA5, A5RefType inA5Ref);

#endif //A5WORLDUTILS_H
