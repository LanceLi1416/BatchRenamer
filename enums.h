#ifndef BATCHRENAMER_ENUMS_H
#define BATCHRENAMER_ENUMS_H

namespace core {
    enum MODE {
        NAME, EXT, NAME_AND_EXT
    };

    enum FORMAT {
        ORIG_TXT_NUM, NUM_TXT_ORIG, TXT_NUM, NUM_TXT
    };
}

namespace gui {
    enum TYPE {
        FIND_AND_REPL, NUM, SET_EXT, REM_TXT
    };
}

#endif //BATCHRENAMER_ENUMS_H
