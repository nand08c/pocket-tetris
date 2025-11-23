
#include "tetris.h"

#include "types.h"

static piece_t tetris[(Xlimit * Ylimit) >> 2];

bool check_colission(piece_t* p) { return true; }
bool piece_rotate(piece_t* p) { return true; }
