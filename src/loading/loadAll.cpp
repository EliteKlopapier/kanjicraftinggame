#include "loading.h"

namespace loading {

void loadAll() {
    loadRecipes();
    loadMeanings();
    loadFreeType();
    loadCharacterFlags();
}

} // namespace loading