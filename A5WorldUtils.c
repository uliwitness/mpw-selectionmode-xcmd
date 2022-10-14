#include "A5WorldUtils.h"
#include <OSUtils.h>

void MakeA5World(A5RefType *outA5Ref) {
    *outA5Ref = NewHandle(A5Size());
    if (*outA5Ref != NULL) {
        HLock(*outA5Ref);
        A5Init( (Ptr) (((long)**outA5Ref) + A5Size() - kAppParmsSize) );
        HUnlock(*outA5Ref);
    }
}

long SetA5World(A5RefType inA5Ref) {
    HLock(inA5Ref);
    return SetA5( ((long)*inA5Ref) + A5Size() - kAppParmsSize );
}

void RestoreA5World(long oldA5, A5RefType inA5Ref) {
    (void)SetA5(oldA5);
    HUnlock(inA5Ref);
}

void DisposeA5World(A5RefType inA5Ref) {
    DisposeHandle(inA5Ref);
}

long OpenA5World(A5RefType *outA5Ref) {
    MakeA5World(outA5Ref);
    if (*outA5Ref) {
        return SetA5World(*outA5Ref);
    } else {
        return 0;
    }
}

void CloseA5World(long oldA5, A5RefType inA5Ref) {
    RestoreA5World(oldA5, inA5Ref);
    DisposeA5World(inA5Ref);
}
