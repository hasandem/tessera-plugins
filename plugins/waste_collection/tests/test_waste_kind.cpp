#include "../components/waste_collection/waste_kind.h"
#include <cassert>

using esphome::waste_collection::WasteKind;
using esphome::waste_collection::waste_kind;

int main() {
  for (const char *name : {"Papir", "Papp og kartong", "PAPP/PAPIR/DRIKKEKARTONG", "Paper", "Papier", "Cardboard"})
    assert(waste_kind(name) == WasteKind::PAPER);
  for (const char *name : {"Matavfall", "HAGEAVFALL", "Food waste", "Organic", "GFT", "Groenafval"})
    assert(waste_kind(name) == WasteKind::ORGANIC);
  for (const char *name : {"Plast", "PLASTEMBALLASJE", "Emballasje", "Plastic", "PMD", "Verpakking", "Blik"})
    assert(waste_kind(name) == WasteKind::PLASTIC);
  for (const char *name : {"Glass", "Glass- og metallemballasje", "METALLEMBALLASJE", "Metall", "Glas", "Glass packaging"})
    assert(waste_kind(name) == WasteKind::GLASS_METAL);
  for (const char *name : {"Restavfall", "RESTAFVAL", "Residual waste", "Ukjent avfall", ""})
    assert(waste_kind(name) == WasteKind::GENERAL);
}
